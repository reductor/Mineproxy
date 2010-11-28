#pragma once


#include "Packet.h"
#include "protocol.h"

class Packet_PickupSpawn : public Packet
{
private:
	int entityID;
	short itemType;
	char count;
	int x;
	int y;
	int z;
	char rotation;
	char pitch;
	char roll;
public:
	Packet_PickupSpawn() : entityID(0),itemType(0),x(0),y(0),z(0),rotation(0),pitch(0),roll(0) {}

	bool ReadPacket(SOCKET s)
	{
		entityID = ReadInt(s);
		itemType = ReadShort(s);
		count = ReadByte(s);
		x = ReadInt(s);
		y = ReadInt(s);
		z = ReadInt(s);
		rotation = ReadByte(s);
		pitch = ReadByte(s);
		roll = ReadByte(s);
		return true;
	}

	void WritePacket(SOCKET s)
	{
		WriteInt(s,entityID);
		WriteShort(s,itemType);
		WriteByte(s,count);
		WriteInt(s,x);
		WriteInt(s,y);
		WriteInt(s,z);
		WriteByte(s,rotation);
		WriteByte(s,pitch);
		WriteByte(s,roll);
	}

	void Print(FILE *fp)
	{
		fprintf(fp, "PickSpawn( entityID = %d, itemType = %d, count = %d, x = %d, y = %d, z = %d, rotation = %d, pitch = %d, roll = %d )",
			entityID, (int)itemType, (int)count, x,y,z, (int)rotation, (int)pitch, (int)roll);
	}
};

REGISTER_PACKET(PickupSpawn);
