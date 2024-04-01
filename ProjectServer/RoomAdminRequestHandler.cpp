#include "RoomAdminRequestHandler.h"

#define ACTIVE 1
#define NOT_ACTIVE 0
#define NOT_ACTIVE_BUT_NOT_CLOSED 2

RoomAdminRequestHandler::RoomAdminRequestHandler() :IRequestHandler()
{
	this->m_handlerFactory = new RequestHandlerFactory();
	this->m_roomManager = new RoomManager();
	this->m_user = LoggedUser();
	this->m_room = new Room();
}

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory* handler, RoomManager* roomManager, LoggedUser user, Room* room) :IRequestHandler()
{
	this->m_handlerFactory = handler;
	this->m_roomManager = roomManager;
	this->m_user = user;
	this->m_room = room;
}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo request)
{
	return (request.RequestId == CLOSEROOM || request.RequestId == STARTGAME || request.RequestId == GETROOMSTATE);
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo request)
{
	RequestResult result;
	ErrorResponse errorRes;
	if (isRequestRelevant(request))
	{
		switch (request.RequestId)
		{
		case CLOSEROOM:
			result = closeRoom(request);
			break;
		case STARTGAME:
			result = startGame(request);
			break;
		case GETROOMSTATE:
			result = getRoomState(request);
			break;
		}
	}
	else
	{//if the request is not possible / don't exist
		errorRes.message = std::to_string(ERROR_RESPONSE);
		result.response = JsonResponsePacketSerializer::serializeResponse(errorRes);
		result.newHandler = nullptr;
	}
	return result;
}

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo request)
{
	RequestResult result;
	CloseRoomResponse closeRoom;
	closeRoom.status = CLOSEROOM_RESPONSE;
	unsigned int roomId = this->m_room->getRoomData().id;
	this->m_room->setIsActive(NOT_ACTIVE);
	this->m_roomManager->deleteRoom(roomId);
	result.response = JsonResponsePacketSerializer::serializeResponse(closeRoom);
	result.newHandler = this->m_handlerFactory->createMenuRequestHandler(this->m_user);
	return result;
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo request)
{
	RequestResult result;
	StartGameResponse startGame;
	startGame.status = STARTGAME_RESPONSE;
	unsigned int roomId = this->m_room->getRoomData().id;
	this->m_roomManager->getRoom(roomId).setIsActive(ACTIVE);
	result.response = JsonResponsePacketSerializer::serializeResponse(startGame);
	this->m_handlerFactory->getGameManager().createGame(this->m_handlerFactory->getRoomManager().getRoom(roomId));
	Game* game = this->m_handlerFactory->getGameManager().getGame(roomId);
	result.newHandler = this->m_handlerFactory->createGameRequestHandler(game, this->m_user);
	return result;
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo request)
{
	RequestResult result;
	GetRoomStateResponse getRoomState;
	getRoomState.status = GETROOMSTATE_RESPONSE;
	if (this->m_room->isActive() == ACTIVE)
	{
		getRoomState.status = ACTIVE;
	}
	else if(this->m_room->isActive() == NOT_ACTIVE_BUT_NOT_CLOSED)
	{
		getRoomState.status = NOT_ACTIVE_BUT_NOT_CLOSED;
	}
	else
	{
		getRoomState.status = NOT_ACTIVE;
	}
	getRoomState.players = this->m_roomManager->getRoom(this->m_room->getRoomData().id).getAllUsers();
	getRoomState.questionCount = this->m_room->getRoomData().numOfQuestionsInGame;
	getRoomState.answerTimeout = this->m_room->getRoomData().timePerQuestion;
	result.response = JsonResponsePacketSerializer::serializeResponse(getRoomState);
	result.newHandler = this;
	return result;
}