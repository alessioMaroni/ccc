#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/lexer.h"

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        printf("Not enough params\n");
        return 1;
    }

    char* file_path = argv[1];
    FILE* file_ptr = fopen(file_path, "r");
    if(file_ptr == NULL)
    {
        printf("Error during file opening\n");
        return 1;
    }

    char token_buffer[TOKENB_SIZE];

    memset(token_buffer, 0, TOKENB_SIZE);

    int c = 0;
    int i = 0;
    while((c = fgetc(file_ptr)) != EOF)
    {
        //printf("%c", (char)c);

        if((char)c == ' ' || (char)c == '\n')
        {
            print_token_found(token_buffer);
            memset(token_buffer, 0, sizeof(TOKENB_SIZE));
            i ^= i;
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

    return 0;
}

