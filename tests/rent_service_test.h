#ifndef RENT_SERVICE_TEST_H
#define RENT_SERVICE_TEST_H
#include "gtest/gtest.h"
#include "service/usermanagementservice.h"
#include "service/carmanagementservice.h"


class RentItNowTest_RENT_SERVICE : public ::testing::Test {
protected:
    void SetUp() override {
        UserManagementService::getInstance().clearAll();
        CarManagementService::getInstance().clearAll();
    }

    void TearDown() override {
        // This function will be called after each test case
        // Place your teardown code here
    }
};
#endif // RENT_SERVICE_TEST_H
