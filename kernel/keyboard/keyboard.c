#include "keyboard.h"
#include "../idt/idt.h"
#include "../../lib/libk/libk.h"
// #include "../prompt/prompt.h"
#include "../vga/vga.h"

void handle_keyboard_interrupt()
{
	ioport_out(PIC1_COMMAND, 0x20); // write end of interrupt (EOI)
	unsigned char status = ioport_in(KEYBOARD_STATUS_PORT);

	if (status & 0x1) {
		char keycode = ioport_in(KEYBOARD_DATA_PORT);
		if (keycode < 0 || keycode >= 128)
			return;
        // kprintf("keycode: %d %c\n", keycode, keyboard_map[keycode]);
        prompt(keyboard_map[keycode]);
    }
}