#pragma once

#include "ITAG.h"


class cTAG_Byte_Array : public ITAG
{
private:
	int size;
	unsigned char *buf;
public:
	cTAG_Byte_Array() : ITAG(eTAG_Byte_Array), size(0),buf(NULL) {}
	cTAG_Byte_Array(int _size, unsigned char *_buf) : ITAG(eTAG_Byte_Array)
	{
		size = _size;
		buf = new unsigned char[size];
		memcpy(buf,_buf,_size);
	}

	~cTAG_Byte_Array()
	{
		delete[] buf;
	}

	void WriteStream(std::ostream &out)
	{
		int temp = htonl(size);
		out.write((char*)&temp,4);
		if(buf != NULL && size != 0)
		out.write((char*)buf,size);
	}
	void ReadStream(std::istream &in)
	{
		if(buf != NULL)
			delete[] buf;

		in.read((char*)&size,4);
		size = ntohl(size);

		buf = new unsigned char[size];
		in.read((char*)buf,size);
	}
};

