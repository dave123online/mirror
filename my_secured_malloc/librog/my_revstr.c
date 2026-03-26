/*
** EPITECH PROJECT, 2025
** my_revstr
** File description:
** a function to reverse string using pointers
*/

char *my_revstr(char *str)
{
    int str_len = 0;
    int i;
    int j;
    char temp;

    while (str[str_len] != '\0') {
        str_len++;
    }
    i = 0;
    j = str_len - 1;
    while (i <= j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
        str = &str[0];
    }
    return str;
}
