#include "eventguard.h"
#include "./ui_eventguard.h"

EventGuard::EventGuard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EventGuard)
{
    ui->setupUi(this);
    connect_slot();
    modelLog = new QStringListModel(this);

    //Call function setLogPathApp
    setLogPathApp();


    connectLink("https://github.com/BHNamSSD/EventGuard");
    //ui->listView_logSystem->setModel(logModel);
    writeLog("Info","System","Ứng dụng khởi động thành công.");
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
    writeLog("Info","App","Call restart");
}

void EventGuard::setLogPathApp()
{
    logDirApp = QDir::currentPath() + LOGDIR;   // Thư mục lưu log
    QDir().mkpath(logDirApp);                            // Tạo thư mục nếu chưa có
    logPath_EventGuard = logDirApp + lOGNAMEFILE;     // Đường dẫn file log
}

//function write log
void EventGuard::writeLog(const QString &level, const QString &category, const QString &message)
{
    //QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd'T'HH:mm:ss.zzz");
    //QString time = QDateTime::currentDateTime().toString(Qt::ISODateWithMs);
    QString time = QDateTime::currentDateTime()
                       .toTimeZone(QTimeZone::systemTimeZone())
                       .toString(Qt::ISODateWithMs);

    QString fullMsg = QString("[%1] [%2] [%3] - %4").arg(time, level, category, message);

    //write to listWiew
    listLog.append(fullMsg);
    modelLog->setStringList(listLog);
    ui->listView_logSystem->setModel(modelLog);
    ui->listView_logSystem->setEditTriggers(QAbstractItemView::NoEditTriggers);     // Không cho sửa

    //write to file: /log/EventGuard.log
    //qDebug() << logPathApp;

    QFile file(logPath_EventGuard);
    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&file);
        out << fullMsg << "\n";
        file.close();
    }

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









