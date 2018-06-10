#ifndef VIGENERE_H
#define VIGENERE_H
#include "Encryption.h"

class Vigenere : public Encryption
{
public:
    Vigenere();
    virtual ~Vigenere();

    virtual QString EncodeMessage(const QString &message);
    virtual QString DecodeMessage(const QString &message);

private:
    QString key;
    std::map<QChar,int> table;
    std::map<QChar,std::vector<QChar>> encryp;
    const QString str = "abcdefghijklmnopqrstuvwxyz";
};

#endif // VIGENERE_H
