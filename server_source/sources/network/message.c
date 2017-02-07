/*
** message.c for srv in /home/ledins_a/Dropbox/irc_lt_2017/server_source/sources/network
** 
** Made by ledins
** Login   <ledins_a@epitech.net>
** 
** Started on  Sun Apr 27 12:48:01 2014 ledins
** Last update Sun Apr 27 12:48:07 2014 ledins
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "server.h"

void send_message_to(t_client *client, char *statement)
{
t_rec_action message;

message.id = MESSAGE;
bzero(message.arg[0], MAX_ARG);
bzero(message.arg[1], MAX_ARG);
if (strlen(statement) > MAX_ARG)
  strncpy(message.arg[0], statement, MAX_ARG);
 else
   strncpy(message.arg[0], statement, strlen(statement));
write(client->socket, (char *)&message, MAX_BUF);
}
