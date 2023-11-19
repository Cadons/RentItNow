#ifndef CIRCLE_H
#define CIRCLE_H


#include <memory>
#include <string>
enum CircleType{
   UNKNOWN=-1,
    INNER=0,
    MIDDLE=1,
    OUTER=2
};

class Circle
{
public:
    Circle(CircleType name);
    Circle(Circle* circle);
    CircleType getName() const;
    std::string toString() const;

    std::shared_ptr<Circle> setChild(const std::shared_ptr<Circle> &newChild);

    std::shared_ptr<Circle> getChild() const;

    std::shared_ptr<Circle> getParent() const;
    std::shared_ptr<Circle> setParent(const std::shared_ptr<Circle> &newParent);

private:
    CircleType name=CircleType::UNKNOWN;
    std::shared_ptr<Circle> child;
    std::shared_ptr<Circle> parent;


};

#endif // CIRCLE_H
