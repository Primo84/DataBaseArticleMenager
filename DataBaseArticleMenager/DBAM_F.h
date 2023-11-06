
#include "winProc.h"

int Count_P;
int Count_A;
int Count_K;
int Count_F;
int Count_Kas;
int MAX_Kas;
int Default;
int *Kas_ind;
int nazT_max;
LONGLONG lsize;				//iloœæ plików modu³ów do obs³ugi kasy fiskalnej

HWND MainWnd,Dlg1,Dlg2,Dlg3;

const int Grow=1000;
const int Max_F=1000;

char path[300],path1[300];

HINSTANCE hst;


#define F_OR		1
#define F_KO		2
#define F_OR_KO		3
#define F_OR_I_KO	4
#define F_PRO		5

const int	MAX_X=1350;
const int	MAX_Y=650;
const int	MAX_ART= 100000;

char Err_Text[350];
char Query_Text[350];

unsigned char (*f_mod1)(char *in, char *out);
unsigned char (*f_mod2)(char *in);

LRESULT _stdcall Dlg11Proc(HWND hwd, int code, WPARAM wp ,LPARAM lp);




LRESULT _stdcall DlgBProc(HWND hwd,int code, WPARAM wp, LPARAM lp);
LRESULT _stdcall WndEProc (HWND hwd, int code, WPARAM wp , LPARAM lp);
LRESULT CALLBACK Dlg5Proc(HWND hwd, int code, WPARAM wp, LPARAM lp);
LRESULT CALLBACK Dlg6Proc(HWND hwd, int code, WPARAM wp, LPARAM lp);
LRESULT CALLBACK Dlg7Proc(HWND hwd, int code, WPARAM wp, LPARAM lp);
INT_PTR _stdcall DlgProc2(HWND hwd,int code, WPARAM wp, LPARAM lp);
INT_PTR _stdcall DlgProc3(HWND hwd,int code, WPARAM wp, LPARAM lp);
LRESULT _stdcall Dlg9Proc(HWND hwd, int code, WPARAM wp, LPARAM lp);
LRESULT _stdcall DLGERRProc(HWND hwd, int code, WPARAM wp, LPARAM lp);
LRESULT _stdcall DLGQProc(HWND hwd, int code, WPARAM wp, LPARAM lp);
LRESULT _stdcall DLGIProc(HWND hwd, int code, WPARAM wp, LPARAM lp);
LRESULT _stdcall DLG14Proc(HWND hwd, int code, WPARAM wp, LPARAM lp);
LRESULT _stdcall DLG15Proc(HWND hwd, int code, WPARAM wp, LPARAM lp);
LRESULT _stdcall DLG16Proc(HWND hwd, int code, WPARAM wp, LPARAM lp);
LRESULT _stdcall DLG22Proc(HWND hwd, int code, WPARAM wp, LPARAM lp);
LRESULT _stdcall DLG23Proc(HWND hwd, int code, WPARAM wp, LPARAM lp);
LRESULT _stdcall DLG24Proc(HWND hwd, int code, WPARAM wp, LPARAM lp);
LRESULT _stdcall DLG25Proc(HWND hwd, int code, WPARAM wp, LPARAM lp);
LRESULT _stdcall DLG26Proc(HWND hwd, int code, WPARAM wp, LPARAM lp);
LRESULT _stdcall DLG27Proc(HWND hwd, int code, WPARAM wp, LPARAM lp);
LRESULT _stdcall DLG39Proc(HWND hwd, int code, WPARAM wp, LPARAM lp);
LRESULT _stdcall DLG41Proc(HWND hwd, int code, WPARAM wp, LPARAM lp);
LRESULT _stdcall DLG46Proc(HWND hwd, int code, WPARAM wp, LPARAM lp);

LPSTR kraje[243]={"AFGHANISTAN","ALBANIA","ALGIERIA","ANDORA","ANGOLA","ANGLIA","ANGUILLA","ANTARKTYDA","ANTIGUA I BARBUDA","ARABIA SAUDYJSKA","ARGENTYNA","ARMENIA","ARUBA","AUSTRALIA","AUSTRIA","AZERBEJD¯AN","BAHAMY","BAHRAJN","BANGLADESZ","BARBADOS","BELGIA",
			"BELIZE","BENIN","BERMUDY","BHUTAN","BIA£ORUŒ","BOLIWIA","BONAIRE, SINT EUSTATIUS I SABA","BOŒNIA I HERCEGOWINA","BOTSWANA","BRAZYLIA","BRUNEI DARUSSALAM","BRYTYJSKIE TERYTORIUM OCEANU INDYJSKIEGO","BU£GARIA","BURKINA FASO","BURUNDI","CEUTA","CHILE","CHINY","CURAÇAO","CHORWACJA",
			"CYPR","CZAD","CZARNOGÓRA","CZECHY","DANIA","DOMINIKA","DOMINIKANA","D¯IBUTI","EGIPT","EKWADOR","ERYTREA","ESTONIA","ETIOPIA","FALKLANDY","FID¯I REPUBLIKA","FILIPINY","FINLANDIA","FRANCUSKIE TERYTORIUM PO£UDNIOWE","FRANCJA","GABON","GAMBIA",
			"GHANA","GIBRALTAR","GRECJA","GRENADA","GRENLANDIA","GRUZJA","GUAM","GUJANA","GWATEMALA","GWINEA","GWINEA RÓWNIKOWA","GWINEA-BISSAU","HAITI","HISZPANIA","HONDURAS","HONGKONG","INDIE","INDONEZJA","IRAK","IRAN",
			"IRLANDIA","ISLANDIA","IZRAEL","JAMAJKA","JAPONIA","JEMEN","JORDANIA","KAJMANY","KAMBOD¯A","KAMERUN","KANADA","KATAR","KAZACHSTAN","KENIA","KIRGISTAN","KIRIBATI","KOLUMBIA","KOMORY","KONGO","KONGO-REPUBLIKA DEMOKRATYCZNA",
			"KOREAÑSKA REPUBLIKA LUDOWO-DEMOKRATYCZNA","KOSOWO","KOSTARYKA","KUBA","KUWEJT","LAOS","LESOTHO","LIBAN","LIBERIA","LIBIA","LIECHTENSTEIN","LITWA","LUKSEMBURG","£OTWA","MACEDONIA","MADAGASKAR","MAJOTTA","MAKAU","MALAWI","MALEDIWY",
			"MALEZJA","MALI","MALTA","MARIANY PÓ£NOCNE","MAROKO","MAURETANIA","MAURITIUS","MEKSYK","MELILLA","MIKRONEZJA","MINOR (POWIERNICZE WYSPY PACYFIKU STANÓW ZJEDNOCZONYCH)","MO£DOWA","MONGOLIA","MONTSERRAT","MOZAMBIK","MYANMAR (BURMA)","NAMIBIA","NAURU","NEPAL","NIDERLANDY",
			"NIEMCY","NIGER","NIGERIA","NIKARAGUA","NIUE","NORFOLK","NORWEGIA","NOWA KALEDONIA","NOWA ZELANDIA","OKUPOWANE TERYTORIUM PALESTYNY","OMAN","PAKISTAN","PALAU","PANAMA","PAPUA NOWA GWINEA","PARAGWAJ","PERU","PITCAIRN","POLINEZJA FRANCUSKA","POLSKA",
			"PO£UDNIOWA GEORGIA I PO£UDNIOWE WYSPY SANDWICH","PORTUGALIA","REPUBLIKA CZESKA","REPUBLIKA KOREI","REP.PO£UD.AFRYKI","REP.ŒRODKOWOAFRYAÑSKA","ROSJA","RWANDA","SAHARA ZACHODNIA","SAINT BARTHELEMY","RUMUNIA","SALWADOR","SAMOA","SAMOA AMERYKAÑSKIE","SAN MARINO","SENEGAL","SERBIA","SESZELE","SIERRA LEONE","SINGAPUR",
			"SUAZI","S£OWACJA","S£OWENIA","SOMALIA","SRI LANKA","ST. PIERRE I MIQUELON","ST.KITTS I NEVIS","ST.LUCIA","ST.VINCENT I GRENADYNY","STANY ZJEDN. AMERYKI","W£¥CZNIE Z PORTORYKO PR","SUDAN","SUDAN PO£UDNIOWY","SURINAM","SYRIA","SZWAJCARIA","SZWECJA","ŒWIÊTA HELENA","TAD¯YKISTAN","TAJLANDIA",
			"TAJWAN","TANZANIA","TOGO","TOKELAU","TONGA","TRYNIDAD I TOBAGO","TUNEZJA","TURCJA","TURKMENISTAN","WYSPY TURKS I CAICOS","TUVALU","UGANDA","UKRAINA","URUGWAJ","UZBEKISTAN","VANUATU","WALLIS I FUTUNA","WATYKAN","WENEZUELA","WÊGRY","WIELKA BRYTANIA","WIETNAM","W£OCHY","WSCHODNI TIMOR","WYB.KOŒCI S£ONIOWEJ","WYSPA BOUVETA","WYSPA BO¯EGO NARODZENIA","WYSPY COOKA","WYSPY DZIEWICZE-USA","WYSPY DZIEWICZE-W.B","WYSPY HEARD I MCDONALD","WYSPY KOKOSOWE (KEELINGA)","WYSPY OWCZE","WYSPY MARSHALLA","WYSPY SALOMONA","WYSPA SINT MAARTEN (CZÊŒÆ HOLENDERSKA WYSPY)","WYSPY ŒW.TOMASZA I KSI¥¯ÊCA","ZAMBIA","ZIELONY PRZYL¥DEK","ZJEDN.EMIRATY ARABSKIE",
			"ZIMBABWE"
			};

HBRUSH hbr;
HPEN hpn;





		//Struktura danych przyjêcia towaru
typedef struct rodz_vat
{
	float rodz;
	float wart;
};
struct Prz_Tow
{
	double cena_n;
	BYTE miesiac;
	WORD rok;
	rodz_vat rodz_v[50];
};



		//Struktua damnych Firmy

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

		// Struktura tabeli producentow

struct Producent
{
	int CRC;
	int IDP;
	char Nazwa[250];
	char Kraj[75];
	char Miasto[75];
	char Adres[250];
	char KodPocz[25];
	char Telefon[25];
	char Fax[25];
	char NIP[13];
	char REGON[14];
	char BR[2];
};

		//Struktura tabeli artykolow

typedef struct Artykuly1
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


	//Struktura tabeli sprzedazy towaru


struct Fakt_Vat
{
	int CRC;
	int IDK;
	int LP;
	char Nazwa[350];
	int PKWiU;
	int ilosc;
	char JM[10];
	double Cena_Netto;
	float Rabat;
	double Cena_Netto2;
	double VAT;
	double KW_Netto;
	double KW_VAT;
	double KW_Brutto;
	char BR[2];
};

	//Struktura Kontrahenta



struct Kontrahent
{
	int CRC;
	int IDK;
	char Nazwa[350];
	char Adres[350];
	char KodPocz[25];
	char Miasto[75];
	char Kraj[75];
	char NIP[13];
	char Regon[14];
	char Tel[25];
	char BR[2];
};

	//Struktura naglówka pliku bazy faktur

struct Header_FB
{
	int CountF;
	int id;
	int rok;
	//int mon;
};

	//Struktura naglowka faktury

struct Header_F
{
	//int crc;
	char numer[50];
	int IDK;
	WORD rok;
	WORD miesiac;
	WORD dzien;
	int count;
	bool is_korekta;
	double KW_N;
	double KW_V;
	double KW_B;
	double Zaplata;
	char form_zap[35];
	bool is_ex;
	BYTE il_dni;
	SYSTEMTIME ter_plat;
};

	//struktura naglowka tabeli producentow

struct Header_P
{
	//int crc;
	int LastID;
	LONG count;
};

	//struktura naglowka tabeli artyku³ów

typedef struct Header_A
{
	int del_cnt;
	int LastID;
	int count;
	int deli[MAX_ART];
};
	//struktura naglowka tabeli kontrahentów


struct Header_K
{
	int LastID;
	LONG count;
};

	//struktura zawieraj¹ca licznik form zapóaty oraz form gotówki

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

	//struktura jednostek miary

typedef struct JM
{
	char naz[25];
	char znak[25];
};

	//struktura stawek vat

typedef struct ST_VAT
{
	float vat;
	char opis[100];
};
	
typedef struct GR_T
{
	char nazwa[50];
};

	//struktura walut
	
typedef struct WALUTA
{
	char naz[25];
	char znak[25];
};

	//struktura form zap³aty

typedef struct FORM_ZAP
{
	char naz[25];
	char opis[350];
};

	//struktura zawieraj¹ca numeracjê faktury vat

typedef struct N_VAT
{
	char przed[8];
	bool is_;
};

	//struktura raportu godzinowego

typedef struct RG
{
	int godz;
	int il_par;
	int il_poz_par;
	float wart_sprz;
};

typedef struct RPG
{
	RG rg[24];
};

typedef struct KASJER
{
	char nazwa[20];        //
	bool d_rap_kon_zm;
	bool d_rap_sprz_wed_gr;
	bool d_rap_szcz_sprz;
	bool d_rap_zwr_op;			//raporty ktore maja byæ drukowane
	bool d_rap_godz;
	bool d_rap_dob;
	bool d_rap_sum_okr1;
	bool d_rap_sprzedaw;	//
	bool z_rap_kon_zm;
	bool z_rap_sprz_wed_gr;
	bool z_rap_szcz_sprz;
	bool z_rap_zwr_op;			//raporty ktore maja byæ zeruj¹ce
	bool z_rap_godz;
	bool z_rap_dob;
	bool z_rap_sum_okr1;
	bool z_rap_sprzedaw;	//
	BYTE max_rab;
	BYTE max_narz;
	BYTE upr[99];
};


		//struktura danych o kasjerach
typedef struct D_KASJER
{
	int id;
	char nazwa[20];
	char haslo[14];
	int numer;
	bool zmiana;
};

FIRMA FRM;
Header_P HD_P;
Header_A HD_A;
Header_K HD_K;
Header_F *HD_F;
Header_FB HD_FB;
Producent *PR;
Artykuly *ART;
Kontrahent *KONTR;
KASA_ *KS;
COUNT cnt;
WALUTA wal[99];
FORM_ZAP form_zap[99];
ST_VAT Vat[99];
JM jm[99];
GR_T GR[99];
N_VAT NV;
//HDM_F *HDM;


typedef int (*get_Count)();
typedef int (*get_Max)();
typedef int (*get_Kas)(KASA_ *kas, int id);
typedef int (*get_All)(KASA_ *kas, int count);
typedef int (*get_First)();
typedef int (*get_Default)();

get_Count Fget_Count;
get_Max Fget_Max;
get_Kas Fget_Kas;
get_All Fget_All;
get_First Fget_First;
get_Default Fget_Default;

void GrowF();


//Funkcja wyszukuje podany ciag w pliku 

