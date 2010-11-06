#pragma once

#include <winsock2.h>
#include "Packet.h"
#include "protocol.h"

class Packet_MobSpawn : public Packet
{
private:
	int entityID;
	char type;
	int x;
	int y;
	int z;
	char rotation;
	char pitch;
public:
	Packet_MobSpawn() : entityID(0),type(0),x(0),y(0),z(0),rotation(0),pitch(0) {}


	bool ReadPacket(SOCKET s)
	{
		entityID = ReadInt(s);
		type = ReadByte(s);
		x = ReadInt(s);
		y = ReadInt(s);
		z = ReadInt(s);
		rotation = ReadByte(s);
		pitch = ReadByte(s);
		return true;
	}

	void WritePacket(SOCKET s)
	{
		WriteInt(s,entityID);
		WriteByte(s,type);
		WriteInt(s,x);
		WriteInt(s,y);
		WriteInt(s,z);
		WriteByte(s,rotation);
		WriteByte(s,pitch);
	}

	void Print(FILE *fp)
	{
		fprintf(fp, "MobSpawn ( entityID = %d, type = %d, x = %d, y = %d, z = %d, rotation = %d, pitch = %d )",
			entityID, (int)type, x,y,z, (int)rotation, (int)pitch);
	}
};

REGISTER_PACKET(MobSpawn);
