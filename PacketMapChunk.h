#pragma once


#include "Packet.h"
#include "protocol.h"
extern "C"
{
	#include "zlib.h"
}

class Packet_MapChunk : public Packet
{
private:
	int32_t x;
	int16_t y;
	int32_t z;
	int8_t size_x;
	int8_t size_y;
	int8_t size_z;
	int32_t compressedSize;
	unsigned char *compressedData;
	unsigned char *uncompressedData;
public:
	Packet_MapChunk() : x(0),y(0),z(0),size_x(0),size_y(0),size_z(0),compressedSize(0),compressedData(NULL) {}
	~Packet_MapChunk()
	{
		delete[] compressedData;
	}


	bool ReadPacket(SOCKET s)
	{
		x = ReadInt(s);
		y = ReadShort(s);
		z = ReadInt(s);
		size_x = ReadByte(s);
		size_y = ReadByte(s);
		size_z = ReadByte(s);
		compressedSize = ReadInt(s);
		compressedData = new unsigned char[compressedSize];
		RecvAll(s,(char*)compressedData,compressedSize,0);

		int decompressedSize = (int)((float)((size_x+1) * (size_y+1) * (size_z+1)) * 2.5);
		uncompressedData = new unsigned char[decompressedSize];
		z_stream zInfo;
		memset(&zInfo,0,sizeof(z_stream));
		zInfo.zalloc = Z_NULL;
		zInfo.zfree = Z_NULL;
		zInfo.opaque = Z_NULL;
		zInfo.total_in=  0; zInfo.avail_in= compressedSize;
		zInfo.total_out= 0; zInfo.avail_out= decompressedSize;
		zInfo.next_in= compressedData;
		zInfo.next_out= uncompressedData;
		
		if(!dumpingWorld)
			return true;

		if(inflateInit(&zInfo) == Z_OK)
		{
			int ret = inflate( &zInfo, Z_FINISH );
			if ( ret != Z_STREAM_END || zInfo.total_out != ((size_x+1)*(size_y+1)*(size_z+1)*2.5))
			{
				printf("Decompressed size does not match packet\n");
			}
		}
		else
		{
			printf("Failed to initalize deflate\n");
		}
		deflateEnd( &zInfo );

		return true;
	}

	void WritePacket(SOCKET s)
	{
		WriteInt(s,x);
		WriteShort(s,y);
		WriteInt(s,z);
		WriteByte(s,size_x);
		WriteByte(s,size_y);
		WriteByte(s,size_z);
		WriteInt(s,compressedSize);
		send(s,(char*)compressedData,compressedSize,0);
	}

	void Process()
	{
		if(!dumpingWorld)
			return;
		int arraysize = ((size_x+1)*(size_y+1)*(size_z+1));
		unsigned char *typedata = uncompressedData;
		unsigned char *metadata = uncompressedData + arraysize;
		unsigned char *blocklight = uncompressedData + (int)((float)arraysize * 1.5);
		unsigned char *skylight = uncompressedData + arraysize * 2;

		Chunk *chunk = g_level.chunks.getChunk(x/16,z/16);
		if(chunk == NULL)
		{
			printf("Unable to find chunk %d,%d in hashmap\n",x,z);
		}

		// not full chunk
		if(size_x != 15 || size_y != 127 || size_z != 15)
			return;

		chunk->populated = true;

		memcpy(chunk->blockTypes,typedata,arraysize);
		memcpy(chunk->metadata,metadata,arraysize/2);
		memcpy(chunk->blocklight,blocklight,arraysize/2);
		memcpy(chunk->skylight,skylight,arraysize/2);
	}

	void Print(FILE *fp)
	{
		fprintf(fp, "MapChunk ( x = %d, y = %d, z = %d, size_x = %d, size_y = %d, size_z = %d, compressedSize = %d )",
			x,(int)y,z,(int)size_x,(int)size_y,(int)size_z,(int)compressedSize);
	}
};

REGISTER_PACKET(MapChunk);
