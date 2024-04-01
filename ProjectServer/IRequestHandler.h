#pragma once
#include <iostream>
#include "RequestsStructs.h"
struct RequestInfo;
struct RequestResult;
class IRequestHandler
{
public:
	IRequestHandler();
	~IRequestHandler();
	virtual bool isRequestRelevant(RequestInfo) = 0;
	virtual RequestResult handleRequest(RequestInfo) = 0;
};