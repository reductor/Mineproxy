#pragma once


#include "Packet.h"

class Packet_KeepAlive : public Packet
{
public:
	bool ReadPacket(SOCKET s){ return true; }
	void WritePacket(SOCKET s){}
	void Print(FILE *fp)
	{
		fprintf(fp,"KeepAlive( )");
	}

};

REGISTER_PACKET(KeepAlive);
