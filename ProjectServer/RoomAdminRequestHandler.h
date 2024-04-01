#pragma once
#include "Room.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"
#include "GameManager.h"

class RoomAdminRequestHandler : public IRequestHandler
{
public:
	RoomAdminRequestHandler(RequestHandlerFactory*, RoomManager*, LoggedUser, Room*);
	RoomAdminRequestHandler();
	bool isRequestRelevant(RequestInfo);
	RequestResult handleRequest(RequestInfo);
	RequestResult closeRoom(RequestInfo);
	RequestResult startGame(RequestInfo);
	RequestResult getRoomState(RequestInfo);
private:
	Room* m_room;
	LoggedUser m_user;
	RoomManager* m_roomManager;
	RequestHandlerFactory* m_handlerFactory;
};
