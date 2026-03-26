/*
** EPITECH PROJECT, 2025
** my_strlen
** File description:
** a function that return the lenght of an string
*/

int my_strlen(char const *str)
{
    int i = 0;

    if (!str)
        return 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}