bool find_str(char *fc,LONGLONG*pos,char*ch,int size)
{
	FILE *pf;
	bool bl=false;
	bool bl1=false;
	int i,pos1=0;
	char zn;
	LARGE_INTEGER lg;
	LONGLONG ll,ll1;
	HANDLE fh=0;



	fh=CreateFileA(fc,GENERIC_READ,FILE_SHARE_WRITE|FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	
	if(fh==NULL) 
		return false;
	
	GetFileSizeEx(fh,&lg);
	CloseHandle(fh);
	ll=lg.QuadPart;

	pf=fopen(fc,"r+");

	if(pf==NULL||ch==NULL||size<=0)
		return false;

	ll1=*pos;
	if(ll1>ll||ll1<0)ll1=0;
	fseek(pf,(long)ll1,FILE_BEGIN);
	do
	{

		//fseek(pf,ll1,FILE_BEGIN);
		zn=fgetc(pf);
		
		ll1++;

		
		if((zn==-1)&&(ll!=ll1))
		{
	
			fseek(pf,(long)ll1,FILE_BEGIN);
		}
		
		if(ll==ll1) bl=true;
		if(zn==ch[0])
		{
			i=1;
			do
			{
				zn=(char)fgetc(pf);
				ll1++;
				if(i>2)
				{
					i=i;
					}
				i++;
				if(ll==ll1) bl=true;
			}while((zn==ch[i-1])&&(i<size+1));
			
			if(i==size+1)
			{
				bl=bl1=true;
				*pos=ll1-1-size;
			}
			else 
			{
				ll1--;
				fseek(pf,-1,FILE_CURRENT);
			}
		}

	}while(!bl);
	fclose(pf);
	return bl1;
}



		//Funkcja zamieniaj¹ca liczbê double na string


int dbl_str(double db,char * zn, int offset,int maxc)
{
	int d,i;
	double l1; 
	float l;
	char z[100];
	bool is_min;
	
	is_min=false;
	if(zn==NULL) return -1;
	if(db<0)
	{
		is_min=true;
		db=(-db);
	}
	d=(int)db;
	l1=db-d;
	for(i=0;i<offset;i++)
	{
		l1=l1*10;
		d=(int)l1;
		l1=l1-d;
	}
	if(l1>0.5)
	{
	
		l=1;
		for(i=0;i<offset;i++)
		{
			l=l/10;
		}
		db=db+l;
	}
	l1=db-int(db);
	memset(zn,0,maxc);
	if(is_min) zn[0]='-';
	itoa(int(db),zn+strlen(zn),10);
	strcpy(zn+strlen(zn),".");
	for(i=0;i<offset;i++)
	{
		l1=l1*10;
		d=(int)l1;
		l1=l1-d;
		itoa(d,zn+strlen(zn),10);
	}
	while(zn[strlen(zn)-1]=='0')
	{
		zn[strlen(zn)-1]=0;
	}
	if(zn[strlen(zn)-1]=='.') zn[strlen(zn)-1]=0;

	return 1;

}
	

		/* Fnkcja obliczajaca sumê kontroln¹ 
			Return :
					-1 jeœli bt=NULL
					jeœli poprawne to zwraca obliczon¹ sumê
		*/

int EnumSum(BYTE *bt, int size)
{
	int i;
	int sm,r;

	r=0;
	sm=0;
	if(bt==NULL||size<0) return -1;
	for(i=0;i<size;i++)
	{
		sm=sm+*bt;
		r=r+(sm%5);
		bt++;
	}
	return r;
}


		// Funkcja inicjuj¹ca bazê danhych aplikacji

bool Init_Base()
{
	int i,i1,j,jc,filec,lastc,sum;
	fstream pl;
	Producent *PR1;
	Artykuly *ART1;
	Kontrahent *KONTR1;
	BYTE *bt,b;
	char zn[30];
	SYSTEMTIME st;
	Header_F *HDF;
	bool bl;
	//HDM_F hdm;
	HKEY hk;
	DWORD dw;
	char text[300];
	DWORD type;

	i=RegOpenKeyEx(HKEY_CURRENT_USER,"Software\\DataBaseArticleMenager",0,KEY_READ,&hk);
	if(i!=0)
	{
		memset(path,0,300);
		GetFullPathName("DataBaseArticleMenager.exe",300,path,NULL);
		j=strlen(path);
		for(i=1;i<27;i++)path[j-i]=0;
		sprintf(&path[strlen(path)],"Data\\");
	}
	else
	{
		memset(text,0,300);
		dw=300;
		type=REG_SZ;
		i=RegQueryValueEx(hk,"FolderPath",NULL,&type,(BYTE*)text,&dw);
		if(i!=0)
		{
			
			memset(path,0,300);
			GetFullPathName("DataBaseArticleMenager.exe",300,path,NULL);
			j=strlen(path);
			for(i=1;i<27;i++)path[j-i]=0;
			sprintf(&path[strlen(path)],"Data\\");

		}else
		{
			memset(path,0,300);
			sprintf(path,"%s\\Data\\",text);

		}
	}
	RegCloseKey(hk);

	bl=true;
	memset(path1,0,300);
	sprintf(path1,"%sDBP.amb",path);
	pl.open(path1,ios_base::in|ios_base::out|ios_base::binary);
	if(!pl)
	{
		memset(path1,0,300);
		sprintf(path1,"%sDBP.amb",path);
		pl.open(path1,ios_base::out|ios_base::in|ios_base::trunc|ios_base::binary);
		HD_P.count=0;
		Count_P=0;
		HD_P.LastID=-1;
		pl.write((char*)&HD_P,sizeof(Header_P));
	}else
	{
		pl.read((char*)&HD_P,sizeof(Header_P));
	}
	if(HD_P.count>0) 
	{
		Count_P=HD_P.count+Grow;
		PR=new Producent[Count_P];
		PR1=PR;
		for(i=0;i<HD_P.count;i++)
		{
			pl.read((char*)PR1,sizeof(Producent));
			sum=EnumSum((BYTE*)PR1+4,sizeof(Producent)-sizeof(int));
			if(sum!=PR1->CRC)
			{
				bl=false;
			}
			PR1++;
		}
	}
	if(pl) pl.close();

memset(path1,0,300);
sprintf(path1,"%sDBK.amb",path);
pl.open(path1,ios_base::in|ios_base::out|ios_base::binary);
	if(!pl)
	{
		memset(path1,0,300);
		sprintf(path1,"%sDBK.amb",path);
		pl.open(path1,ios_base::out|ios_base::in|ios_base::trunc|ios_base::binary);	
		HD_K.count=0;
		Count_K=0;
		HD_K.LastID=-1;
		pl.write((char*)&HD_K,sizeof(Header_K));
		
	}else
	{
		pl.read((char*)&HD_K,sizeof(Header_K));
	}
	if(HD_K.count>0) 
	{
		Count_K=HD_K.count+Grow;
		KONTR=new Kontrahent[Count_K];
		KONTR1=KONTR;
		for(i=0;i<HD_K.count;i++)
		{
			pl.read((char*)KONTR1,sizeof(Kontrahent));
			sum=EnumSum((BYTE*)KONTR1+4,sizeof(Kontrahent)-sizeof(int));
			if(sum!=KONTR1->CRC)
			{
				bl=false;
			}
			KONTR1++;
		}
	}
	if(pl) pl.close();
	memset(path1,0,300);
	sprintf(path1,"%sDBF1.amb",path);
	pl.open(path1,ios_base::in|ios_base::out|ios_base::binary);
	if(!pl)
	{
		memset(path1,0,300);
		sprintf(path1,"%sDBF1.amb",path);
		pl.open(path1,ios_base::out|ios_base::in|ios_base::trunc|ios_base::binary);	
		Count_F=0;
		HD_FB.CountF=0;
		HD_FB.id=0;
		GetSystemTime(&st);
		HD_FB.rok=st.wYear;
		pl.write((char*)&HD_FB,sizeof(Header_FB));
		
	}else
	{
		pl.read((char*)&HD_FB,sizeof(Header_FB));
	}
	Count_F=HD_FB.CountF+Grow;
	HD_F=new Header_F[Count_F];
	if(HD_FB.CountF==0)
	{
		filec=1;
		lastc=0;
	}
	else 
	{
		filec=(int)HD_FB.CountF/Max_F;
		lastc=(int)HD_FB.CountF%Max_F;
		if(lastc!=0)filec++;
	}
	HDF=HD_F;
	for(i=1;i<=filec;i++)
	{
		if(i>1)
		{
			memset(path1,0,300);
			sprintf(path1,"%sDBF",path);
			//memset(zn,0,30);
			//strcpy(zn,"Data\\DBF");
			itoa(i,path1+strlen(path1),10);
			strcpy(path1+strlen(path1),".amb");
			pl.open(path1,ios_base::in|ios_base::out|ios_base::binary);
		}
		if(i!=filec)jc=Max_F; else jc=lastc;
		if(jc==0 && filec==i && HD_FB.CountF>0) jc=Max_F;
		for(j=0;j<jc;j++)
		{
			pl.read((char*)HDF,sizeof(Header_F));
			pl.seekg(sizeof(Fakt_Vat)*HDF->count,ios_base::cur);
			HDF++;
		}
		if(pl) 
		{
			pl.close();
		}
	}

	return bl;
}


	//Funkcja powiêksza tablicê nag³ówków faktur

void GrowF()
{
	int i,i1;
	Header_F *HDF;

	if(HD_F==NULL)
		return;

	HDF=new Header_F[Count_F+Grow];
	for(i=0;i<Count_F;i++)
	{
		HDF[i]=HD_F[i];
	}
	//memcpy(HDF,HD_F,sizeof(Header_F)*Count_F);
	delete HD_F;
	HD_F=HDF;
	Count_F=Count_F+Grow;
}

	//Funkcja powiêksza tablicê artyku³ów

int GrowAR()
{
	int i,j;
	Artykuly *ART1;

	if(ART==NULL)
		return -1;
	i=HD_A.count;
	if(i+Grow<MAX_ART) j=Grow; else j=MAX_ART-Grow;
	ART1=new Artykuly[i+j];
	memcpy(ART1,ART,sizeof(Artykuly)*i);
	delete ART;
	ART=ART1;
	return j;
}

	//Funkcja powiêksza tablicê artyku³ów

void GrowPR()
{
	int i;
	Producent *PR1;

	if(PR==NULL)
		return;

	i=HD_P.count;
	PR1=new Producent[i];
	memcpy(PR1,PR,sizeof(Producent)*i);
	delete PR;
	PR=new Producent[i+Grow];
	memcpy(PR,PR1,sizeof(Producent)*i);
	delete PR1;
}


	//Funkcja powiêksza tablicê kontrahentów

void GrowKR()
{
	int i;
	Kontrahent *KONTR1;

	if(KONTR==NULL)
		return;

	i=HD_K.count;
	KONTR1=new Kontrahent[i+Grow];
	memcpy(KONTR1,KONTR,sizeof(Kontrahent)*i);
	delete KONTR;
	KONTR=KONTR1;
}

//Funkcja zapisuje bzê producentów
	
int Save_Prt(Producent *pr, Header_P hdp)
{
	fstream pl;
	Producent *prt;
	int i;

	if(pr==NULL) return -1;
	prt=pr;
	memset(path1,0,300);
	sprintf(path1,"%sDBP.amb",path);
	pl.open(path1,ios_base::out|ios_base::in|ios_base::trunc|ios_base::binary);
	if (!pl) return 0;
	pl.write((char*)&hdp,sizeof(Header_P));
	for(i=0;i<hdp.count;i++)
	{
		pl.write((char*)prt,sizeof(Producent));
		prt++;
	}
	pl.close();
	return 1;
}

	


		//Funkcja zapisuje bazê kontrahentów
	
int Save_Kontr(Kontrahent *kr, Header_K hdk)
{
	fstream pl;
	Kontrahent *krt;
	int i;

	if(kr==NULL) return -1;
	krt=kr;
	memset(path1,0,300);
	sprintf(path1,"%sDBK.amb",path);
	pl.open(path1,ios_base::out|ios_base::in|ios_base::trunc|ios_base::binary);
	if (!pl) return 0;
	pl.write((char*)&hdk,sizeof(Header_K));
	for(i=0;i<hdk.count;i++)
	{
		pl.write((char*)krt,sizeof(Kontrahent));
		krt++;
	}
	pl.close();
	return 1;
}



	//Funkcja usuwania producentów

bool Us_PR(int id)
{
	Producent *PR_Temp;
	int i,i1;

	if(PR==NULL)return false;
	PR_Temp=new Producent[Count_P];
	i1=0;

	for(i=0;i<HD_P.count;i++)
	{
		if(PR[i].IDP!=id) 
		{
			PR_Temp[i1]=PR[i];
			i1++;
		}
						

	}
	HD_P.count--;
	delete PR;
	Save_Prt(PR_Temp,HD_P);
	PR=PR_Temp;
	return true;
}

	//Funkcja usuwa artyku³ z bazy

bool Us_AR(int id)
{
	Artykuly *AR_Temp;
	int i,i1,i2;
	LONGLONG pos;
	fstream pl;

	if(ART==NULL)return false;
	AR_Temp=new Artykuly[Count_A];
	i1=0;

	for(i=0;i<HD_A.count;i++)
	{
		if(ART[i].indeks!=id) 
		{
			AR_Temp[i1]=ART[i];
			i1++;
		}
		else 
		{
			HD_A.deli[HD_A.del_cnt]=ART[i].indeks;
			i2=i;
		}
						

	}
	i=HD_A.deli[HD_A.del_cnt];
	HD_A.count--;
	HD_A.del_cnt++;
	if(!find_str("DBA.dll",&pos,"ADAPRIM_1234",12)) return false;
	pl.open("DBA.dll",ios_base::in|ios_base::out|ios_base::binary);
	if(!pl) return false;
	pl.seekg(pos+16,ios_base::beg);
	pos=pos+sizeof(Header_A);
	pos+=36;
	ART[i2].exist=false;
	pl.write((char*)&HD_A,sizeof(Header_A));
	pl.seekg(pos+(i*sizeof(Artykuly)),ios_base::beg);
	pl.write((char*)&ART[i2],sizeof(Artykuly));

	delete ART;
	ART=AR_Temp;

	return true;
}

	//Funkcja usuwa kontrahenta z bazy

bool Us_KR(int id)
{
	Kontrahent *KR_Temp;
	int i,i1;

	if(KONTR==NULL)return false;
	KR_Temp=new Kontrahent[Count_K];
	i1=0;

	for(i=0;i<HD_K.count;i++)
	{
		if(KONTR[i].IDK!=id) 
		{
			KR_Temp[i1]=KONTR[i];
			i1++;
		}
						

	}
	HD_K.count--;
	delete KONTR;
	Save_Kontr(KR_Temp,HD_K);
	KONTR=KR_Temp;
	return true;
}

	//Funkcja dodaje nowego producenta do bazy danych

bool Dodaj_PR(Producent *PR1)
{
	fstream pl;
	int i,i1;

	if(PR1==NULL) return false;

	if(HD_P.count==0 && PR==NULL)
	{
		PR=new Producent[Grow];
		Count_P=Grow;
	}else
	{
		if(Count_P<=HD_P.count)
		{
			GrowPR();
			Count_P=Count_P+Grow;
		}
	}
	
	memcpy(PR+(HD_P.count),PR1,sizeof(Producent));
	HD_P.count++;
	HD_P.LastID++;
	memset(path1,0,300);
	sprintf(path1,"%sDBP.amb",path);
	pl.open(path1,ios_base::in|ios_base::out|ios_base::binary);
	if(!pl) return false;
	pl.write((char*)&HD_P,sizeof(Header_P));
	pl.seekg(0,ios_base::end);
	pl.write((char*)PR1,sizeof(Producent));
	pl.close();
	return true;
}


	//Funkcja dodaje nowy artyku³ do bazy danych

bool Dodaj_AR(Artykuly *ART1)
{
	LONGLONG pos;
	fstream pl;
	int i,i1;

	if(ART1==NULL) return false;
	//if(!find_str("DBA.dll",&pos,"ADAPRIM_1234",12)) return false;
	pos=22528;
	if(HD_A.count==0 && ART==NULL)
	{
		ART=new Artykuly[Grow];
		Count_A=Grow;
	}else
	{
		if(Count_A<=HD_A.count && HD_A.count < MAX_ART)
		{
			i=GrowAR();
			Count_A=Count_A+i;
		}
	}
	
	HD_A.count++;
	HD_A.LastID++;
	pl.open("DBA.dll",ios_base::in|ios_base::out|ios_base::binary);
	if(!pl) return false;
	pl.seekg(pos+16,ios_base::beg);
	pos=pos+sizeof(Header_A);
	pos+=36;
	if(HD_A.del_cnt==0)
	{
		ART1->indeks=HD_A.count-1;
		memcpy(ART+(HD_A.count-1),ART1,sizeof(Artykuly));
		pl.write((char*)&HD_A,sizeof(Header_A));
		pos+=(HD_A.count-1)*sizeof(Artykuly);
		pl.seekg(pos,ios_base::beg);
		pl.write((char*)ART1,sizeof(Artykuly));
	}
	else
	{
		HD_A.del_cnt--;
		i=ART1->indeks=HD_A.deli[HD_A.del_cnt];
		HD_A.deli[HD_A.del_cnt]=-1;
		memcpy(ART+(HD_A.count-1),ART1,sizeof(Artykuly));
		pl.write((char*)&HD_A,sizeof(Header_A));
		pl.seekg(pos+(i*sizeof(Artykuly)),ios_base::beg);
		pl.write((char*)ART1,sizeof(Artykuly));
	}
	pl.close();
	return true;
}



//Funkcja dodaje nowego kontrahenta do bazy danych

bool Dodaj_Kontr(Kontrahent *KONTR1)
{
	fstream pl;
	int i,i1;

	if(KONTR1==NULL) return false;

	if(HD_K.count==0 && KONTR==NULL)
	{
		KONTR=new Kontrahent[Grow];
		Count_K=Grow;
	}else
	{
		if(Count_K<=HD_K.count)
		{
			GrowKR();
			Count_K=Count_K+Grow;
		}
	}
	
	memcpy(KONTR+(HD_K.count),KONTR1,sizeof(Kontrahent));
	HD_K.count++;
	HD_K.LastID++;
	memset(path1,0,300);
	sprintf(path1,"%sDBK.amb",path);
	pl.open(path1,ios_base::in|ios_base::out|ios_base::binary);
	if(!pl) return false;
	pl.write((char*)&HD_K,sizeof(Header_K));
	pl.seekg(0,ios_base::end);
	pl.write((char*)KONTR1,sizeof(Kontrahent));
	pl.close();
	return true;
}

	//Funkcja usuwa fakture

int Usun_Fakt(int fid)
{
	int l,m;
	char str[300];
	fstream pl;
	Header_F hdf_t;
	Fakt_Vat fv;
	int i;
	
	if(HD_FB.CountF<=0) return -2;
	if(fid<0 || fid> HD_FB.CountF) return -2;
	l=(fid+1)/Max_F;
	m=(fid+1) % Max_F;
	if(m>0)l++;
	else m=Max_F;
	memset(str,0,300);
	sprintf(str,"%sDBF%d.amb",path,l);
	pl.open(str,ios_base::in | ios_base::out | ios_base::binary);
	if(pl.fail()) return -1;
	if(l==1) pl.seekg(sizeof(Header_FB),ios_base::beg);
	for(i=0;i<m;i++)
	{
		pl.read((char*)&hdf_t,sizeof(Header_F));
		pl.seekg(sizeof(Fakt_Vat)*hdf_t.count,ios_base::cur);
	}
	HD_F[fid].is_ex=false;
	pl.write((char*)&HD_F[fid],sizeof(Header_F));
	pl.close();
	return 0;
}


	//Funkcja zapisuje zmiany w fakturze

int Save_Fakt(int fid)
{
	int l,m;
	char str[300];
	fstream pl;
	Header_F hdf_t;
	Fakt_Vat fv;
	int i;
	
	if(HD_FB.CountF<=0) return -2;
	if(fid<0 || fid> HD_FB.CountF) return -2;
	l=(fid+1)/Max_F;
	m=(fid+1)% Max_F;
	if(m>0)l++;
	else m=Max_F;
	memset(str,0,300);
	sprintf(str,"%sDBF%d.amb",path,l);
	pl.open(str,ios_base::in | ios_base::out | ios_base::binary);
	if(pl.fail()) return -1;
	if(l==1) pl.seekg(sizeof(Header_FB),ios_base::beg);
	for(i=0;i<m-1;i++)
	{
		pl.read((char*)&hdf_t,sizeof(Header_F));
		pl.seekg(sizeof(Fakt_Vat)*hdf_t.count,ios_base::cur);
	}
	pl.write((char*)&HD_F[fid],sizeof(Header_F));
	pl.close();
	return 0;
}


	//Funkcja dodaj¹ca fakturê do bazy danych

bool Dodaj_Fakt(Fakt_Vat *fvat , Header_F hdf)
{
	fstream pl;
	SYSTEMTIME st;
	int filec,lastc,i;
	char zn[300];
	Fakt_Vat *fvat1;

	if(fvat==NULL) return false; 
	else fvat1=fvat;

	if(HD_FB.CountF==Count_F) GrowF();
	HD_F[HD_FB.CountF]=hdf;
	if(HD_FB.CountF==0) filec=1;
	else
	{
		filec=HD_FB.CountF/Max_F;
		lastc=HD_FB.CountF%Max_F;
		if(lastc>=0) filec++;
	}
	GetSystemTime(&st);
	if(st.wYear!=HD_FB.rok)
	{
		HD_FB.rok=st.wYear;
		HD_FB.id=1;
	}else if(!hdf.is_korekta) HD_FB.id++;
	HD_FB.CountF++;
	memset(path1,0,300);
	sprintf(path1,"%sDBF1.amb",path);
	pl.open(path1,ios_base::out | ios_base::in | ios_base::binary);
	if(pl)
	{
		pl.write((char*)&HD_FB,sizeof(Header_FB));
		pl.close();
	}
	memset(zn,0,300);
	sprintf(zn,"%sDBF",path);
	if(lastc==0)
	{
		itoa(filec,zn+strlen(zn),10);
		strcpy(zn+strlen(zn),".amb");
		pl.open(zn,ios_base::out | ios_base::in | ios_base::trunc | ios_base::binary);
	} else
	{
		itoa(filec,zn+strlen(zn),10);
		strcpy(zn+strlen(zn),".amb");
		pl.open(zn,ios_base::out | ios_base::in | ios_base::binary);
	}
	pl.seekg(0,ios_base::end);
	pl.write((char*)&hdf,sizeof(Header_F));
	for(i=0;i<hdf.count;i++)
	{
		pl.write((char*)fvat1,sizeof(Fakt_Vat));
		fvat1++;
	}
	if(pl) pl.close();
	return true;
}
	


	//Funkcja zapisuj¹ca zmiany w bazie artyku³ów

bool Save_AR(Artykuly *ART1)
{
	fstream pl;
	LONGLONG pos;
	Artykuly art;
	
	if(ART1==NULL) return false;
	//if(!find_str("DBA.dll",&pos,"ADAPRIM_4321",12)) return false;
	pl.open("DBA.dll",ios_base::in|ios_base::out|ios_base::binary);
	if(!pl) return false;
	pos=422556;
	pos+=20;
	pos+=sizeof(Artykuly)*(ART1->indeks);
	pl.seekg(pos,ios_base::beg);
	pl.write((char*)ART1,sizeof(Artykuly));
	pl.close();
	return true;
}


//Funkcja zapisuj¹ca zmiany w bazie producebtów

bool Save_PR(Producent *PRT)
{
	fstream pl;
	int i;
	Producent prt;

	if(PRT==NULL) return false;
	memset(path1,0,300);
	sprintf(path1,"%sDBP.amb",path);
	pl.open(path1,ios_base::in|ios_base::out|ios_base::binary);
	if(!pl) return false;
	pl.seekg(sizeof(Header_P),ios_base::beg);
	while(!pl.eof())
	{
		pl.read((char*)&prt,sizeof(Producent));
		if(prt.IDP==PRT->IDP)
		{
			i=sizeof(Producent);
			pl.seekg(-i,ios_base::cur);
			pl.write((char*)PRT,sizeof(Producent));
			break;
		}
	}
	pl.close();
	return true;
}

	//Funkcja zapisuj¹ca zmiany w bazie kontrahentów

bool Save_KR(Kontrahent *KONTR1)
{
	fstream pl;
	int i;
	Kontrahent krt;

	if(KONTR1==NULL) return false;
	memset(path1,0,300);
	sprintf(path1,"%sDBK.amb",path);
	pl.open(path1,ios_base::in|ios_base::out|ios_base::binary);
	if(!pl) return false;
	pl.seekg(sizeof(Header_K),ios_base::beg);
	while(!pl.eof())
	{
		pl.read((char*)&krt,sizeof(Kontrahent));
		if(krt.IDK==KONTR1->IDK)
		{
			i=sizeof(Kontrahent);
			pl.seekg(-i,ios_base::cur);
			pl.write((char*)KONTR1,sizeof(Kontrahent));
			break;
		}
	}
	pl.close();
	return true;
}


	//Funkcja zapisuj¹ca do bazy dane przyjêcia towaru;

int Save_TW(Prz_Tow prz_t,float vat)
{
	fstream pl;
	int i,il,j;
	char zn[4];
	Prz_Tow p_t;
	bool is_e,is_v;
	LONGLONG pos;

	memset(path1,0,300);
	sprintf(path1,"%sDBT.amb",path);
	pl.open(path1,ios_base::in|ios_base::out|ios_base::binary);
	if(!pl)
	{
		memset(path1,0,300);
		sprintf(path1,"%sDBT.amb",path);
		pl.open(path1,ios_base::in|ios_base::out|ios_base::binary|ios_base::trunc);
		i=0;
		pl.write((char*)&i,sizeof(int));
		pl.close();
		pl.open(path1,ios_base::in|ios_base::out|ios_base::binary);
		if(!pl) return -1;
	}
	pos=sizeof(int);
	pl.read((char*)&il,sizeof(int));
	is_e=false;
	for(i=0;i<il;i++)
	{
		pl.read((char*) &p_t, sizeof(Prz_Tow));
		if(p_t.rok==prz_t.rok && p_t.miesiac==prz_t.miesiac)
		{
			p_t.cena_n+=prz_t.cena_n;
			pl.seekg(pos,ios_base::beg);
			is_v=false;
			for(j=0;j<50;j++)
			{
				if(p_t.rodz_v[j].rodz==vat)
				{
					p_t.rodz_v[j].wart+=(((vat/100)+1)*prz_t.cena_n)-prz_t.cena_n;
					is_v=true;
					break;
				}
			}
			if(!is_v)
			{
				for(j=0;j<50;j++)
				{
					if(p_t.rodz_v[j].rodz==0)
					{
						p_t.rodz_v[j].rodz=vat;
						p_t.rodz_v[j].wart=(((vat/100)+1)*prz_t.cena_n)-prz_t.cena_n;
						break;
					}
				}
			}
			pl.write((char*)&p_t,sizeof(Prz_Tow));
			is_e=true;
			break;
		}else pos+=sizeof(Prz_Tow);
	}
	if(!is_e)
	{
		il++;
		pl.seekg(0,ios_base::beg);
		pl.write((char*)&il,sizeof(int));
		pl.seekg(0,ios_base::end);
		for(j=0;j<50;j++)
		{
			prz_t.rodz_v[j].rodz=0;
			prz_t.rodz_v[j].wart=0;
		}
		if(vat!=0)
		{
			prz_t.rodz_v[0].rodz=vat;
			prz_t.rodz_v[0].wart=(((vat/100)+1)*prz_t.cena_n)-prz_t.cena_n;
		}
		pl.write((char*)&prz_t,sizeof(Prz_Tow));
	}
	pl.close();

	return 1;
	 
}


	//Funkcja zapisuj¹ca do bazy dane przyjêcia towaru;

int Save_SP(Prz_Tow prz_t,double vat)
{
	fstream pl;
	int i,il,j;
	char zn[4];
	Prz_Tow p_t;
	bool is_e,is_v;
	LONGLONG pos;

	memset(path1,0,300);
	sprintf(path1,"%sDBS.amb",path);
	pl.open(path1,ios_base::in|ios_base::out|ios_base::binary);
	if(!pl)
	{
		pl.open(path1,ios_base::in|ios_base::out|ios_base::binary|ios_base::trunc);
		i=0;
		pl.write((char*)&i,sizeof(int));
		pl.close();
		pl.open(path1,ios_base::in|ios_base::out|ios_base::binary);
		if(!pl) return -1;
	}
	pos=sizeof(int);
	pl.read((char*)&il,sizeof(int));
	is_e=false;
	for(i=0;i<il;i++)
	{
		pl.read((char*) &p_t, sizeof(Prz_Tow));
		if(p_t.rok==prz_t.rok && p_t.miesiac==prz_t.miesiac)
		{
			p_t.cena_n+=prz_t.cena_n;
			pl.seekg(pos,ios_base::beg);
			is_v=false;
			for(j=0;j<50;j++)
			{
				if(p_t.rodz_v[j].rodz==vat)
				{
					p_t.rodz_v[j].wart+=(((vat/100)+1)*prz_t.cena_n)-prz_t.cena_n;
					is_v=true;
					break;
				}
			}
			if(!is_v)
			{
				for(j=0;j<50;j++)
				{
					if(p_t.rodz_v[j].rodz==0)
					{
						p_t.rodz_v[j].rodz=vat;
						p_t.rodz_v[j].wart=(((vat/100)+1)*prz_t.cena_n)-prz_t.cena_n;
						break;
					}
				}
			}
			pl.write((char*)&p_t,sizeof(Prz_Tow));
			is_e=true;
			break;
		}else pos+=sizeof(Prz_Tow);
	}
	if(!is_e)
	{
		il++;
		pl.seekg(0,ios_base::beg);
		pl.write((char*)&il,sizeof(int));
		pl.seekg(0,ios_base::end);
		for(j=0;j<50;j++)
		{
			prz_t.rodz_v[j].rodz=0;
			prz_t.rodz_v[j].wart=0;
		}
		if(vat!=0)
		{
			prz_t.rodz_v[0].rodz=vat;
			prz_t.rodz_v[0].wart=(((vat/100)+1)*prz_t.cena_n)-prz_t.cena_n;
		}
		pl.write((char*)&prz_t,sizeof(Prz_Tow));
	}
	pl.close();

	return 1;
	 
}

	// Funkcja rysuj¹ca toolbar okna aplikacji

bool PaintTool(HDC hdc, int cx, int sy)
{
	SIZE sz;
	int x,y;
	LOGFONT lgf={15,9,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_ROMAN,"Times New Roman"};
	HFONT hf;

	if (hdc==NULL) return false;
	hbr=CreateSolidBrush(0xFDBFB3);
	hpn=CreatePen(PS_SOLID,2,(COLORREF)0xbababa);
	SelectObject(hdc,(HGDIOBJ)hbr);
	RoundRect(hdc,0,0,MAX_X-20,217,10,10);
	SelectObject(hdc,(HGDIOBJ)hpn);
	RoundRect(hdc,0,0,MAX_X-20,217,10,10);
	MoveToEx(hdc,1004,0,NULL);
	LineTo(hdc,1004,MAX_Y-20);
	DeleteObject((HGDIOBJ)hbr);
	//DeleteObject((HGDIOBJ)hpn);
	//hpn=CreatePen(PS_SOLID,1,(COLORREF)0xbababa);
	SelectObject(hdc,(HGDIOBJ)hpn);
	MoveToEx(hdc,10,15,NULL);
	LineTo(hdc,25,15);
	hf=CreateFontIndirect(&lgf);
	SelectObject(hdc,(HGDIOBJ)hf);
	GetTextExtentPoint32(hdc,"S",1,&sz);
	y=15-sz.cy/2;
	SetBkColor(hdc,0xFDBFB3);
	TextOut(hdc,35-sz.cx,y,"Szukaj Wed³ug",13);
	GetTextExtentPoint32(hdc,"Szukaj Wed³ug",13,&sz);
	MoveToEx(hdc,25+sz.cx,15,NULL);
	LineTo(hdc,25+sz.cx+185,15);
	LineTo(hdc,25+sz.cx+185,182);
	LineTo(hdc,10,182);
	LineTo(hdc,10,15);
	DeleteObject((HGDIOBJ)hf);
	DeleteObject((HGDIOBJ)hpn);
	SetBkColor(hdc,(COLORREF)0xFDBFB3);
	TextOut(hdc,350,15,"Nazwa Towaru",12);
	TextOut(hdc,350,68,"Nazwa Producenta",16);
	TextOut(hdc,350,121,"Stan",4);
	TextOut(hdc,575,15,"Cena Zakupu",11);
	TextOut(hdc,575,68,"Mar¿a",5);
	TextOut(hdc,575,121,"Cena Netto",10);
	TextOut(hdc,665,35,"-",1);
	TextOut(hdc,665,88,"-",1);
	TextOut(hdc,665,141,"-",1);
	TextOut(hdc,800,15,"VAT",3);
	TextOut(hdc,904,15,"Kod",3);
	TextOut(hdc,800,68,"Cena Brutto",11);
	TextOut(hdc,800,121,"Minimum",7);
	TextOut(hdc,890,88,"-",1);
	TextOut(hdc,890,141,"-",1);
	TextOut(hdc,443,141,"-",1);
	return true;
}


	//Funkcja drukuj¹ca fakturê VAT


bool is_print,is_prof;
int sel_item,duplex,color;
DWORD print_type;
PRINTER_INFO_2 *pr_i;
BYTE *bt;


int Print_Vat(Header_F Hdf, Fakt_Vat *Fvat, HWND hwd, HINSTANCE hs,bool is_pr)
{

	char text[350];

	bool bl;
	HANDLE hnd;
	HDC dc;
	HFONT font,font1;
	LOGFONT lgf;
	_DOCINFOA Doc_info;
	SIZE lps;
	HBRUSH hb;
	int i,j,k,pos,pos1,br,wyn,resz,wys,l,m;
	int max_x,max_y,max_c[11],posX[11];
	SIZE size;
	char zn[350];

	if (Fvat==NULL) return -1;
	is_prof=is_pr;
	DialogBox(hs,MAKEINTRESOURCE(ID_DLG_11),hwd,(DLGPROC)Dlg11Proc);

	if(is_print)
	{
	
		Doc_info.lpszDocName="Faktura VAT";
		Doc_info.lpszDatatype=pr_i[sel_item].pDatatype;
		Doc_info.lpszOutput=NULL;
	
		dc=CreateDC(pr_i[sel_item].pDriverName,pr_i[sel_item].pPrinterName,pr_i[sel_item].pPortName,pr_i[sel_item].pDevMode);
		if(!dc)
		{
			MessageBox(hwd,"Nie mo¿na pobraæ kontekstu drukarki","Wiadomoœæ",MB_OK);
			return 0;
		}else
		{
			if(print_type==F_OR_I_KO)m=2;else m=1;
			for(l=0;l<m;l++)
			{
				StartDocA(dc,&Doc_info);
				StartPage(dc);

				SetMapMode(dc,MM_LOMETRIC);
				GetWindowExtEx(dc,&lps);
				max_x=lps.cx;
				max_y=lps.cy-20;
				hb=CreateSolidBrush((COLORREF)0);
				lgf.lfWidth=20;
				lgf.lfHeight=40;
				lgf.lfWeight=FW_NORMAL;
				lgf.lfCharSet=EASTEUROPE_CHARSET;
				lgf.lfOutPrecision=OUT_DEFAULT_PRECIS;
				lgf.lfClipPrecision=CLIP_DEFAULT_PRECIS;
				lgf.lfQuality=DEFAULT_QUALITY;
				lgf.lfPitchAndFamily=DEFAULT_PITCH | FF_ROMAN;
				lgf.lfItalic=false;
				lgf.lfStrikeOut=false;
				lgf.lfUnderline=false;
				lgf.lfOrientation=0;
				lgf.lfEscapement=0;
				strcpy(lgf.lfFaceName,"Capri");
				font=CreateFontIndirect(&lgf);
				SelectObject(dc,(HGDIOBJ)font);
				SetTextColor(dc,(COLORREF)0);
				memset(text,0,350);
				strcpy(text,"Miejsce wyst.: ");
				strcpy(text+strlen(text),FRM.Miasto);
				TextOut(dc,1250,0,text,strlen(text));
				memset(text,0,350);
				strcpy(text,"Data Sprzeda¿y: ");
				itoa(Hdf.rok,text+strlen(text),10);
				strcpy(text+strlen(text),"-");
				itoa(Hdf.miesiac,text+strlen(text),10);
				strcpy(text+strlen(text),"-");
				itoa(Hdf.dzien,text+strlen(text),10);
				TextOut(dc,1250,-50,text,strlen(text));
				memset(text,0,350);
				strcpy(text,"Data Wystawienia: ");
				itoa(Hdf.rok,text+strlen(text),10);
				strcpy(text+strlen(text),"-");
				itoa(Hdf.miesiac,text+strlen(text),10);
				strcpy(text+strlen(text),"-");
				itoa(Hdf.dzien,text+strlen(text),10);
				TextOut(dc,1250,-100,text,strlen(text));
				SelectObject(dc,hb);
				Rectangle(dc,1005,-150,lps.cx+20,-155);
				DeleteObject(font);
				lgf.lfWidth=32;
				lgf.lfWeight=FW_BOLD;
				font=CreateFontIndirect(&lgf);
				SelectObject(dc,font);
				TextOut(dc,140,-175,"SPRZEDAWCA",10);
				DeleteFont(font);
				lgf.lfWidth=20;
				lgf.lfWeight=FW_NORMAL;
				font=CreateFontIndirect(&lgf);
				SelectObject(dc,font);
				TextOut(dc,140,-225,FRM.Nazwa,strlen(FRM.Nazwa));
				memset(text,0,350);
				strcpy(text,FRM.Adres);
				strcpy(text+strlen(text)," ");
				strcpy(text+strlen(text),FRM.Kod_Pocz);
				strcpy(text+strlen(text)," ");
				strcpy(text+strlen(text),FRM.Miasto);
				strcpy(text+strlen(text)," ");
				strcpy(text+strlen(text),FRM.Kraj);
				TextOut(dc,140,-275,text,strlen(text));
				memset(text,0,350);
				strcpy(text,"NIP: ");
				strcpy(text+strlen(text),FRM.NIP);
				strcpy(text+strlen(text)," REGON: ");
				strcpy(text+strlen(text),FRM.Regon);
				TextOut(dc,140,-325,text,strlen(text));
				memset(text,0,350);
				strcpy(text,"Tel.: ");
				strcpy(text+strlen(text),FRM.Tel);
				TextOut(dc,140,-375,text,strlen(text));
				SelectObject(dc,hb);
				Rectangle(dc,0,-425,2090,-430);
				DeleteObject(font);
				lgf.lfWidth=26;
				lgf.lfWeight=FW_BOLD;
				font=CreateFontIndirect(&lgf);
				SelectObject(dc,font);
				TextOut(dc,1050,-450,"NABYWCA",7);
				DeleteFont(font);
				lgf.lfWidth=20;
				lgf.lfWeight=FW_NORMAL;
				font=CreateFontIndirect(&lgf);
				SelectObject(dc,font);
				for(i=0;i<HD_K.count;i++)
				{
					if(KONTR[i].IDK==Hdf.IDK) break;
				}
				TextOut(dc,1050,-500,KONTR[i].Nazwa,strlen(KONTR[i].Nazwa));
				TextOut(dc,1050,-550,KONTR[i].Adres,strlen(KONTR[i].Adres));
				memset(text,0,350);
				strcpy(text,KONTR[i].KodPocz);

				strcpy(text+strlen(text)," ");
				strcpy(text+strlen(text),KONTR[i].Miasto);
				strcpy(text+strlen(text)," ");
				strcpy(text+strlen(text),KONTR[i].Kraj);
				TextOut(dc,1050,-600,text,strlen(text));
				memset(text,0,350);
				strcpy(text,"NIP: ");
				strcpy(text+strlen(text),KONTR[i].NIP);
				strcpy(text+strlen(text)," REGON: ");
				strcpy(text+strlen(text),KONTR[i].Regon);
				TextOut(dc,1050,-650,text,strlen(text));
				memset(text,0,350);
				strcpy(text,"Tel.: ");
				strcpy(text+strlen(text),KONTR[i].Tel);
				TextOut(dc,1050,-700,text,strlen(text));
				SelectObject(dc,hb);
				Rectangle(dc,0,-750,2090,-755);	
				DeleteObject(font);

				lgf.lfWeight=FW_SEMIBOLD;
				lgf.lfHeight=65;
				lgf.lfWidth=16;
				font=CreateFontIndirect(&lgf);
				memset(text,0,350);
				if(Hdf.is_korekta) sprintf(text,"Korekta Faktury VAT KR%s",Hdf.numer);
				else sprintf(text,"Faktura VAT %s",Hdf.numer); 
				if(l==1)strcpy(text+strlen(text)," kopia");else
				if(print_type==F_OR) strcpy(text+strlen(text)," orygina³"); else 
					if(print_type==F_KO) strcpy(text+strlen(text)," kopia");else
						if(print_type==F_OR_KO) strcpy(text+strlen(text)," orygina³/kopia");else
							if(print_type==F_OR_I_KO) strcpy(text+strlen(text)," orygina³");else
								if(print_type==F_PRO) strcpy(text+strlen(text)," proforma");
				SelectObject(dc,font);
				GetTextExtentPoint32(dc,text,strlen(text),&size);
				i=2100-size.cx;
				i=i/2;
				TextOut(dc,i,-800,text,strlen(text));
				DeleteObject(font);
				lgf.lfWidth=10;
				lgf.lfHeight=40;
				lgf.lfWeight=FW_SEMIBOLD;
				font=CreateFontIndirect(&lgf);
				SelectObject(dc,hb);
				Rectangle(dc,150,-920,1950,-922);
				Rectangle(dc,150,-921,152,-1024);
				Rectangle(dc,1950,-921,1948,-1024);
				Rectangle(dc,151,-1022,1950,-1024);
				DeleteObject(hb);
				hb=CreateSolidBrush((COLORREF)0xFDBFB3);
				SelectObject(dc,hb);
				Rectangle(dc,152,-922,1948,-1022);
				DeleteObject(hb);
				hb=CreateSolidBrush((COLORREF)0);
				SelectObject(dc,hb);
				Rectangle(dc,222,-921,224,-1021);
				Rectangle(dc,624,-921,626,-1021);
				Rectangle(dc,726,-921,728,-1021);
				Rectangle(dc,828,-921,830,-1021);
				Rectangle(dc,930,-921,932,-1021);
				Rectangle(dc,1032,-921,1034,-1021);			
				Rectangle(dc,1244,-921,1246,-1021);
				Rectangle(dc,1316,-921,1318,-1021);
				Rectangle(dc,1528,-921,1530,-1021);
				Rectangle(dc,1740,-921,1742,-1021);
				SelectObject(dc,font);
				SetBkColor(dc,(COLORREF)0xFDBFB3);
				GetTextExtentPoint32(dc,"LP",2,&size);i=(70-size.cx)/2;
				TextOut(dc,152+i,-952,"LP",2);
				posX[0]=162;
				GetTextExtentPoint32(dc,"NAZWA",5,&size);i=(400-size.cx)/2;
				TextOut(dc,224+i,-952,"NAZWA",5);
				posX[1]=234;
				GetTextExtentPoint32(dc,"PKWiU",5,&size);i=(100-size.cx)/2;
				TextOut(dc,626+i,-952,"PKWiU",5);
				posX[2]=636;
				GetTextExtentPoint32(dc,"ILOŒÆ",5,&size);i=(100-size.cx)/2;
				TextOut(dc,728+i,-952,"ILOŒÆ",5);
				posX[3]=738;
				GetTextExtentPoint32(dc,"JM",2,&size);i=(100-size.cx)/2;
				TextOut(dc,830+i,-952,"JM",2);
				posX[4]=840;
				GetTextExtentPoint32(dc,"RABAT",5,&size);i=(100-size.cx)/2;
				TextOut(dc,932+i,-932,"RABAT",5);
				posX[5]=942;
				GetTextExtentPoint32(dc,"(%)",3,&size);i=(100-size.cx)/2;
				TextOut(dc,932+i,-972,"(%)",3);
				GetTextExtentPoint32(dc,"CENA NETTO",10,&size);i=(210-size.cx)/2;
				TextOut(dc,1034+i,-952,"CENA NETTO",10);
				posX[6]=1044;
				GetTextExtentPoint32(dc,"VAT",3,&size);i=(70-size.cx)/2;
				TextOut(dc,1246+i,-932,"VAT",3);
				posX[7]=1256;
				GetTextExtentPoint32(dc,"(%)",3,&size);i=(70-size.cx)/2;
				TextOut(dc,1246+i,-972,"(%)",3);
				GetTextExtentPoint32(dc,"KWOTA NETTO",11,&size);i=(210-size.cx)/2;
				TextOut(dc,1318+i,-952,"KWOTA NETTO",11);
				posX[8]=1328;
				GetTextExtentPoint32(dc,"KWOTA VAT",9,&size);i=(210-size.cx)/2;
				TextOut(dc,1530+i,-952,"KWOTA VAT",9);
				posX[9]=1540;
				GetTextExtentPoint32(dc,"KWOTA BRUTTO",12,&size);i=(210-size.cx)/2;
				TextOut(dc,1742+i-3,-952,"KWOTA BRUTTO",12);
				posX[10]=1752;
				pos=-1024;
				DeleteObject(font);
				lgf.lfWeight=FW_NORMAL;
				font=CreateFontIndirect(&lgf);
				SetBkColor(dc,(COLORREF)0xFFFFFF);
				for(i=0;i<Hdf.count;i++)
				{
					br=1;
					memset(zn,0,350);
					itoa(Fvat[i].LP,zn,10);
					GetTextExtentPoint32(dc,zn,strlen(zn),&lps);
					max_c[0]=50;
					wyn=lps.cx/50;
					resz=lps.cx % 50;
					if(resz>0) wyn++;
					if(wyn>br) br=wyn;
				
					GetTextExtentPoint32(dc,Fvat[i].Nazwa,strlen(Fvat[i].Nazwa),&lps);
					max_c[1]=380;
					wyn=lps.cx/380;
					resz=lps.cx % 380;
					if(resz>0) wyn++;
					if(wyn>br) br=wyn;
					
					memset(zn,0,350);
					itoa(Fvat[i].PKWiU,zn,10);
					GetTextExtentPoint32(dc,zn,strlen(zn),&lps);
					max_c[2]=80;
					wyn=lps.cx/80;
					resz=lps.cx % 80;
					if(resz>0) wyn++;
					if(wyn>br) br=wyn;

					memset(zn,0,350);
					itoa(Fvat[i].ilosc,zn,10);
					GetTextExtentPoint32(dc,zn,strlen(zn),&lps);
					max_c[3]=80;
					wyn=lps.cx/80;
					resz=lps.cx % 80;
					if(resz>0) wyn++;
					if(wyn>br) br=wyn;

					GetTextExtentPoint32(dc,Fvat[i].JM,strlen(Fvat[i].JM),&lps);
					max_c[4]=80;
					wyn=lps.cx/80;
					resz=lps.cx % 80;
					if(resz>0) wyn++;
					if(wyn>br) br=wyn;
					
					memset(zn,0,350);
					dbl_str(Fvat[i].Rabat,zn,2,350);
					GetTextExtentPoint32(dc,zn,strlen(zn),&lps);
					max_c[5]=80;
					wyn=lps.cx/80;
					resz=lps.cx % 80;
					if(resz>0) wyn++;
					if(wyn>br) br=wyn;

					memset(zn,0,350);
					dbl_str(Fvat[i].Cena_Netto2,zn,2,350);
					GetTextExtentPoint32(dc,zn,strlen(zn),&lps);
					max_c[6]=190;
					wyn=lps.cx/190;
					resz=lps.cx % 190;
					if(resz>0) wyn++;
					if(wyn>br) br=wyn;

					memset(zn,0,350);
					dbl_str(Fvat[i].VAT,zn,2,350);
					GetTextExtentPoint32(dc,zn,strlen(zn),&lps);
					max_c[7]=50;
					wyn=lps.cx/50;
					resz=lps.cx % 50;
					if(resz>0) wyn++;
					if(wyn>br) br=wyn;

					memset(zn,0,350);
					dbl_str(Fvat[i].KW_Netto,zn,2,350);
					GetTextExtentPoint32(dc,zn,strlen(zn),&lps);
					max_c[8]=190;
					wyn=lps.cx/190;
					resz=lps.cx % 190;
					if(resz>0) wyn++;
					if(wyn>br) br=wyn;

					memset(zn,0,350);
					dbl_str(Fvat[i].KW_VAT,zn,2,350);
					GetTextExtentPoint32(dc,zn,strlen(zn),&lps);
					max_c[9]=190;
					wyn=lps.cx/190;
					resz=lps.cx % 190;
					if(resz>0) wyn++;
					if(wyn>br) br=wyn;

					memset(zn,0,350);
					dbl_str(Fvat[i].KW_Brutto,zn,2,350);
					GetTextExtentPoint32(dc,zn,strlen(zn),&lps);
					max_c[10]=190;
					wyn=lps.cx/190;
					resz=lps.cx % 190;
					if(resz>0) wyn++;
					if(wyn>br) br=wyn;

					wys=(br*40);
					wys=wys+20;
					if(-(pos-wys-2)>max_y)
					{
						EndPage(dc);
						StartPage(dc);
						pos=-252;
						SelectObject(dc,hb);
						Rectangle(dc,150,-250,1950,-252);
					}

					Rectangle(dc,150,pos,152,pos-wys-2);
					Rectangle(dc,1950,pos,1948,pos-wys-2);
					Rectangle(dc,150,pos-wys,1950,pos-wys-2);

					Rectangle(dc,222,pos,224,pos-wys);
					Rectangle(dc,624,pos,626,pos-wys);
					Rectangle(dc,726,pos,728,pos-wys);
					Rectangle(dc,828,pos,830,pos-wys);
					Rectangle(dc,930,pos,932,pos-wys);
					Rectangle(dc,1032,pos,1034,pos-wys);			
					Rectangle(dc,1244,pos,1246,pos-wys);
					Rectangle(dc,1316,pos,1318,pos-wys);
					Rectangle(dc,1528,pos,1530,pos-wys);
					Rectangle(dc,1740,pos,1742,pos-wys);
				
					for(k=0;k<11;k++)
					{
						pos1=pos-10;
						memset(zn,0,350);
						if(k==0) itoa(Fvat[i].LP,zn,10); else if(k==1) strcpy(zn,Fvat[i].Nazwa); else if(k==2) itoa(Fvat[i].PKWiU,zn,10);
						else if(k==3)itoa(Fvat[i].ilosc,zn,10); else if(k==4) strcpy(zn,Fvat[i].JM); else if(k==5) dbl_str(Fvat[i].Rabat,zn,2,350);
						else if(k==6) dbl_str(Fvat[i].Cena_Netto2,zn,2,350); else if(k==7) dbl_str(Fvat[i].VAT,zn,2,350);
						else if(k==8) dbl_str(Fvat[i].KW_Netto,zn,2,350); else if(k==9) dbl_str(Fvat[i].KW_VAT,zn,2,350);
						else if(k==10) dbl_str(Fvat[i].KW_Brutto,zn,2,350);
						if(zn[0]==0) continue;
						j=0;
				
						GetTextExtentPoint32(dc,zn,strlen(zn),&lps);
						wyn=lps.cx/max_c[k];
						resz=lps.cx%max_c[k];
						if(resz>0)wyn++;
						for(l=0;l<wyn;l++)
						{
							m=0;
							if(l+1==wyn)TextOut(dc,posX[k],pos1,zn+j,strlen(zn)-j);
							else
							{
								do
								{
									m++;
									GetTextExtentPoint32(dc,zn+j,m,&lps);
								}while(lps.cx<max_c[k]);
								TextOut(dc,posX[k],pos1,zn+j,m-1);
								j+=(m-1);
								pos1-=40;
							}
						}
						
					}
					pos=pos-wys-2;

				}

				if(-(pos-904)>max_y)
				{
					EndPage(dc);
					StartPage(dc);
					pos=-250;
				}
				else pos=pos-140;

				DeleteFont(font);
				lgf.lfHeight=50;
				lgf.lfWidth=23;
				lgf.lfWeight=FW_EXTRALIGHT;
				font=CreateFontIndirect(&lgf);
				lgf.lfWeight=FW_BOLD;
				font1=CreateFontIndirect(&lgf);
				SelectObject(dc,font);
				TextOut(dc,150,pos,"Razem: ",7);
				GetTextExtentPoint32(dc,"Razem: ",7,&lps);
				SelectObject(dc,font1);
				dbl_str(Hdf.KW_B,zn,2,350);
				sprintf(zn+strlen(zn)," %s",wal[cnt.def_wal].naz);
				TextOut(dc,150+lps.cx,pos,zn,strlen(zn));
				pos=pos-70;
				SelectObject(dc,font);
				TextOut(dc,150,pos,"W tym podatek VAT: ",19);
				GetTextExtentPoint32(dc,"W tym podatek VAT: ",19,&lps);
				SelectObject(dc,font1);
				dbl_str(Hdf.KW_V,zn,2,350);
				sprintf(zn+strlen(zn)," %s",wal[cnt.def_wal].naz);
				TextOut(dc,150+lps.cx,pos,zn,strlen(zn));
				pos=pos-70;
				SelectObject(dc,font);
				memset(zn,0,350);
				strcpy(zn,"Forma zap³aty - ");
				strcpy(zn+strlen(zn),Hdf.form_zap);
				strcpy(zn+strlen(zn),": ");
				TextOut(dc,150,pos,zn,strlen(zn));
				GetTextExtentPoint32(dc,zn,strlen(zn),&lps);
				SelectObject(dc,font1);
				dbl_str(Hdf.KW_B-Hdf.Zaplata,zn,2,350);
				sprintf(zn+strlen(zn)," %s",wal[cnt.def_wal].naz);
				TextOut(dc,150+lps.cx,pos,zn,strlen(zn));
				pos=pos-70;
				SelectObject(dc,font);
				TextOut(dc,150,pos,"Pozosta³o do zap³aty: ",22);
				GetTextExtentPoint32(dc,"Pozosta³o do zap³aty: ",22,&lps);
				SelectObject(dc,font1);
				dbl_str(Hdf.Zaplata,zn,2,350);
				sprintf(zn+strlen(zn)," %s",wal[cnt.def_wal].naz);
				TextOut(dc,150+lps.cx,pos,zn,strlen(zn));
				pos=pos-70;
				memset(zn,0,350);
				sprintf(zn,"Termin p³atnoœci: %d dni (%d-%d-%d)",Hdf.il_dni,Hdf.ter_plat.wDay,Hdf.ter_plat.wMonth,Hdf.ter_plat.wYear);
				SelectObject(dc,font);
				TextOut(dc,150,pos,zn,strlen(zn));
				pos=pos-450;
				DeleteFont(font);
				lgf.lfWeight=FW_LIGHT;
				lgf.lfWidth=10;
				lgf.lfHeight=30;
				font=CreateFontIndirect(&lgf);
				SelectObject(dc,hb);
				Rectangle(dc,150,pos,700,pos-2);
				Rectangle(dc,1400,pos,1950,pos-2);
				pos=pos-12;
				SelectObject(dc,font);
				TextOut(dc,150,pos,"Podpis osoby upowa¿nionej do wystawienia faktury",48);
				TextOut(dc,1400,pos,"Podpis osoby upowa¿nionej do odebrania faktury",46);
				EndPage(dc);
				EndDoc(dc);
			}
			DeleteObject(font);
			DeleteObject(font1);
			DeleteObject(hb);
			DeleteDC(dc);	
				
		}
	}

	if(pr_i!=NULL) delete pr_i;
	bt=NULL;
	pr_i=NULL;

	return 1;
}



LRESULT _stdcall Dlg11Proc(HWND hwd, int code, WPARAM wp ,LPARAM lp)
{
	bool bl;
	int i;
	DWORD pcn,pcr,sbuf;
	static DWORD buf;
	static char *zn;
	int licz;
	HANDLE hnd;
	DWORD ptype,result;
	BYTE *bt;
	DWORD size,nsize,rsize;
	HDC dc;

	switch(code)
	{
		case WM_INITDIALOG:
			{
				if(!is_prof) CheckDlgButton(hwd,DLG11_RB4,BST_CHECKED);
				else
				{
					CheckDlgButton(hwd,DLG11_RB5,BST_CHECKED);
					EnableWindow(GetDlgItem(hwd,DLG11_RB1),false);
					EnableWindow(GetDlgItem(hwd,DLG11_RB2),false);
					EnableWindow(GetDlgItem(hwd,DLG11_RB3),false);
					EnableWindow(GetDlgItem(hwd,DLG11_RB4),false);

				}
				CheckDlgButton(hwd,DLG11_RB6,BST_CHECKED);
				CheckDlgButton(hwd,DLG11_RB9,BST_CHECKED);
				CheckDlgButton(hwd,DLG11_RB11,BST_CHECKED);
				sbuf=sizeof(BYTE);
				pcn=0;
				pcr=0;
				bt=new BYTE;
				bl=EnumPrinters(PRINTER_ENUM_LOCAL,NULL,2,bt,sbuf,&pcn,&pcr);
				if(!bl)
				{
					delete bt;
					bt=new BYTE[pcn];
					sbuf=pcn;
					memset(bt,0,sbuf);
					bl=EnumPrinters(PRINTER_ENUM_LOCAL,NULL,2,bt,sbuf,&pcn,&pcr);
				}
				buf=350;
				zn = new char[buf];
				memset(zn,0,buf);
				bl=GetDefaultPrinter(zn,&buf);
				if(!bl)
				{
					delete zn;
					zn = new char[buf];
					bl=GetDefaultPrinter(zn,&buf);
				}
				pr_i=(PRINTER_INFO_2*)bt;
				licz=0;
				buf=0;
				do
				{
					if(!IsBadStringPtr(pr_i[licz].pPrinterName,350))
					{
						ComboBox_AddString(GetDlgItem(hwd,DLG11_CB1),pr_i[licz].pPrinterName);
						if(strcmp(pr_i[licz].pPrinterName,zn)==0) sel_item=licz;
						if(strlen(pr_i[licz].pPrinterName)>buf) buf=strlen(pr_i[licz].pPrinterName);
						licz++;
					}
				}while(!IsBadStringPtr(pr_i[licz].pPrinterName,350));
				licz--;
				ComboBox_SetCurSel(GetDlgItem(hwd,DLG11_CB1),sel_item);
				if(pr_i[sel_item].pDevMode->dmFields&DM_DUPLEX)
				{
					EnableWindow(GetDlgItem(hwd,DLG11_RB7),true);
					EnableWindow(GetDlgItem(hwd,DLG11_RB8),true);
				}else
				{
					CheckDlgButton(hwd,DLG11_RB6,BST_CHECKED);
					CheckDlgButton(hwd,DLG11_RB7,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG11_RB8,BST_UNCHECKED);
					EnableWindow(GetDlgItem(hwd,DLG11_RB7),false);
					EnableWindow(GetDlgItem(hwd,DLG11_RB8),false);
				}
				
				if(pr_i[sel_item].pDevMode->dmFields&DM_COLOR)
				{
					EnableWindow(GetDlgItem(hwd,DLG11_RB11),true);
					EnableWindow(GetDlgItem(hwd,DLG11_RB12),true);
				}else
				{
					CheckDlgButton(hwd,DLG11_RB12,BST_CHECKED);
					EnableWindow(GetDlgItem(hwd,DLG11_RB11),false);
				}
				
			}
		case WM_COMMAND:
			{
				if(LOWORD(wp)==DLG11_CB1)
				{
					if(HIWORD(wp)==CBN_SELENDOK)
					{
						memset(zn,0,buf);
						sel_item=ComboBox_GetCurSel(GetDlgItem(hwd,DLG11_CB1));
						ComboBox_SetCurSel(GetDlgItem(hwd,DLG11_CB1),sel_item);
						ComboBox_GetText(GetDlgItem(hwd,DLG11_CB1),zn,buf);
						if(pr_i[sel_item].pDevMode->dmFields&DM_DUPLEX)
						{
							EnableWindow(GetDlgItem(hwd,DLG11_RB7),true);
							EnableWindow(GetDlgItem(hwd,DLG11_RB8),true);
						}else
						{
							CheckDlgButton(hwd,DLG11_RB6,BST_CHECKED);
							CheckDlgButton(hwd,DLG11_RB7,BST_UNCHECKED);
							CheckDlgButton(hwd,DLG11_RB8,BST_UNCHECKED);
							EnableWindow(GetDlgItem(hwd,DLG11_RB7),false);
							EnableWindow(GetDlgItem(hwd,DLG11_RB8),false);
						}
						
						if(pr_i[sel_item].pDevMode->dmFields&DM_COLOR)
						{
							EnableWindow(GetDlgItem(hwd,DLG11_RB12),true);
							EnableWindow(GetDlgItem(hwd,DLG11_RB11),true);
						}else
						{
							CheckDlgButton(hwd,DLG11_RB12,BST_CHECKED);
							EnableWindow(GetDlgItem(hwd,DLG11_RB11),false);
						}
						break;
					}
					if(HIWORD(wp)==CBN_EDITCHANGE)
					{
						SetWindowText(GetDlgItem(hwd,DLG11_CB1),zn);
						break;
					}
				}

				if(wp==DLG11_RB1||wp==DLG11_RB2||wp==DLG11_RB3||wp==DLG11_RB4||wp==DLG11_RB5)
				{
					if(wp==DLG11_RB1)
					{
						CheckDlgButton(hwd,DLG11_RB1,BST_CHECKED);
						CheckDlgButton(hwd,DLG11_RB2,BST_UNCHECKED);
						CheckDlgButton(hwd,DLG11_RB3,BST_UNCHECKED);
						CheckDlgButton(hwd,DLG11_RB4,BST_UNCHECKED);
						CheckDlgButton(hwd,DLG11_RB5,BST_UNCHECKED);
					}else
					if(wp==DLG11_RB2)
					{
						CheckDlgButton(hwd,DLG11_RB1,BST_UNCHECKED);
						CheckDlgButton(hwd,DLG11_RB2,BST_CHECKED);
						CheckDlgButton(hwd,DLG11_RB3,BST_UNCHECKED);
						CheckDlgButton(hwd,DLG11_RB4,BST_UNCHECKED);
						CheckDlgButton(hwd,DLG11_RB5,BST_UNCHECKED);
					}else
					if(wp==DLG11_RB3)
					{
						CheckDlgButton(hwd,DLG11_RB1,BST_UNCHECKED);
						CheckDlgButton(hwd,DLG11_RB2,BST_UNCHECKED);
						CheckDlgButton(hwd,DLG11_RB3,BST_CHECKED);
						CheckDlgButton(hwd,DLG11_RB4,BST_UNCHECKED);
						CheckDlgButton(hwd,DLG11_RB5,BST_UNCHECKED);
					}else
					if(wp==DLG11_RB4)
					{
						CheckDlgButton(hwd,DLG11_RB1,BST_UNCHECKED);
						CheckDlgButton(hwd,DLG11_RB2,BST_UNCHECKED);
						CheckDlgButton(hwd,DLG11_RB3,BST_UNCHECKED);
						CheckDlgButton(hwd,DLG11_RB4,BST_CHECKED);
						CheckDlgButton(hwd,DLG11_RB5,BST_UNCHECKED);
					}else
					if(wp==DLG11_RB5)
					{
						CheckDlgButton(hwd,DLG11_RB1,BST_UNCHECKED);
						CheckDlgButton(hwd,DLG11_RB2,BST_UNCHECKED);
						CheckDlgButton(hwd,DLG11_RB3,BST_UNCHECKED);
						CheckDlgButton(hwd,DLG11_RB4,BST_UNCHECKED);
						CheckDlgButton(hwd,DLG11_RB5,BST_CHECKED);
					}
					break;
				}
				if(wp==DLG11_RB6||wp==DLG11_RB7||wp==DLG11_RB8)
				{
					if(wp==DLG11_RB6)
					{
						CheckDlgButton(hwd,DLG11_RB6,BST_CHECKED);
						CheckDlgButton(hwd,DLG11_RB7,BST_UNCHECKED);
						CheckDlgButton(hwd,DLG11_RB8,BST_UNCHECKED);
					}else
					if(wp==DLG11_RB7)
					{
						CheckDlgButton(hwd,DLG11_RB6,BST_UNCHECKED);
						CheckDlgButton(hwd,DLG11_RB7,BST_CHECKED);
						CheckDlgButton(hwd,DLG11_RB8,BST_UNCHECKED);
					}else
					if(wp==DLG11_RB8)
					{
						CheckDlgButton(hwd,DLG11_RB6,BST_UNCHECKED);
						CheckDlgButton(hwd,DLG11_RB7,BST_UNCHECKED);
						CheckDlgButton(hwd,DLG11_RB8,BST_CHECKED);
					}
					break;
				}
				if(wp==DLG11_RB9||wp==DLG11_RB10)
				{
					if(wp==DLG11_RB9)
					{
						CheckDlgButton(hwd,DLG11_RB9,BST_CHECKED);
						CheckDlgButton(hwd,DLG11_RB10,BST_UNCHECKED);
					}else
					if(wp==DLG11_RB10)
					{
						CheckDlgButton(hwd,DLG11_RB9,BST_UNCHECKED);
						CheckDlgButton(hwd,DLG11_RB10,BST_CHECKED);
					}
					break;
				}

				if(wp==DLG11_RB11||wp==DLG11_RB12)
				{
					if(wp==DLG11_RB11)
					{
						CheckDlgButton(hwd,DLG11_RB11,BST_CHECKED);
						CheckDlgButton(hwd,DLG11_RB12,BST_UNCHECKED);
					}else
					if(wp==DLG11_RB12)
					{
						CheckDlgButton(hwd,DLG11_RB11,BST_UNCHECKED);
						CheckDlgButton(hwd,DLG11_RB12,BST_CHECKED);
					}
					break;
				}
				if(wp==DLG11_B2)		//Anuluj
				{

					is_print=false;
					DestroyWindow(hwd);
					break;
				}
				if(wp==DLG11_B1)		//Drukuj
				{
					is_print=true;
					if(IsDlgButtonChecked(hwd,DLG11_RB1)) print_type=F_OR;
						else if(IsDlgButtonChecked(hwd,DLG11_RB2)) print_type=F_KO;
							else if(IsDlgButtonChecked(hwd,DLG11_RB3)) print_type=F_OR_KO;
								else if(IsDlgButtonChecked(hwd,DLG11_RB4)) print_type=F_OR_I_KO;
									else if(IsDlgButtonChecked(hwd,DLG11_RB5)) print_type=F_PRO;
					if(IsDlgButtonChecked(hwd,DLG11_RB6)) pr_i[sel_item].pDevMode->dmDuplex=DMDUP_SIMPLEX;
						else if(IsDlgButtonChecked(hwd,DLG11_RB7)) pr_i[sel_item].pDevMode->dmDuplex=DMDUP_VERTICAL;
							else if(IsDlgButtonChecked(hwd,DLG11_RB8)) pr_i[sel_item].pDevMode->dmDuplex=DMDUP_HORIZONTAL;
					if(IsDlgButtonChecked(hwd,DLG11_RB9)) pr_i[sel_item].pDevMode->dmOrientation=DMORIENT_PORTRAIT;
						else if(IsDlgButtonChecked(hwd,DLG11_RB10)) pr_i[sel_item].pDevMode->dmOrientation=DMORIENT_LANDSCAPE;
					if(IsDlgButtonChecked(hwd,DLG11_RB11)) pr_i[sel_item].pDevMode->dmColor=DMCOLOR_COLOR;
						else if(IsDlgButtonChecked(hwd,DLG11_RB12)) pr_i[sel_item].pDevMode->dmColor=DMCOLOR_MONOCHROME;

					DestroyWindow(hwd);
					break;
				}
				break;
			}
		case WM_CLOSE:
			{
				DestroyWindow(hwd);
				break;
			}

		case WM_DESTROY:
			{
				if(zn!=NULL) delete zn;
				EndDialog(hwd,0);
				break;
			}
		default : return DefDlgProc(GetParent(hwd),code,wp,lp);
	}
	return 0;
}


		//Funkcja ³aduj¹ca zapisane kasy z biblioteki

int Init_KS()
{
	HMODULE hm;
	int (*pf)(void);
	int (*pf1)(KASA_ *KS , int c);
	int i;
	hm=LoadLibrary("fisk.dll");
	if(hm==NULL) return -1;
	Fget_Count=(get_Count)GetProcAddress(hm,"get_Count");
	if(Fget_Count==NULL) return 0;
	Count_Kas=(*Fget_Count)();
	Fget_Max=(get_Max)GetProcAddress(hm,"get_Max");
	if(Fget_Max==NULL) return 0;
	MAX_Kas=(*Fget_Max)();
	Fget_All=(get_All)GetProcAddress(hm,"get_All");
	if(Fget_All==NULL) return 0;
	KS= new KASA_[MAX_Kas];
	Kas_ind=new int[MAX_Kas];
	i=(*Fget_All)(KS,MAX_Kas);
	for(i=0;i<MAX_Kas;i++)
	{
		KS[i]=KS[i];
	}
	Fget_Default=(get_Default)GetProcAddress(hm,"get_Default");
	if(Fget_Default==NULL) return 0;
	Default=(*Fget_Default)();
	FreeLibrary(hm);
	return 1;
}

	//funkcja zapisuje konfiguracjê kas fiskalnych

int Save_KS(bool b)
{
	bool bl;
	LONGLONG pos;
	fstream pl;
	int i;

	if(KS==NULL) return -2;
	bl=find_str("fisk.dll",&pos,"ADAPRIM_1234",12);
	if(!bl) return -1;
	pl.open("fisk.dll",ios_base::in|ios_base::out|ios_base::binary);
	if(!pl.is_open()) return 0;
	pl.seekg(pos+16,ios_base::beg);
	pl.write((char*)&Count_Kas,sizeof(int));
	pl.write((char*)&Default,sizeof(int));
	if(!b) 
	{	
		pl.close();
		return 1;
	}
	for(i=0;i<MAX_Kas;i++)
	{
		pl.write((char*)(KS+i),sizeof(KASA_));
	}
	pl.close();
	return 1;
}


int Save_Cnt();

	//Funkcja zapisuje formy zap³aty do bilbioteki


int Save_FZ()
{
	bool bl;
	LONGLONG pos;
	fstream pl;
	int i;

	if( (i=Save_Cnt())!= 1)
	return i;
	bl=find_str("attr_kon.dll",&pos,"ADAPRIM_5678",12);
	if(!bl) return -1;
	pl.open("attr_kon.dll",ios_base::in|ios_base::out|ios_base::binary);
	if(!pl.is_open()) return 0;
	pl.seekg(pos+16,ios_base::beg);

	for(i=0;i<99;i++)
	{
		pl.write((char*)(&form_zap[i]),sizeof(FORM_ZAP));
	}
	pl.close();
	return 1;
}



//Funkcja zapisuje waluty do bilbioteki



int Save_Wal()
{
	bool bl;
	LONGLONG pos;
	fstream pl;
	int i;

	if( (i=Save_Cnt())!= 1)
	return i;
	bl=find_str("attr_kon.dll",&pos,"ADAPRIM_1234",12);
	if(!bl) return -1;
	pl.open("attr_kon.dll",ios_base::in|ios_base::out|ios_base::binary);
	if(!pl.is_open()) return 0;
	pl.seekg(pos+16,ios_base::beg);

	for(i=0;i<99;i++)
	{
		pl.write((char*)(&wal[i]),sizeof(WALUTA));
	}
	pl.close();
	return 1;
}



//Funkcja zapisuje stawki vat do bilbioteki



int Save_Vat()
{
	bool bl;
	LONGLONG pos;
	fstream pl;
	int i;

	if( (i=Save_Cnt())!= 1)
	return i;
	bl=find_str("attr_kon.dll",&pos,"ADAPRIM_8765",12);
	if(!bl) return -1;
	pl.open("attr_kon.dll",ios_base::in|ios_base::out|ios_base::binary);
	if(!pl.is_open()) return 0;
	pl.seekg(pos+16,ios_base::beg);

	for(i=0;i<99;i++)
	{
		pl.write((char*)(&Vat[i]),sizeof(ST_VAT));
	}
	pl.close();
	return 1;
}


//Funkcja zapisuje grupy towarowe do bilbioteki



int Save_GR()
{
	bool bl;
	LONGLONG pos;
	fstream pl;
	int i;

	if( (i=Save_Cnt())!= 1)
	return i;
	bl=find_str("attr_kon.dll",&pos,"ADAPRIM_4167",12);
	if(!bl) return -1;
	pl.open("attr_kon.dll",ios_base::in|ios_base::out|ios_base::binary);
	if(!pl.is_open()) return 0;
	pl.seekg(pos+16,ios_base::beg);

	for(i=0;i<99;i++)
	{
		pl.write((char*)(&GR[i]),sizeof(GR_T));
	}
	pl.close();
	return 1;
}


//Funkcja zapisuje jednostki miary do bilbioteki



int Save_JM()
{
	bool bl;
	LONGLONG pos;
	fstream pl;
	int i;

	if( (i=Save_Cnt())!= 1)
	return i;
	bl=find_str("attr_kon.dll",&pos,"ADAPRIM_2685",12);
	if(!bl) return -1;
	pl.open("attr_kon.dll",ios_base::in|ios_base::out|ios_base::binary);
	if(!pl.is_open()) return 0;
	pl.seekg(pos+16,ios_base::beg);

	for(i=0;i<99;i++)
	{
		pl.write((char*)(&jm[i]),sizeof(JM));
	}
	pl.close();
	return 1;
}

//Funkcja zapisuje licznik walut i form zap³aty do bilbioteki


int Save_Cnt()
{
	bool bl;
	LONGLONG pos;
	fstream pl;
	int i;

	bl=find_str("attr_kon.dll",&pos,"ADAPRIM_321",11);
	if(!bl) return -1;
	pl.open("attr_kon.dll",ios_base::in|ios_base::out|ios_base::binary);
	if(!pl.is_open()) return 0;
	pl.seekg(pos+12,ios_base::beg);
	pl.write((char*)(&cnt),sizeof(COUNT));
	pl.close();
	return 1;
}



//Funkcja zapisuje przedrostek numeracji faktury VAt do bazy


int Save_NV()
{
	bool bl;
	LONGLONG pos;
	fstream pl;
	int i;

	bl=find_str("attr_kon.dll",&pos,"ADAPRIM_1001",12);
	if(!bl) return -1;
	pl.open("attr_kon.dll",ios_base::in|ios_base::out|ios_base::binary);
	if(!pl.is_open()) return 0;
	pl.seekg(pos+16,ios_base::beg);
	pl.write((char*)(&NV),sizeof(N_VAT));
	pl.close();
	return 1;
}



		//funkcja dodaje iloœæ dni do daty w formacie LPSYSTEMTIME



SYSTEMTIME Time_Add(SYSTEMTIME tm, DWORD day)
{
	int i, md, dv;
	WORD _year, _month, _day;
	char zn[7];
	bool is_prz, kon;
	SYSTEMTIME _tm;


	if(day<=0) return tm;
	_tm = tm;
	memset(zn,0,7);
	itoa((int)tm.wYear,zn,10);
	if(zn[strlen(zn)-1]=='0' && zn[strlen(zn)-2]=='0') i=400; else i=4;
	md= tm.wYear % i;
	if(md==0)
	{
		_year= day/366;
		i=day % 366;
		is_prz=true;
	}else
	{
		_year= day/365;
		i=day % 365;
		is_prz=false;
	}
	kon= false;
	_year=_year+tm.wYear;
	_month=tm.wMonth;
	_day=tm.wDay;
	do
	{
		if(_month==1 || _month==3 || _month==5 || _month==7 || _month==8 || _month==10 || _month==12) 
			dv=31;
		else if(_month==2)
		{
			if(is_prz) dv=29; else dv=28;
		}
		else dv=30;
		md=dv-_day;
		if(i<md)
		{
			_day+=i;
			kon=true;
		}else
		{
			i=i-(md+1);
			_month++;
			if(_month>12)
			{
				_month=1;
				_year++;
			}
			_day=1;
		}
	}while(!kon);

	_tm.wYear=_year;
	_tm.wMonth=_month;
	_tm.wDay=_day;

	return _tm;
}

//funkcja odczytuje nazwy grup z kasy

int get_gr(KASA_ *KT, GR_T *gr_t,int * out)
{
	fstream pl;
	char zn;
	int i,j,licz,ind,licz1;
	WIN32_FIND_DATA fdt;
	HANDLE hn;
	char txt[150];

	if(gr_t==NULL || KT==NULL || out==NULL) return -1;
	i=get_data(*KT,NULL,_OGrupa,NULL,0);
	if(i==-1) return -1;
	else if(i>0) return i;
	hn=FindFirstFile("Config/pin.out",&fdt);
	if(hn==INVALID_HANDLE_VALUE) return -1;

	pl.open("Config/pin.out",ios_base::in | ios_base::binary);
	if(!pl) return -1;
	licz=0;
	i=0;
	do
	{
		zn=pl.get();
		if(zn==10) i++;
		licz++;
	}while(licz<fdt.nFileSizeLow);
	i=i-3;
	if(i>*out) 
	{
		*out=i;
		pl.close();
		return -2;
	}
	*out=i;
	licz=0;
	pl.seekg(0,ios_base::beg);
	do
	{
		zn=pl.get();
		licz++;
	}while(zn!='$' && licz<fdt.nFileSizeLow);

	ind=0;

	for(i=0;i<*out;i++)
	{
		memset(txt,0,150);
		do
		{
			zn=pl.get();
			licz++;
		}while(zn!='\t' && licz<fdt.nFileSizeLow);
		
		licz1=0;
		do
		{
			zn=pl.get();
			licz++;
			if(zn!=10 && zn!=13)
			{
				txt[licz1]=zn;
				licz1++;
			}

		}while(zn!='\n' && licz<fdt.nFileSizeLow);
		j=strlen(txt)-1;
		while(txt[j]==32) 
		{
			txt[j]=0;
			j--;
		}
		strncpy(gr_t[ind].nazwa,txt,50);
		ind++;
	}

	pl.close();
	return 0;

}


	//funkcja odczytuje nazwy jednostek z kasy

int get_jm(KASA_ *KT, JM *jm_t,int * out)
{
	fstream pl;
	char zn;
	int i,j,licz,licz1,ind;
	WIN32_FIND_DATA fdt;
	HANDLE hn;
	char txt[150];

	if(jm_t==NULL || KT==NULL || out==NULL) return -1;
	i=get_data(*KT,NULL,_OJednost,NULL,0)==-1;
	if(i==-1) return -1;
	else if(i>0) return i;
	hn=FindFirstFile("Config/pin.out",&fdt);
	if(hn==INVALID_HANDLE_VALUE) return -1;

	pl.open("Config/pin.out",ios_base::in | ios_base::binary);
	if(!pl) return -1;
	licz=0;
	i=*out;
	memset(jm_t,0,sizeof(JM)*i);
	i=0;
	do
	{
		zn=pl.get();
		if(zn==10) i++;
		licz++;
	}while(licz<fdt.nFileSizeLow);

	if(i>*out) 
	{
		*out=i;
		pl.close();
		return -2;
	}
	*out=i-3;
	licz=0;
	pl.seekg(0,ios_base::beg);
	do
	{
		zn=pl.get();
		licz++;
	}while(zn!='$' && licz<fdt.nFileSizeLow);

	ind=0;

	for(i=0;i<*out;i++)
	{
		memset(txt,0,150);
		do
		{
			zn=pl.get();
			licz++;
		}while(zn!='\t' && licz<fdt.nFileSizeLow);
		
		licz1=0;
		do
		{
			zn=pl.get();
			licz++;
			if(zn!=10 && zn!=13)
			{
				txt[licz1]=zn;
				licz1++;
			}

		}while(zn!='\n' && licz<fdt.nFileSizeLow);
		itoa(ind+1,jm_t[ind].naz,10);
		j=strlen(txt)-1;
		while(txt[j]==32) 
		{
			txt[j]=0;
			j--;
		}
		strncpy(jm_t[ind].znak,txt,25);
		ind++;
	}

	pl.close();
	return 0;

}

//funkcja odczytuje stawki vat z kasy

int get_vat(KASA_ *KT, ST_VAT *vat_t,int * out)
{
	fstream pl;
	char zn;
	int i,licz,ind;
	WIN32_FIND_DATA fdt;
	HANDLE hn;
	char txt[150];

	if(vat_t==NULL || KT==NULL || out==NULL) return -1;
	i=*out;
	memset(vat_t,0,sizeof(ST_VAT)*i);
	for(ind=0;ind<i;ind++)
	{
		vat_t[ind].vat=-1;
	}
	i=get_data(*KT,NULL,_OPodatek,NULL,0)==-1;
	if(i==-1) return -1;
	else if(i>0) return i;
	hn=FindFirstFile("Config/pin.out",&fdt);
	if(hn==INVALID_HANDLE_VALUE) return -1;

	pl.open("Config/pin.out",ios_base::in | ios_base::binary);
	if(!pl) return -1;
	licz=0;
	
	do
	{
		zn=pl.get();
		licz++;
	}while(zn!='$' && licz<fdt.nFileSizeLow);
	i=0;
	do
	{
		zn=pl.get();
		if(zn==9) i++;
		licz++;
	}while(licz<fdt.nFileSizeLow);
	i++;
	if(i>*out)
	{
		*out=i;
		pl.close();
		return -2;
	}
	i=0;
	pl.seekg(0,ios_base::beg);
	licz=0;
	do
	{
		zn=pl.get();
		licz++;
	}while(zn!='$' && licz<fdt.nFileSizeLow);
	do
	{
		memset(txt,0,150);
		ind=0;
		do
		{
			zn=pl.get();
			licz++;
			if(zn!='\t') 
			{
				txt[ind]=zn;
				ind++;
			}
		}while(zn!='\t' && licz<fdt.nFileSizeLow);
		if(strncmp(txt,"ZWOLNIONA",9)==0)
		{
			vat_t[i].vat=0;
			strcpy(vat_t[i].opis,"ZWOLNIONA");
		}else if(stricmp(txt,"REZERWA")==0)
		{
			vat_t[i].vat=0;
			strcpy(vat_t[i].opis,"REZERWA");
		}else
		vat_t[i].vat=atof(txt);

		i++;
	}while(zn!='\n' && licz<fdt.nFileSizeLow && i<*out);
	vat_t[i].vat=-1;
	pl.close();
	return 0;

}

//funkcja odczytuje nazwy form zap³aty z kasy

int get_zap(KASA_ *KT, FORM_ZAP *zap_t,int * out)
{
	fstream pl;
	char zn;
	int i,j,licz,ind,licz1;
	WIN32_FIND_DATA fdt;
	HANDLE hn;
	char txt[150];

	if(zap_t==NULL || KT==NULL || out==NULL) return -1;
	i=get_data(*KT,NULL,_OPlat,NULL,0);
	if(i==-1) return -1;
	else if(i>0) return i;
	hn=FindFirstFile("Config/pin.out",&fdt);
	if(hn==INVALID_HANDLE_VALUE) return -1;

	pl.open("Config/pin.out",ios_base::in | ios_base::binary);
	if(!pl) return -1;
	licz=0;
	i=0;
	do
	{
		zn=pl.get();
		if(zn==10) i++;
		licz++;
	}while(licz<fdt.nFileSizeLow);
	i=i-3;
	if(i>*out) 
	{
		*out=i;
		pl.close();
		return -2;
	}
	*out=i;
	licz=0;
	pl.seekg(0,ios_base::beg);
	do
	{
		zn=pl.get();
		licz++;
	}while(zn!='$' && licz<fdt.nFileSizeLow);

	ind=0;

	for(i=0;i<*out;i++)
	{
		memset(txt,0,150);
		do
		{
			zn=pl.get();
			licz++;
		}while(zn!='\t' && licz<fdt.nFileSizeLow);
		
		licz1=0;
		do
		{
			zn=pl.get();
			licz++;
			if(zn!=10 && zn!=13)
			{
				txt[licz1]=zn;
				licz1++;
			}

		}while(zn!='\n' && licz<fdt.nFileSizeLow);
		j=strlen(txt)-1;
		while(txt[j]==32) 
		{
			txt[j]=0;
			j--;
		}
		strncpy(zap_t[ind].naz,txt,25);
		ind++;
	}

	pl.close();
	return 0;

}


	// funkcja zczytuje z pliku wyjœciowego kasy fiskalnej towary do tablicy

int get_tow(Artykuly *Art,int *indeks,JM *jm,ST_VAT *vt, GR_T *grt, int il,int il_gr, int cnt)
{
	fstream pl;
	char txt[350];
	char zn;
	int i,j;
	LONGLONG l1,l2;
	HANDLE hn;
	WIN32_FIND_DATA wfd;

	hn=FindFirstFile("Config/pin.out",&wfd);
	if(hn==INVALID_HANDLE_VALUE) return -1;
	if(Art==NULL || indeks== NULL || jm==NULL || vt==NULL) return -1;
	pl.open("Config/pin.out",ios_base::in | ios_base::binary);
	if(!pl) return -1;
	
	for(j=0;j<cnt;j++)
	{
		do
		{
			zn=pl.get();
			if(pl.eof())
			{
				pl.close();
				return 1;
			}
		}while(zn!='$');
		zn=pl.get();
		while(zn=='0')
		{
			zn=pl.get();
		}
		memset(txt,0,350);
		i=0;
		txt[i]=zn;
		do
		{
			zn=pl.get();
			if(zn!='\t')
			{
				i++;
				txt[i]=zn;
			}
		}while(zn!='\t');
		strncpy(Art[*indeks].KOD_TOW,txt,35);

		memset(txt,0,350);
		i=-1;
		do
		{
			zn=pl.get();
			if(zn!='\t')
			{
				i++;
				txt[i]=zn;
			}
		}while(zn!='\t');

		i=strlen(txt)-1;
		while(txt[i]==32) 
		{
			txt[i]=0;
			i--;
		}

		strcpy(Art[*indeks].Nazwa,txt);

		memset(txt,0,350);
		i=-1;
		do
		{
			zn=pl.get();
			if(zn!='\t')
			{
				i++;
				txt[i]=zn;
			}
		}while(zn!='\t');
		i=atoi(txt);
		Art[*indeks].VAT=vt[i-1].vat;

		memset(txt,0,350);
		i=-1;
		do
		{
			zn=pl.get();
			if(zn!='\t')
			{
				i++;
				txt[i]=zn;
			}
		}while(zn!='\t');
		i=atoi(txt);
		strcpy(Art[*indeks].Grupa,grt[i-1].nazwa);

		i=-1;
		do
		{
			zn=pl.get();
		}while(zn!='\t');

		memset(txt,0,350);
		i=-1;
		do
		{
			zn=pl.get();
			if(zn!='\t')
			{
				i++;
				txt[i]=zn;
			}
		}while(zn!='\t');

		i=atoi(txt);
		strcpy(Art[*indeks].JM,jm[i-1].znak);

		do
		{
			zn=pl.get();
		}while(zn!='\t');

		memset(txt,0,350);
		i=-1;
		do
		{
			zn=pl.get();
			if(zn!='\t')
			{
				i++;
				txt[i]=zn;
			}
		}while(zn!='\t');
		strncpy(Art[*indeks].KOD_KR,txt,35);
	
		memset(txt,0,350);
		i=-1;
		do
		{
			zn=pl.get();
			if(zn!='\t')
			{
				i++;
				txt[i]=zn;
			}
		}while(zn!='\t');
		Art[*indeks].Cena_Brutto=(atof(txt)/100);
		if(Art[*indeks].VAT==0) Art[*indeks].Cena_Netto=Art[*indeks].Cena_Brutto;
		else Art[*indeks].Cena_Netto=Art[*indeks].Cena_Brutto/(1+(Art[*indeks].VAT/100));

		memset(txt,0,350);
		i=-1;
		do
		{
			zn=pl.get();
			if(zn!='\t')
			{
				i++;
				txt[i]=zn;
			}
		}while(zn!='\t');
		i=atoi(txt);
		if(i==0)Art[*indeks].is_op=false; else Art[*indeks].is_op=true;

		memset(txt,0,350);
		i=-1;
		do
		{
			zn=pl.get();
			if(zn!='\t')
			{
				i++;
				txt[i]=zn;
			}
		}while(zn!='\t');
		i=atoi(txt);
		if(i==0)Art[*indeks].is_wylznr=false; else Art[*indeks].is_wylznr=true;

		memset(txt,0,350);
		i=-1;
		do
		{
			zn=pl.get();
			if(zn!='\t')
			{
				i++;
				txt[i]=zn;
			}
		}while(zn!='\t');
		i=atoi(txt);
		if(i==0)Art[*indeks].is_cena=false; else Art[*indeks].is_cena=true;

		memset(txt,0,350);
		i=-1;
		do
		{
			zn=pl.get();
			if(zn!='\t')
			{
				i++;
				txt[i]=zn;
			}
		}while(zn!='\t');
		i=atoi(txt);
		if(i==0)Art[*indeks].is_list=false; else Art[*indeks].is_list=true;

		do
		{
			zn=pl.get();
		}while(zn!='\n');
		*indeks=*indeks+1;
	}
	pl.close();
	return 1;
}



	//funkcja uaktualnia stany magazynowe na podstawie plków wyjœciowych


int Mag_act()
{
	Prz_Tow prz_t;
	fstream pl;
	char txt[350];
	char zn;
	int i,j,k;
	LONGLONG l1,l2;
	HANDLE hn;
	WIN32_FIND_DATA wfd;
	double cena;
	float f,c;
	bool is_f;
	double vat;

	_SYSTEMTIME st;
	hn=FindFirstFile("Config/naz.txt",&wfd);
	if(hn==INVALID_HANDLE_VALUE) return -1;
	pl.open("Config/naz.txt",ios_base::in | ios_base::binary);
	if(!pl) return -1;
	l1=0;
	cena=0;
	GetSystemTime(&st);
	prz_t.miesiac=st.wMonth;
	prz_t.rok=st.wYear;
	do
	{
		do
		{
			zn=pl.get();
			l1++;
		}while(zn!='$' && l1<wfd.nFileSizeLow);
		if(l1==wfd.nFileSizeLow)
		{
			pl.close();
			prz_t.cena_n=cena;
			return 1;
		}
		zn=pl.get();
		l1++;
		while(zn=='0')
		{
			zn=pl.get();
			l1++;
		}
		memset(txt,0,350);
		txt[0]=zn;
		i=0;
		do
		{
			zn=pl.get();
			i++;
			if(zn!=9) txt[i]=zn;
			l1++;
		}while(zn!=9 && l1<wfd.nFileSizeLow);
		if(l1==wfd.nFileSizeLow)
		{
			pl.close();
			prz_t.cena_n=cena;
			return 1;
		}
		is_f=false;
		for(k=0;k<HD_A.count;k++)
		{
			if(strcmp(ART[k].KOD_TOW,txt)==0)
			{
				j=k;
				is_f=true;
				break;
			}
		}
		memset(txt,0,350);
		i=0;
		do
		{
			zn=pl.get();
			if(zn!=9) 
			{
				txt[i]=zn;
				i++;
			}
			l1++;
		}while(zn!=9 && l1<wfd.nFileSizeLow);
		f=atof(txt);

		memset(txt,0,350);
		i=0;
		do
		{
			zn=pl.get();
			if(zn!=9 && zn!=10) 
			{
				txt[i]=zn;
				i++;
			}
			l1++;
		}while(zn!=9 && zn!=10 && l1<wfd.nFileSizeLow);

		c=atof(txt);
		c=c/100;
		c=c/(1+(ART[j].VAT/100));
		if(is_f)
		{
			ART[j].Stan-=f;
			prz_t.cena_n=c;
			Save_AR(&ART[j]);
			Save_SP(prz_t,ART[j].VAT);
		}

	}while(l1<wfd.nFileSizeLow);
	pl.close();
	return 1;
}


//funkcja odczytuje dane o towarze z kasy


int get_tow_kas(TOW_K * T , KASA_ KT,char* numer)
{
	int i;
	fstream pl;
	char con_str[350],txt[350],zn;
	int c;
	HANDLE hn;
	int licz,licz1;
	WIN32_FIND_DATA wfd;
	bool is_elz;

	if(T==NULL || numer==NULL) return -1;
	
	memset(T,0,sizeof(TOW_K));
	i=InitKonf(KT);
	if(i<1) return -1;

	pl.open("Config/pin.in",ios_base::in|ios_base::out|ios_base::trunc);
	if(!pl.is_open()) return -1;
	
	memset(con_str,0,350);

	sprintf(con_str,"#%s\n#\n#\n$%s",KT.numer,numer);
	pl.write(con_str,strlen(con_str));
	pl.close();

	pl.open("Config/pin.out",ios_base::in|ios_base::out|ios_base::trunc);
	if(!pl.is_open()) return -1;
	
	pl.close();
	(*_OTowar)("Config/pin.in","Config/pin.out");
	i=RAP(NULL,0);
	if(i!=0) return i;
	hn=FindFirstFile("Config/pin.out",&wfd);
	if(hn==INVALID_HANDLE_VALUE) return -1;
	pl.open("Config/pin.out",ios_base::in | ios_base::binary);
	if(!pl) return -1;
	memset(T->numer,0,50);
	strncpy(T->numer,numer,50);
	licz=0;
	do
	{
		zn=pl.get();
		licz++;
	}while(zn!='$' && licz<wfd.nFileSizeLow);
	if(zn!='$' && licz>=wfd.nFileSizeLow)
	{
		pl.close();
		return -3;
	}
	c=0;
	licz1=licz;
	do
	{
		zn=pl.get();
		if(zn==9) c++;
		licz1++;
	}while(zn!=10 && licz1<wfd.nFileSizeLow);

	if(c>9)is_elz=true; else is_elz=false;
	pl.seekg(licz,ios_base::beg);
	
	while(zn!=9 && licz<wfd.nFileSizeLow)
	{
		zn=pl.get();
		licz++;
	}

	memset(txt,0,350);
	i=-1;

	do
	{
		zn=pl.get();
		licz++;
		if(zn!=9)
		{
			i++;
			txt[i]=zn;
		}
	}while(zn!=9 && licz<wfd.nFileSizeLow);

	i=strlen(txt)-1;
	if(i>0)nazT_max=i+1; else nazT_max=34;
	while(txt[i]==32)
	{
		txt[i]=0;
		i--;
	}
	strncpy(T->nazwa,txt,150);
	memset(txt,0,350);
	i=-1;
	do
	{
		zn=pl.get();
		licz++;
		if(zn!=9)
		{
			i++;
			txt[i]=zn;
		}
	}while(zn!=9 && licz<wfd.nFileSizeLow);
	i=atoi(txt);
	T->vat=i;

	memset(txt,0,350);
	i=-1;
	do
	{
		zn=pl.get();
		licz++;
		if(zn!=9)
		{
			i++;
			txt[i]=zn;
		}
	}while(zn!=9 && licz<wfd.nFileSizeLow);
	T->grupa=atoi(txt);
	memset(txt,0,350);
	i=-1;
	do
	{
		zn=pl.get();
		licz++;
		if(zn!=9)
		{
			i++;
			txt[i]=zn;
		}
	}while(zn!=9 && licz<wfd.nFileSizeLow);
	T->mpp=atoi(txt);

	memset(txt,0,350);
	i=-1;
	do
	{
		zn=pl.get();
		licz++;
		if(zn!=9)
		{
			i++;
			txt[i]=zn;
		}
	}while(zn!=9 && licz<wfd.nFileSizeLow);
	T->jm=atoi(txt);

	memset(txt,0,350);
	i=-1;
	do
	{
		zn=pl.get();
		licz++;
		if(zn!=9)
		{
			i++;
			txt[i]=zn;
		}
	}while(zn!=9 && licz<wfd.nFileSizeLow);

	i=atoi(txt);
	if(i==1) T->is_bl=true; else T->is_bl=false;

	memset(txt,0,350);
	i=-1;
	do
	{
		zn=pl.get();
		licz++;
		if(zn!=9)
		{
			i++;
			txt[i]=zn;
		}
	}while(zn!=9 && licz<wfd.nFileSizeLow);

	strncpy(T->kod_kr,txt,35);

	memset(txt,0,350);
	i=-1;
	do
	{
		zn=pl.get();
		licz++;
		if(zn!=9)
		{
			i++;
			txt[i]=zn;
		}
	}while(zn!=9 && licz<wfd.nFileSizeLow);

	T->cenab=atof(txt);
	T->cenab/=100;

	memset(txt,0,350);
	i=-1;
	do
	{
		zn=pl.get();
		licz++;
		if(zn!=9)
		{
			i++;
			txt[i]=zn;
		}
	}while(zn!=9 && licz<wfd.nFileSizeLow);

	i=atoi(txt);
	if(i==1) T->is_op=true; else T->is_op=false;
	if(!is_elz)
	{
		T->is_wylzRN=false;
		T->list_podr=false;
		T->wpr_cen=false;
	}else
	{
		memset(txt,0,350);
		i=-1;
		do
		{
			zn=pl.get();
			licz++;
			if(zn!=9)
			{
				i++;
				txt[i]=zn;
			}
		}while(zn!=9 && licz<wfd.nFileSizeLow);
		i=atoi(txt);
		if(i==1) T->is_wylzRN=true; else T->is_wylzRN=false;

		memset(txt,0,350);
		i=-1;
		do
		{
			zn=pl.get();
			licz++;
			if(zn!=9)
			{
				i++;
				txt[i]=zn;
			}
		}while(zn!=9 && licz<wfd.nFileSizeLow);
		i=atoi(txt);
		if(i==1) T->wpr_cen=true; else T->wpr_cen=false;

		memset(txt,0,350);
		i=-1;
		do
		{
			zn=pl.get();
			licz++;
			if(zn!=9)
			{
				i++;
				txt[i]=zn;
			}
		}while(zn!=9 && licz<wfd.nFileSizeLow);
		i=atoi(txt);
		if(i==1) T->list_podr=true; else T->list_podr=false;

		memset(txt,0,350);
		i=-1;
		do
		{
			zn=pl.get();
			licz++;
			if(zn!=9)
			{
				i++;
				txt[i]=zn;
			}
		}while(zn!=9 && licz<wfd.nFileSizeLow);
		T->num_wag=atoi(txt);

		memset(txt,0,350);
		i=-1;
		do
		{
			zn=pl.get();
			licz++;
			if(zn!=9)
			{
				i++;
				txt[i]=zn;
			}
		}while(zn!=9 && licz<wfd.nFileSizeLow);
		T->licz_starz=atoi(txt);

	}

	pl.close();

	return 0;
}


// Funkcja zapisuje dane o towarze


int set_tow(KASA_ KT, TOW_K * T)
{
	fstream pl;
	int i,j,k,l,m;
	char con_str[350];
	char txt[150];
	if(T==NULL) return -1;

	i=InitKonf(KT);
	if(i<1) return -1;

	pl.open("Config/pin.in",ios_base::in|ios_base::out|ios_base::trunc);
	if(!pl.is_open()) return -1;
	memset(txt,0,150);
	if (nazT_max<=0)nazT_max=34;
	memset(txt,32,nazT_max);
	i=strlen(T->nazwa);
	if(i>34)i=34;
	strncpy(txt,T->nazwa,i);
	txt[34]=0;
	memset(con_str,0,350);
	if(T->is_bl)i=1;else i=0;
	if(T->is_op)j=1;else j=0;
	if(T->is_wylzRN)k=1;else k=0;
	if(T->wpr_cen)l=1;else l=0;
	if(T->list_podr)m=1;else m=0;
	if(T->num_wag==0)T->num_wag=1;
	sprintf(con_str,"#%s\n#\n#\n$%s\t%s\t%d\t%d\t%d\t%d\t%d\t%s\t%0.0f\t%d\t%d\t%d\t%d\t%d\t%d\n",KT.numer,T->numer,txt,T->vat,T->grupa,T->mpp,T->jm,i,T->kod_kr,T->cenab*100,j,k,l,m,T->num_wag,T->licz_starz);
	pl.write(con_str,strlen(con_str));
	pl.close();

	pl.open("Config/pin.out",ios_base::in|ios_base::out|ios_base::trunc);
	if(!pl.is_open()) return -1;
	
	pl.close();

	(*_ZTowar)("Config/pin.in");
	i=RAP(NULL,0);
	if(i!=0) return i;

	return 0;
}

	//funkcja kasuje towar z kasy fiskalnej

int del_tow_kas(KASA_ KT,char* numer)
{
	int i;
	fstream pl;
	char con_str[350],txt[350],zn;

	if(numer==NULL) return -1;
	i=InitKonf(KT);
	if(i<1) return -1;

	pl.open("Config/pin.in",ios_base::in|ios_base::out|ios_base::trunc);
	if(!pl.is_open()) return -1;
	
	memset(con_str,0,350);

	sprintf(con_str,"#%s\n#\n#\n$%s",KT.numer,numer);
	pl.write(con_str,strlen(con_str));
	pl.close();

	pl.open("Config/pin.out",ios_base::in|ios_base::out|ios_base::trunc);
	if(!pl.is_open()) return -1;
	
	pl.close();

	(*_KTowar)("Config/pin.in");
	i=RAP(NULL,0);
	if(i!=0) return i;
	return 0;
}


	//funkcja zapisuje numer kasy fiskalnej

int zap_numKas(KASA_ KT,char* numer)
{
	int i;
	fstream pl;
	char con_str[350],txt[350],zn;

	if(numer==NULL) return -1;
	i=InitKonf(KT);
	if(i<1) return -1;

	pl.open("Config/pin.in",ios_base::in|ios_base::out|ios_base::trunc);
	if(!pl.is_open()) return -1;
	
	memset(con_str,0,350);

	sprintf(con_str,"#%s\n#\n#\n$%s",KT.numer,numer);
	pl.write(con_str,strlen(con_str));
	pl.close();

	pl.open("Config/pin.out",ios_base::in|ios_base::out|ios_base::trunc);
	if(!pl.is_open()) return -1;
	
	pl.close();

	(*_ZNrKasy)("Config/pin.in");
	i=RAP(NULL,0);
	if(i!=0) return i;
	return 0;
}

	//funkcja zapisuje rabat do kasy fiskalnej

int zap_rab(KASA_ KT, char* numer)
{
	int i;
	fstream pl;
	char con_str[350],txt[350],zn;

	if(numer==NULL) return -1;
	i=InitKonf(KT);
	if(i<1) return -1;

	pl.open("Config/pin.in",ios_base::in|ios_base::out|ios_base::trunc);
	if(!pl.is_open()) return -1;
	
	memset(con_str,0,350);

	sprintf(con_str,"#%s\n#\n#\n$%s",KT.numer,numer);
	pl.write(con_str,strlen(con_str));
	pl.close();

	pl.open("Config/pin.out",ios_base::in|ios_base::out|ios_base::trunc);
	if(!pl.is_open()) return -1;
	
	pl.close();

	(*_ZRabat)("Config/pin.in");
	i=RAP(NULL,0);
	if(i!=0) return i;
	return 0;
}


	//funkcja zapisuje narzut do kasy fiskalnej

int zap_narz(KASA_ KT, char* numer)
{
	int i;
	fstream pl;
	char con_str[350],txt[350],zn;

	if(numer==NULL) return -1;
	i=InitKonf(KT);
	if(i<1) return -1;

	pl.open("Config/pin.in",ios_base::in|ios_base::out|ios_base::trunc);
	if(!pl.is_open()) return -1;
	
	memset(con_str,0,350);

	sprintf(con_str,"#%s\n#\n#\n$%s",KT.numer,numer);
	pl.write(con_str,strlen(con_str));
	pl.close();

	pl.open("Config/pin.out",ios_base::in|ios_base::out|ios_base::trunc);
	if(!pl.is_open()) return -1;
	
	pl.close();

	(*_ZNarzut)("Config/pin.in");
	i=RAP(NULL,0);
	if(i!=0) return i;
	return 0;
}

int find_num(KASA_ KT,int *num, int*max)	//funkcja wyszukuje wolny numer w kasie fiskalnej
{
	int i,j,k,l;
	int *numT;
	bool is_d;

	i=get_data(KT,&j,_ONrTowar,NULL,0);
	if(i>0) return i;
	if(max!=NULL)
	{
		*max=j;
	}
	numT=new int[j];
	l=j;

	for(i=0;i<j;i++)numT[i]=-1;
	for(i=0;i<HD_A.count;i++)
	{
		if(ART[i].KOD_TOW[0]==0) is_d=false; else is_d=true;
		for(j=0;j<strlen(ART[i].KOD_TOW);j++)
		{
			if(!isdigit(ART[i].KOD_TOW[j]))
			{
				is_d=false;
				break;
			}
		}
		if(is_d)
		{
			k=atoi(ART[i].KOD_TOW);
			if(k<=l && k>0)
			numT[k-1]=k;
		}
	}
	is_d=false;
	i=0;
	while(numT[i]!=-1 && i<HD_A.count) i++;
	if(i<l)i++;
	delete numT;
	numT=NULL;
	if(num!=NULL)*num=i;
	return 0;
}
		//funkcja odczytuje bajty konfiguracj kasy fiskalnej

int get_bitcfg(KASA_ *K, KAS_CFG * KCFG)
{
	fstream pl;
	char con_str[350];
	int i,licz,lbit;
	WIN32_FIND_DATA fdt;
	HANDLE hn;
	char zn,txt[150];
	KAS_CFG K_CFG;

	if(K==NULL || KCFG==NULL) return -2;
	memset(KCFG->bt,0,23);
	i=get_data(*K,NULL,_OBajty,NULL,0);
	if(i!=0) return i;

	hn=FindFirstFile("Config/pin.out",&fdt);
	if(hn==INVALID_HANDLE_VALUE) return -1;

	pl.open("Config/pin.out",ios_base::in);
	if(!pl.is_open()) return -1;
	licz=0;
	zn=0;
	lbit=0;
	while(licz<fdt.nFileSizeLow && zn!='$')
	{
		pl.read((char*)&zn,1);
		licz++;
	}
	if(zn=='$' && licz<fdt.nFileSizeLow)
	{
		while(licz<fdt.nFileSizeLow)
		{
			zn=0;
			while(zn!=9 && licz<fdt.nFileSizeLow)
			{
				pl.read((char*)&zn,1);
				licz++;
			}
			if(licz>=fdt.nFileSizeLow) break;
			memset(txt,0,150);
			i=0;
			do
			{
				zn=pl.get();
				licz++;
				if(zn!=10 && zn!=13 && zn!='$')
				{
					txt[i]=zn;
					i++;
				}
			}while(zn!=10 && zn!=13 && licz<fdt.nFileSizeLow);
			
			KCFG->bt[lbit]=atoi(txt);
			lbit++;

		}
	}
	pl.close();
	return 0;
}


		//funkcja zapisuje bajty konfiguracj kasy fiskalnej

int set_bitcfg(KASA_ *K, KAS_CFG * KCFG)
{
	fstream pl;
	int i;
	char txt[150];
	KAS_CFG K_CFG;

	if(K==NULL || KCFG==NULL) return -2;
	i=InitKonf(*K);
	if(i<1) return -1;

	pl.open("Config/pin.in",ios_base::in | ios_base::out | ios_base::trunc);
	if(!pl.is_open()) return -1;
	memset(txt,0,150);

	sprintf(txt,"#%s\n#\n#\n",K->numer);
	pl.write(txt,strlen(txt));
	for(i=0;i<24;i++)
	{
		memset(txt,0,150);
		sprintf(txt,"$%d\t%d\n",i+1,KCFG->bt[i]);
		pl.write(txt,strlen(txt));
	}
	pl.close();
	_ZBajty("Config/pin.in");
	i=RAP(NULL,0);
	return i;
}


		//funkcja zapisuje jednostki miary kasy fiskalnej

int set_jm(KASA_ *K, JM* jedn, int cnt)
{
	fstream pl;
	int i,i1,j;
	char txt[150],txt1[150];
	KAS_CFG K_CFG;

	if(K==NULL || jedn==NULL || cnt<0) return -2;
	i=InitKonf(*K);
	if(i<1) return -1;

	pl.open("Config/pin.in",ios_base::in | ios_base::out | ios_base::trunc);
	if(!pl.is_open()) return -1;
	memset(txt,0,150);

	sprintf(txt,"#%s\n#\n#\n",K->numer);
	pl.write(txt,strlen(txt));
	for(i=0;i<cnt;i++)
	{	
		memset(txt1,0,150);
		strcpy(txt1,jedn[i].znak);
		j=strlen(jedn[i].znak);
		if(j<4)
		{
			for(j=j;j<4;j++) txt1[j]=32;
		}
		memset(txt,0,150);
		sprintf(txt,"$%d\t%4s\n",i+1,txt1);
		pl.write(txt,strlen(txt));
	}
	pl.close();
	_ZJednost("Config/pin.in");
	i=RAP(NULL,0);
	return i;
}



		//funkcja zapisuje grupy towarowe kasy fiskalnej

int set_gr(KASA_ *K, GR_T* gr, int cnt)
{
	fstream pl;
	int i,i1,j;
	char txt[150],txt1[150];
	KAS_CFG K_CFG;

	if(K==NULL || gr==NULL || cnt<0) return -2;
	i=InitKonf(*K);
	if(i<1) return -1;

	pl.open("Config/pin.in",ios_base::in | ios_base::out | ios_base::trunc);
	if(!pl.is_open()) return -1;
	memset(txt,0,150);

	sprintf(txt,"#%s\n#\n#\n",K->numer);
	pl.write(txt,strlen(txt));
	for(i=0;i<cnt;i++)
	{	
		memset(txt1,0,150);
		strcpy(txt1,gr[i].nazwa);
		j=strlen(gr[i].nazwa);
		if(j<19)
		{
			for(j=j;j<19;j++) txt1[j]=32;
		}
		memset(txt,0,150);
		sprintf(txt,"$%d\t%s\n",i+1,txt1);
		pl.write(txt,strlen(txt));
	}
	pl.close();
	_ZGrupa("Config/pin.in");
	i=RAP(NULL,0);
	return i;
}



		//funkcja zapisuje formy zap³aty do kasy fiskalnej

int set_fz(KASA_ *K, FORM_ZAP* fz, int cnt)
{
	fstream pl;
	int i,i1,j;
	char txt[150],txt1[150];
	KAS_CFG K_CFG;

	if(K==NULL || fz==NULL || cnt<0) return -2;
	if(cnt<0) return -2;
	i=InitKonf(*K);
	if(i<1) return -1;

	pl.open("Config/pin.in",ios_base::in | ios_base::out | ios_base::trunc);
	if(!pl.is_open()) return -1;
	memset(txt,0,150);

	sprintf(txt,"#%s\n#\n#\n",K->numer);
	pl.write(txt,strlen(txt));
	for(i=0;i<cnt;i++)
	{	
		memset(txt1,0,150);
		strcpy(txt1,fz[i].naz);
		j=strlen(fz[i].naz);
		if(j<13)
		{
			for(j=j;j<13;j++) txt1[j]=32;
		}
		memset(txt,0,150);
		sprintf(txt,"$%d\t%s\n",i+1,txt1);
		pl.write(txt,strlen(txt));
	}
	pl.close();
	_ZPlat("Config/pin.in");
	i=RAP(NULL,0);
	return i;
}


		//funkcja pobiera raport godzinowy z kasy fiskalnej

int rap_godz(KASA_ *K, RPG* rpg, int code)
{
	fstream pl;
	int i,i1,j,licz;
	char txt[150];
	KAS_CFG K_CFG;
	char zn;
	WIN32_FIND_DATA fdt;
	HANDLE hn;

	if(K==NULL || rpg==NULL) return -2;
	i=InitKonf(*K);
	if(i<1) return -1;

	pl.open("Config/pin.in",ios_base::in | ios_base::out | ios_base::trunc);
	if(!pl.is_open()) return -1;
	memset(txt,0,150);

	sprintf(txt,"#%s\n#\n#\n",K->numer);
	pl.write(txt,strlen(txt));
	pl.close();
	if(code==0)_ODaneARG("Config/pin.in","Config/pin.out"); else
		_ODanePRG("Config/pin.in","Config/pin.out");
	i=RAP(NULL,0);
	if(i!=0) return i;
	i1=-1;
	licz=0;
	hn=FindFirstFile("Config/pin.out",&fdt);
	if (hn==INVALID_HANDLE_VALUE) return -1;
	pl.open("Config/pin.out",ios_base::in);
	if(pl.fail()) return -1;
	do
	{
		do
		{
			zn=pl.get();
			licz++;
		}while(zn!='$' && licz<fdt.nFileSizeLow);
		if(licz>=fdt.nFileSizeLow)
		{
			pl.close();
			return 0;
		}
		i=0;
	
		i1++;
		do
		{
			zn=pl.get();
			if(zn!=9) txt[i]=zn;
			i++;
			licz++;
		}while(zn!=9 && licz<fdt.nFileSizeLow);
		if(i1==0)rpg->rg[i1].godz=24; else rpg->rg[i1].godz=i1;
		i=0;
		memset(txt,0,150);
		do
		{
			zn=pl.get();
			if(zn!=9) txt[i]=zn;
			i++;
			licz++;
		}while(zn!=9 && licz<fdt.nFileSizeLow);
		rpg->rg[i1].il_par=atoi(txt);

		i=0;
		memset(txt,0,150);
		do
		{
			zn=pl.get();
			if(zn!=9) txt[i]=zn;
			i++;
			licz++;
		}while(zn!=9 && licz<fdt.nFileSizeLow);
		rpg->rg[i1].il_poz_par=atoi(txt);

		i=0;
		memset(txt,0,150);
		do
		{
			zn=pl.get();
			if(zn!=10) txt[i]=zn;
			i++;
			licz++;
		}while(zn!=10 && licz<fdt.nFileSizeLow);
		rpg->rg[i1].wart_sprz=(atof(txt)/100);
	}while(licz<fdt.nFileSizeLow);
	pl.close();
	return 0;
}


	//Funkcja odczytuje rodzaje kasjerów z kasy


int ORodz_Kasj(KASA_ KT, KASJER *ksj, int *out)
{
	int i,j,licz,ind;
	fstream pl;
	WIN32_FIND_DATA fdt;
	HANDLE hn;
	char zn;
	char con_str[350],txt[350];

	if(ksj==NULL || out==NULL) return -1;
	if(out<=0) return -1;
	i=InitKonf(KT);
	if(i<1) return -1;
	pl.open("Config/pin.in",ios_base::in|ios_base::out|ios_base::trunc);
	if(!pl.is_open()) return -1;
	
	memset(con_str,0,350);

	sprintf(con_str,"#%s\n#\n#",KT.numer);
	pl.write(con_str,strlen(con_str));
	pl.close();

	pl.open("Config/pin.out",ios_base::in|ios_base::out|ios_base::trunc);
	if(!pl.is_open()) return -1;
	
	pl.close();

	(*_ORodzKas)("Config/pin.in","Config/pin.out");
	i=RAP(NULL,0);
	if(i!=0) return i;

	hn=FindFirstFile("Config/pin.out",&fdt);
	if(hn==INVALID_HANDLE_VALUE) return -1;

	pl.open("Config/pin.out",ios_base::in | ios_base::binary);
	if(!pl) return -1;
	licz=0;
	i=0;
	do
	{
		zn=pl.get();
		if(zn==10) i++;
		licz++;
	}while(licz<fdt.nFileSizeLow);
	i=i-3;
	if(i>*out) 
	{
		*out=i;
		pl.close();
		return -2;
	}
	*out=i;
	licz=0;
	pl.seekg(0,ios_base::beg);
	ind=-1;
	memset(ksj,0,sizeof(KASJER)*i);
	while(1)
	{
		ind++;
		do
		{
			zn=pl.get();
			licz++;
		}while(zn!='$' && licz<fdt.nFileSizeLow);
		if(licz>=fdt.nFileSizeLow)
		{
			break;
		}

		while(zn!=9 && licz<fdt.nFileSizeLow)
		{
			zn=pl.get();
			licz++;
		}

		i=0;
		memset(txt,0,350);
		zn=0;
		while(zn!=9 && licz<fdt.nFileSizeLow)
		{
			zn=pl.get();
			licz++;										//nazwa
			if(zn!=9) 
			{
				txt[i]=zn;
				i++;
			}
		}
		//txt[19]=0;
		i=strlen(txt);
		for(i=i-1;i>=0;i--)
		{
			if(txt[i]==32) txt[i]=0;else break;
		}
		strncpy(ksj[ind].nazwa,txt,19);
		ksj[ind].nazwa[19]=0;
		i=0;
		memset(txt,0,350);
		zn=0;
		while(zn!=9 && licz<fdt.nFileSizeLow)
		{
			zn=pl.get();
			licz++;
			if(zn!=9) 
			{
				txt[i]=zn;
				i++;
			}							//raport koñca zmiany
		}
		ksj[ind].d_rap_kon_zm=(bool)atoi(txt);

		i=0;
		memset(txt,0,350);
		zn=0;
		while(zn!=9 && licz<fdt.nFileSizeLow)
		{
			zn=pl.get();
			licz++;
			if(zn!=9) 
			{
				txt[i]=zn;
				i++;
			}						//raport sprzeda¿y wed³ug grup
		}
		ksj[ind].d_rap_sprz_wed_gr=(bool)atoi(txt);

		i=0;
		memset(txt,0,350);
		zn=0;
		while(zn!=9 && licz<fdt.nFileSizeLow)
		{
			zn=pl.get();
			licz++;
			if(zn!=9) 
			{
				txt[i]=zn;
				i++;
			}							//raport szczegó³owy sprzeda¿y
		}
		ksj[ind].d_rap_szcz_sprz=(bool)atoi(txt);

		i=0;
		memset(txt,0,350);
		zn=0;
		while(zn!=9 && licz<fdt.nFileSizeLow)
		{
			zn=pl.get();
			licz++;
			if(zn!=9) 
			{
				txt[i]=zn;
				i++;
			}							//raport zwrotów opakowañ
		}
		ksj[ind].d_rap_zwr_op=(bool)atoi(txt);

		i=0;
		memset(txt,0,350);
		zn=0;
		while(zn!=9 && licz<fdt.nFileSizeLow)
		{
			zn=pl.get();
			licz++;
			if(zn!=9) 
			{
				txt[i]=zn;
				i++;
			}						//raport godzinowy
		}
		ksj[ind].d_rap_godz=(bool)atoi(txt);

		i=0;
		memset(txt,0,350);
		zn=0;
		while(zn!=9 && licz<fdt.nFileSizeLow)
		{
			zn=pl.get();
			licz++;
			if(zn!=9) 
			{
				txt[i]=zn;
				i++;
			}							//raport dobowy
		}
		ksj[ind].d_rap_dob=(bool)atoi(txt);

		i=0;
		memset(txt,0,350);
		zn=0;
		while(zn!=9 && licz<fdt.nFileSizeLow)
		{
			zn=pl.get();
			licz++;
			if(zn!=9) 
			{
				txt[i]=zn;
				i++;
			}							//raport okresowy
		}
		ksj[ind].d_rap_sum_okr1=(bool)atoi(txt);

		i=0;
		memset(txt,0,350);
		zn=0;
		while(zn!=9 && licz<fdt.nFileSizeLow)
		{
			zn=pl.get();
			licz++;
			if(zn!=9) 
			{
				txt[i]=zn;
				i++;
			}							//raport sprzedawcówy
		}
		ksj[ind].d_rap_sprzedaw=(bool)atoi(txt);

		i=0;
		memset(txt,0,350);
		zn=0;
		while(zn!=9 && licz<fdt.nFileSizeLow)
		{
			zn=pl.get();
			licz++;
			if(zn!=9) 
			{
				txt[i]=zn;
				i++;
			}							//raport koñca zmiany
		}
		ksj[ind].z_rap_kon_zm=(bool)atoi(txt);

		i=0;
		memset(txt,0,350);
		zn=0;
		while(zn!=9 && licz<fdt.nFileSizeLow)
		{
			zn=pl.get();
			licz++;
			if(zn!=9) 
			{
				txt[i]=zn;
				i++;
			}							//raport sprzeda¿y wed³ug grup
		}
		ksj[ind].z_rap_sprz_wed_gr=(bool)atoi(txt);

		i=0;
		memset(txt,0,350);
		zn=0;
		while(zn!=9 && licz<fdt.nFileSizeLow)
		{
			zn=pl.get();
			licz++;
			if(zn!=9) 
			{
				txt[i]=zn;
				i++;
			}							//raport szczegó³owy sprzeda¿y
		}
		ksj[ind].z_rap_szcz_sprz=(bool)atoi(txt);

		i=0;
		memset(txt,0,350);
		zn=0;
		while(zn!=9 && licz<fdt.nFileSizeLow)
		{
			zn=pl.get();
			licz++;
			if(zn!=9) 
			{
				txt[i]=zn;
				i++;
			}							//raport zwrotów opakowañ
		}
		ksj[ind].z_rap_zwr_op=(bool)atoi(txt);

		i=0;
		memset(txt,0,350);
		zn=0;
		while(zn!=9 && licz<fdt.nFileSizeLow)
		{
			zn=pl.get();
			licz++;
			if(zn!=9) 
			{
				txt[i]=zn;
				i++;
			}							//raport godzinowy
		}
		ksj[ind].z_rap_godz=(bool)atoi(txt);

		i=0;
		memset(txt,0,350);
		zn=0;
		while(zn!=9 && licz<fdt.nFileSizeLow)
		{
			zn=pl.get();
			licz++;
			if(zn!=9) 
			{
				txt[i]=zn;
				i++;
			}							//raport dobowy
		}
		ksj[ind].z_rap_dob=(bool)atoi(txt);

		i=0;
		memset(txt,0,350);
		zn=0;
		while(zn!=9 && licz<fdt.nFileSizeLow)
		{
			zn=pl.get();
			licz++;
			if(zn!=9) 
			{
				txt[i]=zn;
				i++;
			}						//raport okresowy
		}
		ksj[ind].z_rap_sum_okr1=(bool)atoi(txt);

		i=0;
		memset(txt,0,350);
		zn=0;
		while(zn!=9 && licz<fdt.nFileSizeLow)
		{
			zn=pl.get();
			licz++;
			if(zn!=9) 
			{
				txt[i]=zn;
				i++;
			}							//raport sprzedawcówy
		}
		ksj[ind].z_rap_sprzedaw=(bool)atoi(txt);

		i=0;
		memset(txt,0,350);
		zn=0;
		while(zn!=9 && licz<fdt.nFileSizeLow)
		{
			zn=pl.get();
			licz++;
			if(zn!=9) 
			{
				txt[i]=zn;
				i++;
			}							//rabat
		}
	
		ksj[ind].max_rab=atoi(txt);

		i=0;
		memset(txt,0,350);
		zn=0;
		while(zn!=9 && licz<fdt.nFileSizeLow)
		{
			zn=pl.get();
			licz++;
			if(zn!=9) 
			{
				txt[i]=zn;			//narzut
				i++;
			}		
		}
		ksj[ind].max_narz=atoi(txt);
		for(j=0;j<99;j++)
		{
			i=0;
			memset(txt,0,350);
			zn=0;
			while(zn!=9 && zn!=10 && licz<fdt.nFileSizeLow)
			{
				zn=pl.get();
				licz++;
				if(zn!=9) 
				{
					txt[i]=zn;			//narzut
					i++;
				}		
			}
			ksj[ind].upr[j]=atoi(txt);
		}
	}
	
	

	pl.close();
	return 0;
}



//Funkcja zapisuje rodzaje kasjerów z kasy


int ZRodz_Kasj(KASA_ KT, KASJER *ksj, int *out)
{
	int i,j;
	fstream pl;
	char con_str[350];
	char txt[20];
	if(ksj==NULL || out==NULL) return -1;
	if(out<=0) return -1;
	i=InitKonf(KT);
	if(i<1) return -1;
	pl.open("Config/pin.in",ios_base::in|ios_base::out|ios_base::trunc);
	if(!pl.is_open()) return -1;
	
	memset(con_str,0,350);

	sprintf(con_str,"#%s\n#\n#\n",KT.numer);
	pl.write(con_str,strlen(con_str));

	for(i=0;i<*out;i++)
	{
		memset(con_str,0,350);
		memset(txt,32,19);
		txt[19]=0;
		if(ksj[i].nazwa[0]!=32)strncpy(txt,ksj[i].nazwa,strlen(ksj[i].nazwa));
		sprintf(con_str,"$%d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d",i+1,txt,ksj[i].d_rap_kon_zm,ksj[i].d_rap_sprz_wed_gr,ksj[i].d_rap_szcz_sprz,ksj[i].d_rap_zwr_op,ksj[i].d_rap_godz,ksj[i].d_rap_dob,ksj[i].d_rap_sum_okr1,ksj[i].d_rap_sprzedaw,ksj[i].z_rap_kon_zm,ksj[i].z_rap_sprz_wed_gr,ksj[i].z_rap_szcz_sprz,ksj[i].z_rap_zwr_op,ksj[i].z_rap_godz,ksj[i].z_rap_dob,ksj[i].z_rap_sum_okr1,ksj[i].z_rap_sprzedaw,ksj[i].max_rab,ksj[i].max_narz);
		for(j=0;j<99;j++)
		{
			sprintf(&con_str[strlen(con_str)],"\t%d",(int)ksj[i].upr[j]);
		}
		sprintf(&con_str[strlen(con_str)],"\n");
		pl.write((char*)con_str,strlen(con_str));
	}
	pl.close();
	(*_ZRodzKas)("Config/pin.in");
	i=RAP(NULL,0);
	if(i!=0) return i;
	return 0;
}


	//Funkcja odczytuje dane kasjerów z kasy


int ODane_Kasj(KASA_ KT, D_KASJER *ksj, int *out)
{
	int i,j,licz,ind;
	fstream pl;
	WIN32_FIND_DATA fdt;
	HANDLE hn;
	char zn;
	char con_str[350],txt[350];

	if(ksj==NULL || out==NULL) return -1;
	if(out<=0) return -1;
	i=InitKonf(KT);
	if(i<1) return -1;
	pl.open("Config/pin.in",ios_base::in|ios_base::out|ios_base::trunc);
	if(!pl.is_open()) return -1;
	
	memset(con_str,0,350);

	sprintf(con_str,"#%s\n#\n#",KT.numer);
	pl.write(con_str,strlen(con_str));
	pl.close();

	pl.open("Config/pin.out",ios_base::in|ios_base::out|ios_base::trunc);
	if(!pl.is_open()) return -1;
	
	pl.close();

	(*_ORKasjer)("Config/pin.in","Config/pin.out");
	i=RAP(NULL,0);
	if(i!=0) return i;

	hn=FindFirstFile("Config/pin.out",&fdt);
	if(hn==INVALID_HANDLE_VALUE) return -1;

	pl.open("Config/pin.out",ios_base::in | ios_base::binary);
	if(!pl) return -1;
	licz=0;
	i=0;
	do
	{
		zn=pl.get();
		if(zn==10) i++;
		licz++;
	}while(licz<fdt.nFileSizeLow);
	i=i-3;
	if(i>*out) 
	{
		*out=i;
		pl.close();
		return -2;
	}
	*out=i;
	licz=0;
	pl.seekg(0,ios_base::beg);
	ind=-1;
	memset(ksj,0,sizeof(D_KASJER)*i);
	while(1)
	{
		ind++;
		do
		{
			zn=pl.get();
			licz++;
		}while(zn!='$' && licz<fdt.nFileSizeLow);
		if(licz>=fdt.nFileSizeLow)
		{
			break;
		}

		i=0;
		memset(txt,0,350);
		zn=0;
		while(zn!=9 && licz<fdt.nFileSizeLow)
		{
			zn=pl.get();
			licz++;								
			if(zn!=9) 
			{
				txt[i]=zn;
				i++;
			}
		}
		ksj[ind].id=atoi(txt);
		i=0;
		memset(txt,0,350);
		zn=0;
		while(zn!=9 && licz<fdt.nFileSizeLow)
		{
			zn=pl.get();
			licz++;										//nazwa
			if(zn!=9) 
			{
				txt[i]=zn;
				i++;
			}
		}
		i=strlen(txt);
		for(i=i-1;i>=0;i--)
		{
			if(txt[i]==32) txt[i]=0; else break;
		}
		strncpy(ksj[ind].nazwa,txt,strlen(txt));
		ksj[ind].nazwa[19]=0;
		i=0;
		memset(txt,0,350);
		zn=0;
		while(zn!=9 && licz<fdt.nFileSizeLow)
		{
			zn=pl.get();
			licz++;										//has³o
			if(zn!=9) 
			{
				txt[i]=zn;
				i++;
			}
		}
		i=strlen(txt);
		for(i=i-1;i>=0;i--)
		{
			if(txt[i]==32) txt[i]=0; else break;
		}
		strncpy(ksj[ind].haslo,txt,strlen(txt));
		ksj[ind].haslo[4]=0;
		i=0;
		memset(txt,0,350);
		zn=0;
		while(zn!=9 && licz<fdt.nFileSizeLow)
		{
			zn=pl.get();
			licz++;										//numer rodzaju kasjera
			if(zn!=9) 
			{
				txt[i]=zn;
				i++;
			}
		}
		ksj[ind].numer=atoi(txt);

		i=0;
		memset(txt,0,350);
		zn=0;
		while(zn!=10 && licz<fdt.nFileSizeLow)
		{
			zn=pl.get();
			licz++;										//zmiana kajsera
			if(zn!=9) 
			{
				txt[i]=zn;
				i++;
			}
		}
		ksj[ind].zmiana=(bool)atoi(txt);
	}
	pl.close();
	return 0;
}



//Funkcja zapisuje dane kasjerów z kasy


int ZDane_Kasj(KASA_ KT, D_KASJER *ksj, int *out)
{
	int i,j;
	fstream pl;
	char con_str[350];
	char txt[20],txt1[14];
	if(ksj==NULL || out==NULL) return -1;
	if(out<=0) return -1;
	i=InitKonf(KT);
	if(i<1) return -1;
	pl.open("Config/pin.in",ios_base::in|ios_base::out|ios_base::trunc);
	if(!pl.is_open()) return -1;
	
	memset(con_str,0,350);

	sprintf(con_str,"#%s\n#\n#\n",KT.numer);
	pl.write(con_str,strlen(con_str));

	for(i=0;i<*out;i++)
	{
		memset(con_str,0,350);
		memset(txt,32,19);
		txt[19]=0;
		memset(txt1,32,13);
		txt1[13]=0;
		if(ksj[i].nazwa[0]!=32)strncpy(txt,ksj[i].nazwa,strlen(ksj[i].nazwa));
		if(ksj[i].haslo[0]!=32)strncpy(txt1,ksj[i].haslo,strlen(ksj[i].haslo));
		sprintf(con_str,"$%d\t%s\t%s\t%d\t%d\n",ksj[i].id,txt,txt1,ksj[i].numer,(int)ksj[i].zmiana);
		pl.write(con_str,strlen(con_str));
	}
	pl.close();
	(*_ZRKasjer)("Config/pin.in");
	i=RAP(NULL,0);
	if(i!=0) return i;
	return 0;
}




//Funkcja usuwa dane kasjerów z kasy


int UDane_Kasj(KASA_ KT, D_KASJER *ksj, int *out)
{
	int i,j;
	fstream pl;
	char con_str[350];
	char txt[20],txt1[14];
	if(ksj==NULL || out==NULL) return -1;
	if(out<=0) return -1;
	i=InitKonf(KT);
	if(i<1) return -1;
	pl.open("Config/pin.in",ios_base::in|ios_base::out|ios_base::trunc);
	if(!pl.is_open()) return -1;
	
	memset(con_str,0,350);

	sprintf(con_str,"#%s\n#\n#\n",KT.numer);
	pl.write(con_str,strlen(con_str));

	for(i=0;i<*out;i++)
	{
		memset(con_str,0,350);
		sprintf(con_str,"$%d\n",ksj[i].id);
		pl.write(con_str,strlen(con_str));
	}
	pl.close();
	(*_KKasjer)("Config/pin.in");
	i=RAP(NULL,0);
	if(i!=0) return i;
	return 0;
}


bool is_num(char* zn , int c)
{
	int i;
	int l;
	bool bl;

	if(zn==NULL) return false;
	if(c<=0) return false;
	for(i=0;i<c;i++)
	{
		if(!isdigit(zn[i]))
		return false;
	}
	return true;
}



int Print_Mag(PRINTER_INFO_2 pr_info,HWND hwd, int *Aid, int cnt)
{

	char text[350];

	bool bl;
	HANDLE hnd;
	HDC dc;
	HFONT font,font1;
	LOGFONT lgf;
	_DOCINFOA Doc_info;
	SIZE lps;
	HBRUSH hb;
	int i,j,k,pos,pos1,br,wyn,resz,wys,l,m;
	int max_x,max_y,max_c[11],posX[11];
	SIZE size;
	char zn[350];
	
	
	Doc_info.lpszDocName="Stan Magazynowy";
	Doc_info.lpszDatatype=pr_info.pDatatype;
	Doc_info.lpszOutput=NULL;
	
	dc=CreateDC(pr_info.pDriverName,pr_info.pPrinterName,pr_info.pPortName,pr_info.pDevMode);
	if(!dc)
	{
		MessageBox(hwd,"Nie mo¿na pobraæ kontekstu drukarki","Wiadomoœæ",MB_OK);
		return 0;
	}else
	{
		
		StartDocA(dc,&Doc_info);	
		StartPage(dc);
		SetMapMode(dc,MM_LOMETRIC);
		GetWindowExtEx(dc,&lps);
		max_x=lps.cx;
		max_y=lps.cy-20;
		hb=CreateSolidBrush((COLORREF)0);	
		
		lgf.lfCharSet=EASTEUROPE_CHARSET;
		lgf.lfOutPrecision=OUT_DEFAULT_PRECIS;
		lgf.lfClipPrecision=CLIP_DEFAULT_PRECIS;
		lgf.lfQuality=DEFAULT_QUALITY;
		lgf.lfPitchAndFamily=DEFAULT_PITCH | FF_ROMAN;
		lgf.lfWeight=FW_SEMIBOLD;
		lgf.lfHeight=65;
		lgf.lfWidth=16;
		lgf.lfOrientation=0;
		lgf.lfItalic=false;
		lgf.lfStrikeOut=false;
		lgf.lfUnderline=false;
		lgf.lfOrientation=0;
		lgf.lfEscapement=0;
		font=CreateFontIndirect(&lgf);
		memset(text,0,350);
		sprintf(text,"W y k a z    t o w a r ó w");
				
		SelectObject(dc,font);
		GetTextExtentPoint32(dc,text,strlen(text),&size);
		i=2100-size.cx;
		i=i/2;
		TextOut(dc,i,-100,text,strlen(text));
		DeleteObject(font);
		lgf.lfWidth=10;
		lgf.lfHeight=40;
		lgf.lfWeight=FW_SEMIBOLD;
		font=CreateFontIndirect(&lgf);
		SelectObject(dc,hb);
		Rectangle(dc,150,-220,1950,-222);
		Rectangle(dc,150,-221,152,-325);
		Rectangle(dc,1950,-221,1948,-325);
		Rectangle(dc,151,-323,1950,-325);
		DeleteObject(hb);
		hb=CreateSolidBrush((COLORREF)0xFDBFB3);
		SelectObject(dc,hb);
		Rectangle(dc,152,-222,1948,-323);
		DeleteObject(hb);
		hb=CreateSolidBrush((COLORREF)0);
		SelectObject(dc,hb);
		Rectangle(dc,222,-221,224,-323);
		Rectangle(dc,624,-221,626,-323);
		Rectangle(dc,726,-221,728,-323);
		Rectangle(dc,828,-221,830,-323);
		Rectangle(dc,930,-221,932,-323);
		Rectangle(dc,1032,-221,1034,-323);			
		Rectangle(dc,1244,-221,1246,-323);
		Rectangle(dc,1316,-221,1318,-323);
		Rectangle(dc,1528,-221,1530,-323);
		Rectangle(dc,1740,-221,1742,-323);
		SelectObject(dc,font);
		SetBkColor(dc,(COLORREF)0xFDBFB3);
		GetTextExtentPoint32(dc,"LP",2,&size);i=(70-size.cx)/2;
		TextOut(dc,152+i,-252,"LP",2);
		posX[0]=162;
		GetTextExtentPoint32(dc,"NAZWA",5,&size);i=(400-size.cx)/2;
		TextOut(dc,224+i,-252,"NAZWA",5);
		posX[1]=234;
		GetTextExtentPoint32(dc,"KOD",3,&size);i=(100-size.cx)/2;
		TextOut(dc,626+i,-252,"KOD",3);
		posX[2]=636;
		GetTextExtentPoint32(dc,"STAN",5,&size);i=(100-size.cx)/2;
		TextOut(dc,728+i,-252,"STAN",5);
		posX[3]=738;
		GetTextExtentPoint32(dc,"JM",2,&size);i=(100-size.cx)/2;
		TextOut(dc,830+i,-252,"JM",2);
		posX[4]=840;
		GetTextExtentPoint32(dc,"MAR¯A",5,&size);i=(100-size.cx)/2;
		TextOut(dc,932+i,-232,"MAR¯A",5);
		posX[5]=942;
		GetTextExtentPoint32(dc,"(%)",3,&size);i=(100-size.cx)/2;
		TextOut(dc,932+i,-272,"(%)",3);
		GetTextExtentPoint32(dc,"CENA NETTO",10,&size);i=(210-size.cx)/2;
		TextOut(dc,1034+i,-252,"CENA NETTO",10);
		posX[6]=1044;
		GetTextExtentPoint32(dc,"VAT",3,&size);i=(70-size.cx)/2;
		TextOut(dc,1246+i,-232,"VAT",3);
		posX[7]=1256;
		GetTextExtentPoint32(dc,"(%)",3,&size);i=(70-size.cx)/2;
		TextOut(dc,1246+i,-272,"(%)",3);
		GetTextExtentPoint32(dc,"CENA BRUTTO",11,&size);i=(210-size.cx)/2;
		TextOut(dc,1318+i,-252,"CENA BRUTTO",11);
		posX[8]=1328;
		GetTextExtentPoint32(dc,"CENA ZAKUPU",11,&size);i=(210-size.cx)/2;
		TextOut(dc,1530+i,-252,"CANA_ZAKUPU",11);
		posX[9]=1540;
		GetTextExtentPoint32(dc,"ZAKUP RAZEM",11,&size);i=(210-size.cx)/2;
		TextOut(dc,1742+i-3,-252,"ZAKUP RAZEM",11);
		posX[10]=1752;
		pos=-325;
		DeleteObject(font);
		lgf.lfWeight=FW_NORMAL;
		lgf.lfWidth=10;
		font=CreateFontIndirect(&lgf);
		SetBkColor(dc,(COLORREF)0xFFFFFF);
		for(i=0;i<cnt;i++)
		{
			br=1;
			memset(zn,0,350);
			itoa(i,zn,10);
			GetTextExtentPoint32(dc,zn,strlen(zn),&lps);
			max_c[0]=50;
			wyn=lps.cx/50;
			resz=lps.cx % 50;
			if(resz>0) wyn++;
			if(wyn>br) br=wyn;
			
			GetTextExtentPoint32(dc,ART[Aid[i]].Nazwa,strlen(ART[Aid[i]].Nazwa),&lps);
			max_c[1]=380;	
			wyn=lps.cx/380;
			resz=lps.cx % 380;
			if(resz>0) wyn++;
			if(wyn>br) br=wyn;
			
				
			GetTextExtentPoint32(dc,ART[Aid[i]].KOD_TOW,strlen(ART[Aid[i]].KOD_TOW),&lps);
			max_c[2]=80;
			wyn=lps.cx/80;
			resz=lps.cx % 80;
			if(resz>0) wyn++;
			if(wyn>br) br=wyn;
			
			memset(zn,0,350);
			itoa(ART[Aid[i]].Stan,zn,10);
			GetTextExtentPoint32(dc,zn,strlen(zn),&lps);
			max_c[3]=80;
			wyn=lps.cx/80;
			resz=lps.cx % 80;
			if(resz>0) wyn++;
			if(wyn>br) br=wyn;

			GetTextExtentPoint32(dc,ART[Aid[i]].JM,strlen(ART[Aid[i]].JM),&lps);
			max_c[4]=80;
			wyn=lps.cx/80;
			resz=lps.cx % 80;
			if(resz>0) wyn++;
			if(wyn>br) br=wyn;
			
			memset(zn,0,350);
			dbl_str(ART[Aid[i]].Marza,zn,2,350);
			GetTextExtentPoint32(dc,zn,strlen(zn),&lps);
			max_c[5]=80;
			wyn=lps.cx/80;
			resz=lps.cx % 80;
			if(resz>0) wyn++;
			if(wyn>br) br=wyn;

			memset(zn,0,350);
			dbl_str(ART[Aid[i]].Cena_Netto,zn,2,350);
			GetTextExtentPoint32(dc,zn,strlen(zn),&lps);
			max_c[6]=190;
			wyn=lps.cx/190;
			resz=lps.cx % 190;
			if(resz>0) wyn++;
			if(wyn>br) br=wyn;

			memset(zn,0,350);
			dbl_str(ART[Aid[i]].VAT,zn,2,350);
			GetTextExtentPoint32(dc,zn,strlen(zn),&lps);
			max_c[7]=50;
			wyn=lps.cx/50;
			resz=lps.cx % 50;
			if(resz>0) wyn++;
			if(wyn>br) br=wyn;

			memset(zn,0,350);
			dbl_str(ART[Aid[i]].Cena_Brutto,zn,2,350);
			GetTextExtentPoint32(dc,zn,strlen(zn),&lps);
			max_c[8]=190;
			wyn=lps.cx/190;
			resz=lps.cx % 190;
			if(resz>0) wyn++;
			if(wyn>br) br=wyn;

			memset(zn,0,350);
			dbl_str(ART[Aid[i]].Cena_Zakupu,zn,2,350);
			GetTextExtentPoint32(dc,zn,strlen(zn),&lps);
			max_c[9]=190;
			wyn=lps.cx/190;
			resz=lps.cx % 190;
			if(resz>0) wyn++;
			if(wyn>br) br=wyn;

			memset(zn,0,350);
			dbl_str(ART[Aid[i]].Cena_Zakupu*ART[Aid[i]].Stan,zn,2,350);
			GetTextExtentPoint32(dc,zn,strlen(zn),&lps);
			max_c[10]=190;
			wyn=lps.cx/190;
			resz=lps.cx % 190;
			if(resz>0) wyn++;
			if(wyn>br) br=wyn;

			wys=(br*40);
			wys=wys+20;
			if(-(pos-wys-2)>max_y)
			{
				EndPage(dc);
				StartPage(dc);
				pos=-252;
				SelectObject(dc,hb);
				Rectangle(dc,150,-250,1950,-252);
			}

			Rectangle(dc,150,pos,152,pos-wys-2);
			Rectangle(dc,1950,pos,1948,pos-wys-2);
			Rectangle(dc,150,pos-wys,1950,pos-wys-2);

			Rectangle(dc,222,pos,224,pos-wys);
			Rectangle(dc,624,pos,626,pos-wys);
			Rectangle(dc,726,pos,728,pos-wys);
			Rectangle(dc,828,pos,830,pos-wys);
			Rectangle(dc,930,pos,932,pos-wys);
			Rectangle(dc,1032,pos,1034,pos-wys);			
			Rectangle(dc,1244,pos,1246,pos-wys);
			Rectangle(dc,1316,pos,1318,pos-wys);
			Rectangle(dc,1528,pos,1530,pos-wys);
			Rectangle(dc,1740,pos,1742,pos-wys);
			for(k=0;k<11;k++)
			{
				pos1=pos-10;
				memset(zn,0,350);
				if(k==0) itoa(i,zn,10); else if(k==1) strcpy(zn,ART[Aid[i]].Nazwa); else if(k==2) strcpy(zn,ART[Aid[i]].KOD_TOW);
				else if(k==3)itoa(ART[Aid[i]].Stan,zn,10); else if(k==4) strcpy(zn,ART[Aid[i]].JM); else if(k==5) dbl_str(ART[Aid[i]].Marza,zn,2,350);
				else if(k==6) dbl_str(ART[Aid[i]].Cena_Netto,zn,2,350); else if(k==7) dbl_str(ART[Aid[i]].VAT,zn,2,350);
				else if(k==8) dbl_str(ART[Aid[i]].Cena_Brutto,zn,2,350); else if(k==9) dbl_str(ART[Aid[i]].Cena_Zakupu,zn,2,350);
				else if(k==10) dbl_str(ART[Aid[i]].Cena_Zakupu*ART[Aid[i]].Stan,zn,2,350);
				if(zn[0]==0) continue;
				j=0;
				
				GetTextExtentPoint32(dc,zn,strlen(zn),&lps);
				wyn=lps.cx/max_c[k];
				resz=lps.cx%max_c[k];
				if(resz>0)wyn++;
				for(l=0;l<wyn;l++)
				{
					m=0;
					if(l+1==wyn)TextOut(dc,posX[k],pos1,zn+j,strlen(zn)-j);
					else
					{
						do
						{
							m++;
							GetTextExtentPoint32(dc,zn+j,m,&lps);
						}while(lps.cx<max_c[k]);
						TextOut(dc,posX[k],pos1,zn+j,m-1);
						j+=(m-1);
						pos1-=40;
					}
				}
				
			}	
			pos=pos-wys-2;

		}

		EndPage(dc);
		EndDoc(dc);
		DeleteObject(font);
		DeleteObject(hb);
		DeleteDC(dc);	
				
	}
	
	return 1;
}
int Print_Mag1(PRINTER_INFO_2 pr_info,HWND hwd, int *Aid, int cnt)
{

	char text[350];

	bool bl;
	HANDLE hnd;
	HDC dc;
	HFONT font,font1;
	LOGFONT lgf;
	_DOCINFOA Doc_info;
	SIZE lps;
	HBRUSH hb;
	int i,j,k,pos,pos1,br,wyn,resz,wys,l,m;
	int max_x,max_y,max_c[6],posX[6];
	SIZE size;
	char zn[350];

	
	
	Doc_info.lpszDocName="Stan Magazynowy";
	Doc_info.lpszDatatype=pr_info.pDatatype;
	Doc_info.lpszOutput=NULL;
	
	dc=CreateDC(pr_info.pDriverName,pr_info.pPrinterName,pr_info.pPortName,pr_info.pDevMode);
	if(!dc)
	{
		MessageBox(hwd,"Nie mo¿na pobraæ kontekstu drukarki","Wiadomoœæ",MB_OK);
		return 0;
	}else
	{
		
		StartDocA(dc,&Doc_info);	
		StartPage(dc);
		SetMapMode(dc,MM_LOMETRIC);
		GetWindowExtEx(dc,&lps);
		max_x=lps.cx;
		max_y=lps.cy-20;
		hb=CreateSolidBrush((COLORREF)0);	
		
		lgf.lfCharSet=EASTEUROPE_CHARSET;
		lgf.lfOutPrecision=OUT_DEFAULT_PRECIS;
		lgf.lfClipPrecision=CLIP_DEFAULT_PRECIS;
		lgf.lfQuality=DEFAULT_QUALITY;
		lgf.lfPitchAndFamily=DEFAULT_PITCH | FF_ROMAN;
		lgf.lfWeight=FW_SEMIBOLD;
		lgf.lfHeight=65;
		lgf.lfWidth=16;
		lgf.lfOrientation=0;
		lgf.lfItalic=false;
		lgf.lfStrikeOut=false;
		lgf.lfUnderline=false;
		lgf.lfOrientation=0;
		lgf.lfEscapement=0;
		font=CreateFontIndirect(&lgf);
		memset(text,0,350);
		sprintf(text,"S p i s    N a t u r y    R z e c z y");
				
		SelectObject(dc,font);
		GetTextExtentPoint32(dc,text,strlen(text),&size);
		i=2100-size.cx;
		i=i/2;
		TextOut(dc,i,-100,text,strlen(text));
		DeleteObject(font);
		lgf.lfWidth=10;
		lgf.lfHeight=40;
		lgf.lfWeight=FW_SEMIBOLD;
		font=CreateFontIndirect(&lgf);
		SelectObject(dc,hb);
		Rectangle(dc,150,-220,1632,-222);
		Rectangle(dc,150,-221,152,-325);
		Rectangle(dc,1632,-221,1630,-325);
		Rectangle(dc,151,-323,1632,-325);
		DeleteObject(hb);
		hb=CreateSolidBrush((COLORREF)0xFDBFB3);
		SelectObject(dc,hb);
		Rectangle(dc,152,-222,1630,-323);
		DeleteObject(hb);
		hb=CreateSolidBrush((COLORREF)0);
		SelectObject(dc,hb);
		Rectangle(dc,222,-221,224,-323);
		Rectangle(dc,824,-221,826,-323);
		Rectangle(dc,926,-221,928,-323);
		Rectangle(dc,1028,-221,1030,-323);
		Rectangle(dc,1330,-221,1332,-323);
		//Rectangle(dc,1632,-221,1634,-323);			
		
		SelectObject(dc,font);
		SetBkColor(dc,(COLORREF)0xFDBFB3);
		GetTextExtentPoint32(dc,"LP",2,&size);i=(70-size.cx)/2;
		TextOut(dc,152+i,-252,"LP",2);
		posX[0]=162;
		GetTextExtentPoint32(dc,"NAZWA",5,&size);i=(600-size.cx)/2;
		TextOut(dc,224+i,-252,"NAZWA",5);
		posX[1]=234;
		GetTextExtentPoint32(dc,"STAN",4,&size);i=(100-size.cx)/2;
		TextOut(dc,826+i,-252,"STAN",4);
		posX[2]=836;
		GetTextExtentPoint32(dc,"JM",2,&size);i=(100-size.cx)/2;
		TextOut(dc,928+i,-252,"JM",2);
		posX[3]=938;
		GetTextExtentPoint32(dc,"CENA ZAKUPU",11,&size);i=(300-size.cx)/2;
		TextOut(dc,1030+i,-252,"CENA ZAKUPU",11);
		posX[4]=1040;
		GetTextExtentPoint32(dc,"ZAKUP RAZEM",11,&size);i=(300-size.cx)/2;
		TextOut(dc,1332+i,-252,"ZAKUP RAZEM",11);
		posX[5]=1342;

		pos=-325;
		DeleteObject(font);
		lgf.lfWeight=FW_NORMAL;
		lgf.lfWidth=10;
		font=CreateFontIndirect(&lgf);
		SetBkColor(dc,(COLORREF)0xFFFFFF);
		for(i=0;i<cnt;i++)
		{
			br=1;
			memset(zn,0,350);
			itoa(i,zn,10);
			GetTextExtentPoint32(dc,zn,strlen(zn),&lps);
			max_c[0]=50;
			wyn=lps.cx/50;
			resz=lps.cx % 50;
			if(resz>0) wyn++;
			if(wyn>br) br=wyn;
			
			GetTextExtentPoint32(dc,ART[Aid[i]].Nazwa,strlen(ART[Aid[i]].Nazwa),&lps);
			max_c[1]=580;
			wyn=lps.cx/580;
			resz=lps.cx % 580;
			if(resz>0) wyn++;	
			if(wyn>br) br=wyn;
			
				
			memset(zn,0,350);
			itoa(ART[Aid[i]].Stan,zn,10);
			GetTextExtentPoint32(dc,zn,strlen(zn),&lps);
			max_c[2]=80;
			wyn=lps.cx/80;
			resz=lps.cx % 80;
			if(resz>0) wyn++;
			if(wyn>br) br=wyn;

			GetTextExtentPoint32(dc,ART[Aid[i]].JM,strlen(ART[Aid[i]].JM),&lps);
			max_c[3]=80;
			wyn=lps.cx/80;
			resz=lps.cx % 80;
			if(resz>0) wyn++;
			if(wyn>br) br=wyn;
			

			memset(zn,0,350);
			dbl_str(ART[Aid[i]].Cena_Zakupu,zn,2,350);
			GetTextExtentPoint32(dc,zn,strlen(zn),&lps);
			max_c[4]=280;
			wyn=lps.cx/280;
			resz=lps.cx % 280;
			if(resz>0) wyn++;
			if(wyn>br) br=wyn;

			memset(zn,0,350);
			dbl_str(ART[Aid[i]].Cena_Zakupu*ART[Aid[i]].Stan,zn,2,350);
			GetTextExtentPoint32(dc,zn,strlen(zn),&lps);
			max_c[5]=280;
			wyn=lps.cx/280;
			resz=lps.cx % 280;
			if(resz>0) wyn++;
			if(wyn>br) br=wyn;

			
			wys=(br*40);
			wys=wys+20;
			if(-(pos-wys-2)>max_y)
			{
				EndPage(dc);
				StartPage(dc);
				pos=-252;
				SelectObject(dc,hb);
				Rectangle(dc,150,-250,1632,-252);
			}

			Rectangle(dc,150,pos,152,pos-wys-2);
			Rectangle(dc,1632,pos,1630,pos-wys-2);
			Rectangle(dc,150,pos-wys,1632,pos-wys-2);

			Rectangle(dc,222,pos,224,pos-wys);
			Rectangle(dc,824,pos,826,pos-wys);
			Rectangle(dc,926,pos,928,pos-wys);
			Rectangle(dc,1028,pos,1030,pos-wys);
			Rectangle(dc,1332,pos,1334,pos-wys);			
	
			for(k=0;k<6;k++)
			{
				pos1=pos-10;
				memset(zn,0,350);
				if(k==0) itoa(i,zn,10); else if(k==1) strcpy(zn,ART[Aid[i]].Nazwa); else if(k==2) dbl_str(ART[Aid[i]].Stan,zn,2,350);
				else if(k==3) strcpy(zn,ART[Aid[i]].JM); else if(k==4) dbl_str(ART[Aid[i]].Cena_Zakupu,zn,2,350); else if(k==5) dbl_str(ART[Aid[i]].Cena_Zakupu*ART[Aid[i]].Stan,zn,2,350);
				
				if(zn[0]==0) continue;
				j=0;
				
				GetTextExtentPoint32(dc,zn,strlen(zn),&lps);
				wyn=lps.cx/max_c[k];
				resz=lps.cx%max_c[k];
				if(resz>0)wyn++;
				for(l=0;l<wyn;l++)
				{
					m=0;
					if(l+1==wyn)TextOut(dc,posX[k],pos1,zn+j,strlen(zn)-j);
					else
					{
						do
						{
							m++;
							GetTextExtentPoint32(dc,zn+j,m,&lps);
						}while(lps.cx<max_c[k]);
						TextOut(dc,posX[k],pos1,zn+j,m-1);
						j+=(m-1);
						pos1-=40;
					}				
				}
				
			}	
			pos=pos-wys-2;

		}

		EndPage(dc);
		EndDoc(dc);
		DeleteObject(font);
		DeleteObject(hb);
		DeleteDC(dc);	
				
	}
	
	return 1;
}