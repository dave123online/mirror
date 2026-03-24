/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** description
*/

#ifndef TOKENIZE_H
    #define TOKENIZE_H
    #include "mysh.h"
typedef struct tokenize_s {
    token_t *head;
    token_t *cur_tok;
    char word[156];
    int idx;
    char cur;
    int i;
} tokenize_t;
#endif
