#pragma once

#include <winsock2.h>
#include "Packet.h"
#include "protocol.h"

class Packet_Handshake : public Packet
{
private:
	char *session;
public:
	Packet_Handshake() : session(NULL) {}

	~Packet_Handshake()
	{
		delete[] session;
	}

	bool ReadPacket(SOCKET s)
	{
		session = ReadString(s);
		return true;
	}

	void WritePacket(SOCKET s)
	{
		WriteString(s,session);
	}

	void Print(FILE *fp)
	{
		fprintf(fp, "Handshake ( session = %s )", session);
	}
};

REGISTER_PACKET(Handshake);
