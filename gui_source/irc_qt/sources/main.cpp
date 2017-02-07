//
// main.cpp for irc_qt in /home/titouan/Dropbox/Code/irc/irc_lt_2017/gui_source/irc_qt
//
// Made by titouan creach
// Login   <creach_a@epitech.net>
//
// Started on  Wed Apr 23 10:49:58 2014 titouan creach
// Last update Wed Apr 23 10:49:58 2014 titouan creach
//

#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
