#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QStringListModel>
#include <QMainWindow>

extern "C"
{
#include "client.h"
}

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindow *ui;
    void printOnScreen(size_t size, enum msg_type cmd);

private slots:
    void reception(void);
    void updateList(void);
    void on_actionConnection_to_server_triggered();

    void on_usersList_clicked(const QModelIndex &index);

public slots:
    void sendMessage(void);

private:
    int _s;
    CircularBuffer _cb;
    QStringListModel *model;

};

#endif // MAINWINDOW_H
