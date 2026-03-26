/*
** EPITECH PROJECT, 2025
** my_putchar
** File description:
** a char displayer
*/

#include <unistd.h>
int my_putchar(char c)
{
    write(1, &c, 1);
    return 1;
}
