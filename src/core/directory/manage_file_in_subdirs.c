#include "minifs/core/directory.h"
#include <string.h>
#include "minifs/errors.h"
#include "minifs/utils.h"


found_file_info_t dir_data__get_file_in_subdirs(const i_node_data_t *dir_i_node_data, uint8_t dir_i_node_data_id, char *filepath, uint8_t file_i_node_id, int *error) {
    *error = NO_ERROR;
    found_file_info_t found_file_info;

    if (dir_i_node_data->is_folder == 0) {
        *error = NOT_A_DIRECTORY;
        return found_file_info;
    }

    filepath = trim_path(filepath);
    unsigned long length = strlen(filepath);

    if (length == 0) {
        found_file_info.dir_i_node_id = dir_i_node_data_id;
        found_file_info.file_i_node_id = dir_i_node_data_id;
        return found_file_info;
    }

    uint8_t last_dir_i_node_data_id;
    for (char * token = strtok(filepath, "/"); token != NULL; token = strtok(NULL, "/")) {
        if (strlen(token) > 7) {
            *error = NOT_A_VALID_PATH;
            return found_file_info;
        }

        last_dir_i_node_data_id = dir_i_node_data_id;
        i_node_data_t i_node_data = i_node_id__get_data(dir_i_node_data_id, error);
        if (*error != NO_ERROR) {
            return found_file_info;
        }

        dir_i_node_data_id = dir_data_get_file_i_node(&i_node_data, token, file_i_node_id, error);
        if (*error == NOT_A_DIRECTORY) {
            *error = NOT_A_VALID_PATH;
            return found_file_info;
        } else if (*error != 0) {
            *error = NO_SUCH_FILE;
            return found_file_info;
        }
    }

    found_file_info.dir_i_node_id = last_dir_i_node_data_id;
    found_file_info.file_i_node_id = dir_i_node_data_id;

    *error = NO_ERROR;
    return found_file_info;
}

found_file_info_t dir_data_id__get_file_in_subdirs(uint8_t dir_i_node_id, char *filepath, uint8_t file_i_node_id, int *error) {
    i_node_data_t dir_i_node_data = i_node_id__get_data(dir_i_node_id, error);
    if (*error != NO_ERROR) {
        return (found_file_info_t) {0};
    }

    return dir_data__get_file_in_subdirs(&dir_i_node_data, dir_i_node_id, filepath, file_i_node_id, error);
}


void dir_data__write_file_in_subdirs(
        i_node_data_t *dir_i_node_data,
        uint8_t dir_i_node_data_id,
        char *filepath,
        uint8_t file_i_node_id,
        int *error
        )
{
    *error = NO_ERROR;

    unsigned long length = strlen(filepath);
    if (length == 0) {
        *error = INVALID_PATH;
        return;
    }

    if (filepath[length - 1] == '/') {
        filepath[length - 1] = 0;
    }

    char* last_occurance = strrchr(filepath, '/');

    last_occurance[0] = '\0';

    found_file_info_t found_file_info = dir_data__get_file_in_subdirs(
            dir_i_node_data, dir_i_node_data_id, filepath, 0, error);
    if (*error != NO_ERROR) {
        return;
    }

    if (dir_i_node_data_id == found_file_info.file_i_node_id) {
        dir_data__register_file_with_name(dir_i_node_data, last_occurance + 1, file_i_node_id, error);
    } else {
        dir_data_id__register_file_with_name(found_file_info.file_i_node_id, last_occurance + 1, file_i_node_id, error);
    }
}

void dir_data_id__write_file_in_subdirs(uint8_t dir_i_node_data_id, char *filepath, uint8_t file_i_node_id, int *error) {
    i_node_data_t dir_i_node_data = i_node_id__get_data(dir_i_node_data_id, error);
    if (*error != NO_ERROR) {
        return;
    }

    dir_data__write_file_in_subdirs(&dir_i_node_data, dir_i_node_data_id, filepath, file_i_node_id, error);
    if (*error == NO_ERROR) {
        i_node__save(dir_i_node_data_id, &dir_i_node_data, error);
        if (*error != NO_ERROR) {
            return;
        }
    }
}


void dir_data__delete_file_in_subdirs(i_node_data_t *dir_i_node_data, uint8_t dir_i_node_data_id, char *filepath, uint8_t file_i_node_id, int *error);
void dir_data_id__delete_file_in_subdirs(uint8_t dir_i_node_data_id, char *filepath, uint8_t file_i_node_id, int *error);


void dir_data__unregister_file_in_subdirs(
        i_node_data_t *dir_i_node_data,
        uint8_t dir_i_node_data_id,
        char *filepath,
        uint8_t file_i_node_id,
        int *error
)
{
    *error = NO_ERROR;

    unsigned long length = strlen(filepath);
    if (length == 0) {
        *error = INVALID_PATH;
        return;
    }

    if (filepath[length - 1] == '/') {
        filepath[length - 1] = 0;
    }

    char* last_occurance = strrchr(filepath, '/');

    last_occurance[0] = '\0';

    found_file_info_t found_file_info = dir_data__get_file_in_subdirs(
            dir_i_node_data, dir_i_node_data_id, filepath, 0, error);
    if (*error != NO_ERROR) {
        return;
    }

    if (dir_i_node_data_id == found_file_info.file_i_node_id) {
        dir_data__unregister_file(dir_i_node_data, last_occurance + 1, file_i_node_id, error);
    } else {
        dir_data_id__unregister_file(found_file_info.file_i_node_id, last_occurance + 1, file_i_node_id, error);
    }
}

void dir_data_id__unregister_file_in_subdirs(uint8_t dir_i_node_data_id, char *filepath, uint8_t file_i_node_id, int *error) {
    i_node_data_t dir_i_node_data = i_node_id__get_data(dir_i_node_data_id, error);
    if (*error != NO_ERROR) {
        return;
    }

    dir_data__unregister_file_in_subdirs(&dir_i_node_data, dir_i_node_data_id, filepath, file_i_node_id, error);
    if (*error == NO_ERROR) {
        i_node__save(dir_i_node_data_id, &dir_i_node_data, error);
        if (*error != NO_ERROR) {
            return;
        }
    }
}