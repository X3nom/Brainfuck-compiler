#pragma once
#include <stdbool.h>
#include <stdio.h>

static const char ASM_START_S[] = "\
_start:\n\
xor rax, rax\n\
xor rbx, rbx\n\
";

static const char ASM_EXIT_S[] = "\
_exit: \n\
    mov rax, 60         ; syscall number for exit \n\
    xor rdi, rdi        ; exit code 0 \n\
    syscall \n\
";

static const char ASM_WRITE_S[] = "\
write: \n\
    mov [mem + rbx], al \n\
    push rax \n\
    lea rsi, [mem + rbx] \n\
    mov rax, 1 \n\
    mov rdi, 1 \n\
    mov rdx, 1 \n\
    syscall \n\
    pop rax \n\
    ret \n\
";

static const char ASM_READ_S[] = "\
read: \n\
    lea rsi, [mem + rbx] \n\
    mov rax, 0 \n\
    mov rdi, 0 \n\
    mov rdx, 1 \n\
    syscall \n\
    movzx rax, byte [mem + rbx] \n\
    ret \n\
";

/*================================
|       LEFT
================================*/
#define _ASM_LEFT "\
    mov [mem + rbx], al \n" \
    X \
    "jnc left_operator_end \n\
    ; wrap around to end \n\
    mov rbx, mem_len \n\
    dec rbx \n\
    left_operator_end: \n\
    movzx rax, byte [mem + rbx] \n\
    ret \n\
"
#define X "sub rbx, 1\n"
// Move ptr left by 1
static const char ASM_LEFT_S[] = "left:\n" _ASM_LEFT;
#undef X
#define X "sub rbx, rdi\n"
// Move ptr left by rdi
static const char ASM_LEFT_N_S[] = "left_n:\n" _ASM_LEFT;
#undef X

/*================================
|       RIGHT
================================*/
#define _ASM_RIGHT "\
    mov [mem + rbx], al \n" \
    X \
    "cmp rbx, mem_len \n\
    jl right_operator_end \n\
    ; wrap around to 0 \n\
    xor rbx, rbx \n\
    right_operator_end: \n\
    movzx rax, byte [mem + rbx] \n\
    ret \n\
"
#define X "add rbx, 1\n"
static const char ASM_RIGHT_S[] = "right:\n" _ASM_RIGHT;
#undef X
#define X "add rbx, rdi\n"
static const char ASM_RIGHT_N_S[] = "right_n\n" _ASM_RIGHT;
#undef X




#define ASM_FUNCTIONS_LIST \
    X(ASM_WRITE) \
    X(ASM_READ) \
\
    X(ASM_LEFT) \
    X(ASM_LEFT_N) \
\
    X(ASM_RIGHT) \
    X(ASM_RIGHT_N) \
\
    X(ASM_EXIT) // should always be last

enum ASM_FUNCS{
    #define X(_x) _x,
    ASM_FUNCTIONS_LIST
    #undef X
    ASM_FUNCS_COUNT
};


extern bool USED_ASM_FUNCS[ASM_FUNCS_COUNT];


static const char *ASM_FUNCS_S[] = {
    #define X(_x) (const char*)_x##_S,
    ASM_FUNCTIONS_LIST
    #undef X
};


#define BF_ASM_USE(_f) USED_ASM_FUNCS[_f] = true

void write_asm_head(FILE *tmp_src_in, FILE *src_out, int memsize);