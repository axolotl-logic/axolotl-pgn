#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "pgn/pgn_frontend.h"
#include "test_helpers.h"

Test(pgn_frontend, pgn_front_end_run, .init = redirect_stdout, .timeout = 1)
{
        pgn_frontend_t *env = pgn_frontend_new();

        cr_assert_not_null(env);

        pgn_frontend_run(env, stdout);

        pgn_frontend_free(env);
}
