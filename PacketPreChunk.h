#pragma once

#include <winsock2.h>
#include "Packet.h"
#include "protocol.h"

class Packet_PreChunk : public Packet
{
private:
	int x;
	int z;
	char mode;
public:
	Packet_PreChunk() : x(0),z(0),mode(0) {}

	bool ReadPacket(SOCKET s)
	{
		x = ReadInt(s);
		z = ReadInt(s);
		mode = ReadByte(s);

		return true;
	}

	void WritePacket(SOCKET s)
	{
		WriteInt(s,x);
		WriteInt(s,z);
		WriteByte(s,mode);
	}

	void Process()
	{
		if(!dumpingWorld)
			return;

		if(mode == 0)
		{
			g_level.chunks._delete(x,z);
		}
		else 
		{
			if(g_level.chunks.getChunk(x,z) == NULL)
				g_level.chunks.insert(new Chunk(x,z),x,z);
		}
	}

	void Print(FILE *fp)
	{
		fprintf(fp, "PreChunk ( x = %d, z = %d, mode = %d )",
			x,z,(int)mode);
	}
};

REGISTER_PACKET(PreChunk);
