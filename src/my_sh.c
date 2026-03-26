/*
** EPITECH PROJECT, 2026
** my_sh.c
** File description:
** main functionalities of the program
*/

#include "../include/librog.h"
#include "../include/xmalloc.h"
#include "../include/mysh.h"
#include "../include/myconstants.h"
#include <asm-generic/errno-base.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
static char *add_slash(char *s, mem_t *mem)
{
    int len = my_strlen(s);
    char *new = xmalloc(len + 2, mem);
    int i = 0;

    if (s == NULL)
        return NULL;
    for (; i < len; i++)
        new[i] = s[i];
    new[len] = '/';
    new[len + 1] = '\0';
    return new;
}

static char **get_path(env_t *env, mem_t *mem)
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

static int search_in_path(char **cmd_array, char *path, mem_t *mem, char **env)
{
    char *buf = xmalloc(255, mem);
    char *real_path = add_slash(path, mem);
    int r_value = 10;

    if (!path)
        return 0;
    my_strcat(&buf, real_path, cmd_array[0]);
    if (!access(buf, X_OK)) {
        r_value = execve(buf, cmd_array, env);
    }
    if (r_value == -1) {
        my_perror("%s: %s\n", cmd_array[0], strerror(errno));
        free_all(mem);
        exit(0);
    }
    return 84;
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

static int exec_builtin2(my_sh_t *args, control_t *ctrl)
{
    if (!my_strcmp(args->tasks->cmds->args[0], "cd")) {
        getcwd(args->temp, 90);
        if (!change_directory(args->tasks->cmds->args, ctrl->env,
                args->prev_dir, ctrl->mem))
            args->prev_dir = xstrdup(args->temp, ctrl->mem);
        return 1;
    }
    if (!my_strcmp(args->tasks->cmds->args[0], "env")
        || (!my_strcmp(args->tasks->cmds->args[0], "/usr/bin/env"))) {
        print_env(ctrl->env, args->tasks->cmds->args);
        return 1;
    }
    if (!my_strcmp(args->tasks->cmds->args[0], "setenv")) {
        x_setenv(&ctrl->env, args->tasks->cmds->args, ctrl->mem);
        return 1;
    }
    return (exec_builtin_3(args, ctrl) != 0);
}

static int exec_builtin(my_sh_t *args, control_t *ctrl)
{
    display_prompt(&args, ctrl);
    add_to_history(args->input);
    if (!my_strcmp(args->input, "\n"))
        return 1;
    args->tokens = tokenize_input(delete_newline(args->input), ctrl->mem);
    args->tasks = build_tasks(args->tokens, ctrl->mem);
    apply_redirections(args, ctrl->a_env);
    if (!my_strcmp(args->tasks->cmds->args[0], "exit"))
        return 2;
    return (exec_builtin2(args, ctrl) != 0);
}

static void init_args(my_sh_t *args, control_t *ctrl)
{
    args->input = NULL;
    args->username = NULL;
    args->size = 90;
    args->pid = -999;
    args->prev_dir = xmalloc(90, ctrl->mem);
    if (!args->prev_dir)
        exit(84);
    args->r_value = -1;
    getcwd(args->prev_dir, args->size);
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

int my_sh(control_t *ctrl)
{
    my_sh_t args;
    int val;

    init_args(&args, ctrl);
    while (1) {
        args.r_value = exec_builtin(&args, ctrl);
        val = sub_sh(&args);
        if (val == 1) {
            restore_fds(&args);
            continue;
        }
        if (val == 2) {
            restore_fds(&args);
            my_printf("exit\n");
            break;
        }
        run_command(&args, ctrl);
    }
    free(args.input);
    return 0;
}
