#include <stdlib.h>

#include <token.h>
#include <stdbool.h>


void squash_math_tokens(BaseTokenString *bts_in, BaseTokenString *bts_out){
    char math_val = 0;
    bool counting = false;

    for(int i=0; i<bts_in->len; i++){
        bts_in->stack[0];
    }
}



// Squashes patches of same tokens together `[{+, 1}, {+, 1}, {+, 1}] -> {+, 3}`
BaseTokenString squash_tokens(BaseTokenString *bts_in){
    BaseTokenString bts_out = BaseTokenString_new();

    squash_math_tokens(bts_in, &bts_out);

    return bts_out;
}
