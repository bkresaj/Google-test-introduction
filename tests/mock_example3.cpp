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

TEST(UserServiceTest, TestAllActions)
{
    MockDatabase mockDb;
    UserService userService(mockDb);

    // Example of Return(value)
    EXPECT_CALL(mockDb, GetUser(1))
        .WillOnce(::testing::Return("JohnDoe"));
    EXPECT_EQ(userService.FetchUserName(1), "JohnDoe");

    // Example of Assign(&variable, value)
    int callCount = 0;
    EXPECT_CALL(mockDb, AddUser(::testing::_, ::testing::_))
        .WillOnce(::testing::Assign(&callCount, 1));
    userService.RegisterUser(20, "Bob");
    EXPECT_EQ(callCount, 1); // callCount should be 1 after the call

    // Example of Throw(exception)
    EXPECT_CALL(mockDb, GetUser(999))
        .WillOnce(::testing::Throw(std::runtime_error("User not found")));
    EXPECT_THROW(userService.FetchUserName(999), std::runtime_error);

    // Example of Invoke(f)
    EXPECT_CALL(mockDb, GetUser(::testing::_))
        .WillOnce(::testing::Invoke([](int id)
                                    { return id == 3 ? "Bob" : "Unknown"; }));
    EXPECT_EQ(userService.FetchUserName(3), "Bob");

    // Example of DoAll(a1, a2, ..., an)
    EXPECT_CALL(mockDb, AddUser(::testing::_, ::testing::_))
        .WillOnce(::testing::DoAll(::testing::Assign(&callCount, 2), ::testing::Return()));
    userService.RegisterUser(20, "Eve");
    EXPECT_EQ(callCount, 2); // callCount should be 2 after the call
}