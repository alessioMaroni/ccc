#ifndef LEXER_H
#define LEXER_H

#include <string.h>

#define TOKENB_SIZE 256

#define TOKEN_RETURN "return"

void print_token_found(char tb[TOKENB_SIZE])
{
    if(strcmp(tb, TOKEN_RETURN) == 0)
    {
        printf("[TOKEN RECOGNIZED] Token recognized: {%s}\n", TOKEN_RETURN);
    }
    else
    {
        printf("[TOKEN UNRECOGNIZED] Token unrecognized: {%s}\n", tb);
    }
}

#endif
