/*
** xclose.c for ledins in /home/ledins_a/Dropbox/irc_lt_2017/server_source/sources/xlib
** 
** Made by ledins
** Login   <ledins_a@epitech.net>
** 
** Started on  Sun Apr 27 12:46:18 2014 ledins
** Last update Sun Apr 27 12:46:19 2014 ledins
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int xclose(int fd, int line, char *file)
{
  int retval;

  retval = close(fd);
  if (retval == -1)
    {
      fprintf(stderr, "error : close failed line %d in file %s\t", line, file);
      perror("");
    }
  return (0);
}
