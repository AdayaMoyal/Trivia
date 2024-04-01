#pragma once
#include <iostream>
#include "IRequestHandler.h"
#include <map>
#include "WSAInitializer.h"
#include "RequestHandlerFactory.h"

class Communicator
{
public:
	Communicator();
	Communicator(IDatabase*);
	~Communicator();
	void startHandleRequests();
	void acceptClients();
private:
	SOCKET m_serverSocket;
	static std::map<SOCKET, IRequestHandler*> m_clients;
	static std::mutex CommunicatorMutex;
	RequestHandlerFactory* m_handlerFactory;
	void bindAndListen();
	void handleNewClient(SOCKET);
};