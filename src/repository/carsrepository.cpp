#include "carsrepository.h"
#include "../model/deluxecar.h"
#include "../model/ecocar.h"
#include "../model/midclasscar.h"
#include "repositoryutils.h"
#include "../service/rentingservice.h"
#include "../service/usermanagementservice.h"


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

    QJsonObject jsonObject;
    for (auto it = data.begin(); it!=data.end();++it) {
        jsonObject[QString::fromStdString(it->second->getLicensePlate())]=convertObjectToJson(it->second.get());
    }
    QJsonDocument jsonDoc(jsonObject);
    std::string myJson=jsonDoc.toJson(QJsonDocument::Compact).toStdString();
    return RepositoryUtils::writeOnFile(myJson,this->path);
}



QJsonObject CarsRepository::convertObjectToJson(Car* obj)
{
    QJsonObject jsonCar;
    jsonCar["name"]=QString::fromStdString(obj->getName());
    jsonCar["brand"]=QString::fromStdString(obj->getBrand());
    jsonCar["lp"]=QString::fromStdString(obj->getLicensePlate());
    jsonCar["type"]=QString::fromStdString(obj->getTypeName());
    jsonCar["km_to_service"]=obj->getKmBeforeService();
    jsonCar["total_km"]=obj->getTotalKm();
    jsonCar["location"]=QString::fromStdString(obj->getLocation().get()->getPosition()->toString());
    if(obj->getOwner()!=nullptr)
        jsonCar["owner"]=QString::fromStdString(obj->getOwner()->getDrivingLicense());
    else
        jsonCar["owner"]=QString("null");
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
    string location=jsonObject["location"].toString().toStdString();
    Location carLocation;
    if(location=="Inner")
    {
        carLocation.setPosition(RentingService::getInstance().getCity().getInner());
    }else if(location=="Middle")
    {
        carLocation.setPosition(RentingService::getInstance().getCity().getInner()->getParent());

    }else{
        carLocation.setPosition(RentingService::getInstance().getCity().getOuter());

    }
    User* owner;
    //When recover cars from db reset all rents, uncomment to recover rented car in the past sessions
   /* if(jsonObject["owner"].toString().toStdString()!="null")
        owner=UserManagementService::getInstance().getUser(jsonObject["owner"].toString().toStdString());
    else*/
        owner=nullptr;
    //Can be improved with chain of responsability
    if(type=="ECO")
    {
        car= std::make_shared<EcoCar>(name,brand,lp);


    }else if(type=="MID-CLASS"){
        car=std::make_shared<MidClassCar>(name,brand,lp);


        return car;
    }else if(type=="DELUXE"){
        car=std::make_shared<DeluxeCar>(name,brand,lp);

    }else{
        return nullptr;
    }

    car->setOwner(owner);

    car->setLocation(carLocation);
    car->setTotalKm(kmTot);
    car->setKmBeforeService(kmservice);
    return car;
}

CarsRepository &CarsRepository::getInstance()
{
    static CarsRepository instance;
    return instance;
}


