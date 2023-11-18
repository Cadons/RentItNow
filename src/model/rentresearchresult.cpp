#include "rentresearchresult.h"

RentResearchResult::RentResearchResult()
{

}

float RentResearchResult::getWaitTime() const
{
    return waitTime;
}

vector<ResultItem> RentResearchResult::getCars() const
{
    return cars;
}

RentResearchResult::RentResearchResult(const vector<ResultItem> &cars, float waitTime) : cars(cars),
    waitTime(waitTime)
{}
