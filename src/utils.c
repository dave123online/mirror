/*
** EPITECH PROJECT, 2026
** utils.c
** File description:
** util functions
*/

#include "../include/librog.h"
#include "../include/myconstants.h"
#include "../include/mysh.h"
#include "../include/xmalloc.h"
int handle_error(int error_code)
{
    if (error_code == ERROR_GETCWD)
        my_perror("%s: %s\n", "getcwd", strerror(errno));
    if (error_code == ERROR_GETLINE)
        my_perror("%s: %s\n", "getline", strerror(errno));
    if (error_code == ERROR_FORK)
        my_perror("%s: %s\n", "fork", strerror(errno));
    if (error_code == ERROR_EXECVE)
        my_perror("%s: %s\n", "execve", strerror(errno));
    my_perror("Call the dev for more explanations\n");
    my_perror("david.capo-chichi@epitech.eu\n");
    exit(84);
}

static env_t *create_first_node(char **env, mem_t *mem)
{
    env_t *node = xmalloc(sizeof(env_t), mem);

    node->env_var = xstrdup(env[0], mem);
    node->next = NULL;
    return node;
}

env_t *array_to_list(char **env, mem_t *mem)
{
    env_t *head = create_first_node(env, mem);
    env_t *curr = head;
    int i = 1;

    if (!env)
        return NULL;
    for (; env[i]; i++) {
        curr->next = xmalloc(sizeof(env_t), mem);
        curr = curr->next;
        curr->env_var = xstrdup(env[i], mem);
        curr->next = NULL;
    }
    return head;
}

char *get_path_version(char *full_path, mem_t *mem)
{
    int i = 0;
    int j = 1;
    char *buf;

    if (!my_strncmp("/home/", full_path, 6) && full_path[6] != '\0') {
        buf = xmalloc(my_strlen(full_path) + 1, mem);
        buf[0] = '~';
        for (i = 6; full_path[i] != '/' && full_path[i] != '\0'; i++);
        for (; full_path[i] != '\0'; i++) {
            buf[j] = full_path[i];
            j++;
        }
        buf[j] = '\0';
        return buf;
    }
    return full_path;
}
