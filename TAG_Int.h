#pragma once

#include "ITAG.h"
#include <winsock2.h>

class cTAG_Int : public ITAG
{
private:
	int data;
public:
	cTAG_Int() : ITAG(eTAG_Int), data(0) {}
	cTAG_Int(int i) : ITAG(eTAG_Int), data(i) {}
	void WriteStream(std::ostream &out)
	{
		int temp = htonl(data);
		out.write((char*)&temp,4);
	}
	void ReadStream(std::istream &in)
	{
		in.read((char*)&data,4);
		data = ntohl(data);
	}
};
