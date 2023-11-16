#include "repositoryutils.h"
#include "qjsondocument.h"


std::string RepositoryUtils::convertJsonToString(QJsonObject obj)
{
    QJsonDocument jsonDocument(obj);

    QByteArray jsonString = jsonDocument.toJson(QJsonDocument::Compact);
    QString jsonStringString = QString::fromUtf8(jsonString);
    return jsonStringString.toStdString();
}
