#pragma once
#include <stack.h>
#include <token_types.h>

// Evil macro magic that generates the enum
#define X(_x) _x,
typedef enum TokenType{
    TOKEN_TYPES_LIST
} TokenType;
#undef X


/*
`n` represents:
- brackets -> id of brackets
- other operators -> operator multiplier 
*/
typedef struct{
    TokenType token_type;
    int n;
} Token;

Token Token_new(TokenType type, int n);


GENERATE_STACK_WRAPPER(Token, TokenString);
