#include "model/ecocar.h"
#include "model/deluxecar.h"
#include "repository/carsrepository.h"
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include "repository/repositoryutils.h"
using namespace testing;
TEST(RentItNowTest_CAR_REPOSITORY, ConvertCarToJSON)
{
    EcoCar car("testCar", "testBrand", "1234");

    auto obj = CarsRepository::getInstance().convertObjectToJson(car);
    std::string expectedJson = "{\"brand\":\"testBrand\",\"km_to_service\":1500,\"location\":\"Inner\",\"lp\":\"1234\",\"name\":\"testCar\",\"owner\":\"null\",\"total_km\":0,\"type\":\"ECO\"}";

    EXPECT_EQ(expectedJson, RepositoryUtils::convertJsonToString(obj));
}

TEST(RentItNowTest_CAR_REPOSITORY, FromJSONToCar)
{
    EcoCar car("testCar", "testBrand", "1234");

    auto obj = CarsRepository::getInstance().convertObjectToJson(car);
    std::string expectedJson = "{\"brand\":\"testBrand\",\"km_to_service\":1500,\"location\":\"Inner\",\"lp\":\"1234\",\"name\":\"testCar\",\"owner\":\"null\",\"total_km\":0,\"type\":\"ECO\"}";

    // Convert JSON to Car
    auto convertedCar = CarsRepository::getInstance().convertJsonToObject(expectedJson);

    // Check if the two cars are equal
    EXPECT_TRUE(car==*convertedCar);

    // Check if the strings are equal
    EXPECT_EQ(expectedJson,  RepositoryUtils::convertJsonToString(CarsRepository::getInstance().convertObjectToJson(*convertedCar)));
}
TEST(RentItNowTest_CAR_REPOSITORY, SaveFile)
{
    std::string expectedJson = "{\"brand\":\"testBrand\",\"km_to_service\":1500,\"lp\":\"1234\",\"name\":\"testCar\",\"total_km\":0,\"type\":\"ECO\"}";
    EXPECT_TRUE(RepositoryUtils::writeOnFile(expectedJson,"./test.json"));
}
TEST(RentItNowTest_CAR_REPOSITORY, ReadFile)
{
    std::string expectedJson = "{\"brand\":\"testBrand\",\"km_to_service\":1500,\"lp\":\"1234\",\"name\":\"testCar\",\"total_km\":0,\"type\":\"ECO\"}";
    RepositoryUtils::writeOnFile(expectedJson,"./test.json");
    EXPECT_EQ(expectedJson,RepositoryUtils::readFromFile("./test.json"));
}
TEST(RentItNowTest_CAR_REPOSITORY, SaveCar)
{
    EcoCar car("testCar", "testBrand", "1234");
    std::map<string, std::shared_ptr<Car> > data;
    data["1234"]=std::make_shared<Car>(car);
    EXPECT_TRUE(CarsRepository::getInstance().save(data));

}
TEST(RentItNowTest_CAR_REPOSITORY, ReadCar)
{
    EcoCar car("testCar", "testBrand", "1234");
    DeluxeCar car2("testCar2", "testBrand", "1235");
    std::map<string, std::shared_ptr<Car> > data;
    data["1234"]=std::make_shared<Car>(car);
    data["1235"]=std::make_shared<Car>(car2);
    EXPECT_TRUE(CarsRepository::getInstance().save(data));
    auto mydb=CarsRepository::getInstance().load();
    EXPECT_EQ(data["1234"]->getLicensePlate(),mydb["1234"]->getLicensePlate());
    EXPECT_EQ(data["1235"]->getLicensePlate(),mydb["1235"]->getLicensePlate());
    EXPECT_EQ(car.getTypeName(),mydb["1234"]->getTypeName());
    EXPECT_EQ(car2.getTypeName(),mydb["1235"]->getTypeName());
}
