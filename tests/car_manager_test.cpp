#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "car_manager_test.h"
#include "model/ecocar.h"
#include "service/carmanagmentservice.h"
using namespace testing;

TEST_F(RentItNowTest_CAR_MANAGER, ADD)
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

}
TEST_F(RentItNowTest_CAR_MANAGER, UPDATE)
{
    EcoCar* myCar=new EcoCar("testCar", "testBrand","ABC1234");
    EcoCar* myCar2=new EcoCar("testCar3", "testBrand3","ABC1234");
    EcoCar* myCar3=new EcoCar("testCar3", "testBrand3","ABC12346");
    CarManagmentService::getInstance().add(myCar);
    EXPECT_FALSE(CarManagmentService::getInstance().update("ABC1234",nullptr));
    EXPECT_FALSE(CarManagmentService::getInstance().update("",nullptr));
    EXPECT_FALSE(CarManagmentService::getInstance().update("",myCar));

    EXPECT_TRUE(CarManagmentService::getInstance().update("ABC1234",myCar2));
    EXPECT_FALSE(CarManagmentService::getInstance().update("ABC1234",myCar3));

    delete myCar;
    delete myCar2;
    delete myCar3;


}
TEST_F(RentItNowTest_CAR_MANAGER, DELETE)
{
    EcoCar* myCar=new EcoCar("testCar", "testBrand","ABC1234");
    EcoCar* myCar2=new EcoCar("testCar2", "testBrand2","ABC1233");

    EXPECT_TRUE(CarManagmentService::getInstance().add(myCar));
    EXPECT_TRUE(CarManagmentService::getInstance().add(myCar2));

    ASSERT_EQ(2,CarManagmentService::getInstance().getCarsCount());
    EXPECT_TRUE(CarManagmentService::getInstance().remove(myCar));
    ASSERT_EQ(1,CarManagmentService::getInstance().getCarsCount());
    EXPECT_TRUE(CarManagmentService::getInstance().remove("ABC1233"));
    EXPECT_FALSE(CarManagmentService::getInstance().remove("1234"));

    ASSERT_EQ(0,CarManagmentService::getInstance().getCarsCount());

    delete myCar;
    delete myCar2;
}
TEST_F(RentItNowTest_CAR_MANAGER, GET_MY_CARS)
{
    EcoCar* myCar=new EcoCar("testCar", "testBrand","ABC1234");
    EcoCar* myCar2=new EcoCar("testCar2", "testBrand2","ABC1233");
    std::map<string, std::shared_ptr<Car>>test;
    test["ABC1234"]=std::make_shared<Car>(*myCar);
    test["ABC1233"]=std::make_shared<Car>(*myCar2);


    EXPECT_TRUE(CarManagmentService::getInstance().add(myCar));
    EXPECT_TRUE(CarManagmentService::getInstance().add(myCar2));

    EXPECT_EQ(2,CarManagmentService::getInstance().getCarsCount());
    auto testcar=CarManagmentService::getInstance().getCars()["ABC1234"].get();

    EXPECT_EQ(test["ABC1234"].get()->toString(),testcar->toString());
    testcar=CarManagmentService::getInstance().getCars()["ABC1233"].get();
    EXPECT_EQ(test["ABC1233"].get()->toString(),testcar->toString());
    delete myCar;
    delete myCar2;

}
TEST_F(RentItNowTest_CAR_MANAGER, NEXT_SERVICE_TIME)
{
    EcoCar* myCar=new EcoCar("testCar", "testBrand","ABC1234");
    myCar->updateDistanceTraveled(1500);
    EXPECT_EQ(-1, CarManagmentService::getInstance().getNextServiceTime("ABC1234"));

    CarManagmentService::getInstance().add(myCar);
    EXPECT_EQ(0, CarManagmentService::getInstance().getNextServiceTime("ABC1234"));
    myCar->resetKm();
    EXPECT_TRUE(CarManagmentService::getInstance().update("ABC1234",myCar));
    EXPECT_EQ(100, CarManagmentService::getInstance().getNextServiceTime("ABC1234"));
    myCar->updateDistanceTraveled(500);
    EXPECT_TRUE(CarManagmentService::getInstance().update("ABC1234",myCar));
    EXPECT_EQ(66, CarManagmentService::getInstance().getNextServiceTime("ABC1234"));

}
TEST_F(RentItNowTest_CAR_MANAGER, GET_TRAVELLED_DISTANCE)
{
    EcoCar* myCar=new EcoCar("testCar", "testBrand","ABC1234");
    myCar->updateDistanceTraveled(1500);
    myCar->resetKm();
    myCar->updateDistanceTraveled(1000);
    CarManagmentService::getInstance().add(myCar);
    EXPECT_EQ(2500, CarManagmentService::getInstance().getTraveledDistance("ABC1234"));
    EXPECT_EQ(0, CarManagmentService::getInstance().getTraveledDistance("1234"));

}
TEST_F(RentItNowTest_CAR_MANAGER, CAR_IN_MAINTENANCE)
{
    EcoCar* myCar=new EcoCar("testCar", "testBrand","ABC1234");
    myCar->updateDistanceTraveled(1500);
    CarManagmentService::getInstance().add(myCar);
    EXPECT_TRUE(CarManagmentService::getInstance().checkAviability("ABC1234"));

    CarManagmentService::getInstance().putCarInMaintenance(myCar->getLicensePlate());

    EXPECT_FALSE(CarManagmentService::getInstance().checkAviability("ABC1234"));
    for (int i = 0; i < 25; i++) {
        CarManagmentService::getInstance().updateMaintenanceStatus();

    }
    EXPECT_TRUE(CarManagmentService::getInstance().checkAviability("ABC1234"));

    EXPECT_FALSE(CarManagmentService::getInstance().checkAviability("ABC1236"));

}
