#ifndef WRITELOG_H
#define WRITELOG_H

#include <QDir>
#include <QString>
#define LOGDIR "/logs"
#define LOG ".log"
#include <QDebug>

class WriteLog
{
public:
    WriteLog();
    WriteLog(QString); //create in put name file log
    void writeLog(const QString &,const QString &,const QString &);
    QString getFullMessLog();

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
