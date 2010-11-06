#pragma once

#include <winsock2.h>
#include "Packet.h"
#include "protocol.h"

class Packet_NamedEntitySpawn : public Packet
{
private:
	int entityID;
	char *playerName;
	int x;
	int y;
	int z;
	char rotation;
	char pitch;
	short currentItem;
public:
	Packet_NamedEntitySpawn() : entityID(0),playerName(NULL),x(0),y(0),z(0),rotation(0),pitch(0),currentItem(0) {}
	~Packet_NamedEntitySpawn()
	{
		delete[] playerName;
	}

	bool ReadPacket(SOCKET s)
	{
		entityID = ReadInt(s);
		playerName = ReadString(s);
		x = ReadInt(s);
		y = ReadInt(s);
		z = ReadInt(s);
		rotation = ReadByte(s);
		pitch = ReadByte(s);
		currentItem = ReadShort(s);
		return true;
	}

	void WritePacket(SOCKET s)
	{
		WriteInt(s,entityID);
		WriteString(s,playerName);
		WriteInt(s,x);
		WriteInt(s,y);
		WriteInt(s,z);
		WriteByte(s,rotation);
		WriteByte(s,pitch);
		WriteShort(s,currentItem);
	}

	void Print(FILE *fp)
	{
		fprintf(fp, "NamedEntitySpawn ( entityID = %d, playerName = %s, x = %d, y = %d, z = %d, rotation = %d, pitch = %d, currentItem = %d )",
			entityID, playerName, x,y,z, (int)rotation, (int)pitch, (int)currentItem);
	}
};

REGISTER_PACKET(NamedEntitySpawn);
