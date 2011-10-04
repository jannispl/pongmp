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

private:
	RakNet::RakPeerInterface *m_pPeer;
};

#endif
