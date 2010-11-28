#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#include <stdint.h>

#ifdef WIN32
#include <winsock2.h>
#include <windows.h>
#else
#include <arpa/inet.h>
typedef int SOCKET;
#endif

#define htonll(x)   ((((uint64_t)htonl(x)) << 32) + htonl(x >> 32))
#define ntohll(x)   ((((uint64_t)ntohl(x)) << 32) + ntohl(x >> 32))

void RecvAll(SOCKET s, char *buf, size_t len, int opts);
int32_t ReadInt(SOCKET s);
void WriteInt(SOCKET s, int32_t val);
int16_t ReadShort(SOCKET s);
void WriteShort(SOCKET s, int16_t val);
float ReadFloat(SOCKET s);
void WriteFloat(SOCKET s, float val);
double ReadDouble(SOCKET s);
void WriteDouble(SOCKET s, double val);
char *ReadString(SOCKET s);
void WriteString(SOCKET s, const char *str);
int8_t ReadByte(SOCKET s);
void WriteByte(SOCKET s, int8_t b);
int64_t ReadLongLong(SOCKET s);
void WriteLongLong(SOCKET s, int64_t val);

#endif
