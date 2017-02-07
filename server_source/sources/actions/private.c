/*
** private.c for srv in /home/ledins_a/Dropbox/irc_lt_2017/server_source/sources/actions
** 
** Made by ledins
** Login   <ledins_a@epitech.net>
** 
** Started on  Sun Apr 27 13:44:44 2014 ledins
** Last update Sun Apr 27 13:44:45 2014 ledins
*/

#include <stdio.h>
#include <strings.h>
#include <string.h>
#include "server.h"

static int defil_users(t_client *l, char *nickname, char *bufs, char *buf)
{
  while (l)
    {
      if (strcmp(l->nickname, nickname) == 0 )
	{
	  strcat(bufs, "a");
	  strcat(bufs, buf);
	  bufs[0] = SHOW_MESSAGE;
	  send(l->socket, bufs, strlen(bufs + 1) + 1, 0);
	  return (0);
	}
      l = l->next;
    }
  return (-1);
}

void action_private(t_server *srv, t_client **cli_raw, char *buf, int tosend)
{
  t_client *list_of_client;
  char *nickname;
  int decal;
  char bufs[4096];

  (void)tosend;
  decal = 0;
  bzero(bufs, sizeof(bufs));
  nickname = strtok(buf, " ");
  if (!nickname)
    return;
  decal += strlen(nickname);
  nickname = strtok(NULL, " ");
  if (!nickname)
    return;
  decal += strlen(nickname);
  buf += decal + 2;
  list_of_client = srv->clients;
  if ((*cli_raw)->channel)
    list_of_client = (*cli_raw)->channel->client;
  if (defil_users(list_of_client, nickname, bufs, buf) == -1)
    send((*cli_raw)->socket, "\02server: user not found", 23, 0);
  else
    send((*cli_raw)->socket, bufs, strlen(bufs + 1) + 1, 0);
}
