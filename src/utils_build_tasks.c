/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** description
*/

#include "../include/mysh.h"
#include "../include/task.h"
static void add_to_cmd(token_t *tok, char **cmd, int *idx, mem_t *mem)
{
    cmd[*idx] = xstrdup(tok->value, mem);
    (*idx)++;
}

void arr_cpy(char **src, char ***dest, int *nb, mem_t *mem)
{
    int i = 0;

    (*dest) = xmalloc(sizeof(char *) * (*nb + 1), mem);
    if (*dest == NULL)
        return;
    for (; i < *nb; i++) {
        (*dest)[i] = xstrdup(src[i], mem);
    }
    (*dest)[i] = NULL;
    *nb = 0;
}

int handle_word_and_pipe(token_t **tok, t_vars_t *v, mem_t *mem)
{
    if ((*tok)->type == WORD) {
        add_to_cmd(*tok, v->cmd, &v->idx, mem);
        (*tok) = (*tok)->next;
        return 1;
    }
    if ((*tok)->type == PIPE) {
        arr_cpy(v->cmd, &v->cmds_c->args, &v->idx, mem);
        v->cmds_c->next = xmalloc(sizeof(cmd_t), mem);
        v->cmds_c = v->cmds_c->next;
        init_cmd(&v->cmds_c);
        v->nb_cmds++;
        (*tok) = (*tok)->next;
        return 1;
    }
    return 0;
}

int handle_semicolon(t_vars_t *v, token_t **tok, mem_t *mem)
{
    if ((*tok)->type == SEMICOLON) {
        arr_cpy(v->cmd, &v->cmds_c->args, &v->idx, mem);
        v->cur->cmds = v->cmds;
        v->cur->cmd_count = v->nb_cmds + 1;
        v->cur->next = xmalloc(sizeof(task_t), mem);
        v->cur = v->cur->next;
        init_task(&v->cur);
        v->cmds = xmalloc(sizeof(cmd_t), mem);
        v->cmds_c = v->cmds;
        init_cmd(&v->cmds_c);
        v->cur->cmds = v->cmds;
        v->nb_cmds = 0;
        v->idx = 0;
        (*tok) = (*tok)->next;
        return 1;
    }
    return 0;
}

int handle_redirs(t_vars_t *v, token_t **tok, mem_t *mem)
{
    if ((*tok)->type == REDIR_OUT) {
        (*tok) = (*tok)->next;
        v->cmds_c->outfile = xstrdup((*tok)->value, mem);
        v->cmds_c->append = 0;
        v->skip = 1;
        (*tok) = (*tok)->next;
        return 1;
    }
    if ((*tok)->type == REDIR_IN) {
        (*tok) = (*tok)->next;
        v->cmds_c->infile = xstrdup((*tok)->value, mem);
        v->skip = 1;
        (*tok) = (*tok)->next;
        return 1;
    }
    return 0;
}

int handle_remaining(t_vars_t *v, token_t **tok, mem_t *mem)
{
    if ((*tok)->type == APPEND) {
        (*tok) = (*tok)->next;
        v->cmds_c->outfile = xstrdup((*tok)->value, mem);
        v->cmds_c->append = 1;
        v->skip = 1;
        (*tok) = (*tok)->next;
        return 1;
    }
    if ((*tok)->type == HEREDOC) {
        (*tok) = (*tok)->next;
        v->cmds_c->heredoc_delim = xstrdup((*tok)->value, mem);
        v->skip = 1;
        (*tok) = (*tok)->next;
        return 1;
    }
    return 0;
}
