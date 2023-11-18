#include "rentingservice.h"
#include "carmanagementservice.h"
#include "usermanagementservice.h"
RentingService::RentingService():city(SimpleTown::getInstance())
{

}

SimpleTown &RentingService::getCity() const
{
    return city;
}

Location RentingService::getLocation(string lp)
{
    auto loc=CarManagementService::getInstance(). getCar(lp)->getLocation();
    Location returnLocation;
    if(loc!=nullptr)
    {
        returnLocation.setPosition(loc->getPosition());
    }
    return returnLocation;
}

RentResearchResult &RentingService::requestRent(string dl, int passegers, CarType type, Location start, Location destination)
{
//TODO
}

bool RentingService::rent(string lp, string dl)
{
    Car* car= CarManagementService::getInstance(). getCar(lp);
    User* user= UserManagementService::getInstance(). getUser(dl);
    if(car!=nullptr&&user!=nullptr){
        car->setOwner(user);
        return true;
    }
    return false;
}

bool RentingService::release(string lp, string dl)
{
    if(lp.empty()||dl.empty()|| CarManagementService::getInstance(). getCar(lp)==nullptr|| CarManagementService::getInstance(). getCar(lp)->getOwner()->getDrivingLicense()!=dl){
        return false;
    }
    CarManagementService::getInstance(). getCar(lp)->setOwner(nullptr);
    return true;
}

RentingService &RentingService::getInstance()
{
    static RentingService instance;
    return instance;
}
