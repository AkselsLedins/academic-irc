/*
** actions.c for srv in /home/ledins_a/Dropbox/irc_lt_2017/server_source/sources/clients
** 
** Made by ledins
** Login   <ledins_a@epitech.net>
** 
** Started on  Sun Apr 27 12:53:49 2014 ledins
** Last update Sun Apr 27 13:06:26 2014 ledins
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include "server.h"

static void init_tab_once(t_server *srv)
{
  static int i;

  if (i != 0)
    return;
  i = 42;
  srv->tab[MESSAGE] = action_message_all;
  srv->tab[LIST] = action_list_users;
  srv->tab[JOIN] = action_join;
  srv->tab[NOT_FOUND] = action_undefined;
  srv->tab[PRIVATE] = action_private;
  srv->tab[NICK] = action_nick;
  srv->tab[PART] = action_quit_channel;
}

void clients_actions(t_server *srv, t_client **cli, CircularBuffer *cb)
{
  char buff[BUFF_SIZE];
  int tosend;
  int i;
  t_rec_action action;
  char *savebuf;

  init_tab_once(srv);
  tosend = cb->nread > cb->size ? cb->size : cb->nread;
  tosend = cb->size == tosend ? tosend - 1 : tosend;
  bzero(buff, sizeof(buff));
  i = 1;
  while (i < tosend + 1)
    {
      buff[i] = cbRead(cb, buff[i]);
      i++;
    }
  buff[0] = 'b';
  buff[i] = '\0';
  savebuf = strdup(buff);
  parse_arguments(buff, &action);
  if ((action.id >= LIST && action.id <= PRIVATE) || action.id == MESSAGE)
    srv->tab[action.id](srv, cli, savebuf, tosend + 1);
  else
    srv->tab[NOT_FOUND](srv, cli, savebuf, tosend + 1);
  free(savebuf);
}
