#include "AES.h"
#include <sstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <QDebug>

AES::AES()
    :Encryption() {}

AES::~AES() {}

QString AES::SetKey(const QString &key)
{
    std::string record = key.toStdString();
    if(record.length() < 16){
        std::string tmp(16-record.length(),'0');
        record += tmp;
    }

    for(auto i = 0; i< 16; i++)
        this->key[i] = Byte(record[i]);
    return key;
}

QString AES::SetInitVec(const QString &target)
{
    std::string record = target.toStdString();
    if(record.length() < 16){
        std::string tmp(16-record.length(),'0');
        record += tmp;
    }

    for(auto i = 0; i< 16; i++)
        this->keyInitVec[i] = Byte(record[i]);
    return target;
}

QString AES::EncodeMessage(const QString &message)
{
    QString result;
    switch(mode){
    case MODE::ECB:
        result = EncodeECB(message);
        break;
    case MODE::CBC:
        result = EncodeCBC(message);
        break;
    }
    return result;
}

QString AES::DecodeMessage(const QString &message)
{
    QString result;
    switch(mode){
    case MODE::ECB:
        result = DecodeECB(message);
        break;
    case MODE::CBC:
        result = DecodeCBC(message);
        break;
    }
    return result;
}

QString AES::EncodeECB(const QString &message)
{
    QString result;
    std::string record;
    // 扩展密钥
    KeyExpansion(key, expansionKey);
    std::string text = message.toStdString();
    int groups = text.length()/16;
    Byte group[16];

    for(auto x = 0;x < groups;++x){
        // 转成byte数组
        for(auto y = 0;y < 16;++y){
            group[y] = Byte(text[x*16+y]);
        }
        // 加密
        EncryPerGroup(group,expansionKey);
        // 输出为16进制的形式
        for(auto y = 0;y < 16;++y){
            std::stringstream ioss;
            std::string temp;
            ioss << std::hex << group[y].to_ulong();
            ioss >> temp;
            record = record + temp + " ";
        }
    }
    //对剩余不足的补'\0'
    if(groups*16 < text.length()){
        std::string substr = text.substr(groups*16);
        substr += std::string(16-substr.size(),'\0');
        // 转成byte数组
        for(auto y = 0;y < 16;++y){
            group[y] = Byte(substr[y]);
        }
        // 加密
        EncryPerGroup(group,expansionKey);
        // 输出为16进制的形式
        for(auto y = 0;y < 16;++y){
            std::stringstream ioss;
            std::string temp;
            ioss << std::hex << group[y].to_ulong();
            ioss >> temp;
            record = record + temp + " ";
        }
    }
    result = QString::fromStdString(record);
    result = result.toUpper();
    return result;
}

QString AES::DecodeECB(const QString &message)
{
    QString result;
    std::string record;
    // 扩展密钥
    KeyExpansion(key, expansionKey);

    QStringList textList = message.split(" ");
    Byte group[16];

    for(auto x = 0;x < textList.size()-1;x += 16){
        // 转成byte数组
        for(auto y = 0;y < 16;++y){
            const char* sC = textList.at(x+y).toStdString().c_str();
            int num;
            std::sscanf(sC, "%X", &num);
            group[y] = Byte(num);
        }
        // 解密
        DecryPerGroup(group,expansionKey);
        // 输出为16进制的形式
        for(auto y = 0;y < 16;++y){
            record += this->BitsetToChar(group[y]);
        }
    }
    result = QString::fromStdString(record);
    return result;
}

