#pragma once


#include <minifs/core/directory.h>
#include "errors.h"


void high_level__file_create(const char * name, int * error);
char* high_level__file_get(const char * name, int * error);
void high_level__file_write(char * name, char * contents, int * error);
void high_level__file_delete(char * name, int * error);
void high_level__file_copy(char * source, char * destination, int * error);


void high_level__dir_create(char * name, int * error);
void high_level__dir_delete(char * name, int * error);
directory_item_t * high_level__dir_get_contents(char * name, uint8_t * size, int * error);


void high_level__filesystem_create(int *error);