#include <gtest/gtest.h>
#include <stdexcept>
#include <iostream>
#include <cstdlib>

void fatalFunction() {
    throw std::runtime_error("Fatal error occurred!");
}

void NormalExit() {
    std::cerr << "Success\n";
    std::exit(0);
}

void errorFunction() {
    int n = 5;
    if (n != 42) {
        std::cerr << "Error on line " << __LINE__;
        std::abort();
    }
}

TEST(DeathTest, HandlesFatalError) {
    EXPECT_ANY_THROW(fatalFunction());
}

TEST(DeathTest, ExpectDeath) {
    EXPECT_DEATH(errorFunction(), "Error on line .*");
}

TEST(DeathTest, AssertDeath) {
    ASSERT_DEATH(errorFunction(), "Error on line .*");
}

TEST(DeathTest, ExpectDeathIfSupported) {
    EXPECT_DEATH_IF_SUPPORTED(errorFunction(), "Error on line .*");
}

TEST(DeathTest, AssertDeathIfSupported) {
    ASSERT_DEATH_IF_SUPPORTED(errorFunction(), "Error on line .*");
}

TEST(DeathTest, ExpectDebugDeath) {
    EXPECT_DEBUG_DEATH(errorFunction(), "Error on line .*");
}

TEST(DeathTest, AssertDebugDeath) {
    ASSERT_DEBUG_DEATH(errorFunction(), "Error on line .*");
}

TEST(DeathTest, ExpectExit) {
    EXPECT_EXIT(NormalExit(), testing::ExitedWithCode(0), "Success");
}

TEST(DeathTest, AssertExit) {
    ASSERT_EXIT(NormalExit(), testing::ExitedWithCode(0), "Success");
}