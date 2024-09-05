#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stdexcept>
#include <string>

#include "singleton_template.h"

// Real implementation of getUser (commented out for mocking purposes)
/*
std::string getUser(const std::string& username) {
    // Imagine this function actually queries a database or a user repository.
    if (username == "john_doe") {
        return "User: john_doe, Status: Active";
    } else if (username == "jane_doe") {
        return "User: jane_doe, Status: Inactive";
    } else {
        return ""; // User not found
    }
}
*/

// Mock Class directly derived from SingletonTemplate
class MockUserManager : public SingletonTemplate<MockUserManager> {
public:
    MOCK_METHOD(std::string, getUser, (const std::string&), ());
};

// Free function to be mocked
std::string getUser(const std::string& username) {
    return MockUserManager::getInstance().getUser(username);
}

// Free function calling another free function
std::string processUser(const std::string& username) {
    std::string userInfo = getUser(username); // This is the function we want to mock
    if (userInfo.empty()) {
        return "User not found";
    } else {
        return "Processing " + userInfo;
    }
}

using ::testing::Return;

TEST(MockReference2, TestProcessUserWithMockedGetUser) {
    MockUserManager mockUserManager;

    // Set up mock expectation for getUser function
    EXPECT_CALL(mockUserManager, getUser("john_doe"))
        .WillOnce(Return("User: john_doe, Status: Active")); // Mocked response

    // Call the function which internally calls the mocked free function
    std::string result = processUser("john_doe");

    // Verify the result
    EXPECT_EQ(result, "Processing User: john_doe, Status: Active");
}

TEST(MockReference2, TestProcessUserWithMockedGetUserNotFound) {
    MockUserManager mockUserManager;

    // Set up mock expectation for getUser function to return empty for a non-existent user
    EXPECT_CALL(mockUserManager, getUser("unknown_user"))
        .WillOnce(Return("")); // Mocked response indicating user not found

    // Call the function which internally calls the mocked free function
    std::string result = processUser("unknown_user");

    // Verify the result
    EXPECT_EQ(result, "User not found");
}