#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/lexer.h"
#include "include/codegen.h"

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        printf("Not enough params\n");
        return 1;
    }

    size_t file_name_size = strlen(argv[1]);
    if(file_name_size < 1)
    {
        return 1;
    }

    char* file_name = malloc(file_name_size + 1);
    if (file_name == NULL) {
        return 1;
    }

    strcpy(file_name, argv[1]);

    if(file_name[file_name_size - 1] != 'c')
    {
        printf("File extension must be 'c'\n");
        free(file_name);
        return 1;
    }

    FILE* c_file_ptr = fopen(file_name, "r");
    if(c_file_ptr == NULL)
    {
        printf("Error during file opening\n");
        free(file_name);
        return 1;
    }

    file_name[file_name_size - 1] = 's';
    char* s_file_name = file_name;

    FILE* s_file_ptr = fopen(s_file_name, "w");
    if(s_file_ptr == NULL)
    {
        printf("Error during file opening\n");
        fclose(c_file_ptr);
        free(file_name);
        return 1;
    }

    free(file_name);

    char token_buffer[TOKENB_SIZE];
    memset(token_buffer, 0, TOKENB_SIZE);

    int c = 0;
    int i = 0;
    int has_returned = 0;
    int expecting_return_val = 0;

    while((c = fgetc(c_file_ptr)) != EOF)
    {
        if((char)c == ' ' || (char)c == '\n' || (char)c == '\t' || (char)c == '\r')
        {
            if (i > 0)
            {
                const char* vt = verify_found_token(token_buffer);

                if (expecting_return_val)
                {
                    write_asm_code(s_file_ptr, TOKEN_KW_RETURN, token_buffer);
                    expecting_return_val = 0;
                    has_returned = 1;
                }
                else if (vt != NULL && strcmp(vt, TOKEN_KW_RETURN) == 0)
                {
                    expecting_return_val = 1;
                }
                else if (vt != NULL)
                {
                    write_asm_code(s_file_ptr, vt, NULL);
                }

                memset(token_buffer, 0, TOKENB_SIZE);
                i = 0;
            }
        }
        else if ((char)c == '}')
        {
            if (i > 0)
            {
                const char* vt = verify_found_token(token_buffer);
                if (expecting_return_val)
                {
                    write_asm_code(s_file_ptr, TOKEN_KW_RETURN, token_buffer);
                    expecting_return_val = 0;
                    has_returned = 1;
                }
                else if (vt != NULL)
                {
                    write_asm_code(s_file_ptr, vt, NULL);
                }

                memset(token_buffer, 0, TOKENB_SIZE);
                i = 0;
            }

            if (!has_returned)
            {
                write_asm_code(s_file_ptr, TOKEN_KW_RETURN, "0");
            }
            has_returned = 0; // Reset per la prossima funzione
        }
        else if ((char)c == '{' || (char)c == '(' || (char)c == ')' || (char)c == ';')
        {
            if (i > 0)
            {
                const char* vt = verify_found_token(token_buffer);

                if (expecting_return_val)
                {
                    write_asm_code(s_file_ptr, TOKEN_KW_RETURN, token_buffer);
                    expecting_return_val = 0;
                    has_returned = 1;
                }
                else if (vt != NULL && strcmp(vt, TOKEN_KW_RETURN) == 0)
                {
                    expecting_return_val = 1;
                }
                else if (vt != NULL)
                {
                    write_asm_code(s_file_ptr, vt, NULL);
                }

                memset(token_buffer, 0, TOKENB_SIZE);
                i = 0;
            }
        }
        else
        {
            if (i < TOKENB_SIZE - 1)
            {
                token_buffer[i] = (char)c;
                i++;
            }
        }
    }

    if (i > 0)
    {
        printf("%s\n", token_buffer);
    }

    fclose(c_file_ptr);
    fclose(s_file_ptr);

    return 0;
}