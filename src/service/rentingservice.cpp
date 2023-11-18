#include "rentingservice.h"
#include "carmanagementservice.h"
#include "usermanagementservice.h"
RentingService::RentingService()
{
    this->outer=std::make_shared<Circle>(CircleType::OUTER);
    std::shared_ptr<Circle> middle=std::make_shared<Circle>(CircleType::MIDDLE);
    std::shared_ptr<Circle> inner=std::make_shared<Circle>(CircleType::INNER);

    outer->setChild(middle)->setChild(inner);
    inner->setParent(middle)->setParent(outer);
    this->inner=inner;
}

std::shared_ptr<Circle> RentingService::getOuterCity() const
{
    return outer;
}

std::shared_ptr<Circle> RentingService::getInnerCity() const
{
    return inner;
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

}

bool RentingService::rent(string lp, string dl)
{
    Car* car= CarManagementService::getInstance(). getCar(lp);
    User* user= UserManagementService::getInstance(). getUser(dl);
    if(car!=nullptr&&user!=nullptr){
        car->setOwner(user);

    }
}

bool RentingService::release(string lp, string dl)
{

    CarManagementService::getInstance(). getCar(lp)->setOwner(nullptr);
}

RentingService &RentingService::getInstance()
{
    static RentingService instance;
    return instance;
}
