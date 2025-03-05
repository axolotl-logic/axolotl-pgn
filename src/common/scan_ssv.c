#include "scan_ssv.h"

#include <stddef.h>

#include "common/smalloc.h"

char *scan_ssv(const char *line, size_t *cursor)
{
        if (line[*cursor] == '\0') {
                return NULL;
        }

        char *buff = smalloc(SSV_BUFF_SIZE);
        for (int i = 0; i < SSV_BUFF_SIZE; i++) {
                // Eat leading space
                while (line[*cursor] == ' ') {
                        cursor++;
                }

                if (line[*cursor] == '\0' || line[*cursor] == ' ') {
                        break;
                }

                buff[i] = line[*cursor];
                cursor++;
        }

        return buff;
}