QString AES::EncodeCBC(const QString &message)
{
    QString result;
    std::string record;
    // 扩展密钥
    KeyExpansion(key, expansionKey);
    std::string text = message.toStdString();
    int groups = text.length()/16;
    Byte group[16];

    for(auto x = 0;x < groups;++x){
        Byte cache_before;
        // 转成byte数组
        for(auto y = 0;y < 16;++y){
            cache_before = group[y];
            group[y] = Byte(text[x*16+y]);
            if(x == 0) group[y] ^= keyInitVec[y];
            else group[y] ^= cache_before;
        }
        // 加密
        EncryPerGroup(group,expansionKey);
        // 输出为16进制的形式
        for(auto y = 0;y < 16;++y){
            std::stringstream ioss;
            std::string temp;
            ioss << std::hex << group[y].to_ulong();
            ioss >> temp;
            record = record + temp + " ";
        }
    }
    //对剩余不足的补'\0'
    if(groups*16 < text.length()){
        std::string substr = text.substr(groups*16);
        substr += std::string(16-substr.size(),'\0');
        // 转成byte数组
        for(auto y = 0;y < 16;++y){
            Byte cache_before = group[y];
            group[y] = Byte(substr[y]);
            if(groups > 0) group[y] ^= cache_before;
            else group[y] ^= keyInitVec[y];
        }
        // 加密
        EncryPerGroup(group,expansionKey);
        // 输出为16进制的形式
        for(auto y = 0;y < 16;++y){
            std::stringstream ioss;
            std::string temp;
            ioss << std::hex << group[y].to_ulong();
            ioss >> temp;
            record = record + temp + " ";
        }
    }
    result = QString::fromStdString(record);
    result = result.toUpper();
    return result;
}

QString AES::DecodeCBC(const QString &message)
{
    QString result;
    std::string record;
    // 扩展密钥
    KeyExpansion(key, expansionKey);
    QStringList textList = message.split(" ");
    Byte group[16];
    Byte tmp_group[16];
    Byte cache_before[16];

    for(auto x = 0;x < textList.size()-1;x += 16){
        // 转成byte数组
        for(auto y = 0;y < 16;++y){
            const char* sC = textList.at(x+y).toStdString().c_str();
            int num;
            std::sscanf(sC, "%X", &num);
            cache_before[y] = group[y];
            group[y] = Byte(num);
            tmp_group[y] = group[y];
        }
        // 解密
        DecryPerGroup(tmp_group,expansionKey);
        // 输出为16进制的形式
        for(auto y = 0;y < 16;++y){
            if(x == 0)tmp_group[y] ^= keyInitVec[y];
            else tmp_group[y] ^= cache_before[y];
            record += this->BitsetToChar(tmp_group[y]);
        }
    }
    result = QString::fromStdString(record);
    return result;
}

void AES::EncryPerGroup(AES::Byte target[16], AES::Word expansionKey[44])
{
    // at first, a word for a col
    Word keyt[4];
    for(int i=0; i<4; ++i)
        keyt[i] = expansionKey[i];
    KeyRoundAdd(target,keyt);

    for(int round=1; round< 10; ++round){
        MapToSboxMtx(target);
        RowsShift(target);
        ColumnsMix(target);
        for(int i=0; i<4; ++i)
            keyt[i] = expansionKey[4*round+i];
        KeyRoundAdd(target, keyt);
    }

    // last round, DO NOT have MixCol
    MapToSboxMtx(target);
    RowsShift(target);
    for(int i=0; i<4; ++i)
        keyt[i] = expansionKey[40+i];
    KeyRoundAdd(target, keyt);
}

void AES::DecryPerGroup(AES::Byte target[16], AES::Word expansionKey[44])
{
    Word keyt[4];
    for(int i=0; i<4; ++i)
        keyt[i] = expansionKey[40+i];
    KeyRoundAdd(target, keyt);

    for(int round=9; round > 0; --round){
        RowsShiftInv(target);
        MapToSboxMtxInv(target);
        for(int i=0; i<4; ++i)
            keyt[i] = expansionKey[4*round+i];
        KeyRoundAdd(target, keyt);
        ColumnsMixInv(target);
    }

    // last round, DO NOT have InvMixCol
    RowsShiftInv(target);
    MapToSboxMtxInv(target);
    for(int i=0; i<4; ++i)
        keyt[i] = expansionKey[i];
    KeyRoundAdd(target, keyt);
}

std::string AES::BitsetToChar(const AES::Byte &target)
{
    std::string result;
    result.push_back(static_cast<char>(target.to_ulong()));
    return result;
}

