#include "generation.h"

#include "common/io.h"
#include <stdio.h>
#include <string.h>

#include "gameclock.h"
#include "pgn.h"
#include "pgn_move.h"
#include "pgn_tag.h"
#include "tagspec.h"

void print_headers(tagspec_t *spec)
{
        bool first = true;
        for (tagorder_t *tag = spec->order_head; tag != NULL; tag = tag->next) {
                if (first) {
                        first = false;
                } else {
                        io_putc(stdout, '\t');
                }

                io_puts(stdout, tag->name);
        }

        io_putc(stdout, '\n');
}

void print_moves(pgn_move_t *moves_head)
{
        int ply = 0;
        for (pgn_move_t *move = moves_head; move != NULL; move = move->next) {
                if (move->kind == PGN_MOVETYPE_MOVE) {
                        if (ply++ > 0) {
                                io_putc(stdout, ' ');
                        }

                        io_puts(stdout, move->value);
                }
        }
}

void print_clock(gameclock_t *clock)
{
        for (timestamp_t *ts = clock->head; ts != NULL; ts = ts->next) {
                if (ts != clock->head) {
                        io_putc(stdout, ' ');
                }

                printf("%d", ts->time);
        }
}

bool is_kept(tagspec_t *spec, pgn_t *pgn)
{
        for (tag_t *tag = pgn->tags->head; tag != NULL; tag = tag->next) {
                if (!tagspec_matches(spec, tag->name, tag->value)) {
                        return false;
                }
        }

        return true;
}

void print_pgn(tagspec_t *spec, pgn_t *pgn)
{
        if (!is_kept(spec, pgn)) {
                return;
        }

        taglist_t *aligned_tags = taglist_new_aligned(pgn->tags, spec);
        bool first = true;
        for (tag_t *tag = aligned_tags->head; tag != NULL; tag = tag->next) {
                if (first) {
                        first = false;
                } else {
                        io_putc(stdout, '\t');
                }

                if (strcmp(tag->name, "Moves") == 0) {
                        print_moves(pgn->moves->head);
                } else if (strcmp(tag->name, "Ply") == 0) {
                        printf("%d", pgn->ply);
                } else if (strcmp(tag->name, "WhiteClock") == 0) {
                        print_clock(pgn->clock_white);
                } else if (strcmp(tag->name, "BlackClock") == 0) {
                        print_clock(pgn->clock_black);
                } else if (tag->value == NULL &&
                           strcmp(tag->name, "Result") == 0) {
                        io_puts(stdout, pgn->result);
                } else if (tag->value != NULL) {
                        io_puts(stdout, tag->value);
                }
        }

        io_putc(stdout, '\n');

        taglist_free(aligned_tags);
}
