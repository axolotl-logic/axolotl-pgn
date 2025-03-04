#include <criterion/criterion.h>

#include "pgn/pgn_move.h"

Test(pgn_movelist, pgn_movelist_add) {
    pgn_movelist_t* moves = pgn_movelist_new();
    cr_assert_not_null(moves);

    pgn_movelist_add(moves, PGN_MOVETYPE_MOVE, "e4");
    cr_assert_not_null(moves->head);

    pgn_movelist_free(moves);
}
