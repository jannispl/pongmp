class Network;

#ifndef _NETWORK_H
#define _NETWORK_H

#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>

class Network
{
public:
	Network();
	~Network();

	bool initialize();
	void deinitialize();

	void process();

	float getCurrentTime();

	void updatePlatform(float fPosition, float fVelocity, Platform::PropulsionState propulsion);
	void updateInput(bool bUp, bool bDown);

private:
	enum GamePackets
	{
		ID_TEST = ID_USER_PACKET_ENUM + 1,
		ID_PLATFORM,

		ID_INIT,
		ID_INPUT,
		ID_CLIENTUPDATE
	};

	DWORD64 m_qwInitTime;
	float m_fLastPlatformPacket;
	
	float m_fCurrentPos;

	RakNet::RakPeerInterface *m_pPeer;
};

#endif
