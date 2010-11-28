#pragma once

#include "chunk.h"

struct ChunkHashMap
{
	Chunk *chunks[441];
	int numChunks;

	ChunkHashMap()
	{
		numChunks = 0;
		memset(chunks,0,sizeof(chunks));
	}
	
	inline int mod(int x, int m)
	{
		int r = x%m;
		return r<0 ? r+m : r;
	}

	int hash(int x, int z)
	{
		return mod(x,21) + mod(z,21) * 21;
	}

	Chunk *getChunk(int x, int z)
	{
		Chunk *chunk = chunks[hash(x,z)];
		if(chunk == NULL)
			return NULL;

		do
		{
			if(chunk->x == x && chunk->z == z)
				return chunk;

			chunk = chunk->next;
		} while(chunk != NULL);

		return NULL;
	}

	void _delete(int x, int z)
	{
		int _hash = hash(x,z);

		Chunk *chunk = chunks[_hash];
		if(chunk == NULL)
			return;

		if(chunk->x == x && chunk->z == z)
		{
			chunks[_hash] = chunk->next;
			delete chunk;
		}
		else
		{
			Chunk *prev = chunk;
			chunk = chunk->next;
			while(chunk != NULL)
			{
				if(chunk->x == x && chunk->z == z)
					break;

				prev = chunk;
				chunk = chunk->next;
			}

			if(chunk != NULL)
			{
				prev->next = chunk->next;
				delete chunk;
			}
		}
	}


	void insert(Chunk *_chunk, int x, int z)
	{
		numChunks++;
		int _hash = hash(x,z);
		if(chunks[_hash] == NULL)
		{
			chunks[_hash] = _chunk;
			return;
		}
		else
		{
			Chunk *chunk = chunks[_hash];
			while(chunk->next != NULL)
				chunk = chunk->next;
			chunk->next = _chunk;
		}
	}

	void clear()
	{
		for(int i=0;i<441;i++)
		{
			Chunk *chunk = chunks[i];
			while(chunk != NULL)
			{
				Chunk *temp = chunk->next;
				delete chunk;
				chunk = temp;
			}
			chunks[i] = NULL;
		}
		numChunks = 0;
	}
};
