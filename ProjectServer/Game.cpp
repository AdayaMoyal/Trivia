#include "Game.h"
#include <iostream>
#include <ctime>
#include <windows.h>

#define FIRST_QUESTION 0

Game::Game(IDatabase* db, int gameId, std::vector<Question> questions, std::map<LoggedUser, GameData> players)
{
	this->m_db = db;
	this->m_gameId = gameId;
	this->m_questions = questions;
	this->m_players = players;
	this->m_updated = false;
}

Game::Game()
{
	this->m_db = nullptr;
	this->m_gameId = 1;
}

Game::~Game()
{

}

Question* Game::getQuestionForUser(LoggedUser user)
{
	getNextQuestion(user);
	time(&this->m_startTime);
	return &this->m_players[user].currentQuestion;
}

int Game::submitAnswer(LoggedUser user, int answerId)
{
	time(&this->m_endTime);
	this->m_players[user].questionNum++;
	if (this->m_players[user].currentQuestion.getCorrectAnswerId() == answerId)
	{
		this->m_players[user].correctAnswerCount++;
	}
	else
	{
		this->m_players[user].wrongAnswerCount++;
	}
	this->m_players[user].averangeAnswerTime += difftime(this->m_endTime, this->m_startTime);
	if (this->m_players[user].questionNum == this->m_questions.size())
	{
		this->m_players[user].averangeAnswerTime = this->m_players[user].averangeAnswerTime / this->m_questions.size();
	}
	int correct = this->m_players[user].currentQuestion.getCorrectAnswerId();
	return correct;
}

bool Game::getNextQuestion(LoggedUser user)
{
	int count = 1;
	int num = 0;
	bool next = false;
	auto firstQuestion = this->m_questions;
	if (this->m_players[user].questionNum == FIRST_QUESTION)
	{
		this->m_players[user].currentQuestion = firstQuestion.front();
		this->m_players[user].correctAnswerCount = 0;
		this->m_players[user].wrongAnswerCount = 0;
		this->m_players[user].averangeAnswerTime = 0;
		return next;
	}
	if (this->m_players[user].questionNum <= this->m_questions.size())
	{
		for (auto it = this->m_questions.begin(); it != this->m_questions.end(); it++)
		{
			num = this->m_players[user].questionNum;
			if (count == num +1)
			{
				this->m_players[user].currentQuestion = *it;
				break;
			}
			count++;
		}
	}
	return next;
}

void Game::removePlayer(LoggedUser user)
{
	int answered = this->m_players[user].questionNum;
	for (int i = answered; i < this->m_questions.size(); i++)
	{
		this->m_players[user].wrongAnswerCount++;
		this->m_players[user].questionNum++;
	}
}

int Game::getGameId()
{
	return this->m_gameId;
}

std::vector<PlayerResults> Game::getPlayersResults()
{
	std::vector<PlayerResults> results;
	bool everyoneFinishedGame = true;
	unsigned int max = 0;
	std::string username = "";
	for (auto it = this->m_players.begin(); it != this->m_players.end(); it++)
	{
		if (it->second.questionNum < this->m_questions.size())
		{
			everyoneFinishedGame = false;
		}
	}
	if (everyoneFinishedGame == true)
	{
		Sleep(300);
		for (auto it = this->m_players.begin(); it != this->m_players.end(); it++)
		{
			if (max < it->second.correctAnswerCount)
			{
				max = it->second.correctAnswerCount;
				username = it->first.getUsername();
			}
		}
		for (auto it = this->m_players.begin(); it != this->m_players.end(); it++)
		{
			PlayerResults result;
			result.username = it->first.getUsername();
			result.correctAnswerCount = it->second.correctAnswerCount;
			result.wrongAnswerCount = it->second.wrongAnswerCount;
			result.averageAnswerTime = it->second.averangeAnswerTime;
			if (username == result.username)
			{
				results.insert(results.begin(), result);
			}
			else
			{
				results.push_back(result);
			}
			if (!this->m_updated)
			{
				UpdateStatistics(result.username, result.correctAnswerCount, (result.correctAnswerCount + result.wrongAnswerCount), result.averageAnswerTime);
			}
		}
		this->m_updated = true;
	}
	return results;
}

void Game::UpdateStatistics(std::string username, int correctAnswers, int totalAnswers, float averageTime)
{
	this->m_db->updatePlayer(username, correctAnswers, totalAnswers, averageTime);
}
