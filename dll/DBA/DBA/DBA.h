#include "windows.h"

const int MAX_ART=100000;

typedef struct Header_A
{
	int del_cnt;
	int LastID;
	int count;
	int deli[MAX_ART];
};

typedef struct Artykuly
{
	char Nazwa[350];
	char Producent[350];
	float Stan;
	char JM[25];
	char Grupa[50];
	double Cena_Zakupu;
	float Marza;
	double Cena_Netto;
	float VAT;
	double Cena_Brutto;
	int Stan_Kr;
	char KOD_TOW[35];
	char KOD_KR[35];
	char Num_Fakt[35];
	int IDA;
	int IDP;
	int indeks;
	bool is_wylznr;
	bool is_blok;
	bool is_list;
	bool is_op;
	bool is_cena;
	bool exist;
};


char zn[13]="ADAPRIM_1234";

Header_A HDA={0,0,0,{-1}};

char zn1[13]="ADAPRIM_4321";
Artykuly ART[MAX_ART]={"XXX","XXX",0,"XXX","XXX",0,0,0,0,0,0,"XXX","XXX","XXX",0,0,-1,false,false,false,false,false,false};


int i;

extern "C"
{
	__declspec(dllexport) bool get_hd(Header_A * hda);
	__declspec(dllexport) bool get_art(Artykuly * art);
}
