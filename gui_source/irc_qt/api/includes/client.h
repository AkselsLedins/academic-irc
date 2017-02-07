/*
** circular_buffers.c for sources in /home/titouan/Dropbox/Code/irc/irc_lt_2017/gui_source/irc_qt/api/sources
**
** Made by titouan creach
** Login   <creach_a@epitech.net>
**
** Started on  Sun Apr 27 19:50:02 2014 titouan creach
** Last update Sun Apr 27 19:50:02 2014 titouan creach
*/

#ifndef CLIENT_H
#define CLIENT_H

#include <sys/socket.h>

#define IGNORE(x) ((void)x)

typedef struct
{
  int         size;
  int         start;
  int         end;
  char        *elems;
} CircularBuffer;

enum msg_type
{
    MSG,
    USER,
    SERVER
};

extern char *last_error;

int connect_server(char *ip, unsigned int port);
char *get_ip_from_string(char *s);
int get_port_from_string(char *s);
void cbInit(CircularBuffer *cb, int size);
void cbFree(CircularBuffer *cb);
int cbIsFull(CircularBuffer *cb);
int cbIsEmpty(CircularBuffer *cb);
void cbWrite(CircularBuffer *cb, char *elem, size_t size);
void cbRead(CircularBuffer *cb, char *elem, size_t size);

#endif
