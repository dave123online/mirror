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

int search_in_path(char **cmd_array, char *path, mem_t *mem, char **env)
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

int exec_builtin(my_sh_t *args, control_t *ctrl)
{
    add_to_history(args->input);
    if (!my_strcmp(args->input, "\n"))
        return 1;
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

int my_sh(control_t *ctrl)
{
    my_sh_t args;
    int r;

    init_args(&args, ctrl);
    while (1) {
        display_prompt(&args, ctrl);
        args.tokens = tokenize_input(delete_newline(args.input), ctrl->mem);
        if (!args.tokens)
            continue;
        args.tasks = build_tasks(args.tokens, ctrl->mem);
        if (!args.tasks)
            continue;
        r = exec_task(args.tasks, &args, ctrl);
        if (r == 1)
            continue;
        if (r == 2)
            break;
    }
    free(args.input);
    return 0;
}
