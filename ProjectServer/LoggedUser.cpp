#include "LoggedUser.h"


LoggedUser::LoggedUser()
{
	this->m_username = "";
}

LoggedUser::LoggedUser(std::string username)
{
	this->m_username = username;
}

bool LoggedUser::operator<(LoggedUser other) const
{
	return this->m_username < other.m_username;
}

std::string LoggedUser::getUsername() const
{
	return this->m_username;
}