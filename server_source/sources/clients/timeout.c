/*
** timeout.c for srv in /home/ledins_a/rendu/PSU_2013_myirc/server_source/sources/clients
**
** Made by ledins
** Login   <ledins_a@epitech.net>
**
** Started on  Sun Apr 27 19:54:23 2014 ledins
** Last update Sun Apr 27 19:54:29 2014 ledins
*/

#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "server.h"

t_client * check_timeout(t_server *srv, t_client *client)
{
  time_t now;
  time_t last_recv;
  time_t diff;
  bool e;

  now = time(NULL);
  last_recv = client->last_recv;
  diff = now - last_recv;
  if (diff > 15)
    {
      send(client->socket, "\02timeout ! you seem inactive", 28, 0);
      return (client_disconnect(srv, client, &e));
    }
  return (client);
}

void function_timeout(t_server *srv)
{
  t_client *cli;
  t_channel *chan;

  cli = srv->clients;
  while (cli)
    {
      cli = check_timeout(srv, cli);
      if (cli)
        cli = cli->next;
    }
  chan = srv->channel;
  while (chan)
    {
      cli = chan->client;
      while (cli)
	{
	  cli = check_timeout(srv, cli);
	  cli = cli->next;
	}
      chan = chan->next;
    }
}
