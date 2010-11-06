#pragma once

#include <winsock2.h>
#include "Packet.h"
#include "protocol.h"

class Packet_ArmAnimation : public Packet
{
private:
	int entityID;
	char forwardAnimation;
public:
	Packet_ArmAnimation() : entityID(0),forwardAnimation(0) {}

	bool ReadPacket(SOCKET s)
	{
		entityID = ReadInt(s);
		forwardAnimation = ReadByte(s);
		return true;
	}

	void WritePacket(SOCKET s)
	{
		WriteInt(s,entityID);
		WriteByte(s,forwardAnimation);
	}

	void Print(FILE *fp)
	{
		fprintf(fp,"ArmAnimation( entityID = %d, forwardAnimation = %d )", entityID, (int)forwardAnimation);
	}
};

REGISTER_PACKET(ArmAnimation);
