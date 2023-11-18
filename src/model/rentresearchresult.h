#ifndef RENTRESEARCHRESULT_H
#define RENTRESEARCHRESULT_H


#include "car.h"
#include <memory>
#include <vector>
struct ResultItem{
    const std::shared_ptr<Car> car;
    const float price;
    const int hopsDistance;
    const float kmDistance;
};

class RentResearchResult
{
public:
    RentResearchResult();
    RentResearchResult(const vector<ResultItem> &cars, float waitTime);
    float getWaitTime() const;

    vector<ResultItem> getCars() const;

private:


    const vector<ResultItem> cars;
    const float waitTime=-1;

};

#endif // RENTRESEARCHRESULT_H
