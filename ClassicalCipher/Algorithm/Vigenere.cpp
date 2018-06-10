#include "Vigenere.h"

Vigenere::Vigenere()
{
    key = QString("deceptive");
    for(uint x = 0;x < str.size();++x){
        table[str[x]] = x;
    }
    //初始化加密表
    for(uint x = 0;x < 26;++x){
        std::vector<QChar> record;
        for(uint y = 0;y < 26;++y){
            record.push_back(str[(y+x)%26]);
        }
        encryp[str[x]] = record;
    }
}

Vigenere::~Vigenere() {}

QString Vigenere::EncodeMessage(const QString &message)
{
    QString result;
    QString record = message.toLower();
    int index = 0;
    for(auto it = record.begin();it != record.end();++it){
        if(it->isLetter()){
            const std::vector<QChar> &tmp = encryp[key[index]];
            result.push_back(tmp[table[*it]]);
            index = (index+1)%key.size();
        }
        else result.push_back(*it);
    }
    return result;
}

QString Vigenere::DecodeMessage(const QString &message)
{
    QString result;
    int index = 0;
    for(auto it = message.begin();it != message.end();++it){
        if(it->isLetter()){
            const std::vector<QChar> &tmp = encryp[key[index]];
            for(uint x = 0;x < tmp.size();++x){
                if(tmp[x] == *it){
                    result.push_back(str[x]);
                    break;
                }
            }
            index = (index+1)%key.size();
        }
        else result.push_back(*it);
    }
    return result;
}
