#include "eventguard.h"
#include "./ui_eventguard.h"
#include "ip.h"
#include "dataDefinition.h"

EventGuard::EventGuard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EventGuard)
{
    ui->setupUi(this);

    modelViewLog = new QStringListModel(this);

    //setLogPathApp();
    writeLogFile = new WriteLog("EventGuard");

    //set Group Box Rule
    setGroupBox_ruleBlock();

    //create rule
    rule = new Rule();

    //create firewall
    fw_system = new FirewallManager();

    connectLink("https://github.com/BHNamSSD/EventGuard");
    connectLinkOpenWDF();

    writeLogFile->writeLog(writeLogFile->levelINFO(),"System","The application started successfully.");
    pushViewLog(writeLogFile->getFullMessLog());

    connect_slot();
    this->setWindowTitle(setVersion(VERSION));
}

//=====================================
//from Rule
void EventGuard::setGroupBox_ruleBlock()
{
    ui->lineEdit_ruleIP->setMaxLength(16);
    QRegularExpression rxRuleIP("^[0-9.]*$");
    QRegularExpressionValidator *validatorRuleIP = new QRegularExpressionValidator(rxRuleIP, this);
    ui->lineEdit_ruleIP->setValidator(validatorRuleIP);
    connect(ui->lineEdit_ruleIP, &QLineEdit::textChanged, this, [=](const QString &text)
    {
        if (text.length() >= ui->lineEdit_ruleIP->maxLength())
            ui->lineEdit_ruleIP->setStyleSheet("background-color: #ffcccc;");
        else
            ui->lineEdit_ruleIP->setStyleSheet("");
    });

    ui->lineEdit_rulePort->setValidator(new QIntValidator(0,65535,this));
    ui->lineEdit_rulePort->setMaxLength(5);


    ui->lineEdit_ruleName->setMaxLength(30);
    QRegularExpression rxRuleName("^[a-zA-Z0-9 _]*$");
    QRegularExpressionValidator *validatorRuleName = new QRegularExpressionValidator(rxRuleName, this);
    ui->lineEdit_ruleName->setValidator(validatorRuleName);

    connect(ui->lineEdit_ruleName, &QLineEdit::textChanged, this, [=](const QString &text)
    {
        if (text.length() >= ui->lineEdit_ruleName->maxLength())
            ui->lineEdit_ruleName->setStyleSheet("background-color: #ffcccc;");
        else
            ui->lineEdit_ruleName->setStyleSheet("");
    });
}

bool EventGuard::checkIPRule()
{

    QString textIP = ui->lineEdit_ruleIP->text();
    //qDebug() << textIP;
    if(!textIP.isEmpty())
    {
        IP checkIP;
        if(checkIP.isValidIPv4(textIP))
        {
            //qDebug() << textIP + " Valid IPv4";
            return true;
        }
        else
        {
            qDebug() << "Invalid IPv4 input format";
            writeLogFile->writeLog(writeLogFile->levelERROR(),"User","Invalid IPv4 input format");
            pushViewLog(writeLogFile->getFullMessLog());

        }
    }
    else
    {
        qDebug() << "IPv4 input is empty";
        writeLogFile->writeLog(writeLogFile->levelERROR(),"User","IPv4 input is empty");
        pushViewLog(writeLogFile->getFullMessLog());
    }

    return false;
}

void EventGuard::changePortRule(Qt::CheckState state)
{
    if (state == Qt::Checked) {
        onCheckBoxAnyPort();
    } else {
        offCheckBoxAnyPort();
    }
}

void EventGuard::onCheckBoxAnyPort()
{
    qDebug() << "Checkbox clicked";
    ui->lineEdit_rulePort->clear();
    ui->lineEdit_rulePort->setEnabled(false);

    ui->radioButton_TCP->setEnabled(false);
    ui->radioButton_UDP->setEnabled(false);

}

void EventGuard::offCheckBoxAnyPort()
{
    qDebug() << "Checkbox unclicked";
    ui->lineEdit_rulePort->clear();
    ui->lineEdit_rulePort->setEnabled(true);

    ui->radioButton_TCP->setEnabled(true);
    ui->radioButton_UDP->setEnabled(true);

}



