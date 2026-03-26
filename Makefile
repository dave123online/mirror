##
## EPITECH PROJECT, 2025
## makefile
## File description:
## makefile to build setting_up
##

NAME = mysh

SRC = src/change_directory.c my_secured_malloc/manage_memory.c\
    src/main.c src/manip_env.c src/my_sh_2.c src/my_sh.c\
    src/utils.c src/my_sh_3.c src/build_tasks.c src/utils_build_jobs.c \
    src/parse_input.c src/utils_my_sh.c

CC = epiclang

FLAGS = -g -W -Wall -Wextra -Wno-unused-parameter -Wno-incompatible-pointer-types

LPATH = ./librog/librog.a

TEST_FILES = src/build_tasks.c src/parse_input.c src/utils_build_jobs.c\
	my_secured_malloc/manage_memory.c tests/*.c

all:
	cd librog && make && cd ..
	$(CC) -o $(NAME) $(SRC) $(FLAGS) $(LPATH)|| true
	cd librog && make fclean && cd ..

clean:
	cleaner || true
	rm -f unit_tests

fclean: clean
	rm -f $(NAME) || true

re: fclean all

unit_tests:
	cd librog && make && cd ..
	$(CC) -o unit_tests $(TEST_FILES) $(LPATH) -lcriterion --coverage
	cd librog && make fclean && cd ..

tests_run: unit_tests
	./unit_tests
