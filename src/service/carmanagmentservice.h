#ifndef CARMANAGMENTSERVICE_H
#define CARMANAGMENTSERVICE_H

#include "ICrud.h"
#include "../model/car.h"
#include <map>
#include <memory>
#include "../model/location.h"

class CarManagmentService: ICrud<string,Car*>
{
private:
  CarManagmentService();

    map<string,std::shared_ptr<Car>> myCars;
    map<string,int> carsInMaintaince;//this map composed by lp and time that remain before the end of service time

    bool verifyLicensePlate(const string lp);

public:
    static CarManagmentService& getInstance();

    bool add(Car* newObject) override;
    bool update(string oldObject, Car* updatedObject) override;
    bool remove(Car* objectToDelete) override;
    bool remove(string licensePlate);
    long long getCarsCount();
    CarManagmentService* clearAll();
    map<string,std::shared_ptr<Car>> getCars();
    Car* getCar(string licensePlate);

    bool checkAviability(string lp);
    Location getCarLoaction(string lp);
    float getTraveledDistance(string lp);
    int getNextServiceTime(string lp);//return how many km remains for the next service






};

#endif // CARMANAGMENTSERVICE_H
