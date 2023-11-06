#include "DBA.h"

bool get_hd(Header_A * hda)
{
	if(hda==NULL) return false;
	memcpy((char*)hda,(char*)&HDA,sizeof(Header_A));
	return true;
}

bool get_art(Artykuly * art)
{
	if(art==NULL) return false;
	for(i=0;i<MAX_ART;i++)
	{
		if(ART[i].exist) 
		{
			*art=ART[i];
			art++;
		}
	}
	return true;
}


extern "C" BOOL WINAPI DllMain(HINSTANCE hinst, DWORD res, LPVOID reserved)
{
	switch(res)
	{
		case DLL_PROCESS_ATTACH:
		{
			break;
		}

		case DLL_PROCESS_DETACH:
		{
			break;
		}

		case DLL_THREAD_ATTACH:
		{
			break;
		}

		case DLL_THREAD_DETACH:
		{
			break;
		}

		default: break;
	}
	return true;
}