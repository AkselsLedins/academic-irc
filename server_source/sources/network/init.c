/*
** init.c for srv in /home/ledins_a/Dropbox/irc_lt_2017/server_source/sources/network
**
** Made by ledins
** Login   <ledins_a@epitech.net>
**
** Started on  Sun Apr 27 12:47:48 2014 ledins
** Last update Sun Apr 27 12:50:11 2014 ledins
*/

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include "xlib.h"
#include "server.h"

static int reuse_socket(int socket)
{
  int opt;
  int retval;

  opt = 1;
  retval = setsockopt(socket,
		      SOL_SOCKET,
		      SO_REUSEADDR,
		      (char *)&opt,
		      sizeof(opt));
  if (retval < 0)
    {
      fprintf(stderr, "error : setsockopt failed %d:%s\t", __LINE__, __FILE__);
      perror("");
    }
  return (retval);
}

static int init_address(t_server *server)
{
  int retval;

  server->address.sin_family = AF_INET;
  server->address.sin_addr.s_addr = INADDR_ANY;
  server->address.sin_port = htons(server->port);
  retval = bind(server->socket,
		(struct sockaddr *)&server->address,
		sizeof(server->address));
  if (retval < 0)
    {
      fprintf(stderr, "error : bind failed %d:%s\t\t", __LINE__, __FILE__);
      perror("");
    }
  return (retval);
}

static int listen_port(t_server *server)
{
  int retval;

  retval = listen(server->socket, DEFAULT_QUEUE);
  if (retval < 0)
    {
      fprintf(stderr, "error : listen failed %d:%s\t", __LINE__, __FILE__);
      perror("");
    }
  else
    printf("server : started listening on port %s%d%s\n",
	   BOLDBLUE,
	   server->port,
	   RESET);
  return (retval);
}

int network_init(t_server *server)
{
  server->port = DEFAULT_PORT;
  server->socket = xsocket(__LINE__, __FILE__);
  
  if (server->socket == 0)
    return (FAIL);
  if (reuse_socket(server->socket) < 0)
    return (FAIL);
  if (init_address(server) < 0)
    return (FAIL);
  if (listen_port(server) < 0)
    return (FAIL);
  printf("server : waiting for connexions\n");
  return (OK);
}
