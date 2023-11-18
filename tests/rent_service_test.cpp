
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "model/ecocar.h"
#include "rent_service_test.h"
#include "service/rentingservice.h"
#include <QDebug>
using namespace testing;

TEST_F(RentItNowTest_RENT_SERVICE, CITY)
{
    RentingService::getInstance();
    auto city=RentingService::getInstance().getCity().getOuter();
    //test from out to in
    EXPECT_EQ(city->toString(),"Outer");
    EXPECT_EQ(city->getChild()->toString(),"Middle");
    EXPECT_EQ(city->getChild()->getChild()->toString(),"Inner");

    //test from inner to out
    auto inner=RentingService::getInstance().getCity().getInner();
    EXPECT_EQ(inner->toString(),"Inner");
    EXPECT_EQ(inner->getParent()->toString(),"Middle");
    EXPECT_EQ(inner->getParent()->getParent()->toString(),"Outer");
}
TEST_F(RentItNowTest_RENT_SERVICE, GET_LOCATION)
{
    Car* car=new EcoCar("testCar","testBrand","1234");
    CarManagementService::getInstance().add(car);
    EXPECT_EQ(RentingService::getInstance().getLocation("1234").getPosition()->toString(),"Inner");
    Location tmp(SimpleTown::getInstance().getOuter());
    CarManagementService::getInstance().moveCar(car->getLicensePlate(),tmp);
    EXPECT_EQ(RentingService::getInstance().getLocation("1234").getPosition()->toString(),"Outer");


}
TEST_F(RentItNowTest_RENT_SERVICE, REQUEST_RENT)
{
    Car* car=new EcoCar("testCar","testBrand","1234");
    CarManagementService::getInstance().add(car);
    User* testUser=new User("John", "Doe", "123 Main St", "1234-5678-9012-3456", "ABCD123456");
    UserManagementService::getInstance().add(testUser);

    EXPECT_FALSE(RentingService::getInstance().rent("",""));

    EXPECT_FALSE(RentingService::getInstance().rent("1234",""));
    EXPECT_FALSE(RentingService::getInstance().rent("","ABCD123456"));
    EXPECT_TRUE(RentingService::getInstance().rent("1234","ABCD123456"));
    EXPECT_EQ("ABCD123456",CarManagementService::getInstance().getCar("1234")->getOwner()->getDrivingLicense());


}
TEST_F(RentItNowTest_RENT_SERVICE, RELEASE_RENT)
{
    Car* car=new EcoCar("testCar","testBrand","1234");
    CarManagementService::getInstance().add(car);
    User* testUser=new User("John", "Doe", "123 Main St", "1234-5678-9012-3456", "ABCD123456");
    UserManagementService::getInstance().add(testUser);


    EXPECT_TRUE(RentingService::getInstance().rent("1234","ABCD123456"));

    EXPECT_FALSE(RentingService::getInstance().release("",""));

    EXPECT_FALSE(RentingService::getInstance().release("1234",""));
    EXPECT_FALSE(RentingService::getInstance().release("","ABCD123456"));
    EXPECT_TRUE(RentingService::getInstance().release("1234","ABCD123456"));
    EXPECT_EQ(nullptr,CarManagementService::getInstance().getCar("1234")->getOwner());

}
