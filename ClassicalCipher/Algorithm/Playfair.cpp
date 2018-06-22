#include "Playfair.h"
#include <set>
#include <QDebug>

Playfair::Playfair()
{
    key = QString("MONARJCHY");
    setKey(key);
}

Playfair::~Playfair()
{

}

void Playfair::setKey(const QString &target){
    //去除重复
    QString ts = target.toUpper();
    std::string tmp = ts.toStdString();
    std::string record;
    std::set<char> flag;
    for(uint x = 0;x < tmp.size();++x){
        if(tmp[x] == 'J'){
            tmp[x] = 'I';
        }
        if(flag.find(tmp[x]) == flag.end()){
            record += tmp[x];
            flag.insert(tmp[x]);
        }
    }
    key = QString::fromStdString(record);
    //生成字母矩阵
    int index = 0, index1 = 0;
    for(int x = 0;x < 5;++x){
        for(int y = 0;y < 5;++y){
            if(index < key.size()){
                matrix[x][y] = key.at(index++);
            }
            else{
                while(key.contains(str[index1]))++index1;
                matrix[x][y] = str[index1++];
            }
        }
    }
    //存到字母表
    for(int x = 0;x < 5;++x){
        for(int y = 0;y < 5;++y){
            table[matrix[x][y]] = std::pair<int,int>(x,y);
            if(matrix[x][y] == QChar('I')){
                table[QChar('J')] = std::pair<int,int>(x,y);
            }
        }
    }
}

QString Playfair::EncodeMessage(const QString &message)
{
    QString result;
    std::vector<std::pair<QChar,QChar>> record = PreProcess(message);
    // 加密
    for(auto it = record.begin();it != record.end();++it){
        //获取坐标
        std::pair<int,int> p1,p2;
        p1 = table[it->first];
        p2 = table[it->second];
        if(p1.first == p2.first){//同一行的处理
            result.push_back(matrix[p1.first][(p1.second+1)%5]);
            result.push_back(matrix[p2.first][(p2.second+1)%5]);
        }
        else if(p1.second == p2.second){//同一列的处理
            result.push_back(matrix[(p1.first+1)%5][p1.second]);
            result.push_back(matrix[(p2.first+1)%5][p2.second]);
        }
        else{//其他情况处理
            result.push_back(matrix[p1.first][p2.second]);
            result.push_back(matrix[p2.first][p1.second]);
        }
    }
    return result;
}

QString Playfair::DecodeMessage(const QString &message)
{
    QString result;
    int cur = 0,next = 0;
    while(cur < message.size()){
        next = cur + 1;
        std::pair<int,int> p1,p2;
        p1 = table[message[cur]];
        p2 = table[message[next]];
        if(p1.first == p2.first){//同一行
            p1.second -= 1;
            if(p1.second < 0)p1.second = 4;
            result.push_back(matrix[p1.first][p1.second]);
            p2.second -= 1;
            if(p2.second < 0)p2.second = 4;
            result.push_back(matrix[p2.first][p2.second]);
        }
        else if(p1.second == p2.second){//同一列
            p1.first -= 1;
            p2.first -= 1;
            if(p1.first < 0)p1.first = 4;
            if(p2.first < 0)p2.first = 4;
            result.push_back(matrix[p1.first][p1.second]);
            result.push_back(matrix[p2.first][p2.second]);
        }
        else{//其他情况
            result.push_back(matrix[p1.first][p2.second]);
            result.push_back(matrix[p2.first][p1.second]);
        }
        cur += 2;
    }
    return result.toLower();
}

std::vector<std::pair<QChar,QChar>>
Playfair::PreProcess(const QString &target)
{
    //对信息预处理
    QString record;
    //只留下字母，将J替换成I
    for(uint x = 0;x < target.size();++x){
        if(target[x].isLetter()){
            if(target[x] == QChar('J'))
                record.push_back(QChar('I'));
            else
                record.push_back(target[x]);
        }
    }
    //转成大写
    record = record.toUpper();

    std::vector<std::pair<QChar,QChar>> result;
    int cur = 0,next = 0;
    while(cur < record.size()){
        std::pair<QChar,QChar> re;
        re.first = record[cur];
        next = cur + 1;
        // 为奇数则填充
        if(next >= record.size()){
            re.second = QChar('X');
            cur += 1;
        }
        // 相等则插入一个X
        else if(record[cur] == record[next]){
            re.second = QChar('X');
            ++cur;
        }
        else{
            re.second = record[next];
            cur += 2;
        }
        result.push_back(re);
    }
    return result;
}
