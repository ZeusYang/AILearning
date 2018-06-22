#ifndef MYSQLQUERYMODEL_H
#define MYSQLQUERYMODEL_H
#include <QSqlQueryModel>

class MySqlQueryModel : public QSqlQueryModel
{
public:
    explicit MySqlQueryModel(QObject *parent = nullptr);
    QVariant data(const QModelIndex &index, int role) const override;
};

#endif // MYSQLQUERYMODEL_H
