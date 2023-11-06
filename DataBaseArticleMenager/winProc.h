
#include "windows.h"
#include "Checkbox.h"
#include "resource.h"
#include "fstream"
#include "windowsx.h"
#include "time.h"


HMODULE WINIP_M;


using namespace std;

 unsigned char (*_ZRKasjer)(char* in);
 unsigned char (*_ORKasjer)(char* in, char* out);
 unsigned char (*_ORodzKas)(char* in, char* out);
 unsigned char (*_ZRodzKas)(char* in);
 unsigned char (*_DrukRap)(char* in, char* out);
 unsigned char (*_DrukRapD)(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _KDBarkod(char* in);
 unsigned char __declspec(dllimport) _cdecl _KDBarMax(char* in);
 unsigned char __declspec(dllimport) _cdecl _KDefKlaw(char* in);
 unsigned char __declspec(dllimport) _cdecl _KDefKMax(char* in);
 unsigned char __declspec(dllimport) _cdecl _KEStDef(char* in);
 unsigned char __declspec(dllimport) _cdecl _KEStDMax(char* in);
 unsigned char __declspec(dllimport) _cdecl _KEStTMax(char* in);
 unsigned char __declspec(dllimport) _cdecl _KEStTow(char* in);
 unsigned char __declspec(dllimport) _cdecl _KGrupa(char* in);
 unsigned char __declspec(dllimport) _cdecl _KGrupMax(char* in);
 unsigned char (*_KKasjer)(char* in);
 unsigned char __declspec(dllimport) _cdecl _KKlawisz(char* in);
 unsigned char __declspec(dllimport) _cdecl _KSDBaMax(char* in);
 unsigned char __declspec(dllimport) _cdecl _KSprawdz(char* in);
 unsigned char __declspec(dllimport) _cdecl _KSprOp(char* in);
 unsigned char __declspec(dllimport) _cdecl _KSTowar(char* in);
 unsigned char __declspec(dllimport) _cdecl _KSTowMax(char* in);
 unsigned char __declspec(dllimport) _cdecl _KSzufMax(char* in);
 unsigned char __declspec(dllimport) _cdecl _KTBarkod(char* in);
 unsigned char (*_KTowar)(char* in);
 unsigned char __declspec(dllimport) _cdecl _KTowMax(char* in);
 unsigned char __declspec(dllimport) _cdecl _KTWaga(char* in);
 unsigned char __declspec(dllimport) _cdecl _KTWagMax(char* in);
 unsigned char __declspec(dllimport) _cdecl _KuchDruk(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _KWaluta(char* in);
 unsigned char __declspec(dllimport) _cdecl _KWiaz(char* in);
 unsigned char __declspec(dllimport) _cdecl _ModHaslo(char* in);
 unsigned char __declspec(dllimport) _cdecl _ModIlDzw(char* in);
 unsigned char __declspec(dllimport) _cdecl _ModNrWer(char* in, char* out);
 unsigned char (*_ModStart)(char* in);
 unsigned char (*_ModStop)(char* in);
 unsigned char __declspec(dllimport) _cdecl _OBajtMax(char* in, char* out);
 unsigned char (*_OBajty)(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OBarPods(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OBarTow(char* in, char* out);
 unsigned char (*_ODaneARG)(char* in, char* out);
 unsigned char (*_ODanePRG)(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _ODaneRek(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _ODaneUz(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _ODataARG(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _ODataPRG(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _ODBajty(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _ODBarkod(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _ODefKlaw(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _ODKBajty(char* in, char* out);
 unsigned char (*_ODNBajty)(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _ODSprzed(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OEStDef(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OEStDMax(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OEStTMax(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OEStTow(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OEtyk(char* in, char* out);
 unsigned char (*_OGrupa)(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OHalo(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OIKas(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OIKasOtw(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OIKasWla(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OIKasZam(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OIKasZZ(char* in, char* out);
 unsigned char (*_OIlZaPLU)(char* in, char* out);
 unsigned char (*_OJednost)(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OKartRab(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OKasjer(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OKlawisz(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OKRabMax(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OKSprzed(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OLinia(char* in, char* out);
 unsigned char (*_ONarzut)(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _ONKasWla(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _ONNazwa(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _ONrDodPa(char* in, char* out);
 unsigned char (*_ONrKasy)(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _ONrParag(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _ONrRap(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _ONrRekor(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _ONrSpraw(char* in, char* out);
 unsigned char (*_ONrTowar)(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _ONrUnik(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OObrRab(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OOpak(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OOSprzed(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OPBarkod(char* in, char* out);
 unsigned char (*_OPlat)(char* in, char* out);
 unsigned char (*_OPodatek)(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OPojemn(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OPSpRoz(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OPSpRozN(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OPSpRozX(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OPSprzed(char* in, char* out);
 unsigned char (*_ORabat)(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _ORabNPod(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OSBajty(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OSJednos(char* in, char* out);
 unsigned char (*_OSpOpMax)(char* in);
 unsigned char __declspec(dllimport) _cdecl _OSprzed(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OSprzPod(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OSPBarko(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OSReklam(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OStatus(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OSTowar(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OSTowMax(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OSygPara(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OSzufMax(char* in, char* out);
 unsigned char (*_OTowar)(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OTPojemn(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OTSpMax(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OTSprzed(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OTWaga(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OTWagMax(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OTypUrz(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OUprKas(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OWaluta(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OWersja(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OWiaz(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OWiersz(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _OZegar(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _Paker(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _PoSekwSt(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _PoslPlik(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _RekorMax(char* in, char* out);
 unsigned char (*_RSTest)(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _Sorter(char* in);
 unsigned char __declspec(dllimport) _cdecl _SortPak(char* in, char* out);
 unsigned char  (*_TowarMax)(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _WyplGot(char* in);
 unsigned char __declspec(dllimport) _cdecl _ZBajtMax(char* in);
 unsigned char (*_ZBajty)(char* in);
 unsigned char __declspec(dllimport) _cdecl _ZBlok(char* in);
 unsigned char __declspec(dllimport) _cdecl _ZBPTowar(char* in, char* out);
 unsigned char __declspec(dllimport) _cdecl _ZCTowar(char* in);
 unsigned char __declspec(dllimport) _cdecl _ZDataAkt(char* in);
 unsigned char __declspec(dllimport) _cdecl _ZDBajty(char* in);
 unsigned char __declspec(dllimport) _cdecl _ZDBarkod(char* in);
 unsigned char __declspec(dllimport) _cdecl _ZDefKlaw(char* in);
 unsigned char __declspec(dllimport) _cdecl _ZDKBajty(char* in);
 unsigned char __declspec(dllimport) _cdecl _ZDNBajty(char* in);
 unsigned char __declspec(dllimport) _cdecl _ZDSprzed(char* in);
 unsigned char __declspec(dllimport) _cdecl _ZEStDef(char* in);
 unsigned char __declspec(dllimport) _cdecl _ZEStTow(char* in);
 unsigned char (*_ZGrupa)(char* in);
 unsigned char __declspec(dllimport) _cdecl _ZHalo(char* in);
 unsigned char (*_ZJednost)(char* in);
 unsigned char __declspec(dllimport) _cdecl _ZKartRab(char* in);
 unsigned char __declspec(dllimport) _cdecl _ZKasjer(char* in);
 unsigned char __declspec(dllimport) _cdecl _ZKlawisz(char* in);
 unsigned char __declspec(dllimport) _cdecl _ZKRabMax(char* in);
 unsigned char __declspec(dllimport) _cdecl _ZLinia(char* in);
 unsigned char (*_ZNarzut)(char* in);
 unsigned char (*_ZNrKasy)(char* in);
 unsigned char __declspec(dllimport) _cdecl _ZNrDodPa(char* in);
 unsigned char __declspec(dllimport) _cdecl _ZNrSpraw(char* in);
 unsigned char __declspec(dllimport) _cdecl _ZPBarkod(char* in);
 unsigned char (*_ZPlat)(char* in);
 unsigned char __declspec(dllimport) _cdecl _ZPojemn(char* in);
 unsigned char (*_ZRabat)(char* in);
 unsigned char __declspec(dllimport) _cdecl _ZSBajty(char* in);
 unsigned char __declspec(dllimport) _cdecl _ZSBlok(char* in);
 unsigned char __declspec(dllimport) _cdecl _ZSJednos(char* in);
 unsigned char __declspec(dllimport) _cdecl _ZSPBarko(char* in);
 unsigned char __declspec(dllimport) _cdecl _ZSReklam(char* in);
 unsigned char __declspec(dllimport) _cdecl _ZSTowar(char* in);
 unsigned char __declspec(dllimport) _cdecl _ZSygPara(char* in);
 unsigned char __declspec(dllimport) _cdecl _ZSzufMax(char* in);
 unsigned char (*_ZTowar)(char* in);
 unsigned char __declspec(dllimport) _cdecl _ZTPojemn(char* in);
 unsigned char __declspec(dllimport) _cdecl _ZTWaga(char* in);
 unsigned char __declspec(dllimport) _cdecl _ZUprKas(char* in);
 unsigned char __declspec(dllimport) _cdecl _ZWaluta(char* in);
 unsigned char __declspec(dllimport) _cdecl _ZWiaz(char* in);
 unsigned char __declspec(dllimport) _cdecl _ZWiersz(char* in);

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


	//struktura odczytu danych o towarze z kasy


typedef struct TOW_K
{
	char numer[50];
	char nazwa[150];
	int vat;
	int grupa;
	int mpp;
	int jm;
	int num_wag;
	int licz_starz;
	char kod_kr[35];
	float cenab;
	bool is_bl;
	bool is_op;
	bool is_wylzRN;
	bool wpr_cen;
	bool list_podr;

};

typedef struct KAS_CFG
{
	BYTE bt[24];
};


typedef unsigned char (*_pf)(char* in, char *out);


 int Init_Proc()
 {
	 bool bl;
	 
	 WINIP_M=LoadLibrary("WinIP.dll");
	 if(WINIP_M==NULL) return -1;
	 bl=true;

	 _RSTest=( unsigned char (*)(char*,char*))GetProcAddress(WINIP_M,"__RSTest");
	 if(_RSTest==NULL) bl=false;
	  _ODNBajty=( unsigned char (*)(char*,char*))GetProcAddress(WINIP_M,"__ODNBajty");
	 if(_ODNBajty==NULL) bl=false;
	 _ONrKasy=( unsigned char (*)(char*,char*))GetProcAddress(WINIP_M,"__ONrKasy");
	 if(_ONrKasy==NULL) bl=false;
	_OBajty=( unsigned char (*)(char*,char*))GetProcAddress(WINIP_M,"__OBajty");
	 if(_OBajty==NULL) bl=false;
	  _ModStart=( unsigned char (*)(char*))GetProcAddress(WINIP_M,"__ModStart");
	 if(_ModStart==NULL) bl=false;
	_ModStop=( unsigned char (*)(char*))GetProcAddress(WINIP_M,"__ModStop");
	 if(_ModStop==NULL) bl=false;
	 _TowarMax=( unsigned char (*)(char*,char*))GetProcAddress(WINIP_M,"__TowarMax");
	 if(_TowarMax==NULL) bl=false;
	 _OTowar=( unsigned char (*)(char*,char*))GetProcAddress(WINIP_M,"__OTowar");
	 if(_OTowar==NULL) bl=false;
	 _ONrTowar=( unsigned char (*)(char*,char*))GetProcAddress(WINIP_M,"__ONrTowar");
	 if(_ONrTowar==NULL) bl=false;
	 _OIlZaPLU=( unsigned char (*)(char*,char*))GetProcAddress(WINIP_M,"__OIlZaPLU");
	 if(_OIlZaPLU==NULL) bl=false;
	 _OJednost=( unsigned char (*)(char*,char*))GetProcAddress(WINIP_M,"__OJednost");
	 if(_OJednost==NULL) bl=false;
	 _OSpOpMax=( unsigned char (*)(char*))GetProcAddress(WINIP_M,"__OSpOpMax");
	 if(_OSpOpMax==NULL) bl=false;
	 _OPodatek=( unsigned char (*)(char*, char*))GetProcAddress(WINIP_M,"__OPodatek");
	 if(_OPodatek==NULL) bl=false;
	 _OGrupa=( unsigned char (*)(char*, char*))GetProcAddress(WINIP_M,"__OGrupa");
	 if(_OGrupa==NULL) bl=false;
	 _ZTowar=( unsigned char (*)(char*))GetProcAddress(WINIP_M,"__ZTowar");
	 if(_ZTowar==NULL) bl=false;
	 _KTowar=( unsigned char (*)(char*))GetProcAddress(WINIP_M,"__KTowar");
	 if(_KTowar==NULL) bl=false;
	 _DrukRap=( unsigned char (*)(char*,char*))GetProcAddress(WINIP_M,"__DrukRap");
	 if(_DrukRap==NULL) bl=false;
	 _DrukRapD=( unsigned char (*)(char*,char*))GetProcAddress(WINIP_M,"__DrukRapD");
	 if(_DrukRapD==NULL) bl=false;
	 _ZNrKasy=( unsigned char (*)(char*))GetProcAddress(WINIP_M,"__ZNrKasy");
	 if(_ZNrKasy==NULL) bl=false;
	 _ZBajty=( unsigned char (*)(char*))GetProcAddress(WINIP_M,"__ZBajty");
	 if(_ZBajty==NULL) bl=false;
	 _ZJednost=( unsigned char (*)(char*))GetProcAddress(WINIP_M,"__ZJednost");
	 if(_ZJednost==NULL) bl=false;
	 _ZGrupa=( unsigned char (*)(char*))GetProcAddress(WINIP_M,"__ZGrupa");
	 if(_ZGrupa==NULL) bl=false;
	 _ZPlat=( unsigned char (*)(char*))GetProcAddress(WINIP_M,"__ZPlat");
	 if(_ZPlat==NULL) bl=false;
	 _OPlat=( unsigned char (*)(char*,char*))GetProcAddress(WINIP_M,"__OPlat");
	 if(_OPlat==NULL) bl=false;
	 _ORabat=( unsigned char (*)(char*,char*))GetProcAddress(WINIP_M,"__ORabat");
	 if(_ORabat==NULL) bl=false;
	  _ZRabat=( unsigned char (*)(char*))GetProcAddress(WINIP_M,"__ZRabat");
	 if(_ZRabat==NULL) bl=false;
	  _ONarzut=( unsigned char (*)(char*, char*))GetProcAddress(WINIP_M,"__ONarzut");
	 if(_ONarzut==NULL) bl=false;
	 _ZNarzut=( unsigned char (*)(char*))GetProcAddress(WINIP_M,"__ZNarzut");
	 if(_ZNarzut==NULL) bl=false;
	 _ODaneARG=( unsigned char (*)(char*,char*))GetProcAddress(WINIP_M,"__ODaneARG");
	 if(_ODaneARG==NULL) bl=false;
	 _ODanePRG=( unsigned char (*)(char*,char*))GetProcAddress(WINIP_M,"__ODanePRG");
	 if(_ODanePRG==NULL) bl=false;
	 _ORodzKas=( unsigned char (*)(char*,char*))GetProcAddress(WINIP_M,"__ORodzKas");
	 if(_ORodzKas==NULL) bl=false;
	 _ZRodzKas=( unsigned char (*)(char*))GetProcAddress(WINIP_M,"__ZRodzKas");
	 if(_ZRodzKas==NULL) bl=false;
	 _ORKasjer=( unsigned char (*)(char*,char*))GetProcAddress(WINIP_M,"__ORKasjer");
	 if(_ORKasjer==NULL) bl=false;
	 _ZRKasjer=( unsigned char (*)(char*))GetProcAddress(WINIP_M,"__ZRKasjer");
	 if(_ZRKasjer==NULL) bl=false;
	 _KKasjer=( unsigned char (*)(char*))GetProcAddress(WINIP_M,"__KKasjer");
	 if(_KKasjer==NULL) bl=false;
	 if(bl) return 1; else return 0;
 }
 

 // funkcja czyta raport komunikacji z kas¹

int RAP(char* naz,int size)
{
	HANDLE hn;
	char txt[350],zn;
	WIN32_FIND_DATA fdt;
	int i,licz,kod;
	fstream pl;

	hn=FindFirstFile("RAPORT.TXT",&fdt);
	if(hn==INVALID_HANDLE_VALUE) return-1;					
	else
	{
		pl.open("RAPORT.TXT",ios_base::in);
		if(!pl.is_open()) return -1;
		
		i=0;
		licz=0;
		do
		{
			pl.read(&zn,1);
			licz++;
			if(zn=='#') i++;
			if(i==2)
			{
				i=0;
				memset(txt,0,150);
				do
				{
					pl.read(&zn,1);
					licz++;
					if(zn!=9) 
					{
						strncpy(txt+i,&zn,1);
						i++;
					} else zn=-1;
				}while(zn!=-1 && licz<fdt.nFileSizeLow);
				kod=atoi(txt);
				if(kod==0 && naz!=NULL)
				{
					i=-1;
					memset(naz,0,size);
					do
					{
						pl.read(&zn,1);
						licz++;
						if (zn=='#')
						{
							do
							{
								pl.read(&zn,1);
								i++;
								licz++;
								if(zn!='(') strncpy(naz+i,&zn,1); 
								if(zn=='(' || zn==10) 
								{
									zn=-1;
									if(naz[strlen(txt)-1]==32 || naz[strlen(txt)-1]=='.') naz[strlen(txt)-1]=0;
								}
							}while(zn!=-1 && licz<fdt.nFileSizeLow);
						}
					}while(zn!=-1 && licz<fdt.nFileSizeLow);
				}
			}
		}while(licz<fdt.nFileSizeLow && zn!=-1 );
	}
	pl.close();				
	if(kod==0) return 0 ;else return kod;

}


	//funkcja wpisuje wpis do pliku KONGIG.TXT

int InitKonf(KASA_ K)
{
	char con_str[350],txt[350];
	fstream pl;

	memset(con_str,0,350);
	memset(txt,0,350);
	strcpy(txt,"MUX");
	sprintf(con_str,"$%s\tCOM%d:%d:%s%d:%d\t%d\t%s",K.numer,K.Com,K.Szybk,txt,K.rodz_pol,K.kanal,K.timeout,K.RU);
	if(K.rodz_pol==2)
	{
		sprintf(con_str+strlen(con_str),"\t%c%s:%s:%d:%d:%d",(char)K.PT,K.tel,K.haslo,K.AT,K.T1,K.ret);
	}else 
		if(K.rodz_pol==1)
	{
						
		sprintf(con_str+strlen(con_str),"\tAnyString:3001:%s:%d:%s:%d:%d",K.IP,K.port,K.haslo,K.T1,K.ret);
	}

	pl.open("KONFIG.txt",ios_base::in|ios_base::out|ios_base::trunc);
	if(!pl.is_open())
	{
		return -1;
	}
	pl.write((char*)con_str,strlen(con_str));
	pl.close();
	return 1;
}



	//funkcja odczytuje maksymalny numer towaru z kasy

int get_num(char * txt, int size)
{
	fstream pl;
	char con_str[350];
	int i,licz;
	WIN32_FIND_DATA fdt;
	HANDLE hn;
	char zn;

	if(txt==NULL) return -1;
	

	hn=FindFirstFile("Config/pin.out",&fdt);
	if(hn==INVALID_HANDLE_VALUE) return -1;

	pl.open("Config/pin.out",ios_base::in);
	if(!pl.is_open()) return -1;
	licz=0;
	zn=0;
	while(licz<fdt.nFileSizeLow && zn!='$')
	{
		pl.read((char*)&zn,1);
		licz++;
	}
	if(zn=='$' && licz<fdt.nFileSizeLow)
	{
		memset(txt,0,size);
		i=0;
		while(zn!=10 && zn!= 13 && i<150 && licz<fdt.nFileSizeLow)
		{
			pl.read((char*)&zn,1);
			if(zn!=10 && zn!=13)
			{
				txt[i]=zn;
				i++;
			}
			licz++;
		
		}
	}
	pl.close();
	return 1;

}



//funkcja odczytuje parametry w zale¿nioœci od podanej funkcji w parfametrze pf

int get_data(KASA_ KT,int * num, _pf pf, char* naz, int size)
{
	fstream pl;
	char con_str[350],txt[350];
	int i,licz;
	WIN32_FIND_DATA fdt;
	HANDLE hn;
	char zn;

	//if (num==NULL) return -1;
	memset(con_str,0,350);
	memset(txt,0,350);
	strcpy(txt,"MUX");
	sprintf(con_str,"$%s\tCOM%d:%d:%s%d:%d\t%d\t%s",KT.numer,KT.Com,KT.Szybk,txt,KT.rodz_pol,KT.kanal,KT.timeout,KT.RU);
	if(KT.rodz_pol==2)
	{
		sprintf(con_str+strlen(con_str),"\t%c%s:%s:%d:%d:%d",(char)KT.PT,KT.tel,KT.haslo,KT.AT,KT.T1,KT.ret);
	}else 
		if(KT.rodz_pol==1)
	{
						
		sprintf(con_str+strlen(con_str),"\tAnyString:3001:%s:%d:%s:%d:%d",KT.IP,KT.port,KT.haslo,KT.T1,KT.ret);
	}

	pl.open("KONFIG.txt",ios_base::in|ios_base::out|ios_base::trunc);
	if(!pl.is_open())  return -1;
	
	pl.write((char*)con_str,strlen(con_str));
 	pl.close();

	pl.open("Config/pin.in",ios_base::in|ios_base::out|ios_base::trunc);
	if(!pl.is_open()) return -1;
	
	memset(con_str,0,350);

	sprintf(con_str,"#%s\n#\n#",KT.numer);
	pl.write(con_str,strlen(con_str));
	pl.close();

	pl.open("Config/pin.out",ios_base::in|ios_base::out|ios_base::trunc);
	if(!pl.is_open()) return -1;
	
	pl.close();

	(*pf)("Config/pin.in","Config/pin.out");
	if(naz!=NULL) i=RAP(naz,size);
	else i=RAP(NULL,0);
	if(i==-1) return i;
	if(i!=0) return i;
	
	if(num!=NULL)
	{
		get_num(txt,350);
		*num=atoi(txt);
	}
	return i;
}


	//Funkcja odczytuje sprzeda¿ z kasy


int OSprz(KASA_ KT)
{
	int i;
	fstream pl;
	char con_str[350],txt[350];

	i=InitKonf(KT);
	if(i<1) return -1;
	pl.open("Config/pin.in",ios_base::in|ios_base::out|ios_base::trunc);
	if(!pl.is_open()) return -1;
	
	memset(con_str,0,350);

	sprintf(con_str,"#%s\n#\n#\n$%s\t%s\t%s",KT.numer,"Config/sprz.txt","Config/naz.txt","Config/sort.txt");
	pl.write(con_str,strlen(con_str));
	pl.close();

	pl.open("Config/pin.out",ios_base::in|ios_base::out|ios_base::trunc);
	if(!pl.is_open()) return -1;
	
	pl.close();

	(*_OSpOpMax)("Config/pin.in");
	i=RAP(NULL,0);
	if(i!=0) return i;
	return 0;
}


