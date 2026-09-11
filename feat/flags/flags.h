#ifndef FLAGS_H
#define FLAGS_H

#include <stdio.h>

#define FD_FLAG_STR "-fd"
#define MV_FLAG_STR "-mv"

typedef enum {
    FLAG_UNKNOWN = 0,

    // Compiler flag that show in output, total size of the file compiled
    //
    // # Example
    // compiler main.c -fd
    FLAG_FD,

    // Compiler flag to rename/move the executable
    //
    // # Example
    // compiler main.c -mv build/program
    // the executable changed name and it's stored in build directory
    FLAG_MV,
}CompilerFlags;

// # match_compiler_flag
//
// Helper function to 'run_compiler_flag' function,
// verify the search fot the flags and return it in case it exist
//
// Return type: char* (a pointer to the flag (string) )
CompilerFlags match_compiler_flag(const char* possible_flag);

// #run_compiler_flags
//
// Take as a paramenter the verified flag returned by
// 'match_compiler_flag' and execute the logic
int run_compiler_flag(CompilerFlags flag, FILE* file_ptr);

// -----------------------

// # compute_file_size
//
// Compute the size of a single file
// usable by compiler flags '-fd'
long compute_file_size(FILE* file_ptr);


#endif
