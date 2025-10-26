#include "eventguard.h"
//#include "firewallmanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //FirewallManager fw;
    //fw.blockIP("192.168.1.100", "Block_192.168.1.100");
    EventGuard w;
    w.show();
    return a.exec();
}
