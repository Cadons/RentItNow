#ifndef IRENTINGSERVICE_H
#define IRENTINGSERVICE_H
#include <string>
#include "../model/location.h"
#include "../model/CarTypeName.h"
#include "../model/rentresearchresult.h"
class IRentingService
{
private:
public:


    virtual Location getLocation(std::string lp)=0;
    virtual std::unique_ptr<RentResearchResult>  requestRent( int passegers, CarTypeName type, Location start, Location destination)=0;;

    virtual bool rent(std::string lp, std::string dl, float price=0)=0;
    virtual bool release(std::string lp, std::string dl)=0;



};
#endif // IRENTINGSERVICE_H
