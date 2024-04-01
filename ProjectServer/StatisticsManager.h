#pragma once
#include <iostream>
#include "SqliteDatabase.h"

class StatisticsManager
{
public:
	StatisticsManager();
	StatisticsManager(IDatabase*);
	std::vector<std::string> getHighScore();
	std::vector<std::string> getUserStatistics(std::string);
private:
	IDatabase* m_database;
};