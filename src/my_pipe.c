/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** description
*/
#include <unistd.h>
#include <sys/wait.h>
#include "../include/mysh.h"
static void main_part_2(int fd[2], char **cmd2,
    char **env, pid_t pid1)
{
    pid_t pid2;

    pid2 = fork();
    if (pid2 == 0) {
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        execve(cmd2[0], cmd2, env);
    }
    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

int my_pipe(cmd_t *cmd1, cmd_t *cmd2, char **env)
{
    int fd[2];
    pid_t pid1;

    pipe(fd);
    pid1 = fork();
    if (pid1 == 0) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execve(cmd1->args[0], cmd1->args, env);
    }
    main_part_2(fd, cmd2, env, pid1);
    return 0;
}
