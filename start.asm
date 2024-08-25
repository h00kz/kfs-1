section .note.GNU-stack
BITS 32

section .multiboot
    align 4
    dd 0x1badb002
    dd 0x0
    dd -(0x1badb002 + 0x0)

section .text
    global _start
    extern kernel_main ; in the c file

_start:
    cli
    mov esp, stack_top
    call kernel_main
    hlt
    jmp 1b

section .bss
    align 16
stack_bottom:
    resb 8192 * 2
stack_top:
