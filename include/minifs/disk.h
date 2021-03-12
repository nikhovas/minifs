#pragma once


#include <stdint.h>
#include <stdio.h>


extern FILE* fileptr;


extern uint8_t* filel;


void set_part_file(const uint8_t *data, FILE* file, size_t offset, size_t length, int *error);
void get_part_file(uint8_t *data, FILE* file, size_t offset, size_t length, int *error);





void create_file(char * path, int *error);
void set_file(FILE * file);