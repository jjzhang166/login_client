#ifndef SIGNUP_H
#define SIGNUP_H

#include <QWidget>
#include <QtNetwork/QUdpSocket>
#include <QDataStream>
#include <QMessageBox>
namespace Ui {
class SignUp;
}

class SignUp : public QWidget
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = 0);
    ~SignUp();

private:
    Ui::SignUp *ui;
    QUdpSocket *udpsocket;

    void initConnect();
    int LocalVerify();

private slots:
    void ReadMessage();
    void clearMSG();
    void SendMSG();
};

#endif // SIGNUP_H
