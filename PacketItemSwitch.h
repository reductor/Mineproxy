#pragma once

#include <winsock2.h>
#include "Packet.h"
#include "protocol.h"

class Packet_ItemSwitch : public Packet
{
private:
	int entityID;
	short blockID;
public:
	Packet_ItemSwitch() : entityID(0),blockID(0) {}

	bool ReadPacket(SOCKET s)
	{
		entityID = ReadInt(s);
		blockID = ReadShort(s);;
		return true;
	}

	void WritePacket(SOCKET s)
	{
		WriteInt(s,entityID);
		WriteShort(s,blockID);
	}

	void Print(FILE *fp)
	{
		fprintf(fp, "ItemSwitch ( entityID = %d, blockID = %d )",
			entityID, (int)blockID);
	}
};

REGISTER_PACKET(ItemSwitch);
