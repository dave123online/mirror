cd librog && make && cd ..
clang test.c src/parse_input.c src/build_tasks.c \
      my_secured_malloc/*.c ./librog/librog.a
cd librog && make fclean && cd ..
