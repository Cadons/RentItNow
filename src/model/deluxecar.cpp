#include "deluxecar.h"

#include "CarTypeName.h"
DeluxeCar::DeluxeCar(const string &name, const string &brand, const string &licensePlate) : Car(name, brand, licensePlate, CarType(CarTypeNameToString(CarTypeName::DELUXE),7,5,50))
{}

