#include "tsv.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

void tsv_fprint(FILE *out_fp, size_t n, const char **row)
{
        bool first = true;
        int ret;
        for (size_t i = 0; i < n; i++) {
                if (first) {
                        first = false;
                } else {
                        ret = fputc('\t', out_fp);
                        assert(ret != EOF &&
                               "writing tsv row tab character failed");
                }

                const char *value = row[i];
                ret = fputs(value, out_fp);
                assert(ret != EOF && "writing tsv value failed");
        }

        // Conclude with a newline.
        ret = fputc('\n', out_fp);
        assert(ret != EOF && "writing tsv row newline failed");
}
