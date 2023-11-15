
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "model/ecocar.h"
#include "service/carmanagmentservice.h"
using namespace testing;

TEST(RentItNowTest_CAR_MANAGER, ADD)
{
    EcoCar* myCar=new EcoCar("testCar", "testBrand","ABC1234");

    ASSERT_FALSE(CarManagmentService::getInstance().add(nullptr));
    ASSERT_TRUE(CarManagmentService::getInstance().add(myCar));
    ASSERT_EQ(1,CarManagmentService::getInstance().getCarsCount());
    ASSERT_FALSE(CarManagmentService::getInstance().add(myCar));
    myCar=new EcoCar("testCar", "testBrand","ABC12332");
    ASSERT_TRUE(CarManagmentService::getInstance().add(myCar));
    ASSERT_EQ(2,CarManagmentService::getInstance().getCarsCount());
    delete myCar;
    CarManagmentService::getInstance().clearAll();

}
TEST(RentItNowTest_CAR_MANAGER, UPDATE)
{
   /* EcoCar* myCar=new EcoCar("testCar", "testBrand","ABC1234");

    ASSERT_FALSE(CarManagmentService::getInstance().add(nullptr));
    ASSERT_TRUE(CarManagmentService::getInstance().add(myCar));
    ASSERT_EQ(1,CarManagmentService::getInstance().getCarsCount());
    ASSERT_FALSE(CarManagmentService::getInstance().add(myCar));
    myCar=new EcoCar("testCar", "testBrand","ABC12332");
    ASSERT_TRUE(CarManagmentService::getInstance().add(myCar));
    ASSERT_EQ(2,CarManagmentService::getInstance().getCarsCount());
    delete myCar;*/

}
TEST(RentItNowTest_CAR_MANAGER, DELETE)
{
    EcoCar* myCar=new EcoCar("testCar", "testBrand","ABC1234");

    EXPECT_TRUE(CarManagmentService::getInstance().add(myCar));
    ASSERT_EQ(1,CarManagmentService::getInstance().getCarsCount());
    EXPECT_TRUE(CarManagmentService::getInstance().remove(myCar));
ASSERT_EQ(0,CarManagmentService::getInstance().getCarsCount());
    delete myCar;
    CarManagmentService::getInstance().clearAll();
}
