#include "pgn/tagspec.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "pgn/pgn_frontend.h"

int main(int argc, char **argv)
{
        if (argc != 2) {
                assert(fputs("Please pass a path to a tagspec\n", stderr));
                return EXIT_FAILURE;
        }

        // Open the file in read mode, exit with error if failure to do so
        const char *spec_path = argv[1];
        FILE *spec_fp = fopen(spec_path, "r");
        if (spec_fp == NULL) {
                perror("fopen");
                return EXIT_FAILURE;
        }

        pgn_frontend_t *env = pgn_frontend_new();

        tagspec_load(env->spec, spec_fp);
        assert(fclose(spec_fp) == 0);

        pgn_frontend_run(env, stdin);

        pgn_frontend_free(env);

        return EXIT_SUCCESS;
}
