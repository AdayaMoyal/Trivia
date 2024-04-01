#include "StatisticsManager.h"

StatisticsManager::StatisticsManager()
{
    this->m_database = nullptr;
}

StatisticsManager::StatisticsManager(IDatabase* db)
{
    this->m_database = db;
}

std::vector<std::string> StatisticsManager::getHighScore()
{
    return this->m_database->getHighScores();
}

std::vector<std::string> StatisticsManager::getUserStatistics(std::string username)
{
    std::vector<std::string>* userStatistics = new std::vector<std::string>();
    float AverageAnswerTime = (this->m_database->getPlayerAverageAnswerTime(username));
    int NumOfCorrectAnswers = (this->m_database->getNumOfCorrectAnswers(username));
    int NumOfTotalAnswers = (this->m_database->getNumOfTotalAnswers(username));
    int NumOfPlayerGames = (this->m_database->getNumOfPlayerGames(username));
    userStatistics->push_back(std::to_string(AverageAnswerTime));
    userStatistics->push_back(std::to_string(NumOfCorrectAnswers));
    userStatistics->push_back(std::to_string(NumOfTotalAnswers));
    userStatistics->push_back(std::to_string(NumOfPlayerGames));
    return *userStatistics;
}