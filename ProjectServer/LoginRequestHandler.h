#pragma once
#include "IRequestHandler.h"
#include "RequestsStructs.h"
#include "RequestHandlerFactory.h"
class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler();
	LoginRequestHandler(RequestHandlerFactory*);
	~LoginRequestHandler();
	virtual bool isRequestRelevant(RequestInfo);
	virtual RequestResult handleRequest(RequestInfo);
	RequestResult login(RequestInfo);
	RequestResult signup(RequestInfo);
private:
	RequestHandlerFactory* m_handlerFactory;
};