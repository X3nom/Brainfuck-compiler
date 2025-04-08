; this base templates
; rbx -> bf mem ptr
; rax -> current cell value

section .bss
    mem resb ;$0

section .data
    mem_len db ;$0

section .text
    global _start
    

_exit:
    ; EXIT
    ; exit syscall: exit(0)
    mov rax, 60         ; syscall number for exit
    xor rdi, rdi        ; exit code 0
    syscall


dot_operator:
    ; . operation -> print out char to stdout
    push rax

    mov rsi, rbx

    mov rax, 1
    mov rdi, 1
    mov rdx, 1
    syscall

    pop rax
    ret

comma_operator:
    ; , operation -> get char from stdin, load it into rax
    lea rsi, [mem + rbx]

    mov rax, 0
    mov rdi, 0
    mov rdx, 1
    syscall

    movzx rax, byte [mem + rbx]
    ret

plus_operator:
    inc al
    ret

minus_operator:
    dec al
    ret

left_operator:
    mov [mem + rbx], al
    dec rbx
    jnz left_operator_end
    ; wrap around to end
    mov rbx, [mem_len]
    dec rbx

    left_operator_end:
    movzx rax, byte [mem + rbx]
    ret

right_operator:
    mov [mem + rbx], al
    inc rbx
    cmp rbx, [mem_len]
    jl right_operator_end
    ; wrap around to 0
    xor rbx, rbx

    right_operator_end:
    movzx rax, byte [mem + rbx]
    ret

; lb0:
;     cmp al, 0
;     jz rb0

; rb0:
;     cmp al, 0
;     jz lb0


_start:

