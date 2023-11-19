#ifndef RENTRESEARCHRESULT_H
#define RENTRESEARCHRESULT_H


#include "car.h"
#include <memory>
#include <vector>
class ResultItem {
private:
    Car* car;
    float price;
    int hopsDistance;
    float kmDistance;

public:
    // Constructor
    ResultItem(Car* car, float price, int hopsDistance)
        : car(car), price(price), hopsDistance(hopsDistance), kmDistance(hopsDistance * 5) {}

    // Accessors (const methods to access member variables)
    Car* getCar() const {
        return car;
    }

    float getPrice() const {
        return price;
    }

    int getHopsDistance() const {
        return hopsDistance;
    }

    float getKmDistance() const {
        return kmDistance;
    }

    // Overload the less-than operator for sorting
    bool operator<(const ResultItem& other) const {
        if (price == other.price) {
            // If prices are equal, compare based on kmDistance
            return kmDistance < other.kmDistance;
        }
        return price < other.price;
    }
};
class RentResearchResult
{
public:
    RentResearchResult();
    RentResearchResult(const vector<ResultItem> &cars, float waitTime);
    float getWaitTime() const;

    vector<ResultItem> getCars() const;

private:


    vector<ResultItem> cars;
    const float waitTime=-1;

};

#endif // RENTRESEARCHRESULT_H
