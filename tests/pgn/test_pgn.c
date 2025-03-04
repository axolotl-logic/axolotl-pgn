#include <criterion/criterion.h>

#include "pgn/pgn.h"

Test(pgn, pgn_add_result) {
    pgnlist_t* pgns = pgnlist_new();
    cr_assert_not_null(pgns);

    pgnlist_add_result(pgns, "*");
    cr_assert_not_null(pgns->head);

    pgn_t* pgn = pgns->head;

    cr_assert_eq(pgn->ply, 0);
    cr_assert_str_eq(pgn->result, "*");

    pgnlist_free(pgns);
}
