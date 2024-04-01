#include "Server.h"
#include "Communicator.h"

Server::Server()
{
	this->m_communicator = Communicator();
}

Server::Server(IDatabase* db)
{
	this->m_database = db;
	this->m_communicator = Communicator(db);
}

Server::Server(IDatabase* db, Communicator communicator, RequestHandlerFactory factory)
{
	this->m_database = db;
	this->m_communicator = communicator;
	this->m_handlerFactory = factory;
}

Server::~Server()
{

}

void Server::run()
{
	this->m_communicator.startHandleRequests();
}