#include "eventguard.h"
#include "./ui_eventguard.h"

EventGuard::EventGuard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EventGuard)
{
    ui->setupUi(this);
}

EventGuard::~EventGuard()
{
    delete ui;
}
