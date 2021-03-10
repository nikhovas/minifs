#include <memory.h>
#include "minifs/disk.h"
#include "minifs/constants.h"


FILE* fileptr;


void set_part_file(const uint8_t *data, FILE* file, size_t offset, size_t length) {
    fseek(file, offset, SEEK_SET);
    fwrite(data, length, 1, file);
}


void get_part_file(uint8_t *data, FILE* file, size_t offset, size_t length) {
    fseek(file, offset, SEEK_SET);
    fread(data, length, 1, file);
}


void create_file(char * path) {
    FILE *fp = fopen(path, "wb");
    fseek(fp, END_OFFSET - 1, SEEK_SET);
    fputc('\0', fp);
    fclose(fp);
}


void set_file(FILE * file) {
    fileptr = file;
}