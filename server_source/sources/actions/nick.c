/*
** nick.c for srv in /home/ledins_a/Dropbox/irc_lt_2017/server_source/sources/actions
** 
** Made by ledins
** Login   <ledins_a@epitech.net>
** 
** Started on  Sun Apr 27 13:44:10 2014 ledins
** Last update Sun Apr 27 13:44:15 2014 ledins
*/

#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "server.h"

void action_nick(t_server *srv, t_client **cli_raw, char *bufd, int tosend)
{
  char buf[4096];
  t_client *cli;
  char *nickname;
  int tocopy;

  cli = *cli_raw;
  nickname = strtok(bufd, " ");
  nickname = strtok(NULL, " ");
  if (nickname)
    tocopy = strlen(nickname);
  if (!nickname || strchr(nickname, ' ') != NULL || tocopy > MAX_NICKNAME)
    {
      strncpy(buf, "kserver : nickname invalid", 26);
      buf[0] = SHOW_SERVER;
      send(cli->socket, buf, 26, 0);
      return;
    }
  bzero(cli->nickname, MAX_NICKNAME);
  strcat(cli->nickname, nickname);
  strncpy(buf, "kserver : nickname changed", 26);
  buf[0] = SHOW_SERVER;
  send(cli->socket, buf, 26, 0);
  (void)tosend;
  (void)srv;
}
