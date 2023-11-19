#include "rentingservice.h"
#include "carmanagementservice.h"
#include "usermanagementservice.h"
#include <limits>
#include <QDebug>
RentingService::RentingService():city(SimpleTown::getInstance())
{

}

int RentingService::calculatePath(const Circle* position,const Circle* from, const Circle* destination, const bool taken=false)
{

    qDebug()<<"car should pass the "+QString::fromStdString(position->toString())+" circle";
    bool startTripWithTheUser=taken;
    if(taken)
    {

        if(position==destination)
        {
            return 0;
        }
    }
    else
    {
        if(position==from){
            startTripWithTheUser=true;
        }
    }


    if(destination->getName()>position->getName())
    {
        return 1+calculatePath(position->getParent().get(),from,destination,startTripWithTheUser);
    }
    if(position==destination)
    {
        return calculatePath(position,from,destination,startTripWithTheUser);
    }
    else{
        return 1+calculatePath(position->getChild().get(), from,destination,startTripWithTheUser);
    }

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

std::unique_ptr<RentResearchResult> RentingService::requestRent( int passegers, CarTypeName type, Location start, Location destination)
{

    std::unique_ptr<RentResearchResult> output;
    if(passegers<=0||passegers>7||type>2||start.getPosition()==nullptr||destination.getPosition()==nullptr)
    {
        return nullptr;
    }

    vector<Car*> cars;
    //Get cars that satisfy requirements
    for(const auto& car: CarManagementService::getInstance().getCars())
    {
        if(car.second->getTypeName()==CarTypeNameToString(type)&&passegers>0&&passegers<=car.second->getCapacity())
        {
            cars.push_back(car.second.get());
        }

    }
    vector<ResultItem> results;

    for(const auto& car : cars)
    {
        if(CarManagementService::getInstance().checkAviability(car->getLicensePlate()))
        {
            int distance=1+calculatePath(car->getLocation()->getPosition().get(),start.getPosition().get(),destination.getPosition().get());

            results.push_back(ResultItem(car,distance*5*car->getPrice(),distance));
        }
    }
    if(results.empty())
    {
        output=std::make_unique<RentResearchResult>(results,std::numeric_limits<float>::max());//no cars return a big time to indicate that there is no car in the stock
    }else{
        output=std::make_unique<RentResearchResult>(results,std::numeric_limits<float>::min());//no cars return a big time to indicate that there is no car in the stock

    }
    return output;

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
