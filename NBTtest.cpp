/*#include <winsock2.h>
#include "protocol.h"
#include "ITAG.h"
#include <fstream>

inline int mod(int x, int m) {
    int r = x%m;
    return r<0 ? r+m : r;
}

void TestNBT()
{
	for(int i=-11;i<11;i++)
	{
		printf("%d mod 21 = %d\n",i,mod(i,21)); 
	}
	std::ifstream strm;
	strm.open("test.schematic", std::ios_base::in);
	if(strm.is_open())
	{
		char check;
		strm.read((char*)&check,1);
		if(check != 0x0A)
			__asm int 3
		cTAG_Compound *compound = new cTAG_Compound();
		compound->ReadStream(strm);
		strm.close();
	}
	//compound
	__asm int 3
}*/