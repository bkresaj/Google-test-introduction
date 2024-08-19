#pragma once

#include "database_interface.h"

class UserService
{
public:
    UserService(DatabaseInterface &db);
    std::string FetchUserName(int userId);
    void RegisterUser(int userId, const std::string &userName);

private:
    DatabaseInterface &db_;
};