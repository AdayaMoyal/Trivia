#include "LoginManager.h"
#include "SqliteDatabase.h"

LoginManager::LoginManager()
{

}

LoginManager::LoginManager(IDatabase* db)
{
	this->m_database = db;
}

bool LoginManager::signup(std::string username, std::string password, std::string mail)
{
	SqliteDatabase sqliteDatabase;
	if (sqliteDatabase.doesUserExist(username) == true)
	{
		return false;
	}
	sqliteDatabase.addNewUser(username, password, mail);
	return true;
}

bool LoginManager::login(std::string username, std::string password)
{
	SqliteDatabase sqliteDatabase;
	if (sqliteDatabase.doesUserExist(username) == true && sqliteDatabase.doesPasswordMatch(username, password) == true)
	{
		LoggedUser* user = new LoggedUser(username);
		this->m_loggedUsers.push_back(*user);
		return true;
	}
	return false;
}

void LoginManager::logout(std::string username)
{
	for (auto it = this->m_loggedUsers.begin(); it != this->m_loggedUsers.end(); it++)
	{
		if (it->getUsername().compare(username)) 
		{
			this->m_loggedUsers.erase(it);
			break;
		}
	}
}