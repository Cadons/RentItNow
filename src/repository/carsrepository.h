#ifndef CARSREPOSITORY_H
#define CARSREPOSITORY_H


#include <string>
#include <memory>
#include <map>
#include "../model/car.h"
#include "IRepository.h"

class CarsRepository: public IRepository<std::string,Car>
{
private:
    CarsRepository();



    // IRepository interface
public:
    std::map<std::string, std::shared_ptr<Car>> load() override;
    bool save(std::map<std::string, std::shared_ptr<Car>> data) override;
    QJsonObject convertObjectToJson(Car obj) override;
    Car* convertJsonToObject(string &obj) override;
    static CarsRepository& getInstance();
};

#endif // CARSREPOSITORY_H
