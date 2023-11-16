#ifndef CARTYPE_H
#define CARTYPE_H
#include <string>

class CarType
{
    friend class Car;
private:
    const int CAPACITY;
    const float PRICE;
    const float SPEED;
    const std::string TYPE_NAME;
public:

    CarType(std::string type_name,int capacity, float price, float speed);

};

#endif // CARTYPE_H
