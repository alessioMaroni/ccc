#ifndef LEXER_H
#define LEXER_H

#include "tokens_def.h"
#include <string.h>

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

extern const char* keyword_strings[KW_COUNT];

TokenType identify_token_group(char tb[TOKENB_SIZE], KeyWords *matched_kw);
char* verify_found_token(char tb[TOKENB_SIZE]);

#endif