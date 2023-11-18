#ifndef SIMPLETOWN_H
#define SIMPLETOWN_H


#include "circle.h"
#include <memory>
class SimpleTown
{
public:
    SimpleTown();
    static SimpleTown& getInstance();

    std::shared_ptr<Circle> getOuter() const;
    std::shared_ptr<Circle> getInner() const;

private:
    std::shared_ptr<Circle> outer;//city perferic
    std::shared_ptr<Circle> inner;//city center
};

#endif // SIMPLETOWN_H
