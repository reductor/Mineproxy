#pragma once

#include <winsock2.h>
#include "Packet.h"
#include "protocol.h"

class Packet_Health : public Packet
{
private:
	char health;
public:
	Packet_Health() : health(0) {}
	~Packet_Health()
	{
	}
	bool ReadPacket(SOCKET s)
	{
		health = ReadByte(s);
		return true;
	}

	void WritePacket(SOCKET s)
	{
		WriteByte(s, health);
	}

	void Print(FILE *fp)
	{
		fprintf(fp, "Health( Health = %d )", (int)health);
	}

	void Process()
	{
	}
};

REGISTER_PACKET(Health);
