#include "firewallmanager.h"
#include <QDebug>
#include <Windows.h>
#include <netfw.h>
#include <comutil.h>

#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "oleaut32.lib")

#ifndef NET_FW_IP_PROTOCOL_ANY
#define NET_FW_IP_PROTOCOL_ANY 256
#endif



FirewallManager::FirewallManager()
{
    writeLogFirewall = new WriteLog("Firewall");
    initialize();
}

FirewallManager::~FirewallManager() {
    cleanup();
}

bool FirewallManager::initialize() {
    HRESULT hr = CoInitializeEx(0, COINIT_APARTMENTTHREADED);
    if (FAILED(hr)) {
        qDebug() << "COM initialization failed";
        writeLogFirewall->writeLog("Error","Firewall","COM initialization failed");
        return false;
    }

    INetFwPolicy2 *policy = nullptr;
    hr = CoCreateInstance(
        __uuidof(NetFwPolicy2),
        nullptr,
        CLSCTX_INPROC_SERVER,
        __uuidof(INetFwPolicy2),
        (void**)&policy);

    if (FAILED(hr)) {
        qDebug() << "Failed to create INetFwPolicy2 instance";
        writeLogFirewall->writeLog("Error","Firewall","Failed to create INetFwPolicy2 instance");
        CoUninitialize();
        return false;
    }

    pPolicy2 = policy;
    return true;
}

void FirewallManager::cleanup() {
    if (pPolicy2) {
        ((INetFwPolicy2*)pPolicy2)->Release();
        pPolicy2 = nullptr;
    }
    CoUninitialize();
}

bool FirewallManager::blockIP(const QString &ip, const QString &ruleName) {
    if (!pPolicy2) return false;

    INetFwRule *pRule = nullptr;
    HRESULT hr = CoCreateInstance(
        __uuidof(NetFwRule),
        nullptr,
        CLSCTX_INPROC_SERVER,
        __uuidof(INetFwRule),
        (void**)&pRule);

    if (FAILED(hr)) {
        qDebug() << "Failed to create INetFwRule";
        writeLogFirewall->writeLog("Error","Firewall","Failed to create INetFwRule");
        return false;
    }

    pRule->put_Name(_bstr_t(ruleName.toStdWString().c_str()));
    pRule->put_Description(_bstr_t(L"Rule created by Qt FirewallManager"));
    pRule->put_Direction(NET_FW_RULE_DIR_IN);
    pRule->put_Action(NET_FW_ACTION_BLOCK);
    pRule->put_Enabled(VARIANT_TRUE);
    pRule->put_RemoteAddresses(_bstr_t(ip.toStdWString().c_str()));

    INetFwRules *rules = nullptr;
    hr = ((INetFwPolicy2*)pPolicy2)->get_Rules(&rules);
    if (SUCCEEDED(hr)) {
        hr = rules->Add(pRule);
        rules->Release();
    }

    pRule->Release();
    QString mess;
    if (SUCCEEDED(hr)) {
        qDebug() << "Blocked IP:" << ip;
        mess = "Blocked IP:" + ip;
        writeLogFirewall->writeLog("Info","Firewall",mess);
        return true;
    } else {
        qDebug() << "Failed to add rule";
        mess = "Failed to add rule";
        writeLogFirewall->writeLog("Error","Firewall",mess);
        return false;
    }
}

