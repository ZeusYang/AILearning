#include "Window.h"
#include "ui_Window.h"
#include "Server.h"
#include "ClientdDB.h"
#include "MySqlQueryModel.h"
#include <QHostInfo>
#include <QHostAddress>
#include <QSqlError>
#include <QTextStream>

Window::Window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);

    // 本地信息
    ui->terminalPlainTextEdit->appendPlainText(this->getInfoHost());

    // 启动服务器
    server = new Server(this);
    server->listen(QHostAddress::Any, 6666);
    connect(server,&Server::showMessage,this,&Window::showMessage);

    QString initMsg = QString("Establishing tcp socket for server...\n");
    initMsg += QString("Begin to listen (port:6666)...\n");
    initMsg += QString("Waiting for the tcp connection...\n");
    ui->terminalPlainTextEdit->appendPlainText(initMsg);

    // 数据库
    ClientdDB::openDatabase();
    ClientdDB::createTable();
    dataModel = new MySqlQueryModel(this);
    dataModel->setQuery("SELECT * FROM client;");
    static const std::vector<QString> headers = {tr("ID"),tr("User Name"),tr("Gender"),
                                                 tr("State"),tr("IP Address"),tr("Best Score"),
                                                 tr("Password")};
    for(uint x = 0;x < headers.size();++x){
        dataModel->setHeaderData(x,Qt::Horizontal,headers[x]);
    }
    ui->clientTableView->setStyleSheet("*{\n"
                                       "font: \"Consolas\" 12pt;\n"
                                       "}\n");
    ui->clientTableView->setModel(dataModel);
    ui->clientTableView->resizeColumnsToContents();
    ui->clientTableView->horizontalHeader()->setFont(QFont("Consolas",12));
    ui->clientTableView->verticalHeader()->hide();
    ui->clientTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//均分列
    updateTable();
}

Window::~Window()
{
    delete ui;
}

void Window::revData(ConnectionThread* thread, QString peerHost, QByteArray data)
{
    QString msg = tr("Message From %1, Length %2:\n").arg(peerHost).arg(data.length());
    msg += QString(data);
    ui->terminalPlainTextEdit->appendPlainText(msg);
    parseMessage(thread, QString(data));
}

void Window::showMessage(QString message)
{
    ui->terminalPlainTextEdit->appendPlainText(message);
}

void Window::showConnection()
{
    QString message = tr("Connection success.");
    showMessage(message);
}

void Window::showDisconnection(ConnectionThread* thread,
                               QString address, int socketDescriptor)
{
    /* remove disconnect socketdescriptor from list */
    server->socketList.removeAll(socketDescriptor);
    QString message = tr("%1 disconnected.").arg(address);
    showMessage(message);
    offLine(thread->id);
}

void Window::updateTable() const
{
    dataModel->setQuery("SELECT * FROM client;");
    QSqlQuery query(ClientdDB::database);
    //更新在线人数
    query.exec("SELECT COUNT(*) FROM client"
               " WHERE client.state='On';");
    query.next();
    int onPersons = query.value(0).toInt();
    ui->onlineLineEdit->setText(tr("%1").arg(onPersons));
    //更新客户总人数
    query.exec("SELECT COUNT(*) FROM client;");
    query.next();
    int cliensTotal = query.value(0).toInt();
    ui->clientLineEdit->setText(tr("%1").arg(cliensTotal));

}

int Window::registerClient(QString target, int socket)
{
    QString responding;
    //注册->0 name password gender
    QStringList record = target.split(" ");
    QString name = record.at(1);
    QString password = record.at(2);
    QString gender = record.at(3);
    //先判断是否存在
    QSqlQuery query(ClientdDB::database);
    query.exec(tr("SELECT COUNT(*) FROM client "
                  "WHERE client.name='%1';").arg(name));
    query.next();
    if(query.value(0).toInt() > 0){
        responding = tr("0 0 %1").arg("Account has already existed");
        sendMessage(responding,socket);
        return -1;
    }

    //获取编号
    int number = 0;
    query.exec("SELECT COUNT(*) FROM client;");
    query.next();
    number = query.value(0).toInt();

    //执行插入
    query.exec(tr("INSERT INTO client VALUES"
                             "(%1,'%2','%3','On','192.168.142.231','0','%4');")
                          .arg(number).arg(name).arg(gender).arg(password));

    onLine(name);
    this->updateTable();
    //成功注册，反馈
    responding = tr("0 1");
    sendMessage(responding,socket);
    return number;
}

