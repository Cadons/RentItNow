
#include "model/ecocar.h"
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
    std::string expectedJson = "{\"brand\":\"testBrand\",\"km_to_service\":1500,\"lp\":\"1234\",\"name\":\"testCar\",\"total_km\":0,\"type\":\"ECO\"}";

    EXPECT_EQ(expectedJson, RepositoryUtils::convertJsonToString(obj));
}

TEST(RentItNowTest_CAR_REPOSITORY, FromJSONToCar)
{
    EcoCar car("testCar", "testBrand", "1234");

    auto obj = CarsRepository::getInstance().convertObjectToJson(car);
    std::string expectedJson = "{\"brand\":\"testBrand\",\"km_to_service\":1500,\"lp\":\"1234\",\"name\":\"testCar\",\"total_km\":0,\"type\":\"ECO\"}";

    // Convert JSON to Car
    auto convertedCar = CarsRepository::getInstance().convertJsonToObject(expectedJson);

    // Check if the two cars are equal
    EXPECT_TRUE(car==*convertedCar);

    // Check if the strings are equal
    EXPECT_EQ(expectedJson,  RepositoryUtils::convertJsonToString(CarsRepository::getInstance().convertObjectToJson(*convertedCar)));
}
