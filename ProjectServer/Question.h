#pragma once
#include <iostream>
#include <vector>

class Question
{
public:
	Question(std::string, std::vector<std::string>, std::string);
	Question();
	~Question();
	std::string getQuestion();
	std::vector<std::string> getPossibleAnswers();
	int getCorrectAnswerId();
private:
	std::string m_question;
	std::vector<std::string> m_possibleAnswers;
	std::string m_correctAnswer;
};