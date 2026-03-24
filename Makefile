##
## EPITECH PROJECT, 2025
## makefile
## File description:
## makefile to build setting_up
##

NAME = mysh

SRC = src/change_directory.c my_secured_malloc/manage_memory.c\
    src/main.c src/manip_env.c src/my_sh_2.c src/my_sh.c\
    src/utils.c src/my_sh_3.c

CC = epiclang

FLAGS = -g -W -Wall -Wextra -Wno-unused-parameter -Wno-incompatible-pointer-types

LPATH = ./librog/librog.a

all:
	cd librog && make && cd ..
	$(CC) -o $(NAME) $(SRC) $(FLAGS) $(LPATH)|| true
	cd librog && make fclean && cd ..

clean:
	cleaner || true

fclean: clean
	rm -f $(NAME) || true

re: fclean all
