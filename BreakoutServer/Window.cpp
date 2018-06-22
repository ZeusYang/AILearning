#include "Window.h"
#include "ui_Window.h"
#include "Server.h"
#include "ClientdDB.h"
#include "MySqlQueryModel.h"
#include <QHostInfo>
#include <QHostAddress>
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

    QString initMsg = QString("Establishing tcp socket for server...\n");
    initMsg += QString("Begin to listen (port:6666)...\n");
    initMsg += QString("Waiting for the tcp connection...\n");
    ui->terminalPlainTextEdit->appendPlainText(initMsg);
    count = 0;

    // 数据库
    ClientdDB::openDatabase();
    ClientdDB::createTable();
    dataModel = new MySqlQueryModel(this);
    dataModel->setQuery("SELECT * FROM client");
    static const std::vector<QString> headers = {tr("ID"),tr("User Name"),tr("Gender"),
                                                tr("State"),tr("IP Address"),tr("Best Score"),
                                                 tr("Password")};
    for(auto x = 0;x < headers.size();++x){
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
}

Window::~Window()
{
    delete ui;
}

void Window::revData(QString peerHost, QByteArray data)
{
    QString msg = tr("Message From %1, Length %2:\n").arg(peerHost).arg(data.length());
    msg += QString(data);
    ui->terminalPlainTextEdit->appendPlainText(msg);
}

//void Window::sendMsg()
//{
//    if(server->socketList.isEmpty()){
//        qDebug() << "Sockt lists is empty!";
//        return;
//    }
//    QString message("This is a testing message skxalsn lamkl xmlaqlxwqqwxqwq"
//                    "asxamklsmndxklqn kwxnqlkjwnx wqkoxqm;xwq"
//                    "asnmklanmlckaj lkmx ;lqwx"
//                    "ansklanckla sjxakljslkxa slkxajkjslxkjq lijwlxkqjlkmsalkncl ansxa"
//                    "xnkjasjlc ajsklxjlksnxaklnxa lmxklsjxqlkjwxioqjwonxhqjbnxkjbqaxasa"
//                    "xsaklchakljcujaioshvnajkbvkjasbfkahklxjlasxlkanslkxnalkssnxklaslxna"
//                    "asxalksjlvajjsncklansvkashlxkanlsbnvkjhqokxn;jqbhoicbkambckajhjsxal"
//                    "ashciasoihnlkfajdlajsxakljcvliqx qm lxkijqmplwx ;ql"
//                    "xsklj colksnmxo qwjiixnq bck qnxohwjnxokqnhqxwqxqccqvwqwvfq"
//                    "xqwxkqhnwfqojxiohnqwonbfcqjphncn pcvqhxj; qlkxmqwljodfioqhnwkc"
//                    "wxhnqkohwvopqiwvhnjkdsbvkjdbvaskl;nhxacksjvbakjxshna"
//                    "xqwjhoihioqiwjfoqpbhgqghwxbqjhwvcajsvcab xagcfqahnxkq");

//    emit sendData(message.toLocal8Bit(),
//                  server->socketList.at(0));
//}

void Window::showConnection()
{
    ++count;
    ui->clientLineEdit->setText(tr("%1").arg(count));
}

void Window::showDisconnection(int socketDescriptor)
{
    --count;
    ui->clientLineEdit->setText(tr("%1").arg(count));
    /* remove disconnect socketdescriptor from list */
    server->socketList.removeAll(socketDescriptor);
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
    qDebug() << result;
    return result;
}

