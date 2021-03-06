#include "minifs/high_level.h"
#include <stdlib.h>
#include <string.h>
#include "minifs/core/file.h"
#include "minifs/core/directory.h"


#define ROOT_DIR_ID 0


void high_level__file_create(const char * name, int * error) {
    char *name2 = malloc(strlen(name));
    strcpy(name2, name);

    uint8_t file_i_node_id = file__create(error);
    if (*error != NO_ERROR) {
        return;
    }

    dir_data_id__write_file_in_subdirs(ROOT_DIR_ID, name2, file_i_node_id, error);
    if (*error != 0) {
        file_id__remove(file_i_node_id, error);
        return;
    }
}


char* high_level__file_get(const char * name, int * error) {
    char *name2 = malloc(strlen(name));
    strcpy(name2, name);

    found_file_info_t found_file = dir_data_id__get_file_in_subdirs(ROOT_DIR_ID, name2, 0, error);
    if (*error != 0) {
        return NULL;
    }

    int file_length = file_id__get_length(found_file.file_i_node_id, error);
    if (*error != 0) {
        return NULL;
    }
    char *contents = malloc(file_length);
    file_id__get_contents(found_file.file_i_node_id, (uint8_t *) contents, error);
    if (*error != 0) {
        return NULL;
    }
    return contents;
}


void high_level__file_write(char * name, char * contents, int * error) {
    char *name2 = malloc(strlen(name));
    strcpy(name2, name);

    found_file_info_t found_file = dir_data_id__get_file_in_subdirs(ROOT_DIR_ID, name2, 0, error);
    if (*error != 0) {
        return;
    }

    file_id__overwrite(found_file.file_i_node_id, (uint8_t *) contents, strlen(contents), error);
    if (*error != 0) {
        return;
    }
}


void high_level__file_delete(char * name, int * error) {
    char *name2 = malloc(strlen(name));
    strcpy(name2, name);

    found_file_info_t found_file = dir_data_id__get_file_in_subdirs(ROOT_DIR_ID, name2, 0, error);
    if (*error != 0) {
        return;
    }

    dir_data_id__unregister_file(found_file.dir_i_node_id, name2, found_file.file_i_node_id, error);
    if (*error != 0) {
        return;
    }

    file_id__remove(found_file.file_i_node_id, error);
}


void high_level__file_copy(char * source, char * destination, int * error) {
    char *name2 = malloc(strlen(source));
    strcpy(name2, source);

    found_file_info_t found_file = dir_data_id__get_file_in_subdirs(ROOT_DIR_ID, name2, 0, error);
    if (*error == NO_SUCH_FILE || *error == NOT_A_DIRECTORY || *error == NOT_A_VALID_PATH) {
        *error = NO_SUCH_SOURCE;
        return;
    } else if (*error != 0) {
        return;
    }

    int file_length = file_id__get_length(found_file.file_i_node_id, error);
    if (*error != 0) {
        return;
    }
    char *contents = malloc(file_length);
    file_id__get_contents(found_file.file_i_node_id, (uint8_t *) contents, error);
    if (*error != 0) {
        return;
    }

    high_level__file_create(destination, error);
    if (*error == NO_SUCH_FILE || *error == NOT_A_DIRECTORY || *error == NOT_A_VALID_PATH) {
        *error = NO_SUCH_DESTINATION;
        return;
    } else if (*error != 0) {
        return;
    }

    high_level__file_write(destination, contents, error);
    if (*error != 0) {
        high_level__file_delete(destination, error);
    }
}