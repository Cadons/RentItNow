#ifndef RENTINGSERVICE_H
#define RENTINGSERVICE_H

#include "../model/simpletown.h"
#include "IRentingService.h"
class RentingService: public IRentingService
{
private:
    RentingService();
    SimpleTown& city;
    int calculatePath(const Circle* position,const Circle* from, const Circle* destination, const bool taken);
    // IRentingService interface
public:
    Location getLocation(string lp) override;
    std::unique_ptr<RentResearchResult> requestRent(int passegers, CarTypeName type, Location start, Location destination) override;
    bool rent(string lp, string dl) override;
    bool release(string lp, string dl) override;
    static RentingService& getInstance();


    SimpleTown &getCity() const;
};

#endif // RENTINGSERVICE_H
