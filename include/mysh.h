/*
** EPITECH PROJECT, 2026
** mysh.h
** File description:
** header mysh
*/

#ifndef MYSH_H
    #define MYSH_H
    #include <unistd.h>
    #include <stdio.h>
    #include <fcntl.h>
    #include <string.h>
    #include <sys/wait.h>
    #include <sys/stat.h>
    #include <errno.h>
    #include <signal.h>
    #include "xmalloc.h"
typedef struct env_s {
    char *env_var;
    struct env_s *next;
} env_t;
typedef enum token_type {
    WORD,
    PIPE,
    SEMICOLON,
    REDIR_IN,
    REDIR_OUT,
    APPEND,
    HERODOC
} tk_type_t;
typedef struct token {
    tk_type_t type;
    char *value;
    struct token *next;
} token_t;
typedef struct cmd_s {
    char **args;
    char *infile;
    char *outfile;
    int append;
    char *herodoc_delim;
    struct cmd_s *next;
} cmd_t;
typedef struct task_s {
    cmd_t *cmds;
    int cmd_count;
    struct task_s *next;
} task_t;
typedef struct control_s {
    env_t *env;
    mem_t *mem;
    char **a_env;
} control_t;
typedef struct my_sh_s {
    char *input;
    char *username;
    char buf[1000];
    size_t size;
    token_t *tokens;
    task_t *tasks;
    pid_t pid;
    int r_value;
    char *prev_dir;
    char temp[90];
    int open_fd;
    int bk_fds[2];
    int r_value_2;
} my_sh_t;
int handle_error(int error_code);
int change_directory(char **cmd_line, env_t *env, char *prev_dir, mem_t *mem);
env_t *array_to_list(char **env, mem_t *mem);
void print_env(env_t *env, char **cmd_line);
void x_setenv(env_t **temp, char **cmd_line, mem_t *mem);
void x_unsetenv(env_t **temp, char **cmd_line);
void handle_signals(void);
void handle_signals_2(void);
void handle_signals_3(void);
char *get_path_version(char *full_path, mem_t *mem);
char *get_username(env_t *env, mem_t *mem);
char **list_to_array(env_t *env, mem_t *mem);
void display_msg(int sig, int status);
char *rm_exec_sign(char *s);
void add_to_history(char *cmd);
token_t *tokenize_input(char *input, mem_t *mem);
task_t *build_tasks(token_t *tokens, mem_t *mem);
int exec_builtin_3(my_sh_t *args, control_t *ctrl);
int my_sh(control_t *ctrl);
void apply_redirections(my_sh_t *args, char **env);
void restore_fds(my_sh_t *args);
void display_prompt(my_sh_t **args, control_t *ctrl);
#endif
