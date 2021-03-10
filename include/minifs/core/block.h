#pragma once


#include <stdint.h>


typedef struct __attribute__((packed)) {
    uint8_t data[32];
} block_data_t;


block_data_t get_block_data_by_id(uint8_t block_id);
void write_bock_data_by_id(uint8_t block_id, block_data_t *block_data);


uint8_t alloc_block(int *error);
void free_block(uint8_t block_id);