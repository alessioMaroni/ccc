#ifndef LEXER_H
#define LEXER_H

#include "tokens_def.h"
#include <string.h>


#define TOKENB_SIZE 64
#define KW_COUNT    32

typedef enum {
    TOKEN_TYPE_KEYWORD,
    TOKEN_TYPE_SPECIAL,
    TOKEN_TYPE_UNKNOWN
} TokenType;

typedef enum {
    KW_AUTO, KW_BREAK, KW_CASE, KW_CHAR, KW_CONST, KW_CONTINUE, KW_DEFAULT, KW_DO,
    KW_DOUBLE, KW_ELSE, KW_ENUM, KW_EXTERN, KW_FLOAT, KW_FOR, KW_GOTO, KW_IF,
    KW_INT, KW_LONG, KW_REGISTER, KW_RETURN, KW_SHORT, KW_SIGNED, KW_SIZEOF, KW_STATIC,
    KW_STRUCT, KW_SWITCH, KW_TYPEDEF, KW_UNION, KW_UNSIGNED, KW_VOID, KW_VOLATILE, KW_WHILE
} KeyWords;

const char* keyword_strings[KW_COUNT] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "int", "long", "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
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

    if (strcmp(tb, TOKEN_MAIN) == 0) 
    {
        return TOKEN_TYPE_SPECIAL;
    }

    return TOKEN_TYPE_UNKNOWN;
}

void print_token_found(char tb[TOKENB_SIZE])
{
    KeyWords kw_type;
    TokenType group = identify_token_group(tb, &kw_type);

    switch (group)
    {
        case TOKEN_TYPE_KEYWORD:
            printf("[GROUP: KEYWORD] Match trovato: {%s} (Enum ID: %d)\n", keyword_strings[kw_type], kw_type);
            
            if (kw_type == KW_RETURN) {
            }
            break;

        case TOKEN_TYPE_SPECIAL:
            printf("[GROUP: SPECIAL] Match trovato: {%s}\n", tb);
            break;

        case TOKEN_TYPE_UNKNOWN:
        default:
            printf("[TOKEN UNRECOGNIZED] Nessun gruppo corrispondente per: {%s}\n", tb);
            break;
    }
}



#endif
