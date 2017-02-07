#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include "mainwindow.h"

extern "C"
{
  #include "client.h"
}

namespace Ui {
class ConnectDialog;
}

class ConnectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectDialog(int socket, QLineEdit *edit, MainWindow *p, QWidget *parent = 0);
    ~ConnectDialog();

private slots:
    void on_buttonBox_accepted();

private:
    int _socket;
    Ui::ConnectDialog *ui;
    QLineEdit *_edit;
    MainWindow *_p;
};

#endif // CONNECTDIALOG_H
