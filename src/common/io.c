#include "io.h"

#include <assert.h>
#include <stdio.h>

int io_disable_buff(FILE *file)
{
        int ret = setvbuf(file, NULL, _IONBF, 0);

        assert(ret == 0 && "Failed to disable buffer");

        return ret;
}

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
