##
## Makefile for client_source in /home/titouan/Dropbox/Code/irc/irc_lt_2017/client_source
## 
## Made by titouan creach
## Login   <creach_a@epitech.net>
## 
## Started on  Tue Apr 15 14:16:18 2014 titouan creach
## Last update Sun Apr 27 19:55:48 2014 ledins
##

CC			=		gcc -g
RM			= 	rm -f
NAME		=		serveur
INC_DIR	=		./includes/
SRC_DIR	=		./sources/
XLIB_DIR=   ./sources/xlib/

CFLAGS	=		-W -Wall -Wextra -I$(INC_DIR)

SRC			=		$(SRC_DIR)main.c \
	$(SRC_DIR)initialization/server.c \
	$(SRC_DIR)circular_buffer/init.c \
	$(SRC_DIR)circular_buffer/free.c \
	$(SRC_DIR)circular_buffer/circular.c \
	$(SRC_DIR)clients/free.c \
	$(SRC_DIR)clients/io.c \
	$(SRC_DIR)clients/list.c \
	$(SRC_DIR)clients/list_delete.c \
	$(SRC_DIR)clients/actions.c \
	$(SRC_DIR)clients/timeout.c \
	$(SRC_DIR)clients/duplicate.c \
	$(SRC_DIR)actions/message.c \
	$(SRC_DIR)actions/undefined.c \
	$(SRC_DIR)actions/list.c \
	$(SRC_DIR)actions/private.c \
	$(SRC_DIR)actions/parsing.c \
	$(SRC_DIR)actions/join.c \
	$(SRC_DIR)actions/part.c \
	$(SRC_DIR)actions/nick.c \
	$(SRC_DIR)channel/free.c \
	$(SRC_DIR)channel/create.c \
	$(SRC_DIR)network/init.c \
	$(SRC_DIR)network/message.c \
	$(SRC_DIR)network/close.c \
	$(SRC_DIR)network/run.c \
	$(XLIB_DIR)xmalloc.c \
	$(XLIB_DIR)xsocket.c \
	$(XLIB_DIR)xclose.c \


OBJ			=		$(SRC:.c=.o)

%.o:	%.c
	$(CC) -c $^ -o $@ $(CFLAGS)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
