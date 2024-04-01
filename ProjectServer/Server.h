#pragma once
#include "Server.h"
#include "Communicator.h"
#include "IDatabase.h"
#include "RequestHandlerFactory.h"
class Communicator;
class Server
{
public:
	Server();
	Server(IDatabase*);
	Server(IDatabase*, Communicator, RequestHandlerFactory);
	~Server();
	void run();
private:
	Communicator m_communicator;
	IDatabase* m_database;
	RequestHandlerFactory m_handlerFactory;
};