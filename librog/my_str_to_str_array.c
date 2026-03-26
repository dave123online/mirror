/*
** EPITECH PROJECT, 2025
** my_radar - main.c
** File description:
** main function
*/

#include "librog.h"
static void init_my_sta_vars(my_sta_t *v)
{
    v->i = 0;
    v->j = 0;
    v->k = 0;
    v->count = 0;
    v->len = 0;
    v->arr = NULL;
}

static void sub_mysta(my_sta_t *v, char *str, char c)
{
    for (v->i = 0; v->i <= v->count; v->i++) {
        v->len = xstrlen(&str[v->k], c);
        v->arr[v->i] = xmalloc(v->len + 1);
        for (v->j = 0; v->j < (int) v->len; v->j++) {
            v->arr[v->i][v->j] = str[v->k];
            v->k++;
        }
        v->arr[v->i][v->j] = '\0';
        for (; str[v->k] == c || str[v->k] == '\t'; v->k++);
    }
}

static char **my_str_to_str_array(char *str, char c)
{
    my_sta_t *v = xmalloc(sizeof(my_sta_t));

    init_my_sta_vars(v);
    for (; str[v->i] != '\0'; v->i++) {
        if ((str[v->i] == '\t' || str[v->i] == c) &&
            str[v->i - 1] != '\t' && str[v->i - 1] != c)
            v->count++;
    }
    v->arr = xmalloc(sizeof(char *) * (v->count + 2));
    sub_mysta(v, str, c);
    v->arr[v->i] = NULL;
    return v->arr;
}
