#include "io.h"

#include <assert.h>
#include <stdio.h>

int io_putc(FILE *out_fp, char out_value)
{
        int ret = fputc(out_value, out_fp);
        assert(ret != EOF);

        return ret;
}

int io_puts(FILE *out_fp, const char *out_value)
{
        int ret = fputs(out_value, out_fp);
        assert(ret != EOF);

        return ret;
}
