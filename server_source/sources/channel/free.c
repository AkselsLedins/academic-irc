/*
** free.c for srv in /home/ledins_a/Dropbox/irc_lt_2017/server_source/sources/channel
** 
** Made by ledins
** Login   <ledins_a@epitech.net>
** 
** Started on  Sun Apr 27 13:42:48 2014 ledins
** Last update Sun Apr 27 13:42:49 2014 ledins
*/

#include <unistd.h>
#include <stdlib.h>
#include "server.h"

void channels_free(t_channel *chan)
{
  t_channel *ptr;

  while (chan)
    {
      ptr = chan;
      chan = chan->next;
      free(ptr);
      ptr = NULL;
    }
}
