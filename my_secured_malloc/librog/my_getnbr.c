/*
** EPITECH PROJECT, 2025
** my_getnbr
** File description:
** a function to return a int to the program
*/

int my_getsign(char const *str)
{
    int x = 0;
    int i = 0;

    while (str[i] == '+' || str[i] == '-') {
        if (str[i] == '-') {
            x++;
        }
        i++;
    }
    return (x % 2 == 0) ? 1 : -1;
}

int my_getnbr(char const *str)
{
    int i = 0;
    int n = 0;
    int sign = my_getsign(str);

    while (str[i] == '+' || str[i] == '-') {
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9') {
        n = (n * 10) + (str[i] - '0');
        i++;
    }
    if (n <= -2147483647 || n >= 2147483647) {
        n = 0;
    }
    n *= sign;
    return n;
}
