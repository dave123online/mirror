/*
** EPITECH PROJECT, 2025
** my_put_nbr
** File description:
** a integer displayer
*/

#include "librog.h"
#include <stdio.h>
int part_two(int i, char tab[15], int count, int nb)
{
    for (i--; i >= 0; i--) {
        count += my_putchar(tab[i]);
    }
    if (nb == -2147483648) {
        my_putstr("2147483648");
        count = 10;
    }
    return count;
}

int my_put_nbr(int nb)
{
    int i = 0;
    char tab[15];
    int count = 0;

    if (nb < 0) {
        my_putchar('-');
        nb = -nb;
        count++;
    }
    if (nb == 0) {
        my_putchar('0');
        count++;
    }
    while (nb > 0) {
        tab[i] = (nb % 10) + 48;
        nb = nb / 10;
        i++;
    }
    count = part_two(i, tab, count, nb);
    return count;
}
