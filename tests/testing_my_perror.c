/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** description
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/librog.h"
Test(my_perror, writing_at_stderr, .init=cr_redirect_stderr)
{
    my_perror("test");
    cr_assert_stderr_eq_str("test");
}
