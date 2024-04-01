#pragma once
#include <string>
#include <iostream>
#include "LoggedUser.h"
#include "IDatabase.h"
#include <vector>
class IDatabase;
class LoginManager
{
public:
	LoginManager();
	LoginManager(IDatabase*);
	bool signup(std::string, std::string, std::string);
	bool login(std::string, std::string);
	void logout(std::string);
private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
};