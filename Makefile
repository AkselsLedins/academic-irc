
RM		= rm -f

all:
	make -C server_source/
	make -C gui_source/irc_qt
	cp -f server_source/serveur .
	cp -f gui_source/irc_qt/client .

clean:
	make -C server_source/ clean
	make -C gui_source/irc_qt clean


fclean:
	make -C server_source/ fclean
	make -C gui_source/irc_qt clean
	$(RM) "client"
	$(RM) "serveur"

re: fclean all
