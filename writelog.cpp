#include "writelog.h"

WriteLog::WriteLog(QString nameFileLog)
{
    setLogPathApp(nameFileLog);
}

void WriteLog::writeLog(const QString &level, const QString &category, const QString &message)
{
    QString time = QDateTime::currentDateTime()
    .toTimeZone(QTimeZone::systemTimeZone())
        .toString(Qt::ISODateWithMs);
    //QString fullMsg = QString("%1 [%2] [%3] - %4").arg(time, level, category, message);
    fullMessLog = QString("%1 [%2] [%3] - %4").arg(time, level, category, message);

    //write to fileLog
    QFile file(logPath_nameFile);
    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&file);
        out << fullMessLog << "\n";
        file.close();
    }
    qDebug() << logPath_nameFile;
}

QString WriteLog::getFullMessLog()
{
    return fullMessLog;
}


