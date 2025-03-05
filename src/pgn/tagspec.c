#include "tagspec.h"

#include "common/scan_ssv.h"
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
        cmp->value = strdup(value);
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
        if (kind != TAG_ALWAYS) {
                tagcmp_t *cmp = tagcmp_new(name, value, kind);

                if (spec->head == NULL) {
                        spec->head = cmp;
                        spec->tail = cmp;
                } else {
                        spec->tail->next = cmp;
                        spec->tail = spec->tail->next;
                }
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
        size_t cursor = 0;
        char *name = scan_ssv(line, &cursor);
        char *cmp = scan_ssv(line, &cursor);
        char *value = scan_ssv(line, &cursor);

        bool success = false;
        if (name[0] != '\0' && value[0] != '\0') {
                assert(cmp[0] != '\0');
                tagcmp_kind_t kind = tagspec_get_kind(cmp[0]);
                if (kind != TAG_UNKNOWN_CMP) {
                        tagspec_add(spec, name, value, kind);
                        success = true;
                }
        } else if (name[0] != '\0') {
                tagspec_add(spec, name, NULL, TAG_ALWAYS);
                success = true;
        } else {
                assert(false &&
                       "in tagspec, specify only name OR name, operator, and value");
        }

        free(name);
        free(value);
        free(cmp);

        return success;
}

void tagspec_load(tagspec_t *spec, FILE *spec_fp)
{
        char *line = NULL;
        size_t line_len = 0;
        while (getline(&line, &line_len, spec_fp) != -1) {
                assert(tagspec_parse_line(spec, line));
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
