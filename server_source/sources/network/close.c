/*
** close.c for close in /home/ledins_a/Dropbox/irc_lt_2017/server_source/sources/network
** 
** Made by ledins
** Login   <ledins_a@epitech.net>
** 
** Started on  Sun Apr 27 12:47:27 2014 ledins
** Last update Sun Apr 27 12:47:30 2014 ledins
*/

#include "xlib.h"
#include "server.h"

void network_close(t_server *server)
{
xclose(server->socket, __LINE__, __FILE__);
}