bool FirewallManager::blockIPPort(const QString &ip,
                                  const QString &ruleName,
                                  const QString &protocol,
                                  const QString &port)
{
    if (!pPolicy2) return false;

    INetFwRule *pRule = nullptr;
    HRESULT hr = CoCreateInstance(
        __uuidof(NetFwRule),
        nullptr,
        CLSCTX_INPROC_SERVER,
        __uuidof(INetFwRule),
        (void**)&pRule);

    if (FAILED(hr)) {
        qDebug() << "Failed to create INetFwRule";
        writeLogFirewall->writeLog("Error","Firewall","Failed to create INetFwRule");
        return false;
    }

    // Thiết lập thông tin cơ bản
    pRule->put_Name(_bstr_t(ruleName.toStdWString().c_str()));
    pRule->put_Description(_bstr_t(L"Rule created by Qt FirewallManager"));
    pRule->put_Direction(NET_FW_RULE_DIR_IN);  // inbound
    pRule->put_Action(NET_FW_ACTION_BLOCK);
    pRule->put_Enabled(VARIANT_TRUE);
    pRule->put_RemoteAddresses(_bstr_t(ip.toStdWString().c_str()));

    // Xác định giao thức (protocol)
    long protoValue = NET_FW_IP_PROTOCOL_TCP;
    if (protocol.compare("UDP", Qt::CaseInsensitive) == 0)
        protoValue = NET_FW_IP_PROTOCOL_UDP;
    else if (protocol.compare("ANY", Qt::CaseInsensitive) == 0)
        protoValue = NET_FW_IP_PROTOCOL_ANY;

    pRule->put_Protocol(protoValue);

    // Nếu có chỉ định port
    if (!port.isEmpty())
        pRule->put_LocalPorts(_bstr_t(port.toStdWString().c_str()));

    // Thêm rule vào firewall
    INetFwRules *rules = nullptr;
    hr = ((INetFwPolicy2*)pPolicy2)->get_Rules(&rules);
    if (SUCCEEDED(hr)) {
        hr = rules->Add(pRule);
        rules->Release();
    }

    pRule->Release();

    QString mess;
    if (SUCCEEDED(hr)) {
        mess = QString("Blocked IP: %1 Port: %2 Protocol: %3").arg(ip, port, protocol);
        qDebug() << mess;
        writeLogFirewall->writeLog("Info","Firewall",mess);
        return true;
    } else {
        mess = "Failed to add rule";
        qDebug() << mess;
        writeLogFirewall->writeLog("Error","Firewall",mess);
        return false;
    }
}

bool FirewallManager::blockIPPort(const QString &ip,
                                  const QString &ruleName,
                                  const QString &protocol,
                                  const QString &port,
                                  const QString &direction)
{
    if (!pPolicy2) return false;

    INetFwRule *pRule = nullptr;
    HRESULT hr = CoCreateInstance(
        __uuidof(NetFwRule),
        nullptr,
        CLSCTX_INPROC_SERVER,
        __uuidof(INetFwRule),
        (void**)&pRule);

    if (FAILED(hr)) {
        qDebug() << "Failed to create INetFwRule";
        writeLogFirewall->writeLog("Error", "Firewall", "Failed to create INetFwRule");
        return false;
    }

    // === Thiết lập thông tin cơ bản ===
    pRule->put_Name(_bstr_t(ruleName.toStdWString().c_str()));
    pRule->put_Description(_bstr_t(L"Rule created by Qt FirewallManager"));
    pRule->put_Action(NET_FW_ACTION_BLOCK);
    pRule->put_Enabled(VARIANT_TRUE);
    pRule->put_RemoteAddresses(_bstr_t(ip.toStdWString().c_str()));

    // === Thiết lập hướng (direction) ===
    NET_FW_RULE_DIRECTION dir = NET_FW_RULE_DIR_IN; // mặc định inbound
    if (direction.compare("OUT", Qt::CaseInsensitive) == 0)
        dir = NET_FW_RULE_DIR_OUT;

    pRule->put_Direction(dir);

    // === Giao thức (protocol) ===
    long protoValue = NET_FW_IP_PROTOCOL_TCP;
    if (protocol.compare("UDP", Qt::CaseInsensitive) == 0)
        protoValue = NET_FW_IP_PROTOCOL_UDP;
    else if (protocol.compare("ANY", Qt::CaseInsensitive) == 0)
        protoValue = NET_FW_IP_PROTOCOL_ANY;

    pRule->put_Protocol(protoValue);

    // === Cổng (port) nếu có ===
    if (!port.isEmpty())
        pRule->put_LocalPorts(_bstr_t(port.toStdWString().c_str()));

    // === Thêm rule vào firewall ===
    INetFwRules *rules = nullptr;
    hr = ((INetFwPolicy2*)pPolicy2)->get_Rules(&rules);
    if (SUCCEEDED(hr)) {
        hr = rules->Add(pRule);
        rules->Release();
    }

    pRule->Release();

    QString mess;
    if (SUCCEEDED(hr)) {
        mess = QString("Blocked %1 IP: %2 Port: %3 Protocol: %4")
        .arg(direction, ip, port, protocol);
        qDebug() << mess;
        writeLogFirewall->writeLog("Info", "Firewall", mess);
        return true;
    } else {
        mess = "Failed to add rule";
        qDebug() << mess;
        writeLogFirewall->writeLog("Error", "Firewall", mess);
        return false;
    }
}


