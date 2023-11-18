#ifndef LOCATION_H
#define LOCATION_H


#include "circle.h"
#include <memory>
class Location
{
public:
    Location();
    Location(const std::shared_ptr<Circle> &newPosition);
    std::shared_ptr<Circle> getPosition() const;
    void setPosition(const std::shared_ptr<Circle> &newPosition);

private:
    std::shared_ptr<Circle> position;

};

#endif // LOCATION_H
