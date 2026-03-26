/*
** EPITECH PROJECT, 2026
** mysh_2.c
** File description:
** description
*/

#include "../include/mysh.h"
#include "../include/librog.h"
#include "../include/myconstants.h"
void handle_signals(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGABRT, SIG_DFL);
    signal(SIGALRM, SIG_DFL);
    signal(SIGFPE, SIG_DFL);
    signal(SIGHUP, SIG_DFL);
    signal(SIGILL, SIG_DFL);
    signal(SIGPIPE, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    signal(SIGTERM, SIG_DFL);
    signal(SIGCHLD, SIG_DFL);
    signal(SIGCONT, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
    signal(SIGBUS, SIG_DFL);
    signal(SIGPOLL, SIG_DFL);
    signal(SIGPROF, SIG_DFL);
    signal(SIGSYS, SIG_DFL);
    signal(SIGTRAP, SIG_DFL);
}

void handle_signals_2(void)
{
    signal(SIGURG, SIG_DFL);
    signal(SIGVTALRM, SIG_DFL);
    signal(SIGXCPU, SIG_DFL);
    signal(SIGXFSZ, SIG_DFL);
}

char *get_username(env_t *env, mem_t *mem)
{
    env_t **temp = &env;

    for (; *temp; temp = &((*temp)->next)) {
        if (!my_strncmp("LOGNAME", (*temp)->env_var, 7)) {
            return (split_string((*temp)->env_var, '=', mem)[1]);
        }
    }
    return NULL;
}

char **list_to_array(env_t *env, mem_t *mem)
{
    env_t **temp = &env;
    int i = 0;
    int j = 0;
    char **arr;

    for (; *temp; temp = &((*temp)->next))
        i++;
    arr = xmalloc((sizeof(char *) * i) + 1, mem);
    temp = &env;
    for (; *temp; temp = &((*temp)->next)) {
        arr[j] = (*temp)->env_var;
        j++;
    }
    arr[j] = NULL;
    return arr;
}

static void display_msg_2(int sig, int status)
{
    switch (sig) {
        case SIGBUS:
            MSG("Bus error\n");
            break;
        case SIGILL:
            MSG("Illegal instruction\n");
            break;
        case SIGABRT:
            MSG("Aborted\n");
            break;
        default:
            break;
    }
}

void display_msg(int sig, int status)
{
    switch (sig) {
        case SIGSEGV:
            if (WCOREDUMP(status))
                MSG("Segmentation fault (core dumped)\n");
            else
                MSG("Segmentation fault\n");
            break;
        case SIGFPE:
            MSG("Floating exception\n");
            break;
        case SIGQUIT:
            if (WCOREDUMP(status))
                MSG("Quit (core dumped)\n");
            else
                MSG("Quit\n");
            break;
    }
    return display_msg_2(sig, status);
}
