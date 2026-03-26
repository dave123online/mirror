/*
** EPITECH PROJECT, 2025
** my_base_converter
** File description:
** as said by the name
*/

#include "librog.h"
int my_base_convert(int nb, char *digits)
{
    int count = 0;
    int i;
    char buffer[12];

    for (i = 0; nb != 0; i++) {
        buffer[i] = digits[nb % my_strlen(digits)];
        nb /= my_strlen(digits);
    }
    for (i--; i >= 0; i--) {
        count += my_putchar(buffer[i]);
    }
    return count;
}
