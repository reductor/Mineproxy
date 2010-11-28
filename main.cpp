#include <stdio.h>
#include <time.h>
#ifdef WIN32
#include <windows.h>
#include <winsock2.h>
#else
#include <netdb.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <errno.h>
// Call me lazy
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define WSAGetLastError() errno
#define WSAEWOULDBLOCK EWOULDBLOCK
#define ioctlsocket ioctl
#endif
char worldfolder[128] = "";
bool dumpingWorld = false;
bool generatingLog = false;


/**
	 * C++ version 0.4 char* style "itoa":
	 * Written by Lukás Chmela
	 * Released under GPLv3.
	 */
	char* itoa(int value, char* result, int base) {
		// check that the base if valid
		if (base < 2 || base > 36) { *result = '\0'; return result; }
	
		char* ptr = result, *ptr1 = result, tmp_char;
		int tmp_value;
	
		do {
			tmp_value = value;
			value /= base;
			*ptr++ = 
"zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value 
* base)];
		} while ( value );
	
		// Apply negative sign
		if (tmp_value < 0) *ptr++ = '-';
		*ptr-- = '\0';
		while(ptr1 < ptr) {
			tmp_char = *ptr;
			*ptr--= *ptr1;
			*ptr1++ = tmp_char;
		}
		return result;
	}

#include "Packet.h"

typedef Packet * (*CreateInstance_t)();
CreateInstance_t packetFactory[256];

#include "level.h"


void SetNonBlocking(SOCKET s)
{
	u_long iMode = 1;
	ioctlsocket(s, FIONBIO, &iMode);

}



SOCKET Connect(const char *host, int port)
{
	SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	hostent *hp;

	unsigned long addr=inet_addr(host);
	if(addr==INADDR_NONE)
	{
		hp=gethostbyname(host);
		addr = *((unsigned long*)hp->h_addr);
	}
	else
	{
		
		hp=gethostbyaddr((char*)&addr,sizeof(addr),AF_INET);
	}

	if(server == INVALID_SOCKET)
	{
		printf("Failed to create socket\n");
		return 0;
	}

	sockaddr_in target;
	target.sin_family = AF_INET;
	target.sin_port = htons(port);
	target.sin_addr.s_addr = addr;
	
	if(hp != NULL)
		printf("Connecting to %s:%d\n",hp->h_name,port);

	if(connect(server, (sockaddr *)&target, sizeof(target)) == SOCKET_ERROR)
	{
		printf("Failed to connect\n");
		return 0;
	}

	printf("Connected\n");
	return server;
}

SOCKET WaitForClient(int port)
{
	SOCKET ourserver = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(ourserver == INVALID_SOCKET)
	{
		printf("Failed to create socket\n");
		return 0;
	}

	sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = INADDR_ANY;

	if(bind(ourserver, (sockaddr*)&local, sizeof(local)) != 0)
	{
		return 0;
	}

	if(listen(ourserver, 1) != 0)// 1 connection, too bad if some faggot port scans us.
	{
		return 0;
	}

	SOCKET client;
	sockaddr_in from;
	socklen_t fromlen = sizeof(from);

	printf("Listening for client on port %d\n",port);

	while(1)
	{
		client = accept(ourserver, (sockaddr*)&from, &fromlen);

		printf("Got connection from %s\n", inet_ntoa(from.sin_addr));
#ifdef WIN32
		closesocket(ourserver);
#else
		close(ourserver);
#endif

		return client;
	}

}


void usage()
{
	printf("Usage:\n"
			"\t-c<clientport>\tThe port your minecraft client will connect to (default 1337)\n"
			"\t-h<host>\tThe hostname of the server to connect to (default localhost)\n"
			"\t-p<port>\tThe port the minecraft server is using (default 25565)\n"
			"\t-l<filename>\tThe filename to log traffic into (- for stdout)\n"
			"\t-d<folder>\tThe folder to dump the world into (no spaces) (experimental)\n");
}


