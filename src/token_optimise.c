#include <stdlib.h>

#include <token.h>
#include <stdbool.h>


#define OR(val, a, b) (val == a || val == b)


#define GENERATE_HANDLE_SQUASH(T1, T2) \
static inline bool handle_squash_##T1##__##T2(TokenString *ts_in, TokenString* ts_out, int *i){ \
    int n = 0; \
    while(*i < ts_in->len && OR(ts_in->stack[*i].token_type, T1, T2)){ \
        n += ts_in->stack[*i].n * ((ts_in->stack[*i].token_type == T1) ? 1 : -1); \
        *i += 1; \
    } \
    if(n != 0){ \
        Token tok; \
        tok.token_type = (n > 0) ? T1 : T2; \
        tok.n = abs(n); \
        TokenString_push(ts_out, tok); \
        return true; \
    } \
    return false; \
}

GENERATE_HANDLE_SQUASH(BT_ADD, BT_SUBTRACT)
GENERATE_HANDLE_SQUASH(BT_RIGHT, BT_LEFT)

// Squashes patches of same tokens together `[{+, 1}, {+, 1}, {+, 1}] -> {+, 3}`
TokenString squash_tokens(TokenString *ts_in){
    TokenString ts_out = TokenString_new();

    int i=0;
    while(i < ts_in->len){
        
        if(handle_squash_BT_ADD__BT_SUBTRACT(ts_in, &ts_out, &i)) continue;

        if(handle_squash_BT_RIGHT__BT_LEFT(ts_in, &ts_out, &i)) continue;

        TokenString_push(&ts_out, ts_in->stack[i]);
        i++; // none was squashed, move i to next char
    }


    return ts_out;
}
