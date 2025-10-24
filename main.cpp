#include "eventguard.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EventGuard w;
    w.show();
    return a.exec();
}
