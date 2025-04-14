#include <stdlib.h>
#include <stdio.h>
#include <token.h>
#include <stack.h>


Token Token_new(TokenType type, int n){
    Token tok;
    tok.n = n;
    tok.token_type = type;
    return tok;
}


TokenString parse_src(FILE *src){
    TokenString bts = TokenString_new();
    intStack bracket_id_stack = intStack_new();
    int bracket_id = 0;

    char c;
    for(c = getc(src); c != EOF; c = getc(src)){
        
        #define scase(_c, ...) case _c: __VA_ARGS__ break;
        #define sscase(_c, _BT_TYPE) scase(_c, TokenString_push(&bts, Token_new(_BT_TYPE, 1)); )
        switch(c){
            sscase('+', BT_ADD)
            sscase('-', BT_SUBTRACT)
            sscase('<', BT_LEFT)
            sscase('>', BT_RIGHT)
            sscase('.', BT_WRITE)
            sscase(',', BT_READ)
            scase('[',
                TokenString_push(&bts, Token_new(BT_LOOP_START, bracket_id));
                intStack_push(&bracket_id_stack, bracket_id);
                bracket_id++;
            )
            scase(']',
                if(bracket_id_stack.len <= 0){
                    fprintf(stderr, "Missing ']'\n");
                    exit(-1);
                }
                int b_id = intStack_pop(&bracket_id_stack);
                TokenString_push(&bts, Token_new(BT_LOOP_END, b_id));
            )
        }
        #undef sscase
        #undef scase
    }

    if(bracket_id_stack.len > 0){
        fprintf(stderr, "Missing ']'\n");
        exit(-1);
    }

    intStack_destroy(&bracket_id_stack);
    return bts;
}