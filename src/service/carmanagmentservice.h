#ifndef CARMANAGMENTSERVICE_H
#define CARMANAGMENTSERVICE_H

#include "ICrud.h"
#include "../model/car.h"
#include <vector>
#include <memory>

class CarManagmentService: ICrud<Car*>
{
private:
  CarManagmentService();
    vector<std::unique_ptr<Car>> myCars;
    bool verifyLicensePlate(const string lp);
    int findCarIndex(Car* car);

public:
    static CarManagmentService& getInstance();

    bool add(Car* newObject) override;
    bool update(Car* oldObject, Car* updatedObject) override;
    bool remove(Car* objectToDelete) override;
    long long getCarsCount();
    bool clearAll();


};

#endif // CARMANAGMENTSERVICE_H
