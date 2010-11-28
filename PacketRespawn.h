#pragma once


#include "Packet.h"
#include "protocol.h"

class Packet_Respawn : public Packet
{
private:
public:
	Packet_Respawn() {}
	~Packet_Respawn()
	{
	}
	bool ReadPacket(SOCKET s)
	{
		return true;
	}

	void WritePacket(SOCKET s)
	{
	}

	void Print(FILE *fp)
	{
		fprintf(fp, "Respawn(  )");
	}

	void Process()
	{
	}
};

REGISTER_PACKET(Respawn);
