#include "Encryption.h"

Encryption::Encryption()
{
    // abstract class
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
