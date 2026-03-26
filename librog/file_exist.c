/*
** EPITECH PROJECT, 2026
** file_exist.c
** File description:
** description
*/

#include "librog.h"
int file_exist(char *filepath)
{
    /*int fd = open(filepath, O_RDONLY);

    if (fd >= 0) {
        close(fd);
        return 1;
    }*/
    return access(filepath, F_OK);
}
