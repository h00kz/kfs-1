#include "prompt.h"

// void prompt(char c)
// {
//     size_t term_col = get_term_col();
//     size_t term_row = get_term_row();
//     switch (c)
//     {
//     case '\n':
//         term_putchar('\n');
//         term_col = get_term_col();
//         term_row = get_term_row();
//         break;
//     case '\b':
//         if (term_col == 0)
//             return;
//         set_term_col(term_col--);
//         term_putchar(' ');
//         set_term_col(term_col--);
//         term_col = get_term_col();
//         term_row = get_term_row();
//         break;
//     case ('\n' || 0):
//         term_print("[kfs-1]:> ");
//         term_col = get_term_col();
//         term_row = get_term_row();
//         break;
//     default:
//         if (c != '\n')
//             term_putchar(c);
//         term_col = get_term_col();
//         term_row = get_term_row();
//         break;
//     }
// }