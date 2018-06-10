#include "Affine.h"
#include <QDebug>

Affine::Affine()
{
    for(int x = 0;x < str.size();++x){
        table[str[x]] = x;
    }
    a = 11;
    b = 5;
    a_inver = 19;
}

Affine::~Affine() {}

QString Affine::EncodeMessage(const QString &message)
{
    QString result;
    for(auto it = message.begin();it != message.end();++it){
        if(it->isLetter()){
             result.push_back(str[(table[*it]*a+b)%26]);
        }
        else result.push_back(*it);
    }
    return result;
}

QString Affine::DecodeMessage(const QString &message)
{
    QString result;
    for(auto it = message.begin();it != message.end();++it){
        if(it->isLetter()){
            int index =  ((table[*it]-b)*a_inver)%26;
            if(index < 0)index += 26;
            result.push_back(str[index]);
        }
        else result.push_back(*it);
    }
    return result;
}
