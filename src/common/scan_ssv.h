#ifndef COMMON_SCAN_SSV_H
#define COMMON_SCAN_SSV_H

#include <stddef.h>

#define SSV_BUFF_SIZE 200

char *scan_ssv(const char *line, size_t *cursor);
#endif
