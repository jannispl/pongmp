#include "StdInc.h"
#include "Server.h"
#include "Player.h"

Server::Server()
	: m_bRunning(false)
{
	m_pNetwork = new Network();
	m_pGroup = new Group();
}

Server::~Server()
{
	delete m_pNetwork;
	delete m_pGroup;
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

Network *Server::getNetwork()
{
	return m_pNetwork;
}

void Server::incomingConnection(RakNet::SystemAddress systemAddress)
{
	Player *pPlayer = new Player(systemAddress);

	int iSlot = m_pGroup->addPlayer(pPlayer);

	Player *pRemote = m_pGroup->getPlayer(iSlot ^ 1);
	if (pRemote != NULL)
	{
		pRemote->sendPlayerIntro(pPlayer, true);
		pPlayer->sendPlayerIntro(pRemote, false);
	}
}

void Server::lostConnection(RakNet::SystemAddress systemAddress, Server::eQuitReason quitReason)
{
	Player *pPlayer = m_pGroup->findPlayer(systemAddress);

	Player *pRemote = m_pGroup->getPlayer(pPlayer->getGroupSlot() ^ 1);
	if (pRemote != NULL)
	{
		pRemote->sendPlayerOutro();
	}

	m_pGroup->removePlayer(pPlayer);
}

void Server::platformUpdate(RakNet::SystemAddress systemAddress, float fPosition, float fVelocity, char cPropulsionState)
{
	Player *pPlayer = m_pGroup->findPlayer(systemAddress);

	Player *pRemote = m_pGroup->getPlayer(pPlayer->getGroupSlot() ^ 1);
	if (pRemote != NULL)
	{
		if (Shared::getCurrentTime() - pRemote->m_fLastPlatformUpdate >= 0.08f)
		{
			pRemote->m_fLastPlatformUpdate = Shared::getCurrentTime();
			pRemote->sendPlatformUpdate(fPosition, fVelocity, cPropulsionState);
		}
	}
}
