#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "Room.h"
#include <mutex>

class RoomManager
{
public:
	RoomManager();
	int createRoom(LoggedUser, RoomData);
	void deleteRoom(int ID);
	unsigned int getRoomState(int ID);
	std::vector<RoomData> getRooms();
	Room& getRoom(int ID);
private:
	int m_roomId;
	static std::map<int, Room> m_rooms;
	static std::mutex RoomManagerMutex;
};