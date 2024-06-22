#include <gtest/gtest.h>

// Function to be tested
int add(int a, int b) {
    return a + b;
}

bool isPositive(int a) {
    return a > 0;
}

float divide(float a, float b) {
    if (b == 0) throw std::runtime_error("Division by zero");
    return a / b;
}

// Basic Assertions
TEST(BasicAssertionsTest, HandlesBasicAssertions) {
    EXPECT_TRUE(isPositive(5));
    EXPECT_FALSE(isPositive(-5));
}

// Binary Comparison Assertions
TEST(BinaryComparisonTest, HandlesComparisonAssertions) {
    EXPECT_EQ(add(1, 2), 3);
    EXPECT_NE(add(1, 2), 4);
    EXPECT_LT(add(1, 2), 5);
    EXPECT_LE(add(1, 2), 3);
    EXPECT_GT(add(3, 2), 4);
    EXPECT_GE(add(3, 2), 5);
}

// String Assertions
TEST(StringAssertionsTest, HandlesStringAssertions) {
    const char* str1 = "hello";
    const char* str2 = "hello";
    const char* str3 = "world";
    EXPECT_STREQ(str1, str2);
    EXPECT_STRNE(str1, str3);
    EXPECT_STRCASEEQ("HELLO", "hello");
    EXPECT_STRCASENE("HELLO", "world");
}

// Floating-Point Assertions
TEST(FloatingPointAssertionsTest, HandlesFloatingPointAssertions) {
    EXPECT_FLOAT_EQ(0.1f * 10, 1.0f);
    EXPECT_DOUBLE_EQ(0.1 * 10, 1.0);
    EXPECT_NEAR(0.1 * 10, 1.0, 1e-6);
}

// Intentionally failing test
TEST(FailingTest, ThisTestWillFail) {
    EXPECT_EQ(add(1, 2), 4); // This assertion will fail
}