int Window::loginClient(QString target, int socket)
{
    //登陆->1 name password
    QString responding;
    QStringList record = target.split(" ");
    QString name = record.at(1);
    QString password = record.at(2);
    QSqlQuery query(ClientdDB::database);
    //用户是否存在
    query.exec(tr("SELECT COUNT(*) FROM client "
                  "WHERE client.name='%1';").arg(name));
    query.next();
    if(query.value(0).toInt() <= 0){
        responding = tr("1 0 %1").arg("Account does not exist.");
        sendMessage(responding,socket);
        return -1;
    }

    //密码是否匹配
    query.exec(tr("SELECT client.id,client.name,client.pwd"
                  " FROM client WHERE client.name='%1';").arg(name));
    query.next();
    if(query.value(2).toString() != password){
        responding = tr("1 0 %1").arg("Pasword error.");
        sendMessage(responding,socket);
        return -1;
    }

    //上线了
    onLine(name);
    responding = tr("1 1");
    sendMessage(responding,socket);
    return query.value(0).toInt();
}

void Window::refreshScore(QString target, int socket)
{
    //2 name password score
    QStringList record = target.split(" ");
    QString name = record.at(1);
    int scores = record.at(2).toInt();
    int curScore = 0;

    //当前最高分
    QSqlQuery query(ClientdDB::database);
    query.exec(tr("SELECT client.score"
                  " FROM client WHERE client.name='%1';").arg(name));
    query.next();
    curScore = query.value(0).toInt();
    //比当前最高分才刷新
    if(scores > curScore){
        query.exec(tr("UPDATE client SET score=%1"
                      " WHERE client.name='%2';").arg(scores).arg(name));
        updateTable();
    }
    else return;
}

void Window::rankList(QString target, int socket)
{
    //3 name:score name:score name:score name:score name:score name:score
    //name:score name:score name:score name:score name:rank
    QStringList record = target.split(" ");
    QString name = record.at(1);
    QSqlQuery query(ClientdDB::database);
    query.exec("SELECT client.name,client.score FROM client"
               " ORDER BY client.score DESC;");
    query.next();
    QString responding = "3";
    for(auto x = 0;x < 10;++x){
        responding += (" " +
                       query.value(0).toString() +
                       ":" +
                       tr("%1").arg(query.value(1).toInt()));
        query.next();
    }
    query.first();
    int index = 1;
    //查看自己的排名
    while(true){
        if(query.value(0).toString() == name){
            responding += (" " + name + tr(":%1").arg(index));
            break;
        }
        ++index;
        if(!query.next())break;
    }
    sendMessage(responding,socket);
}

void Window::sendMessage(QString message, int socket)
{
    //发送信息
    emit sendData(message.toLocal8Bit(),socket);
}

void Window::onLine(QString name)
{
    QSqlQuery query(ClientdDB::database);
    bool ret = query.exec(tr("UPDATE client SET state='On'"
                             "WHERE client.name='%1';").arg(name));
    if(!ret){
        qDebug() << "Update online error!"
                 << query.lastError();
    }
    updateTable();
}

void Window::offLine(int id)
{
    QSqlQuery query(ClientdDB::database);
    bool ret = query.exec(tr("UPDATE client SET state='Off'"
                             "WHERE client.id=%1;").arg(id));
    if(!ret){
        qDebug() << "Update offline error!";
    }
    updateTable();
}

void Window::parseMessage(ConnectionThread* thread, QString target)
{
    if(target.at(0) == '0'){//注册
        int id = registerClient(target, thread->socketDescriptor);
        if(id != -1){
            thread->id = id;
            server->threads[id] = thread;
        }
    }
    else if(target.at(0) == '1'){//登陆
        int id = loginClient(target, thread->socketDescriptor);
        if(id != -1){
            thread->id = id;
            server->threads[id] = thread;
        }
    }
    else if(target.at(0) == '2'){//游戏结束
        refreshScore(target, thread->socketDescriptor);
    }
    else if(target.at(0) == '3'){//排行榜
        rankList(target,thread->socketDescriptor);
    }
}

QString Window::getInfoHost() const
{
    QString result;
    //QHostInfo类作用，获取主机名，也可以通过主机名来查找IP地址，或者通过IP地址来反向查找主机名。
    QString localHostName = QHostInfo::localHostName();
    result += tr("LocalHostName:%1\n").arg(localHostName);

    QStringList record;
    //获取IP地址
    QHostInfo info = QHostInfo::fromName(localHostName);
    foreach(QHostAddress address, info.addresses()){
        if (address.protocol() == QAbstractSocket::IPv4Protocol){
            result += tr("IPv4 Address:%1\n").arg(address.toString());
            record.append(address.toString());
        }
    }

    ui->IPv4ComboBox->addItems(record);
    return result;
}
