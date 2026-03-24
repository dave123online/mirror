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
void *xmalloc(ssize_t size);
char *xstrdup(char *str);
void free_all(void);
#endif /* MY_H */
