#include "codegen.h"
#include "tokens_def.h"
#include "x86_64_regs_def.h"

#include <string.h>

void write_asm_code(FILE* asm_file, const char* vt, const char* return_value) {
    if (asm_file == NULL || vt == NULL) {
        return;
    }

    if (strcmp(vt, TOKEN_SP_MAIN) == 0) {
        fprintf(asm_file, "    .globl main\n");
        fprintf(asm_file, "main:\n");
    }
    else if (strcmp(vt, TOKEN_KW_RETURN) == 0) {
        if (return_value != NULL) {
            fprintf(asm_file, "    mov %s, %s\n", REGS_64_RAX, return_value);
        }
        fprintf(asm_file, "    ret\n");
    }
}