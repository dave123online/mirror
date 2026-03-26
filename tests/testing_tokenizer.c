/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** description
*/

#include <criterion/criterion.h>
#include "../include/mysh.h"

Test(tokenizer, pipe_and_redir)
{
    mem_t mem = {0};
    token_t *tok = tokenize_input("ls -l | wc -c > tutu", &mem);

    cr_assert_not_null(tok);
    cr_assert_eq(tok->type, WORD);
    cr_assert_str_eq(tok->value, "ls");
    tok = tok->next;
    cr_assert_eq(tok->type, WORD);
    cr_assert_str_eq(tok->value, "-l");
    tok = tok->next;
    cr_assert_eq(tok->type, PIPE);
    cr_assert_null(tok->value);
    tok = tok->next;
    cr_assert_eq(tok->type, WORD);
    cr_assert_str_eq(tok->value, "wc");
    tok = tok->next;
    cr_assert_eq(tok->type, WORD);
    cr_assert_str_eq(tok->value, "-c");
    tok = tok->next;
    cr_assert_eq(tok->type, REDIR_OUT);
    cr_assert_null(tok->value);
    tok = tok->next;
    cr_assert_eq(tok->type, WORD);
    cr_assert_str_eq(tok->value, "tutu");
    cr_assert_null(tok->next);
    free_all(&mem);
}

Test(tokenizer, semicolon_and_append)
{
    mem_t mem = {0};
    token_t *tok = tokenize_input("echo hi ; cat >> out", &mem);

    cr_assert_not_null(tok);
    cr_assert_eq(tok->type, WORD);
    cr_assert_str_eq(tok->value, "echo");
    tok = tok->next;
    cr_assert_eq(tok->type, WORD);
    cr_assert_str_eq(tok->value, "hi");
    tok = tok->next;
    cr_assert_eq(tok->type, SEMICOLON);
    tok = tok->next;
    cr_assert_eq(tok->type, WORD);
    cr_assert_str_eq(tok->value, "cat");
    tok = tok->next;
    cr_assert_eq(tok->type, APPEND);
    tok = tok->next;
    cr_assert_eq(tok->type, WORD);
    cr_assert_str_eq(tok->value, "out");
    cr_assert_null(tok->next);
    free_all(&mem);
}
