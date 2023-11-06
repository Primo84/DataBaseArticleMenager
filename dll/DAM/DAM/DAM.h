#include "windows.h"
#include "String"

typedef struct Firma
{
	bool _is;
	char Nazwa[150];
	char Adres[350];
	char Kod_Pocz[25];
	char Miasto[50];
	char Kraj[50];
	char NIP[25];
	char Regon[25];
	char Tel[25];
}FIRMA;



char st[12]="ADAPRIM_A&P";

FIRMA FRM={false,"ADAPRIM_A&P"};


extern "C"
{
	__declspec(dllexport) void get_Firma(char* f);
}