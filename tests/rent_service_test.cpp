
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "rent_service_test.h"
#include "service/rentingservice.h"
#include <QDebug>
using namespace testing;

TEST_F(RentItNowTest_RENT_SERVICE, createService)
{
    RentingService::getInstance();
    auto circles=RentingService::getInstance().getOuterCity();
    //test from out to in
    EXPECT_EQ(circles->toString(),"Outer");
    EXPECT_EQ(circles->getChild()->toString(),"Middle");
    EXPECT_EQ(circles->getChild()->getChild()->toString(),"Inner");

    //test from inner to out
    auto inner=RentingService::getInstance().getInnerCity();
    EXPECT_EQ(inner->toString(),"Inner");
    EXPECT_EQ(inner->getParent()->toString(),"Middle");
    EXPECT_EQ(inner->getParent()->getParent()->toString(),"Outer");
}

