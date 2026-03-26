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

void display_prompt(my_sh_t *args, control_t *ctrl)
{
    if (!getcwd(args->buf, 1000))
        handle_error(ERROR_GETCWD);
    if (isatty(0)) {
        my_printf("\033[1;34m|-[ %s ] \033[0m",
            get_username(ctrl->env, ctrl->mem));
        my_printf("%s\n|_", get_path_version(args->buf, ctrl->mem));
    }
    if (getline(&args->input, &args->size, stdin) == -1) {
        if (errno != ENOTTY)
            handle_error(ERROR_GETLINE);
        exit(0);
    }
}

static int parse_path(char **cmd_array, control_t *ctrl)
{
    int i = 0;
    char **paths = get_path(ctrl->env, ctrl->mem);

    if (!paths || !paths[0])
        return 0;
    while (paths[i] != NULL) {
        if (!search_in_path(cmd_array, paths[i], ctrl->mem, ctrl->a_env))
            return 1;
        i++;
    }
    return 0;
}

static void run_command(my_sh_t *args, control_t *ctrl)
{
    args->r_value_2 = 10;
    handle_signals();
    handle_signals_2();
    if (((args->tasks->cmds->args[0][0] == '.' ||
                args->tasks->cmds->args[0][1] == '/')
            || (args->tasks->cmds->args[0][0] == '/'))
        && !access(args->tasks->cmds->args[0], X_OK)) {
        args->r_value_2 = execve(args->tasks->cmds->args[0],
            args->tasks->cmds->args, ctrl->a_env);
    }
    if (args->r_value_2 == -1) {
        my_perror("%s: %s\n", args->tasks->cmds->args[0], strerror(errno));
        exit(0);
    }
    if (!parse_path(args->tasks->cmds->args, ctrl)) {
        my_perror("%s: Command not found.\n", delete_newline(args->input));
        free_all(ctrl->mem);
        free(args->input);
        exit(0);
    }
}

static int sub_sh(my_sh_t *args)
{
    int status = -1;
    int sig = -1;

    if (args->r_value == 1)
        return 1;
    if (args->r_value == 2)
        return 2;
    args->pid = fork();
    if (args->pid == -1)
        handle_error(ERROR_FORK);
    if (args->pid > 0) {
        wait(&status);
        if (WIFSIGNALED(status))
            sig = WTERMSIG(status);
        display_msg(sig, status);
        return 1;
    }
    return 0;
}

int exec_cmd(my_sh_t *args, control_t *ctrl)
{
    int val;

    args->r_value = exec_builtin(args, ctrl);
    val = sub_sh(args);
    if (val == 1) {
        restore_fds(args);
        return 1;
    }
    if (val == 2) {
        restore_fds(args);
        my_printf("exit\n");
        return 2;
    }
    run_command(args, ctrl);
    return 0;
}

int exec_task(task_t *task, my_sh_t *args, control_t *ctrl)
{
    if (task->cmd_count == 1) {
        return exec_cmd(args, ctrl);
    }
    /*while (task->cmds != NULL) {
        my_
    }*/
}
