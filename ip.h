#ifndef IP_H
#define IP_H
#include <QHostAddress>
#include <QAbstractSocket>
#include <QRegularExpression>

class IP
{
public:
    IP();
    bool isValidIP(const QString &ip);        // IPv4 hoặc IPv6
    bool isValidIPv4(const QString &ip);
    bool isValidIPv6(const QString &ip);

    void setIP(const QString &ip);
    QString getIP();

private:
    QString ip;



};

#endif // IP_H
