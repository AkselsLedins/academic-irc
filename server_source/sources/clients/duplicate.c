/*
** duplicate.c for srv in /home/ledins_a/Dropbox/irc_lt_2017/server_source/sources/clients
** 
** Made by ledins
** Login   <ledins_a@epitech.net>
** 
** Started on  Sun Apr 27 12:54:01 2014 ledins
** Last update Sun Apr 27 12:54:05 2014 ledins
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "server.h"
#include "xlib.h"

t_client * clone_client(t_client *cli)
{
  t_client *new_client;

  new_client = NULL;
  new_client = xmalloc(sizeof(t_client), __LINE__, __FILE__);
  if (new_client)
    {
      if (cli->ip)
	new_client->ip = strdup(cli->ip);
      else
	new_client->ip = NULL;
      new_client->socket = cli->socket;
      new_client->color = cli->color;
      new_client->channel = cli->channel;
      new_client->next = NULL;
      new_client->last_recv = cli->last_recv;
      memcpy(&new_client->nickname, &cli->nickname, MAX_NICKNAME);
      return (new_client);
    }
  else
    exit(EXIT_FAILURE);
  return (new_client);
}
