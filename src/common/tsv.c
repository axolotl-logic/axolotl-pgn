#include "tsv.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "io.h"

void tsv_fprint(FILE *out_fp, size_t n, const char **row)
{
        bool first = true;

        int ret;
        for (size_t i = 0; i < n; i++) {
                if (first) {
                        first = false;
                } else {
                        io_putc(out_fp, '\t');
                }

                io_puts(out_fp, row[i]);
        }

        // Conclude with a newline.
        io_putc(out_fp, '\n');
}
