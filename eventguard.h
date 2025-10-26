#ifndef EVENTGUARD_H
#define EVENTGUARD_H


#define VERSION 1.01
#define LOGDIR "/logs"
#define lOGNAMEFILE "/EventGuard.log"

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


    //View log App object
    QStringListModel *modelViewLog;
    QStringList listViewLog;



    FirewallManager fw_system;
    WriteLog *writeLogFile;

private slots:
    void connect_slot();

    void pushViewLog(QString);

    void connectLink(QString);

    void connectLinkOpenWDF();

    void restart();

    void exit_app();




};
#endif // EVENTGUARD_H
