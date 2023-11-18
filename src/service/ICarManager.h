#ifndef ICARMANAGER_H
#define ICARMANAGER_H

#include <map>
#include <memory>

#include "ICrud.h"
#include "../model/car.h"
class ICarManager:public ICrud<string,Car*>
{
public:

    virtual map<string,std::shared_ptr<Car>> getCars()=0;
    virtual Car* getCar(string licensePlate)=0;

    virtual bool checkAviability(string lp)=0;
    virtual Location* getCarLoaction(string lp)=0;
    virtual float getTraveledDistance(string lp)=0;
    virtual int getNextServiceTime(string lp)=0;//return how many km remains for the next service
    virtual void putCarInMaintenance(string ls)=0;
    virtual void updateMaintenanceStatus()=0;//this method should be performed every tick (1 tick=1 hour in the simulation)

};
#endif // ICARMANAGER_H
