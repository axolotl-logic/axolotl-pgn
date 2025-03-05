#include "satoi.h"

#include <assert.h>
#include <limits.h>
#include <stdlib.h>

#define BASE_10 10

int satoi(const char *str)
{
        char *endptr = NULL;
        long result = strtol(str, &endptr, BASE_10);

        assert(result < INT_MAX && "Number would overflow integer");
        assert(str != endptr && "Nothing was parsed");

        return (int)result;
}
