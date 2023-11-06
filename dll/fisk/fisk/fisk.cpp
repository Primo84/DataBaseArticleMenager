
#include "fisk.h"


__declspec(dllexport) int get_Count()
{
	return Count;
}

__declspec(dllexport) int get_Max()
{
	return MAX;
}

__declspec(dllexport) int get_Kas(KASA_ *kas, int id)
{
	if(kas==NULL) return -1;
	if (id<1||id>MAX) return 0;
	
	if(id==1) {memcpy(kas,&KAS1,sizeof(KASA_)); return 1;}
	if(id==2) {memcpy(kas,&KAS2,sizeof(KASA_)); return 1;}
	if(id==3) {memcpy(kas,&KAS3,sizeof(KASA_)); return 1;}
	if(id==4) {memcpy(kas,&KAS4,sizeof(KASA_)); return 1;}
	if(id==5) {memcpy(kas,&KAS5,sizeof(KASA_)); return 1;}
	if(id==6) {memcpy(kas,&KAS6,sizeof(KASA_)); return 1;}
	if(id==7) {memcpy(kas,&KAS7,sizeof(KASA_)); return 1;}
	if(id==8) {memcpy(kas,&KAS8,sizeof(KASA_)); return 1;}
	if(id==9) {memcpy(kas,&KAS9,sizeof(KASA_)); return 1;}
	if(id==10) {memcpy(kas,&KAS10,sizeof(KASA_)); return 1;}
	if(id==11) {memcpy(kas,&KAS10,sizeof(KASA_)); return 1;}
	if(id==12) {memcpy(kas,&KAS12,sizeof(KASA_)); return 1;}
	if(id==13) {memcpy(kas,&KAS13,sizeof(KASA_)); return 1;}
	if(id==14) {memcpy(kas,&KAS14,sizeof(KASA_)); return 1;}
	if(id==15) {memcpy(kas,&KAS15,sizeof(KASA_)); return 1;}
	if(id==16) {memcpy(kas,&KAS16,sizeof(KASA_)); return 1;}
	if(id==17) {memcpy(kas,&KAS17,sizeof(KASA_)); return 1;}
	if(id==18) {memcpy(kas,&KAS18,sizeof(KASA_)); return 1;}
	if(id==19) {memcpy(kas,&KAS19,sizeof(KASA_)); return 1;}
	if(id==20) {memcpy(kas,&KAS20,sizeof(KASA_)); return 1;}
	if(id==21) {memcpy(kas,&KAS21,sizeof(KASA_)); return 1;}
	if(id==22) {memcpy(kas,&KAS22,sizeof(KASA_)); return 1;}
	if(id==23) {memcpy(kas,&KAS23,sizeof(KASA_)); return 1;}
	if(id==24) {memcpy(kas,&KAS24,sizeof(KASA_)); return 1;}
	if(id==25) {memcpy(kas,&KAS25,sizeof(KASA_)); return 1;}
	if(id==26) {memcpy(kas,&KAS26,sizeof(KASA_)); return 1;}
	if(id==27) {memcpy(kas,&KAS27,sizeof(KASA_)); return 1;}
	if(id==28) {memcpy(kas,&KAS28,sizeof(KASA_)); return 1;}
	if(id==29) {memcpy(kas,&KAS29,sizeof(KASA_)); return 1;}
	if(id==30) {memcpy(kas,&KAS30,sizeof(KASA_)); return 1;}
	return 1;
}

__declspec(dllexport) int get_All(KASA_ *KAS, int count)
{
	int l;

	if(KAS==NULL) return -1;
	if(count>MAX) return 0;
	for(i=0;i<MAX;i++)
	{
		l=get_Kas(KAS+i,i+1);
		if(l!=1) return -2;
	}
	return 1;
}

__declspec(dllexport) int get_First()
{
	bool bl;
	KASA_ K;

	i=0;
	bl=false;
	do
	{
		i++;
		get_Kas(&K,i);
		if(K.is_exist) bl=true; 
	}while(!bl);
	if(i>MAX) return 0; else return i;
}

__declspec(dllexport) int get_Default()
{
	return Default;
}

BOOL APIENTRY DllMain(HINSTANCE hst, DWORD reson, LPVOID reserved)
{
	int i;
	switch(reson)
	{
		
		case DLL_PROCESS_ATTACH:
			{
				hs=hst;
				Default=Default;
				Count=Count;
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
	}

	return true;
}