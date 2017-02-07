![Screenshot](http://git.aksels.me/academic/my-irc/raw/master/screenshot/connect.png)
![Screenshot](http://git.aksels.me/academic/my-irc/raw/master/screenshot/1client.png)
![Screenshot](http://git.aksels.me/academic/my-irc/raw/master/screenshot/2client.png)
![Screenshot](http://git.aksels.me/academic/my-irc/raw/master/screenshot/end.png)

The aim of this project is to realise a IRC client / server.  
Server is in C.
Client is partially in C and the GUI is in QT/C++.  


the communication network is through TCP sockets and select.  
The server is not only non-blocking, but also use "turning round" tampons to  
secure and optimize the sending as the receiving of the various commands and responses.