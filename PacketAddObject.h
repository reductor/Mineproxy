#pragma once


#include "Packet.h"
#include "protocol.h"

class Packet_AddObject : public Packet
{
private:
	int entityID;
	char type;
	int x;
	int y;
	int z;
public:
	Packet_AddObject() : entityID(0),type(0),x(0),y(0),z(0) {}

	bool ReadPacket(SOCKET s)
	{
		entityID = ReadInt(s);
		type = ReadByte(s);
		x = ReadInt(s);
		y = ReadInt(s);
		z = ReadInt(s);
		return true;
	}

	void WritePacket(SOCKET s)
	{
		WriteInt(s,entityID);
		WriteByte(s,type);
		WriteInt(s,x);
		WriteInt(s,y);
		WriteInt(s,z);
	}

	void Print(FILE *fp)
	{
		fprintf(fp,"AddObject( entityID = %d, type = %d, x = %d, y = %d, z = %d )",entityID,(int)type,x,y,z);
	}
};

REGISTER_PACKET(AddObject);
