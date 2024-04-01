#include "GameManager.h"

GameManager::GameManager(IDatabase* db)
{
	this->m_database = db;
	this->m_games = std::vector<Game*>();
}

GameManager::GameManager()
{
	this->m_database = nullptr;
}

GameManager::~GameManager()
{

}

Game* GameManager::createGame(Room room)
{
	int count = 1;
	std::map<LoggedUser, GameData> players;
	std::vector<Question> questions = this->m_database->getQuestions(room.getRoomData().numOfQuestionsInGame);
	std::vector<std::string> users = room.getAllUsers();
	for (auto it = users.begin(); it != users.end(); it++)
	{
		LoggedUser user(*it);
		GameData data;
		data.questionNum = 0;
		players[user] = data;
	}
	Game* game = new Game(this->m_database, room.getRoomData().id, questions ,players);
	this->m_games.push_back(game);
	return game;
}

Game* GameManager::getGame(int gameId)
{
	for (auto it = this->m_games.begin(); it != this->m_games.end(); it++)
	{
		Game* game = *it;
		if (game->getGameId() == gameId)
		{
			return *it;
		}
	}
	return new Game();
}

void GameManager::deleteGame(int gameId)
{
	for (auto it = this->m_games.begin(); it != this->m_games.end(); it++)
	{
		Game* game = *it;
		if (game->getGameId() == gameId)
		{
			this->m_games.erase(it);
			break;
		}
	}
}
