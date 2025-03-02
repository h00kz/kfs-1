#include "keyboard.h"
#include "../idt/idt.h"
#include "../../lib/libk/libk.h"
// #include "../prompt/prompt.h"
#include "../vga/vga.h"

void handle_keyboard_interrupt(char vga_address)
{
	ioport_out(PIC1_COMMAND, 0x20); // write end of interrupt (EOI)
	unsigned char status = ioport_in(KEYBOARD_STATUS_PORT);

	if (status & 0x1) {
		char keycode = ioport_in(KEYBOARD_DATA_PORT);
		if (keycode < 0 || keycode >= 128)
			return;
		
		// term_putchar(keycode);
		term_putchar('\n');
		term_print("keycode :");
		term_putchar(keycode);
		if (keycode == 38) // 38 = 'l'
		{
			// term_putchar(vga_address);
			term_print("'l' key pressed !");
			term_putchar(vga_address);
			term_putchar(VGA_ADDRESS_1);
			if (vga_address == VGA_ADDRESS_1)
			{
				term_print("Swtich to VGA_ADDRESS_2");
				vga_address = VGA_ADDRESS_2;
			}
			else if (vga_address == VGA_ADDRESS_2)
			{
				term_print("Swtich to VGA_ADDRESS_1");
				vga_address = VGA_ADDRESS_1;
			}
			term_launcher(vga_address);
		}
		else
		{
        	// kprintf("keycode: %d %c\n", keycode, keyboard_map[keycode]);
        	prompt(keyboard_map[keycode]);
		}
	}
}