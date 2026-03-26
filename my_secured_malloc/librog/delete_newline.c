/*
** EPITECH PROJECT, 2026
** delete_newline.c
** File description:
** description
*/

#include "librog.h"
char *delete_newline(char *s)
{
    int len = my_strlen(s);

    if (s == NULL)
        return NULL;
    if (s[len - 1] == '\n')
        s[len - 1] = '\0';
    return s;
}
