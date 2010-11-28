#pragma once


#include "Packet.h"
#include "protocol.h"

class Packet_AttachEntity : public Packet
{
private:
	int entityID;
	int vehicleID;
public:
	Packet_AttachEntity() : entityID(0), vehicleID(0) {}
	~Packet_AttachEntity()
	{
	}
	bool ReadPacket(SOCKET s)
	{
		entityID = ReadInt(s);
		vehicleID = ReadInt(s);
		return true;
	}

	void WritePacket(SOCKET s)
	{
		WriteInt(s, entityID);
		WriteInt(s, vehicleID);
	}

	void Print(FILE *fp)
	{
		fprintf(fp, "AttachEntity?( entityID = %d, vehicleID = %d )", entityID, vehicleID);
	}

	void Process()
	{
	}
};

REGISTER_PACKET(AttachEntity);
