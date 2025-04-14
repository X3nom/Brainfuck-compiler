#include <asm_funcs.h>
#include <stdio.h>


bool USED_ASM_FUNCS[] = {
#define X(_x) false,
    ASM_FUNCTIONS_LIST
#undef X
};


void write_asm_head(FILE *tmp_src_in, FILE *src_out, int memsize){

    fprintf(src_out, "\
\
section .bss \n\
    mem resb %u \n\
section .data \n\
    mem_len equ %u \n\
section .text \n\
    global _start \n",
    memsize,
    memsize
    );


    USED_ASM_FUNCS[ASM_EXIT] = true; // has to be written
    for(int i=0; i < sizeof(USED_ASM_FUNCS)/sizeof(bool); i++){
        if(USED_ASM_FUNCS[i]){
            fprintf(src_out, "%s\n", ASM_FUNCS_S[i]);
        }
    }
    fprintf(src_out, "%s\n", ASM_START_S); // write _start

    for(char c = getc(tmp_src_in); c != EOF; c  = getc(tmp_src_in)){
        putc(c, src_out);
    }

    fprintf(src_out, "jmp _exit\n"); // write _exit at the end

}
