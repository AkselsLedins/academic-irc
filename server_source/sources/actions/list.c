/*
** list.c for srv in /home/ledins_a/Dropbox/irc_lt_2017/server_source/sources/actions
**
** Made by ledins
** Login   <ledins_a@epitech.net>
**
** Started on  Sun Apr 27 13:43:54 2014 ledins
** Last update Sun Apr 27 13:47:30 2014 ledins
*/

#include <stdio.h>
#include <strings.h>
#include <string.h>
#include "server.h"

void action_list_users(t_server *srv, t_client **cli_raw, char *b, int t)
{
  t_client *cli;
  char buf_list[4096];
  t_client *list_of_client;

  cli = *cli_raw;
  (void)t;
  (void)b;
  bzero(buf_list, sizeof(buf_list));
  list_of_client = srv->clients;
  if (cli->channel)
    list_of_client = cli->channel->client;
  buf_list[0] = SHOW_USER;
  while (list_of_client)
    {
      strcat(buf_list, list_of_client->nickname);
      strcat(buf_list, " ");
      list_of_client = list_of_client->next;
    }
  send(cli->socket, buf_list, strlen(buf_list), 0);
}
