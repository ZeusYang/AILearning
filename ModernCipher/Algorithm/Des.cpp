#include "Des.h"
#include <QDebug>
#include <iostream>

Des::Des()
    :Encryption() {}

Des::~Des() {}

QString Des::EncodeMessage(const QString &message)
{
    QString result;
    switch(this->mode){
    case MODE::ECB:
        result = EncodeECB(message);
        break;
    case MODE::CBC:
        result = EncodeCBC(message);
        break;
    }
    return result;
}

QString Des::DecodeMessage(const QString &message)
{
    QString result;
    switch(this->mode){
    case MODE::ECB:
        result = DecodeECB(message);
        break;
    case MODE::CBC:
        result = DecodeCBC(message);
        break;
    }
    return result;
}

QString Des::SetKey(const QString &key)
{
    std::bitset<64> ret = CharToBitset(key.toStdString());
    QString record;
    this->key = ret;
    return record;
}

QString Des::SetInitVec(const QString &target)
{
    std::bitset<64> ret = CharToBitset(target.toStdString());
    QString record;
    this->keyInitVec = ret;
    return record;
}

QString Des::EncodeECB(const QString &message)
{
    QString result;
    subkey = GenerateCiphers(key);
    std::string text = message.toStdString();
    std::string record;
    int length = text.size();
    int groups = length/8;
    for(auto x = 0;x < groups;++x){
        std::string substr = text.substr(x*8,8);
        std::bitset<64> target = CharToBitset(substr);
        std::bitset<64> cipher = EncryPerGroup(target);
        record += cipher.to_string();
    }

    // 对剩余的不足64进行操作
    if(groups*8 < length){
        std::string substr = text.substr(groups*8);
        int len = substr.length();
        for(auto x = len;x < 8;++x)substr.push_back('\0');
        std::bitset<64> target = this->CharToBitset(substr);
        std::bitset<64> cipher = EncryPerGroup(target);
        record += cipher.to_string();
    }
    result = QString::fromStdString(record);
    return result;
}

QString Des::DecodeECB(const QString &message)
{
    QString result;
    subkey = GenerateCiphers(key);
    std::string text = message.toStdString();
    std::string record;
    int length = text.size();
    int groups = length/64;
    for(auto x = 0;x < groups;++x){
        std::string substr = text.substr(x*64,64);
        std::bitset<64> target(substr);
        std::bitset<64> answer = DecryPerGroup(target);
        record += BitsetToChar(answer);
    }
    result = QString::fromStdString(record);
    return result;
}

QString Des::EncodeCBC(const QString &message)
{
    QString result;
    subkey = GenerateCiphers(key);
    std::string text = message.toStdString();
    std::string record;
    int length = text.size();
    int groups = length/8;
    for(auto x = 0;x < groups;++x){
        std::string substr = text.substr(x*8,8);
        std::bitset<64> target = CharToBitset(substr);
        target = target ^ keyInitVec;
        std::bitset<64> cipher = EncryPerGroup(target);
        keyInitVec = cipher;
        record += cipher.to_string();
    }

    // 对剩余的不足64进行操作
    if(groups*8 < length){
        std::string substr = text.substr(groups*8);
        int len = substr.length();
        for(auto x = len;x < 8;++x)substr.push_back('\0');
        std::bitset<64> target = this->CharToBitset(substr);
        target = target ^ keyInitVec;
        std::bitset<64> cipher = EncryPerGroup(target);
        keyInitVec = cipher;
        record += cipher.to_string();
    }
    result = QString::fromStdString(record);
    return result;
}

QString Des::DecodeCBC(const QString &message)
{
    QString result;
    subkey = GenerateCiphers(key);
    std::string text = message.toStdString();
    std::string record;
    int length = text.size();
    int groups = length/64;
    for(auto x = 0;x < groups;++x){
        std::string substr = text.substr(x*64,64);
        std::bitset<64> target(substr);
        std::bitset<64> answer = DecryPerGroup(target);
        answer = answer ^ keyInitVec;
        keyInitVec = target;
        record += BitsetToChar(answer);
    }
    result = QString::fromStdString(record);
    return result;
}

std::bitset<64> Des::CharToBitset(const std::string &target)
{
    std::bitset<64> bits;
    for(int i=0; i<8; ++i)
        for(int j=0; j<8; ++j)
            bits[i*8+j] = ((target[i]>>j) & 1);
    return bits;
}

std::string Des::BitsetToChar(const std::bitset<64> &target)
{
    std::string result;
    for(auto x = 0;x < 8;++x){
        char tmp1 = '\0';
        std::bitset<8> det;
        for(auto y = 0;y < 8;++y)
            det[y] = target[x*8+y];
        tmp1 = static_cast<char>(det.to_ulong());
        result.push_back(tmp1);
    }
    return result;
}

