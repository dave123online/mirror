/*
** EPITECH PROJECT, 2026
** my_strdup.c
** File description:
** description
*/

#include <stdlib.h>
#include "librog.h"
char *my_strdup(char *str)
{
    char *dup = NULL;
    int i = 0;
    int len = 0;

    if (!str)
        return NULL;
    len = my_strlen(str);
    dup = malloc(len + 1);
    if (dup == NULL)
        return NULL;
    while (i < len) {
        dup[i] = str[i];
        i++;
    }
    dup[i] = '\0';
    return dup;
}
