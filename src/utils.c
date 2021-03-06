#include "minifs/utils.h"
#include <string.h>


uint8_t get_bit(uint8_t val, uint8_t bit_num) {
    return (val >> bit_num) & 1;
}


uint8_t set_bit(uint8_t val, uint8_t bit_num) {
    return (val | (1 << bit_num));
}


char* trim_path(char *path) {
    unsigned long length = strlen(path);

    if (length == 0) {
        return path;
    }

    if (path[length - 1] == '/') {
        path[length - 1] = 0;
    }

    if (path[0] == '/') {
        return path + 1;
    }

    return path;
}