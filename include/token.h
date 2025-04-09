#pragma once
#include <stack.h>

typedef enum BaseTokenType{
    BT_PLUS,
    BT_MINUS,
    
    BT_LEFT,
    BT_RIGHT,

    BT_DOT,
    BT_COMMA,

    BT_LBR,
    BT_RBR,
} BaseTokenType;



/*
`n` represents:
- brackets -> id of brackets
- other operators -> operator multiplier 
*/
typedef struct{
    BaseTokenType token_type;
    int n;
} BaseToken;

BaseToken BaseToken_new(BaseTokenType type, int count);


GENERATE_STACK_WRAPPER(BaseToken, BaseTokenString);
