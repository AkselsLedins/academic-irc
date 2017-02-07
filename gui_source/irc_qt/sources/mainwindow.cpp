#include <string.h>
#include <QString>
#include <QApplication>
#include <QTimer>
#include <unistd.h>
#include "mainwindow.h"
#include "connectdialog.h"
#include "ui_mainwindow.h"
#include <sys/select.h>
#include <QDebug>
#include <QCompleter>
#include <algorithm>
#include <errno.h>

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow),
        _s(-1)
{
    QStringList completionList;

    ui->setupUi(this);
    connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(sendMessage()));
    connect(ui->userInput , SIGNAL(returnPressed()), this, SLOT(sendMessage()));
    QTimer *timer = new QTimer(this);
    QTimer *timerUser = new QTimer(this);
    connect(timerUser, SIGNAL(timeout()), this, SLOT(updateList()));
    timerUser->start(10000);
    connect(timer, SIGNAL(timeout()), this, SLOT(reception()));
    timer->start(500);
    QFile File("./res/style.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    qApp->setStyleSheet(StyleSheet);
    cbInit(&_cb, 4096);
    model = new QStringListModel(this);
    completionList << "/server" << "/join" << "/private";
    QCompleter *completer = new QCompleter(completionList, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->userInput->setCompleter(completer);
}
void MainWindow::printOnScreen(size_t size, enum msg_type cmd)
{
    char buff[size + 1];

    bzero(buff, size);
    cbRead(&_cb, buff, size);
    buff[size] = 0;
    QStringList l;
    char *a = buff;
    char *g;

    qDebug() <<  cmd;
    if (cmd == USER)
    {
        while ((g = strtok(a, " ")) != NULL)
        {
            l << g;
            a = NULL;
        }

        model->setStringList(l);
        ui->usersList->setModel(model);
    }
    else if (cmd == SERVER)
    {
        std::string buffStd = buff;
        std::replace(buffStd.begin(), buffStd.end(), static_cast<char>(SERVER), static_cast<char>(10));
        ui->messages->appendHtml(QString("<font color=\"#2E9AFE\"><i>") + QString(buff) + QString("</font></i>"));
    }
    else
    {
        ui->messages->appendPlainText(QString(buff));
    }

}

void MainWindow::updateList()
{
    if (_s != -1)
        write(_s, "/list\r\n", 7);
}

void MainWindow::reception()
{
    fd_set rfds;
    size_t n = 16;
    struct timeval t;
    char buff[16];
    size_t buff_size = 0;
    enum msg_type cmd = MSG;
    int retval;

    if (_s == -1)
        return;
    FD_ZERO(&rfds);
    t.tv_sec = 0;
    t.tv_usec = 0;
    FD_SET(_s, &rfds);
    retval = select(_s + 1, &rfds, NULL, NULL, &t);
    if (retval < 0 && errno != EINTR)
    {
      ui->messages->appendHtml(QString("<i><font color=\"#ff0000\">")  + QString("Select has failed...") + QString("</font></i>"));

    }
    if (FD_ISSET(_s, &rfds))
    {
        while (n == 16)
        {
            n = recv(_s, buff, 16, 0);

            if (buff_size == 0 && n)
            {
                buff_size += (n - 1);
                cbWrite(&_cb, buff + 1, n - 1);
                cmd = static_cast<enum msg_type>(*buff);
            }
            else
            {
                buff_size += n;
                cbWrite(&_cb, buff, n);
            }
            if (n == 0)
            {
                ui->messages->appendHtml(QString("<i><font color=\"#ff0000\">")  + QString("You're now deconnected") + QString("</font></i>"));
                _s = 1;
                return;
            }
        }
        printOnScreen(buff_size, cmd);
    }
}

void MainWindow::sendMessage()
{
    if (ui->userInput->text().isEmpty())
        return;
    if (!strncmp(ui->userInput->text().toStdString().c_str(), "/server", strlen("/server")))
    {
        _s = connect_server(get_ip_from_string(ui->userInput->text().toLocal8Bit().data()),
                            get_port_from_string(ui->userInput->text().toLocal8Bit().data()));
        if (_s == -1)
        {
            ui->messages->appendHtml(QString("<i><font color=\"#ff0000\">")  + QString(last_error) + QString("</font></i>"));
            ui->userInput->setText("");
        }
        else
        {
            ui->messages->appendHtml(QString("<i><font color=\"#78A419\">")  + QString("Connected") + QString("</font></i>"));
            emit updateList();
        }
        ui->userInput->setText("");
        return;
    }
    if (_s == -1)
    {
        ui->messages->appendHtml(QString("<i><font color=\"#ff0000\">")  + QString("You must be connected, type /server ip port") + QString("</font></i>"));
        ui->userInput->setText("");
        return;
    }
    QString tmp = ui->userInput->text() + QString("\r\n");
    send(_s, tmp.toStdString().c_str(), tmp.length(), 0);
    ui->userInput->setText("");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionConnection_to_server_triggered()
{
    QDialog *d = new ConnectDialog(_s, ui->userInput, this);
    d->show();
}

void MainWindow::on_usersList_clicked(const QModelIndex &index)
{
    ui->userInput->setText(QString("/private ") + index.data().toString() + QString(" "));
}
