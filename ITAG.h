#pragma once

#include <iostream>

enum eTAG_Type
{
	eTAG_End,
	eTAG_Byte,
	eTAG_Short,
	eTAG_Int,
	eTAG_Long,
	eTAG_Float,
	eTAG_Double,
	eTAG_Byte_Array,
	eTAG_String,
	eTAG_List,
	eTAG_Compound
};

class ITAG
{
protected:
	eTAG_Type type;
public:
	ITAG(eTAG_Type _type)
	{
		type = _type;
	}
	virtual ~ITAG() {};
	eTAG_Type GetType() { return type; }
	virtual void WriteStream(std::ostream &out) = 0;
	virtual void ReadStream(std::istream &in) = 0;
};

class TAG_Factory
{
public:
	static ITAG *CreateTag(eTAG_Type tag);
};

#include "TAG_End.h"
#include "TAG_Byte.h"
#include "TAG_Short.h"
#include "TAG_Int.h"
#include "TAG_Long.h"
#include "TAG_Float.h"
#include "TAG_Double.h"
#include "TAG_Byte_Array.h"
#include "TAG_String.h"
#include "TAG_List.h"
#include "TAG_Compound.h"

ITAG *TAG_Factory::CreateTag(eTAG_Type tag)
{
	if(tag == eTAG_End)
		return new cTAG_End();
	else if(tag == eTAG_Byte)
		return new cTAG_Byte();
	else if(tag == eTAG_Short)
		return new cTAG_Short();
	else if(tag == eTAG_Int)
		return new cTAG_Int();
	else if(tag == eTAG_Long)
		return new cTAG_Long();
	else if(tag == eTAG_Byte_Array)
		return new cTAG_Byte_Array();
	else if(tag == eTAG_String)
		return new cTAG_String();
	else if(tag == eTAG_List)
		return new cTAG_List();
	else if(tag == eTAG_Compound)
		return new cTAG_Compound();
	else
		return new cTAG_End();
}
