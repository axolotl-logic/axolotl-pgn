#include "test_helpers.h"

#include <criterion/redirect.h>

#include "common/io.h"

void redirect_stdout(void)
{
        io_disable_buff(stdout);

        cr_redirect_stdout();
}
