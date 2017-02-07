/*
** xlib.h for xlib in /home/ledins_a/Dropbox/irc_lt_2017/server_source/includes
** 
** Made by ledins
** Login   <ledins_a@epitech.net>
** 
** Started on  Sun Apr 27 13:53:47 2014 ledins
** Last update Sun Apr 27 13:53:54 2014 ledins
*/

#include <stdlib.h>

#ifndef XLIB_H
#define XLIB_H

void * xmalloc(size_t size, int line, char *file);
int  xsocket(int line, char *file);
int xclose(int fd, int line, char *file);

#endif // XLIB_H
