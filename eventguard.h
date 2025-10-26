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

    QStringListModel *modelLog;
    QStringList listLog;

    QString logDirApp;
    //QString logPathApp;
    QString logPath_EventGuard;
    void setLogPathApp();

    //void setTabWidget_system();


private slots:
    void connect_slot();
    void writeLog(const QString &,const QString &,const QString &);

    void connectLink(QString);

    void restart();

    void exit_app();




};
#endif // EVENTGUARD_H
