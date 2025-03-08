#include <stdio.h>

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "pgn/tagspec.h"
#include "pgn/pgn_frontend.h"
#include "test_helpers.h"

const char test_pgn[] = "[Event \"F/S Return Match\"]\n"
                        "[Site \"Belgrade, Serbia JUG\"]\n"
                        "[Date \"1992.11.04\"]\n"
                        "[Round \"29\"]\n"
                        "[White \"Fischer, Robert J.\"]\n"
                        "[Black \"Spassky, Boris V.\"]\n"
                        "[Result \"1/2-1/2\"]\n"
                        "\n"
                        "1.e4 e5 2.Nf3 Nc6 3.Bb5 1/2-1/2\n\0";

Test(pgn_frontend, e2e_happy, .init = redirect_stdout, .timeout = 1)
{
        pgn_frontend_t *env = pgn_frontend_new();
        tagspec_add(env->spec, "Date", NULL, TAG_ALWAYS);

        cr_assert_not_null(env);

        pgn_frontend_run_str(env, test_pgn);

        cr_assert_stdout_eq_str("Date\n1992.11.04\n");

        pgn_frontend_free(env);
}