std::bitset<64> Des::EncryPerGroup(const std::bitset<64> &target)
{
    std::bitset<64> cipher;
    std::bitset<64> currentBits;
    std::bitset<32> left,right,newLeft;
    // 第一步：初始置换
    for(auto i = 0; i < 64; ++i)
        currentBits[i] = target[DES_Operation::init_ip[i]-1];
    for(auto i = 0; i < 32; ++i){
        left[i] = currentBits[i+32];
        right[i] = currentBits[i];
    }

    // 第二步: 16轮迭代
    for(auto round = 0; round < 16; ++round){
        newLeft = right;
        right = left ^ Function_f(right,subkey[round]);
        left = newLeft;
    }

    // 第三步：因为第16轮不交换,所以换回来
    std::bitset<32> tmpChange = left;
    left = right;
    right = tmpChange;
    for(auto i = 0; i < 32; ++i){
        cipher[i+32] = left[i];
        cipher[i] = right[i];
    }
    currentBits = cipher;

    //最后逆置换
    for(int i=0; i<64; ++i)
        cipher[i] = currentBits[DES_Operation::init_ip_rever[i] - 1];

    return cipher;
}

std::bitset<64> Des::DecryPerGroup(const std::bitset<64> &target)
{
    std::bitset<64> cipher;
    std::bitset<64> currentBits;
    std::bitset<32> left,right,newLeft;
    // 第一步：初始置换
    for(auto i = 0; i < 64; ++i)
        currentBits[i] = target[DES_Operation::init_ip[i]-1];
    for(auto i = 0; i < 32; ++i){
        left[i] = currentBits[i+32];
        right[i] = currentBits[i];
    }

    // 第二步: 16轮迭代
    for(auto round = 15; round >= 0; --round){
        newLeft = right;
        right = left ^ Function_f(right,subkey[round]);
        left = newLeft;
    }

    // 第三步：因为第16轮不交换,所以换回来
    std::bitset<32> tmpChange = left;
    left = right;
    right = tmpChange;
    for(auto i = 0; i < 32; ++i){
        cipher[i] = right[i];
        cipher[i+32] = left[i];
    }
    currentBits = cipher;

    //最后逆置换
    for(int i=0; i<64; ++i)
        cipher[i] = currentBits[DES_Operation::init_ip_rever[i] - 1];

    return cipher;
}

std::bitset<28> Des::leftShift(std::bitset<28> target, int shift)
{
    std::bitset<28> tmp = target;
    for(auto i = 0; i < 27; ++i){
        target[(i+28+shift)%28] = tmp[i];
    }
    return target;
}

std::vector<std::bitset<48> >
Des::GenerateCiphers(const std::bitset<64> &key)
{
    std::bitset<56> realKey;
    std::bitset<28> left;
    std::bitset<28> right;
    std::bitset<48> compressKey;
    std::vector<std::bitset<48>> result(16);
    // 去掉奇偶标记位，提取其中的56位真实密钥
    for (int i = 0; i < 56; ++i)
        realKey[i] = key[DES_Operation::PC_1[i]-1];

    // 生成16个要用到的子密钥
    for(int round = 0; round < 16; ++round){
        // 前28位与后28位
        for(int i = 0; i < 28; ++i){
            left[i] = realKey[i+28];
            right[i] = realKey[i];
        }
        // 左移
        left = leftShift(left, DES_Operation::shiftBits[round]);
        right = leftShift(right, DES_Operation::shiftBits[round]);

        // 压缩置换，由56位得到48位子密钥
        for(int i = 0; i < 28; ++i){
            realKey[i+28] = left[i];
            realKey[i]    = right[i];
        }
        for(int i = 0; i < 48; ++i)
            compressKey[i] = realKey[DES_Operation::PC_2[i]-1];
        result[round] = compressKey;
    }
    return result;
}


std::bitset<32> Des::Function_f(const std::bitset<32> &data,
                                std::bitset<48> &subcipher)
{
    //32数据扩展48
    std::bitset<48> expandData;
    for(int i = 0; i < 48; i++)
        expandData[i] = data[DES_Operation::E[i] - 1];

    //48数据异或子密钥
    expandData = expandData^subcipher;
    std::bitset<32> output;

    //查找S_BOX置换表
    int index = 0;
    for(int i=0; i<48; i=i+6){
        int row = expandData[i+5]*2
                + expandData[i];
        int col = expandData[i+4]*8
                + expandData[i+3]*4
                + expandData[i+2]*2
                + expandData[i+1];
        int num = DES_Operation::S_BOX[i/6][row][col];

        std::bitset<4> binary(num);

        output[index] = binary[0];
        output[index+1] = binary[1];
        output[index+2] = binary[2];
        output[index+3] = binary[3];

        index += 4;
    }

    //直接换位盒,32->32
    std::bitset<32> tmp = output;
    for(int i=0; i < 32; ++i){
        output[i] = tmp[DES_Operation::P[i] - 1];
    }
    return output;
}
