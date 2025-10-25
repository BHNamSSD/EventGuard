#ifndef EVENTGUARD_H
#define EVENTGUARD_H


#define VERSION 1.01
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QDateTime>
#include <QStringListModel>
#include <QModelIndex>
#include <QDesktopServices>
#include <QApplication>

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

private slots:
    void connect_slot();
    void writeLog(const QString &);

    void connectLink(QString);

    void restart();

    void exit_app();




};
#endif // EVENTGUARD_H
