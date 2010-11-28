#pragma once

#include "ITAG.h"


class cTAG_String : public ITAG
{
private:
	short size;
	char *buf;
public:
	cTAG_String() : ITAG(eTAG_String), size(0),buf(NULL) {}
	cTAG_String(int _size, char *_buf) : ITAG(eTAG_String), size(_size)
	{
		buf = new char[size];
		memcpy(buf,_buf,size);
	}

	cTAG_String(const char *_buf) : ITAG(eTAG_String)
	{
		size = strlen(_buf);
		buf = new char[size];
		memcpy(buf,_buf,size);
	}
	~cTAG_String()
	{
		delete[] buf;
	}

	void WriteStream(std::ostream &out)
	{
		int temp = htons(size);
		out.write((char*)&temp,2);
		if(buf != NULL && size != 0)
		out.write(buf,size);
	}
	void ReadStream(std::istream &in)
	{
		if(buf != NULL)
			delete[] buf;

		in.read((char*)&size,2);
		size = ntohs(size);

		buf = new char[size+1];
		in.read(buf,size);
		buf[size] = 0;
	}
};
