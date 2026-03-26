/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** description
*/

#ifndef TASK_H
    #define TASK_H
    #include "mysh.h"
typedef struct task_vars {
    task_t *head;
    task_t *cur;
    cmd_t *cmds;
    cmd_t *cmds_c;
    token_t *tmp;
    char *cmd[90];
    int idx;
    int nb_cmds;
    int skip;
    int count;
} t_vars_t;
void init_cmd(cmd_t **cmds);
void init_task(task_t **tsk);
void arr_cpy(char **src, char ***dest, int *nb, mem_t *mem);
int handle_word_and_pipe(token_t **tok, t_vars_t *v, mem_t *mem);
int handle_semicolon(t_vars_t *v, token_t **tok, mem_t *mem);
int handle_redirs(t_vars_t *v, token_t **tok, mem_t *mem);
int handle_remaining(t_vars_t *v, token_t **tok, mem_t *mem);
#endif
