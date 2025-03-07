#ifndef COMMON_IO_H
#define COMMON_IO_H

#include <stdio.h>

int io_putc(FILE* out_fp, char out_value);
int io_puts(FILE* out_fp, const char* out_value);

#endif
