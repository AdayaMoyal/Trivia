#pragma once
#include <iostream>
#include "IDatabase.h"
#include "LoginManager.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "GameRequestHandler.h"

class LoginRequestHandler;
class IDatabase;
class MenuRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;
class GameRequestHandler;
class GameManager;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory();
	RequestHandlerFactory(IDatabase*);
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager();
	MenuRequestHandler* createMenuRequestHandler(LoggedUser);
	StatisticsManager& getStatisticsManager();
	RoomManager& getRoomManager();
	RoomAdminRequestHandler* createRoomAdminRequestHandler(LoggedUser, Room*);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(LoggedUser, Room*);
	GameRequestHandler* createGameRequestHandler(Game*, LoggedUser);
	GameManager& getGameManager();
private:
	LoginManager m_loginManager;
	RoomManager* m_roomManager;
	StatisticsManager m_statisticsManager;
	IDatabase* m_database;
	GameManager* m_gameManager;
};