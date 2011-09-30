#include "StdInc.h"
#include "Network.h"
#include <stdio.h>
#include <BitStream.h>
#include <RakNetTypes.h>

Network::Network()
{
}

Network::~Network()
{
}

bool Network::initialize()
{
	m_qwInitTime = GetTickCount64();

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
			{
				printf("Our connection request has been accepted.\n");

				// Use a BitStream to write a custom user message
				// Bitstreams are easier to use than sending casted structures, and handle endian swapping automatically
				RakNet::BitStream bsOut;
				bsOut.Write((RakNet::MessageID)ID_INIT);

				Platform *p = g_pGame->getPlatform(1);
				float fX, fY;
				p->getPosition(fX, fY);
				bsOut.Write(fY);
				bsOut.Write(p->getVelocity());

				m_pPeer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, pPacket->systemAddress, false);
			}
			break;
		case ID_NO_FREE_INCOMING_CONNECTIONS:
			printf("The server is full.\n");
			break;
		case ID_DISCONNECTION_NOTIFICATION:
			printf("We have been disconnected.\n");
			break;
		case ID_CONNECTION_LOST:
			printf("Connection lost.\n");
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
				bsIn.Read(fPos);
				bsIn.Read(fVelocity);

				Platform *p = g_pGame->getPlatform(1);
				float fX, fY;
				p->getPosition(fX, fY);
				p->setPosition(fX, fPos);
				p->setVelocity(fVelocity);
			}
			break;

		/*case ID_INIT:
			{
				RakNet::BitStream bsIn(pPacket->data, pPacket->length, false);
				bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

				bsIn.Read(m_fCurrentPos);
			}
			break;

		case ID_CLIENTUPDATE:
			{
				RakNet::BitStream bsIn(pPacket->data, pPacket->length, false);
				bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

				float fTime;
				unsigned char ucState;
				float fPos, fVel;
				bsIn.Read(fTime);
				bsIn.Read(ucState);
				bsIn.Read(fPos);
				bsIn.Read(fVel);

				float fDeltaPos = m_fCurrentPos >= fPos ? m_fCurrentPos - fPos : fPos - m_fCurrentPos;
				if (fDeltaPos > 1.0f)
				{
					m_fCurrentPos = fPos;
				}
				else if (fDeltaPos > 0.2f)
				{
					m_fCurrentPos += (m_fCurrentPos - fPos) * 0.1f;
				}

				Platform *p = g_pGame->getPlatform(1);
				float fX, fY;
				p->getPosition(fX, fY);
				p->setPosition(fX, m_fCurrentPos);
				p->setVelocity(fVel);
			}
			break;*/
		
		default:
			printf("Message with identifier %i has arrived.\n", pPacket->data[0]);
			break;
		}
	}
}

float Network::getCurrentTime()
{
	DWORD64 qwDelta = GetTickCount64() - m_qwInitTime;
	return (float)qwDelta / 1000.0f;
}

void Network::updatePlatform(float fPos, float fVelocity)
{
	RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID)ID_PLATFORM);
	bsOut.Write(fPos);
	bsOut.Write(fVelocity);
	m_pPeer->Send(&bsOut, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}

void Network::updateInput(bool bUp, bool bDown)
{
	unsigned char ucState = 0;
	if (bUp)
	{
		ucState = 1;
	}
	else if (bDown)
	{
		ucState = 2;
	}

	RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID)ID_INPUT);
	bsOut.Write(GetTickCount());
	bsOut.Write(ucState);
	m_pPeer->Send(&bsOut, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}
