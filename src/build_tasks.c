/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** description
*/

#include "../include/mysh.h"
#include "../include/librog.h"
#include "../include/task.h"
static void init_build(t_vars_t *v, mem_t *mem)
{
    v->head = xmalloc(sizeof(task_t), mem);
    v->cur = v->head;
    v->cmds = xmalloc(sizeof(cmd_t), mem);
    v->cmds_c = v->cmds;
    v->idx = 0;
    v->nb_cmds = 0;
    v->count = 0;
}

void init_task(task_t **tsk)
{
    (*tsk)->cmd_count = 0;
    (*tsk)->cmds = NULL;
    (*tsk)->next = NULL;
}

void init_cmd(cmd_t **cmds)
{
    (*cmds)->append = 0;
    (*cmds)->args = NULL;
    (*cmds)->herodoc_delim = 0;
    (*cmds)->infile = 0;
    (*cmds)->next = NULL;
    (*cmds)->outfile = 0;
}

static task_t *flush(t_vars_t *v, mem_t *mem)
{
    arr_cpy(v->cmd, &v->cmds_c->args, &v->idx, mem);
    v->cur->cmds = v->cmds;
    v->cur->cmd_count = v->nb_cmds + 1;
    return v->head;
}

static int check(t_vars_t *v, mem_t *mem, token_t **tok)
{
    if (handle_word_and_pipe(tok, v, mem))
        return 1;
    if (handle_semicolon(v, tok, mem))
        return 1;
    if (handle_redirs(v, tok, mem))
        return 1;
    if (handle_remaining(v, tok, mem))
        return 1;
    return 0;
}

task_t *build_tasks(token_t *tokens, mem_t *mem)
{
    t_vars_t v = {0};

    init_build(&v, mem);
    if (!v.cur || !v.cmds) {
        my_perror("malloc failed\n");
        exit(84);
    }
    init_task(&v.head);
    init_cmd(&v.cmds);
    while (tokens) {
        v.skip = 0;
        if (check(&v, mem, &tokens))
            continue;
    }
    return flush(&v, mem);
}
