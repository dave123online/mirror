/*
** EPITECH PROJECT, 2025
** my.h
** File description:
** my.h
*/

#ifndef LIBROG_H
    #define LIBROG_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <stdarg.h>
    #include <fcntl.h>
    #include "../my_secured_malloc/include/xmalloc.h"
int my_strlen(char *str);
int my_putchar(char c);
int my_put_nbr(int nb);
int my_atoi(char *str);
int my_base_convert(int nb, char *digits);
int my_pow(int x, int y);
int my_put_floats(double nb);
int my_put_g(double nb);
int maj_g_case(double nb);
long long my_put_ints(long long nb);
int *handle_n_case(int count);
int y_put_floats(double nb);
int my_put_ptr(void *ptr);
void my_put_sci_e(double nb);
void maj_e_case(double nb);
int my_putstr(char const *str);
int skip_character(char *s, char u, char v, int i);
char *my_revstr(char *str);
int my_strcmp(char *str1, char *str2);
int my_strncmp(char *s1, char *s2, int n);
int is_digit(char c);
char *my_strdup(char *c);
char **split_string(char *s, char c, mem_t *mem);
int my_strcat(char **buf, char *s1, char *s2);
char *delete_newline(char *s);
typedef const char *restrict ccr_t;
int my_printf(ccr_t format, ...);
int print_sub1(ccr_t format, int i, va_list args);
int print_sub2(ccr_t format, int i, va_list args);
int print_sub3(ccr_t format, int i, va_list args);
int print_sub4(ccr_t format, int i, va_list args);
int print_sub4(ccr_t format, int i, va_list args);
int my_perror(ccr_t format, ...);
int file_exist(char *filepath);
typedef struct split_string_variables {
    char buf[90];
    int i;
    int j;
    int idx;
    char **spl;
    mem_t *mem;
} spl_str_t;

#endif /* LIBROG_H */
