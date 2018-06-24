#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QHostAddress>
#include <vector>
#include "Window.h"
#include "ConnectionThread.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    std::map<int,ConnectionThread*> threads;
    QList<int> socketList;

    explicit Server(QObject *parent = nullptr);
    ~Server();
signals:
    void showMessage(QString message);
private:
    void incomingConnection(int socketDescriptor) override;
    Window *window;
};

#endif // SERVER_H
