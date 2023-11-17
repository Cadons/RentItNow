#include "carsrepository.h"
#include "model/deluxecar.h"
#include "model/ecocar.h"
#include "model/midclasscar.h"
#include "repository/repositoryutils.h"


#include <QJsonDocument>
#include <QFile>
#include <QString>
CarsRepository::CarsRepository()
{

}

std::map<string, std::shared_ptr<Car> > CarsRepository::load()
{
    std::string json=RepositoryUtils::readFromFile(this->path);
    if(json=="-1")
    {
       return {};
    }
    else{
       QJsonDocument jsonDoc=QJsonDocument::fromJson(QString::fromStdString(json).toUtf8());
       QJsonObject jsonMap=jsonDoc.object();
       std::map<string,std::shared_ptr<Car>> carsDb{};
       for(auto it=jsonMap.begin();it!=jsonMap.end();++it)
       {
           QJsonObject carObject = it.value().toObject();
           std::string carJsonStr = QJsonDocument(carObject).toJson(QJsonDocument::Compact).toStdString();

           carsDb[it.key().toStdString()] =convertJsonToObject(carJsonStr);
       }
       return carsDb;
    }
}

bool CarsRepository::save(std::map<string, std::shared_ptr<Car> > data)
{
    if(data.empty())
        return false;
    QJsonObject jsonObject;
    for (auto it = data.begin(); it!=data.end();++it) {
        jsonObject[QString::fromStdString(it->second->getLicensePlate())]=convertObjectToJson(*it->second);
    }
    QJsonDocument jsonDoc(jsonObject);
    std:string myJson=jsonDoc.toJson(QJsonDocument::Compact).toStdString();
    return RepositoryUtils::writeOnFile(myJson,this->path);
}



QJsonObject CarsRepository::convertObjectToJson(Car obj)
{
    QJsonObject jsonCar;
    jsonCar["name"]=QString::fromStdString(obj.getName());
    jsonCar["brand"]=QString::fromStdString(obj.getBrand());
    jsonCar["lp"]=QString::fromStdString(obj.getLicensePlate());
    jsonCar["type"]=QString::fromStdString(obj.getTypeName());
    jsonCar["km_to_service"]=obj.getKmBeforeService();
    jsonCar["total_km"]=obj.getTotalKm();
    return jsonCar;
}

std::shared_ptr<Car> CarsRepository::convertJsonToObject(string &obj)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(QString::fromStdString(obj).toUtf8());
    QJsonObject jsonObject=jsonDoc.object();
    string type=jsonObject["type"].toString().toStdString();
     std::shared_ptr<Car> car;
    string name=jsonObject["name"].toString().toStdString();
    string brand=jsonObject["brand"].toString().toStdString();
    string lp=jsonObject["lp"].toString().toStdString();
    int kmservice=jsonObject["km_to_service"].toInt();
    int kmTot=jsonObject["total_km"].toInt();
    //Can be improved with chain of responsability
    if(type=="ECO")
    {
        car= std::make_shared<EcoCar>(name,brand,lp);
        car->setTotalKm(kmTot);
        car->setKmBeforeService(kmservice);
        return car;
    }else if(type=="MID-CLASS"){
        car=std::make_shared<MidClassCar>(name,brand,lp);
        car->setTotalKm(kmTot);
        car->setKmBeforeService(kmservice);
        return car;
    }else if(type=="DELUXE"){
        car=std::make_shared<DeluxeCar>(name,brand,lp);

    }else{
        return nullptr;
    }
    car->setTotalKm(kmTot);
    car->setKmBeforeService(kmservice);
    return car;
}

CarsRepository &CarsRepository::getInstance()
{
    static CarsRepository instance;
    return instance;
}


