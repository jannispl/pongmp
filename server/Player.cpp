#include "StdInc.h"
#include "Player.h"
#include "../shared/Packets.h"
#include <BitStream.h>

Player::Player(RakNet::SystemAddress systemAddress)
	: m_systemAddress(systemAddress)
{
}

Player::~Player()
{
}

void Player::setGroupSlot(int iSlot)
{
	m_iGroupSlot = iSlot;
}

int Player::getGroupSlot()
{
	return m_iGroupSlot;
}

void Player::sendPlatformUpdate(float fPosition, float fVelocity, char cPropulsionState)
{
	RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID)ID_PLATFORM);
	bsOut.Write(Shared::getCurrentTime());
	bsOut.Write(fPosition);
	bsOut.Write(fVelocity);
	bsOut.Write(cPropulsionState);
	g_pServer->getNetwork()->send(&bsOut, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, m_systemAddress, false);
}

RakNet::SystemAddress Player::getSystemAddress()
{
	return m_systemAddress;
}
