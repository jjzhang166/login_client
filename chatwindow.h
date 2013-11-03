#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>
#include <QtNetwork/QUdpSocket>
#include <QDataStream>
#include <QByteArray>
#include "TYPES.h"

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWindow(QString username,QWidget *parent = 0);
    ~ChatWindow();
private slots:
    void on_pushButton_clicked();

private:
    Ui::ChatWindow *ui;
    QUdpSocket *udpsocket;
    QString username;
    void    Sendmessage(Type);

private slots:
    void processPendingDatagrams();
};

#endif // CHATWINDOW_H
