#ifndef CARTYPE_H
#define CARTYPE_H


class CarType
{
    friend class Car;
private:
    const int CAPACITY;
    const float PRICE;
    const float SPEED;
public:

    CarType(int capacity, float price, float speed);

};

#endif // CARTYPE_H
