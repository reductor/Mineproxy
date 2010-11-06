#pragma once

#include <winsock2.h>
#include "Packet.h"
#include "protocol.h"

class Packet_PlayerLook : public Packet
{
private:
	float rotation;
	float pitch;
	char flying;
public:
	Packet_PlayerLook() : rotation(0.f), pitch(0.f), flying(0) {}

	bool ReadPacket(SOCKET s)
	{
		rotation = ReadFloat(s);
		pitch = ReadFloat(s);
		flying = ReadByte(s);
		return true;
	}

	void WritePacket(SOCKET s)
	{
		WriteFloat(s, rotation);
		WriteFloat(s, pitch);
		WriteByte(s, flying);
	}

	void Print(FILE *fp)
	{
		fprintf(fp, "PlayerLook( rotation = %f, pitch = %f, flying = %d )",
			rotation, pitch, (int)flying);
	}
};

REGISTER_PACKET(PlayerLook);
