#include "car.h"


void Car::setLicensePlate(const string &newLicensePlate)
{
    licensePlate = newLicensePlate;
}

string Car::getName() const
{
    return name;
}

void Car::setName(const string &newName)
{
    name = newName;
}

string Car::getBrand() const
{
    return brand;
}

void Car::setBrand(const string &newBrand)
{
    brand = newBrand;
}

string Car::getLicensePlate() const
{
    return licensePlate;
}
int Car::getCapacity(){
    return type.CAPACITY;
}
float Car::getSpeed(){
    return type.SPEED;
}
float Car::getPrice(){
    return type.PRICE;
}

bool Car::needService()
{
    return !(this->kmBeforeService>0);
}

bool Car::updateDistanceTraveled(int km)
{
    if(km<0||km>this->kmBeforeService)
        return false;
    else
    {
        if((this->kmBeforeService-km)>=0)
        {
            this->kmBeforeService-=km;
            return true;
        }else{
            this->kmBeforeService=0;
            return false;
        }
    }

}

int Car::getKmBeforeService() const
{
    return kmBeforeService;
}

Car Car::resetKm()
{
    this->kmBeforeService=1500;
    return *this;
}



Car::Car(const string &name, const string &brand, const string &licensePlate, const CarType &carType) : name(name),
    brand(brand),
    licensePlate(licensePlate),
    type(carType)
{}
// Copy constructor
Car::Car(const Car &other)
    : name(other.name), brand(other.brand), licensePlate(other.licensePlate), kmBeforeService(other.kmBeforeService), type(other.type)
{
}
