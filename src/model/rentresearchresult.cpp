#include "rentresearchresult.h"
#include <algorithm>

RentResearchResult::RentResearchResult()
{

}

float RentResearchResult::getWaitTime() const
{
    return waitTime;
}

vector<ResultItem> RentResearchResult::getResults() const
{
    return results;
}

RentResearchResult::RentResearchResult(const vector<ResultItem> &cars, float waitTime) : results(cars),
    waitTime(waitTime)
{
    std::sort(this->results.begin(),this->results.end());
}
