#include <criterion/criterion.h>

#include "common/symbol.h"

Test(symbol, symboltable_add) {
    symboltable_t* symbols = symboltable_new();
    cr_assert(symbols);

    const char* expected = "test 1";
    const char* actual = symboltable_add(symbols, expected);
    cr_assert_str_eq(expected, actual);

    symboltable_free(symbols);
}
