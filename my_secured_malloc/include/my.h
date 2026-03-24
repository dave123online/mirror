/*
** EPITECH PROJECT, 2025
** my.h
** File description:
** header of the project
*/

#ifndef MY_H
    #define MY_H
    #include <stdlib.h>
    #include <unistd.h>
    #include <signal.h>
typedef struct adress_store {
    void *ptr;
    struct adress_store *next;
} add_malloc_t;
int my_perror(const char *format, ...);
int my_strlen(char *s);
#endif
