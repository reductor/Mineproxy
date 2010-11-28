#pragma once


#include "Packet.h"
#include "protocol.h"

class Packet_EntityMove : public Packet
{
private:
	int entityID;
	char x;
	char y;
	char z;
public:
	Packet_EntityMove() : entityID(0),x(0),y(0),z(0) {}


	bool ReadPacket(SOCKET s)
	{
		entityID = ReadInt(s);
		x = ReadByte(s);
		y = ReadByte(s);
		z = ReadByte(s);
		return true;
	}

	void WritePacket(SOCKET s)
	{
		WriteInt(s,entityID);
		WriteByte(s,x);
		WriteByte(s,y);
		WriteByte(s,z);
	}

	void Print(FILE *fp)
	{
		fprintf(fp, "EntityMove( entityID = %d, x = %d, y = %d, z = %d )",
			entityID, (int)x, (int)y, (int)z);
	}
};

REGISTER_PACKET(EntityMove);
