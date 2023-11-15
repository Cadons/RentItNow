#include "carmanagmentservice.h"

CarManagmentService &CarManagmentService::getInstance()
{
    static CarManagmentService instance; // Guaranteed to be initialized only once.
    return instance;
}

bool CarManagmentService::add(Car* newObject)
{

    if(newObject!=nullptr)
    {
        if(!this->myCars.empty())
            if (verifyLicensePlate(newObject->getLicensePlate()))
                return false;
        this->myCars[newObject->getLicensePlate()] = std::make_shared<Car>(*newObject);

            return true;
    }else{
            return false;
    }

}
bool CarManagmentService::verifyLicensePlate(const string lp)
{
    return !(this->myCars.find(lp)==this->myCars.end());
}
bool CarManagmentService::update(string lp, Car* updatedObject)
{
    //search the object by licencse plate
    if(lp!=""&&updatedObject!=nullptr&&myCars[lp]!=nullptr&&lp==updatedObject->getLicensePlate())
    {

            if(updatedObject->getBrand()!="")
            myCars[lp].get()->setBrand(updatedObject->getBrand());
            if(updatedObject->getName()!="")
            myCars[lp].get()->setName(updatedObject->getName());
            if(updatedObject->getKmBeforeService()>myCars[lp]->getKmBeforeService())
            myCars[lp].get()->resetKm();
            else{
            myCars[lp].get()->updateDistanceTraveled(myCars[lp]->getKmBeforeService()-updatedObject->getKmBeforeService());
            }
            if(updatedObject->getTotalKm()>myCars[lp]->getTotalKm())
            myCars[lp].get()->setTotalKm(updatedObject->getTotalKm());

           return true;


    }else{
            return false;
    }

}
bool CarManagmentService::remove(string licensePlate)
{
    if(verifyLicensePlate(licensePlate))
        return this->remove(myCars[licensePlate].get());
    return false;
}

bool CarManagmentService::remove(Car* objectToDelete)
{
    if(objectToDelete!=nullptr&&myCars.size()>0){

            myCars.erase(objectToDelete->getLicensePlate());
            return true;

    }
    return false;
}


long long CarManagmentService::getCarsCount()
{
    return this->myCars.size();
}

CarManagmentService* CarManagmentService::clearAll()
{
    this->myCars.clear();
    return this;
}

map<string,std::shared_ptr<Car>> CarManagmentService::getCars()
{
    return this->myCars;
}

Car *CarManagmentService::getCar(string licensePlate)
{
    if(licensePlate.empty())
        return nullptr;
    else
        return this->myCars[licensePlate].get();
}

bool CarManagmentService::checkAviability(string lp)
{
    if(this->carsInMaintaince.find(lp)!=this->carsInMaintaince.end())
        return true;
    return false;
}

Location CarManagmentService::getCarLoaction(string lp)
{
    if(lp.empty()||!verifyLicensePlate(lp))
        return Location();

    return this->myCars[lp]->getLocation();
}

float CarManagmentService::getTraveledDistance(string lp)
{
    if(lp.empty()||!verifyLicensePlate(lp))
        return 0;

    return this->myCars[lp]->getTotalKm();
}

int CarManagmentService::getNextServiceTime(string lp)
{
    if(lp.empty()||!verifyLicensePlate(lp))
        return -1;

    return(this->myCars[lp]->getKmBeforeService()/ this->myCars[lp]->getSpeed());
}

CarManagmentService::CarManagmentService()
{

}
