#pragma once


#include "Packet.h"
#include "protocol.h"
#include "level.h"

class Packet_SpawnPlayer : public Packet
{
private:
	int x;
	int y;
	int z;
public:
	Packet_SpawnPlayer() : x(0),y(0),z(0) {}

	bool ReadPacket(SOCKET s)
	{
		x = ReadInt(s);
		y = ReadInt(s);
		z = ReadInt(s);

		g_level.spawnX = x;
		g_level.spawnY = y;
		g_level.spawnZ = z;
		return true;
	}

	void WritePacket(SOCKET s)
	{
		WriteInt(s,x);
		WriteInt(s,y);
		WriteInt(s,z);
	}

	void Print(FILE *fp)
	{
		fprintf(fp, "SpawnPlayer ( x = %d, y = %d, z = %d )",
			x,y,z);
	}
};

REGISTER_PACKET(SpawnPlayer);
