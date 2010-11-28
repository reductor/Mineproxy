#pragma once


#include "Packet.h"
#include "protocol.h"

class Packet_UseEntity : public Packet
{
private:
	int user;
	int target;
	char punching;
public:
	Packet_UseEntity() : user(0), target(0), punching(0) {}
	~Packet_UseEntity()
	{
	}
	bool ReadPacket(SOCKET s)
	{
		user = ReadInt(s);
		target = ReadInt(s);
		punching = ReadByte(s);
		return true;
	}

	void WritePacket(SOCKET s)
	{
		WriteInt(s, user);
		WriteInt(s, target);
		WriteByte(s, punching);
	}

	void Print(FILE *fp)
	{
		fprintf(fp, "UseEntity( user = %d, target = %d, punching? = %d )", user, target, (int)punching);
	}

	void Process()
	{
	}
};

REGISTER_PACKET(UseEntity);
