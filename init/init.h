#ifndef INIT_H
#define INIT_H

#include <stdio.h>

// Compiler flag to rename/move the executable
//
// TODO: Consider to move compiler flags logic
//
// # Example
// compiler main.c -mv build/program
// the executable changed name and it's stored in build directory
#define MV_FLAGS "-mv"

// Compiler flag that show in output, total size of the file compiled
//
// # Example
// compiler main.c  
#define FD_FLAGS "-fd"

int init_compiler(int argc, char* argv[], FILE* file_ptr);

// # Helper function
long compute_file_size(FILE* file_ptr);

// # Helper function
int match_compiler_flags(FILE* file_ptr,char* possible_flag);

#endif
