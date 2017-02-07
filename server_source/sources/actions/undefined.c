/*
** undefined.c for srv in /home/ledins_a/Dropbox/irc_lt_2017/server_source/sources/actions
** 
** Made by ledins
** Login   <ledins_a@epitech.net>
** 
** Started on  Sun Apr 27 13:44:53 2014 ledins
** Last update Sun Apr 27 13:44:56 2014 ledins
*/

#include <stdio.h>
#include <strings.h>
#include <string.h>
#include "server.h"

void action_undefined(t_server *srv, t_client **cli_raw, char *buf, int tosend)
{
t_client *client;

client = *cli_raw;
send(client->socket, "\02server : command not found", 27, 0);
(void)srv;
(void)cli_raw;
(void)buf;
(void)tosend;
}
