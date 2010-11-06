#pragma once

#include "ITAG.h"
#include <winsock2.h>

class cTAG_Float : public ITAG
{
private:
	float data;
public:
	cTAG_Float() : ITAG(eTAG_Float), data(0) {}
	cTAG_Float(float f) : ITAG(eTAG_Float), data(f) {}
	void WriteStream(std::ostream &out)
	{
		unsigned int temp = *reinterpret_cast<unsigned int*>(&data);
		temp = htonl(temp);
		out.write((char*)&temp,4);
	}
	void ReadStream(std::istream &in)
	{
		unsigned int temp;
		in.read((char*)&temp,4);
		temp = ntohl(temp);
		data = *reinterpret_cast<float *>(&temp);
	}
};
