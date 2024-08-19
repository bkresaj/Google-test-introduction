#pragma once

#include <string>

class DatabaseInterface
{
public:
    virtual ~DatabaseInterface() = default;

    virtual std::string GetUser(int userId) const = 0;
    virtual void AddUser(int userId, const std::string &userName) = 0;
};