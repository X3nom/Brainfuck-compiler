#pragma once
#include <token.h>
#include <token_types.h>
#include <stdio.h>


typedef void (*translate_func)(FILE *out, Token* tok);

/* Generates the function signature + name for translating
signature: `void translate_<tokentype>(FILE *out, Token* tok)`*/
#define DEF_TRANSLATE_FN(_tok_T) void translate_##_tok_T(FILE *out, Token *tok)

#define TRANSLATE_FN(_tok_T) translate_##_tok_T


// Automatic declaration of translation functions for all TokenTypes
#define X(_tok_T) DEF_TRANSLATE_FN(_tok_T);
TOKEN_TYPES_LIST
#undef X

// Lookup table mapping `enum TokenType` => `func translate_<TokenType>`
static translate_func TRANSLATION_TABLE[] = {
    // Automatic generation of lookup table 
    #define X(_tok_T) [_tok_T] = TRANSLATE_FN(_tok_T),
    TOKEN_TYPES_LIST
    #undef X
};

void translate_tokens_2_asm(FILE *out, TokenString ts);