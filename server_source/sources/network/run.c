/*
** run.c for srv in /home/ledins_a/Dropbox/irc_lt_2017/server_source/sources/network
**
** Made by ledins
** Login   <ledins_a@epitech.net>
**
** Started on  Sun Apr 27 12:48:11 2014 ledins
** Last update Sun Apr 27 18:53:14 2014 ledins
*/

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <time.h>
#include "server.h"

static void add_chan_fdset(t_server *server, t_channel *chan)
{
  t_client *client;
  int socket;

  while (chan)
    {
      client = chan->client;
      while (client)
	{
	  socket = client->socket;
	  if (socket > 0)
	    FD_SET(socket, &server->readfds);
	  if (socket > server->max_socket)
	    server->max_socket = socket;
	  client = client->next;
	}
      chan = chan->next;
    }
}

static void add_clients_fdset(t_server *server)
{
  int socket;
  t_client *client;

  client = server->clients;
  while (client)
    {
      socket = client->socket;
      if (socket > 0)
	FD_SET(socket, &server->readfds);
      if (socket > server->max_socket)
	server->max_socket = socket;
      client = client->next;
    }
  add_chan_fdset(server, server->channel);
}

static void try_select(t_server *server)
{
  int retval;
  struct timeval timout;

  timout.tv_sec = 3 * 60;
  timout.tv_usec = 0;
  retval = select(server->max_socket + 1,
   &server->readfds, NULL, NULL, &timout);
  if (retval < 0 && errno != EINTR)
  {
    fprintf(stderr, "error : select failed %d:%s\t", __LINE__, __FILE__);
    perror("");
  }
  else if (retval == 0)
  {
    printf("timeout reached\n");
    exit(EXIT_FAILURE);
  }
  else if (retval < 0)
  {
    fprintf(stderr, "warning : retrying select because\t");
    perror("");
    sleep(1);
    try_select(server);
  }
}

static int accept_new_connexion(t_server *server)
{
  int socket;

  if (FD_ISSET(server->socket, &server->readfds))
    {
      memset(&server->address, 0, sizeof(struct sockaddr));
      socket = accept(server->socket,
		      (struct sockaddr *)&server->address,
		      (socklen_t *)&server->addrlen);
      if (socket < 0)
	{
	  fprintf(stderr, "error : accept failed %d:%s\t", __LINE__, __FILE__);
	  perror("");
	  return (FAIL);
	}
      printf("server : %snew connexion%s from %s:%d\n",
	     BOLDGREEN,
	     RESET,
	     inet_ntoa(server->address.sin_addr),
	     ntohs(server->address.sin_port));
      client_add_client(server, socket);
    }
  return (OK);
}

void network_run(t_server *server)
{

  CircularBuffer cb;
  cbInit(&cb, BUFF_SIZE);
  while (1)
    {
      FD_ZERO(&server->readfds);
      FD_SET(server->socket, &server->readfds);
      server->max_socket = server->socket;
      add_clients_fdset(server);
      try_select(server);
      if (accept_new_connexion(server) == FAIL)
	      return;
      clients_io(server, &cb);
//      function_timeout(server);
    }
}
