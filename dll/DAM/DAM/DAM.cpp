#include "DAM.h"


void get_Firma(char* f)
{
	memcpy(f,&FRM,sizeof(FIRMA));
}


extern "C" BOOL WINAPI DllMain(HINSTANCE hst, DWORD reason, LPVOID reserved)
{
	switch(reason)
	{
		case DLL_PROCESS_ATTACH:
			{	
				
				break;
			}
		case DLL_THREAD_ATTACH:
			{
				
				break;
			}
		default: break;
	}
	return true;
}