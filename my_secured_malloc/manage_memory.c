/*
** EPITECH PROJECT, 2025
** manage_memory
** File description:
** a fantastic tool to avoid memory leak
*/

#include "include/xmalloc.h"
#include "../librog/librog.h"
static int print_error(void *ptr)
{
    if (!ptr) {
        my_perror("malloc error");
        return 1;
    }
    return 0;
}

void *xmalloc(ssize_t size, mem_t *h)
{
    add_malloc_t **head = &(h->head);
    add_malloc_t *node = NULL;
    void *ptr = malloc(size);

    if (print_error(ptr))
        return NULL;
    node = malloc(sizeof(add_malloc_t));
    if (print_error(node))
        return NULL;
    node->ptr = ptr;
    node->next = *head;
    *head = node;
    return ptr;
}

char *xstrdup(char *str, mem_t *h)
{
    char *copy = xmalloc(my_strlen(str) + 1, h);
    int i = 0;

    while (str[i] != '\0') {
        copy[i] = str[i];
        i++;
    }
    copy[i] = '\0';
    return copy;
}

void free_all(mem_t *hd)
{
    add_malloc_t **h = &(hd->head);
    add_malloc_t *head = *h;
    add_malloc_t *temp;

    while (head) {
        temp = head->next;
        free(head->ptr);
        free(head);
        head = temp;
    }
    *h = NULL;
}

void free_only_curr(void *ptr, mem_t *hd)
{
    add_malloc_t **h = &(hd->head);
    add_malloc_t *temp;

    while (*h) {
        if ((*h)->ptr == ptr) {
            temp = (*h)->next;
            free((*h)->ptr);
            free(*h);
            *h = temp;
            return;
        }
    }
}
