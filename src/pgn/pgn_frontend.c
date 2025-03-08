#include "pgn_frontend.h"

#include "common/io.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "generation.h"
#include "pgn.h"
#include "tagspec.h"
#include "common/smalloc.h"
#include "common/symbol.h"

#define UNUSED(x) (void)(x)

typedef void *yyscan_t;
typedef void *YYLTYPE;
typedef void *YY_BUFFER_STATE;

int yylex_destroy(yyscan_t yyscanner);
int yylex_init(yyscan_t *scanner);
int yyparse(yyscan_t scanner, pgn_frontend_t *env);
void yyset_in(FILE *_in_str, yyscan_t yyscanner);
YY_BUFFER_STATE yy_scan_string(const char *yy_str, yyscan_t yyscanner);

pgn_frontend_t *pgn_frontend_new(void)
{
        pgn_frontend_t *env = smalloc(sizeof(struct pgn_frontend_t));

        env->pgns = pgnlist_new();
        env->spec = tagspec_new();
        env->symbols = symboltable_new();

        return env;
}

void pgn_frontend_free(pgn_frontend_t *env)
{
        pgnlist_free(env->pgns);
        tagspec_free(env->spec);
        symboltable_free(env->symbols);

        free(env);
}

void pgn_frontend_run(pgn_frontend_t *env, FILE *in_fp)
{
        print_headers(env->spec);

        yyscan_t scanner;
        yylex_init(&scanner);
        yyset_in(in_fp, scanner);
        // Parse into the pgns list.
        yyparse(scanner, env);
        yylex_destroy(scanner);
}

void pgn_frontend_run_str(pgn_frontend_t *env, const char *in_str)
{
        print_headers(env->spec);

        yyscan_t scanner;
        yylex_init(&scanner);
        yy_scan_string(in_str, scanner);
        yyparse(scanner, env);
        yylex_destroy(scanner);
}

void flush_pgns(pgn_frontend_t *env)
{
        for (pgn_t *pgn = env->pgns->head; pgn != NULL && pgn->result != NULL;
             pgn = pgn->next) {
                print_pgn(env->spec, pgn);
        }

        pgnlist_free(env->pgns);
        env->pgns = pgnlist_new();

        symboltable_free(env->symbols);
        env->symbols = symboltable_new();
}

void yyerror(YYLTYPE *yyllocp, yyscan_t scanner, pgn_frontend_t *env,
             const char *msg)
{
        UNUSED(scanner);
        UNUSED(env);
        UNUSED(yyllocp);
        io_puts(stderr, "error: ");
        io_puts(stderr, msg);
        io_putc(stderr, '\n');
}
