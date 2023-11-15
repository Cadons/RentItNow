
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "model/ecocar.h"
#include "model/midclasscar.h"
#include "model/deluxecar.h"
using namespace testing;

TEST(RentItNowTest_CAR, BASIC_CAR)
{
    EcoCar myCar("testCar", "testBrand","ABC1234");
    EXPECT_EQ("testCar", myCar.getName());
    EXPECT_EQ("testBrand",myCar.getBrand());
    EXPECT_EQ("ABC1234",myCar.getLicensePlate());

    EXPECT_FALSE(myCar.needService());
    EXPECT_FALSE(myCar.updateDistanceTraveled(5000));
    EXPECT_FALSE(myCar.updateDistanceTraveled(-5000));
    EXPECT_TRUE(myCar.updateDistanceTraveled(1500));
    EXPECT_TRUE(myCar.needService());
    EXPECT_FALSE(myCar.resetKm().needService());

}

TEST(RentItNowTest_CAR, ECO_CAR)
{
    EcoCar myCar("testCar", "testBrand","ABC1234");
    EXPECT_EQ(2,myCar.getCapacity());
    EXPECT_EQ(1,myCar.getPrice());
    EXPECT_EQ(15,myCar.getSpeed());

}

TEST(RentItNowTest_CAR, MID_CLASS_CAR)
{
    MidClassCar myCar("testCar", "testBrand","ABC1234");
    EXPECT_EQ(4,myCar.getCapacity());
    EXPECT_EQ(2,myCar.getPrice());
    EXPECT_EQ(25,myCar.getSpeed());

}
TEST(RentItNowTest_CAR,DELUXE_CAR)
{
    DeluxeCar myCar("testCar", "testBrand","ABC1234");
    EXPECT_EQ(7,myCar.getCapacity());
    EXPECT_EQ(5,myCar.getPrice());
    EXPECT_EQ(50,myCar.getSpeed());

}
