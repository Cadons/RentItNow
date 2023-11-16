#include "ecocar.h"

#include "CarTypeName.h"


EcoCar::EcoCar(const string &name, const string &brand, const string &licensePlate) : Car(name, brand, licensePlate, CarType(CarTypeNameToString(CarTypeName::ECO),2,1,15))
    {}

