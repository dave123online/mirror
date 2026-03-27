/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** description
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/mysh.h"

Test(redirections, redir_out, .init = cr_redirect_stdout)
{
    mem_t mem = {0};
    token_t *tok = tokenize_input("echo hello > /tmp/test_redir", &mem);
    task_t *task = build_tasks(tok, &mem);

    cr_assert_not_null(task);
    cr_assert_str_eq(task->cmds->outfile, "/tmp/test_redir");
    cr_assert_eq(task->cmds->append, 0);
    free_all(&mem);
}

Test(redirections, redir_append)
{
    mem_t mem = {0};
    token_t *tok = tokenize_input("echo hello >> /tmp/test_append", &mem);
    task_t *task = build_tasks(tok, &mem);

    cr_assert_not_null(task);
    cr_assert_str_eq(task->cmds->outfile, "/tmp/test_append");
    cr_assert_eq(task->cmds->append, 1);
    free_all(&mem);
}

Test(redirections, redir_in)
{
    mem_t mem = {0};
    token_t *tok = tokenize_input("cat < /tmp/test_redir", &mem);
    task_t *task = build_tasks(tok, &mem);

    cr_assert_not_null(task);
    cr_assert_str_eq(task->cmds->infile, "/tmp/test_redir");
    cr_assert_null(task->cmds->outfile);
    free_all(&mem);
}

Test(redirections, heredoc_delim)
{
    mem_t mem = {0};
    token_t *tok = tokenize_input("cat << EOF", &mem);
    task_t *task = build_tasks(tok, &mem);

    cr_assert_not_null(task);
    cr_assert_str_eq(task->cmds->heredoc_delim, "EOF");
    free_all(&mem);
}

Test(redirections, pipe_with_redir)
{
    mem_t mem = {0};
    token_t *tok = tokenize_input("ls | wc -l > /tmp/out", &mem);
    task_t *task = build_tasks(tok, &mem);
    cmd_t *cmd;

    cr_assert_not_null(task);
    cr_assert_eq(task->cmd_count, 2);
    cmd = task->cmds;
    cr_assert_null(cmd->outfile);
    cmd = cmd->next;
    cr_assert_str_eq(cmd->outfile, "/tmp/out");
    cr_assert_eq(cmd->append, 0);
    free_all(&mem);
}
