#ifndef RENTINGSERVICE_H
#define RENTINGSERVICE_H

#include "../model/simpletown.h"
#include "IRentingService.h"
#include "../model/bank.h"
#include <list>
class RentingService: public IRentingService
{
private:
    RentingService();
    SimpleTown& city;
    int calculatePath(std::shared_ptr<Circle>position, const std::shared_ptr<Circle> from, const std::shared_ptr<Circle> destination, const bool taken);
    std::unique_ptr<Bank> myBank;
    std::list<Location> tmpPath;

public:
    Location getLocation(string lp) override;
    std::unique_ptr<RentResearchResult> requestRent(int passegers, CarTypeName type, Location start, Location destination) override;
    bool rent(string lp, string dl, float price=0) override;
    bool release(string lp, string dl) override;
    static RentingService& getInstance();


    SimpleTown &getCity() const;
    Bank*getMyBank() const;
};

#endif // RENTINGSERVICE_H
