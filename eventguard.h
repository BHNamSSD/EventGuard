#ifndef EVENTGUARD_H
#define EVENTGUARD_H


#define VERSION 1.01
#include <QMainWindow>

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
};
#endif // EVENTGUARD_H
