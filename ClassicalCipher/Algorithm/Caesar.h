#ifndef CAESAR_H
#define CAESAR_H
#include "Encryption.h"
#include <map>

class Caesar : public Encryption
{
public:
    Caesar();
    virtual ~Caesar();

    // encryption
    virtual QString EncodeMessage(const QString &message);
    virtual QString DecodeMessage(const QString &message);
private:
    std::map<char,int> table;
    const std::string str = "abcdefghijklmnopqrstuvwxyz";
};

#endif // CAESAR_H
