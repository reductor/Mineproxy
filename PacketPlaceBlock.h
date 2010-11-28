#pragma once


#include "Packet.h"
#include "protocol.h"

class Packet_PlaceBlock : public Packet
{
private:
	short blockID;
	int x;
	char y;
	int z;

	char direction;
public:
	Packet_PlaceBlock() : blockID(0),x(0),y(0),z(0),direction(0) {}

	bool ReadPacket(SOCKET s)
	{
		blockID = ReadShort(s);
		x = ReadInt(s);
		y = ReadByte(s);
		z = ReadInt(s);
		direction = ReadByte(s);
		return true;
	}

	void WritePacket(SOCKET s)
	{
		WriteShort(s,blockID);
		WriteInt(s,x);
		WriteByte(s,y);
		WriteInt(s,z);
		WriteByte(s,direction);
	}

	void Print(FILE *fp)
	{
		fprintf(fp, "PlaceBlock ( blockID = %d, x = %d, y = %d, z = %d, direction = %d )",
			(int)blockID, x, (int)y, z, (int)direction);
	}
};

REGISTER_PACKET(PlaceBlock);
