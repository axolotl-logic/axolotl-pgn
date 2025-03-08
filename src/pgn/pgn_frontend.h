#ifndef PGN_PGN_FRONTEND_H
#define PGN_PGN_FRONTEND_H

#include "pgn.h"

#include <stdio.h>

#include "common/symbol.h"
#include "tagspec.h"

typedef struct pgn_frontend_t {
    pgnlist_t* pgns;
    tagspec_t* spec;
    symboltable_t* symbols;
} pgn_frontend_t;

/* Allocates a new pgn_frontend */
pgn_frontend_t* pgn_frontend_new(void);

/* Deallocates pgn_frontend */
void pgn_frontend_free(pgn_frontend_t* env);

void pgn_frontend_run(pgn_frontend_t* env, FILE* in_fp);
void pgn_frontend_run_str(pgn_frontend_t* env, const char* in_str);

#endif
