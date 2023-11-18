#include "usersrepository.h"
#include <QJsonDocument>
#include <QFile>
#include <QString>
#include "repositoryutils.h"

UsersRepository::UsersRepository()
{

}
//Can be generalized
std::map<std::string, std::shared_ptr<User> > UsersRepository::load()
{
    std::string json=RepositoryUtils::readFromFile(this->path);
    if(json=="-1")
    {
        return {};
    }
    else{
        QJsonDocument jsonDoc=QJsonDocument::fromJson(QString::fromStdString(json).toUtf8());
        QJsonObject jsonMap=jsonDoc.object();
        std::map<std::string,std::shared_ptr<User>> usersDb{};
        for(auto it=jsonMap.begin();it!=jsonMap.end();++it)
        {
            QJsonObject userObject = it.value().toObject();
            std::string userJsonStr = QJsonDocument(userObject).toJson(QJsonDocument::Compact).toStdString();

            usersDb[it.key().toStdString()] =convertJsonToObject(userJsonStr);
        }
        return usersDb;
    }
}
//Can be generalized
bool UsersRepository::save(std::map<std::string, std::shared_ptr<User> > data)
{
    QJsonObject jsonObject;
    for (auto it = data.begin(); it!=data.end();++it) {
        jsonObject[QString::fromStdString(it->second->getDrivingLicense())]=convertObjectToJson(*it->second);
    }
    QJsonDocument jsonDoc(jsonObject);
    std::string myJson=jsonDoc.toJson(QJsonDocument::Compact).toStdString();
    return RepositoryUtils::writeOnFile(myJson,this->path);
}

QJsonObject UsersRepository::convertObjectToJson(User obj)
{
    QJsonObject jsonObject;
    jsonObject["name"] = QString::fromStdString(obj.getName());
    jsonObject["surname"] = QString::fromStdString(obj.getSurname());
    jsonObject["address"] = QString::fromStdString(obj.getAddress());
    jsonObject["creditCard"] = QString::fromStdString(obj.getCreditCard());
    jsonObject["drivingLicense"] = QString::fromStdString(obj.getDrivingLicense());

    return jsonObject;
}

std::shared_ptr<User> UsersRepository::convertJsonToObject(std::string &obj)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(QString::fromStdString(obj).toUtf8());
    QJsonObject jsonObject=jsonDoc.object();
    std::shared_ptr<User> user;
    std::string name = jsonObject["name"].toString().toStdString();
    std::string surname = jsonObject["surname"].toString().toStdString();
    std::string address = jsonObject["address"].toString().toStdString();
    std::string creditCard = jsonObject["creditCard"].toString().toStdString();
    std::string drivingLicense = jsonObject["drivingLicense"].toString().toStdString();
    return std::make_shared<User>(name, surname, address,creditCard, drivingLicense);
}

UsersRepository &UsersRepository::getInstance()
{
    static UsersRepository instance;
    return instance;
}
