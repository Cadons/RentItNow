#ifndef CAR_MANAGER_TEST_H
#define CAR_MANAGER_TEST_H
#include "gtest/gtest.h"
#include "service/carmanagmentservice.h"

class RentItNowTest_CAR_MANAGER : public ::testing::Test {
protected:
    void SetUp() override {
        CarManagmentService::getInstance().clearAll();
    }

    void TearDown() override {
        // This function will be called after each test case
        // Place your teardown code here
    }
};
#endif // CAR_MANAGER_TEST_H
