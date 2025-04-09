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
inc al
inc al
inc al
inc al
inc al
inc al
lb0:
cmp al, 0
jz rb0
dec al
call right_operator
inc al
inc al
inc al
inc al
inc al
inc al
inc al
inc al
inc al
inc al
call left_operator
rb0:
cmp al, 0
jnz lb0
call right_operator
inc al
inc al
call dot_operator
call left_operator
inc al
inc al
inc al
lb1:
cmp al, 0
jz rb1
dec al
call right_operator
inc al
inc al
inc al
inc al
inc al
inc al
inc al
inc al
inc al
inc al
call left_operator
rb1:
cmp al, 0
jnz lb1
call right_operator
dec al
call dot_operator
inc al
inc al
inc al
inc al
inc al
inc al
inc al
call dot_operator
call dot_operator
inc al
inc al
inc al
call dot_operator
call right_operator
inc al
inc al
inc al
inc al
inc al
inc al
inc al
inc al
inc al
inc al
call dot_operator
call _exit
