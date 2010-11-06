#pragma once

#include <winsock2.h>
#include "Packet.h"
#include "protocol.h"
#include "level.h"


class Packet_Login : public Packet
{
private:
	int version;
	char *name;
	char *password;
	__int64 mapSeed;
	char dimension;
public:
	Packet_Login() : version(0),name(NULL),password(NULL) {}
	~Packet_Login()
	{
		delete[] name;
		delete[] password;
	}
	bool ReadPacket(SOCKET s)
	{
		version = ReadInt(s);
		name = ReadString(s);
		password = ReadString(s);
		mapSeed = ReadLongLong(s);
		dimension = ReadByte(s);
		return true;
	}

	void WritePacket(SOCKET s)
	{
		WriteInt(s,version);
		WriteString(s,name);
		WriteString(s,password);
		WriteLongLong(s,mapSeed);
		WriteByte(s, dimension);
	}

	void Print(FILE *fp)
	{
		fprintf(fp, "Login( version = %d, name = %s, password = %s, mapSeed = %lld, dimension = %d )", version, name, password, mapSeed, (int)dimension);
	}

	void Process()
	{
		if(!dumpingWorld)
			return;

		if(mapSeed != 0)
			g_level.mapSeed = mapSeed;
	}
};

REGISTER_PACKET(Login);
