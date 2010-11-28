#pragma once


#include "Packet.h"
#include "protocol.h"

class Packet_EntityTeleport : public Packet
{
private:
	int entityID;
	int x;
	int y;
	int z;
	char rotation;
	char pitch;
public:
	Packet_EntityTeleport() : entityID(0),x(0),y(0),z(0),rotation(0),pitch(0) {}

	bool ReadPacket(SOCKET s)
	{
		entityID = ReadInt(s);
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
		WriteInt(s,x);
		WriteInt(s,y);
		WriteInt(s,z);
		WriteByte(s,rotation);
		WriteByte(s,pitch);
	}

	void Print(FILE *fp)
	{
		fprintf(fp, "EntityTeleport( entityID = %d, x = %d, y = %d, z = %d, rotation = %d, pitch = %d )",
			entityID, x,y,z, (int)rotation, (int)pitch);
	}
};

REGISTER_PACKET(EntityTeleport);
