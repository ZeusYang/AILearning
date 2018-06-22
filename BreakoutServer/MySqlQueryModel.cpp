#include "MySqlQueryModel.h"
#include <QFont>

MySqlQueryModel::MySqlQueryModel(QObject *parent)
    :QSqlQueryModel(parent)
{
}

QVariant MySqlQueryModel::data(const QModelIndex &item, int role) const
{
    QVariant value = QSqlQueryModel::data(item, role);
    if(role ==  Qt::TextAlignmentRole ){
        value   =   (Qt::AlignCenter);
        return value;
    }
    else if(role == Qt::FontRole){
        value   =   (QFont("Consolas",12));
        return value;
    }
    return value;
}
