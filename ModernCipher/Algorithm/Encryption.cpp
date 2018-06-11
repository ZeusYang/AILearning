#include "Encryption.h"

Encryption::Encryption()
{
    // abstract class
}

void Encryption::setMode(int index)
{
    this->mode = static_cast<MODE>(index);
}

Encryption::~Encryption()
{
    // abstract class
}

QString Encryption::EncodeMessage(const QString &message)
{
    // abstract class
    Q_UNUSED(message);
}

QString Encryption::DecodeMessage(const QString &message)
{
    // abstract class
    Q_UNUSED(message);
}

QString Encryption::SetKey(const QString &key)
{
    // abstract class
    Q_UNUSED(key);
    return QString();
}

QString Encryption::SetInitVec(const QString &target)
{
    // abstract class
    Q_UNUSED(target);
    return QString();
}

