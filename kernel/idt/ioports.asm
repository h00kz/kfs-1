section .note.GNU-stack



global ioport_in
global ioport_out
global keyboard_handler
global enable_int
extern handle_keyboard_interrupt

ioport_in:
    mov edx, [esp + 4] ; PORT_TO_READ, 16 bits
    in al, dx
    ret

ioport_out:
    mov edx, [esp + 4] ; dest io port 16bits
    mov eax, [esp + 8] ; value to write 8bits
    out dx, al
    ret

enable_int:
    sti
    ret


keyboard_handler:
    pushad
    cld
    call handle_keyboard_interrupt
    popad
    iretd