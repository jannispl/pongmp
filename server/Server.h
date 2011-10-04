class Server;

#ifndef _SERVER_H
#define _SERVER_H

#include "Network.h"

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

private:
	bool m_bRunning;

	Network *m_pNetwork;
};

#endif
