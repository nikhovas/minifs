#include "minifs/core/i_node.h"
#include "minifs/disk.h"
#include "minifs/core/bitmap.h"
#include "minifs/constants.h"


i_node_data_t i_node_id__get_data(uint8_t i_node_id) {
    i_node_data_t i_node_data;
    get_part_file((uint8_t *) &i_node_data, fileptr, I_NODE_DATA_OFFSET + i_node_id * I_NODE_SIZE, I_NODE_SIZE);
    return i_node_data;
}


void i_node__save(uint8_t i_node_id, i_node_data_t *i_node_data) {
    set_part_file((uint8_t *) i_node_data, fileptr, I_NODE_DATA_OFFSET + i_node_id * I_NODE_SIZE, I_NODE_SIZE);
}


uint8_t i_node__alloc(int *error) {
    return alloc_bitmap_node(fileptr, SUPERBLOCK_SIZE, 256, error);
}


void i_node_id__free(uint8_t i_node_id) {
    free_bitmap_node(fileptr, SUPERBLOCK_SIZE, i_node_id);
}