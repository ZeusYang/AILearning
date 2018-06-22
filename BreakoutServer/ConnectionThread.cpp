#include "ConnectionThread.h"
#include <QDebug>

ConnectionThread::ConnectionThread(int socketDes, QObject *parent) :
    QThread(parent), socketDescriptor(socketDes), socket(nullptr) {}

ConnectionThread::~ConnectionThread()
{
    socket->close();
    if(socket)delete socket;
    socket = nullptr;
}

void ConnectionThread::run()
{
    // 创建一个新的连接套接字
    socket = new ConnectionSocket(socketDescriptor, 0);

    if (!socket->setSocketDescriptor(socketDescriptor)){
        qDebug() << "Create socket error!";
        return ;
    }

    // 断开连接
    connect(socket, &ConnectionSocket::disconnected,
            this, &ConnectionThread::disconnectToHost);

    // 接收数据
    connect(socket, SIGNAL(revData(QString, QByteArray)),
            this, SLOT(recvData(QString, QByteArray)));

    // 发送数据
    connect(this, SIGNAL(sendDat(QByteArray, int)),
            socket, SLOT(sendMsg(QByteArray, int)));

    exec();
}

void ConnectionThread::sendData(QByteArray data, int id)
{
    if (data == "") return ;
    emit sendDat(data, id);
}

void ConnectionThread::recvData(QString peerAddr, QByteArray data)
{
    emit revData(peerAddr, data);
}

void ConnectionThread::disconnectToHost()
{
    emit disconnectTCP(socketDescriptor);
    socket->disconnectFromHost();
}
