##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## makefile for the autograder
##

CC = clang

NAME = librog.a

SRC = delete_newline.c my_put_floats.c\
    file_exist.c my_put_nbr.c\
    my_atoi.c my_put_ptr.c\
    maj_e_case.c my_put_scie.c\
    my_base_convert.c my_putstr.c\
    my_getnbr.c my_revstr.c print_sub.c\
    my_isdigit.c my_strcat.c\
    my_perror.c my_strcmp.c skip_character.c\
    my_pow.c my_strdup.c split_string.c\
    my_printf.c my_strlen.c\
    my_putchar.c my_strncmp.c\

all:
	clang -c $(SRC)
	ar -rc $(NAME) *.o
clean:
	rm -f *.o || true
	rm -f *.gcda || true
	rm -f *.gcno || true
fclean: clean
	rm -f $(NAME) || true
	rm -f ../$(NAME) || true

re: fclean all
