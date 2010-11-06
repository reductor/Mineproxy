#pragma once

#include "ITAG.h"

class cTAG_Byte : public ITAG
{
private:
	char data;
public:
	cTAG_Byte() : ITAG(eTAG_Byte), data(0) {}
	cTAG_Byte(char _data) : ITAG(eTAG_Byte), data(_data) {}
	void WriteStream(std::ostream &out)
	{
		out.write((char*)&data,1);
	}
	void ReadStream(std::istream &in)
	{
		in.read((char*)&data,1);
	}
};
