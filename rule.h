#ifndef RULE_H
#define RULE_H
#include <QString>
#include <qDebug>

class Rule
{
public:
    Rule();

    void test_getVailRuleCurrent();
    QString getRuleIP();
    QString getRulePort();
    QString getRuleTCPorUDP();
    QString getRuleName();
    QString getRuleInOut();

    void setRuleIP(const QString &);
    void setRulePort(const QString &);
    void setRuleTCPorUDP(const QString &);
    void setRuleName(const QString &);
    void setRuleInOut(const QString &);

private:
    QString ruleIP;
    QString rulePort;
    QString ruleTCPorUDP;
    QString ruleName;
    QString ruleInOut;
};

#endif // RULE_H
