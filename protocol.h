#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#define htonll(x)   ((((unsigned __int64)htonl(x)) << 32) + htonl(x >> 32))
#define ntohll(x)   ((((unsigned __int64)ntohl(x)) << 32) + ntohl(x >> 32))

void RecvAll(SOCKET s, char *buf, size_t len, int opts);
int ReadInt(SOCKET s);
void WriteInt(SOCKET s, int val);
unsigned int ReadUInt(SOCKET s);
void WriteUInt(SOCKET s, unsigned int val);
short ReadShort(SOCKET s);
void WriteShort(SOCKET s, short val);
float ReadFloat(SOCKET s);
void WriteFloat(SOCKET s, float val);
double ReadDouble(SOCKET s);
void WriteDouble(SOCKET s, double val);
char *ReadString(SOCKET s);
void WriteString(SOCKET s, const char *str);
char ReadByte(SOCKET s);
void WriteByte(SOCKET s, char b);
unsigned char ReadUByte(SOCKET s);
void WriteUByte(SOCKET s, unsigned char b);
unsigned long long ReadLongLong(SOCKET s);
void WriteLongLong(SOCKET s,unsigned long long val);

#endif