#pragma once


#include "Packet.h"
#include "protocol.h"

class Packet_PlayerPosition : public Packet
{
private:
	double x;
	double y;
	double stance;
	double z;
	char flying;
public:
	Packet_PlayerPosition() : x(0), y(0), stance(0), z(0), flying(0) {}

	bool ReadPacket(SOCKET s)
	{
		x = ReadDouble(s);
		y = ReadDouble(s);
		stance = ReadDouble(s);
		z = ReadDouble(s);
		flying = ReadByte(s);
		return true;
	}

	void WritePacket(SOCKET s)
	{
		WriteDouble(s,x);
		WriteDouble(s,y);
		WriteDouble(s,stance);
		WriteDouble(s,z);
		WriteByte(s,flying);
	}

	void Print(FILE *fp)
	{
		fprintf(fp, "PlayerPosition ( x = %f, y = %f, z = %f, stance = %f, flying = %d )",
			x,y,z,stance,(int)flying);
	}
};

REGISTER_PACKET(PlayerPosition);
