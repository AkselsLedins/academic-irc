#include "connectdialog.h"
#include "ui_connectdialog.h"
#include "mainwindow.h"

ConnectDialog::ConnectDialog(int socket, QLineEdit *edit, MainWindow *p, QWidget *parent) :
    QDialog(parent),
    _socket(socket),
    ui(new Ui::ConnectDialog),
    _edit(edit),
    _p(p)
{
    ui->setupUi(this);
}

ConnectDialog::~ConnectDialog()
{
    delete ui;
}

void ConnectDialog::on_buttonBox_accepted()
{
    QString tmp;

    tmp = "/server " + ui->a->text() + "." +ui->b->text() + "." + ui->c->text()+ "." + ui->d->text() + ":" + ui->port->text();
    qDebug(tmp.toStdString().c_str());
    _edit->setText(tmp);
    emit _p->sendMessage();
}
