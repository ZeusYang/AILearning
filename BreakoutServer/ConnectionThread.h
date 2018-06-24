#ifndef CONNECTIONTHREAD_H
#define CONNECTIONTHREAD_H
#include <QThread>
#include <QObject>
#include <QtNetwork>
#include "ConnectionSocket.h"

class ConnectionThread : public QThread
{
    Q_OBJECT
public:
    int id;
    int socketDescriptor;

    ConnectionThread(int socketDes, QObject *parent = nullptr);
    ~ConnectionThread();
    void run();
    ConnectionSocket* getSocket();

signals:
    void revData(ConnectionThread*, QString, QByteArray);
    void sendDat(QByteArray data, int ids);
    void disconnectTCP(ConnectionThread*, QString, int );

private slots:
    void sendData(QByteArray data, int ids);
    void recvData(QString, QByteArray);
    void disconnectToHost();

private:
    ConnectionSocket *socket;
};

#endif // CONNECTIONTHREAD_H
