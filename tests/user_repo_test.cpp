
#include "model/user.h"
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "repository/repositoryutils.h"
#include "repository/usersrepository.h"

using namespace testing;

TEST(RentItNowTest_USER_REPOSITORY, ConvertUserToJSON)
{
    User testUser("123456","John", "Doe", "123 Main St", "1234-5678-9012-3456", "ABCD123456");
    auto obj = UsersRepository::getInstance().convertObjectToJson(testUser);

    std::string expectedJson=R"({"address":"123 Main St","creditCard":"1234-5678-9012-3456","drivingLicense":"ABCD123456","id":"123456","name":"John","surname":"Doe"})";
    EXPECT_EQ(expectedJson, RepositoryUtils::convertJsonToString(obj));

}
TEST(RentItNowTest_USER_REPOSITORY, FromJSONToUser)
{
    User testUser("123456","John", "Doe", "123 Main St", "1234-5678-9012-3456", "ABCD123456");
    auto obj = UsersRepository::getInstance().convertObjectToJson(testUser);
    std::string expectedJson=R"({"address":"123 Main St","creditCard":"1234-5678-9012-3456","drivingLicense":"ABCD123456","id":"123456","name":"John","surname":"Doe"})";

    auto convertedUser = UsersRepository::getInstance().convertJsonToObject(expectedJson);
    EXPECT_TRUE(testUser==*convertedUser);

    // Check if the strings are equal
    EXPECT_EQ(expectedJson,  RepositoryUtils::convertJsonToString(UsersRepository::getInstance().convertObjectToJson(*convertedUser)));

}

TEST(RentItNowTest_CAR_REPOSITORY, SaveUser)
{
    User testUser("123456","John", "Doe", "123 Main St", "1234-5678-9012-3456", "ABCD123456");
    std::map<std::string, std::shared_ptr<User> > data;
    data["123456"]=std::make_shared<User>(testUser);
    EXPECT_TRUE(UsersRepository::getInstance().save(data));

}
TEST(UsersRepositoryTest, SaveAndLoadUser) {
    // Create a test user
    User user("123456", "John", "Doe", "123 Main St", "1234-5678-9012-3456", "ABCD123456");

    // Save the user to the repository
    std::map<std::string, std::shared_ptr<User>> data;
    data[user.getId()] = std::make_shared<User>(user);
    EXPECT_TRUE(UsersRepository::getInstance().save(data));

    // Load the user from the repository
    auto loadedData = UsersRepository::getInstance().load();

    // Check if the loaded data matches the original user
    ASSERT_EQ(1, loadedData.size()) << "Unexpected number of users loaded";
    auto loadedUser = loadedData[user.getId()];

    EXPECT_EQ(user.getId(), loadedUser->getId()) << "IDs don't match";
    EXPECT_EQ(user.getName(), loadedUser->getName()) << "Names don't match";
    EXPECT_EQ(user.getSurname(), loadedUser->getSurname()) << "Surnames don't match";
    EXPECT_EQ(user.getAddress(), loadedUser->getAddress()) << "Addresses don't match";
    EXPECT_EQ(user.getCreditCard(), loadedUser->getCreditCard()) << "Credit cards don't match";
    EXPECT_EQ(user.getDrivingLicense(), loadedUser->getDrivingLicense()) << "Driving licenses don't match";
}
