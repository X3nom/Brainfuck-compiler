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

left:
    mov [mem + rbx], al 
sub rbx, 1
jnc left_operator_end 
    ; wrap around to end 
    mov rbx, mem_len 
    dec rbx 
    left_operator_end: 
    movzx rax, byte [mem + rbx] 
    ret 

right:
    mov [mem + rbx], al 
add rbx, 1
cmp rbx, mem_len 
    jl right_operator_end 
    ; wrap around to 0 
    xor rbx, rbx 
    right_operator_end: 
    movzx rax, byte [mem + rbx] 
    ret 

_exit: 
    mov rax, 60         ; syscall number for exit 
    xor rdi, rdi        ; exit code 0 
    syscall 

_start:
xor rax, rax
xor rbx, rbx

add rax, 7
cmp al, 0
je le0
ls0:
dec rax
call right
add rax, 10
call left
cmp al, 0
jnz ls0
le0:
call right
add rax, 2
call write
call left
add rax, 3
cmp al, 0
je le1
ls1:
dec rax
call right
add rax, 10
call left
cmp al, 0
jnz ls1
le1:
call right
dec rax
call write
add rax, 7
call write
call write
add rax, 3
call write
call right
add rax, 10
call write
jmp _exit
