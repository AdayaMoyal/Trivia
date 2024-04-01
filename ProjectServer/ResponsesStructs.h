#pragma once
#include <iostream>
#include <map>
#include <vector>
#include "Room.h"

#define ERROR_RESPONSE 404
#define LOGIN_RESPONSE 100
#define SIGNUP_RESPONSE 101
#define LOGOUT_RESPONSE 102
#define JOINROOM_RESPONSE 501
#define CREATEROOM_RESPONSE 502
#define GETROOMS_RESPONSE 503
#define GET_PLAYERS_IN_ROOM_RESPONSE 504
#define HIGH_SCORE_RESPONSE 505
#define USER_STATISTICS 506
#define CLOSEROOM_RESPONSE 507
#define STARTGAME_RESPONSE 508
#define GETROOMSTATE_RESPONSE 509
#define LEAVEROOM_RESPONSE 510
#define LEAVEGAME_RESPONSE 511
#define GETQUESTION_RESPONSE 512
#define SUBMITANSWER_RESPONSE 513
#define GETGAMERESULTS_RESPONSE 514
#define ADDQUESTION_RESPONSE 515

struct PlayerResults
{
	std::string username;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	float averageAnswerTime;
};

struct ErrorResponse
{
	std::string message;
};

struct LoginResponse
{
	unsigned int status;
};

struct SignupResponse
{
	unsigned int status;
};

struct LogoutResponse
{
	unsigned int status;
};

struct GetRoomsResponse
{
	unsigned int status;
	std::vector<RoomData> rooms;
};

struct GetPlayersInRoomResponse
{
	std::vector<std::string> players;
};

struct GetHighScoreResponse
{
	unsigned int status;
	std::vector<std::string> statistics;
};

struct GetPersonalStatsResponse
{
	unsigned int status;
	std::vector<std::string> statistics;
};

struct JoinRoomResponse
{
	unsigned int status;
};

struct CreateRoomResponse
{
	unsigned int status;
	unsigned int roomId;
};

struct CloseRoomResponse
{
	unsigned int status;
};

struct StartGameResponse
{
	unsigned int status;
};

struct GetRoomStateResponse
{
	unsigned int status;
	bool hasGameBegun;
	std::vector<std::string> players;
	unsigned int questionCount;
	float answerTimeout;
};

struct LeaveRoomResponse
{
	unsigned int status;
};

struct LeaveGameResponse
{
	unsigned int status;
};

struct GetQuestionResponse
{
	unsigned int status;
	std::string question;
	std::map<unsigned int, std::string> answers;
};

struct SubmitAnswerResponse
{
	unsigned int status;
	unsigned int correctAnswerId;
};

struct GetGameResultsResponse
{
	unsigned int status;
	std::vector<PlayerResults> results;
};

struct AddQuestionResponse
{
	unsigned int status;
};