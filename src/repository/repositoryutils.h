#ifndef REPOSITORYUTILS_H
#define REPOSITORYUTILS_H

#include <string>
#include <QJsonObject>
class RepositoryUtils
{
public:
    static std::string convertJsonToString(QJsonObject obj);

};

#endif // REPOSITORYUTILS_H
