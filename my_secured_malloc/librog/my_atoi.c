/*
** EPITECH PROJECT, 2025
** my_atoi
** File description:
** a function to convert char * digits to int
*/

#include "librog.h"
int my_atoi(char *str)
{
    int i = 0;
    int j = 0;
    int x = 0;
    int converted = 0;
    int tab[64];

    if (str[0] == '0')
        i++;
    if (str[1] == 'x' || str[1] == 'X')
        i++;
    while (str[i] != '\0') {
        tab[x] = str[i] - 48;
        x++;
        i++;
    }
    for (j = 0; j < x; j++) {
        converted += tab[j] * my_pow(10, x - j - 1);
    }
    return converted;
}