bool EventGuard::checkRulePort()
{
    int port = ui->lineEdit_rulePort->text().toInt();
    if(port > 0 && port <= MAXPORT)
    {
        return true;
    }
    else
    {
        qDebug() << "Port incorrect";
        writeLogFile->writeLog(writeLogFile->levelERROR(),"User","Port incorrect");
        pushViewLog(writeLogFile->getFullMessLog());
    }
    return false;
}

bool EventGuard::checkBoxPort()
{
    //check Port
    if(ui->checkBox_ruleAnyPort->isChecked())
    {
        //protocol ANY
        qDebug() << "Checkbox clicked " TEXTANY;
        return true;
    }
    else
    {
        return false;
    }
}

QString EventGuard::getTCPorUDP()
{
    if(ui->radioButton_TCP->isChecked())
    {
        //TCP
        return TEXTTCP;
    }
    if(ui->radioButton_UDP->isChecked())
    {
        //UDP
        return TEXTUDP;
    }
    return TEXTNULL;
}

bool EventGuard::checkNameRule()
{

    if(!ui->lineEdit_ruleName->text().isEmpty())
    {
        return true;
    }
    else
    {
        qDebug() << "Rule Name is empty";
        writeLogFile->writeLog(writeLogFile->levelERROR(),"User","Rule Name is empty");
        pushViewLog(writeLogFile->getFullMessLog());
    }
    return false;
}

QString EventGuard::getInOutRule()
{
    if(ui->radioButton_ruleInbound->isChecked())
    {
        //IN
        return TEXTIN;
    }
    if(ui->radioButton_ruleOutbound->isChecked())
    {
        //OUT
        return TEXTOUT;
    }
    return TEXTNULL;
}

bool EventGuard::funcCheckNameAndInOrOUT()
{
    if(checkNameRule())
    {
        rule->setRuleName(ui->lineEdit_ruleName->text());

        if(getInOutRule() != TEXTNULL)
        {
            rule->setRuleInOut(getInOutRule());
            return true;
        }
        else
        {
            qDebug() << "ERROR: Add rule: IN/OUT check fail";
        }
    }
    else
    {
        qDebug() << "ERROR: Add rule: Rule Name check fail";
    }
    return false;
}

void EventGuard::addRuleBlockIP()
{
    QString mess;
    if(fw_system->blockIPPort(rule->getRuleIP(),rule->getRuleName(),rule->getRuleTCPorUDP(),rule->getRulePort(),rule->getRuleInOut()))
    {

        mess = QString("Blocked %1 Rule: %2 IP: %3 Port: %4 Protocol: %5").arg(rule->getRuleInOut(),
                                                                               rule->getRuleName(),
                                                                               rule->getRuleIP(),
                                                                               rule->getRulePort(),
                                                                               rule->getRuleTCPorUDP());
        writeLogFile->writeLog(writeLogFile->levelINFO(),"System",mess);
        pushViewLog(writeLogFile->getFullMessLog());
    }
    else
    {
        mess = "Dont create Rule";
        writeLogFile->writeLog(writeLogFile->levelERROR(),"System",mess);
        pushViewLog(writeLogFile->getFullMessLog());
    }

}

void EventGuard::clearGroupBox_ruleBlock()
{
    ui->lineEdit_ruleIP->clear();
    ui->lineEdit_rulePort->clear();
    ui->lineEdit_ruleName->clear();
    QString mess;
    mess = "Clear data input in group box rule";
    writeLogFile->writeLog(writeLogFile->levelINFO(),"System",mess);
    pushViewLog(writeLogFile->getFullMessLog());
}

void EventGuard::showFormAddRule()
{
    auto *formRule = new FormRulesDialog();
    formRule->setRuleData(rule);
    //giai phong con tro Rule
    formRule->setAttribute(Qt::WA_DeleteOnClose);
    int result = formRule->exec();
    if (result == QDialog::Accepted) {
        qDebug() << "User choose YES or OK";
    } else if (result == QDialog::Rejected) {
        qDebug() << "User choose NO or close dialog";
    }
}

