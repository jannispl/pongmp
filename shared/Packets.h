#ifndef _PACKETS_H
#define _PACKETS_H

#include <MessageIdentifiers.h>

enum GamePackets
{
	ID_PLATFORM = ID_USER_PACKET_ENUM + 1,
	ID_PLAYER_INTRO,
	ID_PLAYER_OUTRO
};

#endif
