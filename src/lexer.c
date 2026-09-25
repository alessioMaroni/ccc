#include "../include/lexer.h"
#include "../include/tokens_def.h"
#include <stdio.h>

const char* keyword_strings[KW_COUNT] = {
    TOKEN_KW_AUTO,     TOKEN_KW_BREAK,    TOKEN_KW_CASE,     TOKEN_KW_CHAR,
    TOKEN_KW_CONST,    TOKEN_KW_CONTINUE, TOKEN_KW_DEFAULT,  TOKEN_KW_DO,
    TOKEN_KW_DOUBLE,   TOKEN_KW_ELSE,     TOKEN_KW_ENUM,     TOKEN_KW_EXTERN,
    TOKEN_KW_FLOAT,    TOKEN_KW_FOR,      TOKEN_KW_GOTO,     TOKEN_KW_IF,
    TOKEN_KW_INT,      TOKEN_KW_LONG,     TOKEN_KW_REGISTER, TOKEN_KW_RETURN,
    TOKEN_KW_SHORT,    TOKEN_KW_SIGNED,   TOKEN_KW_SIZEOF,   TOKEN_KW_STATIC,
    TOKEN_KW_STRUCT,   TOKEN_KW_SWITCH,   TOKEN_KW_TYPEDEF,  TOKEN_KW_UNION,
    TOKEN_KW_UNSIGNED, TOKEN_KW_VOID,     TOKEN_KW_VOLATILE, TOKEN_KW_WHILE
};

TokenType identify_token_group(char tb[TOKENB_SIZE], KeyWords *matched_kw) 
{
    for (int i = 0; i < KW_COUNT; i++) 
    {
        if (strcmp(tb, keyword_strings[i]) == 0) 
        {
            *matched_kw = (KeyWords)i;
            return TOKEN_TYPE_KEYWORD;
        }
    }

    if (strcmp(tb, TOKEN_SP_MAIN) == 0) 
    {
        return TOKEN_TYPE_SPECIAL;
    }

    return TOKEN_TYPE_UNKNOWN;
}

char* verify_found_token(char tb[TOKENB_SIZE])
{
    KeyWords kw_type;
    TokenType group = identify_token_group(tb, &kw_type);

    char* verified_token = NULL;

    switch (group)
    {
        case TOKEN_TYPE_KEYWORD:
            printf("[GROUP: KEYWORD] Match trovato: {%s} (Enum ID: %d)\n", keyword_strings[kw_type], kw_type);
            verified_token = tb;
            break;

        case TOKEN_TYPE_SPECIAL:
            printf("[GROUP: SPECIAL] Match trovato: {%s}\n", tb);
            verified_token = tb;
            break;

        case TOKEN_TYPE_UNKNOWN:
        default:
            if(strcmp(tb, " ") == 1)
            {
                printf("[TOKEN UNRECOGNIZED] Nessun gruppo corrispondente per: {%s}\n", tb);
            }

            break;
    }

    return verified_token;
}