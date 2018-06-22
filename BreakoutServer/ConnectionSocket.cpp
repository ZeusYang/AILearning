#include "ConnectionSocket.h"
#include <QHostAddress>
#include <QDebug>

ConnectionSocket::ConnectionSocket(int socketDesc, QObject *parent)
    : QTcpSocket(parent), socketDescriptor(socketDesc)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(recvData()));
}

void ConnectionSocket::sendMsg(QByteArray msg, int id)
{
    if (id == socketDescriptor){
        this->write(msg);
    }
}

void ConnectionSocket::recvData()
{
    // 获取数据包
    QByteArray data;
    QString peerAddr;
    data = this->readAll();

    // 获取ip地址
    QString temp = this->peerAddress().toString();
    peerAddr = temp.remove(0, 7);
    emit revData(peerAddr, data);
}
