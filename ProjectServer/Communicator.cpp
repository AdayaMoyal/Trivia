#include "Communicator.h"
#include <exception>
#include <iostream>
#include <string>
#include <numeric>
#include <thread>
#include <vector>
#include "LoginRequestHandler.h"
#include "Helper.h"
#include "RequestHandlerFactory.h"

std::map<SOCKET, IRequestHandler*> Communicator::m_clients;
std::mutex Communicator::CommunicatorMutex;//To add the clients to the map without issues

#define LENGTH_OF_FIRST_MESSAGE 5
#define BYTES_TO_RECV 1024
#define LENGTH_OF_ID 1
#define LENGTH_OF_CONTENT 4
#define CURRENT_TIME 0
#define AFTER_LOGIN_OR_SIGNUP 1

// using static const instead of macros 
static const unsigned short PORT = 8826;
static const unsigned int IFACE = 0;

Communicator::Communicator()
{
	m_serverSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_serverSocket == INVALID_SOCKET)
	{
		throw std::exception("Problem with creating the socket");
	}
}

Communicator::Communicator(IDatabase* db)
{
	m_serverSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_serverSocket == INVALID_SOCKET)
	{
		throw std::exception("Problem with creating the socket");
	}
	this->m_handlerFactory = new RequestHandlerFactory(db);
}

Communicator::~Communicator()
{

}

void Communicator::startHandleRequests()
{
	bindAndListen();
	while (true)
	{
		acceptClients();
	}
}

void Communicator::bindAndListen()
{
	struct sockaddr_in sa = { 0 };
	sa.sin_port = htons(PORT);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = IFACE;
	// again stepping out to the global namespace
	if (::bind(this->m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	if (::listen(this->m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
}

void Communicator::handleNewClient(SOCKET clientSocket)
{
	Helper helper;
	IRequestHandler* handler = new LoginRequestHandler(this->m_handlerFactory);
	RequestInfo request;
	RequestResult result;
	int countRequests = 0;
	bool loggedInOneTime = false;
	char infoFromClient[BYTES_TO_RECV] = { 0 };
	std::cout << "New client" << std::endl;
	while (true)
	{
		try {
			recv(clientSocket, infoFromClient, BYTES_TO_RECV - 1, 0);
			int code = Helper::getMessageCode(infoFromClient);
			if (code == 0)
			{
				return;
			}
			int size = Helper::convert4BytesToInt(infoFromClient);
			std::string data = Helper::getDataFromMessage(infoFromClient);
			request.RequestId = code;
			request.receivalTime = time(CURRENT_TIME);
			request.buffer = Helper::stringToVector(data);
			if (countRequests != 0)
			{
				handler = result.newHandler;
			}
			if(handler == nullptr)
			{
				return;
			}
			result = handler->handleRequest(request);
		}
		catch (std::exception exception)
		{
			//
		}
		try 
		{
			std::string response(result.response.begin(), result.response.end());
			if (response != "")
			{
				CommunicatorMutex.lock();
				helper.sendData(clientSocket, response);
				CommunicatorMutex.unlock();
			}
			countRequests++;
		}
		catch (std::exception exception)
		{
			//
		}
		memset(infoFromClient, 0, BYTES_TO_RECV);
	}
}

void Communicator::acceptClients()
{
	SOCKET client_socket = accept(this->m_serverSocket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);
	LoginRequest* handler = new LoginRequest();
	CommunicatorMutex.lock();
	this->m_clients[client_socket] = (IRequestHandler * )handler;
	CommunicatorMutex.unlock();
	// create new thread for client	and detach from it
	std::thread tr(&Communicator::handleNewClient, this, client_socket);
	tr.detach();
}