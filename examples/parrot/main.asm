section .bss 
    mem resb 4095 
section .data 
    mem_len equ 4095 
section .text 
    global _start 
write: 
    mov [mem + rbx], al 
    push rax 
    lea rsi, [mem + rbx] 
    mov rax, 1 
    mov rdi, 1 
    mov rdx, 1 
    syscall 
    pop rax 
    ret 

read: 
    lea rsi, [mem + rbx] 
    mov rax, 0 
    mov rdi, 0 
    mov rdx, 1 
    syscall 
    movzx rax, byte [mem + rbx] 
    ret 

_exit: 
    mov rax, 60         ; syscall number for exit 
    xor rdi, rdi        ; exit code 0 
    syscall 

_start:
xor rax, rax
xor rbx, rbx

inc rax
cmp al, 0
je le0
ls0:
call write
call read
cmp al, 0
jnz ls0
le0:
jmp _exit
