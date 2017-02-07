/*
** list.c for srv in /home/ledins_a/Dropbox/irc_lt_2017/server_source/sources/clients
** 
** Made by ledins
** Login   <ledins_a@epitech.net>
** 
** Started on  Sun Apr 27 12:54:43 2014 ledins
** Last update Sun Apr 27 13:09:49 2014 ledins
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "server.h"
#include "xlib.h"

static t_client *new_client(int socket)
{
  t_client *new;

  new = xmalloc(sizeof(t_client), __LINE__, __FILE__);
  if (!new)
    exit(EXIT_FAILURE);
  new->socket = socket;
  new->channel = NULL;
  new->next = NULL;
  new->ip = NULL;
  new->last_recv = time(NULL);
  bzero(new->nickname, MAX_NICKNAME);
  strcpy(new->nickname, "guest");
  return (new);
}

static void add_first_client(t_server *server, t_client **raw, int socket)
{
  t_client *new;

  new = new_client(socket);
  *raw = new;
  server->clients = *raw;
}

static void add_another_client(t_client *raw, int socket)
{
  t_client *new;

  new = new_client(socket);
  while (raw && raw->next)
    raw = raw->next;
  raw->next = new;
}

void client_add_client(t_server *server, int socket)
{
  t_client *client;

  client = server->clients;
  if (client)
    add_another_client(client, socket);
  else
    add_first_client(server, &server->clients, socket);
}
