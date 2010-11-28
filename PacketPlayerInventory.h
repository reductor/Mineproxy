#pragma once


#include "Packet.h"
#include "protocol.h"

class Packet_PlayerInventory : public Packet
{
private:
	int type;
	short count;

	struct Item
	{
		short itemid;
		char count;
		short health;
	};

	Item *items;

public:
	Packet_PlayerInventory() : type(0),count(0),items(NULL) {}

	~Packet_PlayerInventory()
	{
		delete items;
	}

	bool ReadPacket(SOCKET s)
	{
		type = ReadInt(s);
		count = ReadShort(s);

		items = new Item[count];

		for(int i=0;i<count;i++)
		{
			items[i].itemid = ReadShort(s);

			if(items[i].itemid != -1)
			{
				items[i].count = ReadByte(s);
				items[i].health = ReadShort(s);
			}
		}
		return true;
	}

	void WritePacket(SOCKET s)
	{
		WriteInt(s,type);
		WriteShort(s,count);

		for(int i=0;i<count;i++)
		{
			WriteShort(s,items[i].itemid);
			if(items[i].itemid != -1)
			{
				WriteByte(s,items[i].count);
				WriteShort(s,items[i].health);
			}
		}

	}

	void Print(FILE *fp)
	{
		fprintf(fp, "PlayerInventory( type = %d, count = %d )",
			type, (int)count);
	}
};

REGISTER_PACKET(PlayerInventory);
