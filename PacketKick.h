#pragma once

#include <winsock2.h>
#include "Packet.h"
#include "protocol.h"

class Packet_Kick : public Packet
{
private:
	char *message;
public:
	Packet_Kick() : message(NULL) {}

	~Packet_Kick()
	{
		delete[] message;
	}

	bool ReadPacket(SOCKET s)
	{
		message = ReadString(s);
		return true;
	}

	void WritePacket(SOCKET s)
	{
		WriteString(s,message);
	}

	void Print(FILE *fp)
	{
		fprintf(fp, "Kick ( message = %s )", message);
	}
};

REGISTER_PACKET(Kick);
