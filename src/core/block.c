#include "minifs/core/block.h"
#include "minifs/core/bitmap.h"
#include "minifs/disk.h"
#include "minifs/constants.h"


block_data_t get_block_data_by_id(uint8_t block_id) {
    block_data_t block_data;
    get_part_file((uint8_t *) &block_data, fileptr,  BLOCK_DATA_OFFSET+ block_id * BLOCK_SIZE, BLOCK_SIZE);
    return block_data;
}


void write_bock_data_by_id(uint8_t block_id, block_data_t *block_data) {
    set_part_file((uint8_t *) block_data, fileptr, BLOCK_DATA_OFFSET+ block_id * BLOCK_SIZE, BLOCK_SIZE);
}


uint8_t alloc_block(int *error) {
    return alloc_bitmap_node(fileptr, BLOCK_BITMAP_DATA_OFFSET, BLOCK_COUNT, error);
}


void free_block(uint8_t block_id) {
    free_bitmap_node(fileptr, BLOCK_BITMAP_DATA_OFFSET, block_id);
}