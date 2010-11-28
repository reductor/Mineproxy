#include "protocol.h"
#include <string.h>
#include <stdint.h>

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

int32_t ReadInt(SOCKET s)
{
	int32_t buf;
	RecvAll(s, (char*)&buf, sizeof(buf), 0);
	return ntohl(buf);
}

void WriteInt(SOCKET s, int32_t val)
{
	val = htonl(val);
	send(s, (char*)&val, sizeof(val), 0);
}

int16_t ReadShort(SOCKET s)
{
	int16_t buf;
	RecvAll(s, (char*)&buf, sizeof(buf), 0);
	return ntohs(buf);
}

void WriteShort(SOCKET s, int16_t val)
{
	val = htons(val);
	send(s, (char*)&val, sizeof(short), 0);
}

float ReadFloat(SOCKET s)
{
	int32_t buf;
	RecvAll(s, (char*)&buf, sizeof(buf), 0);
	buf = ntohl(buf);
	float f;
	memcpy(&f, &buf, sizeof(f));
	return f;
}

void WriteFloat(SOCKET s, float val)
{
	int32_t ival;
	memcpy(&ival, &val, sizeof(ival));
	ival = htonl(ival);
	send(s, (char*)&ival, sizeof(ival), 0);
}

double ReadDouble(SOCKET s)
{
	uint64_t buf;
	RecvAll(s, (char*)&buf, sizeof(buf), 0);
	buf = ntohll(buf);
	double d;
	memcpy(&d, &buf, sizeof(buf));
	return d;
}


void WriteDouble(SOCKET s, double val)
{
	uint64_t ival;
	memcpy(&ival, &val,  sizeof(ival));
	ival = htonll(ival);
	send(s, (char*)&ival, sizeof(ival), 0);
}

char *ReadString(SOCKET s)
{
	int16_t stringlen;
	RecvAll(s, (char*)&stringlen, sizeof(stringlen), 0);
	stringlen = ntohs(stringlen);
	char *str = new char[stringlen+1];
	RecvAll(s, str, stringlen, 0);
	str[stringlen] = 0;
	return str;

}

void WriteString(SOCKET s, const char *str)
{
	int16_t stringlen = htons(strlen(str));
	send(s, (char*)&stringlen, sizeof(short), 0);
	send(s, str, strlen(str), 0);
}


int8_t ReadByte(SOCKET s)
{
	int8_t buf;
	RecvAll(s, (char*)&buf,1,0);
	return buf;
}

void WriteByte(SOCKET s, int8_t b)
{
	send(s, (char*)&b, 1, 0);
}

int64_t ReadLongLong(SOCKET s)
{
	int64_t buf;
	RecvAll(s, (char*)&buf, sizeof(buf), 0);
	return ntohll(buf);	
}

void WriteLongLong(SOCKET s, int64_t val)
{
	val = htonll(val);
	send(s, (char*)&val, sizeof(val), 0);
}
