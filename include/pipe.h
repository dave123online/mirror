/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** description
*/

#ifndef PIPE_H_
    #define PIPE_H_
    #include "mysh.h"
typedef struct pipe_s {
    cmd_t *cmd;
    int prev_fd;
    int fd[2];
    pid_t pid;
    int n;
    pid_t *pids;
    int i;
} pipe_t;
#endif /* PIPE_H_ */
