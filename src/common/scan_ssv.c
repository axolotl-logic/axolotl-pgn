#include "scan_ssv.h"

#include <stddef.h>

#include "common/smalloc.h"

#define BUFF_SIZE 200

char *scan_ssv(const char *line, size_t *cursor)
{
        if (line[*cursor] == '\0') {
                return NULL;
        }

        char *buff = smalloc(BUFF_SIZE);
        for (int i = 0; i < BUFF_SIZE; i++) {
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
