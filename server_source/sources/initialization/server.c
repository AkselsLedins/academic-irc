/*
** server.c for srv in /home/ledins_a/Dropbox/irc_lt_2017/server_source/sources/initialization
**
** Made by ledins
** Login   <ledins_a@epitech.net>
**
** Started on  Sun Apr 27 12:53:09 2014 ledins
** Last update Sun Apr 27 12:53:34 2014 ledins
*/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "server.h"

static int server_init_actions(t_actions ** raw)
{
  return (create_n_actions(raw, MAX_ACTIONS));
}

int server_init(t_server ** raw)
{
  t_server *server;

  if ((server = malloc(sizeof(t_server))) == NULL)
    return (FAIL);

  memset( server, 0, sizeof (t_server) );

  server->actions = NULL;
  if (server_init_actions(&server->actions) == FAIL)
    return (FAIL);
  server->clients = NULL;
  server->channel = NULL;
  *raw = server;
  return (OK);
}

void server_free(t_server *server)
{
  actions_free(server->actions);
  clients_free(server->clients);
  channels_free(server->channel);
  free(server->clients);
  server->clients = NULL;
  free(server->actions);
  server->actions = NULL;
  free(server->channel);
  server->channel = NULL;
  free(server);
  server = NULL;
}
