#include "DBA_U.h"





int WINAPI WinMain(HINSTANCE hinst, HINSTANCE prev,LPSTR cmd_code, int cmd_show)
{
	MSG msg;

	hst=hinst;
	bl=false;
	if(MessageBox(NULL,"Czy napewno chcesz odinstalowaæ program ?","",MB_YESNO)==IDNO) 
		return 0;
	if(MessageBox(NULL,"Czy chcesz usun¹æ tak¿e pliki z baz¹ danych ?","",MB_YESNO)==IDYES) 
		bl=true;

	DialogBox(hinst,MAKEINTRESOURCE(DLG),NULL,(DLGPROC)&DLGProc);

	
	return 0;
}