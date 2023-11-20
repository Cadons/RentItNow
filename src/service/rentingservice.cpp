#include "rentingservice.h"
#include "carmanagementservice.h"
#include "usermanagementservice.h"
#include <limits>
#include <QDebug>
#include "../repository/bankrepository.h"
RentingService::RentingService():city(SimpleTown::getInstance())
{

    this->myBank=   BankRepository::getInstance().load();
    if(this->myBank==nullptr)
    {
         this->myBank=   std::make_unique<Bank>();
    }


}

RentingService::~RentingService()
{
    BankRepository::getInstance().save(this->myBank.get());
}

int RentingService::calculatePath(std::shared_ptr<Circle> position,const std::shared_ptr<Circle> from, const std::shared_ptr<Circle> destination, const bool taken=false)
{
    Location pos;
    pos.setPosition(position);
    tmpPath.push_back(pos);
    qDebug()<<"car should pass the "+QString::fromStdString(position->toString())+" circle";
    bool startTripWithTheUser=taken;
    if(from==position&&position==destination)
    {
        return 0;
    }
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


    if(startTripWithTheUser)
    {
        if(destination->getName()>position->getName())
        {

            return 1+calculatePath(position->getParent(),from,destination,startTripWithTheUser);
        }
        else{
            return 1+calculatePath(position->getChild(), from,destination,startTripWithTheUser);
        }
    }else{
        if(from->getName()>position->getName())
        {

            return 1+calculatePath(position->getParent(),from,destination,startTripWithTheUser);
        }
        else{
            return 1+calculatePath(position->getChild(), from,destination,startTripWithTheUser);
        }
    }


}

Bank*RentingService::getMyBank() const
{
    return myBank.get();
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
    float waitTime=std::numeric_limits<float>::max();
    for(const auto& car : cars)
    {
        if(CarManagementService::getInstance().checkAviability(car->getLicensePlate()))
        {
            int distance=1+calculatePath(car->getLocation()->getPosition(),start.getPosition(),destination.getPosition());
            if((distance*5)<=car->getKmBeforeService())
            {
                results.push_back(ResultItem(car,distance*5*car->getPrice(),distance, tmpPath));
                tmpPath.clear();
            }else{

                waitTime=CarManagementService::getInstance().getMaintenanceTime(car->getLicensePlate());
                if(waitTime==-1)
                    waitTime=24;
            }

        }else{

            if(CarManagementService::getInstance().getMaintenanceTime(car->getLicensePlate())>0)
                if(CarManagementService::getInstance().getMaintenanceTime(car->getLicensePlate())<waitTime)//get the minumum wait time
                    waitTime=CarManagementService::getInstance().getMaintenanceTime(car->getLicensePlate());
        }
    }
    if(results.empty())
    {
        output=std::make_unique<RentResearchResult>(results,waitTime);
    }else{
        output=std::make_unique<RentResearchResult>(results,std::numeric_limits<float>::min());//no cars return a big time to indicate that there is no car in the stock

    }
    return output;

}

bool RentingService::rent(string lp, string dl, float price)
{
    Car* car= CarManagementService::getInstance(). getCar(lp);
    User* user= UserManagementService::getInstance(). getUser(dl);
    for(const auto& car: CarManagementService::getInstance().getCars())
    {
        if(user==car.second->getOwner())
            return false;//user can rent only a car at a time
    }
  if(car!=nullptr&&user!=nullptr){
        if(CarManagementService::getInstance().checkAviability(lp))
        {
           this->myBank->deposit(price);
            BankRepository::getInstance().save(this->myBank.get());
            car->setOwner(user);

            qDebug()<<"Payment completed";
              return CarManagementService::getInstance().save();
        }

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
