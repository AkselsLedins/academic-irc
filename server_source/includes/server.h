/*
** server.h for srv in /home/ledins_a/Dropbox/irc_lt_2017/server_source/includes
** 
** Made by ledins
** Login   <ledins_a@epitech.net>
** 
** Started on  Sun Apr 27 13:54:04 2014 ledins
** Last update Sun Apr 27 13:56:23 2014 ledins
*/

#include <unistd.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <time.h>
#include <stdbool.h>

#ifndef SERVER_H
#define SERVER_H

/* default values */
#define DEFAULT_PORT 4550
#define DEFAULT_QUEUE 30
#define BUFF_SIZE 4096

#define MAX_BUF 260
#define MAX_ARG 128
#define MAX_NICKNAME 50
#define MAX_CHANNEL_NAME 50
#define MAX_ACTIONS 4

/* colors*/
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

#define FAIL 1
#define OK 0

enum e_show
{
  SHOW_MESSAGE,
  SHOW_USER,
  SHOW_SERVER
};

enum e_command
{
  SERVER,
  LIST,
  NICK,
  JOIN,
  PART,
  USERS,
  PRIVATE,
  SEND_FILE,
  ACCEPT_FILE,
  QUIT,
  MESSAGE,
  NOT_FOUND
};

typedef struct s_client
{
  char nickname[MAX_NICKNAME];
  unsigned int color;
  int socket;
  char * ip;
  struct s_channel * channel;
  struct s_client * next;
  time_t last_recv;
} t_client;

typedef struct s_channel
{
  unsigned int id;
  char name[MAX_CHANNEL_NAME];
  struct s_client * client;
  struct s_channel * next;
} t_channel;

typedef struct s_rec_action
{
  char arg[2][128];
  enum e_command id;
} t_rec_action;

typedef struct s_list
{
  char arg[2][128];
  enum e_command id;
  struct s_list * next;
} t_list;

typedef struct s_actions
{
  struct s_list * list;
  struct s_list * head;
  struct s_list * tail;
} t_actions;

typedef struct s_server
{
  struct s_actions * actions;
  struct s_client * clients;
  struct s_channel * channel;
  fd_set readfds;
  int socket;
  int max_socket;
  struct sockaddr_in address;
  int port;
  socklen_t addrlen;
  void (*tab[12])(struct s_server *, t_client **, char *, int);
} t_server;

struct s_circular_buffer
{
  char buff[BUFF_SIZE];
  char *ptr_write_begin;
  char *ptr_read_begin;
};

typedef struct
{
  int         size;
  int         start;
  int         end;
  int         nread;
  char        *elems;
} CircularBuffer;

/* functions prototypes */
int server_init(t_server **);
void server_free(t_server *);
int create_n_actions(t_actions **, size_t);
void actions_free(t_actions *);
void clients_free(t_client *);
t_client * client_disconnect(t_server *, t_client *, bool *);
void clients_io(t_server *, CircularBuffer *);
void clients_actions(t_server *, t_client **, CircularBuffer *);
t_client * clone_client(t_client *);
t_client * client_delete_node(t_server *, t_client *, t_client *);
void client_add_client(t_server *, int);
void channels_free(t_channel *);
void channel_create(t_server *, char []);
int network_init(t_server *);
void network_close(t_server *);
void network_run(t_server *);
void send_message_to(t_client *, char *);
void action_message_all(t_server *, t_client **, char *, int);
void action_list_users(t_server *srv, t_client **cli, char *buf, int);
void action_join(t_server *srv, t_client **cli, char *buf, int);
void action_undefined(t_server *srv, t_client **cli_raw, char *buf, int);
void action_nick(t_server *srv, t_client **cli_raw, char *buf, int);
void action_private(t_server *, t_client **, char *, int);
void action_quit_channel(t_server *srv, t_client **cli_raw, char *buf, int);
void cbInit(CircularBuffer *cb, int size);
void cbFree(CircularBuffer *cb);
int cbIsFull(CircularBuffer *cb);
int cbIsEmpty(CircularBuffer *cb);
void cbWrite(CircularBuffer *cb, char elem);
char cbRead(CircularBuffer *cb, char elem);
void parse_arguments(char *s, struct s_rec_action *action);
t_client * client_delete_node_chan(t_channel *chan, t_client *to_delete);
void function_timeout(t_server *srv);

#endif /* ! server.h */
