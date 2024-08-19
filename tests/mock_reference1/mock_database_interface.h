#pragma once

#include <gmock/gmock.h>
#include "database_interface.h"

class MockDatabaseInterface : public DatabaseInterface
{
public:
    // MOCK_METHOD macro is used to create mock methods
    MOCK_METHOD(std::string, GetUser, (int userId), (const, override));
    MOCK_METHOD(void, AddUser, (int userId, const std::string &userName), (override));
};