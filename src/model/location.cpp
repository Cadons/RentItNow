#include "location.h"
#include "../service/rentingservice.h"
Location::Location()
{
    position=SimpleTown::getInstance().getInner();//Default location
}

Location::Location(const std::shared_ptr<Circle> &newPosition)
{
    setPosition(newPosition);
}

std::shared_ptr<Circle> Location::getPosition() const
{
    return position;
}

void Location::setPosition(const std::shared_ptr<Circle> &newPosition)
{
    position = newPosition;
}
