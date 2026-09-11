#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "init.h"
#include "../feat/flags/flags.h"

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

    for (int i = 0; i < flags_count; i++) {
        CompilerFlags flag = match_compiler_flag(flags_list[i]);

        if (flag == FLAG_UNKNOWN) {
            free(flags_list);
            return 1;
        }


        if (run_compiler_flag(flag, file_ptr) != 0) {
            free(flags_list);
            return 1;
        }
    }

    free(flags_list);

    return 0;
}

