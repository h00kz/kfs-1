section .note.GNU-stack

global load_idt

load_idt:
    mov eax, [esp + 4] ; idt_addr
    lidt [eax]
    ret