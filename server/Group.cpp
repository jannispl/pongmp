#include "StdInc.h"
#include "Group.h"

Group::Group()
{
	m_pPlayer[0] = NULL;
	m_pPlayer[1] = NULL;
}

Group::~Group()
{
}

int Group::addPlayer(Player *pPlayer)
{
	if (m_pPlayer[0] == NULL)
	{
		printf("got player in group, slot 0\n");
		m_pPlayer[0] = pPlayer;
		pPlayer->setGroupSlot(0);
		return 0;
	}
	else if (m_pPlayer[1] == NULL)
	{
		printf("got player in group, slot 1\n");
		m_pPlayer[1] = pPlayer;
		pPlayer->setGroupSlot(1);
		return 1;
	}
	return -1;
}

bool Group::removePlayer(Player *pPlayer)
{
	if (m_pPlayer[0] == pPlayer)
	{
		m_pPlayer[0] = NULL;
		return true;
	}
	else if (m_pPlayer[1] == pPlayer)
	{
		m_pPlayer[1] = NULL;
		return true;
	}

	return false;
}

Player *Group::getPlayer(int iSlot)
{
	return m_pPlayer[iSlot];
}

Player *Group::findPlayer(RakNet::SystemAddress systemAddress)
{
	if (m_pPlayer[0]->getSystemAddress() == systemAddress)
	{
		return m_pPlayer[0];
	}
	else if (m_pPlayer[1]->getSystemAddress() == systemAddress)
	{
		return m_pPlayer[1];
	}

	return NULL;
}
