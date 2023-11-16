#include "car.h"

#include <typeinfo>

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

string Car::getTypeName() const
{
    return type.TYPE_NAME;
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
            this->setTotalKm(km);
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

bool Car::operator ==(const Car &other) const
{
    if (this != &other && this->name == other.name &&
        this->brand == other.brand && this->licensePlate == other.licensePlate &&
        this->kmBeforeService == other.kmBeforeService && typeid(this->type) == typeid(other.type))
    {
        return true;
    }

    return false;
}

string Car::toString()
{
    std::string result;
    result += "Name: " + name + "\n";
    result += "Brand: " + brand + "\n";
    result += "License Plate: " + licensePlate + "\n";

    // Assuming CarType has a getTypeName() method
    const std::string carTypeName =  typeid(type).name();
    result += "Car Type: " + carTypeName + "\n";

    result += "Kilometers Before Service: " + std::to_string(kmBeforeService) + "\n";
    // Include other details as needed

    return result;
}

float Car::getTotalKm() const
{
    return totalKm;
}

void Car::setTotalKm(float kmToAdd)
{
    if(kmToAdd>0)
        totalKm += kmToAdd;
}

Location Car::getLocation() const
{
    return this->location;
}

void Car::setLocation(const Location &newLocation)
{
    this->location = newLocation;
}



Car::Car(const string &name, const string &brand, const string &licensePlate, const CarType &carType) : name(name),
    brand(brand),
    licensePlate(licensePlate),
    type(carType)
{}
// Copy constructor
Car::Car(const Car &other)
    : name(other.name), brand(other.brand), licensePlate(other.licensePlate), kmBeforeService(other.kmBeforeService), type(other.type), totalKm(other.totalKm)
{
}
