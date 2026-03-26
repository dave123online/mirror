/*
** EPITECH PROJECT, 2025
** my_put_floats
** File description:
** a function to display floats
*/

#include "librog.h"
int my_put_floats(double nb)
{
    int int_part = (int) nb;
    double dec_part = nb - int_part;
    int count = 0;

    count += my_put_nbr(int_part);
    if (int_part == nb)
        return count;
    my_putchar('.');
    count += my_put_nbr((int) (dec_part * 10000));
    return count;
}
