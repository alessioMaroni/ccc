#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "init/init.h"

#define MAX_LINES 100
#define MAX_LEN 512

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

    printf("\n\n");

    char lines[MAX_LINES][MAX_LEN];
    int total_lines = 0;


    while (total_lines < MAX_LINES && fgets(lines[total_lines], MAX_LEN, mf_ptr) != NULL){
        total_lines++;
    }


    for (int i = 0; i < total_lines; i++){
        for (int j = 0; lines[i][j] != '\0'; j++){
           if (lines[i][j] == '#') {
                char *after_hash = &lines[i][j + 1];
                while (*after_hash == ' ' || *after_hash == '\t') {
                    after_hash++;
                }

                char directive[32];
                directive[0] = '#';
                if (sscanf(after_hash, "%30s", &directive[1]) == 1) {
                    printf("Directive found: %s\n", directive);
                }

                break;
            }
        }
    }

    fclose(mf_ptr);
    return 0x0;
}
