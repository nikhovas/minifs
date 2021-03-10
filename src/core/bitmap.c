#include "minifs/core/bitmap.h"
#include "minifs/disk.h"
#include "minifs/errors.h"
#include "minifs/utils.h"


size_t alloc_bitmap_node(FILE* file, size_t offset, size_t length, int * error) {
    *error = NO_ERROR;

    length = length / 8;
    uint8_t* data = malloc(length);
    get_part_file(data, file, offset, length);

    for (size_t i = 0; i < length; ++i) {
        uint8_t val = data[i];
        for (uint8_t j = 0; j < 8; ++j) {
            uint8_t bit_value = get_bit(val, j);
            if (bit_value == 0) {
                val = set_bit(val, j);
                set_part_file(&val, file, offset + i * 8, 1);
                return i * 8 + j;
            }
        }
    }

    *error = NO_FREE_NODES_AVAILABLE;
    return 0;
}


void free_bitmap_node(FILE* file, size_t offset, size_t number) {
    uint8_t val;
    get_part_file(&val, file, offset + number / 8, 1);
    val = set_bit(val, number % 8);
    set_part_file(&val, file, offset + number / 8, 1);
}