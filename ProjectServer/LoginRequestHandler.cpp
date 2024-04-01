#include "IRequestHandler.h"
#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "ResponsesStructs.h"
#include "JsonResponsePacketSerializer.h"
#include "MenuRequestHandler.h"

LoginRequestHandler::LoginRequestHandler() : IRequestHandler()
{

}

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory* handler) : IRequestHandler()
{
	this->m_handlerFactory = handler;
}

LoginRequestHandler::~LoginRequestHandler()
{

}

bool LoginRequestHandler::isRequestRelevant(RequestInfo request)
{
	if (request.RequestId == LOGIN_REQUEST || request.RequestId == SIGNUP_REQUEST)
	{
		return true;
	}
	return false;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo request)
{
	RequestResult result;
	ErrorResponse errorRes;
	if (isRequestRelevant(request) == true)
	{
		switch (request.RequestId)
		{
		case LOGIN_REQUEST:
			result = login(request);
			break;
		case SIGNUP_REQUEST:
			result = signup(request);
			break;
		}
	}
	else
	{//if the request is not possible / don't exist
		errorRes.message = std::to_string(ERROR_RESPONSE);
		result.response = JsonResponsePacketSerializer::serializeResponse(errorRes);
		result.newHandler = nullptr;
	}
	return result;
}

RequestResult LoginRequestHandler::login(RequestInfo request)
{
	LoginRequest login;
	LoginResponse loginRes;
	ErrorResponse errorRes;
	RequestResult result;
	bool userExist = false;
	LoginManager manager = this->m_handlerFactory->getLoginManager();
	login = JsonRequestPacketDeserializer::deserializeLoginRequest(request.buffer);
	userExist = manager.login(login.username, login.password);
	if (userExist == false)
	{
		errorRes.message = std::to_string(ERROR_RESPONSE);
		result.response = JsonResponsePacketSerializer::serializeResponse(errorRes);
		result.newHandler = (IRequestHandler*)this->m_handlerFactory->createLoginRequestHandler();
	}
	else
	{
		loginRes.status = LOGIN_RESPONSE;
		result.response = JsonResponsePacketSerializer::serializeResponse(loginRes);
		LoggedUser user(login.username);
		result.newHandler = (IRequestHandler*)this->m_handlerFactory->createMenuRequestHandler(user);
	}
	return result;
}

RequestResult LoginRequestHandler::signup(RequestInfo request)
{
	bool userExist = true;
	ErrorResponse errorRes;
	SignupRequest signUp;
	SignupResponse signupRes;
	RequestResult result;
	LoginManager manager = this->m_handlerFactory->getLoginManager();
	signUp = JsonRequestPacketDeserializer::deserializeSignupRequest(request.buffer);
	userExist = manager.signup(signUp.username, signUp.password, signUp.email);
	if (userExist == false)
	{
		errorRes.message = std::to_string(ERROR_RESPONSE);
		result.response = JsonResponsePacketSerializer::serializeResponse(errorRes);
		result.newHandler = (IRequestHandler*)this->m_handlerFactory->createLoginRequestHandler();
	}
	else
	{
		signupRes.status = SIGNUP_RESPONSE;
		result.response = JsonResponsePacketSerializer::serializeResponse(signupRes);
		LoggedUser user(signUp.username);
		result.newHandler = (IRequestHandler*)this->m_handlerFactory->createMenuRequestHandler(user);
	}
	return result;
}
