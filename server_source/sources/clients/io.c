/*
** io.c for srv in /home/ledins_a/Dropbox/irc_lt_2017/server_source/sources/clients
**
** Made by ledins
** Login   <ledins_a@epitech.net>
**
** Started on  Sun Apr 27 12:54:38 2014 ledins
** Last update Sun Apr 27 13:40:43 2014 ledins
*/

#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "server.h"

static t_client * rinf(t_server *s, t_client *cli, CircularBuffer *cb, bool *e)
{
  int sd;
  char tmpbuf[BUFF_SIZE];
  int nread;
  int i;

  sd = cli->socket;
  nread = BUFF_SIZE;
  bzero(tmpbuf, sizeof(tmpbuf));
  while (nread == BUFF_SIZE)
    {
      if ((nread = read(sd, tmpbuf, BUFF_SIZE)) == 0)
	  cli = client_disconnect(s, cli, e);
      else
	{
	  cb->nread += nread;
	  i = -1;
	  if (nread != BUFF_SIZE)
	    nread -= 2;
	  while (++i < nread)
	    cbWrite(cb, tmpbuf[i]);
	}
      cb->nread -= 2;
    }
  return (cli);
}

static t_client *cl_par(t_server *s, t_client *client, CircularBuffer *cb)
{
  bool error;
  int sd;

  sd = client->socket;
  if (FD_ISSET(sd, &s->readfds))
    {
      cb->nread = 0;
      error = false;
      client = rinf(s, client, cb, &error);
      FD_CLR(sd, &s->readfds);
      if (error == false)
	clients_actions(s, &client, cb);
    }
  return (client);
}
static void client_parcours(t_server *srv, t_client *c, CircularBuffer *cb)
{
  t_client *old_client;

  old_client = NULL;
  while (c)
    {
      c = cl_par(srv, c, cb);
      if (!c)
	{
	  if (old_client)
	    c = old_client->next;
	}
      else if (c)
	{
	  old_client = c;
	  c = c->next;
	}
    }
}

static void chan_io(t_server *server, CircularBuffer *cb)
{
  t_channel *channel;
  t_client *client;

  channel = server->channel;
  while (channel)
    {
      client = channel->client;
      client_parcours(server, client, cb);
      channel = channel->next;
    }
}

void clients_io(t_server *server, CircularBuffer *cb)
{
  chan_io(server, cb);
  client_parcours(server, server->clients, cb);
}
