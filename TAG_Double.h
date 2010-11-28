#pragma once

#include "ITAG.h"


class cTAG_Double : public ITAG
{
private:
	double data;
public:
	cTAG_Double() : ITAG(eTAG_Double), data(0) {}
	cTAG_Double(double d) : ITAG(eTAG_Double), data(d) {}
	void WriteStream(std::ostream &out)
	{
		unsigned long long temp = *reinterpret_cast<unsigned long long*>(&data);
		temp = htonll(temp);
		out.write((char*)&temp,8);
	}
	void ReadStream(std::istream &in)
	{
		unsigned long long temp;
		in.read((char*)&temp,8);
		temp = ntohll(temp);
		data = *reinterpret_cast<double *>(&temp);
	}
};
