#include "windows.h"

struct COUNT
{
	BYTE walcnt;
	BYTE fzapcnt;
};

struct WALUTA
{
	char naz[25];
	char znak[25];
};

struct FORM_ZAP
{
	char naz[25];
	char opis[350];
};

char zn1[12]="ADAPRIM_321";
COUNT cnt={3,2};
char zn2[13]="ADAPRIM_1234";
WALUTA wal[15]={
					{"PLN","z³"},{"EURO","€"},{"DOLAR","$"},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},
					{"",""},{"",""},{"",""},{"",""},{"",""},{"",""}
				};
char zn3[13]="ADAPRIM_5678";
FORM_ZAP formzap[15]={
						{"Gotówka",""},{"Przelew","Przelwe na rachunek bankowy"},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},
						{"",""},{"",""},{"",""},{"",""},{"",""}
					};


int i;

extern "C"
{

	__declspec(dllexport) COUNT wal_cnt();
	__declspec(dllexport) bool get_wal(WALUTA * wal);
	__declspec(dllexport) bool get_formzap(FORM_ZAP * frmzap); 
}