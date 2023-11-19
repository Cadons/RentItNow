
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "model/deluxecar.h"
#include "model/ecocar.h"
#include "model/midclasscar.h"
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
TEST_F(RentItNowTest_RENT_SERVICE, RENT)
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
TEST_F(RentItNowTest_RENT_SERVICE, REQUEST_RENT)
{
    Car* car=new EcoCar("testCar","testBrand","1234e");
    car->setLocation(SimpleTown::getInstance().getOuter()->getChild());
    CarManagementService::getInstance().add(car);
    CarManagementService::getInstance().add(new MidClassCar("testCar2","testBrand2","1234m"));
    CarManagementService::getInstance().add(new MidClassCar("testCar4","testBrand4","1234m2"));
    CarManagementService::getInstance().add(new EcoCar("testCar5","testBrand5","1234e2"));

    Location from;
    from.setPosition(nullptr);
    Location to;

    EXPECT_EQ(nullptr,RentingService::getInstance().requestRent(0,CarTypeName::ECO,from,to).get());
    to.setPosition(nullptr);
    EXPECT_EQ(nullptr,RentingService::getInstance().requestRent(0,CarTypeName::ECO,from,to).get());
    EXPECT_EQ(nullptr,RentingService::getInstance().requestRent(100,CarTypeName::ECO,from,to).get());

    to.setPosition(SimpleTown::getInstance().getOuter());
    from.setPosition(SimpleTown::getInstance().getInner());
    EXPECT_EQ(nullptr,RentingService::getInstance().requestRent(100,CarTypeName::ECO,from,to).get());

    EXPECT_EQ(std::numeric_limits<float>::max(),RentingService::getInstance().requestRent(1,CarTypeName::DELUXE,from,to).get()->getWaitTime());
    CarManagementService::getInstance().add(new DeluxeCar("testCar3","testBrand3","1234d"));

    EXPECT_EQ(std::numeric_limits<float>::min(),RentingService::getInstance().requestRent(1,CarTypeName::ECO,from,to).get()->getWaitTime());
    EXPECT_EQ(3,RentingService::getInstance().requestRent(1,CarTypeName::ECO,from,to).get()->getCars()[0].getHopsDistance());
    from.setPosition(SimpleTown::getInstance().getInner());
    to.setPosition(SimpleTown::getInstance().getInner()->getParent());
    EXPECT_EQ(2,RentingService::getInstance().requestRent(1,CarTypeName::ECO,from,to).get()->getCars()[0].getHopsDistance());
    from.setPosition(SimpleTown::getInstance().getInner());
    to.setPosition(SimpleTown::getInstance().getInner());
    EXPECT_EQ(1,RentingService::getInstance().requestRent(1,CarTypeName::ECO,from,to).get()->getCars()[0].getHopsDistance());
    EXPECT_EQ(5,RentingService::getInstance().requestRent(1,CarTypeName::ECO,from,to).get()->getCars()[0].getKmDistance());
    EXPECT_EQ(5,RentingService::getInstance().requestRent(1,CarTypeName::ECO,from,to).get()->getCars()[0].getPrice());
    EXPECT_EQ(25,RentingService::getInstance().requestRent(1,CarTypeName::DELUXE,from,to).get()->getCars()[0].getPrice());
    EXPECT_EQ(10,RentingService::getInstance().requestRent(1,CarTypeName::MID_CLASS,from,to).get()->getCars()[0].getPrice());
    from.setPosition(SimpleTown::getInstance().getInner()->getParent());
    to.setPosition(SimpleTown::getInstance().getOuter());
    EXPECT_EQ(2,RentingService::getInstance().requestRent(2,CarTypeName::ECO,from,to).get()->getCars().size());

    EXPECT_EQ( CarManagementService::getInstance().getCar("1234e"),RentingService::getInstance().requestRent(2,CarTypeName::ECO,from,to).get()->getCars()[0].getCar());

    EXPECT_EQ( CarManagementService::getInstance().getCar("1234e2"),RentingService::getInstance().requestRent(2,CarTypeName::ECO,from,to).get()->getCars()[1].getCar());

    EXPECT_NE(CarManagementService::getInstance().getCar("1234e2"),RentingService::getInstance().requestRent(2,CarTypeName::ECO,from,to).get()->getCars()[0].getCar());

}
