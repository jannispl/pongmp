#include "StdInc.h"
#include "Network.h"
#include <stdio.h>
#include <BitStream.h>
#include <RakNetTypes.h>

Network::Network()
	: m_fLastPlatformPacket(0.0f)
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

	m_pPeer->Startup(1, &RakNet::SocketDescriptor(), 1);

	m_pPeer->Connect("localhost", 45000, NULL, 0);

	return true;
}

void Network::deinitialize()
{
	m_pPeer->Shutdown(300, 0, HIGH_PRIORITY);
	RakNet::RakPeerInterface::DestroyInstance(m_pPeer);
}

void Network::process()
{
	for (RakNet::Packet *pPacket = m_pPeer->Receive(); pPacket; m_pPeer->DeallocatePacket(pPacket), pPacket = m_pPeer->Receive())
	{
		switch (pPacket->data[0])
		{
		case ID_REMOTE_DISCONNECTION_NOTIFICATION:
			printf("Another client has disconnected.\n");
			break;
		case ID_REMOTE_CONNECTION_LOST:
			printf("Another client has lost the connection.\n");
			break;
		case ID_REMOTE_NEW_INCOMING_CONNECTION:
			printf("Another client has connected.\n");
			break;
		case ID_CONNECTION_REQUEST_ACCEPTED:
			printf("Our connection request has been accepted.\n");
			break;
		case ID_NO_FREE_INCOMING_CONNECTIONS:
			g_pGame->getGraphics()->showStatusMessage("Sry, Server is full");
			break;
		case ID_DISCONNECTION_NOTIFICATION:
			printf("We have been disconnected.\n");
			break;
		case ID_CONNECTION_LOST:
			printf("Connection lost.\n");
			break;

		case ID_PLAYER_INTRO:
			{
				RakNet::BitStream bsIn(pPacket->data, pPacket->length, false);
				bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

				char cIsFresh;
				bsIn.Read(cIsFresh);

				g_pGame->getGraphics()->showStatusMessage("Got other player", 3.0f);
			}
			break;

		case ID_PLAYER_OUTRO:
			{
				g_pGame->getGraphics()->showStatusMessage("Other player left", 3.0f);
			}
			break;
			
		case ID_PLATFORM:
			{
				RakNet::BitStream bsIn(pPacket->data, pPacket->length, false);
				bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
				
				float fTimestamp;
				bsIn.Read(fTimestamp);

				if (m_fLastPlatformPacket > fTimestamp)
				{
					break;
				}
				m_fLastPlatformPacket = fTimestamp;

				float fPos, fVelocity;
				Platform::PropulsionState propulsionState;
				bsIn.Read(fPos);
				bsIn.Read(fVelocity);
				bsIn.Read(propulsionState);

				Platform *p = g_pGame->getPlatform(1);
				float fX, fY;
				p->getPosition(fX, fY);
				p->setPosition(fX, fPos);
				p->setVelocity(fVelocity);
				p->setPropulsionState(propulsionState);
			}
			break;

		default:
			printf("Message with identifier %i has arrived.\n", pPacket->data[0]);
			break;
		}
	}
}

void Network::updatePlatform(float fPos, float fVelocity, Platform::PropulsionState propulsionState)
{
	RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID)ID_PLATFORM);
	bsOut.Write(fPos);
	bsOut.Write(fVelocity);
	bsOut.Write((char)propulsionState);
	m_pPeer->Send(&bsOut, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}