AES::Word AES::ByteToWord(AES::Byte &k1, AES::Byte &k2,
                          AES::Byte &k3, AES::Byte &k4)
{
    //将四个字节压成一个字
    Word result(0x00000000);
    Word temp;

    temp = k1.to_ulong();
    temp <<= 24;
    result |= temp;

    temp = k2.to_ulong();
    temp <<= 16;
    result |= temp;

    temp = k3.to_ulong();
    temp <<= 8;
    result |= temp;

    temp = k4.to_ulong();
    result |= temp;
    return result;
}

AES::Word AES::LeftShift(const AES::Word &target)
{
    /**
     *  按字节 循环左移一位
     *  即把[a0, a1, a2, a3]变成[a1, a2, a3, a0]
     */
    Word high = target << 8;
    Word low  = target >> 24;
    return high | low;
}

AES::Word AES::MapToSboxKey(const AES::Word &target)
{
    /**
     *  对输入word中的每一个字节进行S-盒映射
     */
    Word ret;
    for(int i = 0; i < 32; i+=8){
        int row = target[i+7]*8 + target[i+6]*4
                + target[i+5]*2 + target[i+4];
        int col = target[i+3]*8 + target[i+2]*4
                + target[i+1]*2 + target[i];
        Byte val = AES_Operation::S_Box[row][col];
        for(int j=0; j<8; ++j)
            ret[i+j] = val[j];
    }
    return ret;
}

void AES::KeyExpansion(AES::Byte key[16], AES::Word w[44])
{
    /**
     *  密钥扩展函数 - 对128位密钥进行扩展得到 w[44]
     */
    Word temp;
    int index = 0;
    // w[]的前4个就是输入的key
    while(index < 4){
        w[index] = ByteToWord(key[4*index], key[4*index+1],
                key[4*index+2], key[4*index+3]);
        ++index;
    }

    index = 4;

    while(index < 44){
        temp = w[index-1]; // 记录前一个word
        if(index % 4 == 0){
            Word tmp2 = LeftShift(temp);
            w[index] = w[index-4] ^
                    MapToSboxKey(tmp2) ^
                    AES_Operation::Rcon[index/4-1];
        }
        else
            w[index] = w[index-4] ^ temp;
        ++index;
    }
}

void AES::MapToSboxMtx(AES::Byte mtx[16])
{
    /*
     *  S盒变换 - 前4位为行号，后4位为列号
     */
    for(int i=0; i<16; ++i){
        int row = mtx[i][7]*8 + mtx[i][6]*4 + mtx[i][5]*2 + mtx[i][4];
        int col = mtx[i][3]*8 + mtx[i][2]*4 + mtx[i][1]*2 + mtx[i][0];
        mtx[i] = AES_Operation::S_Box[row][col];
    }
}

void AES::RowsShift(AES::Byte mtx[16])
{
    /*
     *  行移位 - 按字节循环移位,第一行不变
     */
    // 第二行循环左移一位
    Byte temp = mtx[4];
    for(int i=0; i<3; ++i)
        mtx[i+4] = mtx[i+5];
    mtx[7] = temp;

    // 第三行循环左移两位
    for(int i=0; i<2; ++i){
        temp = mtx[i+8];
        mtx[i+8] = mtx[i+10];
        mtx[i+10] = temp;
    }

    // 第四行循环左移三位
    temp = mtx[15];
    for(int i=3; i>0; --i)
        mtx[i+12] = mtx[i+11];
    mtx[12] = temp;
}

AES::Byte AES::GFMultiply(AES::Byte a, AES::Byte b)
{
    /*
     *  有限域上的乘法和加法 GF(2^8)
     */
    Byte ret = 0;
    Byte hi_bit_set;
    for (int counter = 0; counter < 8; ++counter) {
        if ((b & Byte(1)) != 0) {
            ret ^= a;
        }
        hi_bit_set = static_cast<Byte>(a & Byte(0x80));
        a <<= 1;
        if (hi_bit_set != 0) {
            a ^= 0x1b; /* x^8 + x^4 + x^3 + x + 1 */
        }
        b >>= 1;
    }
    return ret;
}

