#ifndef CONNECTIONSOCKET_H
#define CONNECTIONSOCKET_H
#include <QTcpSocket>

class ConnectionSocket : public QTcpSocket
{
    Q_OBJECT
public:
    QString address;
    explicit ConnectionSocket(int socket, QObject *parent = nullptr);

signals:
    void revData(QString, QByteArray);

public slots:
    void recvData();
    void sendMsg(QByteArray msg, int id);

private:
    int socketDescriptor;
};

#endif // CONNECTIONSOCKET_H
