#include "Caesar.h"
#include <string>
#include <QDebug>

Caesar::Caesar()
    :Encryption()
{
    // 初始化
    for(uint x = 0;x < str.size();++x){
        table[str[x]] = x;
    }
}

Caesar::~Caesar(){}

QString Caesar::EncodeMessage(const QString &message){
    QString result;
    std::string target = message.toStdString();
    std::string record;
    // 加密
    for(auto it = target.begin();it != target.end();++it){
        int nu;
        if(isalpha(*it)) {
            nu = (table[*it] + 3)%26;
            record += str[nu];
        }
        else record += *it;
    }
    result = result.fromStdString(record);
    return result;
}

QString Caesar::DecodeMessage(const QString &message){
    QString ts = message.toLower();
    QString result;
    std::string target = ts.toStdString();
    std::string record;
    // 解密
    for(auto it = target.begin();it != target.end();++it){
        if(isalpha(*it)){
            int num = table[*it] - 3;
            if(num < 0)num = 26+num;
            record += str[num];
        }
        else record += *it;
    }
    result = result.fromStdString(record);
    return result;
}
