/*
** EPITECH PROJECT, 2025
** my_put_scie
** File description:
** a function to display scientific form of numbers
*/

#include "librog.h"
#include <stdio.h>
void second_case(double nb, int i, double n)
{
    int j = (int) nb;

    if (nb > 1) {
        for (i = 0; j > 10; i++) {
            nb /= 10;
            j = (int) nb;
        }
        n = (n / my_pow(10, i));
        my_put_floats(n);
        if (i < 10) {
            my_putstr("e+0");
            my_put_nbr(i);
        } else {
            my_putstr("e+");
            my_put_nbr(i);
        }
    }
}

void my_put_sci_e(double nb)
{
    int i = 0;
    int j = (int) nb;
    double n = nb;

    if (nb < 1) {
        for (i = 0; j < 1; i++) {
            nb *= 10;
            j = (int) nb;
        }
        n = (n * my_pow(10, i));
        my_put_floats(n);
        if (i < 10) {
            my_putstr("e-0");
            my_put_nbr(i);
        } else {
            my_putstr("e-");
            my_put_nbr(i);
        }
    } else
        second_case(nb, i, n);
}
