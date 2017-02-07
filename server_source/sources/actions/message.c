/*
** message.c for srv in /home/ledins_a/Dropbox/irc_lt_2017/server_source/sources/actions
** 
** Made by ledins
** Login   <ledins_a@epitech.net>
** 
** Started on  Sun Apr 27 13:44:05 2014 ledins
** Last update Sun Apr 27 13:45:38 2014 ledins
*/

#include <stdio.h>
#include <strings.h>
#include <string.h>
#include "server.h"

void action_message_all(t_server *srv, t_client **cli_raw, char *buf, int t)
{
  t_client *list_of_client;
  t_client *cli;

  cli = *cli_raw;
  list_of_client = srv->clients;
  buf[0] = SHOW_MESSAGE;
  if (cli->channel)
    list_of_client = cli->channel->client;
  while (list_of_client)
    {
      send(list_of_client->socket, buf, t, 0);
      list_of_client = list_of_client->next;
    }
}
