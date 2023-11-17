#ifndef USER_MANAGER_TEST_H
#define USER_MANAGER_TEST_H
#include "gtest/gtest.h"
#include "service/usermanagementservice.h"


class RentItNowTest_USER_MANAGER : public ::testing::Test {
protected:
    void SetUp() override {
        UserManagementService::getInstance().clearAll();
    }

    void TearDown() override {
        // This function will be called after each test case
        // Place your teardown code here
    }
};
#endif // USER_MANAGER_TEST_H
