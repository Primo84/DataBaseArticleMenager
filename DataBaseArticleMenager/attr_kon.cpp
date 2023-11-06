#include "attr_kon.h"


bool wal_cnt(COUNT * count)
{
	if(count==NULL) return false;
	memcpy(count,&cnt,sizeof(COUNT));
	return true;
}

bool get_gr(GR_T * grt)
{
	if(gr==NULL) return false;
	for(i=0;i<15;i++) grt[i]=gr[i];
	return true;
}


bool get_vat(ST_VAT * vat)
{
	if(vat==NULL) return false;
	for(i=0;i<15;i++) vat[i]=VAT[i];
	return true;
}

bool get_wal(WALUTA * waluta)
{
	if(waluta==NULL) return false;
	for(i=0;i<15;i++) waluta[i]=wal[i];
	return true;
}


bool get_formzap(FORM_ZAP * frmzap)
{
	if(frmzap==NULL) return false;
	for(i=0;i<15;i++) frmzap[i]=formzap[i];
	return true;
}


bool get_jm(JM * miar)
{
	if(miar==NULL) return false;
	for(i=0;i<15;i++) miar[i]=jm[i];
	return true;
}

bool get_NV(N_VAT * nv)
{
	if(nv==NULL) return false;
	memcpy((char*)nv,(char*)&NV,sizeof(N_VAT));
	return true;
}

extern "C" BOOL WINAPI DllMain(HINSTANCE hst, DWORD reson, LPVOID reserv)
{
	switch(reson)
	{
		case DLL_PROCESS_ATTACH:
			{

				break;
			}
		case DLL_THREAD_ATTACH:
			{
				break;
			}
		case DLL_PROCESS_DETACH:
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