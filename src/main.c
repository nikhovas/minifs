#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "minifs/high_level.h"


void cmd_file_create(char * name) {
    int error;
    char error_description[128];
    high_level__file_create(name, &error, error_description);
    if (error != NO_ERROR) {
        printf("%s\n", error_description);
    }
}


void cmd_file_get(char * name) {
    int error;
    char error_description[128];
    char * data = high_level__file_get(name, &error, error_description);
    if (error != NO_ERROR) {
        printf("%s\n", error_description);
    } else {
        printf("%s\n", data);
    }
}


void cmd_file_write(char * name, char * contents) {
    int error;
    char error_description[128];
    high_level__file_write(name, contents, &error, error_description);
    if (error != NO_ERROR) {
        printf("%s\n", error_description);
    }
}


void cmd_file_delete(char * name) {
    int error;
    char error_description[128];
    high_level__file_delete(name, &error, error_description);
    if (error != NO_ERROR) {
        printf("%s\n", error_description);
    }
}


void cmd_file_copy(char * source, char * destination) {
    int error;
    char error_description[128];
    high_level__file_copy(source, destination, &error, error_description);
    if (error != NO_ERROR) {
        printf("%s\n", error_description);
    }
}


void cmd_dir_create(char * name) {
    int error;
    char error_description[128];
    high_level__dir_create(name, &error, error_description);
    if (error != NO_ERROR) {
        printf("%s\n", error_description);
    }
}

void cmd_dir_delete(char * name) {
    int error;
    char error_description[128];
    high_level__dir_delete(name, &error, error_description);
    if (error != NO_ERROR) {
        printf("%s\n", error_description);
    }
}


void cmd_dir_get(char * name) {
    int error;
    char error_description[128];
    uint8_t size;
    directory_item_t * dir_items = high_level__dir_get_contents(name, &size, &error, error_description);
    if (error != NO_ERROR) {
        printf("%s\n", error_description);
    }

    for (uint8_t i = 0; i < size; ++i) {
        printf("%s\n", dir_items[i].name);
    }
}


void execute_cmd(int args_count, char** args) {
    if (args_count >= 3) {
        if (strcmp(args[0], "file") == 0) {
            if (strcmp(args[1], "create") == 0) {
                cmd_file_create(args[2]);
            } else if (strcmp(args[1], "get") == 0) {
                cmd_file_get(args[2]);
            } else if (strcmp(args[1], "write") == 0) {
                if (args_count >= 4) {
                    cmd_file_write(args[2], args[3]);
                } else {
                    printf("Wrong cmd\n");
                }
            } else if (strcmp(args[1], "delete") == 0) {
                cmd_file_delete(args[2]);
            } else if (strcmp(args[1], "copy") == 0) {
                if (args_count >= 4) {
                    cmd_file_copy(args[2], args[3]);
                } else {
                    printf("Wrong cmd\n");
                }
            } else {
                printf("Wrong cmd\n");
            }
        } else if (strcmp(args[0], "dir") == 0) {
            if (strcmp(args[1], "create") == 0) {
                cmd_dir_create(args[2]);
            } else if (strcmp(args[1], "get") == 0) {
                cmd_dir_get(args[2]);
            } else if (strcmp(args[1], "delete") == 0) {
                cmd_dir_delete(args[2]);
            } else {
                printf("Wrong cmd\n");
            }
        }
    } else {
        printf("Wrong cmd\n");
    }
}


void cmd() {
    while (1) {
        char data[1024];
        int args_count = 0;
        char *args[32];
        fgets(data, 1024, stdin);
        data[strlen(data) - 1] = 0;
//        scanf("%s", data);
        if (strcmp(data, "exit") == 0) {
            break;
        }
        const char delim[] = " ";

        for (char *ptr = strtok(data, delim); ptr != NULL; ptr = strtok(NULL, delim)) {
            args[args_count++] = ptr;
        }

        execute_cmd(args_count, args);
    }
}


int main() {
    high_level__filesystem_create();
    cmd();
    return 0;
}
