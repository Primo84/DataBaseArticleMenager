
#include "windows.h"
#include "stdio.h"



const int MAX=30;

	//Struktura zarejestrowanej kasy fiskalnej

typedef struct 
{
	char nazwa[50];
	char numer[50];
	int Com;
	int Szybk;
	char IP[50];
	int port;
	int rodz_pol;
	int kanal;
	int timeout;
	char RU[50];
	int  PT;
	char tel[50];
	char haslo[50];
	int AT;
	int T1;
	int ret;
	bool is_exist;
	char end_str[13];

}KASA_;

int i;

char st[13]="ADAPRIM_1234";

int Count=-1;

int Default=-1;

KASA_ KAS1={"N","X1",-1,-1,"non",-1,-1,0,-1,"XX",0,"XXX","XXXX",-1,-1,-1,false,"ADAPRIM_4321"};
KASA_ KAS2={"N","X2",-1,-1,"non",-1,-1,0,-1,"XX",0,"XXX","XXXX",-1,-1,-1,false,"ADAPRIM_4321"};
KASA_ KAS3={"N","X3",-1,-1,"non",-1,-1,0,-1,"XX",0,"XXX","XXXX",-1,-1,-1,false,"ADAPRIM_4321"};
KASA_ KAS4={"N","X4",-1,-1,"non",-1,-1,0,-1,"XX",0,"XXX","XXXX",-1,-1,-1,false,"ADAPRIM_4321"};
KASA_ KAS5={"N","X5",-1,-1,"non",-1,-1,0,-1,"XX",0,"XXX","XXXX",-1,-1,-1,false,"ADAPRIM_4321"};
KASA_ KAS6={"N","X6",-1,-1,"non",-1,-1,0,-1,"XX",0,"XXX","XXXX",-1,-1,-1,false,"ADAPRIM_4321"};
KASA_ KAS7={"N","X7",-1,-1,"non",-1,-1,0,-1,"XX",0,"XXX","XXXX",-1,-1,-1,false,"ADAPRIM_4321"};
KASA_ KAS8={"N","X8",-1,-1,"non",-1,-1,0,-1,"XX",0,"XXX","XXXX",-1,-1,-1,false,"ADAPRIM_4321"};
KASA_ KAS9={"N","X9",-1,-1,"non",-1,-1,0,-1,"XX",0,"XXX","XXXX",-1,-1,-1,false,"ADAPRIM_4321"};
KASA_ KAS10={"N","X10",-1,-1,"non",-1,-1,0,-1,"XX",0,"XXX","XXXX",-1,-1,-1,false,"ADAPRIM_4321"};
KASA_ KAS11={"N","X11",-1,-1,"non",-1,-1,0,-1,"XX",0,"XXX","XXXX",-1,-1,-1,false,"ADAPRIM_4321"};
KASA_ KAS12={"N","X12",-1,-1,"non",-1,-1,0,-1,"XX",0,"XXX","XXXX",-1,-1,-1,false,"ADAPRIM_4321"};
KASA_ KAS13={"N","X13",-1,-1,"non",-1,-1,0,-1,"XX",0,"XXX","XXXX",-1,-1,-1,false,"ADAPRIM_4321"};
KASA_ KAS14={"N","X14",-1,-1,"non",-1,-1,0,-1,"XX",0,"XXX","XXXX",-1,-1,-1,false,"ADAPRIM_4321"};
KASA_ KAS15={"N","X15",-1,-1,"non",-1,-1,0,-1,"XX",0,"XXX","XXXX",-1,-1,-1,false,"ADAPRIM_4321"};
KASA_ KAS16={"N","X16",-1,-1,"non",-1,-1,0,-1,"XX",0,"XXX","XXXX",-1,-1,-1,false,"ADAPRIM_4321"};
KASA_ KAS17={"N","X17",-1,-1,"non",-1,-1,0,-1,"XX",0,"XXX","XXXX",-1,-1,-1,false,"ADAPRIM_4321"};
KASA_ KAS18={"N","X18",-1,-1,"non",-1,-1,0,-1,"XX",0,"XXX","XXXX",-1,-1,-1,false,"ADAPRIM_4321"};
KASA_ KAS19={"N","X19",-1,-1,"non",-1,-1,0,-1,"XX",0,"XXX","XXXX",-1,-1,-1,false,"ADAPRIM_4321"};
KASA_ KAS20={"N","X20",-1,-1,"non",-1,-1,0,-1,"XX",0,"XXX","XXXX",-1,-1,-1,false,"ADAPRIM_4321"};
KASA_ KAS21={"N","X21",-1,-1,"non",-1,-1,0,-1,"XX",0,"XXX","XXXX",-1,-1,-1,false,"ADAPRIM_4321"};
KASA_ KAS22={"N","X22",-1,-1,"non",-1,-1,0,-1,"XX",0,"XXX","XXXX",-1,-1,-1,false,"ADAPRIM_4321"};
KASA_ KAS23={"N","X23",-1,-1,"non",-1,-1,0,-1,"XX",0,"XXX","XXXX",-1,-1,-1,false,"ADAPRIM_4321"};
KASA_ KAS24={"N","X24",-1,-1,"non",-1,-1,0,-1,"XX",0,"XXX","XXXX",-1,-1,-1,false,"ADAPRIM_4321"};
KASA_ KAS25={"N","X25",-1,-1,"non",-1,-1,0,-1,"XX",0,"XXX","XXXX",-1,-1,-1,false,"ADAPRIM_4321"};
KASA_ KAS26={"N","X26",-1,-1,"non",-1,-1,0,-1,"XX",0,"XXX","XXXX",-1,-1,-1,false,"ADAPRIM_4321"};
KASA_ KAS27={"N","X27",-1,-1,"non",-1,-1,0,-1,"XX",0,"XXX","XXXX",-1,-1,-1,false,"ADAPRIM_4321"};
KASA_ KAS28={"N","X28",-1,-1,"non",-1,-1,0,-1,"XX",0,"XXX","XXXX",-1,-1,-1,false,"ADAPRIM_4321"};
KASA_ KAS29={"N","X29",-1,-1,"non",-1,-1,0,-1,"XX",0,"XXX","XXXX",-1,-1,-1,false,"ADAPRIM_4321"};
KASA_ KAS30={"N","X30",-1,-1,"non",-1,-1,0,-1,"XX",0,"XXX","XXXX",-1,-1,-1,false,"ADAPRIM_4321"};

HINSTANCE hs;



extern "C"
{
	__declspec(dllexport) int get_Count();
	__declspec(dllexport) int get_Max();
	__declspec(dllexport) int get_Kas(KASA_ *kas, int id);
	__declspec(dllexport) int get_All(KASA_ *KAS, int count);
	__declspec(dllexport) int get_First();
	__declspec(dllexport) int get_Default();
}

