#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "init/init.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Too few arguments\n");
        return 0x1;
    }

    // # (m)ain (f)ile path
    //
    // The second element passed to the program
    // holds the path of the file
    char* mf_path = argv[1];

    // # (m)ain (f)ile (P)oin(t)e(r)
    //
    // A pointer to the beginning of the main file
    // (file that contains the main function)
    FILE* mf_ptr = fopen(mf_path, "r");
    if (mf_ptr == NULL) {
        printf("Error during file opening\n");
        return 0x1;
    }

    printf("Compiling...\n");

    int program_exit_code = 0x0;

    // Init
    if(init_compiler(argc, argv, mf_ptr) == 1){
        return 0x1;
    }

    fclose(mf_ptr);
    return 0x0;
}
