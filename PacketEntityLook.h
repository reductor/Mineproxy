#pragma once


#include "Packet.h"
#include "protocol.h"

class Packet_EntityLook : public Packet
{
private:
	int entityID;
	char rotation;
	char pitch;
public:
	Packet_EntityLook() : entityID(0),rotation(0),pitch(0) {}


	bool ReadPacket(SOCKET s)
	{
		entityID = ReadInt(s);
		rotation = ReadByte(s);
		pitch = ReadByte(s);
		return true;
	}

	void WritePacket(SOCKET s)
	{
		WriteInt(s,entityID);
		WriteByte(s,rotation);
		WriteByte(s,pitch);
	}

	void Print(FILE *fp)
	{
		fprintf(fp, "EntityLook ( entityID = %d, rotation = %d, pitch = %d )", entityID, (int)rotation, (int)pitch);
	}
};

REGISTER_PACKET(EntityLook);
