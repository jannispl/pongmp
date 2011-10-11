class Server;

#ifndef _SERVER_H
#define _SERVER_H

#include "Network.h"
#include "Group.h"

const int MAX_CLIENTS = 2;
const int SERVER_PORT = 45000;

class Server
{
public:
	Server();
	~Server();

	bool initialize();
	void deinitialize();
	void run();

	Network *getNetwork();

	enum eQuitReason
	{
		Timeout,
		Leaving
	};
	void incomingConnection(RakNet::SystemAddress systemAddress);
	void lostConnection(RakNet::SystemAddress systemAddress, eQuitReason quitReason);
	void platformUpdate(RakNet::SystemAddress systemAddress, float fPosition, float fVelocity, char cPropulsionState);

private:
	bool m_bRunning;

	Network *m_pNetwork;
	Group *m_pGroup;
};

#endif
