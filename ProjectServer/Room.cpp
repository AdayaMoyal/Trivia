#include "Room.h"

#define ACTIVE 1
#define NOT_ACTIVE_BUT_NOT_CLOSED 2
#define NOT_ACTIVE 0

Room::Room()
{

}

Room::Room(RoomData rm)
{
    this->m_metadata = rm;
    this->m_metadata.isActive = NOT_ACTIVE_BUT_NOT_CLOSED;
}

Room::~Room()
{
}

bool Room::addUser(LoggedUser user)
{
    if (this->m_metadata.maxPlayers == this->m_users.size())
    {
        return false;//there are max number of players in the room
    }
    this->m_users.push_back(user);
    return true;
}

void Room::removeUser(LoggedUser user)
{
    for (auto it = this->m_users.begin(); it != this->m_users.end(); it++)
    {
        if (it->getUsername().compare(user.getUsername()) == 0)
        {
            this->m_users.erase(it);
            break;
        }
    }
    if (this->m_users.size() == 0)//the room is not active anymore-zero players left in the room
    {
        this->m_metadata.isActive = 0;
    }
}

std::vector<std::string> Room::getAllUsers()
{
    std::vector<std::string> names;
    for (int i = 0; i < this->m_users.size(); i++)
    {
        names.push_back(this->m_users[i].getUsername());
    }
    return names;
}

unsigned int Room::isActive()
{
    return this->m_metadata.isActive;
}

RoomData Room::getRoomData()
{
    return m_metadata;
}

std::string Room::getRoomData(RoomData rd)
{
    std::string str = "";
    str += rd.id + " ";
    str += rd.isActive + " ";
    str += rd.maxPlayers + " ";
    str += rd.name + " ";
    str += rd.numOfQuestionsInGame + " ";
    str += rd.timePerQuestion + " ";
    return str;
}

void Room::setIsActive(int activeOrNot)
{
    this->m_metadata.isActive = activeOrNot;
}