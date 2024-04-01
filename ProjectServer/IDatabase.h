#pragma once
#include <string>
#include <iostream>
#include <list>
#include <vector>
#include "Question.h"
#include "RequestsStructs.h"

class IDatabase
{
public:
	IDatabase();
	~IDatabase();
	virtual bool open() = 0;
	virtual bool close() = 0;
	virtual bool doesUserExist(std::string) = 0;
	virtual bool doesPasswordMatch(std::string, std::string) = 0;
	virtual void addNewUser(std::string, std::string, std::string) = 0;
	virtual float getPlayerAverageAnswerTime(std::string) = 0;
	virtual int getNumOfCorrectAnswers(std::string) = 0;
	virtual int getNumOfTotalAnswers(std::string) = 0;
	virtual int getNumOfPlayerGames(std::string) = 0;
	virtual float getPlayerScore(std::string) = 0;
	virtual std::vector<std::string> getHighScores() = 0;
	virtual std::vector<Question> getQuestions(int) = 0;
	virtual void updatePlayer(std::string, int, int, float) = 0;
	virtual void updatePlayersTotalTime(std::string, float) = 0;
	virtual void updatePlayersTotalAnswers(std::string, int) = 0;
	virtual void updateNumOfCorrectAnswers(std::string, int) = 0;
	virtual std::string getMaxScoreName(std::list<std::string> list) = 0;
	virtual void updatePlayersGame(std::string) = 0;
	virtual void addNewKey(std::string key, int id_key)=0;
	virtual void addQuestion(AddQuestionRequest request) = 0;
};