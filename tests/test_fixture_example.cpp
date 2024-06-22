#include <gtest/gtest.h>
#include <stdexcept>
#include <iostream>

class Calculator {
public:
    Calculator() {
        std::cout << "Calculator initialized\n";
    }

    ~Calculator() {
        std::cout << "Calculator destroyed\n";
    }

    int add(int a, int b) {
        return a + b;
    }

    int subtract(int a, int b) {
        return a - b;
    }
};

class CalculatorTest : public ::testing::Test {
protected:
    Calculator* calc;

    void SetUp() override {
        calc = new Calculator();
        std::cout << "SetUp: Calculator instance created\n";
    }

    void TearDown() override {
        delete calc;
        std::cout << "TearDown: Calculator instance destroyed\n";
    }
};

TEST_F(CalculatorTest, HandlesAddition) {
    std::cout << "Running test\n";
    EXPECT_EQ(calc->add(1, 2), 3);
    EXPECT_EQ(calc->add(-1, -1), -2);
    EXPECT_EQ(calc->add(-1, 1), 0);
}

TEST_F(CalculatorTest, HandlesSubtraction) {
    std::cout << "Running test\n";
    EXPECT_EQ(calc->subtract(5, 3), 2);
    EXPECT_EQ(calc->subtract(3, 5), -2);
}