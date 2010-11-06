#pragma once

#include <winsock2.h>
#include "Packet.h"
#include "protocol.h"

class Packet_Flying : public Packet
{
private:
	char flying;
public:
	Packet_Flying() : flying(0) {}

	bool ReadPacket(SOCKET s)
	{
		flying = ReadByte(s);
		return true;
	}

	void WritePacket(SOCKET s)
	{
		WriteByte(s,flying);
	}

	void Print(FILE *fp)
	{
		fprintf(fp,"Flying ( flying = %d )", flying);
	}

};

REGISTER_PACKET(Flying);
