/*
** EPITECH PROJECT, 2025
** my.h
** File description:
** header of the project
*/

#include <stdlib.h>
#ifndef MY_H
    #define MY_H
typedef struct adress_store {
    void *ptr;
    struct address_store *next;
} add_malloc_t;
typedef struct memory_control_s {
    add_malloc_t *head;
} mem_t;
void *xmalloc(ssize_t size, mem_t *h);
char *xstrdup(char *str, mem_t *h);
void free_all(mem_t *h);
void free_only_curr(void *ptr, mem_t *hd);
#endif /* MY_H */
