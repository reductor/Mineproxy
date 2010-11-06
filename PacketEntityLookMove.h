#pragma once

#include <winsock2.h>
#include "Packet.h"
#include "protocol.h"

class Packet_EntityLookMove : public Packet
{
private:
	int entityID;
	char x;
	char y;
	char z;
	char rotation;
	char pitch;
public:
	Packet_EntityLookMove() : entityID(0),x(0),y(0),z(0),rotation(0),pitch(0) {}


	bool ReadPacket(SOCKET s)
	{
		entityID = ReadInt(s);
		x = ReadByte(s);
		y = ReadByte(s);
		z = ReadByte(s);
		rotation = ReadByte(s);
		pitch = ReadByte(s);
		return true;
	}

	void WritePacket(SOCKET s)
	{
		WriteInt(s,entityID);
		WriteByte(s,x);
		WriteByte(s,y);
		WriteByte(s,z);
		WriteByte(s,rotation);
		WriteByte(s,pitch);
	}

	void Print(FILE *fp)
	{
		fprintf(fp, "EntityLookMove ( entityID = %d, x = %d, y = %d, z = %d, rotation = %d, pitch = %d )",
			entityID, (int)x, (int)y, (int)z, (int)rotation, (int)pitch);
	}
};

REGISTER_PACKET(EntityLookMove);
