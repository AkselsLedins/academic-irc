/*
** connection.c for sources in /home/titouan/Dropbox/Code/irc/irc_lt_2017/client_source/sources
**
** Made by titouan creach
** Login   <creach_a@epitech.net>
**
** Started on  Wed Apr 16 10:22:50 2014 titouan creach
** Last update Wed Apr 16 10:22:50 2014 titouan creach
*/

#include <stdlib.h>
#include <ctype.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include "client.h"

char *last_error;

int connect_server(char *ip, unsigned int port)
{
  struct protoent *pe;
  struct sockaddr_in sin;
  int s;

  pe = getprotobyname("TCP");
  if ((s = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
  {
    last_error = strerror(errno);
    return (-1);
  }
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = inet_addr(ip);
  sin.sin_port = htons(port);
  if (connect(s, (struct sockaddr*)&sin, sizeof(sin)) == -1)
  {
    last_error = strerror(errno);
    return (-1);
  }
  return (s);
}

char *get_ip_from_string(char *s)
{
  char *ret;

  if (!strtok(s, " :\t\n"))
    return (NULL);
  ret = strtok(NULL, " :\t\n");
  return (ret ? ret : "127.0.0.1");
}

int get_port_from_string(char *s)
{
  char *ret;

  if (strtok(s, ":\t\n") == NULL)
    return 1337;
  ret = strtok(NULL, ":\t\n");
  return (ret ? atoi(ret) : 4550);
}
