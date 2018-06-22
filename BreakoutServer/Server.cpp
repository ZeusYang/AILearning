#include "server.h"

Server::Server(QObject *parent)
    :QTcpServer(parent)
{
    window = qobject_cast<Window*>(parent);
}

Server::~Server() {}

void Server::incomingConnection(int socketDescriptor){
    // 创建一个新的客户连接线程
    socketList.append(socketDescriptor);
    ConnectionThread *thread = new ConnectionThread(socketDescriptor, nullptr);

    connect(thread, SIGNAL(started()),
            window, SLOT(showConnection()));
    connect(thread, SIGNAL(disconnectTCP(int)),
            window, SLOT(showDisconnection(int)));
    connect(thread, SIGNAL(revData(QString, QByteArray)),
            window, SLOT(revData(QString, QByteArray)));
    connect(window, SIGNAL(sendData(QByteArray, int)),
            thread, SLOT(sendData(QByteArray, int)));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread->start();
}

