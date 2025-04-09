#include <stdlib.h>
#include <stdio.h>
#include <token.h>
#include <stack.h>




BaseTokenString parse_src(FILE *src){
    BaseTokenString bts = BaseTokenString_new();
    intStack bracket_id_stack = intStack_new();
    int bracket_id = 0;

    char c;
    for(c = getc(src); c != EOF; c = getc(src)){
        
        #define scase(_c, ...) case _c: __VA_ARGS__ break;
        #define sscase(_c, _BT_TYPE) scase(_c, BaseTokenString_push(&bts, BaseToken_new(_BT_TYPE, 1)); )
        switch(c){
            sscase('+', BT_PLUS)
            sscase('-', BT_MINUS)
            sscase('<', BT_LEFT)
            sscase('>', BT_RIGHT)
            sscase('.', BT_DOT)
            sscase(',', BT_COMMA)
            scase('[',
                BaseTokenString_push(&bts, BaseToken_new(BT_LBR, bracket_id));
                intStack_push(&bracket_id_stack, bracket_id);
                bracket_id++;
            )
            scase(']',
                if(bracket_id_stack.len <= 0){
                    perror("Missing ']'\n");
                    exit(-1);
                }
                int b_id = intStack_pop(&bracket_id_stack);
                BaseTokenString_push(&bts, BaseToken_new(BT_RBR, b_id));
            )
        }
        #undef sscase
        #undef scase
    }

    intStack_destroy(&bracket_id_stack);
    return bts;
}