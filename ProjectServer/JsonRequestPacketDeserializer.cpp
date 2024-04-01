#include "JsonRequestPacketDeserializer.h"
#include "Helper.h"
#include<iostream>
#include<string>

JsonRequestPacketDeserializer::JsonRequestPacketDeserializer()
{

}

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<unsigned char> login)
{
	std::string loginStr(login.begin(), login.end());
	json LoginRequestJson = json::parse(loginStr);
	return LoginRequest({ LoginRequestJson["username"], LoginRequestJson["password"] });
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<unsigned char> signUp)
{
	std::string signUpStr(signUp.begin(), signUp.end());
	json SignupRequestJson = json::parse(signUpStr);
	return SignupRequest({ SignupRequestJson["username"], SignupRequestJson["password"], SignupRequestJson["mail"]});
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersRequest(std::vector<unsigned char> playersRequest)
{
	std::string playersRequestStr(playersRequest.begin(), playersRequest.end());
	json playersRequestJson = json::parse(playersRequestStr);
	std::string str = playersRequestJson["roomId"];
	unsigned int id = std::stoi(str);
	return GetPlayersInRoomRequest({ id });
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(std::vector<unsigned char> joinRoom)
{
	std::string joinRoomStr(joinRoom.begin(), joinRoom.end());
	json joinRoomRequestJson = json::parse(joinRoomStr);
	std::string str = joinRoomRequestJson["roomId"];
	unsigned int id = std::stoi(str);
	return JoinRoomRequest({ id });
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(std::vector<unsigned char> createRoom)
{
	std::string createRoomStr(createRoom.begin(), createRoom.end());
	json createRoomRequestJson = json::parse(createRoomStr);
	std::string str = createRoomRequestJson["maxUsers"];
	unsigned int maxUsers = std::stoi(str);
	str = createRoomRequestJson["questionCount"];
	unsigned int questionCount = std::stoi(str);
	str = createRoomRequestJson["answerTimeout"];
	unsigned int answerTimeout = std::stoi(str);
	return CreateRoomRequest({ createRoomRequestJson["roomName"], maxUsers, questionCount ,answerTimeout });
}

SubmitAnswerRequest JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(std::vector<unsigned char> submitAnswer)
{
	std::string submitAnswerStr(submitAnswer.begin(), submitAnswer.end());
	json submitAnswerRequestJson = json::parse(submitAnswerStr);
	std::string str = submitAnswerRequestJson["answerId"];
	unsigned int answerId = std::stoi(str);
	return SubmitAnswerRequest({ answerId });
}

AddQuestionRequest JsonRequestPacketDeserializer::deserializeAddQuestionRequest(std::vector<unsigned char> addQuestion)
{
	std::string addQuestionStr(addQuestion.begin(), addQuestion.end());
	json addQuestionRequestJson = json::parse(addQuestionStr);
	return AddQuestionRequest({ addQuestionRequestJson["question"], addQuestionRequestJson["answer1"], addQuestionRequestJson["answer2"], addQuestionRequestJson["answer3"], addQuestionRequestJson["answer4"], addQuestionRequestJson["rightAnswer"] });
}
