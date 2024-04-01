#pragma once
#include "IRequestHandler.h"
#include "RequestsStructs.h"
#include "RequestHandlerFactory.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "GameManager.h"

class RequestHandlerFactory;
class StatisticsManager;

class RoomMemberRequestHandler : public IRequestHandler
{
public:
	RoomMemberRequestHandler(RequestHandlerFactory*, RoomManager*, LoggedUser, Room*);
	RoomMemberRequestHandler();
	~RoomMemberRequestHandler();
	virtual bool isRequestRelevant(RequestInfo);
	virtual RequestResult handleRequest(RequestInfo);
	RequestResult leaveRoom(RequestInfo);
	RequestResult getRoomState(RequestInfo);

private:
	Room* m_room;
	LoggedUser m_user;
	RoomManager* m_roomManager;
	RequestHandlerFactory* m_handlerFactory;
};
