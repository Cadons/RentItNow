#include "repositoryutils.h"
#include "qjsondocument.h"
#include <QFile>

std::string RepositoryUtils::convertJsonToString(QJsonObject obj)
{
    QJsonDocument jsonDocument(obj);

    QByteArray jsonString = jsonDocument.toJson(QJsonDocument::Compact);
    QString jsonStringString = QString::fromUtf8(jsonString);
    return jsonStringString.toStdString();
}

bool RepositoryUtils::writeOnFile(std::string content, std::string filename)
{
    QString filePath = QString::fromStdString(filename);

    QFile file(filePath);
    if(file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
         QTextStream out(&file);
        out<<QString::fromStdString(content);
         file.close();
        qDebug() << "File successfully written.";
         return true;
    }
    return false;

}

std::string RepositoryUtils::readFromFile(std::string filename)
{
    QString filePath = QString::fromStdString(filename);
    QString content;
    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream in(&file);
        content=in.readAll();
        file.close();
        qDebug() << "File successfully red.";
        return content.toStdString();
    }
    return "-1";
}
