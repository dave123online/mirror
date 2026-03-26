/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** description
*/

#include <criterion/criterion.h>
#include "../include/mysh.h"

Test(build_tasks, simple_pipe)
{
    mem_t mem = {0};
    token_t *tok = tokenize_input("ls -l | wc -l", &mem);
    task_t *task = build_tasks(tok, &mem);
    cmd_t *cmd;

    cr_assert_not_null(task);
    cr_assert_eq(task->cmd_count, 2);
    cmd = task->cmds;
    cr_assert_not_null(cmd);
    cr_assert_str_eq(cmd->args[0], "ls");
    cr_assert_str_eq(cmd->args[1], "-l");
    cr_assert_null(cmd->args[2]);
    cmd = cmd->next;
    cr_assert_not_null(cmd);
    cr_assert_str_eq(cmd->args[0], "wc");
    cr_assert_str_eq(cmd->args[1], "-l");
    cr_assert_null(cmd->args[2]);
    cr_assert_null(task->next);
    free_all(&mem);
}

Test(build_tasks, semicolon_two_jobs)
{
    mem_t mem = {0};
    token_t *tok = tokenize_input("echo hi ; ls", &mem);
    task_t *task = build_tasks(tok, &mem);

    cr_assert_not_null(task);
    cr_assert_eq(task->cmd_count, 1);
    cr_assert_str_eq(task->cmds->args[0], "echo");
    cr_assert_str_eq(task->cmds->args[1], "hi");
    task = task->next;
    cr_assert_not_null(task);
    cr_assert_eq(task->cmd_count, 1);
    cr_assert_str_eq(task->cmds->args[0], "ls");
    cr_assert_null(task->next);
    free_all(&mem);
}

Test(build_tasks, redir_out)
{
    mem_t mem = {0};
    token_t *tok = tokenize_input("echo hi > out.txt", &mem);
    task_t *task = build_tasks(tok, &mem);
    cmd_t *cmd;

    cr_assert_not_null(task);
    cr_assert_eq(task->cmd_count, 1);
    cmd = task->cmds;
    cr_assert_str_eq(cmd->args[0], "echo");
    cr_assert_str_eq(cmd->args[1], "hi");
    cr_assert_str_eq(cmd->outfile, "out.txt");
    cr_assert_eq(cmd->append, 0);
    cr_assert_null(cmd->infile);
    free_all(&mem);
}

Test(build_tasks, append_and_pipe)
{
    mem_t mem = {0};
    token_t *tok = tokenize_input("ls | wc -c >> out.txt", &mem);
    task_t *task = build_tasks(tok, &mem);
    cmd_t *cmd;

    cr_assert_not_null(task);
    cr_assert_eq(task->cmd_count, 2);
    cmd = task->cmds;
    cr_assert_str_eq(cmd->args[0], "ls");
    cr_assert_null(cmd->outfile);
    cmd = cmd->next;
    cr_assert_str_eq(cmd->args[0], "wc");
    cr_assert_str_eq(cmd->outfile, "out.txt");
    cr_assert_eq(cmd->append, 1);
    free_all(&mem);
}
