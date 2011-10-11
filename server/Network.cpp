#include "StdInc.h"
#include "Network.h"
#include "../shared/Packets.h"
#include <BitStream.h>

Network::Network()
{
}

Network::~Network()
{
}

bool Network::initialize()
{
	m_pPeer = RakNet::RakPeerInterface::GetInstance();
	if (!m_pPeer)
	{
		return false;
	}

	m_pPeer->Startup(MAX_CLIENTS, &RakNet::SocketDescriptor(SERVER_PORT, 0), 1);
	m_pPeer->SetMaximumIncomingConnections(MAX_CLIENTS);

	return true;
}

void Network::deinitialize()
{
	RakNet::RakPeerInterface::DestroyInstance(m_pPeer);
}

void Network::process()
{
	for (RakNet::Packet *pPacket = m_pPeer->Receive(); pPacket != NULL; m_pPeer->DeallocatePacket(pPacket), pPacket = m_pPeer->Receive())
	{
		switch (pPacket->data[0])
		{
		case ID_NEW_INCOMING_CONNECTION:
			//printf("A connection is incoming.\n");
			g_pServer->incomingConnection(pPacket->systemAddress);
			break;
		case ID_DISCONNECTION_NOTIFICATION:
			//printf("A client has disconnected.\n");
			g_pServer->lostConnection(pPacket->systemAddress, Server::Leaving);
			break;
		case ID_CONNECTION_LOST:
			//printf("A client lost the connection.\n");
			g_pServer->lostConnection(pPacket->systemAddress, Server::Timeout);
			break;

		case ID_PLATFORM:
			{
				RakNet::BitStream bsIn(pPacket->data, pPacket->length, false);
				bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
				
				float fPos, fVelocity;
				char cPropulsionState;
				bsIn.Read(fPos);
				bsIn.Read(fVelocity);
				bsIn.Read(cPropulsionState);

				g_pServer->platformUpdate(pPacket->systemAddress, fPos, fVelocity, cPropulsionState);

				printf("platform %f/%f/%d\n", fPos, fVelocity, cPropulsionState);

				/*RakNet::BitStream bsOut;
				bsOut.Write((RakNet::MessageID)ID_PLATFORM);
				bsOut.Write(Shared::getCurrentTime());
				bsOut.Write(fPos);
				bsOut.Write(fVelocity);
				bsOut.Write((char)cPropulsionState);
				m_pPeer->Send(&bsOut, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0, pPacket->systemAddress, false);*/
			}
			break;

		default:
			printf("Message with identifier %i has arrived.\n", pPacket->data[0]);
			break;
		}
	}
}

void Network::send(RakNet::BitStream *pBitStream, PacketPriority priority, PacketReliability reliability, RakNet::SystemAddress systemAddress, bool bBroadcast)
{
	m_pPeer->Send(pBitStream, priority, reliability, 0, systemAddress, bBroadcast);
}