bool EventGuard::checkAddRule()
{
    auto *formRule = new FormRulesDialog();
    formRule->setRuleData(rule);
    //giai phong con tro Rule
    formRule->setAttribute(Qt::WA_DeleteOnClose);
    int result = formRule->exec();
    if (result == QDialog::Accepted) {
        qDebug() << "User choose YES or OK";
        return true;
    } else if (result == QDialog::Rejected) {
        qDebug() << "User choose NO or close dialog";
    }
    return false;
}

void EventGuard::clickAddRule()
{
    if (!isRunningAsAdmin()) {
        //QMessageBox::warning(nullptr, "Quyền hạn",
        //                     "Ứng dụng cần chạy với quyền Administrator để thực hiện thao tác này.");
        QMessageBox::warning(this, "Decentralization policy",
                            "The application needs to run with Administrator rights to perform this operation.");

        writeLogFile->writeLog(writeLogFile->levelERROR(),"System","Current powers are not allowed to set rules");
        pushViewLog(writeLogFile->getFullMessLog());
    }
    else
    {
        //qDebug() << ui->lineEdit_ruleIP->text();
        if(checkIPRule())
        {
            rule->setRuleIP(ui->lineEdit_ruleIP->text());
            if(checkBoxPort())
            {
                qDebug() << "INFO: Add rule: Protocol: " TEXTANY;
                rule->setRulePort(TEXTNULL);
                rule->setRuleTCPorUDP(TEXTANY);

                if(funcCheckNameAndInOrOUT())
                {
                    //rule->test_getVailRuleCurrent();
                    //showFormAddRule();
                    if(checkAddRule())
                    {
                        addRuleBlockIP();
                        clearGroupBox_ruleBlock();
                    }
                }
            }
            else
            {
                qDebug() << "Port number and TCP or UDP";
                if(checkRulePort())
                {
                    rule->setRulePort(ui->lineEdit_rulePort->text());
                    if(getTCPorUDP() != "NULL")
                    {
                        rule->setRuleTCPorUDP(getTCPorUDP());
                    }
                    else
                    {
                        qDebug() << "ERROR: Add rule: TCP/UDP check fail";
                    }


                    if(funcCheckNameAndInOrOUT())
                    {
                        //rule->test_getVailRuleCurrent();
                        //showFormAddRule();
                        if(checkAddRule())
                        {
                            addRuleBlockIP();
                            clearGroupBox_ruleBlock();
                        }
                    }
                }
                else
                {
                    ui->lineEdit_rulePort->clear();
                    qDebug() << "ERROR: Add rule: Port check fail";
                }
            }
        }
        else
        {
            ui->lineEdit_ruleIP->clear();
            qDebug() << "ERROR: Add rule: IP check fail";
        }
    }
    //clear
    //ui->lineEdit_ruleIP->clear();

}

//=====================================

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

    connect(ui->pushButton_ruleAdd,SIGNAL(clicked(bool)),this, SLOT(clickAddRule()));

    //connect(ui->pushButton_ruleAdd,SIGNAL(clicked(bool)),this, SLOT(checkAddRule()));
    //check status (any port)
    connect(ui->checkBox_ruleAnyPort, &QCheckBox::checkStateChanged, this, &EventGuard::changePortRule);



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
    writeLogFile->writeLog(writeLogFile->levelINFO(),"App","Call restart");
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

bool EventGuard::isRunningAsAdmin()
{
    BOOL isAdmin = FALSE;
    PSID adminGroup = nullptr;

    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;

    if (AllocateAndInitializeSid(
            &NtAuthority,
            2,
            SECURITY_BUILTIN_DOMAIN_RID,
            DOMAIN_ALIAS_RID_ADMINS,
            0, 0, 0, 0, 0, 0,
            &adminGroup))
    {
        CheckTokenMembership(nullptr, adminGroup, &isAdmin);
        FreeSid(adminGroup);
    }

    return (isAdmin == TRUE);
}






