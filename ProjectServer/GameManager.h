#pragma once
#include <vector>
#include "IDatabase.h"
#include "Game.h"
#include "Room.h"

class GameManager
{
public:
	GameManager(IDatabase*);
	GameManager();
	~GameManager();
	Game* createGame(Room);
	Game* getGame(int gameId);
	void deleteGame(int gameId);
private:
	IDatabase* m_database;
	std::vector<Game*> m_games;
};