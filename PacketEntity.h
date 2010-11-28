#pragma once


#include "Packet.h"
#include "protocol.h"

class Packet_Entity : public Packet
{
private:
	int entityID;
public:
	Packet_Entity() : entityID(0) {}


	bool ReadPacket(SOCKET s)
	{
		entityID = ReadInt(s);
		return true;
	}

	void WritePacket(SOCKET s)
	{
		WriteInt(s,entityID);
	}

	void Print(FILE *fp)
	{
		fprintf(fp, "Entity( entityID = %d )", entityID);
	}
};

REGISTER_PACKET(Entity);
