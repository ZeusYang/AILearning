#include "ClientdDB.h"
#include <QSqlError>
#include <QDebug>

QSqlDatabase ClientdDB::database;
QString ClientdDB::databaseName = "information.db";

bool ClientdDB::openDatabase()
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(databaseName);
    if(database.open()){
        return true;
    }
    else{
        qDebug() << "Open database error!";
        return false;
    }
}

bool ClientdDB::createTable()
{
    QSqlQuery query(database);
    // 先判断表是否存在
    bool isTableExist = query.exec(
                QString("SELECT COUNT(*) FROM client;"));
    if(isTableExist) {
        qDebug() << "Table already exist!";
        //query.exec("DROP TABLE client;");
        return false;
    }
    else{
        if(!query.exec("CREATE TABLE client("
                   "id      INT(10) PRIMARY KEY,"
                   "name    VARCHAR(30),"
                   "gender  CHAR(1) NOT NULL,"
                   "state   VARCHAR(3) NOT NULL,"
                   "ipaddr  VARCHAR(15),"
                   "score   INT(12) DEFAULT '0',"
                   "pwd     VARCHAR(30) NOT NULL"
                       ");")){
            qDebug() << "Creation error!";
            qDebug() << query.lastError();
        }
        query.exec("INSERT INTO client VALUES"
                   "(0,'LiMing','M','Off','192.168.142.129','20','dest');");
        query.exec("INSERT INTO client VALUES"
                   "(1,'LiuTao','F','Off','192.168.142.119','30','asasxa');");
        query.exec("INSERT INTO client VALUES"
                   "(2,'Kim Scar','M','Off','192.168.142.142','120','desaxasst');");
        query.exec("INSERT INTO client VALUES"
                   "(3,'JinShijia','M','Off','192.168.142.152','412','fasdqxq');");
        query.exec("INSERT INTO client VALUES"
                   "(4,'Huge','M','On','192.168.142.137','57','xsasbgbnvc');");
        query.exec("INSERT INTO client VALUES"
                   "(5,'LiuYifei','F','Off','192.168.142.112','75','opioiiu');");
        query.exec("INSERT INTO client VALUES"
                   "(6,'DengJiajia','F','On','192.168.142.91','26','54511');");
        query.exec("INSERT INTO client VALUES"
                   "(7,'Zhaoji','F','On','192.168.142.251','117','aizhanbo');");
        query.exec("INSERT INTO client VALUES"
                   "(8,'LouYixiao','F','Off','192.168.142.12','91','4895210');");
        return true;
    }
}

