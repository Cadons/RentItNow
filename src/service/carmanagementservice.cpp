#include "carmanagementservice.h"
#include "../repository/carsrepository.h"
#include "../service/rentingservice.h"
#include <mutex>
CarManagementService &CarManagementService::getInstance()
{
    static CarManagementService instance; // Guaranteed to be initialized only once.
    return instance;
}

bool CarManagementService::add(Car* newObject)
{

    if(newObject!=nullptr)
    {
        if(!this->myCars.empty())
            if (verifyLicensePlate(newObject->getLicensePlate()))
                return false;
        this->myCars[newObject->getLicensePlate()] = std::make_shared<Car>(*newObject);

      return save();
    }else{
            return false;
    }

}
bool CarManagementService::verifyLicensePlate(const string lp)
{
    return this->myCars.count(lp)>0;
}
bool CarManagementService::update(string lp, Car* updatedObject)
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
            if(updatedObject->getOwner()!=myCars[lp]->getOwner())
            myCars[lp].get()->setOwner(updatedObject->getOwner());
            return save();


    }else{
            return false;
    }

}
bool CarManagementService::remove(string licensePlate)
{
    if(verifyLicensePlate(licensePlate))
        return this->remove(myCars[licensePlate].get());
    return false;
}

bool CarManagementService::remove(Car* objectToDelete)
{
    if(objectToDelete!=nullptr&&myCars.size()>0){

            myCars.erase(objectToDelete->getLicensePlate());
        return save();


    }
    return false;
}


long long CarManagementService::getCarsCount()
{
    return this->myCars.size();
}

CarManagementService* CarManagementService::clearAll()
{
    this->myCars.clear();
    return this;
}

map<string,std::shared_ptr<Car>> CarManagementService::getCars()
{
    return this->myCars;
}

Car *CarManagementService::getCar(string licensePlate)
{
    if(licensePlate.empty())
        return nullptr;
    else
        return this->myCars[licensePlate].get();
}

bool CarManagementService::checkAviability(string lp)
{
    if(this->myCars.count(lp)==0)
        return false;
    if(this->myCars.at(lp)->needService())
        return false;

    if(this->myCars.at(lp)->getOwner()!=nullptr)
        return false;
    if(this->carsInMaintaince.count(lp)==0)
        return true;

    return false;
}

Location* CarManagementService::getCarLoaction(string lp)
{
    if(lp.empty()||!verifyLicensePlate(lp))
        return new Location();

    return this->myCars[lp]->getLocation().get();
}

float CarManagementService::getTraveledDistance(string lp)
{
    if(lp.empty()||!verifyLicensePlate(lp))
        return 0;

    return this->myCars[lp]->getTotalKm();
}

int CarManagementService::getNextServiceTime(string lp)
{
    if(lp.empty()||!verifyLicensePlate(lp))
        return -1;

    return(this->myCars[lp]->getKmBeforeService()/ this->myCars[lp]->getSpeed());
}

bool CarManagementService::putCarInMaintenance(string lp)
{

    if(lp.empty())
        return false;

    if(this->carsInMaintaince.count(lp)==0&&myCars.count(lp)>0&&myCars.at(lp)->needService())
    {

        if(RentingService::getInstance().getMyBank()->pay(300))
        {
                mutex.lock();
            this->carsInMaintaince[lp]=24;
                qDebug()<<lp+" in Maintenance";
                mutex.unlock();
        return true;
        }else{
        return false;
      }
    }
    return false;

}
void CarManagementService::updateMaintenanceStatus()
{
    //Check if there are cars that did not get enough money for the service and try to add new ones
    for (const auto& it : myCars)
    {
      if(carsInMaintaince.count(it.first)==0)
          if(it.second->needService())
            putCarInMaintenance(it.first);
    }
    mutex.lock();
    for (auto it = carsInMaintaince.begin(); it != carsInMaintaince.end(); ) {
      // Store the license plate before erasing the item
      string licensePlate = it->first;

      // Update the value
      it->second -= 1;

      // Check if the updated value is 0, then remove the item
      if (it->second == 0) {
        if (getCar(licensePlate) != nullptr) {
                getCar(licensePlate)->resetKm();
                qDebug() << licensePlate + " out of Maintenance";
        }

        // Erase the item using the stored iterator
        it = carsInMaintaince.erase(it);
      } else {
        ++it;
      }
    }
    mutex.unlock();
}

void CarManagementService::moveCar(string lp, Location& to)
{
    if(lp.empty())
        return;
    Car* car=getCar(lp);
    if(car!=nullptr){
        //TODO add km calc
        car->updateDistanceTraveled(5);
        car->setLocation(to);
        if(car->needService())
            putCarInMaintenance(lp);
        save();
    }

}

int CarManagementService::getMaintenanceTime(string lp)
{
    if(this->carsInMaintaince.count(lp)>0)
        return this->carsInMaintaince.at(lp);
    else
        return -1;
}

bool CarManagementService::save()
{
    return CarsRepository::getInstance().save(myCars);

}

bool CarManagementService::load()
{
    this->myCars=CarsRepository::getInstance().load();
    return true;
}

CarManagementService::CarManagementService()
{

    this->myCars=CarsRepository::getInstance().load();

}

CarManagementService::~CarManagementService()
{
    //Fast forwarding of service at the end of the simulation, in order to clean the list
    for (int i = 0; i < 24; i++) {
        this->updateMaintenanceStatus();
    }
    mutex.lock();
    CarsRepository::getInstance().save(myCars);
  mutex.unlock();

}
