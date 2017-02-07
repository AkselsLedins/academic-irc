/*
** list_delete.c for srv in /home/ledins_a/Dropbox/irc_lt_2017/server_source
** 
** Made by ledins
** Login   <ledins_a@epitech.net>
** 
** Started on  Sun Apr 27 13:09:18 2014 ledins
** Last update Sun Apr 27 13:11:23 2014 ledins
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "server.h"
#include "xlib.h"

static t_client * case_one(t_client *tmp, t_client *l)
{
  tmp->next = l->next;
  free(l);
  l = NULL;
  return (tmp->next);
}

t_client * client_delete_node_chan(t_channel *chan, t_client *to_delete)
{
  t_client *tmp;
  t_client *l;

  l = chan->client;
  tmp = NULL;
  while (l)
    {
      if (l == to_delete)
        {
          if (tmp)
            {
	      return (case_one(tmp, l));
            }
          else
            {
              tmp = l->next;
              chan->client = tmp;
              free(l);
              return (tmp);
            }
        }
      tmp = l;
      l= l->next;
    }
  return (NULL);
}

t_client * client_delete_node(t_server *srv, t_client *l, t_client *to_delete)
{
  t_client *tmp;

  tmp = NULL;
  while (l)
    {
      if (l == to_delete)
        {
          if (tmp)
            {
	      tmp->next = l->next;
              free(l);
              return (tmp->next);
            }
          else
            {
              tmp = l->next;
              srv->clients = tmp;
              free(l);
	      return (tmp);
	    }
	}
      tmp = l;
      l = l->next;
    }
  return (NULL);
}
