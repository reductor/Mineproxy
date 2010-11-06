#pragma once

#include "ITAG.h"

class cTAG_End : public ITAG
{
public:
	cTAG_End() : ITAG(eTAG_End) {}
	void WriteStream(std::ostream &out) {};
	void ReadStream(std::istream &in) {};
};
