/*
** part.c for srv in /home/ledins_a/Dropbox/irc_lt_2017/server_source/sources/actions
** 
** Made by ledins
** Login   <ledins_a@epitech.net>
** 
** Started on  Sun Apr 27 13:44:30 2014 ledins
** Last update Sun Apr 27 13:46:31 2014 ledins
*/

#include <stdio.h>
#include <strings.h>
#include <string.h>
#include "server.h"

void quit_channel(t_server *srv, t_client **cli_raw)
{
  t_client *l;
  t_client *clone;

  clone = clone_client(*cli_raw);
  clone->next = NULL;
  clone->channel = NULL;
  if (srv->clients)
    {
      l = srv->clients;
      while (l && l->next)
	l = l->next;
      l->next = clone;
    }
  else
    srv->clients = clone;
  client_delete_node_chan((*cli_raw)->channel, *cli_raw);
}

void action_quit_channel(t_server *srv, t_client **cli_raw, char *b, int t)
{
  t_client *cli;

  (void)b;
  (void)t;
  cli = *cli_raw;
  if (!cli->channel)
    {
      send(cli->socket, "\02server:  you haven't joined a channel", 38, 0);
      return;
    }
  send(cli->socket, "\02server:  you have quit the channel", 35, 0);
  quit_channel(srv, cli_raw);
  cli_raw = NULL;
}
