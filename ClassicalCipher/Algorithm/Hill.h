#ifndef HILL_H
#define HILL_H
#include "Encryption.h"

class Hill : public Encryption
{
public:
    Hill();
    virtual ~Hill();
    virtual QString EncodeMessage(const QString &message);
    virtual QString DecodeMessage(const QString &message);

private:
    const int key[3][3] ={
        {17,17,5},
        {21,18,21},
        {2,2,19}
    };
    const int reverkey[3][3] = {
        {4,9,15},
        {15,17,6},
        {24,0,17}
    };
    std::map<QChar,int> table;
    const QString str = "abcdefghijklmnopqrstuvwxyz";

    QString PreProcess(const QString &target);
};

#endif // HILL_H
