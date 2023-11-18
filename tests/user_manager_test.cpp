#include "user_manager_test.h"
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "car_manager_test.h"
#include "model/user.h"

using namespace testing;

TEST_F(RentItNowTest_USER_MANAGER, ADD)
{
    User* testUser=new User("John", "Doe", "123 Main St", "1234-5678-9012-3456", "ABCD123456");

    ASSERT_FALSE(UserManagementService::getInstance().add(nullptr));
    ASSERT_TRUE(UserManagementService::getInstance().add(testUser));
    ASSERT_EQ(1,UserManagementService::getInstance().getUsers().size());
    ASSERT_FALSE(UserManagementService::getInstance().add(testUser));
    testUser=new User("John", "Doe", "123 Main St", "1234-5678-90125-3456", "ABCD1234456");
    ASSERT_TRUE(UserManagementService::getInstance().add(testUser));
    ASSERT_EQ(2,UserManagementService::getInstance().getUsers().size());
    delete testUser;

}
TEST_F(RentItNowTest_USER_MANAGER, UPDATE)
{
    User* testUser=new User("John", "Doe", "123 Main St", "1234-5678-9012-3456", "ABCD123456");
    User* testUser2=new User("John", "Weak", "123 Main St", "1234-5678-9012-3456", "ABCD123456");
    User* testUser3=new User("John", "Weak", "123 Main St", "1234-5678-9012-3456", "ABCdfD123456");

    UserManagementService::getInstance().add(testUser);
    UserManagementService::getInstance().add(testUser3);
    EXPECT_FALSE(UserManagementService::getInstance().update("ABCD123456",nullptr));
    EXPECT_FALSE(UserManagementService::getInstance().update("",nullptr));
    EXPECT_FALSE(UserManagementService::getInstance().update("",testUser));

    EXPECT_TRUE(UserManagementService::getInstance().update("ABCD123456",testUser2));
    testUser2->setDrivingLicense(testUser3->getDrivingLicense());
    EXPECT_FALSE(UserManagementService::getInstance().update("ABCD123456",testUser2));
    testUser->setDrivingLicense("123456789");
    EXPECT_TRUE(UserManagementService::getInstance().update("ABCD123456",testUser));
    EXPECT_TRUE(UserManagementService::getInstance().getUsers().count("123456789")>0);
    EXPECT_FALSE(UserManagementService::getInstance().update("ABCD123456",testUser3));

    delete testUser;

    delete testUser2;
    delete testUser3;
}
TEST_F(RentItNowTest_USER_MANAGER, DELETE)
{
    User* testUser=new User("John", "Doe", "123 Main St", "1234-5678-9012-3456", "ABCD123456");
    User* testUser2=new User("John", "Weak", "123 Main St", "1234-5678-df9012-3456", "ABCdfD123456");

    EXPECT_TRUE(UserManagementService::getInstance().add(testUser));
    EXPECT_TRUE(UserManagementService::getInstance().add(testUser2));

    ASSERT_EQ(2,UserManagementService::getInstance().getUsers().size());;
    EXPECT_TRUE(UserManagementService::getInstance().remove(testUser));
    ASSERT_EQ(1,UserManagementService::getInstance().getUsers().size());
    EXPECT_TRUE(UserManagementService::getInstance().remove("ABCdfD123456"));
    EXPECT_FALSE(UserManagementService::getInstance().remove("ABCdfD123456"));

    ASSERT_EQ(0,UserManagementService::getInstance().getUsers().size());

    delete testUser;
    delete testUser2;
}
TEST_F(RentItNowTest_USER_MANAGER, GET_MY_USERS)
{
    User* testUser=new User("John", "Doe", "123 Main St", "1234-5678-9012-3456", "ABCD123456");
    User* testUser2=new User("John", "Weak", "123 Main St", "1234-5678-df9012-3456", "ABCdfD123456");
    std::map<string, std::shared_ptr<User>>test;
    test["ABCD123456"]=std::make_shared<User>(*testUser);
    test["ABCdfD123456"]=std::make_shared<User>(*testUser2);


    EXPECT_TRUE(UserManagementService::getInstance().add(testUser));
    EXPECT_TRUE(UserManagementService::getInstance().add(testUser2));


    auto testcar=UserManagementService::getInstance().getUsers()["123456"].get();

    EXPECT_EQ(test["ABCD123456"].get()->toString(),testUser->toString());
    testcar=UserManagementService::getInstance().getUsers()["ABCD123456"].get();
    EXPECT_EQ(test["ABCdfD123456"].get()->toString(),testUser2->toString());
    delete testUser;
    delete testUser2;

}

