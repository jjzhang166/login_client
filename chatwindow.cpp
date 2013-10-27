#include "chatwindow.h"
#include "ui_chatwindow.h"

ChatWindow::ChatWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);
    udpsocket=new QUdpSocket;
    udpsocket->bind(7777,QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint);
    connect(udpsocket,SIGNAL(readyRead()),this,SLOT(processPendingDatagrams()));
    Sendmessage(Join);
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

void ChatWindow::processPendingDatagrams()
{

}

void ChatWindow::Sendmessage(SendType TYPE)
{

}

void ChatWindow::on_pushButton_clicked()
{

}
