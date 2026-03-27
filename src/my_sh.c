/*
** EPITECH PROJECT, 2026
** my_sh.c
** File description:
** main functionalities of the program
*/

#include "../include/librog.h"
#include "../include/xmalloc.h"
#include "../include/mysh.h"
#include <sys/wait.h>
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

static int exec_tasks(my_sh_t *args, control_t *ctrl)
{
    int r;
    task_t *cur = args->tasks;

    while (cur) {
        r = exec_task(cur, args, ctrl);
        if (r == 2)
            return 2;
        cur = cur->next;
    }
    return 0;
}

int my_sh(control_t *ctrl)
{
    my_sh_t args;

    init_args(&args, ctrl);
    while (1) {
        display_prompt(&args, ctrl);
        add_to_history(args.input);
        args.tokens = tokenize_input(delete_newline(args.input), ctrl->mem);
        if (!args.tokens)
            continue;
        args.tasks = build_tasks(args.tokens, ctrl->mem);
        if (!args.tasks || !args.tasks->cmds || !args.tasks->cmds->args)
            continue;
        if (exec_tasks(&args, ctrl) == 2) {
            my_printf("exit\n");
            break;
        }
    }
    free(args.input);
    return 0;
}
