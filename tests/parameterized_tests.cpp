#include <gtest/gtest.h>

int multiply(int a, int b) {
    return a * b;
}

// Non-parameterized tests
TEST(MultiplyTest, HandlesPositiveNumbers) {
    EXPECT_EQ(multiply(2, 3), 6);
}

TEST(MultiplyTest, HandlesNegativeNumbers) {
    EXPECT_EQ(multiply(-2, -3), 6);
}

TEST(MultiplyTest, HandlesMixedNumbers) {
    EXPECT_EQ(multiply(-2, 3), -6);
}

TEST(MultiplyTest, HandlesZeros) {
    EXPECT_EQ(multiply(0, 0), 0);
    EXPECT_EQ(multiply(0, 5), 0);
    EXPECT_EQ(multiply(4, 0), 0);
}

// Parameterized test case
class MultiplyTest : public ::testing::TestWithParam<std::tuple<int, int, int>> {
};

TEST_P(MultiplyTest, HandlesAllCases) {
    int a = std::get<0>(GetParam());
    int b = std::get<1>(GetParam());
    int expected = std::get<2>(GetParam());
    EXPECT_EQ(multiply(a, b), expected);
}

// Test cases to be run
INSTANTIATE_TEST_SUITE_P(MultiplyTests, MultiplyTest, ::testing::Values(
    std::make_tuple(2, 3, 6),
    std::make_tuple(-2, -3, 6),
    std::make_tuple(-2, 3, -6),
    std::make_tuple(0, 0, 0),
    std::make_tuple(0, 5, 0),
    std::make_tuple(4, 0, 0)
));