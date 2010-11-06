#pragma once

#include <winsock2.h>
#include "Packet.h"
#include "protocol.h"
#include "level.h"

class Packet_TimeUpdate : public Packet
{
private:
	unsigned long long time;
public:
	Packet_TimeUpdate() : time(0) {}

	bool ReadPacket(SOCKET s)
	{
		time = ReadLongLong(s);
		return true;
	}

	void WritePacket(SOCKET s)
	{
		WriteLongLong(s,time);
	}

	void Print(FILE *fp)
	{
		fprintf(fp, "TimeUpdate ( time = %lld )", time);
	}

	void Process()
	{
		if(!dumpingWorld)
			return;

		g_level.time = time;
	}
};

REGISTER_PACKET(TimeUpdate);
