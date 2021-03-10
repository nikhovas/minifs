#pragma once


#include <stdint.h>
#include <stdio.h>
#include <libc.h>


size_t alloc_bitmap_node(FILE* file, size_t offset, size_t length, int * error);
void free_bitmap_node(FILE* file, size_t offset, size_t number);