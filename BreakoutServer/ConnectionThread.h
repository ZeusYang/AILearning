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
    int socketDescriptor;

    ConnectionThread(int socketDes, QObject *parent = nullptr);
    ~ConnectionThread();
    void run();

signals:
    void revData(QString, QByteArray);
    void sendDat(QByteArray data, int id);
    void disconnectTCP(int );

private slots:
    void sendData(QByteArray data, int id);
    void recvData(QString, QByteArray);
    void disconnectToHost();

private:
    ConnectionSocket *socket;
};

#endif // CONNECTIONTHREAD_H
