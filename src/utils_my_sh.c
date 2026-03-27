/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** description
*/

#include "../include/mysh.h"
#include "../include/librog.h"
#include "../include/myconstants.h"
char **get_path(env_t *env, mem_t *mem)
{
    env_t **temp = &env;

    if (!env)
        return NULL;
    for (; *temp; temp = &(*temp)->next) {
        if (!my_strncmp((*temp)->env_var, "PATH", 4)
            && (*temp)->env_var[my_strlen("PATH")] == '=') {
            return (split_string(&((*temp)->env_var[5]), ':', mem));
        }
    }
    return NULL;
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

int parse_path(char **cmd_array, control_t *ctrl)
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

static int helper_sub_sh(my_sh_t *args, int *status, int *sig)
{
    args->pid = fork();
    if (args->pid == -1)
        handle_error(ERROR_FORK);
    if (args->pid > 0) {
        wait(status);
        if (WIFSIGNALED(*status))
            *sig = WTERMSIG(*status);
        display_msg(*sig, *status);
        return 1;
    }
    return 0;
}

static int sub_sh(my_sh_t *args, int should_fork)
{
    int status = -1;
    int sig = -1;

    if (args->r_value == 1)
        return 1;
    if (args->r_value == 2)
        return 2;
    if (should_fork) {
        if (helper_sub_sh(args, &status, &sig))
            return 1;
    }
    return 0;
}

static int exec_cmd(my_sh_t *args, control_t *ctrl, int should_fork)
{
    int val;

    apply_redirections(args, ctrl->a_env);
    args->r_value = exec_builtin(args, ctrl);
    val = sub_sh(args, should_fork);
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
    if (task->cmd_count == 1)
        return exec_cmd(args, ctrl, 1);
    return my_pipe(task, args, ctrl);
}
