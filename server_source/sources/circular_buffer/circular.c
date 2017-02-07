/*
** circular.c for srv in /home/ledins_a/Dropbox/irc_lt_2017/server_source/sources/circular_buffer
** 
** Made by ledins
** Login   <ledins_a@epitech.net>
** 
** Started on  Sun Apr 27 13:41:09 2014 ledins
** Last update Sun Apr 27 13:41:14 2014 ledins
*/

#include <stdio.h>
#include <stdlib.h>
#include "server.h"

void cbInit(CircularBuffer *cb, int size)
{
  cb->size  = size + 1;
  cb->start = 0;
  cb->end   = 0;
  cb->nread = 0;
  cb->elems = calloc(cb->size, sizeof(char));
}

void cbFree(CircularBuffer *cb)
{
  free(cb->elems);
}

int cbIsFull(CircularBuffer *cb)
{
  return (cb->end + 1) % cb->size == cb->start;
}

int cbIsEmpty(CircularBuffer *cb) {
  return cb->end == cb->start;
}

void cbWrite(CircularBuffer *cb, char elem)
{
  cb->elems[cb->end] = elem;
  cb->end = (cb->end + 1) % cb->size;
  if (cb->end == cb->start)
    cb->start = (cb->start + 1) % cb->size;
}

char cbRead(CircularBuffer *cb, char elem)
{
  elem = cb->elems[cb->start];
  cb->start = (cb->start + 1) % cb->size;
  return (elem);
}

