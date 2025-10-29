#ifndef EVENTGUARD_H
#define EVENTGUARD_H



#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QDateTime>
#include <QStringListModel>
#include <QModelIndex>
#include <QDesktopServices>
#include <QApplication>
#include <QIcon>
#include <QStandardItem>
#include <QDir>
#include <QProcess>


#include "firewallmanager.h"
#include "writelog.h"
#include "rule.h"

#include <Userenv.h>
#include "formrulesdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class EventGuard;
}
QT_END_NAMESPACE

class EventGuard : public QMainWindow
{
    Q_OBJECT

public:
    EventGuard(QWidget *parent = nullptr);
    ~EventGuard();




private:
    Ui::EventGuard *ui;
    QString setVersion(double);

    bool isRunningAsAdmin();

    //View log App object
    QStringListModel *modelViewLog;
    QStringList listViewLog;


    FirewallManager *fw_system;
    WriteLog *writeLogFile;
    Rule *rule;

private slots:
    void connect_slot();

    void pushViewLog(QString);

    void connectLink(QString);


    //=====================================
    // Rule
    void showFormAddRule();
    bool checkAddRule();

    void setGroupBox_ruleBlock();
    void clearGroupBox_ruleBlock();

    bool checkIPRule();

    void changePortRule(Qt::CheckState);
    void onCheckBoxAnyPort();
    void offCheckBoxAnyPort();

    QString getTCPorUDP();
    QString getInOutRule();

    bool funcCheckNameAndInOrOUT();

    bool checkNameRule();
    bool checkRulePort();
    bool checkBoxPort();

    void clickAddRule();

    void addRuleBlockIP();

    //=====================================

    void connectLinkOpenWDF();

    void restart();

    void exit_app();




};
#endif // EVENTGUARD_H
