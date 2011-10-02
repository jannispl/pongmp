#include <stdio.h>
#include <RakPeerInterface.h>
#include <BitStream.h>
#include <MessageIdentifiers.h>
#include <windows.h>

#define MAX_CLIENTS 2
#define SERVER_PORT 45000

enum GamePackets
{
	ID_TEST = ID_USER_PACKET_ENUM + 1,
	ID_PLATFORM
};

DWORD64 g_qwStartTime = 0;

float currentTime()
{
	DWORD64 qwDelta = GetTickCount64() - g_qwStartTime;
	return (float)qwDelta / 1000.0f;
}

int main(int argc, char *argv[])
{
	g_qwStartTime = GetTickCount64();

	RakNet::RakPeerInterface *peer = RakNet::RakPeerInterface::GetInstance();
	peer->Startup(MAX_CLIENTS, &RakNet::SocketDescriptor(SERVER_PORT, 0), 1);
	peer->SetMaximumIncomingConnections(MAX_CLIENTS);

	DWORD dwLastTime = 0;

	unsigned char ucCurrentState = 0;
	float fCurPos = 0.0f, fCurVel = 0.0f;

	float fNextPhysics = currentTime();

	RakNet::Packet *packet;
	while (true)
	{
/*		if (currentTime() >= fNextPhysics)
		{
			fNextPhysics += 1.0f / 60.0f;

			if (ucCurrentState == 1) // up
			{
				fCurVel -= 0.60f;
			}
			else if (ucCurrentState == 2) // down
			{
				fCurVel += 0.60f;
			}

			if (fCurVel > 7.0f)
			{
				fCurVel = 7.0f;
			}
			else if (fCurVel < -7.0f)
			{
				fCurVel = -7.0f;
			}

			if (ucCurrentState == 0)
			{
				if (fCurVel < 0.0f)
				{
					fCurVel += 0.15f;
					if (fCurVel > 0.0f) fCurVel = 0.0f;
				}
				else if (fCurVel > 0.0f)
				{
					fCurVel -= 0.15f;
					if (fCurVel < 0.0f) fCurVel = 0.0f;
				}
			}

			fCurPos += fCurVel;
			if (fCurPos < 0)
			{
				printf("BEFORE: %f/%f | Preventing negative border break-out\n", fCurPos, fCurVel);
				fCurPos = 0;
				fCurVel = 0.0f;
			}
			else if (fCurPos > 480.0f - 50.0f)
			{
				printf("BEFORE: %f/%f | Preventing positive border break-out\n", fCurPos, fCurVel);
				fCurPos = 480.0f - 50.0f;
				fCurVel = 0.0f;
			}

			RakNet::BitStream bsOut;
			bsOut.Write((RakNet::MessageID)ID_CLIENTUPDATE);
			bsOut.Write(currentTime());
			bsOut.Write(ucCurrentState);
			bsOut.Write(fCurPos);
			bsOut.Write(fCurVel);
			peer->Send(&bsOut, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);

			printf("%f / %f\n", fCurPos, fCurVel);
		}*/

		for (packet = peer->Receive(); packet != NULL; peer->DeallocatePacket(packet), packet = peer->Receive())
		{
			switch (packet->data[0])
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
			case ID_NEW_INCOMING_CONNECTION:
				printf("A connection is incoming.\n");
				break;
			case ID_NO_FREE_INCOMING_CONNECTIONS:
				printf("The server is full.\n");
				break;
			case ID_DISCONNECTION_NOTIFICATION:
				printf("A client has disconnected.\n");
				break;
			case ID_CONNECTION_LOST:
				printf("A client lost the connection.\n");
				break;

			case ID_PLATFORM:
				{
					RakNet::BitStream bsIn(packet->data, packet->length, false);
					bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

					
					float fPos, fVelocity;
					enum {OFF, UP, DOWN} propulsionState; // yes. cba to include the Platform header file
					bsIn.Read(fPos);
					bsIn.Read(fVelocity);
					bsIn.Read(propulsionState);

					printf("platform %f/%f/%d\n", fPos, fVelocity, propulsionState);

					RakNet::BitStream bsOut;
					bsOut.Write((RakNet::MessageID)ID_PLATFORM);
					bsOut.Write(currentTime());
					bsOut.Write(fPos);
					bsOut.Write(fVelocity);
					bsOut.Write(propulsionState);
					peer->Send(&bsOut, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0, packet->systemAddress, false);
				}
				break;

			/*case ID_INIT:
				{
					RakNet::BitStream bsIn(packet->data,  packet->length, false);
					bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

					float fPos, fVelocity;
					bsIn.Read(fPos);
					bsIn.Read(fVelocity);

					fCurPos = fPos;
					fCurVel = fVelocity;

					RakNet::BitStream bsOut;
					bsOut.Write((RakNet::MessageID)ID_INIT);
					bsOut.Write(fPos);
					peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);
				}

			case ID_INPUT:
				{
					RakNet::BitStream bsIn(packet->data, packet->length, false);
					bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

					DWORD dwTime;
					bsIn.Read(dwTime);

					if (dwTime < dwLastTime)
					{
						// reject if we had a newer packet already
						break;
					}

					DWORD dwDeltaTime = dwLastTime - dwTime;
					dwLastTime = GetTickCount();

					unsigned char ucState;
					bsIn.Read(ucState);

					ucCurrentState = ucState;
				}
				break;*/
			
			default:
				printf("Message with identifier %i has arrived.\n", packet->data[0]);
				break;
			}
		}
	}

	RakNet::RakPeerInterface::DestroyInstance(peer);

	return 0;
}
