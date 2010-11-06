#pragma once

#include "ITAG.h"
#include <winsock2.h>

class cTAG_Long : public ITAG
{
private:
	__int64 data;
public:
	cTAG_Long() : ITAG(eTAG_Long), data(0) {}
	cTAG_Long(__int64 l) : ITAG(eTAG_Long), data(l) {}
	void WriteStream(std::ostream &out)
	{
		__int64 temp = htonll(data);
		out.write((char*)&temp,8);
		
	}
	void ReadStream(std::istream &in)
	{
		in.read((char*)&data,8);
		data = ntohll(data);
	}
};
