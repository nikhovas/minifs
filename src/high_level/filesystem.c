#include "minifs/high_level.h"
#include <stdlib.h>
#include <string.h>
#include "minifs/core/file.h"
#include "minifs/core/directory.h"
#include "minifs/disk.h"
#include <unistd.h>


#define ROOT_DIR_ID 0


void high_level__filesystem_create() {
    if (access("filesystem", F_OK) != 0) {
        create_file("filesystem");
    }
    set_file(fopen("filesystem", "r+b"));
    int error;
    dir_data_create(&error);
}