#include "RoomMemberRequestHandler.h"
#include "JsonResponsePacketSerializer.h"

#define ACTIVE 1
#define NOT_ACTIVE_BUT_NOT_CLOSED 2
#define NOT_ACTIVE 0

RoomMemberRequestHandler::RoomMemberRequestHandler() :IRequestHandler()
{
	this->m_handlerFactory = new RequestHandlerFactory();
	this->m_roomManager = new RoomManager();
	this->m_user = LoggedUser();
	this->m_room = new Room();
}

RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory* handler, RoomManager* roomManager, LoggedUser user, Room* room)
{
	this->m_handlerFactory = handler;
	this->m_roomManager = roomManager;
	this->m_user = user;
	this->m_room = room;
}

RoomMemberRequestHandler::~RoomMemberRequestHandler()
{

}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo request)
{
	return (request.RequestId == GETROOMSTATE || request.RequestId == LEAVEROOM);
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo request)
{
	RequestResult result;
	ErrorResponse errorRes;
	if (isRequestRelevant(request))
	{
		switch (request.RequestId)
		{
		case GETROOMSTATE:
			result = getRoomState(request);
			break;
		case LEAVEROOM:
			result = leaveRoom(request);
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

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo request)
{
	RequestResult result;
	LeaveRoomResponse leaveRoom;
	try {
		this->m_roomManager->getRoom(this->m_room->getRoomData().id).removeUser(this->m_user);
	}
	catch (std::exception ex)
	{
		//
	}
	leaveRoom.status = LEAVEROOM_RESPONSE;
	result.response = JsonResponsePacketSerializer::serializeResponse(leaveRoom);
	result.newHandler = this->m_handlerFactory->createMenuRequestHandler(this->m_user);
	return result;
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo request)
{
	RequestResult result;
	GetRoomStateResponse getRoomState;
	getRoomState.status = GETROOMSTATE_RESPONSE;
	if (this->m_room->isActive() == ACTIVE)
	{
		getRoomState.status = ACTIVE;
		Game* game = this->m_handlerFactory->getGameManager().getGame(this->m_room->getRoomData().id);
		result.newHandler = this->m_handlerFactory->createGameRequestHandler(game, this->m_user);
	}
	else if (this->m_room->isActive() == NOT_ACTIVE_BUT_NOT_CLOSED)
	{
		getRoomState.status = NOT_ACTIVE_BUT_NOT_CLOSED;
		result.newHandler = this->m_handlerFactory->createRoomMemberRequestHandler(this->m_user, this->m_room);
	}
	else
	{
		getRoomState.status = NOT_ACTIVE;
	}
	if (getRoomState.status == NOT_ACTIVE)
	{
		getRoomState.players;
		getRoomState.questionCount = 0;
		getRoomState.answerTimeout = 0;
		result.newHandler = this->m_handlerFactory->createMenuRequestHandler(this->m_user);
	}
	else
	{
		getRoomState.players = this->m_room->getAllUsers();
		getRoomState.questionCount = this->m_room->getRoomData().numOfQuestionsInGame;
		getRoomState.answerTimeout = this->m_room->getRoomData().timePerQuestion;
	}
	result.response = JsonResponsePacketSerializer::serializeResponse(getRoomState);
	return result;
}
