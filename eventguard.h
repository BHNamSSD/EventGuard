#ifndef EVENTGUARD_H
#define EVENTGUARD_H

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
};
#endif // EVENTGUARD_H
