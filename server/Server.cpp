#include "StdInc.h"
#include "Server.h"

Server::Server()
	: m_bRunning(false)
{
	m_pNetwork = new Network();
}

Server::~Server()
{
	delete m_pNetwork;
}

bool Server::initialize()
{
	if (!m_pNetwork->initialize())
	{
		return false;
	}

	return true;
}

void Server::deinitialize()
{
	m_pNetwork->deinitialize();
}

void Server::run()
{
	m_bRunning = true;
	do
	{
		m_pNetwork->process();

		Shared::sleep(5);
	}
	while (m_bRunning);
}
