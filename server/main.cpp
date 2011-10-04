#include "StdInc.h"
#include <RakPeerInterface.h>
#include <BitStream.h>
#include "../shared/Packets.h"

#define MAX_CLIENTS 2
#define SERVER_PORT 45000

Server *g_pServer = NULL;

int main(int argc, char *argv[])
{
	Shared::initialize();

	g_pServer = new Server();

	if (!g_pServer->initialize())
	{
		printf("Failed to initialize server\n");
		return 1;
	}

	g_pServer->run();

	g_pServer->deinitialize();

	delete g_pServer;

	return 0;
}
