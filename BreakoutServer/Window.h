#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QSqlQueryModel>
#include "ClientdDB.h"

/*
 * 协议：
 * 客户端->服务端
 * 注册->0 name password gender
 * 登陆->1 name password
 * 游戏结束->2 name score
 * 查看排行榜->3 name
 *
 * 服务端->客户端
 *注册->0 1或0(1是成功) 失败消息
 *登陆->1 1或0(1是成功) 失败消息
 *排行榜-
 * 3 name:score name:score name:score name:score name:score
 * name:score name:score name:score name:score name:score
 * name:rank
 */

namespace Ui {
class Window;
}
class Server;
class MySqlQueryModel;
class ConnectionThread;
class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = nullptr);
    ~Window();

signals:
    void sendData(QByteArray data, int id);

public slots:
    void revData(ConnectionThread*, QString peerHost, QByteArray data);
    void showMessage(QString message);

private slots:
    // 消息
    //void sendMsg();
    // 连接
    void showConnection();
    void showDisconnection(ConnectionThread*, QString address, int socketDescriptor);

private:
    Ui::Window *ui;
    Server *server;
    MySqlQueryModel *dataModel;

    void updateTable()const;
    void parseMessage(ConnectionThread* thread, QString target);
    int registerClient(QString target, int socket);
    int loginClient(QString target, int socket);
    void refreshScore(QString target, int socket);
    void rankList(QString target, int socket);

    void sendMessage(QString message,int socket);

    void onLine(QString name);
    void offLine(int id);

    QString getInfoHost() const;
};

#endif // WINDOW_H
