#include "user_service.h"

UserService::UserService(DatabaseInterface &db) : db_(db) {}

std::string UserService::FetchUserName(int userId)
{
    return db_.GetUser(userId);
}

void UserService::RegisterUser(int userId, const std::string &userName)
{
    db_.AddUser(userId, userName);
}
