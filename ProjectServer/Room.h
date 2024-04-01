#pragma once
#include "LoggedUser.h"
#include <iostream>
#include <vector>

struct RoomData
{
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	unsigned int isActive;//Room that is active- isActive=1. Room that is not active- isActive=0. Room that is not active but not closed - isActive=2 
};

class Room
{
public:
	Room();
	Room(RoomData);
	~Room();
	bool addUser(LoggedUser);
	void removeUser(LoggedUser);
	std::vector<std::string> getAllUsers();
	unsigned int isActive();
	void setIsActive(int activeOrNot);
	RoomData getRoomData();
	static std::string getRoomData(RoomData);

private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
};

