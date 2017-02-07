/*
** xsocket.c for srv in /home/ledins_a/Dropbox/irc_lt_2017/server_source/sources/xlib
** 
** Made by ledins
** Login   <ledins_a@epitech.net>
** 
** Started on  Sun Apr 27 12:46:36 2014 ledins
** Last update Sun Apr 27 12:47:11 2014 ledins
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>

int xsocket(int line, char *file)
{
  int msocket;

  msocket = socket(AF_INET, SOCK_STREAM, 0);
  if (msocket == 0)
    {
      fprintf(stderr, "error : socket failed line %d : %s\t", line, file);
      perror("");
    }
  return (msocket);
}
