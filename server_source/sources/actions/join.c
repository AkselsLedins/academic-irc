/*
** join.c for srv in /home/ledins_a/Dropbox/irc_lt_2017/server_source/sources/actions
**
** Made by ledins
** Login   <ledins_a@epitech.net>
**
** Started on  Sun Apr 27 13:43:49 2014 ledins
** Last update Sun Apr 27 18:45:21 2014 ledins
*/

#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <time.h>
#include "server.h"

static t_channel * chan_exists(t_channel *chan, char arg[])
{
  size_t chan_name_size;
  size_t arg_size;
  size_t compare;

  arg_size = strlen(arg);
  while (chan)
    {
      chan_name_size = strlen(chan->name);
      compare = (chan_name_size < arg_size) ? arg_size : chan_name_size;
      compare = (compare >= MAX_CHANNEL_NAME) ? MAX_CHANNEL_NAME : compare;
      if (strncmp(chan->name, arg, compare) == 0)
	return (chan);
      chan = chan->next;
    }
  return (NULL);
}

static int add_client_to_chan(t_channel *chan, t_client *client)
{
  t_client *list;

  list = chan->client;
  if (list)
    {
      while (list && list->next)
	list = list->next;
      list->next = client;
    }
  else
    chan->client = client;
  return (OK);
}

static int join_chan(t_server *srv, t_channel *chan, t_client *cli)
{
  t_client *clone;

  send(cli->socket, "\02server:  you have joined the chan", 34, 0);
  clone = clone_client(cli);
  clone->channel = chan;
  add_client_to_chan(chan, clone);
  client_delete_node(srv, srv->clients, cli);
  return (OK);
}

static void action_join_else(t_server *srv, t_client **cli_raw, char *name)
{
  t_client *cli;
  t_channel *to_join;
  t_channel *chan;

  cli = *cli_raw;
  channel_create(srv, name);
  chan = srv->channel;
  to_join = chan_exists(chan, name);
  send(cli->socket, "\02server:  you have created the chan", 35, 0);
  join_chan(srv, to_join, cli);
}

void action_join(t_server *srv, t_client **cli_raw, char *buf, int tosend)
{
  t_channel *chan;
  t_channel *to_join;
  t_client *cli;
  char *name;

  cli = *cli_raw;
  (void)tosend;
  name = strtok(buf, " ");
  name = strtok(NULL, " ");
  chan = srv->channel;
  if (!name)
    return;
  if (cli->channel)
    {
      send(cli->socket, "\02server:  leave the chan first", 30, 0);
      return;
    }
  to_join = chan_exists(chan, name);
  if (to_join)
      join_chan(srv, to_join, cli);
  else
    action_join_else(srv, cli_raw, name);
  *cli_raw = NULL;
}
