#include <winsock2.h>
#include <windows.h>
#include "protocol.h"

void RecvAll(SOCKET s, char *buf, size_t len, int opts)
{
	while(len != 0)
	{
		int thisread = recv(s, buf, len, opts);
		if(thisread == 0)
			throw "recv returned 0";
		if(thisread == -1)
			continue;
		len -= thisread;
		buf += thisread;
	}
}

int ReadInt(SOCKET s)
{
	int buf;
	RecvAll(s, (char*)&buf, sizeof(int), 0);
	return ntohl(buf);
}

void WriteInt(SOCKET s, int val)
{
	val = htonl(val);
	send(s, (char*)&val, sizeof(int), 0);
}

unsigned int ReadUInt(SOCKET s)
{
	unsigned int buf;
	RecvAll(s, (char*)&buf, sizeof(int), 0);
	return ntohl(buf);
}

void WriteUInt(SOCKET s, unsigned int val)
{
	val = htonl(val);
	send(s, (char*)&val, sizeof(int), 0);
}

short ReadShort(SOCKET s)
{
	short buf;
	RecvAll(s, (char*)&buf, sizeof(short), 0);
	return ntohs(buf);
}

void WriteShort(SOCKET s, short val)
{
	val = htons(val);
	send(s, (char*)&val, sizeof(short), 0);
}

float ReadFloat(SOCKET s)
{
	u_long buf;
	RecvAll(s, (char*)&buf, sizeof(u_long), 0);
	buf = ntohl(buf);
	return *reinterpret_cast<float *>(&buf);
}

void WriteFloat(SOCKET s, float val)
{
	int ival = *reinterpret_cast<unsigned int*>(&val);
	ival = htonl(ival);
	send(s, (char*)&ival, sizeof(float), 0);
}

double ReadDouble(SOCKET s)
{
	unsigned long long buf;
	RecvAll(s, (char*)&buf, sizeof(double), 0);
	buf = ntohll(buf);
	return *reinterpret_cast<double *>(&buf);
}


void WriteDouble(SOCKET s, double val)
{
	unsigned long long ival = *reinterpret_cast<unsigned long long*>(&val);
	ival = htonll(ival);
	send(s, (char*)&ival, sizeof(double), 0);
}

char *ReadString(SOCKET s)
{
	short stringlen;
	RecvAll(s, (char*)&stringlen, sizeof(short), 0);
	stringlen = ntohs(stringlen);
	char *str = new char[stringlen+1];
	RecvAll(s, str, stringlen, 0);
	str[stringlen] = 0;
	return str;

}

void WriteString(SOCKET s, const char *str)
{
	short stringlen = htons(strlen(str));
	send(s, (char*)&stringlen, sizeof(short), 0);
	send(s, str, strlen(str), 0);
}


char ReadByte(SOCKET s)
{
	char buf;
	RecvAll(s, (char*)&buf,1,0);
	return buf;
}

void WriteByte(SOCKET s, char b)
{
	send(s, (char*)&b, 1, 0);
}

unsigned char ReadUByte(SOCKET s)
{
	unsigned char buf;
	RecvAll(s, (char*)&buf,1,0);
	return buf;
}

void WriteUByte(SOCKET s, unsigned char b)
{
	send(s, (char*)&b, 1, 0);
}

unsigned long long ReadLongLong(SOCKET s)
{
	unsigned long long buf;
	RecvAll(s, (char*)&buf, sizeof(unsigned long long), 0);
	return ntohll(buf);	
}

void WriteLongLong(SOCKET s, unsigned long long val)
{
	val = htonll(val);
	send(s, (char*)&val, sizeof(unsigned long long), 0);
	
}
