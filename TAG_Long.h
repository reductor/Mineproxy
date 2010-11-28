#pragma once

#include "ITAG.h"


class cTAG_Long : public ITAG
{
private:
	int64_t data;
public:
	cTAG_Long() : ITAG(eTAG_Long), data(0) {}
	cTAG_Long(int64_t l) : ITAG(eTAG_Long), data(l) {}
	void WriteStream(std::ostream &out)
	{
		int64_t temp = htonll(data);
		out.write((char*)&temp,8);
		
	}
	void ReadStream(std::istream &in)
	{
		in.read((char*)&data,8);
		data = ntohll(data);
	}
};
