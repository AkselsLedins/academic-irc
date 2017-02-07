/*
** free.c for srv in /home/ledins_a/Dropbox/irc_lt_2017/server_source/sources/circular_buffer
** 
** Made by ledins
** Login   <ledins_a@epitech.net>
** 
** Started on  Sun Apr 27 13:41:22 2014 ledins
** Last update Sun Apr 27 13:41:25 2014 ledins
*/

#include <unistd.h>
#include <stdlib.h>
#include "server.h"

void actions_free(t_actions * ptr)
{
t_list *list;
t_list *tmp;
int counter;

counter = 0;

list = ptr->list;
while (counter < MAX_ACTIONS)
  {
tmp = list;
if (list)
  list = list->next;
free(tmp);
tmp = NULL;
counter++;
}
}
