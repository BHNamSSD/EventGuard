#include "ip.h"


IP::IP() {
    ip = "";
}

// Dùng QHostAddress để kiểm tra IPv4/IPv6
bool IP::isValidIP(const QString &ip)
{
    if (ip.isEmpty()) return false;
    QHostAddress addr(ip);
    return !addr.isNull();
}

bool IP::isValidIPv4(const QString &ip)
{
    QString cleanIp = ip.trimmed();
    // Tạo regex tĩnh, compile 1 lần duy nhất
    static const QRegularExpression regex(
        "^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])\\."
        "(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])\\."
        "(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])\\."
        "(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])$"
        );

    const QRegularExpressionMatch match = regex.match(cleanIp);
    bool result = match.hasMatch();

    //qDebug() << "Checking IPv4:" << cleanIp << "=>" << result;
    return result;
}

bool IP::isValidIPv6(const QString &ip)
{
    if (ip.isEmpty()) return false;
    QHostAddress addr(ip);
    if (addr.isNull()) return false;
    return addr.protocol() == QAbstractSocket::IPv6Protocol;
}

void IP::setIP(const QString &ip)
{
    if(isValidIP(ip))
    {
        this->ip = ip;
    }
    else
    {
        //error ip
    }
}

QString IP::getIP()
{
    return this->ip;
}




