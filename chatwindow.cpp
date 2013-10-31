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
//enum Type{Message,Join,Leave};
void ChatWindow::processPendingDatagrams()
{
    while (udpsocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpsocket->pendingDatagramSize());
        QDataStream in(&datagram,QIODevice::ReadOnly);
        Type type;
        in>>type;
        switch (type) {
        case Message:
            break;
        case Join:
            break;
        case Leave:
            break;
        }
    }
}

void ChatWindow::Sendmessage(Type TYPE)
{
    QByteArray data;
    QDataStream out(&data,QIODevice::WriteOnly);
    switch(TYPE)
    {
    case Join:out<<Join;break;
    case Leave:out<<Leave;break;
    case Message:out<<Message<<ui->textEdit->toPlainText();break;
    }
    udpsocket->writeDatagram(data,data.length(),QHostAddress::Broadcast,7777);
}

void ChatWindow::on_pushButton_clicked()
{

}
