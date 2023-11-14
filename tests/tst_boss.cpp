
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "model/Car.h"
#include "model/user.h"
using namespace testing;

TEST(RentItNowTest, Boss)
{
    Car car();
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}
TEST(RentItNowTest, Boss2)
{
    User user();
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}

