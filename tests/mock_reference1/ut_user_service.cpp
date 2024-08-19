#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "mock_database_interface.h"
#include "user_service.h"

TEST(MockReference1UserServiceTest, FetchUserName)
{
    // Create a mock object
    MockDatabaseInterface mockDb;

    // Set up expectations
    EXPECT_CALL(mockDb, GetUser(1))
        .WillOnce(::testing::Return("JohnDoe")); // When GetUser(1) is called, return "JohnDoe"

    // Use the mock in the UserService
    UserService userService(mockDb);

    // Call the method and check the result
    std::string userName = userService.FetchUserName(1);
    EXPECT_EQ(userName, "JohnDoe"); // Verify the result
}

TEST(MockReference1UserServiceTest, RegisterUser)
{
    // Create a mock object
    MockDatabaseInterface mockDb;

    // Set up expectations
    EXPECT_CALL(mockDb, AddUser(1, "JohnDoe"))
        .Times(1); // Expect AddUser to be called once with specific arguments

    // Use the mock in the UserService
    UserService userService(mockDb);

    // Call the method
    userService.RegisterUser(1, "JohnDoe");
}