void AES::ColumnsMix(AES::Byte mtx[])
{
    /*
     *  列混淆，矩阵乘法
     */
    Byte arr[4];
    for(int i=0; i<4; ++i){
        for(int j=0; j<4; ++j)
            arr[j] = mtx[i+j*4];

        mtx[i]   = GFMultiply(0x02, arr[0]) ^
                GFMultiply(0x03, arr[1]) ^ arr[2] ^ arr[3];
        mtx[i+4] = arr[0] ^
                GFMultiply(0x02, arr[1]) ^
                GFMultiply(0x03, arr[2]) ^ arr[3];
        mtx[i+8] = arr[0] ^ arr[1] ^
                GFMultiply(0x02, arr[2]) ^
                GFMultiply(0x03, arr[3]);
        mtx[i+12] = GFMultiply(0x03, arr[0]) ^
                arr[1] ^ arr[2] ^ GFMultiply(0x02, arr[3]);
    }
}

void AES::KeyRoundAdd(AES::Byte mtx[16], AES::Word k[4])
{
    /*
     *  轮密钥加变换 - 将每一列与扩展密钥进行异或
     */
    for(int i=0; i<4; ++i){
        // 获取字的四个字节
        Word k1 = (k[i] >> 24);
        Word k2 = (k[i] <<  8) >> 24;
        Word k3 = (k[i] << 16) >> 24;
        Word k4 = (k[i] << 24) >> 24;

        mtx[i]    = mtx[i]    ^ Byte(k1.to_ulong());
        mtx[i+4]  = mtx[i+4]  ^ Byte(k2.to_ulong());
        mtx[i+8]  = mtx[i+8]  ^ Byte(k3.to_ulong());
        mtx[i+12] = mtx[i+12] ^ Byte(k4.to_ulong());
    }
}

void AES::RowsShiftInv(AES::Byte mtx[16])
{
    /*
     *  逆行变换 - 以字节为单位循环右移
     */
    // 第二行循环右移一位
    Byte temp = mtx[7];
    for(int i=3; i>0; --i)
        mtx[i+4] = mtx[i+3];
    mtx[4] = temp;
    // 第三行循环右移两位
    for(int i=0; i<2; ++i)
    {
        temp = mtx[i+8];
        mtx[i+8] = mtx[i+10];
        mtx[i+10] = temp;
    }
    // 第四行循环右移三位
    temp = mtx[12];
    for(int i=0; i<3; ++i)
        mtx[i+12] = mtx[i+13];
    mtx[15] = temp;
}

void AES::MapToSboxMtxInv(AES::Byte mtx[16])
{
    /*
     *  逆S盒变换
     */
    for(int i=0; i<16; ++i)
    {
        int row = mtx[i][7]*8 + mtx[i][6]*4 + mtx[i][5]*2 + mtx[i][4];
        int col = mtx[i][3]*8 + mtx[i][2]*4 + mtx[i][1]*2 + mtx[i][0];
        mtx[i] = AES_Operation::Inv_S_Box[row][col];
    }
}

void AES::ColumnsMixInv(AES::Byte mtx[])
{
    /*
     * 逆向列混淆
     */
    Byte arr[4];
    for(int i=0; i<4; ++i){
        for(int j=0; j<4; ++j)
            arr[j] = mtx[i+j*4];

        mtx[i]    = GFMultiply(0x0e, arr[0]) ^
                GFMultiply(0x0b, arr[1]) ^
                GFMultiply(0x0d, arr[2]) ^
                GFMultiply(0x09, arr[3]);
        mtx[i+4]  = GFMultiply(0x09, arr[0]) ^
                GFMultiply(0x0e, arr[1]) ^
                GFMultiply(0x0b, arr[2]) ^
                GFMultiply(0x0d, arr[3]);
        mtx[i+8]  = GFMultiply(0x0d, arr[0]) ^
                GFMultiply(0x09, arr[1]) ^
                GFMultiply(0x0e, arr[2]) ^
                GFMultiply(0x0b, arr[3]);
        mtx[i+12] = GFMultiply(0x0b, arr[0]) ^
                GFMultiply(0x0d, arr[1]) ^
                GFMultiply(0x09, arr[2]) ^
                GFMultiply(0x0e, arr[3]);
    }
}
