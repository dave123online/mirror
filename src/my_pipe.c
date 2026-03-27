/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** description
*/

#include <unistd.h>
#include <sys/wait.h>
#include "../include/mysh.h"
#include "../include/librog.h"
#include "../include/pipe.h"
static void helper_child_exec(pipe_t *v, my_sh_t *args, control_t *ctrl)
{
    if (v->prev_fd != -1) {
        dup2(v->prev_fd, STDIN_FILENO);
        close(v->prev_fd);
    }
    if (v->cmd->next) {
        dup2(v->fd[1], STDOUT_FILENO);
        close(v->fd[0]);
        close(v->fd[1]);
    }
    if (v->cmd->infile) {
        args->open_fd = open(v->cmd->infile, O_RDONLY);
        dup2(args->open_fd, STDIN_FILENO);
        close(args->open_fd);
    }
    if (v->cmd->outfile) {
        args->open_fd = open(v->cmd->outfile, O_WRONLY | O_CREAT |
            (v->cmd->append ? O_APPEND : 0), 0644);
        dup2(args->open_fd, STDOUT_FILENO);
        close(args->open_fd);
    }
}

static void child_exec(pipe_t *v, my_sh_t *args, control_t *ctrl)
{
    handle_signals();
    handle_signals_2();
    helper_child_exec(v, args, ctrl);
    if (!parse_path(v->cmd->args, ctrl)) {
        my_perror("%s: Command not found.\n", v->cmd->args[0]);
        free_all(ctrl->mem);
        exit(84);
    }
    exit(0);
}

static void end_sub_pipe(pipe_t *v)
{
    if (v->prev_fd != -1)
        close(v->prev_fd);
    if (v->cmd->next) {
        close(v->fd[1]);
        v->prev_fd = v->fd[0];
    }
}

static int sub_pipe(pipe_t *v, my_sh_t *args, control_t *ctrl)
{
    if (v->cmd->next && pipe(v->fd) == -1) {
        perror("pipe");
        return 1;
    }
    v->pid = fork();
    if (v->pid == -1) {
        perror("fork");
        return 1;
    }
    if (v->pid == 0)
        child_exec(v, args, ctrl);
    v->pids[v->i] = v->pid;
    v->i++;
    end_sub_pipe(v);
    v->cmd = v->cmd->next;
    return 0;
}

static void init_pipe(pipe_t *pipe, task_t **task)
{
    pipe->cmd = (*task)->cmds;
    pipe->prev_fd = -1;
    pipe->n = (*task)->cmd_count;
    pipe->pids = malloc(sizeof(pid_t) * pipe->n);
    pipe->i = 0;
}

int my_pipe(task_t *task, my_sh_t *args, control_t *ctrl)
{
    pipe_t v = {0};

    init_pipe(&v, &task);
    while (v.cmd) {
        if (sub_pipe(&v, args, ctrl))
            return 1;
    }
    for (int j = 0; j < v.i; j++)
        waitpid(v.pids[j], NULL, 0);
    return 0;
}
