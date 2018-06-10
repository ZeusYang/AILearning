#ifndef ENCRYPTION_H
#define ENCRYPTION_H
#include<QObject>

class Encryption
{
public:
    Encryption();
    virtual ~Encryption();

    virtual QString EncodeMessage(const QString &message);
    virtual QString DecodeMessage(const QString &message);
};

#endif // ENCRYPTION_H
