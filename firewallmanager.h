#ifndef FIREWALLMANAGER_H
#define FIREWALLMANAGER_H

#include <QString>
#include <QList>
#include <QPair>
#include "writelog.h"

class FirewallManager
{
public:
    FirewallManager();
    ~FirewallManager();

    bool blockIP(const QString &ip, const QString &ruleName);
    bool blockIPPort(const QString &ip,
                     const QString &ruleName,
                     const QString &protocol,
                     const QString &port);

    bool blockIPPort(const QString &ip,
                     const QString &ruleName,
                     const QString &protocol,
                     const QString &port,
                     const QString &directio);
    bool unblockRule(const QString &ruleName);
    QList<QPair<QString, QString>> listBlockedIPs();

private:
    bool initialize();
    void cleanup();
    void *pPolicy2 = nullptr; // INetFwPolicy2*
    WriteLog *writeLogFirewall;
};

#endif // FIREWALLMANAGER_H
