#include "cartype.h"

CarType::CarType(std::string type_name,int capacity, float price, float speed) : CAPACITY(capacity),
    PRICE(price),
    SPEED(speed),
    TYPE_NAME(type_name)
{}
