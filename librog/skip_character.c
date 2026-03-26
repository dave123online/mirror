/*
** EPITECH PROJECT, 2025
** skip_characters
** File description:
** a function to skip up to 2 characters
*/

int skip_character(char *s, char u, char v, int i)
{
    while (s[i] == u || s[i] == v) {
        i++;
    }
    return i;
}
