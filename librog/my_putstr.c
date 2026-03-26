/*
** EPITECH PROJECT, 2025
** my_putstr
** File description:
** a str displayer
*/

#include "librog.h"
int my_putstr(char const *str)
{
    int count = 0;
    int i = 0;

    if (str == NULL)
        return 84;
    while (str[i] != '\0') {
        my_putchar(str[i]);
        i++;
        count++;
    }
    return count;
}
