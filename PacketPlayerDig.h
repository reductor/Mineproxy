#pragma once

#include <winsock2.h>
#include "Packet.h"
#include "protocol.h"

class Packet_PlayerDig : public Packet
{
private:
	char status;

	int x;
	char y;
	int z;

	char direction;
public:
	Packet_PlayerDig() : status(0), x(0),y(0),z(0),direction(0) {}

	bool ReadPacket(SOCKET s)
	{
		status = ReadByte(s);
		x = ReadInt(s);
		y = ReadByte(s);
		z = ReadInt(s);
		direction = ReadByte(s);
		return true;
	}

	void WritePacket(SOCKET s)
	{
		WriteByte(s,status);
		WriteInt(s,x);
		WriteByte(s,y);
		WriteInt(s,z);
		WriteByte(s,direction);
	}

	void Print(FILE *fp)
	{
		fprintf(fp,"PlayerDig ( status = %d, x = %d, y = %d, z = %d, direction = %d )",
			(int)status, x, (int)y, z, (int)direction);
	}
};

REGISTER_PACKET(PlayerDig);
