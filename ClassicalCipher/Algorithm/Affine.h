#ifndef AFFINE_H
#define AFFINE_H
#include "Encryption.h"

class Affine : public Encryption
{
public:
    Affine();
    virtual ~Affine();

    virtual QString EncodeMessage(const QString &message);
    virtual QString DecodeMessage(const QString &message);

private:
    int a,b;
    int a_inver;
    std::map<QChar,int> table;
    const QString str = "abcdefghijklmnopqrstuvwxyz";
};

#endif // AFFINE_H
