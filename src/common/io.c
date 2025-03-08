#include "io.h"

#include <assert.h>
#include <stdio.h>

#define INT_STR_SIZE 18

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

int io_puti(FILE *out_fp, int out_value)
{
        char str[INT_STR_SIZE] = { '\0' };
        int written = snprintf(str, INT_STR_SIZE, "%d", out_value);

        assert(written > 0 && str[INT_STR_SIZE - 1] == '\0');

        return io_puts(out_fp, str);
}

int io_puts(FILE *out_fp, const char *out_value)
{
        int ret = fputs(out_value, out_fp);
        assert(ret != EOF);

        return ret;
}
