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
        if(!verifyLicensePlate(newObject->getLicensePlate()))
            return false;
        Car* registerCar=newObject;
        this->myCars.push_back(std::make_unique<Car>(*registerCar));
            return true;
    }else{
            return false;
    }

}
bool CarManagmentService::verifyLicensePlate(const string lp)
{
    for (const auto& car : myCars) {
            if(car->getLicensePlate()==lp)
                return false;//return false if there is already a car with that lp
    }
    return true;

}
bool CarManagmentService::update(Car* oldObject, Car* updatedObject)
{
    //search the object by licencse plate
    if(oldObject!=nullptr&&updatedObject!=nullptr)
    {
            for(const auto& car : myCars){
                if(car.get()==oldObject)
                {
                    if(updatedObject->getBrand()!="")
                    car->setBrand(updatedObject->getBrand());
                       if(updatedObject->getName()!="")
                    car->setName(updatedObject->getName());
                    return true;
                }else{
                    return false;
                }
            }

    }else{
            return false;
    }

}

bool CarManagmentService::remove(Car* objectToDelete)
{
    if(objectToDelete!=nullptr&&myCars.size()>0){

            int myIndex=findCarIndex(objectToDelete);
            myCars.erase(myCars.begin()+myIndex);
            return true;

    }
    return false;
}
int CarManagmentService::findCarIndex(Car* car){
    for (int i = 0; i < myCars.size() ; i++) {
            if(myCars[i].get()->getLicensePlate()==car->getLicensePlate())
            {
                return i;
            }
    }
    return -1;
}
long long CarManagmentService::getCarsCount()
{
    return this->myCars.size();
}

bool CarManagmentService::clearAll()
{
    this->myCars.clear();
}

CarManagmentService::CarManagmentService()
{

}
