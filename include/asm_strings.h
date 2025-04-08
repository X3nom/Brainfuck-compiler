#pragma ONCE

#define BF_ASM_EXIT "\
_exit: \n\
    mov rax, 60         ; syscall number for exit \n\
    xor rdi, rdi        ; exit code 0 \n\
    syscall \n\
"

#define BF_ASM_DOT "\
dot_operator: \n\
    push rax \n\
    mov rsi, rbx \n\
    mov rax, 1 \n\
    mov rdi, 1 \n\
    mov rdx, 1 \n\
    syscall \n\
    pop rax \n\
    ret \n\
"

#define BF_ASM_COMMA "\
comma_operator: \n\
    lea rsi, [mem + rbx] \n\
    mov rax, 0 \n\
    mov rdi, 0 \n\
    mov rdx, 1 \n\
    syscall \n\
    movzx rax, byte [mem + rbx] \n\
    ret \n\
"


#define BF_ASM_LEFT "\
left_operator: \n\
    mov [mem + rbx], al \n\
    dec rbx \n\
    jnz left_operator_end \n\
    ; wrap around to end \n\
    mov rbx, [mem_len] \n\
    dec rbx \n\
    left_operator_end: \n\
    movzx rax, byte [mem + rbx] \n\
    ret \n\
"

#define BF_ASM_RIGHT "\
right_operator: \n\
    mov [mem + rbx], al \n\
    inc rbx \n\
    cmp rbx, [mem_len] \n\
    jl right_operator_end \n\
    ; wrap around to 0 \n\
    xor rbx, rbx \n\
    right_operator_end: \n\
    movzx rax, byte [mem + rbx] \n\
    ret \n\
"

#define BF_ASM_START "\
section .text \n\
    global _start \n\
_start:\n"


#define BF_ASM_HEAD_FULL \
    BF_ASM_EXIT \
    BF_ASM_DOT \
    BF_ASM_COMMA \
    BF_ASM_LEFT \
    BF_ASM_RIGHT \
    BF_ASM_START
