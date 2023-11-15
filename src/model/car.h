#ifndef CAR_H
#define CAR_H

#include "cartype.h"
#include <stdlib.h>
#include <string>
using namespace std;
class Car
{
public:

    Car(const string &name, const string &brand, const string &licensePlate, const CarType &carType);
    Car(const Car &other);
    void setLicensePlate(const string &newLicensePlate);

    string getName() const;
    void setName(const string &newName);
    string getBrand() const;
    void setBrand(const string &newBrand);
    string getLicensePlate() const;
    int getCapacity();
    float getSpeed();
    float getPrice();
    bool needService();
    bool updateDistanceTraveled(int km);
    int getKmBeforeService() const;
    Car resetKm();

private:
    string name="";
    string brand="";
    string licensePlate="";
    int kmBeforeService=1500;
    const CarType type;




};

#endif // CAR_H
