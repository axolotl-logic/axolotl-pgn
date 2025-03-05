#include "tsv.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

void tsv_fprint(FILE *out_fp, size_t n, const char **row)
{
        bool first = true;
        for (size_t i = 0; i < n; i++) {
                if (!first) {
                        assert(fputc('\t', out_fp) != EOF);
                } else {
                        first = false;
                }

                const char *value = row[i];
                assert(fputs(value, out_fp));
        }

        // Conclude with a newline.
        assert(fputc('\n', out_fp) != EOF);
}
