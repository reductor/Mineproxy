#pragma once

#include <winsock2.h>
#include "Packet.h"
#include "protocol.h"

class Packet_Velocity : public Packet
{
private:
	int entityID;
	short velocityX;
	short velocityY;
	short velocityZ;
public:
	Packet_Velocity() : entityID(0), velocityX(0), velocityY(0), velocityZ(0) {}
	~Packet_Velocity()
	{
	}
	bool ReadPacket(SOCKET s)
	{
		entityID = ReadInt(s);
		velocityX = ReadShort(s);
		velocityY = ReadShort(s);
		velocityZ = ReadShort(s);
		return true;
	}

	void WritePacket(SOCKET s)
	{
		WriteInt(s, entityID);
		WriteShort(s, velocityX);
		WriteShort(s, velocityY);
		WriteShort(s, velocityZ);
	}

	void Print(FILE *fp)
	{
		fprintf(fp, "Velocity?( entityID = %d, velocityX = %d, velocityY = %d, velocityZ )", entityID, (int)velocityX, (int)velocityY, (int)velocityZ);
	}

	void Process()
	{
	}
};

REGISTER_PACKET(Velocity);
