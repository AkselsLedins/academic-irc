/*
** init.c for srv in /home/ledins_a/Dropbox/irc_lt_2017/server_source/sources/circular_buffer
**
** Made by ledins
** Login   <ledins_a@epitech.net>
**
** Started on  Sun Apr 27 13:41:32 2014 ledins
** Last update Sun Apr 27 13:41:58 2014 ledins
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "server.h"
#include "xlib.h"

static t_list * new_node()
{
  t_list * node;

  if ((node = xmalloc(sizeof(t_list), __LINE__, __FILE__)) == NULL)
    return (NULL);
  node->id = NOT_FOUND;
  return (node);
}

static int first_node(t_actions ** raw)
{
  t_actions * actions;
  t_list * list;

  if ((actions = xmalloc(sizeof(t_actions), __LINE__, __FILE__)) == NULL)
    return (FAIL);
  if ((list = xmalloc(sizeof(t_list), __LINE__, __FILE__)) == NULL)
    return (FAIL);
  list->next = list;
  list->id = NOT_FOUND;
  actions->head = list;
  actions->tail = list;
  actions->list = list;
  *raw = actions;
  return (OK);
}

static int add_node(t_actions ** raw)
{
  t_list * tmp;
  t_list * new;

  if (*raw)
    {
      if ((new = new_node()) == NULL)
	return (FAIL);
      tmp = (*raw)->tail;
      tmp->next = new;
      (*raw)->tail = new;
      (*raw)->tail->next = (*raw)->head;
      return (OK);
    }
  return (first_node(raw));
}

int create_n_actions(t_actions ** raw, size_t n)
{
  while (n > 0)
    {
      if (add_node(raw) == FAIL)
	return (FAIL);
      n--;
    }
  return (OK);
}
