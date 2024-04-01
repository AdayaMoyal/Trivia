#include "RoomManager.h"

std::map<int, Room> RoomManager::m_rooms;
std::mutex RoomManager::RoomManagerMutex;//To add the room to the map without issues

RoomManager::RoomManager()
{
    this->m_roomId = 1;
}

int RoomManager::createRoom(LoggedUser user, RoomData roomData)
{
    roomData.id = this->m_roomId;
    Room* room = new Room(roomData);
    room->addUser(user);
    RoomManagerMutex.lock();
    this->m_rooms.insert({ roomData.id, *room });
    RoomManagerMutex.unlock();
    this->m_roomId++;
    return roomData.id;
}

void RoomManager::deleteRoom(int ID)
{
    this->m_rooms.erase(ID);
}

unsigned int RoomManager::getRoomState(int ID)
{
    return this->m_rooms.at(ID).isActive();
}

std::vector<RoomData> RoomManager::getRooms()
{
    std::vector<RoomData> rdVector;
    for (auto itr = this->m_rooms.begin(); itr != this->m_rooms.end(); itr++)
    {
        rdVector.push_back(itr->second.getRoomData());
    }
    return rdVector;
}

Room& RoomManager::getRoom(int ID)
{
    return this->m_rooms.find(ID)->second;
}

