class Network;

#ifndef _NETWORK_H
#define _NETWORK_H

#include "../shared/Packets.h"
#include <RakPeerInterface.h>

class Network
{
public:
	Network();
	~Network();

	bool initialize();
	void deinitialize();

	void process();

	void updatePlatform(float fPosition, float fVelocity, Platform::PropulsionState propulsion);
private:
	float m_fLastPlatformPacket;
	
	float m_fCurrentPos;

	RakNet::RakPeerInterface *m_pPeer;
};

#endif
