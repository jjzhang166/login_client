#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>
#include <QtNetwork/QUdpSocket>

namespace Ui {
class ChatWindow;
}

enum SendType{Message,Join,Leave};

class ChatWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = 0);
    ~ChatWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ChatWindow *ui;
    QUdpSocket *udpsocket;
    void    Sendmessage(SendType);

private slots:
    void processPendingDatagrams();
};

#endif // CHATWINDOW_H
