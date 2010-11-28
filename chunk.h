#pragma once

#include "ITAG.h"
#include <stdlib.h>
#include <sstream>
#ifdef WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#define _mkdir(x) mkdir(x, 0755)
#endif
extern "C"
{
#include "zlib.h"
}
#define ARRAY_SIZE 16*128*16

inline int mod(int x, int m)
{
	int r = x%m;
	return r<0 ? r+m : r;
}

struct Chunk
{
	int x;
	int z;
	unsigned char blockTypes[ARRAY_SIZE];
	unsigned char metadata[ARRAY_SIZE/2];
	unsigned char blocklight[ARRAY_SIZE/2];
	unsigned char skylight[ARRAY_SIZE/2];
	bool populated;

	Chunk(int _x, int _z)
	{
		populated = false;
		x = _x;
		z = _z;
		next = NULL;
		memset(blockTypes,0,ARRAY_SIZE);
		memset(metadata,0,ARRAY_SIZE/2);
		memset(blocklight,0,ARRAY_SIZE/2);
		memset(skylight,0,ARRAY_SIZE/2);
	}

	~Chunk()
	{
		Save();
	}

	void Save()
	{
		cTAG_Compound *chunk = new cTAG_Compound("Level");
		chunk->add("Blocks", new cTAG_Byte_Array(ARRAY_SIZE,blockTypes));
		chunk->add("Data", new cTAG_Byte_Array(ARRAY_SIZE/2,metadata));
		chunk->add("SkyLight", new cTAG_Byte_Array(ARRAY_SIZE/2,skylight));
		chunk->add("BlockLight", new cTAG_Byte_Array(ARRAY_SIZE/2,blocklight));

		unsigned char *heightmap = new unsigned char[256];

		for(int _x=0;_x<=16;_x++)
		{
			for(int _z=0;_z<=16;_z++)
			{
				for(int _y=128;_y<=0;_y++)
				{
					if(blockTypes[_y + (_z * 128) + (_x * 128 * 16)] !=0)
					{
						heightmap[_x*128+_z] = _y;
						break;
					}
				}
			}
		}

		chunk->add("HeightMap", new cTAG_Byte_Array(256,heightmap));
		chunk->add("Entities", new cTAG_List(eTAG_Compound,0));
		chunk->add("TileEntities", new cTAG_List(eTAG_Compound,0));
		chunk->add("LastUpdate", new cTAG_Long());
		chunk->add("xPos", new cTAG_Int(x));
		chunk->add("zPos", new cTAG_Int(z));
		chunk->add("TerrainPopulated", new cTAG_Byte(populated ? 0 : 1));
		delete heightmap;

		//_mkdir("World");
		char path[256];
		char xMod64[16];
		char zMod64[16];
		char xBase36[16];
		char zBase36[16];
		itoa(mod(x,64),xMod64,36);
		itoa(mod(z,64),zMod64,36);

		itoa(x,xBase36,36);
		itoa(z,zBase36,36);

		_mkdir(worldfolder);

		sprintf(path,"%s/%s",worldfolder,xMod64);
		_mkdir(path);
		sprintf(strchr(path,0),"/%s",zMod64);
		_mkdir(path);
		sprintf(strchr(path,0),"/c.%s%s.%s%s.dat",x<0?"-":"",xBase36,z<0?"-":"",zBase36);

		std::stringstream ss(std::stringstream::in | std::stringstream::out);
		unsigned int c = 0x0A00000A;
		ss.write((char*)&c,4);
		chunk->WriteStream(ss);
		char cend = 0;
		ss.write((char*)&cend,1);

		std::string a = ss.str();
		gzFile fp = gzopen(path,"w");
		gzwrite(fp, a.c_str(),a.length());
		gzclose(fp);

		delete chunk;
	}

	Chunk *next;
};
