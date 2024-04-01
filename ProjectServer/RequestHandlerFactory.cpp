#include "RequestHandlerFactory.h"
#include "MenuRequestHandler.h"
#include "SqliteDatabase.h"
#include "LoginManager.h"
#include "GameRequestHandler.h"

RequestHandlerFactory::RequestHandlerFactory()
{
	this->m_loginManager = nullptr;
	this->m_database = new SqliteDatabase();
}

RequestHandlerFactory::RequestHandlerFactory(IDatabase* db)
{
	this->m_loginManager = LoginManager(db);
	this->m_database = db;
	this->m_statisticsManager = StatisticsManager(db);
	this->m_roomManager = new RoomManager();
	this->m_gameManager = new GameManager(db);
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(this);
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
	return this->m_loginManager;
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser user)
{
	return new MenuRequestHandler(this->m_database, user, this->m_roomManager, this);
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
	return this->m_statisticsManager;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
	return *this->m_roomManager;
}

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(LoggedUser user, Room* room)
{
	return new RoomAdminRequestHandler(this, this->m_roomManager, user, room);
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(LoggedUser user, Room* room)
{
	return new RoomMemberRequestHandler(this, this->m_roomManager, user, room);
}

GameRequestHandler* RequestHandlerFactory::createGameRequestHandler(Game* game, LoggedUser user)
{
	return new GameRequestHandler(game, user, this->m_gameManager, this);
}

GameManager& RequestHandlerFactory::getGameManager()
{
	return *this->m_gameManager;
}