/*
** circular_buffers.c for sources in /home/titouan/Dropbox/Code/irc/irc_lt_2017/gui_source/irc_qt/api/sources
**
** Made by titouan creach
** Login   <creach_a@epitech.net>
**
** Started on  Sun Apr 27 19:50:02 2014 titouan creach
** Last update Sun Apr 27 19:50:02 2014 titouan creach
*/

#include <stdio.h>
#include <stdlib.h>
#include "client.h"

void cbInit(CircularBuffer *cb, int size)
{
  cb->size  = size + 1;
  cb->start = 0;
  cb->end   = 0;
  cb->elems = calloc(cb->size, sizeof(char));
}

void cbWrite(CircularBuffer *cb, char *elem, size_t size)
{
  size_t i;

  i = 0;
  while (i < size)
  {
    cb->elems[cb->end] = *elem;
    cb->end = (cb->end + 1) % cb->size;
    if (cb->end == cb->start)
      cb->start = (cb->start + 1) % cb->size;
    ++elem;
    ++i;
  }
 }

void cbRead(CircularBuffer *cb, char *elem, size_t size)
{
  size_t i;

  i = 0;
  while (i < size)
  {
    *elem = cb->elems[cb->start];
    cb->start = (cb->start + 1) % cb->size;
    ++i;
    ++elem;
  }
}

