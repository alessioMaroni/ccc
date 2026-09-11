#include "flags.h"

#include <stdio.h>
#include <string.h>

CompilerFlags match_compiler_flag(const char* possible_flag) {
    if (strcmp(possible_flag, FD_FLAG_STR) == 0) {
        return FLAG_FD;
    }
    if (strcmp(possible_flag, MV_FLAG_STR) == 0) {
        return FLAG_MV;
    }

    printf("Unknown flag: %s\n", possible_flag);
    return FLAG_UNKNOWN;
}

int run_compiler_flag(CompilerFlags flag, FILE* file_ptr) {
    switch (flag) {
        case FLAG_FD:
            printf("Total Size: %ld bytes\n", compute_file_size(file_ptr));
            break;

        case FLAG_MV:
            printf("Executing move/rename logic...\n");
            break;

        case FLAG_UNKNOWN:
        default:
            return 1;
    }

    return 0;
}

// TODO: Consider to move this type of function in other files
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
