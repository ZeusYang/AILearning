#ifndef ENCRYPTION_H
#define ENCRYPTION_H
#include <QObject>
#include <bitset>

class Encryption
{
public:
    enum MODE{ECB=0,CBC=1};

    Encryption();
    void setMode(int index);

    virtual ~Encryption();
    virtual QString SetKey(const QString &key);
    virtual QString SetInitVec(const QString &target);

    virtual QString EncodeMessage(const QString &message);
    virtual QString DecodeMessage(const QString &message);
protected:
    MODE mode;
};

#endif // ENCRYPTION_H
