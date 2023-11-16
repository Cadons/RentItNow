#include "carsrepository.h"
#include "model/deluxecar.h"
#include "model/ecocar.h"
#include "model/midclasscar.h"


#include <QJsonDocument>
#include <QFile>
#include <QString>
CarsRepository::CarsRepository()
{

}

std::map<string, std::shared_ptr<Car> > CarsRepository::load()
{
    return {};
}

bool CarsRepository::save(std::map<string, std::shared_ptr<Car> > data)
{
    if(data.empty())
        return false;

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

Car* CarsRepository::convertJsonToObject(string &obj)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(QString::fromStdString(obj).toUtf8());
    QJsonObject jsonObject=jsonDoc.object();
    string type=jsonObject["type"].toString().toStdString();
    Car* car;
    string name=jsonObject["name"].toString().toStdString();
    string brand=jsonObject["brand"].toString().toStdString();
    string lp=jsonObject["lp"].toString().toStdString();
    int kmservice=jsonObject["km_to_service"].toInt();
    int kmTot=jsonObject["total_km"].toInt();
    if(type=="ECO")
    {
        car=new EcoCar(name,brand,lp);
        car->setTotalKm(kmTot);
        car->setKmBeforeService(kmservice);
        return car;
    }else if(type=="MID-CLASS"){
        car=new MidClassCar(name,brand,lp);
        car->setTotalKm(kmTot);
        car->setKmBeforeService(kmservice);
        return car;
    }else if(type=="DELUXE"){
        car=new DeluxeCar(name,brand,lp);

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


