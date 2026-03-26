/*
** EPITECH PROJECT, 2026
** my_strncmp
** File description:
** description
*/

#include "librog.h"
int my_strncmp(char *str1, char *str2, int n)
{
    int i = 0;
    int diff = 0;

    if (!str1 || !str2)
        return -1;
    if (my_strlen(str1) < n || my_strlen(str2) < n)
        return 1;
    while (i < n) {
        if (str1[i] - str2[i])
            diff = str1[i] - str2[i];
        i++;
    }
    return diff;
}
