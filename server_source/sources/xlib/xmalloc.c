/*
** xmalloc.c for srv in /home/ledins_a/Dropbox/irc_lt_2017/server_source/sources/xlib
** 
** Made by ledins
** Login   <ledins_a@epitech.net>
** 
** Started on  Sun Apr 27 12:46:45 2014 ledins
** Last update Sun Apr 27 12:46:49 2014 ledins
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void * xmalloc(size_t size, int line, char *file)
{
void * ptr;

ptr = malloc(size);
if (!ptr)
  fprintf(stderr, "error : malloc failed line %d in %s\n", line, file);
return (ptr);
}
