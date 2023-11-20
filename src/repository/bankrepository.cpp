#include "bankrepository.h"
#include "repositoryutils.h"
#include "qjsondocument.h"

BankRepository::BankRepository()
{

}
bool BankRepository::save(Bank* data)
{
    QJsonObject jsonObject;

    jsonObject["bank"]=convertObjectToJson(data);

    QJsonDocument jsonDoc(jsonObject);
    std::string myJson=jsonDoc.toJson(QJsonDocument::Compact).toStdString();
    return RepositoryUtils::writeOnFile(myJson,this->path);
}

std::unique_ptr<Bank> BankRepository::load()
{
    std::string json=RepositoryUtils::readFromFile(this->path);
    if(json=="-1")
    {
        return {};
    }
    else{
        QJsonDocument jsonDoc=QJsonDocument::fromJson(QString::fromStdString(json).toUtf8());
        QJsonObject jsonMap=jsonDoc.object();
        std::unique_ptr<Bank> bank;
        for(auto it=jsonMap.begin();it!=jsonMap.end();++it)
        {
            QJsonObject carObject = it.value().toObject();
            std::string carJsonStr = QJsonDocument(carObject).toJson(QJsonDocument::Compact).toStdString();
            bank =convertJsonToObject(carJsonStr);
        }
        return bank;
    }
}


QJsonObject BankRepository::convertObjectToJson(Bank *obj)
{
    QJsonObject jsonBank;
    jsonBank["balance"]=obj->getBalance();

    return jsonBank;
}

std::unique_ptr<Bank> BankRepository::convertJsonToObject(std::string &obj)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(QString::fromStdString(obj).toUtf8());
    QJsonObject jsonObject=jsonDoc.object();
    std::unique_ptr<Bank> bank;
    float balance=(float)jsonObject["balance"].toDouble();
    bank=std::make_unique<Bank>(balance);

    return bank;
}

BankRepository &BankRepository::getInstance()
{
    static BankRepository instance;
    return instance;
}
