#pragma once

#include "ITAG.h"
#include <winsock2.h>

class cTAG_List : public ITAG
{
private:
	eTAG_Type listtype;
	int size;
	ITAG **buf;
public:
	cTAG_List() : ITAG(eTAG_List), listtype(eTAG_End), size(0),buf(NULL) {}
	cTAG_List(eTAG_Type _type, int _size) : ITAG(eTAG_List), listtype(_type), size(_size)
	{
		buf = new ITAG*[_size];
	}

	ITAG *operator[](int i)
	{
		return buf[i];
	}

	~cTAG_List()
	{
		if(buf != NULL)
		{
			for(int i=0;i<size;i++)
			{
				delete buf;
			}
			delete[] buf;
		}
		
	}

	void WriteStream(std::ostream &out)
	{
		out.write((char*)&listtype,1);
		int temp = htonl(size);
		out.write((char*)&temp,4);
		for(int i=0;i<size;i++)
		{
			buf[i]->WriteStream(out);
		}
	}
	void ReadStream(std::istream &in)
	{
		in.read((char*)&listtype,1);
		in.read((char*)&size,4);
		size = ntohl(size);
		for(int i=0;i<size;i++)
		{
			buf[i]->ReadStream(in);
		}
	}
};
