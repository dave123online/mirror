/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** description
*/

#include "../include/mysh.h"
#include "../include/librog.h"
void add_to_history(char *cmd)
{
    int fd = open(".history", O_WRONLY | O_APPEND | O_CREAT, 0644);

    if (fd == -1)
        return;
    write(fd, cmd, my_strlen(cmd));
    close(fd);
}

void display_history(void)
{
    int fd = open(".history", O_RDONLY);
    struct stat data;
    char *buf;
    ssize_t len;
    int val;

    val = stat(".history", &data);
    if (fd == -1 || val == -1)
        return;
    buf = malloc(sizeof(data.st_size));
    if (!buf) {
        close(fd);
        return;
    }
    len = (ssize_t) data.st_size;
    if (read(fd, buf, len) > 0)
        my_printf("%s", buf);
    close(fd);
}

int exec_builtin_3(my_sh_t *args, control_t *ctrl)
{
    if (!my_strcmp(args->tasks->cmds->args[0], "unsetenv")) {
        x_unsetenv(&ctrl->env, args->tasks->cmds->args);
        return 1;
    }
    if (!my_strcmp(args->tasks->cmds->args[0], "history")) {
        display_history();
        return 1;
    }
    return 0;
}
