#ifndef CLIENTDDB_H
#define CLIENTDDB_H
#include <QSqlDatabase>
#include <QSqlQuery>

class ClientdDB
{
public:
    static QSqlDatabase database;

    static QString databaseName;

    static bool openDatabase();

    static bool createTable();

private:
    ClientdDB(){}
};

#endif // CLIENTDDB_H
