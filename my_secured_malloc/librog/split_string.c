/*
** EPITECH PROJECT, 2026
** split_string
** File description:
** string to word array
*/

#include "librog.h"
#include "../my_secured_malloc/include/xmalloc.h"
static int count_words(char *s, char c)
{
    int i = 0;
    int count = 0;

    for (; s[i] != '\0'; i++) {
        if (s[i] == '\t' || s[i] == c)
            count++;
    }
    return count + 1;
}

static int skip_separators(char *s, int i, char c)
{
    while ((s[i] == '\t' || s[i] == c)
        && (s[i + 1] == '\t' || s[i + 1] == c || s[i + 1] == '\0'))
        i++;
    return i;
}

char **fill_last_idx(spl_str_t *args)
{
    args->buf[args->j] = '\0';
    args->spl[args->idx] = xstrdup(args->buf, args->mem);
    args->idx++;
    args->spl[args->idx] = NULL;
    args->spl[args->idx + 1] = NULL;
    args->spl[args->idx + 2] = NULL;
    return args->spl;
}

static void init_args(spl_str_t *args, char *s, char c, mem_t *mem)
{
    args->i = 0;
    args->j = 0;
    args->idx = 0;
    args->spl = xmalloc(sizeof(char *) * (count_words(s, c) + 3), mem);
    args->mem = mem;
}

static int fill_idx(spl_str_t *args, char *s, char c)
{
    if (s[args->i] == c || s[args->i] == '\t') {
        args->buf[args->j] = '\0';
        if (args->buf[0] == c || args->buf[0] == '\t') {
            args->j = 0;
            return 84;
        }
        args->spl[args->idx] = xstrdup(args->buf, args->mem);
        args->j = 0;
        args->i++;
        args->idx++;
        return 84;
    }
    return 0;
}

char **split_string(char *s, char c, mem_t *mem)
{
    spl_str_t args;

    init_args(&args, s, c, mem);
    for (; s[args.i] == '\t' || s[args.i] == c; args.i++);
    while (s[args.i] != '\0') {
        args.i = skip_separators(s, args.i, c);
        if (fill_idx(&args, s, c))
            continue;
        args.buf[args.j] = s[args.i];
        args.i++;
        args.j++;
    }
    return fill_last_idx(&args);
}
