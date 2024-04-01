#pragma once
#include <vector>
#include "RequestsStructs.h"
#include <fstream>
#include <iostream>
#include "json.hpp"
using json = nlohmann::json;

class JsonRequestPacketDeserializer
{
public:
	JsonRequestPacketDeserializer();
	static LoginRequest deserializeLoginRequest(std::vector<unsigned char>);
	static SignupRequest deserializeSignupRequest(std::vector<unsigned char>);
	static GetPlayersInRoomRequest deserializeGetPlayersRequest(std::vector<unsigned char>);
	static JoinRoomRequest deserializeJoinRoomRequest(std::vector<unsigned char>);
	static CreateRoomRequest deserializeCreateRoomRequest(std::vector<unsigned char>);
	static SubmitAnswerRequest deserializeSubmitAnswerRequest(std::vector<unsigned char>);
	static AddQuestionRequest deserializeAddQuestionRequest(std::vector<unsigned char>);

};