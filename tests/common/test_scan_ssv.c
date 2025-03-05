#include <criterion/criterion.h>

#include "common/scan_ssv.h"
#include <stddef.h>

Test(scan_ssv, scan_ssv)
{
        const char *line = "V-A V-B V-C";
        size_t cursor = 0;

        char *actual_1 = scan_ssv(line, &cursor);
        cr_expect_str_eq("V-A", actual_1);

        char *actual_2 = scan_ssv(line, &cursor);
        cr_expect_str_eq("V-B", actual_2);

        char *actual_3 = scan_ssv(line, &cursor);
        cr_expect_str_eq("V-C", actual_2);

        char *actual_4 = scan_ssv(line, &cursor);
        cr_expect_null(actual_4);
}
