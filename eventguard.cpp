#include "eventguard.h"
#include "./ui_eventguard.h"

EventGuard::EventGuard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EventGuard)
{
    ui->setupUi(this);





    this->setWindowTitle(setVersion(VERSION));
}

EventGuard::~EventGuard()
{
    delete ui;
}

//function set version
QString EventGuard::setVersion(double version){
    QString title = QString("EventGuard - v%1").arg(version);
    return title;
}
