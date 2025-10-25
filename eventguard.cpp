#include "eventguard.h"
#include "./ui_eventguard.h"

EventGuard::EventGuard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EventGuard)
{
    ui->setupUi(this);
    connect_slot();
    modelLog = new QStringListModel(this);



    connectLink("https://github.com/BHNamSSD/EventGuard");
    //ui->listView_logSystem->setModel(logModel);
    writeLog("Ứng dụng khởi động thành công.");
    this->setWindowTitle(setVersion(VERSION));
}

EventGuard::~EventGuard()
{
    delete ui;
}

void EventGuard::connectLink(QString linkIn)
{
    QString url1 = "<a style='color:#0088D3;' href=\"";
    QString url2 = "\">BHNamSSD</a>";
    ui->label_bhnamssd->setText(url1 + linkIn + url2);
    ui->label_bhnamssd->setTextFormat(Qt::RichText);
    ui->label_bhnamssd->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->label_bhnamssd->setOpenExternalLinks(false); // tắt tự mở
    connect(ui->label_bhnamssd, &QLabel::linkActivated, this, [](const QString &link){
        QDesktopServices::openUrl(QUrl(link));
    });
}

//connect slot
void EventGuard::connect_slot()
{
    connect(ui->pushButton_exitApp,SIGNAL(clicked(bool)),this,SLOT(exit_app()));
    connect(ui->pushButton_restart,SIGNAL(clicked(bool)),this,SLOT(restart()));
}

//function set version
QString EventGuard::setVersion(double version)
{
    QString title = QString("EventGuard - v%1").arg(version);
    return title;
}

//function restart
void EventGuard::restart()
{
    writeLog("call restart");
}

//function write log
void EventGuard::writeLog(const QString &message)
{
    QString time = QDateTime::currentDateTime().toString("HH:mm:ss");
    QString fullMsg = QString("[%1] %2").arg(time, message);

    listLog.append(fullMsg);
    modelLog->setStringList(listLog);
    ui->listView_logSystem->setModel(modelLog);
    ui->listView_logSystem->setEditTriggers(QAbstractItemView::NoEditTriggers);     // Không cho sửa
}

//function question exit app
void EventGuard::exit_app()
{
    int choose = QMessageBox::question(this,"Exit","Do you want to exit the application?");
    if(choose == QMessageBox::Yes)
    {
        qApp->exit(1);
    }
    else if(choose == QMessageBox::No)
    {

    }
}









