/*
** EPITECH PROJECT, 2025
** my_strcmp
** File description:
** fonction to compare two strings
*/

int my_strcmp(char *str1, char *str2)
{
    int i = 0;
    int diff = 0;

    if (!str1 || !str2)
        return -1;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] - str2[i]) {
            diff = str1[i] - str2[i];
            break;
        }
        i++;
    }
    if (str1[i] == '\0')
        return -str2[i];
    if (str2[i] == '\0')
        return str1[i];
    return diff;
}
