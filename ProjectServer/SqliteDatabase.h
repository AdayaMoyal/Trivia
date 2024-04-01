#pragma once
#include <iostream>
#include "IDatabase.h"
#include "sqlite3.h"
#include "io.h"
#include "RequestsStructs.h"


class SqliteDatabase :public IDatabase
{
public:
	SqliteDatabase();
	~SqliteDatabase();
	bool open();
	bool close();
	void insertQuestion();
	void runQuery(std::string);
	bool doesUserExist(std::string);
	bool doesPasswordMatch(std::string, std::string);
	void addNewUser(std::string, std::string, std::string);
	float getPlayerAverageAnswerTime(std::string);
	void updatePlayer(std::string, int, int, float);
	void updatePlayersTotalTime(std::string, float);
	void updatePlayersGame(std::string);
	void updatePlayersTotalAnswers(std::string, int);
	int getNumOfCorrectAnswers(std::string);
	void updateNumOfCorrectAnswers(std::string,int);
	int getNumOfTotalAnswers(std::string);
	int getNumOfPlayerGames(std::string);
	float getPlayerScore(std::string);
	std::vector<std::string> getHighScores();
	std::string getMaxScore(std::list<std::string>);
	std::string getMaxScoreName(std::list<std::string> list);
	std::vector<Question> getQuestions(int);
	void addNewKey(std::string key, int id_key);
	void addQuestion(AddQuestionRequest request);
private:
	sqlite3* _db;
};