/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** description
*/

#include "../include/mysh.h"
#include "../include/librog.h"
#include "../include/tokenize.h"
static void append_tok(tokenize_t *args, tk_type_t type,
    char *value, mem_t *mem)
{
    token_t *tok;

    tok = xmalloc(sizeof(token_t), mem);
    if (!tok) {
        my_perror("malloc failed\n");
        exit(84);
    }
    tok->type = type;
    tok->value = (value) ? xstrdup(value, mem) : NULL;
    tok->next = NULL;
    if (!(args->head)) {
        (args->head) = tok;
        (args->cur_tok) = tok;
        return;
    }
    (args->cur_tok)->next = tok;
    args->cur_tok = tok;
}

static void init_tokenization(tokenize_t *args)
{
    args->head = NULL;
    args->cur_tok = NULL;
    args->idx = 0;
    args->i = 0;
}

static void flush_word(tokenize_t *args, mem_t *mem)
{
    if (args->idx > 0) {
        args->word[args->idx] = '\0';
        append_tok(args, WORD, args->word, mem);
        args->idx = 0;
    }
}

static int sub_tokenize_input_3(tokenize_t *args, char *input, mem_t *mem)
{
    if (args->cur == '|' && input[args->i + 1] == '|') {
        flush_word(args, mem);
        my_perror("syntax error near unexpected token `||'\n");
        return -1;
    }
    if (args->cur == '|') {
        flush_word(args, mem);
        append_tok(args, PIPE, NULL, mem);
        args->i++;
        return 1;
    }
    if (args->cur == '<' && input[args->i + 1] == '<') {
        flush_word(args, mem);
        append_tok(args, HEREDOC, NULL, mem);
        args->i += 2;
        return 1;
    }
    return 0;
}

static int sub_tokenize_input_2(tokenize_t *args, char *input, mem_t *mem)
{
    if (args->cur == '<') {
        flush_word(args, mem);
        append_tok(args, REDIR_IN, NULL, mem);
        args->i++;
        return 1;
    }
    if (args->cur == ' ') {
        if (args->idx > 0) {
            args->word[args->idx] = '\0';
            append_tok(args, WORD, args->word, mem);
            args->idx = 0;
        }
        args->i++;
        return 1;
    }
    return 0;
}

static int sub_tokenize_input(tokenize_t *args, char *input, mem_t *mem)
{
    if (args->cur == ';') {
        flush_word(args, mem);
        append_tok(args, SEMICOLON, NULL, mem);
        args->i++;
        return 1;
    }
    if (args->cur == '>' && input[args->i + 1] == '>') {
        flush_word(args, mem);
        append_tok(args, APPEND, NULL, mem);
        args->i += 2;
        return 1;
    }
    if (args->cur == '>') {
        flush_word(args, mem);
        append_tok(args, REDIR_OUT, NULL, mem);
        args->i++;
        return 1;
    }
    return 0;
}

static int check(char *input, mem_t *mem, tokenize_t *args)
{
    int r;

    if (sub_tokenize_input(args, input, mem) == 1)
        return 1;
    r = sub_tokenize_input_3(args, input, mem);
    if (r != 0)
        return r;
    if (sub_tokenize_input_2(args, input, mem))
        return 1;
    return 0;
}

token_t *tokenize_input(char *input, mem_t *mem)
{
    tokenize_t args = {0};
    int r;

    init_tokenization(&args);
    while (input[args.i]) {
        args.cur = input[args.i];
        r = check(input, mem, &args);
        if (r == -1)
            return NULL;
        if (r == 1)
            continue;
        args.word[args.idx] = args.cur;
        args.idx++;
        args.i++;
    }
    if (args.idx > 0) {
        args.word[args.idx] = '\0';
        append_tok(&args, WORD, args.word, mem);
    }
    return args.head;
}
