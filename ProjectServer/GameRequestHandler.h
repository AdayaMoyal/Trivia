#pragma once
#include "GameManager.h"
#include "Game.h"
#include "Room.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;
class Game;
class GameManager;

class GameRequestHandler : public IRequestHandler
{
public:
	GameRequestHandler(Game*, LoggedUser, GameManager*, RequestHandlerFactory*);
	GameRequestHandler();
	~GameRequestHandler();
	bool isRequestRelevant(RequestInfo);
	RequestResult handleRequest(RequestInfo);
	RequestResult getQuestion(RequestInfo);
	RequestResult submitAnswer(RequestInfo);
	RequestResult getGameResults(RequestInfo);
	RequestResult leaveGame(RequestInfo);
private:
	Game* m_game;
	LoggedUser m_user;
	GameManager* m_gameManager;
	RequestHandlerFactory* m_handlerFactory;
};