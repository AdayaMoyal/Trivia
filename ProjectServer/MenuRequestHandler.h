#pragma once
#include "IRequestHandler.h"
#include "RequestsStructs.h"
#include "RequestHandlerFactory.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
class RequestHandlerFactory;
class StatisticsManager;

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler();
	MenuRequestHandler(IDatabase*, LoggedUser, RoomManager*, RequestHandlerFactory*);
	~MenuRequestHandler();
	virtual bool isRequestRelevant(RequestInfo);
	virtual RequestResult handleRequest(RequestInfo);
	RequestResult signout(RequestInfo);
	RequestResult getRooms(RequestInfo);
	RequestResult getPlayersInRoom(RequestInfo);
	RequestResult getPersonalStats(RequestInfo);
	RequestResult getHighScore(RequestInfo);
	RequestResult joinRoom(RequestInfo);
	RequestResult createRoom(RequestInfo);
	RequestResult addQuestion(RequestInfo);
private:
	IDatabase* m_database;
	LoggedUser m_user;
	RoomManager* m_roomManager;
	StatisticsManager* m_statisticsManager;
	RequestHandlerFactory* m_handlerFactory;
};
