#ifndef RSA_ENCRYPTION_H
#define RSA_ENCRYPTION_H
#include "BigInteger.h"
#include <QObject>

class RSA_Encryption : public QObject
{
    Q_OBJECT
public:
    explicit RSA_Encryption(QObject *parent = nullptr);
    ~RSA_Encryption(){}

    // 初始化,产生公私钥对
    void Initial(const unsigned int &length);

    QString EncodeMessage(const QString &message);
    QString DecodeMessage(const QString &message);

    QString GetPublicKey()const;
    QString GetPrivateKey()const;

    bool GenearteKey()const;
signals:
    void SendProgress(double progress);
private:
    bool hasKey;
    BigInteger public_key,n;
    BigInteger private_key;
    BigInteger p,q,eul;

    /*--------------------------加密/解密--------------------*/
    BigInteger EncryptByPublicKey(const BigInteger &key);    // 公钥加密
    BigInteger DecryptByPrivateKey(const BigInteger &key);// 私钥解密

    /*-------------------------辅助函数---------------------*/
    // 生成一个大奇数,参数为其长度
    BigInteger CreateOddNum(unsigned);
    // 判断是否为素数
    bool IsPrime(const BigInteger &, const unsigned);
    // 随机创建一个更小的数
    BigInteger CreateRandomSmaller(const BigInteger &);
    // 生成一个大素数,参数为其长度
    BigInteger CreatePrime(unsigned, const unsigned);
    // 根据提供的欧拉数生成公钥、私钥指数
    void CreateExponent(const BigInteger &);
};

#endif // RSA_ENCRYPTION_H
