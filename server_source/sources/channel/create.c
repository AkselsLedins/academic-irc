/*
** create.c for srv in /home/ledins_a/Dropbox/irc_lt_2017/server_source/sources/channel
** 
** Made by ledins
** Login   <ledins_a@epitech.net>
** 
** Started on  Sun Apr 27 13:42:36 2014 ledins
** Last update Sun Apr 27 13:43:14 2014 ledins
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "xlib.h"

static t_channel *new_channel(char name[])
{
  t_channel *new;

  new = xmalloc(sizeof(t_channel), __LINE__, __FILE__);
  if (!new)
    exit(EXIT_FAILURE);
  memcpy(new->name, name, strlen(name));
  new->name[strlen(name)] = '\0';
  new->client = NULL;
  new->next = NULL;
  return (new);
}

static void add_first_channel(t_server *server, t_channel **raw, char name[])
{
  t_channel *new;

  new = new_channel(name);
  *raw = new;
  server->channel = *raw;
}

static void add_another_channel(t_channel *raw, char name[])
{
  t_channel *new;

  new = new_channel(name);
  while (raw && raw->next)
    raw = raw->next;
  raw->next = new;
}

void channel_create(t_server *server, char name[])
{
  t_channel *channel;

  channel = server->channel;
  if (channel)
    add_another_channel(channel, name);
  else
    add_first_channel(server, &server->channel, name);
}
