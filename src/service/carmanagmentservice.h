#ifndef CARMANAGMENTSERVICE_H
#define CARMANAGMENTSERVICE_H

#include "ICarManager.h"
#include "../model/car.h"
#include <map>
#include <memory>
#include "../model/location.h"

class CarManagmentService: public ICarManager
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
    map<string,std::shared_ptr<Car>> getCars() override;
    Car* getCar(string licensePlate) override;

    bool checkAviability(string lp) override;
    Location getCarLoaction(string lp) override;
    float getTraveledDistance(string lp) override;
    int getNextServiceTime(string lp) override;//return how many km remains for the next service
    void putCarInMaintenance(string ls) override;
    void updateMaintenanceStatus() override;//this method should be performed every tick (1 tick=1 hour in the simulation)


};

#endif // CARMANAGMENTSERVICE_H
