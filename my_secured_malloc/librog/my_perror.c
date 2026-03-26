/*
** EPITECH PROJECT, 2025
** mini_printf
** File description:
** a function that handle some parts of printf
*/

#include "my_perror.h"
static void my_putchar(char c)
{
    write(2, &c, 1);
}

static int my_putstr(char const *str)
{
    int i = 0;

    if (!str)
        return 0;
    while (str[i] != '\0') {
        my_putchar(str[i]);
        i++;
    }
    my_putchar('\0');
    return 0;
}

static int my_put_nbr(int nb)
{
    int i = 0;
    char tab[12];

    if (nb < 0) {
        my_putchar('-');
        nb = -nb;
    }
    if (nb == 0) {
        my_putchar('0');
        return 0;
    }
    while (nb > 0) {
        tab[i] = (nb % 10) + 48;
        nb = nb / 10;
        i++;
    }
    for (i--; i >= 0; i--) {
        my_putchar(tab[i]);
    }
    return 0;
}

static void smnprintf(const char *format, int i, va_list args)
{
    switch (format[i + 1]) {
        case 'd':
        case 'i':
            my_put_nbr(va_arg(args, int));
            break;
        case 's':
            my_putstr(va_arg(args, char *));
            break;
        case 'c':
            my_putchar(va_arg(args, int));
            break;
        case '%':
            my_putchar('%');
            break;
        default:
            my_putchar(format[i + 1]);
            break;
    }
}

int my_perror(const char *format, ...)
{
    va_list args;
    int i;

    va_start(args, format);
    for (i = 0; i < my_strlen((char *)format); i++) {
        if (format[i] == '%') {
            smnprintf(format, i, args);
            i++;
        } else {
            my_putchar(format[i]);
        }
    }
    va_end(args);
    return 0;
}
