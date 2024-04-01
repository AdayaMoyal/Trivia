#include "JsonResponsePacketSerializer.h"
#include <iostream>

JsonResponsePacketSerializer::JsonResponsePacketSerializer()
{
	
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse error)
{
	json errorJson = { {"message" , error.message} };
	return createVector(ERROR_RESPONSE, errorJson.dump());
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LoginResponse login)
{
	json loginJson = { {"status" , login.status} };
	return createVector(LOGIN_RESPONSE, loginJson.dump());
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(SignupResponse signUp)
{
	json signUpJson = { {"status" , signUp.status} };
	return createVector(SIGNUP_RESPONSE, signUpJson.dump());
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LogoutResponse logout)
{
	json logoutJson = { {"status",logout.status}};
	return createVector(LOGOUT_RESPONSE, logoutJson.dump());
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse getRooms)
{
	std::vector<std::string> roomsVector;
	std::string data = "";
	for (auto it = getRooms.rooms.begin(); it != getRooms.rooms.end(); it++)
	{
		data += std::to_string(it->id) + "," + it->name + "," + std::to_string(it->maxPlayers) + "," + std::to_string(it->numOfQuestionsInGame) + "," + std::to_string(it->timePerQuestion) + "," + std::to_string(it->isActive);
		roomsVector.push_back(data);
		data = "";
	}
	json getRoomJson = { {"status", getRooms.status}, {"Rooms", roomsVector} };
	return createVector(GETROOMS_RESPONSE, getRoomJson.dump());
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse getPlayersInRoom)
{
	std::string players = "";
	for (int i = 0; i < getPlayersInRoom.players.size(); i++)
	{
		players += getPlayersInRoom.players[i] + ", ";
	}
	json getPlayersInRoomJson = { {"PlayersInRoom", players} };
	return createVector(GET_PLAYERS_IN_ROOM_RESPONSE, getPlayersInRoomJson.dump());
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse joinRoom)
{
	json joinRoomJson = { {"status",joinRoom.status} };
	return createVector(JOINROOM_RESPONSE, joinRoomJson.dump());
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse createRoom)
{
	json createRoomJson = { {"status",createRoom.status} ,{"roomId", createRoom.roomId}};
	return createVector(CREATEROOM_RESPONSE, createRoomJson.dump());
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetHighScoreResponse getHighScore)
{
	json getHighScoreJson = { {"status", getHighScore.status} , {"statistics", getHighScore.statistics}};
	return createVector(HIGH_SCORE_RESPONSE, getHighScoreJson.dump());
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetPersonalStatsResponse getPersonalStats)
{
	std::vector<std::string>* personalStats = new std::vector<std::string>();
	for (auto it = getPersonalStats.statistics.begin(); it != getPersonalStats.statistics.end(); it++)
	{
		personalStats->push_back(*it);
	}
	json getPersonalStatsJson;
	getPersonalStatsJson["status"] = USER_STATISTICS;
	getPersonalStatsJson["UserStatistics"] = *personalStats;
	return createVector(USER_STATISTICS, getPersonalStatsJson.dump());
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(CloseRoomResponse closeRoom)
{
	json closeRoomJson = { {"status",closeRoom.status} };
	return createVector(CLOSEROOM_RESPONSE, closeRoomJson.dump());
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(StartGameResponse startGame)
{
	json startGameJson = { {"status",startGame.status} };
	return createVector(STARTGAME_RESPONSE, startGameJson.dump());
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse leaveRoom)
{
	json leaveRoomJson = { {"status",leaveRoom.status} };
	return createVector(LEAVEROOM_RESPONSE, leaveRoomJson.dump());
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetRoomStateResponse getRoomState)
{
	json getRoomStateJson = { {"status", getRoomState.status}, {"hasGameBegun", getRoomState.hasGameBegun},{"players", getRoomState.players},{"questionCount", getRoomState.questionCount},{"answerTimeout", getRoomState.answerTimeout}};
	return createVector(GETROOMSTATE_RESPONSE, getRoomStateJson.dump());
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetGameResultsResponse getGameResults)
{
	std::string info = "";
	std::vector<std::string>* vec = new std::vector<std::string>();
	for (auto it = getGameResults.results.begin(); it != getGameResults.results.end(); it++)
	{
		info += it->username + "," + std::to_string(it->correctAnswerCount) + "," + std::to_string(it->wrongAnswerCount) + "," + std::to_string(it->averageAnswerTime);
		vec->push_back(info);
		info = "";
	}
	json getGameResultsJson;
	getGameResultsJson["status"] = getGameResults.status;
	getGameResultsJson["results"] = *vec;
	return createVector(GETGAMERESULTS_RESPONSE, getGameResultsJson.dump());
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(SubmitAnswerResponse submitAnswer)
{
	json submitAnswerJson = { {"status",submitAnswer.status}, {"correctAnswerId", submitAnswer.correctAnswerId}};
	return createVector(SUBMITANSWER_RESPONSE, submitAnswerJson.dump());
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetQuestionResponse getQuestion)
{
	std::string question = "";
	std::string answers = "";
	for (auto it = getQuestion.answers.begin(); it != getQuestion.answers.end(); it++)
	{
		answers += it->second + ",";
	}
	json getQuestionJson = { {"status", getQuestion.status} ,{"question", getQuestion.question}, {"answers", answers}};
	return createVector(GETQUESTION_RESPONSE, getQuestionJson.dump());
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LeaveGameResponse leaveGame)
{
	json leaveGameJson = { {"status",leaveGame.status} };
	return createVector(LEAVEGAME_RESPONSE, leaveGameJson.dump());
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(AddQuestionResponse addQuestion)
{
	json addQuestionJson = { {"status", addQuestion.status} };
	return createVector(ADDQUESTION_RESPONSE, addQuestionJson.dump());
}

std::vector<unsigned char> JsonResponsePacketSerializer::createVector(int messageCode, std::string responseInfo)
{
	std::vector<unsigned char> infoVector;
	infoVector.push_back((unsigned char)messageCode);
	int infoSize = responseInfo.size();
	unsigned char bytes[4];
	bytes[0] = (infoSize >> 24) & 0xFF;
	bytes[1] = (infoSize >> 16) & 0xFF;
	bytes[2] = (infoSize >> 8) & 0xFF;
	bytes[3] = infoSize & 0xFF;
	for (int i = 0; i < 4; i++)
	{
		infoVector.push_back(bytes[i]);
	}
	std::copy(responseInfo.begin(), responseInfo.end(), std::back_inserter(infoVector));
	return infoVector;
}
