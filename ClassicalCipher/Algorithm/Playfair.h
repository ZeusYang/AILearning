#ifndef PLAYFAIR_H
#define PLAYFAIR_H
#include "Encryption.h"

class Playfair : public Encryption
{
public:
    Playfair();
    virtual ~Playfair();

    void setKey(const QString &target);

    virtual QString EncodeMessage(const QString &message);
    virtual QString DecodeMessage(const QString &message);

private:
    QString key;
    QChar matrix[5][5];//字母矩阵
    std::map<QChar,std::pair<int,int>> table;
    const std::string str = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    std::vector<std::pair<QChar,QChar>> PreProcess(const QString &target);
};

#endif // PLAYFAIR_H
