#include "Question.h"

Question::Question(std::string question, std::vector<std::string> possibleAnswers, std::string correctAnswerId)
{
	this->m_question = question;
	this->m_possibleAnswers = possibleAnswers;
	this->m_correctAnswer = correctAnswerId;
}

Question::Question()
{
	this->m_question = "";
	this->m_possibleAnswers;
	this->m_correctAnswer = "";
}

Question::~Question()
{

}

std::string Question::getQuestion()
{
	return this->m_question;
}

std::vector<std::string> Question::getPossibleAnswers()
{
	return this->m_possibleAnswers;
}

int Question::getCorrectAnswerId()
{
	int count = 0;
	for (auto it = this->m_possibleAnswers.begin(); it != this->m_possibleAnswers.end(); it++)
	{
		if (this->m_correctAnswer.compare(*it) == 0)
		{
			return count+1;
		}
		count++;
	}
	return 0;
}
