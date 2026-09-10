#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "init.h"

int init_compiler(int argc, char* argv[], FILE* file_ptr) {
    (void)file_ptr;

    char** flags_list = malloc((size_t)argc * sizeof(char*));
    if (flags_list == NULL) {
        printf("Error during memory allocation\n");
        return 1;
    }

    int flags_count = 0;

    for (int i = 2; i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] != '\0') {
            flags_list[flags_count] = argv[i];
            flags_count++;
        }
    }

    printf("Flags number (%d):\n", flags_count);
    for (int i = 0; i < flags_count; i++) {
        int flags_exit_code = match_compiler_flags(file_ptr, flags_list[i]);
        if(flags_exit_code == 1){
            return 1;
        }
        printf("  %s\n", flags_list[i]);
    }

    free(flags_list);

    return 0;
}

int match_compiler_flags(FILE* file_ptr,char* possible_flag){
    if(strcmp(possible_flag, FD_FLAGS) == 0){
        printf("Total Size: %ld\n", compute_file_size(file_ptr));
    }
    else {
        printf("Unknown flags: %s\n", possible_flag);
        return 1;
    }

    return 0;
}

// # Helper function
// compute_file_size
//
// Compute a single file size by moving his pointer to the end
long compute_file_size(FILE* file_ptr) {
    if (file_ptr == NULL) {
        return 0;
    }

    fseek(file_ptr, 0, SEEK_END);

    // # (m)ain (f)ile size
    //
    // size of the main file
    long size = ftell(file_ptr);
    if (size < 0) {
        rewind(file_ptr);
        return 0;
    }

    rewind(file_ptr);
    return size;
}

