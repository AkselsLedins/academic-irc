/*
** free.c for srv in /home/ledins_a/Dropbox/irc_lt_2017/server_source/sources/clients
**
** Made by ledins
** Login   <ledins_a@epitech.net>
**
** Started on  Sun Apr 27 12:54:10 2014 ledins
** Last update Sun Apr 27 13:37:50 2014 ledins
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include "server.h"
#include "xlib.h"

t_client * client_disconnect(t_server *server, t_client *client, bool *e)
{
  *e = true;
  /* a sauvegarder dans la structure du client */
  getpeername(client->socket ,
	      (struct sockaddr*)&server->address,
	      (socklen_t*)&server->addrlen);
  printf("server : %sclient disconnected%s -> %s:%d \n",
	 BOLDRED,
	 RESET,
	 inet_ntoa(server->address.sin_addr),
	 ntohs(server->address.sin_port));
  xclose(client->socket, __LINE__, __FILE__);
  if (client->channel)
    return (client_delete_node_chan(client->channel, client));
  return (client_delete_node(server, server->clients, client));
}

void clients_free(t_client *client)
{
  t_client *ptr;

  while (client)
    {
      ptr = client;
      client = client->next;
      free(ptr->ip);
      ptr->ip = NULL;
      free(ptr);
      ptr = NULL;
    }
}
