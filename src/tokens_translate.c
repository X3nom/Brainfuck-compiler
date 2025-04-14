#include <stdio.h>
#include <token.h>
#include <asm_funcs.h>
#include <tokens_translate.h>


DEF_TRANSLATE_FN(BT_NONE){/*Do nothing?*/}


DEF_TRANSLATE_FN(BT_ADD){
    if(tok->n > 1) fprintf(out, "add rax, %d\n", tok->n % 256);
    else if(tok->n == 1) fprintf(out, "inc rax\n");
}
DEF_TRANSLATE_FN(BT_SUBTRACT){
    if(tok->n > 1) fprintf(out, "sub rax, %d\n", tok->n % 256);
    else if(tok->n == 1) fprintf(out, "dec rax\n");
}

DEF_TRANSLATE_FN(BT_LEFT){
    if(tok->n == 1){
        fprintf(out, "call left\n");
        BF_ASM_USE(ASM_LEFT);
    }
    else if(tok->n > 1){
        fprintf(out, "mov rdi, %d\ncall left_n\n", tok->n);
        BF_ASM_USE(ASM_LEFT_N);
    }
}
DEF_TRANSLATE_FN(BT_RIGHT){
    if(tok->n == 1){
        fprintf(out, "call right\n");
        BF_ASM_USE(ASM_RIGHT);
    }
    else if(tok->n > 1){
        fprintf(out, "mov rdi, %d\ncall right_n\n", tok->n);
        BF_ASM_USE(ASM_RIGHT_N);
    }
}

DEF_TRANSLATE_FN(BT_LOOP_START){
    fprintf(out, "cmp al, 0\n" "je le%d\n" "ls%d:\n", tok->n, tok->n);
}
DEF_TRANSLATE_FN(BT_LOOP_END){
    fprintf(out, "cmp al, 0\n" "jnz ls%d\n" "le%d:\n", tok->n, tok->n);
}

DEF_TRANSLATE_FN(BT_READ){
    fprintf(out, "call read\n");
    BF_ASM_USE(ASM_READ);
}
DEF_TRANSLATE_FN(BT_WRITE){
    fprintf(out, "call write\n");
    BF_ASM_USE(ASM_WRITE);
}


void translate_tokens_2_asm(FILE *out, TokenString ts){
    for(int i=0; i < ts.len; i++){

        Token tok = ts.stack[i]; 
        
        translate_func f = TRANSLATION_TABLE[tok.token_type];

        f(out, &tok);

    }

}



/*
void write_head(FILE *output, uint32_t memsize){
    fprintf(output, "\
\
section .bss \n\
    mem resb %u \n\
section .data \n\
    mem_len equ %u \n\
section .text \n\
    global _start \n\
%s",
    memsize,
    memsize,
    BF_ASM_HEAD_FULL
    );
}

void write_exit(FILE *output){
    fprintf(output, "call _exit\n");
}
*/
