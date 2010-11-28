#pragma once


#include "Packet.h"
#include "protocol.h"

class Packet_AddToInventory : public Packet
{
private:
	short blockID;
	char amount;
	short life;
public:
	Packet_AddToInventory() : blockID(0),amount(0),life(0) {}

	bool ReadPacket(SOCKET s)
	{
		blockID = ReadShort(s);
		amount = ReadByte(s);
		life = ReadShort(s);
		return true;
	}

	void WritePacket(SOCKET s)
	{
		WriteShort(s,blockID);
		WriteByte(s,amount);
		WriteShort(s,life);
	}

	void Print(FILE *fp)
	{
		fprintf(fp,"AddToInventory( blockID = %d, amount = %d, life = %d )",(int)blockID,(int)amount,(int)life);
	}
};

REGISTER_PACKET(AddToInventory);
