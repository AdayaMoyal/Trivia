#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include "IRequestHandler.h"

#define LOGIN_REQUEST 5
#define SIGNUP_REQUEST 7
#define PLAYERS_IN_ROOM 9
#define JOIN_ROOM 10
#define CREATE_ROOM 11
#define HIGH_SCORE 12
#define LOG_OUT 13
#define GET_ROOMS 14
#define GET_STATISTICS 15
#define CLOSEROOM 16
#define STARTGAME 17
#define GETROOMSTATE 18
#define LEAVEROOM 19
#define LEAVEGAME 20
#define GETQUESTION 21
#define SUBMITANSWER 22
#define GETGAMERESULT 23
#define ADDQUESTION 24

class IRequestHandler;
struct RequestInfo
{
	int RequestId;
	time_t receivalTime;
	std::vector<unsigned char> buffer;
};

struct RequestResult
{
	std::vector<unsigned char> response;
	IRequestHandler* newHandler;
};

struct LoginRequest
{
	std::string username;
	std::string password;
};

struct SignupRequest
{
	std::string username;
	std::string password;
	std::string email;
};

struct GetPlayersInRoomRequest
{
	unsigned int roomId;
};

struct JoinRoomRequest
{
	unsigned int roomId;
};

struct CreateRoomRequest
{
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
};

struct SubmitAnswerRequest
{
	unsigned int answerId;
};

struct AddQuestionRequest
{
	std::string question;
	std::string answer1;
	std::string answer2;
	std::string answer3;
	std::string answer4;
	std::string rightAnswer;
};