int main(int argc, char *argv[])
{
	printf("Minecraft Alpha Proxy by ReDucTor (James Mitchell)\n");
	printf("Version: 1.5\n");

	int clientport = 1337;
	char hostname[128] = "localhost";
	char logfilename[128] = "";
	int serverport = 25565;

	while ((argc > 1) && (argv[1][0] == '-'))
	{
		switch (argv[1][1])
		{
			case 'c': // client port
				clientport = atoi(&argv[1][2]);
				break;

			case 'h': // host
				strcpy(hostname,&argv[1][2]);
				break;

			case 'p': // host port
				serverport = atoi(&argv[1][2]);
				break;

			case 'l': // log file
				strcpy(logfilename,&argv[1][2]);
				generatingLog = true;
				break;

			case 'd': // dump world
				strcpy(worldfolder,&argv[1][2]);
				dumpingWorld = true;
				break;

			default:
				printf("Wrong Argument: %s\n", argv[1]);
				
				usage();
				return 0;
		}

		++argv;
		--argc;
	}

	if(worldfolder[0] == 0 && logfilename[0] == 0)
	{
		printf("You must specify to either log and/or generate a save\n");
		usage();
		return 0;
	}


	FILE *fp = stdout;
	if(logfilename[0] != '-' && generatingLog)
	{
		fp = fopen(logfilename,"wt");
		if(fp == NULL)
		{
			printf("Failed to open log file.\n");
			return 0;
		}
	}

	packetFactory[0x00] = CreatePacket_KeepAlive;
	packetFactory[0x01] = CreatePacket_Login;
	packetFactory[0x02] = CreatePacket_Handshake;
	packetFactory[0x03] = CreatePacket_Chat;
	packetFactory[0x04] = CreatePacket_TimeUpdate;
	packetFactory[0x05] = CreatePacket_PlayerInventory;
	packetFactory[0x06] = CreatePacket_SpawnPlayer;
	packetFactory[0x07] = CreatePacket_UseEntity;
	packetFactory[0x08] = CreatePacket_Health;
	packetFactory[0x09] = CreatePacket_Respawn;

	packetFactory[0x0A] = CreatePacket_Flying;
	packetFactory[0x0B] = CreatePacket_PlayerPosition;
	packetFactory[0x0C] = CreatePacket_PlayerLook;
	packetFactory[0x0D] = CreatePacket_PlayerPositionLook;
	packetFactory[0x0E] = CreatePacket_PlayerDig;
	packetFactory[0x0F] = CreatePacket_PlaceBlock;
	packetFactory[0x10] = CreatePacket_ItemSwitch;
	packetFactory[0x11] = CreatePacket_AddToInventory;
	packetFactory[0x12] = CreatePacket_ArmAnimation;

	packetFactory[0x14] = CreatePacket_NamedEntitySpawn;
	packetFactory[0x15] = CreatePacket_PickupSpawn;
	packetFactory[0x16] = CreatePacket_CollectItem;
	packetFactory[0x17] = CreatePacket_AddObject;
	packetFactory[0x18] = CreatePacket_MobSpawn;
	
	packetFactory[0x1C] = CreatePacket_Velocity;
	packetFactory[0x1D] = CreatePacket_DestroyEntity;
	packetFactory[0x1E] = CreatePacket_Entity;
	packetFactory[0x1F] = CreatePacket_EntityMove;
	packetFactory[0x20] = CreatePacket_EntityLook;
	packetFactory[0x21] = CreatePacket_EntityLookMove;
	packetFactory[0x22] = CreatePacket_EntityTeleport;

	packetFactory[0x27] = CreatePacket_AttachEntity;
	packetFactory[0x32] = CreatePacket_PreChunk;
	packetFactory[0x33] = CreatePacket_MapChunk;
	packetFactory[0x34] = CreatePacket_MultiBlockChange;
	packetFactory[0x35] = CreatePacket_BlockChange;
	packetFactory[0x3B] = CreatePacket_ComplexEntity;

	packetFactory[0xFF] = CreatePacket_Kick;

#ifdef WIN32
	WSADATA wsadata;

	if(WSAStartup(MAKEWORD(2,2), &wsadata) != 0)
	{
		printf("Failed to start winsock\n");
		return 0;
	}

	if(LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wVersion) != 2)
	{
		printf("Invalid version\n");
		return 0;
	}
