/*
** EPITECH PROJECT, 2026
** my_strcat.c
** File description:
** description
*/

#include "librog.h"
int my_strcat(char **buf, char *s1, char *s2)
{
    int i = 0;
    int j = 0;
    int l1 = my_strlen(s1);
    int l2 = my_strlen(s2);

    if (!s1 || !s2)
        return 84;
    while (i < l1) {
        (*buf)[i] = s1[i];
        i++;
    }
    if (s2) {
        for (i = l1; i < l2 + l1; i++) {
            (*buf)[i] = s2[j];
            j++;
        }
        (*buf)[i] = '\0';
    }
    return 0;
}
