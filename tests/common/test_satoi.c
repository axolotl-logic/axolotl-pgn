#include <criterion/criterion.h>

#include "common/satoi.h"

Test(satoi, satoi)
{
        cr_expect_eq(satoi("0"), 0);

        cr_expect_eq(satoi("3"), 3);
        cr_expect_eq(satoi("4"), 4);

        cr_expect_eq(satoi("11"), 11);
}
