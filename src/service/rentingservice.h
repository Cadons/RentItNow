#ifndef RENTINGSERVICE_H
#define RENTINGSERVICE_H

#include "../model/simpletown.h"
#include "IRentingService.h"
class RentingService: public IRentingService
{
private:
    RentingService();
    SimpleTown& city;
    // IRentingService interface
public:
    Location getLocation(string lp) override;
    RentResearchResult &requestRent(string dl, int passegers, CarType type, Location start, Location destination) override;
    bool rent(string lp, string dl) override;
    bool release(string lp, string dl) override;
    static RentingService& getInstance();


    SimpleTown &getCity() const;
};

#endif // RENTINGSERVICE_H
