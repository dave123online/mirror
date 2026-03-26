/*
** EPITECH PROJECT, 2025
** my_pow
** File description:
** a recoding of libC pow
*/

#include "librog.h"
int my_pow(int x, int y)
{
    int i = 1;
    int n = x;

    while (i < y) {
        x *= n;
        i++;
    }
    if (y == 1)
        x = x;
    if (y == 0)
        x = 1;
    return x;
}
