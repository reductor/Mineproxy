#pragma once

#include <winsock2.h>
#include "Packet.h"
#include "protocol.h"

class Packet_PlayerPositionLook : public Packet
{
private:
	double x;
	double y;
	double stance;
	double z;
	float rotation;
	float pitch;
	char flying;
public:
	Packet_PlayerPositionLook() :  x(0), y(0), stance(0), z(0), rotation(0.f), pitch(0.f), flying(0) {}

	bool ReadPacket(SOCKET s)
	{
		x = ReadDouble(s);
		y = ReadDouble(s);
		stance = ReadDouble(s);
		z = ReadDouble(s);
		rotation = ReadFloat(s);
		pitch = ReadFloat(s);
		flying = ReadByte(s);
		return true;
	}

	void WritePacket(SOCKET s)
	{
		WriteDouble(s,x);
		WriteDouble(s,y);
		WriteDouble(s,stance);
		WriteDouble(s,z);
		WriteFloat(s,rotation);
		WriteFloat(s,pitch);
		WriteByte(s,flying);
	}

	void Print(FILE *fp)
	{
		fprintf(fp, "PlayerPositionLook ( x = %f, y = %f, z = %f, stance = %f, rotation = %f, pitch = %f, flying = %d )",
			x,y,z,stance,rotation,pitch,(int)flying);
	}
};

REGISTER_PACKET(PlayerPositionLook);
