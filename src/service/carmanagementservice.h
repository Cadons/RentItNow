#ifndef CARMANAGEMENTSERVICE_H
#define CARMANAGEMENTSERVICE_H

#include "ICarManager.h"
#include "../model/car.h"
#include <map>
#include <memory>
#include "../model/location.h"

class CarManagementService: public ICarManager
{
private:
    CarManagementService();
    virtual ~CarManagementService();

    map<string,std::shared_ptr<Car>> myCars;
    map<string,int> carsInMaintaince;//this map composed by lp and time that remain before the end of service time

    bool verifyLicensePlate(const string lp);

public:
    static CarManagementService& getInstance();

    bool add(Car* newObject) override;
    bool update(string oldObject, Car* updatedObject) override;
    bool remove(Car* objectToDelete) override;
    bool remove(string licensePlate) override;
    long long getCarsCount();
    CarManagementService* clearAll();
    map<string,std::shared_ptr<Car>> getCars() override;
    Car* getCar(string licensePlate) override;

    bool checkAviability(string lp) override;
    Location* getCarLoaction(string lp) override;
    float getTraveledDistance(string lp) override;
    int getNextServiceTime(string lp) override;//return how many km remains for the next service
    bool putCarInMaintenance(string lp) override;
    void updateMaintenanceStatus() override;//this method should be performed every tick (1 tick=1 hour in the simulation)
    void moveCar(string lp, Location& to) override;
    int getMaintenanceTime(string lp);


    // ICarManager interface
public:
    bool save() override;
    bool load() override;
};

#endif // CARMANAGEMENTSERVICE_H
