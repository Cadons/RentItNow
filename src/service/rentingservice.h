#ifndef RENTINGSERVICE_H
#define RENTINGSERVICE_H


#include "IRentingService.h"
class RentingService: public IRentingService
{
private:
    RentingService();
    std::shared_ptr<Circle> outer;//city perferic
    std::shared_ptr<Circle> inner;//city center
    // IRentingService interface
public:
    Location getLocation(string lp) override;
    RentResearchResult &requestRent(string dl, int passegers, CarType type, Location start, Location destination) override;
    bool rent(string lp, string dl) override;
    bool release(string lp, string dl) override;
    static RentingService& getInstance();
    std::shared_ptr<Circle> getOuterCity() const;
    std::shared_ptr<Circle> getInnerCity() const;

};

#endif // RENTINGSERVICE_H
