#pragma once
#include "i_node.h"
#include "block.h"
#include "minifs/errors.h"


// manage block data
block_data_t file__get_block_data(i_node_data_t *i_node_data, uint8_t block_number);
void file__set_block_data(i_node_data_t *i_node_data, uint8_t block_number, block_data_t* block_data);


//// manage block count
//void file__add_blocks_to_end(i_node_data_t *i_node_data, uint8_t new_blocks, int * error);
//void file__remove_blocks_from_end(i_node_data_t *i_node_data, uint8_t remove_block_count);
//void file__set_block_count(i_node_data_t *i_node_data, uint8_t new_block_size, int * error);


// get contents
void file__get_contents(i_node_data_t *i_node_data, uint8_t* contents);
void file_id__get_contents(uint8_t i_node_id, uint8_t* contents);


// get length
uint16_t file__get_length(i_node_data_t *i_node_data);
uint16_t file_id__get_length(uint8_t i_node_id);


// overwrites
void file__overwrite(i_node_data_t *i_node_data, uint8_t* data, uint16_t length, int * error);
void file_id__overwrite(uint8_t i_node_id, uint8_t* data, uint16_t length, int * error);


// existant operations
void file_id__remove(uint8_t i_node_id);
uint8_t file__create(int * error);