#include "Hill.h"
#include <QDebug>

Hill::Hill()
{
    for(uint x = 0;x < str.size();++x){
        table[str[x]] = x;
    }
}

Hill::~Hill() {}

QString Hill::EncodeMessage(const QString &message){
    QString record = PreProcess(message);
    QString result;
    uint i1=0,i2=0,i3=0;
    uint size = record.size();
    // 加密
    while(i1 < size){
        QChar p1,p2,p3;
        i2 = i1 + 1;
        i3 = i1 + 2;
        p1 = record[i1];
        p2 = record[i2];
        p3 = record[i3];
        int c1 = (key[0][0]*table[p1]+key[1][0]*table[p2]+key[2][0]*table[p3])%26;
        int c2 = (key[0][1]*table[p1]+key[1][1]*table[p2]+key[2][1]*table[p3])%26;
        int c3 = (key[0][2]*table[p1]+key[1][2]*table[p2]+key[2][2]*table[p3])%26;
        result.push_back(str[c1]);
        result.push_back(str[c2]);
        result.push_back(str[c3]);
        i1 += 3;
    }
    return result;
}

QString Hill::DecodeMessage(const QString &message)
{
    QString result;
    int i1=0,i2=0,i3=0;
    while(i1 < message.size()){
        QChar p1,p2,p3;
        i2 = i1 + 1;
        i3 = i1 + 2;
        p1 = message[i1];
        p2 = message[i2];
        p3 = message[i3];
        int c1 = (reverkey[0][0]*table[p1]+reverkey[1][0]*table[p2]+reverkey[2][0]*table[p3])%26;
        int c2 = (reverkey[0][1]*table[p1]+reverkey[1][1]*table[p2]+reverkey[2][1]*table[p3])%26;
        int c3 = (reverkey[0][2]*table[p1]+reverkey[1][2]*table[p2]+reverkey[2][2]*table[p3])%26;
        result.push_back(str[c1]);
        result.push_back(str[c2]);
        result.push_back(str[c3]);
        i1 += 3;
    }
    return result;
}

QString Hill::PreProcess(const QString &target)
{
    QString result;
    for(uint x = 0;x < target.size();++x){
        if(target[x].isLetter()){
            result.push_back(target[x]);
        }
    }
    int len = result.size();
    if(len % 3 != 0){
        if(len%3 == 1)result.push_back("xx");
        else if(len%3 == 2)result.push_back("x");
    }
    return result;
}
