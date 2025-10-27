#include "rule.h"

Rule::Rule()
{
    ruleIP = "";
    rulePort = "";
    ruleTCPorUDP = "";
    ruleName = "";
    ruleInOut = "";
}

void Rule::test_getVailRuleCurrent()
{
    qDebug() << ruleIP;
    qDebug() << rulePort;
    qDebug() << ruleTCPorUDP;
    qDebug() << ruleName;
    qDebug() << ruleInOut;
}

QString Rule::getRuleIP()
{
    return this->ruleIP;
}

QString Rule::getRulePort()
{
    return this->rulePort;
}

QString Rule::getRuleTCPorUDP()
{
    return this->ruleTCPorUDP;
}
QString Rule::getRuleName()
{
    return this->ruleName;
}

QString Rule::getRuleInOut()
{
    return this->ruleInOut;
}

void Rule::setRuleIP(const QString &ruleIP)
{
    this->ruleIP = ruleIP;
}

void Rule::setRulePort(const QString &rulePort)
{
    this->rulePort = rulePort;
}

void Rule::setRuleTCPorUDP(const QString &ruleTCPorUDP)
{
    this->ruleTCPorUDP = ruleTCPorUDP;
}

void Rule::setRuleName(const QString &ruleName)
{
    this->ruleName = ruleName;
}

void Rule::setRuleInOut(const QString &ruleInOut)
{
    this->ruleInOut = ruleInOut;
}
