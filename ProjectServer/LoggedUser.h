#pragma once
#include <iostream>

class LoggedUser
{
public:
	LoggedUser();
	LoggedUser(std::string);
	std::string getUsername() const;
	bool operator<(LoggedUser other) const;
private:
	std::string m_username;
};