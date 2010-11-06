#pragma once

#include <winsock2.h>
#include "Packet.h"
#include "protocol.h"

class Packet_BlockChange : public Packet
{
private:
	int x;
	char y;
	int z;
	char blockType;
	char metaData;
public:
	Packet_BlockChange() : x(0),y(0),z(0),blockType(0),metaData(0) {}


	bool ReadPacket(SOCKET s)
	{
		x = ReadInt(s);
		y = ReadByte(s);
		z = ReadInt(s);
		blockType = ReadByte(s);
		metaData = ReadByte(s);
		return true;
	}

	void WritePacket(SOCKET s)
	{
		WriteInt(s,x);
		WriteByte(s,y);
		WriteInt(s,z);
		WriteByte(s,blockType);
		WriteByte(s,metaData);
	}

	void Print(FILE *fp)
	{
		fprintf(fp, "BlockChange( x = %d, y = %d, z = %d, blockType = %d, metaData = %d )",x,(int)y,z,(int)blockType,(int)metaData);
	}
};

REGISTER_PACKET(BlockChange);
