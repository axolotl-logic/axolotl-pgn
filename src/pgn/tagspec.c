#include "tagspec.h"

#include <assert.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common/satoi.h"
#include "common/smalloc.h"

tagcmp_t *tagcmp_new(const char *name, const char *value, tagcmp_kind_t kind)
{
        tagcmp_t *cmp = smalloc(sizeof(*cmp));

        cmp->name = strdup(name);
        cmp->value = value == NULL ? NULL : strdup(value);
        cmp->kind = kind;

        return cmp;
}

tagorder_t *tagorder_new(const char *name)
{
        tagorder_t *tag = smalloc(sizeof(*tag));

        tag->name = strdup(name);

        return tag;
}

void tagorder_free(tagorder_t *tag)
{
        while (tag != NULL) {
                tagorder_t *next = tag->next;

                free(tag->name);
                free(tag);

                tag = next;
        }
}

void tagspec_add(tagspec_t *spec, const char *name, const char *value,
                 tagcmp_kind_t kind)
{
        tagcmp_t *cmp = tagcmp_new(name, value, kind);

        if (spec->head == NULL) {
                spec->head = cmp;
                spec->tail = cmp;
        } else {
                spec->tail->next = cmp;
                spec->tail = spec->tail->next;
        }

        tagorder_t *tag = tagorder_new(name);

        if (spec->order_head == NULL) {
                spec->order_head = tag;
                spec->order_tail = tag;
        } else {
                spec->order_tail->next = tag;
                spec->order_tail = spec->order_tail->next;
        }
}

tagspec_t *tagspec_new(void)
{
        tagspec_t *tags = smalloc(sizeof(*tags));

        return tags;
}

void tagcmp_free(tagcmp_t *cmp)
{
        while (cmp != NULL) {
                tagcmp_t *next = cmp->next;

                free(cmp->name);
                free(cmp->value);
                free(cmp);

                cmp = next;
        }
}

void tagspec_free(tagspec_t *spec)
{
        if (spec == NULL) {
                return;
        }

        tagcmp_free(spec->head);
        tagorder_free(spec->order_head);

        free(spec);
}

tagcmp_kind_t tagspec_get_kind(char opperator)
{
        tagcmp_kind_t result = TAG_UNKNOWN_CMP;
        switch (opperator) {
        case '!':
                result = TAG_NOT_EQUALS;
                break;
        case '=':
                result = TAG_EQUALS;
                break;
        case '-':
                result = TAG_NOT_CONTAINS;
                break;
        case '~':
                result = TAG_CONTAINS;
                break;
        case '>':
                result = TAG_GREATER_THAN;
                break;
        default:
                break;
        }

        return result;
}

bool tagspec_parse_line(tagspec_t *spec, const char *line)
{
        char line_copy[TAGSPEC_FIELD_SIZE * 3] = { '\0' };

        strncpy(line_copy, line, sizeof(line_copy) / sizeof(line_copy[0]));
        char *save_ptr = NULL;
        char *name = strtok_r(line_copy, " ", &save_ptr);
        char *cmp = strtok_r(NULL, " ", &save_ptr);
        char *value = strtok_r(NULL, "\n", &save_ptr);

        tagcmp_kind_t kind = cmp == NULL ? TAG_ALWAYS :
                                           tagspec_get_kind(cmp[0]);

        if (kind == TAG_UNKNOWN_CMP) {
                return false;
        }

        tagspec_add(spec, name, value, kind);

        return true;
}

void tagspec_load(tagspec_t *spec, FILE *spec_fp)
{
        char *line = NULL;
        size_t line_len = 0;
        while (getline(&line, &line_len, spec_fp) != -1) {
                bool success = tagspec_parse_line(spec, line);
                assert(success);
        }

        free(line);
}

bool tagspec_matches_value(const tagcmp_t *cmp, const char *value)
{
        switch (cmp->kind) {
        case TAG_EQUALS:
                return strcmp(value, cmp->value) == 0;
        case TAG_NOT_EQUALS:
                return strcmp(value, cmp->value) != 0;
        case TAG_CONTAINS:
                return strstr(value, cmp->value) != NULL;
        case TAG_NOT_CONTAINS:
                return strstr(value, cmp->value) == NULL;
        case TAG_GREATER_THAN:
                return satoi(value) > satoi(cmp->value);
        case TAG_ALWAYS:
                return true;
        default:
                assert(fputs("Unknown operator", stderr));
                assert(false && "unimplemented");
        }

        return false;
}

bool tagspec_matches(tagspec_t *spec, const char *name, const char *value)
{
        for (tagcmp_t *cmp = spec->head; cmp != NULL; cmp = cmp->next) {
                if (strcmp(name, cmp->name) != 0) {
                        continue;
                }

                if (!tagspec_matches_value(cmp, value)) {
                        return false;
                }
        }

        return true;
}
