/*
** EPITECH PROJECT, 2026
** change_directory.c
** File description:
** description
*/

#include "../include/librog.h"
#include "../include/xmalloc.h"
#include "../include/mysh.h"
char *get_home(env_t *env, mem_t *mem)
{
    env_t **temp = &env;


    
    for (; *temp; temp = &(*temp)->next) {
        if (!my_strncmp("HOME", (*temp)->env_var, 4)) {
            return (split_string((*temp)->env_var, '=', mem)[1]);
        }
    }
    return NULL;
}

static int sub_cd(char **cmd_line, env_t *env, char *prev_dir)
{
    if (!cmd_line || !env)
        return 84;
    if (cmd_line[2]) {
        my_perror("cd: too many arguments.\n");
        return 84;
    }
    return 0;
}

int change_directory(char **cmd_line, env_t *env, char *prev_dir, mem_t *mem)
{
    char *home_path = NULL;

    if (sub_cd(cmd_line, env, prev_dir))
        return 84;
    if (!cmd_line[1] || !my_strcmp(cmd_line[1], "~")) {
        home_path = get_home(env, mem);
        if (home_path && !chdir(home_path))
            return 0;
    }
    if (!my_strcmp(cmd_line[1], "-")) {
        if (!chdir(prev_dir))
            return 0;
        return 84;
    }
    if (!chdir(cmd_line[1])) {
        return 0;
    }
    my_perror("cd: no such file or directory: %s\n.", cmd_line[1]);
    return 84;
}
