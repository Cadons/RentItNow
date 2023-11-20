#ifndef CAR_MANAGER_TEST_H
#define CAR_MANAGER_TEST_H
#include "gtest/gtest.h"
#include "service/carmanagementservice.h"
#include "service/rentingservice.h"

class RentItNowTest_CAR_MANAGER : public ::testing::Test {
protected:
    void SetUp() override {
        CarManagementService::getInstance().clearAll();
        RentingService::getInstance().getMyBank()->deposit(10000);

    }

    void TearDown() override {
        // This function will be called after each test case
        // Place your teardown code here
    }
};
#endif // CAR_MANAGER_TEST_H
