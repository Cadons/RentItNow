#include "location.h"

Location::Location()
{

}

std::shared_ptr<Circle> Location::getPosition() const
{
    return position;
}

void Location::setPosition(const std::shared_ptr<Circle> &newPosition)
{
    position = newPosition;
}
