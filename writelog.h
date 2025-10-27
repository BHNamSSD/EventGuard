#ifndef WRITELOG_H
#define WRITELOG_H

#include <QDir>
#include <QString>
#define LOGDIR "/logs"
#define LOG ".log"
#include <QDebug>

#define TRACE "TRACE"
#define DEBUG "DEBUG"
#define INFO "INFO"
#define WARN "WARN"
#define ERROR "ERROR"
#define CRITICAL "CRITICAL"



class WriteLog
{
public:
    WriteLog();
    WriteLog(QString); //create in put name file log
    void writeLog(const QString &,const QString &,const QString &);
    QString getFullMessLog();

    QString levelTRACE()
    {
        return TRACE;
    }

    QString levelDEBUG()
    {
        return DEBUG;
    }

    QString levelINFO()
    {
        return INFO;
    }

    QString levelWARN()
    {
        return WARN;
    }

    QString levelERROR()
    {
        return ERROR;
    }

    QString levelCRITICAL()
    {
        return CRITICAL;
    }

private:
    QString logDirApp;
    QString logPath_nameFile;
    QString fullMessLog;
    void setLogPathApp(QString nameFileLog)
    {
        logDirApp = QDir::currentPath() + LOGDIR;   // Thư mục lưu log
        QDir().mkpath(logDirApp);                   // Tạo thư mục nếu chưa có
        logPath_nameFile = logDirApp + "/" +nameFileLog + LOG;     // Đường dẫn file log
    }
};

#endif // WRITELOG_H