bool FirewallManager::unblockRule(const QString &ruleName) {
    if (!pPolicy2) return false;

    INetFwRules *rules = nullptr;
    HRESULT hr = ((INetFwPolicy2*)pPolicy2)->get_Rules(&rules);
    if (FAILED(hr)) return false;

    hr = rules->Remove(_bstr_t(ruleName.toStdWString().c_str()));
    rules->Release();
    QString mess;
    if (SUCCEEDED(hr)) {
        qDebug() << "Removed rule:" << ruleName;
        mess = "Removed rule:" + ruleName;
        writeLogFirewall->writeLog("Info","Firewall",mess);
        return true;
    } else {
        qDebug() << "Failed to remove rule";
        mess = "Failed to remove rule";
        writeLogFirewall->writeLog("Error","Firewall",mess);
        return false;
    }
}

QList<QPair<QString, QString>> FirewallManager::listBlockedIPs() {
    QList<QPair<QString, QString>> result;

    if (!pPolicy2) {
        qDebug() << "Firewall policy interface not initialized.";
        return result;
    }

    INetFwRules *rules = nullptr;
    HRESULT hr = ((INetFwPolicy2*)pPolicy2)->get_Rules(&rules);

    if (FAILED(hr) || !rules) {
        qDebug() << "Failed to get firewall rules.";
        return result;
    }

    IUnknown *pUnkEnum = nullptr;
    hr = rules->get__NewEnum(&pUnkEnum);

    if (FAILED(hr) || !pUnkEnum) {
        rules->Release();
        qDebug() << "Failed to get rule enumerator.";
        return result;
    }

    IEnumVARIANT *pEnum = nullptr;
    hr = pUnkEnum->QueryInterface(__uuidof(IEnumVARIANT), (void**)&pEnum);
    pUnkEnum->Release();

    if (FAILED(hr) || !pEnum) {
        rules->Release();
        qDebug() << "Failed to query IEnumVARIANT.";
        return result;
    }

    VARIANT var;
    VariantInit(&var);

    while (pEnum->Next(1, &var, nullptr) == S_OK) {
        if (var.vt == VT_DISPATCH && var.pdispVal != nullptr) {
            INetFwRule *pRule = nullptr;
            hr = var.pdispVal->QueryInterface(__uuidof(INetFwRule), (void**)&pRule);

            if (SUCCEEDED(hr) && pRule) {
                BSTR bstrName = nullptr;
                BSTR bstrAddr = nullptr;
                NET_FW_ACTION action;

                pRule->get_Name(&bstrName);
                pRule->get_RemoteAddresses(&bstrAddr);
                pRule->get_Action(&action);

                if (action == NET_FW_ACTION_BLOCK) {
                    QString name = QString::fromWCharArray(bstrName);
                    QString addr = QString::fromWCharArray(bstrAddr);
                    result.append(qMakePair(name, addr));
                }

                if (bstrName) SysFreeString(bstrName);
                if (bstrAddr) SysFreeString(bstrAddr);

                pRule->Release();
            }
        }
        VariantClear(&var);
    }

    pEnum->Release();
    rules->Release();

    return result;
}






