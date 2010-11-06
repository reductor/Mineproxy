#pragma once

#include <winsock2.h>
#include "Packet.h"
#include "protocol.h"

class Packet_Chat : public Packet
{
private:
	char *message;
public:
	Packet_Chat() : message(NULL) {}

	~Packet_Chat()
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
		fprintf(fp, "Chat ( message = %s )", message);
	}
};

REGISTER_PACKET(Chat);
