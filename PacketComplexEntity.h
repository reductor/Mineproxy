#pragma once


#include "Packet.h"
#include "protocol.h"

class Packet_ComplexEntity : public Packet
{
private:
	int x;
	short y;
	int z;
	short payloadSize;
	unsigned char *payload;
public:
	Packet_ComplexEntity() : x(0),y(0),z(0),payloadSize(0),payload(NULL) {}
	~Packet_ComplexEntity()
	{
		delete[] payload;
	}


	bool ReadPacket(SOCKET s)
	{
		x = ReadInt(s);
		y = ReadShort(s);
		z = ReadInt(s);
		payloadSize = ReadShort(s);
		payload = new unsigned char[payloadSize];
		RecvAll(s,(char*)payload,payloadSize,0);
		return true;
	}

	void WritePacket(SOCKET s)
	{
		WriteInt(s,x);
		WriteShort(s,y);
		WriteInt(s,z);
		WriteShort(s,payloadSize);
		send(s,(char*)payload,payloadSize,0);
	}

	void Print(FILE *fp)
	{
		fprintf(fp, "ComplexEntity( x = %d, y = %d, z = %d, payloadSize = %d )",x,(int)y,z,(int)payloadSize);
	}

};

REGISTER_PACKET(ComplexEntity);
