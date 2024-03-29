class Player;

#ifndef _PLAYER_H
#define _PLAYER_H

class Player
{
public:
	Player(RakNet::SystemAddress systemAddress);
	~Player();

	void setGroupSlot(int iSlot);
	int getGroupSlot();

	void sendPlayerIntro(Player *pPlayer, bool bFresh);
	void sendPlayerOutro();
	void sendPlatformUpdate(float fPosition, float fVelocity, char cPropulsionState);

	RakNet::SystemAddress getSystemAddress();

	float m_fLastPlatformUpdate;

private:
	int m_iGroupSlot;
	RakNet::SystemAddress m_systemAddress;

	float m_fPlatformPosition;
};

#endif
