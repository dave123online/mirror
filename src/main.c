/*
** EPITECH PROJECT, 2026
** main.c
** File description:
** entry point
*/

#include "../include/mysh.h"
#include "../include/xmalloc.h"
#include "../include/librog.h"
void handle_sigint(int signum)
{
    write(1, &"\033[33m\n|+> \033[0m", 15);
}

int main(int ac, char **av, char **env)
{
    control_t control;
    mem_t memory = {NULL};

    if (ac != 1)
        return 84;
    signal(SIGINT, handle_sigint);
    signal(SIGTERM, exit);
    errno = 0;
    control.mem = &memory;
    control.a_env = env;
    control.env = array_to_list(env, control.mem);
    if (!env || !control.env) {
        my_perror("no env was provided\n");
        exit(84);
    }
    my_sh(&control);
    free_all(control.mem);
    return 0;
}
