#include "RSA_Encryption.h"
#include <ctime>
#include <sstream>
#include <assert.h>
#include <QDebug>
#include <bitset>
/**
 * 函数功能:初始化RSA对象的相关信息
 * 参数含义:len表示大素数的二进制位数
 */
RSA_Encryption::RSA_Encryption(QObject *parent)
    :QObject(parent),hasKey(false) {}

void RSA_Encryption::Initial(const unsigned int &length){
    emit SendProgress(0.0);
    hasKey = true;
    srand((unsigned)time(nullptr));
    // 产生大素数p和q
    emit SendProgress(0.1);
    p = CreatePrime(length, 15);// 出错概率为(1/4)^15
    emit SendProgress(0.4);
    q = CreatePrime(length, 15);
    emit SendProgress(0.6);
    // 计算出n
    n = p*q;
    // 计算出n的欧拉函数
    eul = (p-1)*(q-1);
    emit SendProgress(0.7);
    // 设置加解密指数e和d
    CreateExponent(eul);
    emit SendProgress(1.0);
}

QString RSA_Encryption::EncodeMessage(const QString &message){
    QString result;
    std::string record = message.toStdString();
    std::string ret;
    emit SendProgress(0.0);
    // 对明文进行加密
    for(auto x = 0;x < record.size();++x){
        std::bitset<8> trans(record[x]);
        BigInteger tar(trans.to_ulong());
        BigInteger Bec = this->EncryptByPublicKey(tar);
        ret += Bec.toString();
        ret += " ";
        emit SendProgress((double)x/(double)(record.size()-1.0));
    }
    result = QString::fromStdString(ret);
    return result;
}

QString RSA_Encryption::DecodeMessage(const QString &message){
    QString result;
    QStringList textList = message.split(" ");
    std::string ret;
    emit SendProgress(0.0);
    // 对密文进行解密
    for(auto x = 0;x < textList.size()-1;++x){
        std::string word = textList.at(x).toStdString();
        BigInteger trans(word);
        BigInteger bec = this->DecryptByPrivateKey(trans);
        word = bec.toString();
        char tmp[10];
        strcpy(tmp,word.c_str());
        int num;
        sscanf(tmp,"%X",&num);
        std::bitset<8> final(num);
        strcpy(tmp,(char*)&final);
        ret += tmp;
        emit SendProgress((double)x/(double)(textList.size()-2.0));
    }
    result = QString::fromStdString(ret);
    return result;
}

QString RSA_Encryption::GetPublicKey() const
{
    return QString::fromStdString(public_key.toString());
}

QString RSA_Encryption::GetPrivateKey() const
{
    return QString::fromStdString(private_key.toString());
}

bool RSA_Encryption::GenearteKey() const
{
    return hasKey;
}

/**
 * 函数功能:使用公钥进行加密
 * 参数含义:m表示要加密的明文
 */
BigInteger RSA_Encryption::EncryptByPublicKey(const BigInteger &target)
{
    return target.modPow(public_key, n);
}

/**
 * 函数功能:使用私钥进行解密
 * 参数含义:c表示要解密的密文
 */
BigInteger RSA_Encryption::DecryptByPrivateKey(const BigInteger &target)
{
    return target.modPow(private_key, n);
}

/**
 * 函数功能:生成一个长度为length的奇数
 * 参数含义:length代表奇数的二进制长度
 */
BigInteger RSA_Encryption::CreateOddNum(unsigned int length)
{
    static const char hex_table[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                                     '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    length >>= 2;    // 十六进制数据,每位占4位二进制
    if (length) {
        std::ostringstream oss;
        for (size_t i = 0; i < length-1; ++i)
            oss << hex_table[rand()%16];
        oss << hex_table[1];// 最后一位为奇数
        return BigInteger(oss.str());
    }
    return BigInteger("F");
}

/**
 * 函数功能:判断一个数是否为素数,采用米勒拉宾大素数检测算法,失误率为(1/4)^k
 * 参数含义:num代表要判定的数,k代表测试次数
 */
bool RSA_Encryption::IsPrime(const BigInteger &num, const unsigned k)
{
    assert(num != BigInteger::ZERO);// 测试num是否为0
    if (num == BigInteger::ONE) return false;
    if (num == BigInteger::TWO) return true;

    BigInteger t = num-1;
    BigInteger::bit b(t);// 二进制数
    // 减一之后为奇数,原数为偶数
    if (b.at(0) == 1) return false;
    // num-1 = 2^s*d
    size_t s = 0;    // 统计二进制末尾有几个0
    BigInteger d(t);
    for (size_t i=0; i<b.size(); ++i) {
        if (!b.at(i)) {
            ++s;
            d = d.shiftRight(1);// 计算出d
        }
        else break;
    }

    for (size_t i=0; i<k; ++i) {// 测试k次
        BigInteger a = CreateRandomSmaller(num);// 生成一个介于[1,num-1]之间的随机数a
        BigInteger x = a.modPow(d, num);
        if (x == BigInteger::ONE)// 可能为素数
            continue;
        bool ok = true;
        // 测试所有0<=j<s,a^(2^j*d) mod num != -1
        for (size_t j=0; j<s && ok; ++j) {
            if (x == t)
                ok = false;    // 有一个相等,可能为素数
            x = x.multiply(x).mod(num);
        }
        // 确实都不等,一定为合数
        if (ok) return false;
    }
    return true;    // 通过所有测试,可能为素数
}

/**
 * 函数功能:随机生成一个比val小的数
 * 参数含义:val代表比较的那个数
 */
BigInteger RSA_Encryption::CreateRandomSmaller(const BigInteger &val)
{
    BigInteger::base_t t = 0;
    do {
        t = rand();
    } while (t == 0);// 随机生成非0数

    BigInteger mod(t);
    BigInteger ans = mod%val;    // 比val要小
    if (ans == BigInteger::ZERO)// 必须非零
        ans = val-BigInteger::ONE;
    return ans;
}

/**
 * 函数功能:生成一个二进制长度为len的大素数
 * 参数含义:len代表大素数的长度,k代表素数检测的次数
 */
BigInteger RSA_Encryption::CreatePrime(unsigned int len, const unsigned int k)
{
    assert(k > 0);
    BigInteger ans = CreateOddNum(len);// 首先生成一个奇数
    while (!IsPrime(ans, k)) {// 素性检测
        ans = ans.add(BigInteger::TWO);// 下一个奇数
    }
    return ans;
}

/**
 * 函数功能:根据提供的欧拉数生成公钥、私钥指数
 * 参数含义:eul表示提供的欧拉数
 */
void RSA_Encryption::CreateExponent(const BigInteger &eul)
{
    public_key = 65537;
    private_key = public_key.modInverse(eul);
}
