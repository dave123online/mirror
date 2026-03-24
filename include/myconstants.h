/*
** EPITECH PROJECT, 2026
** myconstants.h
** File description:
** constants definition
*/

#ifndef MYCONSTANTS_H
    #define MYCONSTANTS_H
    #define ERROR_GETCWD 30
    #define ERROR_GETLINE 31
    #define ERROR_FORK 32
    #define ERROR_EXECVE 33
    #define MSG(s) write(2, s, sizeof(s) - 1)
#endif /* MYCONSTANTS */
