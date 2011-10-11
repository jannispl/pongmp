class Group;

#ifndef _GROUP_H
#define _GROUP_H

#include "Player.h"

class Group
{
public:
	Group();
	~Group();

	int addPlayer(Player *pPlayer);
	bool removePlayer(Player *pPlayer);
	Player *getPlayer(int iSlot);
	Player *findPlayer(RakNet::SystemAddress systemAddress);

private:
	Player *m_pPlayer[2];
};

#endif
