#ifndef REPOSITORYUTILS_H
#define REPOSITORYUTILS_H

#include <string>
#include <QJsonObject>
class RepositoryUtils
{
public:
    static std::string convertJsonToString(QJsonObject obj);
    static bool writeOnFile(std::string content,std::string filename);
    static std::string readFromFile(std::string filename);
};

#endif // REPOSITORYUTILS_H
