#include "circle.h"

Circle::Circle(CircleType name):
    name(name)
{
    parent=nullptr;
    child=nullptr;
}

Circle::Circle(Circle *circle): name(circle->name)
{

}

CircleType Circle::getName() const
{
    return name;
}

std::string Circle::toString()
{
    switch (name) {
    case CircleType::INNER:
        return "Inner";
    case CircleType::MIDDLE:
        return "Middle";
    case CircleType::OUTER:
        return "Outer";
    default:
        return "Unknown";
    }
}

std::shared_ptr<Circle> Circle::setChild(const std::shared_ptr<Circle> &newChild)
{
    child = newChild;
    return newChild;
}

std::shared_ptr<Circle> Circle::getChild() const
{
    return child;
}

std::shared_ptr<Circle> Circle::getParent() const
{
    return parent;
}

std::shared_ptr<Circle> Circle::setParent(const std::shared_ptr<Circle> &newParent)
{
    parent = newParent;
    return newParent;
}
