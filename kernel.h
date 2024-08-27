// #pragma once

// static inline void outb(uint16_t port, uint8_t val)
// {
//     asm volatile ( "outb %b0, %w1": 
//                    : "a"(val), "Nd"(port)
//                    : "memory");
//     // appel l'instruction outb qui permet d'envoyer la valeur 'val' dans le port i/o 'port'
// }


// // pareil, appel l'instruction inb qui permet de recup la valeur du port i/o 'port'
// static inline uint8_t inb(uint16_t port)
// {
//     uint8_t ret;
//     asm volatile ( "inb %w1, %b0"
//                    : "=a"(ret)
//                    : "Nd"(port)
//                    : "memory");
//     return ret;
// }
