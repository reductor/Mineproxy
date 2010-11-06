#pragma once

#include <winsock2.h>
#include "Packet.h"
#include "protocol.h"

class Packet_DestroyEntity : public Packet
{
private:
	int entityID;
public:
	Packet_DestroyEntity() : entityID(0) {}

	bool ReadPacket(SOCKET s)
	{
		entityID = ReadInt(s);
		return true;
	}

	void WritePacket(SOCKET s)
	{
		WriteInt(s,entityID);
	}

	void Print(FILE *fp)
	{
		fprintf(fp,"DestroyEntity( entityID = %d )",entityID);
	}
};

REGISTER_PACKET(DestroyEntity);
