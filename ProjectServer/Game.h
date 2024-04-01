#pragma once
#include <map>
#include <vector>
#include <iostream>
#include "Question.h"
#include "LoggedUser.h"
#include "ResponsesStructs.h"
#include "StatisticsManager.h"

struct GameData
{
	unsigned int questionNum;
	Question currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	float averangeAnswerTime;
};

class LoggedUser;
class Question;

class Game
{
public:
	Game();
	Game(IDatabase*, int, std::vector<Question>, std::map<LoggedUser, GameData>);
	~Game();
	Question* getQuestionForUser(LoggedUser);
	int submitAnswer(LoggedUser, int);
	void removePlayer(LoggedUser);
	int getGameId();
	bool getNextQuestion(LoggedUser);
	std::vector<PlayerResults> getPlayersResults();
	void UpdateStatistics(std::string, int, int, float);
private:
	IDatabase* m_db;
	std::vector<Question> m_questions;
	std::map<LoggedUser, GameData> m_players;
	int m_gameId;
	time_t m_startTime;
	time_t m_endTime;
	bool m_updated;
};