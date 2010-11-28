#pragma once

#include "ITAG.h"
#include <map>


#include "TAG_String.h"

class cTAG_Compound : public ITAG
{
private:
	cTAG_String name;
	eTAG_Type listtype;
	std::map<cTAG_String *,ITAG*> buf;
public:
	cTAG_Compound() : ITAG(eTAG_Compound) {}

	cTAG_Compound(const char *str) : ITAG(eTAG_Compound), name(str)
	{
	}

	~cTAG_Compound()
	{
		std::map<cTAG_String*,ITAG*>::iterator it = buf.begin();
		for(;it!=buf.end();it++)
		{
			delete it->first;
			delete it->second;
		}
		buf.clear();
	}

	void add(const char *cstr, ITAG *tag)
	{
		cTAG_String *str = new cTAG_String(cstr);
		buf.insert( std::pair<cTAG_String *,ITAG*>(str,tag) );
	}

	void WriteStream(std::ostream &out)
	{
		name.WriteStream(out);
		std::map<cTAG_String *,ITAG*>::iterator it = buf.begin();
		for(;it!=buf.end();it++)
		{

			unsigned char type = (unsigned char)it->second->GetType();
			out.write((char*)&type,1);

			it->first->WriteStream(out);


			it->second->WriteStream(out);
		}
		char c = eTAG_End;
		out.write((char*)&c,1);
	}
	void ReadStream(std::istream &in)
	{
		name.ReadStream(in);
		std::map<cTAG_String *,ITAG*>::iterator it = buf.begin();
		for(;it!=buf.end();it++)
		{
			delete it->first;
			delete it->second;
		}
		buf.clear();

		ITAG *tag = NULL;

		while(tag == NULL || tag->GetType() != eTAG_End)
		{
			unsigned char type;
			in.read((char*)&type,1);

			if(type == eTAG_End)
				break;

			cTAG_String *name = new cTAG_String();
			name->ReadStream(in);


			tag = TAG_Factory::CreateTag((eTAG_Type)type);
			tag->ReadStream(in);

			buf.insert( std::pair<cTAG_String *,ITAG*>(name,tag) );
		}
	}
};
