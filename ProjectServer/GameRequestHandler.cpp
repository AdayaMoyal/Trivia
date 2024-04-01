#include "GameRequestHandler.h"

GameRequestHandler::GameRequestHandler(Game* game, LoggedUser user, GameManager* gameManager, RequestHandlerFactory* handler) : IRequestHandler()
{
	this->m_game = game;
	this->m_handlerFactory = handler;
	this->m_gameManager = gameManager;
	this->m_user = user;
}

GameRequestHandler::GameRequestHandler() : IRequestHandler()
{
	this->m_game = new Game();
	this->m_gameManager = new GameManager();
	this->m_user = LoggedUser();
	this->m_handlerFactory = new RequestHandlerFactory();
}

GameRequestHandler::~GameRequestHandler()
{

}

bool GameRequestHandler::isRequestRelevant(RequestInfo request)
{
	return (request.RequestId == LEAVEGAME || request.RequestId == GETQUESTION || request.RequestId == SUBMITANSWER || request.RequestId == GETGAMERESULT);
}

RequestResult GameRequestHandler::handleRequest(RequestInfo request)
{
	RequestResult result;
	ErrorResponse errorRes;
	if (isRequestRelevant(request))
	{
		switch (request.RequestId)
		{
		case LEAVEGAME:
			result = leaveGame(request);
			break;
		case GETQUESTION:
			result = getQuestion(request);
			break;
		case SUBMITANSWER:
			result = submitAnswer(request);
			break;
		case GETGAMERESULT:
			result = getGameResults(request);
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

RequestResult GameRequestHandler::getQuestion(RequestInfo request)
{
	RequestResult result;
	GetQuestionResponse getQuestion;
	std::map<unsigned int, std::string> answers;
	int count = 0;
	getQuestion.status = GETQUESTION_RESPONSE;
	Question* question = this->m_game->getQuestionForUser(this->m_user);
	getQuestion.question = question->getQuestion();
	std::vector<std::string> PossibleAnswers = question->getPossibleAnswers();
	for (auto it = PossibleAnswers.begin(); it != PossibleAnswers.end(); it++)
	{
		answers[count] = *it;
		count++;
	}
	getQuestion.answers = answers;
	result.response = JsonResponsePacketSerializer::serializeResponse(getQuestion);
	result.newHandler = this;
	return result;
}

RequestResult GameRequestHandler::submitAnswer(RequestInfo request)
{
	RequestResult result;
	SubmitAnswerRequest submitAnswer;
	SubmitAnswerResponse submitAnswerResponse;
	submitAnswer = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(request.buffer);
	submitAnswerResponse.status = SUBMITANSWER_RESPONSE;
	submitAnswerResponse.correctAnswerId = this->m_game->submitAnswer(this->m_user, submitAnswer.answerId);
	result.response = JsonResponsePacketSerializer::serializeResponse(submitAnswerResponse);
	result.newHandler = this;
	return result;
}

RequestResult GameRequestHandler::getGameResults(RequestInfo request)
{
	RequestResult result;
	GetGameResultsResponse gameResults;
	gameResults.status = GETGAMERESULTS_RESPONSE;
	gameResults.results = this->m_game->getPlayersResults();
	result.response = JsonResponsePacketSerializer::serializeResponse(gameResults);
	if (gameResults.results.size() == 0)
	{
		result.newHandler = this;
	}
	else
	{
		this->m_handlerFactory->getRoomManager().deleteRoom(this->m_game->getGameId());
		this->m_gameManager->deleteGame(this->m_game->getGameId());
		result.newHandler = this->m_handlerFactory->createMenuRequestHandler(this->m_user);
	}
	return result;
}

RequestResult GameRequestHandler::leaveGame(RequestInfo request)
{
	RequestResult result;
	LeaveGameResponse leaveGame;
	leaveGame.status = LEAVEGAME_RESPONSE;
	this->m_game->removePlayer(this->m_user);
	this->m_handlerFactory->getRoomManager().getRoom(this->m_game->getGameId()).removeUser(this->m_user);
	result.response = JsonResponsePacketSerializer::serializeResponse(leaveGame);
	result.newHandler = this->m_handlerFactory->createMenuRequestHandler(this->m_user);
	return result;
}
