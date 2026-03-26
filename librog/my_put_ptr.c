/*
** EPITECH PROJECT, 2025
** my_put_ptr
** File description:
** a function to display pointers
*/

#include <stdint.h>
#include "librog.h"
int my_put_ptr(void *ptr)
{
    int count = 0;
    uintptr_t addr = (uintptr_t) ptr;
    char *digits = "0123456789abcdef";
    char buffer[64];
    int i;

    my_putstr("0x");
    for (i = 0; addr > 0; i++) {
        buffer[i] = digits[addr % 16];
        addr /= 16;
    }
    for (i--; i >= 0; i--) {
        my_putchar(buffer[i]);
        count++;
    }
    return count + 2;
}
