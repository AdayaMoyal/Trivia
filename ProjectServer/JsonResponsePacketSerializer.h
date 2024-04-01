#pragma once
#include <vector>
#include "ResponsesStructs.h"
#include <fstream>
#include <iostream>
#include "json.hpp"
using json = nlohmann::json;

class JsonResponsePacketSerializer
{
public:
	JsonResponsePacketSerializer();
	static std::vector<unsigned char> serializeResponse(ErrorResponse);
	static std::vector<unsigned char> serializeResponse(LoginResponse);
	static std::vector<unsigned char> serializeResponse(SignupResponse);
	static std::vector<unsigned char> serializeResponse(LogoutResponse);
	static std::vector<unsigned char> serializeResponse(GetRoomsResponse);
	static std::vector<unsigned char> serializeResponse(GetPlayersInRoomResponse);
	static std::vector<unsigned char> serializeResponse(JoinRoomResponse);
	static std::vector<unsigned char> serializeResponse(CreateRoomResponse);
	static std::vector<unsigned char> serializeResponse(GetHighScoreResponse);
	static std::vector<unsigned char> serializeResponse(GetPersonalStatsResponse);
	static std::vector<unsigned char> serializeResponse(CloseRoomResponse);
	static std::vector<unsigned char> serializeResponse(StartGameResponse);
	static std::vector<unsigned char> serializeResponse(GetRoomStateResponse);
	static std::vector<unsigned char> serializeResponse(LeaveRoomResponse);
	static std::vector<unsigned char> serializeResponse(GetGameResultsResponse);
	static std::vector<unsigned char> serializeResponse(SubmitAnswerResponse);
	static std::vector<unsigned char> serializeResponse(GetQuestionResponse);
	static std::vector<unsigned char> serializeResponse(LeaveGameResponse);
	static std::vector<unsigned char> serializeResponse(AddQuestionResponse);

	static std::vector<unsigned char> createVector(int messageCode, std::string responseInfo);

};
