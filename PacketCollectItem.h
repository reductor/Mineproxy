#pragma once


#include "Packet.h"
#include "protocol.h"

class Packet_CollectItem : public Packet
{
private:
	int collectedID;
	int collectorID;
public:
	Packet_CollectItem() : collectedID(0),collectorID(0) {}

	bool ReadPacket(SOCKET s)
	{
		collectedID = ReadInt(s);
		collectorID = ReadInt(s);
		return true;
	}

	void WritePacket(SOCKET s)
	{
		WriteInt(s,collectedID);
		WriteInt(s,collectorID);
	}

	void Print(FILE *fp)
	{
		fprintf(fp, "CollectItem( collectedID = %d, collectorID = %d )", collectedID, collectorID);
	}
};

REGISTER_PACKET(CollectItem);
