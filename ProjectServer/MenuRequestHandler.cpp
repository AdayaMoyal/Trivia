#include "MenuRequestHandler.h"
#include "JsonResponsePacketSerializer.h"

#define ACTIVE 1
#define NOT_ACTIVE_BUT_NOT_CLOSED 2
#define NOT_ACTIVE 0
#define LIMITED 0

MenuRequestHandler::MenuRequestHandler() :IRequestHandler()
{

}

MenuRequestHandler::MenuRequestHandler(IDatabase* db, LoggedUser user, RoomManager* roomManager, RequestHandlerFactory* handler) :IRequestHandler()
{
	this->m_database = db;
	this->m_user = user;
	this->m_statisticsManager = new StatisticsManager(db);
	this->m_roomManager = roomManager;
	this->m_handlerFactory = handler;
}

MenuRequestHandler::~MenuRequestHandler()
{

}

bool MenuRequestHandler::isRequestRelevant(RequestInfo request)
{
	return (request.RequestId == PLAYERS_IN_ROOM || request.RequestId == JOIN_ROOM || request.RequestId == CREATE_ROOM || request.RequestId == HIGH_SCORE || request.RequestId == LOG_OUT || request.RequestId == GET_ROOMS || request.RequestId == GET_STATISTICS || request.RequestId == ADDQUESTION);
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo request)
{
	RequestResult* result = new RequestResult();
	ErrorResponse errorRes;
	if (isRequestRelevant(request))
	{
		switch (request.RequestId)
		{
		case PLAYERS_IN_ROOM:
			*result = getPlayersInRoom(request);
			break;
		case JOIN_ROOM:
			*result = joinRoom(request);
			break;
		case CREATE_ROOM:
			*result = createRoom(request);
			break;
		case HIGH_SCORE:
			*result = getHighScore(request);
			break;
		case LOG_OUT:
			*result = signout(request);
			break;
		case GET_ROOMS:
			*result = getRooms(request);
			break;
		case GET_STATISTICS:
			*result = getPersonalStats(request);
			break;
		case ADDQUESTION:
			*result = addQuestion(request);
			break;
		}
	}
	else
	{//if the request is not possible / don't exist
		errorRes.message = std::to_string(ERROR_RESPONSE);
		result->response = JsonResponsePacketSerializer::serializeResponse(errorRes);
		result->newHandler = nullptr;
	}
	return *result;
}

RequestResult MenuRequestHandler::signout(RequestInfo request)
{
	RequestResult result;
	LogoutResponse logOut;
	this->m_handlerFactory->getLoginManager().logout(this->m_user.getUsername());
	logOut.status = LOGOUT_RESPONSE;
	result.response = JsonResponsePacketSerializer::serializeResponse(logOut);
	result.newHandler = this->m_handlerFactory->createLoginRequestHandler();
	return result;
}

RequestResult MenuRequestHandler::getRooms(RequestInfo request)
{
	RequestResult result;
	GetRoomsResponse getRooms;
	getRooms.status = GETROOMS_RESPONSE;
	getRooms.rooms = this->m_roomManager->getRooms();
	result.response = JsonResponsePacketSerializer::serializeResponse(getRooms);
	result.newHandler = this;
	return result;
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo request)
{
	RequestResult result;
	GetPlayersInRoomRequest playersInRoom;
	GetPlayersInRoomResponse players;
	playersInRoom = JsonRequestPacketDeserializer::deserializeGetPlayersRequest(request.buffer);
	Room room = this->m_roomManager->getRoom(playersInRoom.roomId);
	players.players = room.getAllUsers();
	result.response = JsonResponsePacketSerializer::serializeResponse(players);
	result.newHandler = this;
	return result;
}

RequestResult MenuRequestHandler::getPersonalStats(RequestInfo request)
{
	RequestResult result;
	GetPersonalStatsResponse getPersonalStats;
	getPersonalStats.status = USER_STATISTICS;
	getPersonalStats.statistics = this->m_statisticsManager->getUserStatistics(this->m_user.getUsername());
	result.response = JsonResponsePacketSerializer::serializeResponse(getPersonalStats);
	result.newHandler = this;
	return result;
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo request)
{
	RequestResult result;
	GetHighScoreResponse getHighScore;
	getHighScore.status = HIGH_SCORE_RESPONSE;
	getHighScore.statistics = this->m_statisticsManager->getHighScore();
	result.response = JsonResponsePacketSerializer::serializeResponse(getHighScore);
	result.newHandler = this;
	return result;
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo request)
{
	RequestResult result;
	JoinRoomResponse joinRoom;
	JoinRoomRequest joinRoomRequest;
	joinRoomRequest = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(request.buffer);
	bool added = this->m_roomManager->getRoom(joinRoomRequest.roomId).addUser(this->m_user);
	if (added == false)
	{
		joinRoom.status = LIMITED;
	}
	else
	{
		joinRoom.status = JOINROOM_RESPONSE;
	}
	result.response = JsonResponsePacketSerializer::serializeResponse(joinRoom);
	result.newHandler = (IRequestHandler*)this->m_handlerFactory->createRoomMemberRequestHandler(this->m_user, &this->m_roomManager->getRoom(joinRoomRequest.roomId));
	return result;
}

RequestResult MenuRequestHandler::createRoom(RequestInfo request)
{
	RequestResult result;
	CreateRoomResponse createRoom;
	CreateRoomRequest createRoomRequest;
	createRoomRequest = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(request.buffer);
	RoomData roomData{ 0, createRoomRequest.roomName, createRoomRequest.maxUsers, createRoomRequest.questionCount, createRoomRequest.answerTimeout, NOT_ACTIVE_BUT_NOT_CLOSED };
	createRoom.roomId = this->m_roomManager->createRoom(this->m_user, roomData);
	createRoom.status = CREATEROOM_RESPONSE;
	result.response = JsonResponsePacketSerializer::serializeResponse(createRoom);
	result.newHandler = (IRequestHandler*)this->m_handlerFactory->createRoomAdminRequestHandler(this->m_user, &this->m_roomManager->getRoom(createRoom.roomId));
	return result;
}

RequestResult MenuRequestHandler::addQuestion(RequestInfo request)
{
	RequestResult result;
	AddQuestionRequest addQuestionRequest;
	AddQuestionResponse addQuestion;
	addQuestionRequest = JsonRequestPacketDeserializer::deserializeAddQuestionRequest(request.buffer);
	this->m_database->addQuestion(addQuestionRequest);
	addQuestion.status = ADDQUESTION_RESPONSE;
	result.response = JsonResponsePacketSerializer::serializeResponse(addQuestion);
	result.newHandler = this;
	return result;
}