#include "signup.h"
#include "ui_signup.h"
#include "TYPES.h"

SignUp::SignUp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignUp)
{
    ui->setupUi(this);
    initConnect();
    connect(this->ui->pushButton_signup,SIGNAL(clicked()),this,SLOT(SendMSG()));
    connect(this->ui->pushButton_reset,SIGNAL(clicked()),this,SLOT(clearMSG()));
}

SignUp::~SignUp()
{
    delete ui;
}

/**
 * @brief SignUp::initConnect 初始化链接
 */
void SignUp::initConnect()
{
    udpsocket = new QUdpSocket;
    udpsocket->bind(7777,QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    connect(udpsocket,SIGNAL(readyRead()),this,SLOT(ReadMessage()));
}

/**
 * @brief SignUp::SendMSG 发送注册消息
 */
void SignUp::SendMSG()
{
    if(!LocalVerify())return;
    QByteArray data;
    QDataStream out(&data,QIODevice::WriteOnly);
    out<<Signup;
    out<<ui->lineEdit_Username->text();
    out<<ui->lineEdit_Passwd->text();
    udpsocket->writeDatagram(data,data.length(),QHostAddress::Broadcast,7777);//hostaddress要改成服务器
}

/**
 * @brief SignUp::LocalVerify 本地验证，账号密码输入框不能为空
 */
int SignUp::LocalVerify()
{
    if(ui->lineEdit_Username->text()=="")
    {
        QMessageBox::information(NULL, "信息提示", "用户名不能为空",
                                 QMessageBox::Yes,
                                 QMessageBox::Yes);
        return 0;
    }
    if(ui->lineEdit_Passwd->text()=="")
    {
        QMessageBox::information(NULL, "信息提示", "密码不能为空.",
                                 QMessageBox::Yes,
                                 QMessageBox::Yes);
        return 0;
    }
    return 1;
}

/**
 * @brief SignUp::ReadMessage 读取注册返回信息
 */
void SignUp::ReadMessage()
{
    while (udpsocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpsocket->pendingDatagramSize());
        udpsocket->readDatagram(datagram.data(),datagram.size());
        QDataStream in(&datagram,QIODevice::ReadOnly);
        int type;
        in>>type;
        QString tmp;
        if(type==SignupRes)
        {
            in>>tmp;
            if(tmp==ui->lineEdit_Username->text())
            {
                in>>tmp;
                if(tmp=="OK")
                {
                    QMessageBox::information(NULL, "信息提示", "注册成功",
                                             QMessageBox::Yes,
                                             QMessageBox::Yes);
                }
                else
                {
                    QMessageBox::information(NULL, "信息提示", "注册失败,该用户名已被注册",
                                             QMessageBox::Yes,
                                             QMessageBox::Yes);
                }
            }
            return;
        }
    }
}

/**
 * @brief SignUp::clearMSG 清除输入框
 */
void SignUp::clearMSG()
{
    this->ui->lineEdit_Username->setText("");
    this->ui->lineEdit_Passwd->setText("");
}
