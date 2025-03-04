#include <criterion/criterion.h>

#include "pgn/pgn_frontend.h"

Test(pgn_frontend,  pgn_front_end_new) {
    pgn_frontend_t* env = pgn_frontend_new();

    cr_assert_not_null(env);

    pgn_frontend_free(env);
}
