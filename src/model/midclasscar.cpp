#include "midclasscar.h"


#include "CarTypeName.h"
MidClassCar::MidClassCar(const string &name, const string &brand, const string &licensePlate) : Car(name, brand, licensePlate,CarType(CarTypeNameToString(CarTypeName::MID_CLASS),4,2,25))
{}


