######################################################################
# Automatically generated by qmake (3.0) Sun Apr 27 20:06:41 2014
######################################################################

TEMPLATE = app
TARGET = client
INCLUDEPATH += . inc api/includes
QT += widgets

# Input
HEADERS += inc/connectdialog.h inc/mainwindow.h api/includes/client.h
FORMS += ui/connectdialog.ui ui/mainwindow.ui
SOURCES += sources/connectdialog.cpp \
           sources/main.cpp \
           sources/mainwindow.cpp \
           api/sources/circular_buffers.c \
           api/sources/connection.c
