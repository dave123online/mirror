/*
** EPITECH PROJECT, 2025
** print_sub
** File description:
** a sub function of my_printf
*/

#include <stdarg.h>
#include "librog.h"
int print_sub5(ccr_t format, int i, va_list args)
{
    int count = 0;

    switch (format[i + 1]) {
        case 'p':
            count += my_put_ptr(va_arg(args, void *));
            break;
        default:
            count += 0;
    }
    return count;
}

int print_sub4(ccr_t format, int i, va_list args)
{
    int count = 0;

    switch (format[i + 1]) {
        case 'u':
            count += 0;
            break;
        case 'X':
            count += my_base_convert(va_arg(args, int), "0123456789ABCDEF");
            break;
        case 'c':
            count += my_putchar(va_arg(args, int));
            break;
        default:
            count += 0;
    }
    count += print_sub5(format, i, args);
    return count;
}

int print_sub3(ccr_t format, int i, va_list args)
{
    int count = 0;

    switch (format[i + 1]) {
        case 's':
            count += my_putstr(va_arg(args, char *));
            break;
        case '%':
            count += my_putchar('%');
            break;
        default:
            count += 0;
    }
    count += print_sub4(format, i, args);
    return count;
}

int print_sub2(ccr_t format, int i, va_list args)
{
    int count = 0;

    switch (format[i + 1]) {
        case 'f':
        case 'F':
            count += my_put_floats(va_arg(args, double));
            break;
        case 'e':
            my_put_sci_e(va_arg(args, double));
            count += 12;
            break;
        case 'E':
            maj_e_case(va_arg(args, double));
            count += 12;
            break;
        default:
            count += 0;
    }
    count += print_sub3(format, i, args);
    return count;
}

int print_sub1(ccr_t format, int i, va_list args)
{
    int count = 0;

    switch (format[i + 1]) {
        case 'd':
        case 'i':
            count += my_put_nbr(va_arg(args, int));
            break;
        case 'o':
            count += my_base_convert(va_arg(args, int), "01234567");
            break;
        case 'x':
            count += my_base_convert(va_arg(args, int), "0123456789abcdef");
            break;
        default:
            count += 0;
    }
    count += print_sub2(format, i, args);
    return count;
}
