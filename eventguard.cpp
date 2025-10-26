#include "eventguard.h"
#include "./ui_eventguard.h"


EventGuard::EventGuard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EventGuard)
{
    ui->setupUi(this);
    connect_slot();
    modelViewLog = new QStringListModel(this);

    //setLogPathApp();
    writeLogFile = new WriteLog("EventGuard");



    connectLink("https://github.com/BHNamSSD/EventGuard");
    connectLinkOpenWDF();

    writeLogFile->writeLog("Info","System","The application started successfully.");
    pushViewLog(writeLogFile->getFullMessLog());

    qDebug() << writeLogFile->getFullMessLog();
    this->setWindowTitle(setVersion(VERSION));
}

// void EventGuard::setTabWidget_system()
// {
//     ui->tabWidget_systen->setTabText(0,"Overview");
// }

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
    connect(ui->label_bhnamssd, &QLabel::linkActivated, this, [this](const QString &link){
        QDesktopServices::openUrl(QUrl(link));
        //writeLogFile->writeLog("Info","System","Click link BHNamSSD");
        //pushViewLog(writeLogFile->getFullMessLog());
    });

}

void EventGuard::connectLinkOpenWDF()
{
    QString linkOpenWDF = "<a href=\"#\">Open WDF</a>";

    ui->label_openWDF->setText(linkOpenWDF);
    ui->label_openWDF->setTextFormat(Qt::RichText);
    ui->label_openWDF->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->label_openWDF->setOpenExternalLinks(false);
    ui->label_openWDF->setCursor(Qt::PointingHandCursor);

    // Khi user click link -> run: mmc wf.msc
    connect(ui->label_openWDF, &QLabel::linkActivated, this, [this](const QString &)
    {
        writeLogFile->writeLog("Info","System","Open Windows Defender Firewall (Advanced Security)");
        pushViewLog(writeLogFile->getFullMessLog());
#ifdef Q_OS_WIN
        // Thử mở bằng đường dẫn tuyệt đối
        QString cmd = "C:\\Windows\\System32\\mmc.exe";
        QStringList args;
        args << "wf.msc";

        bool ok = QProcess::startDetached(cmd, args);
        if (!ok)
            qDebug() << "Cant run mmc wf.msc";
#else
        qDebug() << "Chức năng này chỉ hỗ trợ trên Windows.";
#endif
    });
    // writeLogFile->writeLog("Info","System","Run mmc wf.msc");
    // pushViewLog(writeLogFile->getFullMessLog());
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
    //writeLog("Info","App","Call restart");
    writeLogFile->writeLog("Info","App","Call restart");
    pushViewLog(writeLogFile->getFullMessLog());
}

void EventGuard::pushViewLog(QString messLog)
{
    //write to listWiew
    listViewLog.append(messLog);
    modelViewLog->setStringList(listViewLog);
    ui->listView_logSystem->setModel(modelViewLog);
    ui->listView_logSystem->setEditTriggers(QAbstractItemView::NoEditTriggers);     // Không cho sửa
}


//function question exit app
void EventGuard::exit_app()
{
    int choose = QMessageBox::question(this,"Exit","Do you want to exit the application?");
    if(choose == QMessageBox::Yes)
    {
        writeLogFile->writeLog("Info","System","The application stoped.");
        qApp->exit(1);
    }
    else if(choose == QMessageBox::No)
    {

    }
}









