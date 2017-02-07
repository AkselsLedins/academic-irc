/*
** parsing.c for sources in /home/titouan/Dropbox/Code/irc/irc_lt_2017/client_source/sources
**
** Made by titouan creach
** Login   <creach_a@epitech.net>
**
** Started on  Tue Apr 15 14:29:11 2014 titouan creach
** Last update Tue Apr 15 14:29:11 2014 titouan creach
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "server.h"

static void parsing_loop(const char **tab, const char *cmd,
    struct s_rec_action *action)
{
  int i;

  i = 0;
  while (i < 10)
  {
    if (!strcmp(cmd, tab[i]))
    {
      action->id = i;
      return;
    }
    ++i;
  }
  action->id  = (cmd[0] == '/') ? (NOT_FOUND) : (MESSAGE);
}

static void identify_cmd(char *cmd_raw, struct s_rec_action *action)
{
  char *cmd;

  cmd = cmd_raw + 1;
  static const char *tab[20] =
  {
    "/server",
    "/list",
    "/nick",
    "/join",
    "/part",
    "/users",
    "/private",
    "/msg",
    "/send_file",
    "/accept_file",
    "/quit"
  };

  parsing_loop(tab, cmd, action);
}

void parse_arguments(char *s, struct s_rec_action *action)
{
  char *cmd;

  cmd = strtok(s, "\n\t ");
  identify_cmd(cmd, action);
}
