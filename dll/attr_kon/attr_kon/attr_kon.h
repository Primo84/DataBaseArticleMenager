#include "windows.h"



typedef struct COUNT
{
	BYTE walcnt;
	BYTE fzapcnt;
	BYTE vatcnt;
	BYTE jmcnt;
	BYTE grcnt;
	BYTE def_wal;
	BYTE def_form_zap;
	BYTE def_vat;
	BYTE def_jm;
	BYTE def_gr;
};

typedef struct GR_T
{
	char nazwa[50];
};
typedef struct N_VAT
{
	char przed[8];
	bool is_;
};

typedef struct ST_VAT
{
	float vat;
	char opis[100];
};

typedef struct WALUTA
{
	char naz[25];
	char znak[25];
};

typedef struct JM
{
	char naz[25];
	char znak[25];
};

typedef struct FORM_ZAP
{
	char naz[25];
	char opis[350];
};

char zn1[12]="ADAPRIM_321";
COUNT cnt={3,2,4,7,2,0,0,0,0,0};
char zn2[13]="ADAPRIM_1234";
WALUTA wal[99]={
					{"PLN","z�"},{"EURO","�"},{"DOLAR","$"},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},
					{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},
					{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},
					{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},
					{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},
					{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},
					{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},
					{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},
					{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},
					{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""}
				};
char zn3[13]="ADAPRIM_5678";
FORM_ZAP formzap[99]={
						{"Got�wka",""},{"Przelew","Przelwe na rachunek bankowy"},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},
						{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},
						{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},
						{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},
						{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},
						{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},
						{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},
						{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},
						{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},
						{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""}
					};



char zn4[13]="ADAPRIM_8765";
ST_VAT VAT[99]={
						{23,"Stawka podstawowa"},{8,"Stawka obni�ona"},{5,"Stawka obni�ona"},{0,"Zwolniona z podatku"},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},
						{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},
						{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},
						{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},
						{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},
						{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},
						{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},
						{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},
						{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},
						{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""},{-1,""}

					};


char zn5[13]="ADAPRIM_2685";
JM jm[99]={
					{"Sztuka","szt"},{"Opakowanie","op"},{"Kilogram","kg"},{"Gramy","gr"},{"Litry","l"},{"Metry","m"},{"Centymetry","cm"},{"",""},{"",""},{"",""},
					{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},
					{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},
					{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},
					{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},
					{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},
					{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},
					{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},
					{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},
					{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""}
				};


char zn6[13]="ADAPRIM_4167";
GR_T gr[99]={
					{"TOWAR"},{"US�UGA",},{"",},{"",},{""},{""},{""},{""},{""},{""},
					{""},{""},{""},{""},{""},{""},{""},{""},{""},{""},
					{""},{""},{""},{""},{""},{""},{""},{""},{""},{""},
					{""},{""},{""},{""},{""},{""},{""},{""},{""},{""},
					{""},{""},{""},{""},{""},{""},{""},{""},{""},{""},
					{""},{""},{""},{""},{""},{""},{""},{""},{""},{""},
					{""},{""},{""},{""},{""},{""},{""},{""},{""},{""},
					{""},{""},{""},{""},{""},{""},{""},{""},{""},{""},
					{""},{""},{""},{""},{""},{""},{""},{""},{""},{""},
					{""},{""},{""},{""},{""},{""},{""},{""},{""}
				};


char zn7[13]="ADAPRIM_1001";
N_VAT NV={"",-1};

int i;

extern "C"
{

	__declspec(dllexport) bool wal_cnt(COUNT * count);
	__declspec(dllexport) bool get_wal(WALUTA * wal);
	__declspec(dllexport) bool get_formzap(FORM_ZAP * frmzap); 
	__declspec(dllexport) bool get_vat(ST_VAT * vat);
	__declspec(dllexport) bool get_jm(JM * miar);
	__declspec(dllexport) bool get_NV(N_VAT * nv);
	__declspec(dllexport) bool get_gr(GR_T *gr);
}

