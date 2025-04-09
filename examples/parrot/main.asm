section .bss 
    mem resb 4095 
section .data 
    mem_len equ 4095 
section .text 
    global _start 
_exit: 
    mov rax, 60         ; syscall number for exit 
    xor rdi, rdi        ; exit code 0 
    syscall 
dot_operator: 
    mov [mem + rbx], al 
    push rax 
    lea rsi, [mem + rbx] 
    mov rax, 1 
    mov rdi, 1 
    mov rdx, 1 
    syscall 
    pop rax 
    ret 
comma_operator: 
    lea rsi, [mem + rbx] 
    mov rax, 0 
    mov rdi, 0 
    mov rdx, 1 
    syscall 
    movzx rax, byte [mem + rbx] 
    ret 
left_operator: 
    mov [mem + rbx], al 
    dec rbx 
    jc left_operator_end 
    ; wrap around to end 
    mov rbx, mem_len 
    dec rbx 
    left_operator_end: 
    movzx rax, byte [mem + rbx] 
    ret 
right_operator: 
    mov [mem + rbx], al 
    inc rbx 
    cmp rbx, mem_len 
    jl right_operator_end 
    ; wrap around to 0 
    xor rbx, rbx 
    right_operator_end: 
    movzx rax, byte [mem + rbx] 
    ret 
_start:
xor rax, rax
xor rbx, rbx
inc al
lb0:
cmp al, 0
jz rb0
call dot_operator
call comma_operator
rb0:
cmp al, 0
jnz lb0
call _exit
