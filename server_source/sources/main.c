/*
** main.c for srv in /home/ledins_a/Dropbox/irc_lt_2017/server_source/sources
**
** Made by ledins
** Login   <ledins_a@epitech.net>
**
** Started on  Sun Apr 27 12:52:43 2014 ledins
** Last update Sun Apr 27 12:52:48 2014 ledins
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "server.h"

int main()
{
  t_server *server;

  server = NULL;
  if (server_init(&server) == FAIL)
    return (EXIT_FAILURE);
  if (network_init(server) == OK)
    {
  network_run(server);
  }
  network_close(server);
  server_free(server);
  return 0;
}
