#include <string>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

class Database
{
public:
    virtual ~Database() = default;
    virtual std::string GetUser(int userId) const = 0;
    virtual void AddUser(int userId, const std::string &userName) = 0;
};

class MockDatabase : public Database
{
public:
    MOCK_METHOD(std::string, GetUser, (int userId), (const, override));
    MOCK_METHOD(void, AddUser, (int userId, const std::string &userName), (override));
};

class UserService
{
public:
    UserService(Database &db) : db_(db) {}

    std::string FetchUserName(int userId)
    {
        return db_.GetUser(userId);
    }

    void RegisterUser(int userId, const std::string &userName)
    {
        db_.AddUser(userId, userName);
    }

private:
    Database &db_;
};

TEST(UserServiceTest, FetchUserNameExpectCall)
{
    MockDatabase mockDb;
    UserService userService(mockDb);

    // Setting expectations
    EXPECT_CALL(mockDb, GetUser(1))
        .Times(1)
        .WillOnce(::testing::Return("John Doe"));

    // Additional expectation for another user id
    EXPECT_CALL(mockDb, GetUser(2))
        .Times(1)
        .WillOnce(::testing::Return("Jane Doe"));

    // Perform actions and verify results
    EXPECT_EQ(userService.FetchUserName(1), "John Doe");
    EXPECT_EQ(userService.FetchUserName(2), "Jane Doe");
}

TEST(UserServiceTest, FetchUserNameOnCall)
{
    MockDatabase mockDb;
    UserService userService(mockDb);

    // Setting default behavior
    ON_CALL(mockDb, GetUser(::testing::_))
        .WillByDefault(::testing::Return("Default User"));

    // Setting specific expectations
    EXPECT_CALL(mockDb, GetUser(2))
        .Times(1);

    // Additional expectation to verify default behavior
    EXPECT_CALL(mockDb, GetUser(3))
        .Times(1);

    // Perform actions and verify results
    EXPECT_EQ(userService.FetchUserName(2), "Default User");
    EXPECT_EQ(userService.FetchUserName(3), "Default User");
}