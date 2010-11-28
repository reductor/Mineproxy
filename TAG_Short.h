#pragma once

#include "ITAG.h"


class cTAG_Short : public ITAG
{
private:
	short data;
public:
	cTAG_Short() : ITAG(eTAG_Short), data(0) {}
	cTAG_Short(short s) : ITAG(eTAG_Short), data(s) {}
	void WriteStream(std::ostream &out)
	{
		int temp = htons(data);
		out.write((char*)&temp,2);
		
	}
	void ReadStream(std::istream &in)
	{
		in.read((char*)&data,2);
		data = ntohs(data);
	}
};
