#include "simpletown.h"

SimpleTown::SimpleTown()
{
    this->outer=std::make_shared<Circle>(CircleType::OUTER);
    std::shared_ptr<Circle> middle=std::make_shared<Circle>(CircleType::MIDDLE);
    std::shared_ptr<Circle> inner=std::make_shared<Circle>(CircleType::INNER);

    outer->setChild(middle)->setChild(inner);
    inner->setParent(middle)->setParent(outer);
    this->inner=inner;
}

std::shared_ptr<Circle> SimpleTown::getOuter() const
{
    return outer;
}

std::shared_ptr<Circle> SimpleTown::getInner() const
{
    return inner;
}

SimpleTown &SimpleTown::getInstance()
{
    static SimpleTown instance;
    return instance;
}
