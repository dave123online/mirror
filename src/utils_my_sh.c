/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** description
*/

#include "../include/mysh.h"
#include "../include/librog.h"
#include "../include/myconstants.h"
static void handle_in_redir(my_sh_t *args, char **env)
{
    if (args->tasks->cmds->infile) {
        args->bk_fds[0] = dup(STDIN_FILENO);
        args->open_fd = open(args->tasks->cmds->infile, O_RDONLY);
        if (args->open_fd == -1) {
            perror("open");
            return;
        }
        dup2(args->open_fd, STDIN_FILENO);
        close(args->open_fd);
    }
}

static void handle_out_redir(my_sh_t *args, char **env)
{
    if (args->tasks->cmds->outfile) {
        args->bk_fds[1] = dup(STDOUT_FILENO);
        args->open_fd = open(args->tasks->cmds->outfile, O_WRONLY | O_CREAT |
            (args->tasks->cmds->append ? O_APPEND : 0), 0644);
        if (args->open_fd == -1) {
            perror("open");
            return;
        }
        dup2(args->open_fd, STDOUT_FILENO);
        close(args->open_fd);
    }
}

void apply_redirections(my_sh_t *args, char **env)
{
    args->bk_fds[0] = -1;
    args->bk_fds[1] = -1;
    handle_in_redir(args, env);
    handle_out_redir(args, env);
}

void restore_fds(my_sh_t *args)
{
    if (args->bk_fds[0] != -1) {
        dup2(args->bk_fds[0], STDIN_FILENO);
        close(args->bk_fds[0]);
    }
    if (args->bk_fds[1] != -1) {
        dup2(args->bk_fds[1], STDOUT_FILENO);
        close(args->bk_fds[1]);
    }
}

void display_prompt(my_sh_t **args, control_t *ctrl)
{
    if (!getcwd((*args)->buf, 1000))
        handle_error(ERROR_GETCWD);
    if (isatty(0)) {
        my_printf("\033[1;34m|-[ %s ] \033[0m",
            get_username(ctrl->env, ctrl->mem));
        my_printf("%s\n|_", get_path_version((*args)->buf, ctrl->mem));
    }
    if (getline(&(*args)->input, &(*args)->size, stdin) == -1) {
        if (errno != ENOTTY)
            handle_error(ERROR_GETLINE);
        exit(0);
    }
}
