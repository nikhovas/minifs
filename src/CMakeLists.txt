INCLUDE_DIRECTORIES(fs ../include)

#SET(SOURCE_FILES main.c)
#ADD_SUBDIRECTORY(core)
#ADD_SUBDIRECTORY(disk_utils)
#ADD_SUBDIRECTORY(high_level)

add_executable(fs
        core/directory/clear.c
        core/directory/existant.c
        core/directory/get_file_i_node.c
        core/directory/get_files_list.c
        core/directory/get_number_of_files.c
        core/directory/manage_file_in_subdirs.c
        core/directory/register_file.c
        core/file/existant.c
        core/file/get_contents.c
        core/file/get_length.c
        core/file/manage_block_data.c
        core/file/overwrite.c
        core/i_node/existance.c
        core/i_node/get_block_info.c
        core/i_node/manage_block_count.c
        core/bitmap.c
        core/block.c
        high_level/directory.c
        high_level/file.c
        high_level/filesystem.c
        disk.c
        utils.c
        main.c
        )
