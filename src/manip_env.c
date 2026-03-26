/*
** EPITECH PROJECT, 2026
** manip_env
** File description:
** description
*/

#include "../include/librog.h"
#include "../include/xmalloc.h"
#include "../include/mysh.h"
void print_env(env_t *env, char **cmd_line)
{
    env_t **temp = &env;

    if (!env)
        return;
    if (cmd_line && cmd_line[1]) {
        my_perror("env: '%s' : No such file or directory\n", cmd_line[1]);
        return;
    }
    for (; *temp; temp = &((*temp)->next))
        my_printf("%s\n", (*temp)->env_var);
    return;
}

static int sub_setenv(env_t *env, char **cmd_line)
{
    if (!cmd_line[1]) {
        print_env(env, NULL);
        return 1;
    }
    if ((cmd_line[1][0] <= 65 || cmd_line[1][0] >= 90)
        && (cmd_line[1][0] <= 97 || cmd_line[1][0] >= 122)
        && cmd_line[1][0] != '_') {
        my_perror("setenv: Variable name must begin with a letter\n");
        return 1;
    }
    if (cmd_line[3]) {
        my_perror("setenv: Too many arguments\n");
        return 1;
    }
    return 0;
}

void x_setenv(env_t **env, char **cmd_line, mem_t *mem)
{
    char *var = cmd_line[1];
    char *val = cmd_line[2];
    env_t **temp = env;
    char *new = xmalloc(my_strlen(var) + my_strlen(val) + 2, mem);

    if (sub_setenv(*env, cmd_line))
        return;
    my_strcat(&new, var, "=");
    if (val)
        my_strcat(&new, new, val);
    for (; *temp; temp = &((*temp)->next)) {
        if (!my_strncmp((*temp)->env_var, var, my_strlen(var))
            && (*temp)->env_var[my_strlen(var)] == '=') {
            (*temp)->env_var = new;
            return;
        }
    }
    *temp = xmalloc(sizeof(env_t), mem);
    (*temp)->env_var = new;
    (*temp)->next = NULL;
}

static int sub_x_unsetenv(env_t **temp, char **cmd_line, char *var)
{
    for (; *temp; temp = &((*temp)->next)) {
        if (!my_strncmp((*temp)->env_var, var, my_strlen(var))
            && (*temp)->env_var[my_strlen(var)] == '=') {
            *temp = (*temp)->next;
            return 1;
        }
    }
    return 0;
}

void x_unsetenv(env_t **env, char **cmd_line)
{
    char *var = NULL;
    int i = 0;

    if (!cmd_line[1]) {
        my_perror("unsetenv: Too few arguments\n");
        return;
    }
    for (i = 1; cmd_line[i]; i++) {
        var = cmd_line[i];
        if (!sub_x_unsetenv(env, cmd_line, var))
            continue;
    }
    return;
}
