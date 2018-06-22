#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QSqlQueryModel>

namespace Ui {
class Window;
}
class Server;
class MySqlQueryModel;
class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = nullptr);
    ~Window();

signals:
    void sendData(QByteArray data, int id);

public slots:
    void revData(QString peerHost, QByteArray data);

private slots:
    // 消息
    //void sendMsg();

    // 连接
    void showConnection();
    void showDisconnection(int socketDescriptor);

private:
    Ui::Window *ui;
    Server *server;
    MySqlQueryModel *dataModel;
    int count;

    QString getInfoHost() const;
};

#endif // WINDOW_H