#endif
	while(1)
	{
		SOCKET client = WaitForClient(clientport);
		if(client == 0)
			continue;
		SetNonBlocking(client);

		SOCKET server = Connect(hostname,serverport);
		if(server == 0)
			continue;
printf("setting non-blocking\n");
		SetNonBlocking(server);

		int starttime = (int)clock();

		bool running = true;

		fd_set socks;

		try
		{
			// packet for packet.
			while(running)
			{
printf("waiting for packets\n");
				FD_ZERO(&socks);
				FD_SET(client, &socks);
				FD_SET(server, &socks);
				timeval timeout;
				timeout.tv_sec = 3;
printf("doign select\n");
				int socketsToRead = select((client > server ? client : 
server)+1,&socks, NULL, NULL, &timeout);
printf("select came back\n");
				if(socketsToRead == SOCKET_ERROR)
				{
					break;
				}


				unsigned char packetType;
				if(FD_ISSET(client, &socks))
				{
printf("select has client\n");
					int len = recv(client,(char*)&packetType,1,0);

					if(len == SOCKET_ERROR && WSAGetLastError() == WSAEWOULDBLOCK)
						break;
					if(len == 0 || len == SOCKET_ERROR)
					{
						running = false;
						break;
					}

					int curtime = (int)clock();
					if(packetFactory[packetType] == NULL)
					{
						printf("%2.5f 0x%02X C->S: ",double(curtime-starttime)/CLOCKS_PER_SEC, packetType);
						printf("Invalid Packet Type");
						running = false;
						break;
					}
					Packet *packet = packetFactory[packetType]();
					if(generatingLog)
					{	
						fprintf(fp,"%2.5f 0x%02X C->S: ",double(curtime-starttime)/CLOCKS_PER_SEC, packetType);
					}
					if(packet->ReadPacket(client))
					{	
						packet->Process();
						if(generatingLog)
						{
							packet->Print(fp);
							fprintf(fp,"\n");
						}
						send(server,(char*)&packetType,1,0);
						packet->WritePacket(server);
					}
					delete packet;
				}

				if(FD_ISSET(server, &socks))
				{
printf("select has server\n");
					int len = recv(server,(char*)&packetType,1,0);

					if(len == SOCKET_ERROR && WSAGetLastError() == WSAEWOULDBLOCK)
						break;
					if(len == 0 || len == SOCKET_ERROR)
					{
						running = false;
						break;
					}

					int curtime = (int)clock();

					if(packetFactory[packetType] == NULL)
					{
						printf("%2.5f 0x%02X C->S: ",double(curtime-starttime)/CLOCKS_PER_SEC, packetType);
						printf("Invalid Packet Type");
						running = false;
						break;
					}
					Packet *packet = packetFactory[packetType]();
					if(generatingLog)
					{
						fprintf(fp,"%2.5f 0x%02X S->C: ",double(curtime-starttime)/CLOCKS_PER_SEC, packetType );
					}
					if(packet->ReadPacket(server))
					{
						packet->Process();
						if(generatingLog)
						{
							packet->Print(fp);
							fprintf(fp,"\n");
						}
						send(client,(char*)&packetType,1,0);
						packet->WritePacket(client);
					}
					delete packet;
				}
			}
		}
		catch (const char *err)
		{
			printf("Exception: %s\n", err);
		}
		if(dumpingWorld)
		{
			g_level.Save();
			g_level.chunks.clear();
		}
		printf("Connection has been terminated (0x%08X)\n",WSAGetLastError());
#ifdef WIN32
		closesocket(client);
		closesocket(server);
#else
		close(client);
		close(server);
#endif
		fflush(fp);
	}
	if(fp != stdout)
		fclose(fp);

}
