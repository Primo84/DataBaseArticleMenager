

#include "DBAM_F.h"
#include "commctrl.h"
#include "ctype.h"



fstream pl;

HWND LV1,LV2,LVD4,LVD6,LVD8,LVD9,LVD_45,CB1,CB2,CB3,CB4,CB5,CB6,CB7,CB8,CB9,CB10,E_Naz;
HWND E1,E2,E3,E4,E5,E6,E7,E8,E9,E10,E11,E12,E13,E14,E15,E16; //kontrolki do wyszukiwania rekordów
HWND B_Szuk,Panel;    // Przycisk wyszukiwania;
MSG msg;
int cx,cy,sy,my,idp;
HDC Wdc,hdc1;
PAINTSTRUCT lpP;
HDC hdc;
bool is_edit,is_dlg1,is_zarz,is_editp,is_wyb_k,is_ch_k,is_dlg2,is_dlg3,is_dlg4,is_dlg6,is_dlg8,is_z_k,is_Korekta;
bool is_ok,is_dlg14, is_zm_wal,is_tow,is_zapT,is_d,is_param,is_send,is_del,is_zap13, is_zm_num;
int * t_id,*A_id,Aid,Tid,*KID,idk,*FID,fid,Kas_id;//*numT;
int Vat_C,id_k;
bool funkcja,is_show;
Fakt_Vat *F_Vat;
char kod_tow[35];
WNDPROC wnd_e,wnd_e1,wnd_e2;
int ecode;
TOW_K TK,TK_T;
JM *jmt;
GR_T *gr_t;
ST_VAT *stv;


HIMAGELIST ImgL;
HTREEITEM H_tri[6];
HTREEITEM H_f[43];
HTREEITEM HTR;
TVINSERTSTRUCTA tv_str;
TVITEMA tv_item;
LPSTR Funkcje[6]={"FUNKCJE ZARZ¥DZANIA TOWARAMI","WYDRUKI RAPORTÓW","FUNKCJE KONFIGURACJI KASY","FUNKCJE OBS£UGI SPRZEDA¯Y","FUNKCJE OBS£UGI KASJERÓW I SPRZEDAWCÓW"};
LPSTR FunkcjeTow[33]={"Odczytanie bazy towarowej z wybranej kasy","Zapisanie pe³nych danych o towarze","Odczytanie pe³nych danych o towarze ","Kasowanie towaru","Wys³anie towarów do kasy fiskalnej","Kasowanie wszystkich towarów","Odczytanie maksymalnego numer zdefiniowanego towaru","Odczytanie iloœci zapisanych w kasie towarów","Wydruk raportów zmienionych i skasowanych towarów","Wydruk raportu fiskalnego dobowego",
							"Odczytanie numeru kasy w systemie","Zapisanie numeru kasy w systemie","Odczytanie bajtów konfiguracji kasy","Zapisanie bajtów konfiguracji kasy"
							,"Odczytanie nazw jednostek","Zapisanie nazw jednostek","Odczytanie nazw grup towarowych","Zapisanie nazw grup towarowych",
							"Odczytanie stawek podatkowych","Odczytanie nazw form p³atnoœci",
							"Zapisanie nazw form p³atnoœci","Odczytanie maksymalnego rabatu","Zapisanie maksymalnego rabatu",
							"Odczytanie maksymalnego narzutu","Zapisanie maksymalnego narzutu","Aktualizacja stanów magazynowych z kas¹ fiskaln¹",
							"Odczytanie aktualnego raportu godzinowego","Odczytanie poprzedniego raportu godzinowego",
							"Odczytanie rodzajów kasjerów","Zapisanie rodzajów kasjerów","Odczytanie danych o kasjerach","Zapisanie danych o kasjerach",
							"Kasowanie danych o kasjerach"
					};
int item[37]={0,0,0,0,0,0,0,0,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,4,4,4,4,4,4,4,4,4};

LPSTR VAT_Col[12]={"LP","NAZWA","PKWiU","ILOŒÆ","JM","CENA NETTO","RABAT","CENA NETTO","VAT","KWOTA NETTO","KWOTA VAT","KWOTA BRUTTO"};
LPSTR LV1_Col[13]={"NAZWA TOWARU","PRODUCENT","STAN","JM","CENA ZAKUPU","MAR¯A(%)","CENA NETTO","VAT(%)","CENA BRUTTO","MINIMUM","KOD KRÓTKI","KOD KRESKOWY","NUMER FAKTURY"};
LPSTR LV2_Col[9]={"NAZWA","KRAJ","MIASTO","ADRES","KOD POCZTOWY","TELEFON","FAX","NIP","REGON"};
LPSTR KONTR_Col[8]={"NAZWA","ADRES","KOD POCZTOWY","MIASTO","KRAJ","NIP","REGON","TELEFON"};
LPSTR LVD8_Col[9]={"NUMER","NAZWA KONTRAHENTA", "DATA WYSTAWIENIA", "KWOTA  NETTO", "KWOTA VAT", "KWOTA BRUTTO","ZAPLACONO","DO ZAPLATY","TERMIN P£ATNOŒCI"};
LPSTR LVD15[5]={"NAZWA","NUMER KASY","PORT","SZYBKOŒÆ TRANSMISJI","RODZAJ PO£¥CZENIA"};
LPSTR LVD37[4]={"GODZINA","ILOŒÆ PAR","ILOŒÆ POZYCJ PAR","WARTOŒÆ SPRZEDA¯Y"};
LPSTR LVD43[5]={"ROK","MIESI¥C","SPRZEDA¯ TOWARU NETTO","PRZYJECIE TOWARU NETTO","SALDO"};
LPSTR LVD45[5]={"ILOŒÆ TOWARÓW","CENA ZAKUPU","ŒREDNIA MAR¯A","CENA NETTO","CENA BRUTTO"};
INT LV37_W[4]={85,100,180,200};
INT LV43_W[5]={85,100,200,200,140};
int LVD4_W[12]={40,200,75,75,60,150,75,150,75,150,150,150};
int LV2_Width[10]={200,150,150,200,150,150,150,150,150,150};
int LV1_Width[13]={200,200,70,70,130,90,130,60,130,80,120,160,185};
int	LV1I_MAX[6]={250,350,25,25,13,14};
int LVD6_W[8]={200,200,175,175,175,175,175,175};
int LVD8_W[8]={200,300,175,175,175,175,175,175};
int LVD15_W[5]={230,150,70,150,200};
int LVD45_W[5]={150,150,150,150,150};


LOGFONT lgf={20,9,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_ROMAN,"Times New Roman"};
HFONT fnt;


WNDPROC wnd_b1,wnd_tv1;


		//Funkcja tworz¹ca kontrolki okna aplikacji


bool Create_Controls(HWND hwd)
{
	LVCOLUMN lcl;
	LVITEM lvi;
	int i,j,x,x1,i1,i2;
	LPSTR LPS;
	char zn[350];
	RECT rc,rc1;
	GetClientRect(hwd,&rc);
	BOOL b;
	if(hwd==NULL) return NULL;
	MENUITEMINFO mni;

	is_zarz=false;
	is_Korekta=false;
	is_tow=false;
	b=RegisterHotKey(hwd,(int)HOT_KON,MOD_CONTROL,'K');
	b=RegisterHotKey(hwd,(int)HOT_ADD_A,MOD_ALT,'A');
	b=RegisterHotKey(hwd,(int)HOT_REM_A,MOD_ALT,'R');
	b=RegisterHotKey(hwd,(int)HOT_ED_A,MOD_ALT,'E');
	b=RegisterHotKey(hwd,(int)HOT_P_D,MOD_ALT,'D');
	b=RegisterHotKey(hwd,(int)HOT_P_Z,MOD_ALT,'Z');
	b=RegisterHotKey(hwd,(int)HOT_F_W,MOD_ALT,'W');
	b=RegisterHotKey(hwd,(int)HOT_F_Z,MOD_ALT,'F');
	b=RegisterHotKey(hwd,(int)HOT_K_Z,MOD_CONTROL,'Z');
	b=RegisterHotKey(hwd,(int)HOT_FIR,MOD_CONTROL,'F');
	b=RegisterHotKey(hwd,(int)HOT_P_T,MOD_CONTROL,'T');
	b=RegisterHotKey(hwd,(int)HOT_K_A,MOD_CONTROL,'A');
	b=RegisterHotKey(hwd,(int)HOT_K_I,MOD_CONTROL,'I');
	b=RegisterHotKey(hwd,(int)HOT_K_U,MOD_CONTROL,'U');
	b=RegisterHotKey(hwd,(int)HOT_K_S,MOD_CONTROL,'S');
	b=RegisterHotKey(hwd,(int)HOT_K_D,MOD_CONTROL,'D');
	b=RegisterHotKey(hwd,(int)HOT_U_WAL,MOD_ALT,'M');
	b=RegisterHotKey(hwd,(int)HOT_U_FZ,MOD_ALT,'P');
	b=RegisterHotKey(hwd,(int)HOT_U_ST,MOD_ALT,'S');
	b=RegisterHotKey(hwd,(int)HOT_U_NF,MOD_ALT,'N');
	b=RegisterHotKey(hwd,(int)HOT_U_JM,MOD_ALT,'J');
	b=RegisterHotKey(hwd,(int)HOT_U_GR,MOD_ALT,'G');

	LV1=CreateWindow(WC_LISTVIEWA,"DataBaseArticleMenager",LVS_REPORT|LVS_SHOWSELALWAYS|LVS_SINGLESEL|WS_VISIBLE|WS_CHILD,10,227,MAX_X-370,MAX_Y-250-sy-40,hwd,NULL,hst,0);
	fnt=GetWindowFont(LV1);
	fnt=CreateFontIndirect(&lgf);
	SetWindowFont(LV1,fnt,true);
	ListView_SetExtendedListViewStyle(LV1,LVS_EX_AUTOSIZECOLUMNS|LVS_EX_FULLROWSELECT|LVS_EX_LABELTIP|LVS_EX_GRIDLINES|LVS_EX_ONECLICKACTIVATE);
	DeleteObject(fnt);
	//Inicjalizuje kontrolke LV1
	
	ListView_SetTextBkColor(LV1,0x99FFFF);
	//ListView_SetBkColor(LV1,0x66FFFF);
	ListView_SetBkColor(LV1,0x99FFFF);
	lcl.mask=LVCF_TEXT|LVCF_WIDTH;
	for(i=0;i<13;i++)
	{
		lcl.pszText=LV1_Col[i];
		lcl.cx=LV1_Width[i];
		x=ListView_InsertColumn(LV1,i,&lcl);
	}
	A_id=new int[HD_A.count];
	memset(A_id,-1,HD_A.count);
	lvi.mask=LVIF_TEXT;
	lvi.iSubItem=0;
	for(i=0;i<HD_A.count;i++)
	{
		lvi.iItem=i;
		lvi.pszText=ART[i].Nazwa; 
		i2=ListView_InsertItem(LV1,&lvi);
		A_id[i2]=i;
		for(i1=1;i1<13;i1++)
		{
			memset(zn,0,350);
			LPS=zn;
			if(i1==1)LPS=ART[i].Producent;else if(i1==2)dbl_str(ART[i].Stan,LPS,2,350);else if(i1==3)LPS=ART[i].JM;else if(i1==4)
			{
				memset(zn,0,350);
				dbl_str(ART[i].Cena_Zakupu,zn,2,350);
				strcpy(zn+strlen(zn)," ");
				strcpy(zn+strlen(zn),wal[cnt.def_wal].znak);
			}else 
				if(i1==5)dbl_str(ART[i].Marza,LPS,2,350); else if(i1==6) 
				{
					memset(zn,0,350);
					dbl_str(ART[i].Cena_Netto,zn,2,350);
					strcpy(zn+strlen(zn)," ");
					strcpy(zn+strlen(zn),wal[cnt.def_wal].znak);

				}else 
					if(i1==7) dbl_str(ART[i].VAT,LPS,2,350); else
					if(i1==8) 
					{
						memset(zn,0,350);
						dbl_str(ART[i].Cena_Brutto,zn,2,350);
						strcpy(zn+strlen(zn)," ");
						strcpy(zn+strlen(zn),wal[cnt.def_wal].znak); 
					}else 
						if(i1==9) dbl_str(ART[i].Stan_Kr,LPS,2,350); else
							if(i1==10) LPS=ART[i].KOD_TOW;else
								if(i1==11)LPS=ART[i].KOD_KR; else
									if(i1==12)LPS=ART[i].Num_Fakt;
			ListView_SetItemText(LV1,i2,i1,LPS);
		}
	}
	//	koniec inicjalizacji kontrolki LV1

	// Tworzy kontrolki do wyszuliwania rekordów
	CB1=CreateWindow("Check","Nazwa Towaru",WS_CHILD|WS_VISIBLE,15,25,150,28,MainWnd,NULL,hst,0);
	CB2=CreateWindow("Check","Nazwa Producenta",WS_CHILD|WS_VISIBLE,15,56,150,28,MainWnd,NULL,hst,0);
	CB3=CreateWindow("Check","Stan",WS_CHILD|WS_VISIBLE,15,87,150,28,MainWnd,NULL,hst,0);
	CB4=CreateWindow("Check","Cena Zakupu",WS_CHILD|WS_VISIBLE,15,118,150,28,MainWnd,NULL,hst,0);
	CB5=CreateWindow("Check","Mar¿a",WS_CHILD|WS_VISIBLE,15,149,150,28,MainWnd,NULL,hst,0);
	CB6=CreateWindow("Check","Cena Netto",WS_CHILD|WS_VISIBLE,180,25,150,28,MainWnd,NULL,hst,0);
	CB7=CreateWindow("Check","Vat",WS_CHILD|WS_VISIBLE,180,56,150,28,MainWnd,NULL,hst,0);
	CB8=CreateWindow("Check","Cena Brutto",WS_CHILD|WS_VISIBLE,180,87,150,28,MainWnd,NULL,hst,0);
	CB9=CreateWindow("Check","Minimum",WS_CHILD|WS_VISIBLE,180,118,150,28,MainWnd,NULL,hst,0);
	CB10=CreateWindow("Check","Kod Towaru",WS_CHILD|WS_VISIBLE,180,149,150,28,MainWnd,NULL,hst,0);
	E1=CreateWindowEx(WS_EX_DLGMODALFRAME,"Edit","",ES_UPPERCASE|ES_AUTOHSCROLL|WS_BORDER|WS_CHILD|WS_VISIBLE,350,35,200,28,MainWnd,NULL,hst,0);							//Nazwa Producenta
	E2=CreateWindowEx(WS_EX_DLGMODALFRAME,"Edit","",ES_UPPERCASE|ES_AUTOHSCROLL|WS_BORDER|WS_CHILD|WS_VISIBLE,350,88,200,28,MainWnd,NULL,hst,0);							//Nazwa Towaru	
	E3=CreateWindowEx(WS_EX_DLGMODALFRAME,"Edit","",ES_NUMBER|ES_UPPERCASE|ES_AUTOHSCROLL|WS_BORDER|WS_CHILD|WS_DISABLED|WS_VISIBLE,350,141,88,28,MainWnd,NULL,hst,0);		//Stan
	E4=CreateWindowEx(WS_EX_DLGMODALFRAME,"Edit","",ES_UPPERCASE|ES_AUTOHSCROLL|WS_BORDER|WS_CHILD|WS_VISIBLE|WS_DISABLED,575,35,85,28,MainWnd,NULL,hst,0);					//	
	E5=CreateWindowEx(WS_EX_DLGMODALFRAME,"Edit","",ES_UPPERCASE|ES_AUTOHSCROLL|WS_BORDER|WS_CHILD|WS_VISIBLE|WS_DISABLED,575,88,85,28,MainWnd,NULL,hst,0);
	E6=CreateWindowEx(WS_EX_DLGMODALFRAME,"Edit","",ES_UPPERCASE|ES_AUTOHSCROLL|WS_BORDER|WS_CHILD|WS_VISIBLE|WS_DISABLED,575,141,85,28,MainWnd,NULL,hst,0);
	E7=CreateWindowEx(WS_EX_DLGMODALFRAME,"Edit","",ES_UPPERCASE|ES_AUTOHSCROLL|WS_BORDER|WS_CHILD|WS_VISIBLE|WS_DISABLED,679,35,85,28,MainWnd,NULL,hst,0);
	E8=CreateWindowEx(WS_EX_DLGMODALFRAME,"Edit","",ES_UPPERCASE|ES_AUTOHSCROLL|WS_BORDER|WS_CHILD|WS_VISIBLE|WS_DISABLED,679,88,85,28,MainWnd,NULL,hst,0);
	E9=CreateWindowEx(WS_EX_DLGMODALFRAME,"Edit","",ES_UPPERCASE|ES_AUTOHSCROLL|WS_BORDER|WS_CHILD|WS_VISIBLE|WS_DISABLED,679,141,85,28,MainWnd,NULL,hst,0);
	E10=CreateWindowEx(WS_EX_DLGMODALFRAME,"Edit","",ES_UPPERCASE|ES_AUTOHSCROLL|WS_BORDER|WS_CHILD|WS_VISIBLE|WS_DISABLED,800,35,55,28,MainWnd,NULL,hst,0);
	E11=CreateWindowEx(WS_EX_DLGMODALFRAME,"Edit","",ES_UPPERCASE|ES_AUTOHSCROLL|WS_BORDER|WS_CHILD|WS_VISIBLE|WS_DISABLED,800,88,85,28,MainWnd,NULL,hst,0);
	E12=CreateWindowEx(WS_EX_DLGMODALFRAME,"Edit","",ES_UPPERCASE|ES_AUTOHSCROLL|WS_BORDER|WS_CHILD|WS_VISIBLE|WS_DISABLED,904,88,85,28,MainWnd,NULL,hst,0);
	E13=CreateWindowEx(WS_EX_DLGMODALFRAME,"Edit","",ES_NUMBER|ES_UPPERCASE|ES_AUTOHSCROLL|WS_BORDER|WS_CHILD|WS_VISIBLE|WS_DISABLED,800,141,88,28,MainWnd,NULL,hst,0);
	E14=CreateWindowEx(WS_EX_DLGMODALFRAME,"Edit","",ES_NUMBER|ES_UPPERCASE|ES_AUTOHSCROLL|WS_BORDER|WS_CHILD|WS_VISIBLE|WS_DISABLED,904,141,88,28,MainWnd,NULL,hst,0);
	E15=CreateWindowEx(WS_EX_DLGMODALFRAME,"Edit","",ES_NUMBER|ES_UPPERCASE|ES_AUTOHSCROLL|WS_BORDER|WS_CHILD|WS_DISABLED|WS_VISIBLE,457,141,88,28,MainWnd,NULL,hst,0);
	E16=CreateWindowEx(WS_EX_DLGMODALFRAME,"Edit","",ES_UPPERCASE|ES_AUTOHSCROLL|WS_BORDER|WS_CHILD|WS_VISIBLE|WS_DISABLED,904,35,88,28,MainWnd,NULL,hst,0);
	Check_check(CB1,true);
	Check_check(CB2,true);

	SetProp(E4,"PROC",(HANDLE)GetWindowLong(E4,GWL_WNDPROC));
	SetProp(E4,"BOOL",(HANDLE)false);
	SetWindowLong(E4,GWL_WNDPROC,(LONG)WndEProc);
	SetProp(E7,"PROC",(HANDLE)GetWindowLong(E7,GWL_WNDPROC));
	SetProp(E7,"BOOL",(HANDLE)false);
	SetWindowLong(E7,GWL_WNDPROC,(LONG)WndEProc);
	SetProp(E5,"PROC",(HANDLE)GetWindowLong(E5,GWL_WNDPROC));
	SetProp(E5,"BOOL",(HANDLE)false);
	SetWindowLong(E5,GWL_WNDPROC,(LONG)WndEProc);
	SetProp(E8,"PROC",(HANDLE)GetWindowLong(E8,GWL_WNDPROC));
	SetProp(E8,"BOOL",(HANDLE)false);
	SetWindowLong(E8,GWL_WNDPROC,(LONG)WndEProc);
	SetProp(E6,"PROC",(HANDLE)GetWindowLong(E6,GWL_WNDPROC));
	SetProp(E6,"BOOL",(HANDLE)false);
	SetWindowLong(E6,GWL_WNDPROC,(LONG)WndEProc);
	SetProp(E9,"PROC",(HANDLE)GetWindowLong(E9,GWL_WNDPROC));
	SetProp(E9,"BOOL",(HANDLE)false);
	SetWindowLong(E9,GWL_WNDPROC,(LONG)WndEProc);
	SetProp(E10,"PROC",(HANDLE)GetWindowLong(E10,GWL_WNDPROC));
	SetProp(E10,"BOOL",(HANDLE)false);
	SetWindowLong(E10,GWL_WNDPROC,(LONG)WndEProc);
	SetProp(E11,"PROC",(HANDLE)GetWindowLong(E11,GWL_WNDPROC));
	SetProp(E11,"BOOL",(HANDLE)false);
	SetWindowLong(E11,GWL_WNDPROC,(LONG)WndEProc);
	SetProp(E12,"PROC",(HANDLE)GetWindowLong(E12,GWL_WNDPROC));
	SetProp(E12,"BOOL",(HANDLE)false);
	SetWindowLong(E12,GWL_WNDPROC,(LONG)WndEProc);
	//Check_SetBkg(CB1,(DWORD)0xFEE4DE);
	//Check_SetBkg(CB2,(DWORD)0xFEE4DE);
	//Check_SetBkg(CB3,(DWORD)0xFEE4DE);
	//Check_SetBkg(CB4,(DWORD)0xFEE4DE);
	//Check_SetBkg(CB5,(DWORD)0xFEE4DE);
	//Check_SetBkg(CB6,(DWORD)0xFEE4DE);
	//Check_SetBkg(CB7,(DWORD)0xFEE4DE);
	//Check_SetBkg(CB8,(DWORD)0xFEE4DE);
	//Check_SetBkg(CB9,(DWORD)0xFEE4DE);
	//Check_SetBkg(CB10,(DWORD)0xFEE4DE);

	Check_SetHoverColor(CB1,(DWORD)0xFEE4DE);
	Check_SetHoverColor(CB2,(DWORD)0xFEE4DE);
	Check_SetHoverColor(CB3,(DWORD)0xFEE4DE);
	Check_SetHoverColor(CB4,(DWORD)0xFEE4DE);
	Check_SetHoverColor(CB5,(DWORD)0xFEE4DE);
	Check_SetHoverColor(CB6,(DWORD)0xFEE4DE);
	Check_SetHoverColor(CB7,(DWORD)0xFEE4DE);
	Check_SetHoverColor(CB8,(DWORD)0xFEE4DE);
	Check_SetHoverColor(CB9,(DWORD)0xFEE4DE);
	Check_SetHoverColor(CB10,(DWORD)0xFEE4DE);
	//Koniec tworzenia kontrolek wyszukiwania
	B_Szuk=CreateWindowEx(WS_EX_DLGMODALFRAME,"Button","Szukaj",BS_DEFPUSHBUTTON|WS_BORDER|WS_CHILD|WS_VISIBLE,350,173,150,28,MainWnd,(HMENU)ID_B_Szuk,hst,0);
	mni.cbSize=sizeof(MENUITEMINFO);
	mni.fMask=MIIM_BITMAP;
	mni.hbmpItem=(HBITMAP)LoadBitmap(hst,MAKEINTRESOURCE(IDB_1));
	b=SetMenuItemInfo(GetSubMenu(GetMenu(MainWnd),0),0,true,&mni);
	mni.hbmpItem=(HBITMAP)LoadBitmap(hst,MAKEINTRESOURCE(IDB_2));
	b=SetMenuItemInfo(GetSubMenu(GetMenu(MainWnd),1),0,true,&mni);
	mni.hbmpItem=(HBITMAP)LoadBitmap(hst,MAKEINTRESOURCE(IDB_3));
	b=SetMenuItemInfo(GetSubMenu(GetMenu(MainWnd),2),0,true,&mni);
	mni.hbmpItem=(HBITMAP)LoadBitmap(hst,MAKEINTRESOURCE(IDB_4));
	b=SetMenuItemInfo(GetSubMenu(GetMenu(MainWnd),2),1,true,&mni);
	mni.hbmpItem=(HBITMAP)LoadBitmap(hst,MAKEINTRESOURCE(IDB_5));
	b=SetMenuItemInfo(GetSubMenu(GetMenu(MainWnd),2),2,true,&mni);
	mni.hbmpItem=(HBITMAP)LoadBitmap(hst,MAKEINTRESOURCE(IDB_9));
	b=SetMenuItemInfo(GetSubMenu(GetMenu(MainWnd),2),3,true,&mni);
	mni.hbmpItem=(HBITMAP)LoadBitmap(hst,MAKEINTRESOURCE(IDB_6));
	b=SetMenuItemInfo(GetSubMenu(GetMenu(MainWnd),3),0,true,&mni);
	mni.hbmpItem=(HBITMAP)LoadBitmap(hst,MAKEINTRESOURCE(IDB_8));
	b=SetMenuItemInfo(GetSubMenu(GetMenu(MainWnd),3),1,true,&mni);
	mni.hbmpItem=(HBITMAP)LoadBitmap(hst,MAKEINTRESOURCE(IDB_7));
	b=SetMenuItemInfo(GetSubMenu(GetMenu(MainWnd),4),0,true,&mni);
	mni.hbmpItem=(HBITMAP)LoadBitmap(hst,MAKEINTRESOURCE(IDB_10));
	b=SetMenuItemInfo(GetSubMenu(GetMenu(MainWnd),4),1,true,&mni);
	mni.hbmpItem=(HBITMAP)LoadBitmap(hst,MAKEINTRESOURCE(IDB_8));
	b=SetMenuItemInfo(GetSubMenu(GetMenu(MainWnd),5),0,true,&mni);
	mni.hbmpItem=(HBITMAP)LoadBitmap(hst,MAKEINTRESOURCE(IDB_11));
	b=SetMenuItemInfo(GetSubMenu(GetMenu(MainWnd),6),0,true,&mni);
	mni.hbmpItem=(HBITMAP)LoadBitmap(hst,MAKEINTRESOURCE(IDB_4));
	b=SetMenuItemInfo(GetSubMenu(GetMenu(MainWnd),6),1,true,&mni);
	mni.hbmpItem=(HBITMAP)LoadBitmap(hst,MAKEINTRESOURCE(IDB_12));
	b=SetMenuItemInfo(GetSubMenu(GetMenu(MainWnd),6),2,true,&mni);
	mni.hbmpItem=(HBITMAP)LoadBitmap(hst,MAKEINTRESOURCE(IDB_72));
	b=SetMenuItemInfo(GetSubMenu(GetMenu(MainWnd),6),3,true,&mni);
	mni.hbmpItem=(HBITMAP)LoadBitmap(hst,MAKEINTRESOURCE(IDB_73));
	b=SetMenuItemInfo(GetSubMenu(GetMenu(MainWnd),6),4,true,&mni);
	mni.hbmpItem=(HBITMAP)LoadBitmap(hst,MAKEINTRESOURCE(IDB_67));
	b=SetMenuItemInfo(GetSubMenu(GetMenu(MainWnd),7),0,true,&mni);
	mni.hbmpItem=(HBITMAP)LoadBitmap(hst,MAKEINTRESOURCE(IDB_68));
	b=SetMenuItemInfo(GetSubMenu(GetMenu(MainWnd),7),1,true,&mni);
	mni.hbmpItem=(HBITMAP)LoadBitmap(hst,MAKEINTRESOURCE(IDB_69));
	b=SetMenuItemInfo(GetSubMenu(GetMenu(MainWnd),7),2,true,&mni);
	mni.hbmpItem=(HBITMAP)LoadBitmap(hst,MAKEINTRESOURCE(IDB_70));
	b=SetMenuItemInfo(GetSubMenu(GetMenu(MainWnd),7),3,true,&mni);
	mni.hbmpItem=(HBITMAP)LoadBitmap(hst,MAKEINTRESOURCE(IDB_71));
	b=SetMenuItemInfo(GetSubMenu(GetMenu(MainWnd),7),4,true,&mni);
	mni.hbmpItem=(HBITMAP)LoadBitmap(hst,MAKEINTRESOURCE(IDB_74));
	b=SetMenuItemInfo(GetSubMenu(GetMenu(MainWnd),7),5,true,&mni);
	mni.hbmpItem=(HBITMAP)LoadBitmap(hst,MAKEINTRESOURCE(IDB_75));
	b=SetMenuItemInfo(GetSubMenu(GetMenu(MainWnd),8),0,true,&mni);
	mni.hbmpItem=(HBITMAP)LoadBitmap(hst,MAKEINTRESOURCE(IDB_76));
	b=SetMenuItemInfo(GetSubMenu(GetMenu(MainWnd),2),4,true,&mni);
	mni.hbmpItem=(HBITMAP)LoadBitmap(hst,MAKEINTRESOURCE(IDB_77));
	b=SetMenuItemInfo(GetSubMenu(GetMenu(MainWnd),2),5,true,&mni);

	Panel=CreateWindow("SysTreeView32","Panel",WS_CHILD|WS_VISIBLE|TVS_HASBUTTONS|TVS_HASLINES|TVS_SINGLEEXPAND,1005,1,MAX_X-1025,MAX_Y-66,MainWnd,NULL,hst,0);
	TreeView_SetBkColor(Panel,RGB(173,245,188));
	TreeView_SetTextColor(Panel,RGB(166,60,181));
	TreeView_SetItemHeight(Panel,48);
	ImgL=ImageList_Create(42,42,ILC_COLOR32,0,0);
	if(ImgL==NULL) i= GetLastError();
	for(i=IDB_18;i<=IDB_56;i++)
	{
		ImageList_Add(ImgL,LoadBitmap(hst,MAKEINTRESOURCE(i)),NULL);

	}
	tv_item.hItem=TVI_LAST;
	tv_item.mask=TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	tv_str.hParent=TVI_ROOT;
	for(i=0;i<5;i++)
	{
		tv_item.pszText=Funkcje[i];
		tv_item.iImage=i;
		tv_item.iSelectedImage=i;
		tv_str.item=tv_item;
		H_tri[i]=TreeView_InsertItem(Panel,&tv_str);
	}
	TreeView_SetImageList(Panel,ImgL,ILS_NORMAL);
	for (i=0;i<33;i++)
	{
		tv_str.hParent=H_tri[item[i]];
		tv_item.pszText=FunkcjeTow[i];
		tv_item.iImage=i+6;
		tv_item.iSelectedImage=i+6;
		tv_str.item=tv_item;
		H_f[i]=TreeView_InsertItem(Panel,&tv_str);
	}
	return true;
}

	//Funkcja obs³uguj¹ca okna gdzie podaje siê wartoœci u³amkowe

LRESULT _stdcall WndEProc (HWND hwd, int code, WPARAM wp , LPARAM lp)
{
	char zn;
	static char zn1[50];
	static bool bl;
	int i;
	WORD w;

	switch(code)
	{
		case WM_CHAR:
			{
				zn=(char)(LOWORD(wp));
				if(zn==',')
				{
					zn='.';
					w=HIWORD(wp);
					wp=MAKELONG((WORD)zn,w);
				}
				memset(zn1,0,25);
				GetWindowText(hwd,zn1,50);
				SetProp(hwd,"BOOL",(HANDLE)false);
				for(i=0;i<strlen(zn1);i++)
				{
					if(zn1[i]=='.')
					{
						SetProp(hwd,"BOOL",(HANDLE)true);
						break;
					}
				}
				if(zn==8)
				{
					if(zn1[strlen(zn1)-1]=='.')
					{
						SetProp(hwd,"BOOL",(HANDLE)false);
					}
					return CallWindowProc((WNDPROC)GetProp(hwd,"PROC"),hwd,WM_CHAR,wp,lp);
					
				}
				if((zn>='0')&&(zn<='9')) 
				{
					if((zn1[0]=='0')&&(zn1[1]==0)) break;
					return CallWindowProc((WNDPROC)GetProp(hwd,"PROC"),hwd,WM_CHAR,wp,lp);
				}
				else
				{
					if((zn=='.')&&(zn1[0]!=0))
					{
						bl=(bool)GetProp(hwd,"BOOL");
						if(!bl)
						{
							SetProp(hwd,"BOOL",(HANDLE)true);
							return CallWindowProc((WNDPROC)GetProp(hwd,"PROC"),hwd,WM_CHAR,wp,lp);
						}
					}
					break;
				}

			}
		
			case WM_KEYUP:
				{
					break;
				}
		default: 
			{
				return CallWindowProc((WNDPROC)GetProp(hwd,"PROC"),hwd,code,wp,lp);
								
			}
	}
	return 0;
}


	//Funkcja okna dialogowego do dodawania artykulow

INT_PTR CALLBACK DlgProc1(HWND wnd, int code, WPARAM wp, LPARAM lp)
{
	HWND h,h1;
	int i,j,k,l;
	char zn[350],zn1[350],txt[350];
	LPSTR LPS;
	static char C_Tow[50],Marza[50],_Vat[50],Netto[50],Brutto[50];
	static double cena,marza,netto,vat,brutto,x;
	SIZE size;
	Artykuly art;
	static Artykuly *artk;
	static bool bl1,bl2,bl3;
	bool bl;
	Prz_Tow przt;
	SYSTEMTIME st;

	switch (code)
	{
		case WM_INITDIALOG:
			{	
				bl1=false;
				bl2=false;
				bl3=false;
				is_dlg1=true;
				Dlg1=wnd;
				h=GetDlgItem(wnd,DLG1_E4);
				h1=GetDlgItem(wnd,DLG1_E14);
				memset(C_Tow,0,50);
				memset(Marza,0,50);
				memset(_Vat,0,50);
				memset(Netto,0,50);
				memset(Brutto,0,50);
				for(i=0;i<cnt.jmcnt;i++)
				{
					memset(zn,0,350);
					sprintf(zn,"%s (%s)",jm[i].naz,jm[i].znak);
					SendMessage(h,CB_ADDSTRING,0,(LPARAM)zn);
				}
				for(i=0;i<cnt.grcnt;i++)
				{
					
					SendMessage(h1,CB_ADDSTRING,0,(LPARAM)GR[i].nazwa);
				}
				for(i=0;i<cnt.vatcnt;i++)
				{
					memset(zn,0,350);
					sprintf(zn,"%0.2f",Vat[i].vat);
					SendMessage(GetDlgItem(wnd,DLG1_E8),CB_ADDSTRING,0,(LPARAM)zn);
				}
				SendMessage(h,CB_SETCURSEL,(WPARAM)cnt.def_jm,0);
				SendMessage(h1,CB_SETCURSEL,(WPARAM)cnt.def_gr,0);
				SendMessage(GetDlgItem(wnd,DLG1_E8),CB_SETCURSEL,(WPARAM)cnt.def_vat,0);
				if(!is_edit)
				{
					if(HD_A.count==0)
					{
						SetWindowText(GetDlgItem(wnd,DLG1_E12),"1");
					}else
					{
						l=0;
						for(i=0;i<HD_A.count;i++)
						{
							if(is_num(ART[i].KOD_TOW,strlen(ART[i].KOD_TOW)))
							{
								k=atoi(ART[i].KOD_TOW);
								if(k>l)l=k;
							}
						}
						if(l!=0)
						{
							memset(zn,0,350);
							itoa(l+1,zn,10);
							SetWindowText(GetDlgItem(wnd,DLG1_E12),zn);
						}
					}
				}
				if(is_edit)
				{
					bl1=bl2=bl3=true;
					artk=ART+Aid;
					SetWindowText(GetDlgItem(wnd,DLG1_E1),artk->Nazwa);
					SetWindowText(GetDlgItem(wnd,DLG1_E2),artk->Producent);
					memset(zn,0,350);
					dbl_str(artk->Stan,zn,2,350);
					SetWindowText(GetDlgItem(wnd,DLG1_E3),zn);
					memset(zn,0,350);
					sprintf(zn,"(%s)",artk->JM);
					SetWindowText(GetDlgItem(wnd,DLG1_E4),zn);
					memset(zn,0,350);
					itoa(artk->Stan_Kr,zn,10);
					SetWindowText(GetDlgItem(wnd,DLG1_E10),zn);
					memset(zn,0,350);
					dbl_str(artk->Cena_Zakupu,zn,2,350);
					SetWindowText(GetDlgItem(wnd,DLG1_E5),zn);
					memset(zn,0,350);
					dbl_str(artk->Marza,zn,2,350);
					SetWindowText(GetDlgItem(wnd,DLG1_E6),zn);
					memset(zn,0,350);
					dbl_str(artk->Cena_Netto,zn,2,350);
					SetWindowText(GetDlgItem(wnd,DLG1_E7),zn);
					memset(zn,0,350);
					dbl_str(artk->VAT,zn,2,350);
					SetWindowText(GetDlgItem(wnd,DLG1_E8),zn);
					memset(zn,0,350);
					dbl_str(artk->Cena_Brutto,zn,2,350);
					SetWindowText(GetDlgItem(wnd,DLG1_E9),zn);
					SetWindowText(GetDlgItem(wnd,DLG1_E12),artk->KOD_TOW);
					SetWindowText(GetDlgItem(wnd,DLG1_E13),artk->KOD_KR);
					EnableWindow(GetDlgItem(wnd,DLG1_E12),false);
					SetWindowText(GetDlgItem(wnd,DLG1_E14),artk->Grupa);
					if(artk->is_blok)CheckDlgButton(wnd,DLG1_C4,true);else CheckDlgButton(wnd,DLG1_C4,false);
					if(artk->is_cena)CheckDlgButton(wnd,DLG1_C2,true);else CheckDlgButton(wnd,DLG1_C2,false);
					if(artk->is_list)CheckDlgButton(wnd,DLG1_C3,true);else CheckDlgButton(wnd,DLG1_C3,false);
					if(artk->is_op)CheckDlgButton(wnd,DLG1_C5,true);else CheckDlgButton(wnd,DLG1_C5,false);
					if(artk->is_wylznr)CheckDlgButton(wnd,DLG1_C1,true);else CheckDlgButton(wnd,DLG1_C1,false);
					if(artk->Num_Fakt[0]!=0) SetWindowText(GetDlgItem(wnd,DLG1_E15),artk->Num_Fakt);
				}
				memset(zn,0,350);
				sprintf(zn,"%s(%s)",wal[cnt.def_wal].naz,wal[cnt.def_wal].znak);
				SetWindowText(GetDlgItem(wnd,DLG1_T13),zn);
				SetWindowText(GetDlgItem(wnd,DLG1_T14),zn);
				SetWindowText(GetDlgItem(wnd,DLG1_T15),zn);
				SetWindowText(GetDlgItem(wnd,DLG1_T16),zn);
				SetWindowText(GetDlgItem(wnd,DLG1_T17),zn);
				SetProp(GetDlgItem(wnd,DLG1_E5),"PROC",(HANDLE)GetWindowLong(GetDlgItem(wnd,DLG1_E5),GWL_WNDPROC));
				SetProp(GetDlgItem(wnd,DLG1_E5),"BOOL",(HANDLE)false);
				SetWindowLong(GetDlgItem(wnd,DLG1_E5),GWL_WNDPROC,(LONG)WndEProc);
				SetProp(GetDlgItem(wnd,DLG1_E6),"PROC",(HANDLE)GetWindowLong(GetDlgItem(wnd,DLG1_E6),GWL_WNDPROC));
				SetProp(GetDlgItem(wnd,DLG1_E6),"BOOL",(HANDLE)false);
				SetWindowLong(GetDlgItem(wnd,DLG1_E6),GWL_WNDPROC,(LONG)WndEProc);
				SetProp(GetDlgItem(wnd,DLG1_E8),"PROC",(HANDLE)GetWindowLong(GetDlgItem(wnd,DLG1_E8),GWL_WNDPROC));
				SetProp(GetDlgItem(wnd,DLG1_E8),"BOOL",(HANDLE)false);
				SetWindowLong(GetDlgItem(wnd,DLG1_E8),GWL_WNDPROC,(LONG)WndEProc);
				SetProp(GetDlgItem(wnd,DLG1_E7),"PROC",(HANDLE)GetWindowLong(GetDlgItem(wnd,DLG1_E7),GWL_WNDPROC));
				SetProp(GetDlgItem(wnd,DLG1_E7),"BOOL",(HANDLE)false);
				SetWindowLong(GetDlgItem(wnd,DLG1_E7),GWL_WNDPROC,(LONG)WndEProc);
				SetProp(GetDlgItem(wnd,DLG1_E9),"PROC",(HANDLE)GetWindowLong(GetDlgItem(wnd,DLG1_E9),GWL_WNDPROC));
				SetProp(GetDlgItem(wnd,DLG1_E9),"BOOL",(HANDLE)false);
				SetWindowLong(GetDlgItem(wnd,DLG1_E9),GWL_WNDPROC,(LONG)WndEProc);
				SetProp(GetDlgItem(wnd,DLG1_E3),"PROC",(HANDLE)GetWindowLong(GetDlgItem(wnd,DLG1_E3),GWL_WNDPROC));
				SetProp(GetDlgItem(wnd,DLG1_E3),"BOOL",(HANDLE)false);
				SetWindowLong(GetDlgItem(wnd,DLG1_E3),GWL_WNDPROC,(LONG)WndEProc);
				bl1=bl2=bl3=false;
				break;
			}
		
		case WM_CLOSE:
			{
				DestroyWindow(wnd);
				break;
			}
		case WM_DESTROY:
			{
				is_dlg1=false;
				Dlg1=NULL;
				EndDialog(wnd,0);
				break;
				//PostQuitMessage(0);
			}
		case WM_COMMAND:
			{
				//Przycisk Anuluj

				if(LOWORD(wp)==DLG1_B1)
				{
					DestroyWindow(wnd);
					break;
				}

				//Zdarzenia pola ceny zakupu towaru

				if(LOWORD(wp)==DLG1_E5|| LOWORD(wp)==DLG1_E6 || LOWORD(wp)==DLG1_E7 || LOWORD(wp)==DLG1_E9 || LOWORD(wp)==DLG1_E8)
				{
					
					if(HIWORD(wp)==EN_CHANGE || HIWORD(wp)==CBN_SELENDOK ||  HIWORD(wp)==CBN_EDITCHANGE)
					{
					
						memset(C_Tow,0,50);
						memset(Marza,0,50);
						memset(Netto,0,50);
						memset(Brutto,0,50);
						GetWindowText(GetDlgItem(wnd,DLG1_E7),Netto,50);
						GetWindowText(GetDlgItem(wnd,DLG1_E9),Brutto,50);
						GetWindowText(GetDlgItem(wnd,DLG1_E5),C_Tow,50);
						GetWindowText(GetDlgItem(wnd,DLG1_E6),Marza,50);
						netto=atof(Netto);
						brutto=atof(Brutto);
						cena=atof(C_Tow);
						marza-atof(Marza);
						if(HIWORD(wp)==CBN_SELENDOK)
						{
							i=ComboBox_GetCurSel(GetDlgItem(wnd,DLG1_E8));
							vat=Vat[i].vat;
							bl3=true;
							if(Netto[0]!=0) 
							{
								netto=strtod(Netto,0);
								if(vat==0)brutto=netto;
								else
								{
									x=vat/100;
									x++;
									brutto=netto*x;
								}
								dbl_str(brutto,Brutto,2,50);
								bl1=true;
								SetWindowText(GetDlgItem(wnd,DLG1_E9),Brutto);
								bl1=false;
							}else SendMessage(wnd,WM_COMMAND,MAKELONG((WORD)DLG1_E9,(WORD)EN_CHANGE),0);
							break;
						}else 
						{	
							if(!bl3)
							{	
								memset(_Vat,0,50);
								GetWindowText(GetDlgItem(wnd,DLG1_E8),_Vat,50);
								if(_Vat[0]!=0) vat=strtod(_Vat,0); else vat=0;
							}
						}


						if(LOWORD(wp)==DLG1_E7 || LOWORD(wp)==DLG1_E9)
						{
							if(bl2 || bl1) break;
							bl1=true;
							bl3=false;
						
							if(Netto[0]==0 && Brutto[0]==0)
							{
								bl1=false;
								break;
							}

							if(LOWORD(wp)==DLG1_E7)
							{	
								netto=strtod(Netto,0);
								if(vat==0)brutto=netto;
								else
								{
									x=vat/100;
									x++;
									brutto=netto*x;
								}
								dbl_str(brutto,Brutto,2,50);
								SetWindowText(GetDlgItem(wnd,DLG1_E9),Brutto);
							}
							else if(LOWORD(wp)==DLG1_E9)
							{
								brutto=strtod(Brutto,0);
								if(vat==0)netto=brutto;
								else
								{
									x=vat/100;
									x++;
									netto=brutto/x;
								}
								dbl_str(netto,Netto,2,50);
								SetWindowText(GetDlgItem(wnd,DLG1_E7),Netto);
							}
							
							if(C_Tow[0]==0 && Marza[0]==0)
							{
								bl1=false;
								break;
							}
							if(C_Tow[0]!=0)
							{
								cena=strtod(C_Tow,0);
								if(cena>0)
								{
									x=(netto-cena)/cena;
									marza=x*100;

								}else marza=0;
								dbl_str(marza,Marza,2,50);
								SetWindowText(GetDlgItem(wnd,DLG1_E6),Marza);
							}
					
							bl1=false;
							break;
						}
						else
						{
							if(bl1) break;
							bl2=true;
							brutto=0;
							if(C_Tow[0]!=0) cena=strtod(C_Tow,0); else cena=0;
							if(cena>0)
							{
								if(LOWORD(wp)==DLG1_E5)
								{
									if(Netto[0]!=0)
									{
										netto=strtod(Netto,0);
										if(netto==0 && cena==0)marza=0;else marza= (netto/cena-1)*100; 
										
										dbl_str(marza,Marza,2,50);
										bl1=true;
										SetWindowText(GetDlgItem(wnd,DLG1_E6),Marza);
										bl1=false;
									} 
									
									bl2=false;
									break;
									
								}else if(LOWORD(wp)==DLG1_E6)
								{
									marza=atof(Marza);
									netto=(marza/100+1)*cena;
									dbl_str(netto,Netto,2,50);
									SetWindowText(GetDlgItem(wnd,DLG1_E7),Netto);
								}
							
								if(vat>=0 && netto>0)
								{
									if(vat==0) brutto=netto;
									else
									{
										brutto=(netto/100)*vat;
										brutto=brutto+netto;
									}
									dbl_str(brutto,Brutto,2,50);
									SetWindowText(GetDlgItem(wnd,DLG1_E9),Brutto);
								}
						
							}else 
							{
								marza=0;
								dbl_str(marza,Marza,2,50);
								bl1=true;
								SetWindowText(GetDlgItem(wnd,DLG1_E6),Marza);
								bl1=false;
							}
							bl2=false;
						}
					}
					break;
				}

				//Przycisk dodania artyku³u

				if(wp==DLG1_B2)
				{
					if(!is_edit && HD_A.count==MAX_ART)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Dodano ju¿ maksymaln¹ iloœæ artyku³ów");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),wnd,(DLGPROC)&DLGIProc);
						SetFocus(wnd);
						break;
					}
					memset(&art,0,sizeof(art));
					memset(Marza,0,50);
					GetWindowText(GetDlgItem(wnd,DLG1_E6),Marza,50);
					if(Marza[0]==0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nale¿y podaæ mar¿ê lub wpisaæ 0");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),wnd,(DLGPROC)&DLGIProc);
						SetFocus(wnd);
						break;
					}
					memset(C_Tow,0,50);
					GetWindowText(GetDlgItem(wnd,DLG1_E5),C_Tow,50);
					if(C_Tow[0]==0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nale¿y podaæ  cenê towaru lub wpisaæ 0");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),wnd,(DLGPROC)&DLGIProc);
						SetFocus(wnd);
						break;
					}
					memset(Netto,0,50);
					GetWindowText(GetDlgItem(wnd,DLG1_E7),Netto,50);
					if(Netto[0]==0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nale¿y podaæ  cenê netto towaru lub wpisaæ 0");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),wnd,(DLGPROC)&DLGIProc);
						SetFocus(wnd);
						break;
					}

					memset(Brutto,0,50);
					GetWindowText(GetDlgItem(wnd,DLG1_E9),Brutto,50);
					if(Brutto[0]==0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nale¿y podaæ  cenê brutto lub wpisaæ 0");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),wnd,(DLGPROC)&DLGIProc);
						SetFocus(wnd);
						break;
					}
					GetWindowText(GetDlgItem(wnd,DLG1_E1),art.Nazwa,350);
					if(art.Nazwa[0]==0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nale¿y podaæ nazwê towaru");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),wnd,(DLGPROC)&DLGIProc);
						SetFocus(wnd);
						break;
					}
					GetWindowText(GetDlgItem(wnd,DLG1_E14),art.Grupa,50);
					if(art.Grupa[0]==0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nale¿y podaæ nazwê towaru");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),wnd,(DLGPROC)&DLGIProc);
						SetFocus(wnd);
						break;
					}
					GetWindowText(GetDlgItem(wnd,DLG1_E2),art.Producent,350);
					GetWindowText(GetDlgItem(wnd,DLG1_E12),art.KOD_TOW,35);
					GetWindowText(GetDlgItem(wnd,DLG1_E15),art.Num_Fakt,35);
					if(!is_edit && art.KOD_TOW[0]!=0)
					{
						bl=true;
						for(i=0;i<HD_A.count;i++)
						{
							if(strcmp(ART[i].KOD_TOW,art.KOD_TOW)==0)
							{
								memset(Err_Text,0,350);
								sprintf(Err_Text,"Towar o takim kodzie ju¿ istnieje");
								DialogBox(hst,MAKEINTRESOURCE(DLG_I),wnd,(DLGPROC)&DLGIProc);
								SetFocus(wnd);
								bl=false;
								break;
							}
						}
						if(!bl) break;
					}
					GetWindowText(GetDlgItem(wnd,DLG1_E13),art.KOD_KR,35);
					if(strlen(art.KOD_KR)!=13 && art.KOD_KR[0]!=0)
					{
						memset(Query_Text,0,350);
						sprintf(Query_Text,"Kod kreskowy powinien zawieraæ 13 cyfr\n Czy chcesz kontynuowaæ ?");
						DialogBox(hst,MAKEINTRESOURCE(DLG_Q),wnd,(DLGPROC)&DLGQProc);
						SetFocus(wnd);
						if(!is_ok) break;
					}
					memset(zn,0,350);
					GetWindowText(GetDlgItem(wnd,DLG1_E3),zn,350);
					if(zn[0]==0)art.Stan=0; else art.Stan=atof(zn);
					memset(zn,0,350);
					GetWindowText(GetDlgItem(wnd,DLG1_E10),zn,350);
					if(zn[0]==0)art.Stan_Kr=0; else art.Stan_Kr=atoi(zn);
					memset(zn,0,350);
					GetWindowText(GetDlgItem(wnd,DLG1_E5),zn,350);
					if(zn[0]==0)art.Cena_Zakupu=0; else art.Cena_Zakupu=atof(zn);
					memset(zn,0,350);
					GetWindowText(GetDlgItem(wnd,DLG1_E6),zn,350);
					if(zn[0]==0)art.Marza=0; else art.Marza=atof(zn);
					memset(zn,0,350);
					GetWindowText(GetDlgItem(wnd,DLG1_E7),zn,350);
					if(zn[0]==0)art.Cena_Netto=0; else art.Cena_Netto=atof(zn);
					memset(zn,0,350);
					GetWindowText(GetDlgItem(wnd,DLG1_E8),zn,350);
					if(zn[0]==0)art.VAT=0; else art.VAT=atof(zn);
					memset(zn,0,350);
					GetWindowText(GetDlgItem(wnd,DLG1_E9),zn,350);
					if(zn[0]==0)art.Cena_Brutto=0; else art.Cena_Brutto=atof(zn);
					memset(zn,0,350);
					GetWindowText(GetDlgItem(wnd,DLG1_E4),zn,350);
					if(IsDlgButtonChecked(wnd,DLG1_C1)) art.is_wylznr=true; else art.is_wylznr=false;
					if(IsDlgButtonChecked(wnd,DLG1_C2)) art.is_cena=true; else art.is_cena=false;
					if(IsDlgButtonChecked(wnd,DLG1_C3)) art.is_list=true; else art.is_list=false;
					if(IsDlgButtonChecked(wnd,DLG1_C4)) art.is_blok=true; else art.is_blok=false;
					if(IsDlgButtonChecked(wnd,DLG1_C5)) art.is_op=true; else art.is_op=false;
					LPS=zn;
					LPS=strstr(zn,"(");
					if(LPS==NULL) strncpy(art.JM,zn,10);
					else
					{
						memset(zn1,0,350);
						strncpy(zn1,LPS+1,strlen(LPS)-2);
						strncpy(art.JM,zn1,10);
					}
					if(is_edit)
					{
						art.IDA=ART[Aid].IDA;
						art.indeks=ART[Aid].indeks;
					}else art.IDA=HD_A.LastID+1;
					art.IDP=idp;
					art.exist=true;
				
					if(is_edit)
					{
						memcpy(artk,&art,sizeof(Artykuly));
						Save_AR(&art);
						memset(Query_Text,0,350);
						sprintf(Query_Text,"Uaktualniono artyku³\n Czy chcesz wprowadziæ zmiany do kasy fiskalnej ?");
						DialogBox(hst,MAKEINTRESOURCE(DLG_Q),wnd,(DLGPROC)&DLGQProc);
						SetFocus(wnd);
						if(is_ok)
						{
							memset(kod_tow,0,35);
							strcpy(kod_tow,art.KOD_TOW);
							is_dlg1=true;
							is_show=true;
							is_tow=true;
							is_param=false;
							DialogBox(hst,MAKEINTRESOURCE(ID_DLG_23),wnd,(DLGPROC)&DLG23Proc);
							SetFocus(wnd);
							is_dlg1=false;
							if(is_tow)is_tow=false;
							else
							{
								is_tow=true;
								if(kod_tow[0]==0) is_param =true;
								DialogBox(hst,MAKEINTRESOURCE(ID_DLG_26),wnd,(DLGPROC)DLG26Proc);
								if(is_param) ecode=-3;
								if(ecode==0)
								{
									if(strcmp(TK.nazwa,art.Nazwa)!=0)
									{
										memset(Query_Text,0,350);
										sprintf(Query_Text,"Artyku³y maj¹ ró¿n¹ nazwê. Czy chcesz napewno zapisaæ zmiany w kasie fiskalnej?");
										DialogBox(hst,MAKEINTRESOURCE(DLG_Q),wnd,(DLGPROC)&DLGQProc);
										SetFocus(wnd);
										TK.cenab=art.Cena_Brutto;
										if(is_ok) 
										{
											memset(TK.nazwa,0,150);
											strcpy(TK.nazwa,art.Nazwa);
											bl=true;
										}else break;
										
									}

									TK.grupa=1;
									TK.vat=1;
									TK.jm=1;
									i=-1;
									bl=false;
									do
									{
										i++;
										if(strcmp(jmt[i].znak,art.JM)==0)
										{
											TK.jm=i+1;
											bl=true;
										}
									}while(jmt[i].znak[0]!=0 && strcmp(art.JM,jmt[i].znak)!=0);
									if(!bl)
									{
										memset(Err_Text,0,350);
										sprintf(Err_Text,"Podana jednostka miary nie jest zdefiniowana w kasie.\nW celu aktualizacji jednostek z kas¹ nale¿y wybraæ opcjê Konfiguracja kasy fiskalnej->Zapisanie jednostek miary, oraz klikn¹æ przycisk Zapisz.");
										DialogBox(hst,MAKEINTRESOURCE(DLG_I),wnd,(DLGPROC)&DLGIProc);
										SetFocus(wnd);

									}
									i=-1;
									bl=false;
									do
									{
										i++;
										if(strcmp(gr_t[i].nazwa,art.Grupa)==0)
										{
											TK.grupa=i+1;
											bl=true;
										}
									}while(gr_t[i].nazwa[0]!=0 && strcmp(art.Grupa,gr_t[i].nazwa)!=0);
									if(!bl)
									{
										memset(Err_Text,0,350);
										sprintf(Err_Text,"Podana grupa towarowa nie jest zdefiniowana w kasie.\nW celu aktualizacji grup towarowych z kas¹ nale¿y wybraæ opcjê Konfiguracja kasy fiskalnej->Zapisanie grup towarowych, oraz klikn¹æ przycisk Zapisz.");
										DialogBox(hst,MAKEINTRESOURCE(DLG_I),wnd,(DLGPROC)&DLGIProc);
										SetFocus(wnd);

									}
									i=-1;
									bl=false;
									do
									{
										i++;
										if(stv[i].vat==art.VAT)
										{
											TK.vat=i+1;
											bl=true;
										}
									}while(stv[i].vat!=-1 && stv[i].vat!=art.VAT);
									if(!bl)
									{
										memset(Err_Text,0,350);
										sprintf(Err_Text,"Podana stawka vat nie jest zdefiniowana w kasie.\nW celu aktualizacji stawek z kas¹ nale¿y wybraæ opcjê Konfiguracja kasy fiskalnej->Odczytanie stawek podatkowych, oraz klikn¹æ przycisk Zapisz stawki do bazy.");
										DialogBox(hst,MAKEINTRESOURCE(DLG_I),wnd,(DLGPROC)&DLGIProc);
										SetFocus(wnd);

									}

									memset(TK.kod_kr,0,35);
									strcpy(TK.kod_kr,art.KOD_KR);
									TK.cenab=art.Cena_Brutto;
									TK.is_bl=art.is_blok;
									TK.is_op=art.is_op;
									TK.is_wylzRN=art.is_wylznr;
									TK.list_podr=art.is_list;
									TK.wpr_cen=art.is_cena;
									if(art.KOD_KR[0]==0)
									{
										strcpy(TK.kod_kr,"0000000000000");
										strcpy(art.KOD_KR,"0000000000000");
									}else strcpy(TK.kod_kr,art.KOD_KR);
									is_zapT=true;
									DialogBox(hst,MAKEINTRESOURCE(ID_DLG_27),wnd,(DLGPROC)&DLG27Proc);
										
								}else if(ecode==-3)
								{
									memset(Query_Text,0,350);
									sprintf(Query_Text,"Artyku³ nie jest zdefiniowany w kasie fiskalnej czy chcesz go dodaæ?");
									DialogBox(hst,MAKEINTRESOURCE(DLG_Q),wnd,(DLGPROC)&DLGQProc);
									SetFocus(wnd);
									if(is_ok)
									{
										TK.grupa=1;
										TK.vat=1;
										TK.jm=1;
										i=-1;

										bl=false;
										do
										{
											i++;
											if(strcmp(jmt[i].znak,art.JM)==0)
											{
												TK.jm=i+1;
												bl=true;
											}
										}while(jmt[i].znak[0]!=0 && strcmp(art.JM,jmt[i].znak)!=0);
										if(!bl)
										{
											memset(Err_Text,0,350);
											sprintf(Err_Text,"Podana jednostka miary nie jest zdefiniowana w kasie.\nW celu aktualizacji jednostek z kas¹ nale¿y wybraæ opcjê Konfiguracja kasy fiskalnej->Zapisanie jednostek miary, oraz klikn¹æ przycisk Zapisz.");
											DialogBox(hst,MAKEINTRESOURCE(DLG_I),wnd,(DLGPROC)&DLGIProc);
											SetFocus(wnd);

										}
										i=-1;
										bl=false;
										do
										{
											i++;
											if(strcmp(gr_t[i].nazwa,art.Grupa)==0)
											{
												TK.grupa=i+1;
												bl=true;
											}
										}while(gr_t[i].nazwa[0]!=0 && strcmp(art.Grupa,gr_t[i].nazwa)!=0);
										if(!bl)
										{
											memset(Err_Text,0,350);
											sprintf(Err_Text,"Podana grupa towarowa nie jest zdefiniowana w kasie.\nW celu aktualizacji grup towarowych z kas¹ nale¿y wybraæ opcjê Konfiguracja kasy fiskalnej->Zapisanie grup towarowych, oraz klikn¹æ przycisk Zapisz.");
											DialogBox(hst,MAKEINTRESOURCE(DLG_I),wnd,(DLGPROC)&DLGIProc);
											SetFocus(wnd);

										}
										i=-1;
										bl=false;
										do
										{
											i++;
											if(stv[i].vat==art.VAT)
											{
												TK.vat=i+1;
												bl=true;
											}
										}while(stv[i].vat!=-1 && stv[i].vat!=art.VAT);
										if(!bl)
										{
											memset(Err_Text,0,350);
											sprintf(Err_Text,"Podana stawka vat nie jest zdefiniowana w kasie.\nW celu aktualizacji stawek z kas¹ nale¿y wybraæ opcjê Konfiguracja kasy fiskalnej->Odczytanie stawek podatkowych, oraz klikn¹æ przycisk Zapisz stawki do bazy.");
											DialogBox(hst,MAKEINTRESOURCE(DLG_I),wnd,(DLGPROC)&DLGIProc);
											SetFocus(wnd);

										}

										TK.mpp=3;
										memset(art.KOD_TOW,0,35);
										strcpy(art.KOD_TOW,TK.numer);
										if(art.KOD_KR[0]==0)
										{
											strcpy(TK.kod_kr,"0000000000000");
											strcpy(art.KOD_KR,"0000000000000");
										}else strcpy(TK.kod_kr,art.KOD_KR);
										bl=false;
										if(strcmp(TK.nazwa,art.Nazwa)!=0)
										{
											memset(TK.nazwa,0,150);
											strcpy(TK.nazwa,art.Nazwa);
										}
									
										TK.cenab=art.Cena_Brutto;
										TK.cenab=art.Cena_Brutto;
										TK.is_bl=art.is_blok;
										TK.is_op=art.is_op;
										TK.is_wylzRN=art.is_wylznr;
										TK.list_podr=art.is_list;
										TK.wpr_cen=art.is_cena;
										is_zapT=true;
										if(TK.numer[0]==0)
										{
											i=find_num(KS[Kas_id],&j,&l);
											memset(TK.numer,0,50);
											itoa(j,TK.numer,10);
											i=get_tow_kas(&TK_T,KS[Kas_id],TK.numer);
											if(i!=-3)
											{
												memset(ART[Aid].KOD_TOW,0,35);
												itoa(l+1,ART[Aid].KOD_TOW,10);
												itoa(l+1,TK.numer,10);
											}else
											{
												memset(ART[Aid].KOD_TOW,0,35);
												itoa(j,ART[Aid].KOD_TOW,10);
											}
											
										}
										DialogBox(hst,MAKEINTRESOURCE(ID_DLG_27),wnd,(DLGPROC)&DLG27Proc);
									}
								}
								
							}
						}
						SetFocus(wnd);
					}else
					{	
						if(art.Stan>0 && art.Cena_Zakupu>0)
						{
							GetSystemTime(&st);
							przt.cena_n=art.Stan*art.Cena_Zakupu;
							przt.miesiac=st.wMonth;
							przt.rok=st.wYear;
							Save_TW(przt,art.VAT);
						}else
						{
							memset(Query_Text,0,350);
							sprintf(Query_Text,"Jeœli nie podasz ceny lub stanu towaru to nie zostanie on uwzglêdniony w statystykach sprzeda¿y\nW celu aktualizacji statystyk mo¿esz pózniej wybraæ z menu Magazyn->Przyjêcie towaru lub wprowadziæ teraz potrzebne dane\nCzy chcesz kontyn³owaæ i pózniej zaktualizowaæ stan magazynowy ?");
							DialogBox(hst,MAKEINTRESOURCE(DLG_Q),wnd,(DLGPROC)&DLGQProc);
							SetFocus(wnd);
							if(!is_ok) break;
						}
						Dodaj_AR(&art);
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Dodano nowy artyku³");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),wnd,(DLGPROC)&DLGIProc);
						SetFocus(wnd);
						memset(Query_Text,0,350);
						sprintf(Query_Text,"Czy chcesz wprowadziæ towar do kasy fiskalnej ?");
						DialogBox(hst,MAKEINTRESOURCE(DLG_Q),wnd,(DLGPROC)&DLGQProc);
						SetFocus(wnd);
						if(is_ok)
						{
							memset(kod_tow,0,35);
							strcpy(kod_tow,art.KOD_TOW);
							if(kod_tow[0]==0)kod_tow[0]='1';
							is_dlg1=true;
							is_show=true;
							is_tow=true;
							DialogBox(hst,MAKEINTRESOURCE(ID_DLG_23),wnd,(DLGPROC)&DLG23Proc);
							SetFocus(wnd);
							is_dlg1=false;
							if(is_tow)is_tow=false;
							else
							{
								is_tow=true;
								is_param=false;
								DialogBox(hst,MAKEINTRESOURCE(ID_DLG_26),wnd,(DLGPROC)DLG26Proc);	
								if(ecode==-3)
								{
									TK.grupa=1;
									TK.vat=1;
									TK.jm=1;
									i=-1;
									bl=false;
									do
									{
										i++;
										if(strcmp(jmt[i].znak,art.JM)==0)
										{
											TK.jm=i+1;
											bl=true;
										}
									}while(jmt[i].znak[0]!=0 && strcmp(art.JM,jmt[i].znak)!=0);
									if(!bl)
									{
										memset(Err_Text,0,350);
										sprintf(Err_Text,"Podana jednostka miary nie jest zdefiniowana w kasie.\nW celu aktualizacji jednostek z kas¹ nale¿y wybraæ opcjê Konfiguracja kasy fiskalnej->Zapisanie jednostek miary, oraz klikn¹æ przycisk Zapisz.");
										DialogBox(hst,MAKEINTRESOURCE(DLG_I),wnd,(DLGPROC)&DLGIProc);
										SetFocus(wnd);

									}
									i=-1;
									bl=false;
									do
									{
										i++;
										if(strcmp(gr_t[i].nazwa,art.Grupa)==0)
										{
											TK.grupa=i+1;
											bl=true;
										}
									}while(gr_t[i].nazwa[0]!=0 && strcmp(art.Grupa,gr_t[i].nazwa)!=0);
									if(!bl)
									{
										memset(Err_Text,0,350);
										sprintf(Err_Text,"Podana grupa towarowa nie jest zdefiniowana w kasie.\nW celu aktualizacji grup towarowych z kas¹ nale¿y wybraæ opcjê Konfiguracja kasy fiskalnej->Zapisanie grup towarowych, oraz klikn¹æ przycisk Zapisz.");
										DialogBox(hst,MAKEINTRESOURCE(DLG_I),wnd,(DLGPROC)&DLGIProc);
										SetFocus(wnd);

									}
									i=-1;
									bl=false;
									do
										{
											i++;
											if(stv[i].vat==art.VAT)
											{
												TK.vat=i+1;
												bl=true;
											}
										}while(stv[i].vat!=-1 && stv[i].vat!=art.VAT);
									if(!bl)
									{
										memset(Err_Text,0,350);
										sprintf(Err_Text,"Podana stawka vat nie jest zdefiniowana w kasie.\nW celu aktualizacji stawek podatkowych z kas¹ nale¿y wybraæ opcjê Konfiguracja kasy fiskalnej->Odczytanie stawek podatkowych, oraz klikn¹æ przycisk Zapisz stawki do bazy.");
										DialogBox(hst,MAKEINTRESOURCE(DLG_I),wnd,(DLGPROC)&DLGIProc);
										SetFocus(wnd);

									}
									TK.mpp=3;
									memset(ART[HD_A.count-1].KOD_TOW,0,35);
									strcpy(ART[HD_A.count-1].KOD_TOW,TK.numer);
									if(ART[HD_A.count].KOD_KR[0]==0)
									{
										strcpy(TK.kod_kr,"0000000000000");
										strcpy(ART[HD_A.count-1].KOD_KR,"0000000000000");
									}else strcpy(TK.kod_kr,ART[HD_A.count-1].KOD_KR);
									
									bl=false;
									if(strcmp(TK.nazwa,art.Nazwa)!=0)
									{
										memset(TK.nazwa,0,150);
										strcpy(TK.nazwa,art.Nazwa);
									}
									
									TK.cenab=art.Cena_Brutto;
									//TK.vat=1;
									//TK.jm=1;
									//TK.grupa=1;
									TK.cenab=art.Cena_Brutto;
									TK.is_bl=art.is_blok;
									TK.is_op=art.is_op;
									TK.is_wylzRN=art.is_wylznr;
									TK.list_podr=art.is_list;
									TK.wpr_cen=art.is_cena;
									is_zapT=true;
									DialogBox(hst,MAKEINTRESOURCE(ID_DLG_27),wnd,(DLGPROC)&DLG27Proc);
								}
								else if (ecode==0)
								{
									
									memset(Query_Text,0,350);
									sprintf(Query_Text,"Pod podanym numerem jest ju¿ zdefiniowany towar\nProgram mo¿e wyszukaæ pierwszy wolny numer w kasie fiskalnej,\n Ale najpierw musisz zaktualizowaæ towary z kasy z baz¹ danych programu.\nCzy chcesz zapisaæ pod pierwszym wolnym numerem ?");
									DialogBox(hst,MAKEINTRESOURCE(DLG_Q),wnd,(DLGPROC)&DLGQProc);
									SetFocus(wnd);
									if(is_ok)
									{
										i=find_num(KS[Kas_id],&j, &l);
										memset(TK.numer,0,50);
										itoa(j,TK.numer,10);
										i=get_tow_kas(&TK_T,KS[Kas_id],TK.numer);
										if(i!=-3)
										{
											memset(ART[Aid].KOD_TOW,0,35);
											itoa(l+1,ART[Aid].KOD_TOW,10);
											itoa(l+1,TK.numer,10);
										}else
										{
											memset(ART[Aid].KOD_TOW,0,35);
											itoa(j,ART[Aid].KOD_TOW,10);
										}
											

										memset(ART[HD_A.count-1].KOD_TOW,0,35);
										strcpy(ART[HD_A.count-1].KOD_TOW,TK.numer);
										if(strcmp(TK.nazwa,art.Nazwa)!=0)
										{
											memset(TK.nazwa,0,150);
											strcpy(TK.nazwa,art.Nazwa);
										}
										TK.cenab=art.Cena_Brutto;

										if(ART[HD_A.count-1].KOD_KR[0]==0)
										{
											strcpy(TK.kod_kr,"0000000000000");
											strcpy(ART[HD_A.count-1].KOD_KR,"0000000000000");
										}else strcpy(TK.kod_kr,ART[HD_A.count-1].KOD_KR);

										TK.vat=1;
										TK.jm=1;
										TK.grupa=1;
										i=-1;

										bl=false;
										do
										{
											i++;
											if(strcmp(jmt[i].znak,art.JM)==0)
											{
												TK.jm=i+1;
												bl=true;
											}
										}while(jmt[i].znak[0]!=0 && strcmp(art.JM,jmt[i].znak)!=0);
										if(!bl)
										{
											memset(Err_Text,0,350);
											sprintf(Err_Text,"Podana jednostka miary nie jest zdefiniowana w kasie.\nW celu aktualizacji jednostek z kas¹ nale¿y wybraæ opcjê Konfiguracja kasy fiskalnej->Zapisanie jednostek miary, oraz klikn¹æ przycisk Zapisz.");
											DialogBox(hst,MAKEINTRESOURCE(DLG_I),wnd,(DLGPROC)&DLGIProc);
											SetFocus(wnd);

										}
										i=-1;
										bl=false;
										do
										{
											i++;
											if(strcmp(gr_t[i].nazwa,art.Grupa)==0)
											{
												TK.grupa=i+1;
												bl=true;
											}
										}while(gr_t[i].nazwa[0]!=0 && strcmp(art.Grupa,gr_t[i].nazwa)!=0);
										if(!bl)
										{
											memset(Err_Text,0,350);
											sprintf(Err_Text,"Podana grupa towarowa nie jest zdefiniowana w kasie.\nW celu aktualizacji grup towarowych z kas¹ nale¿y wybraæ opcjê Konfiguracja kasy fiskalnej->Zapisanie grup towarowych, oraz klikn¹æ przycisk Zapisz.");
											DialogBox(hst,MAKEINTRESOURCE(DLG_I),wnd,(DLGPROC)&DLGIProc);
											SetFocus(wnd);

										}
										i=-1;
										bl=false;
										do
										{
											i++;
											if(stv[i].vat==art.VAT)
											{
												TK.vat=i+1;
												bl=true;
											}
										}while(stv[i].vat!=-1 && stv[i].vat!=art.VAT);
										if(!bl)
										{
											memset(Err_Text,0,350);
											sprintf(Err_Text,"Podana stawka vat nie jest zdefiniowana w kasie.\nW celu aktualizacji stawek z kas¹ nale¿y wybraæ opcjê Konfiguracja kasy fiskalnej->Odczytanie stawek podatkowych, oraz klikn¹æ przycisk Zapisz stawki do bazy.");
											DialogBox(hst,MAKEINTRESOURCE(DLG_I),wnd,(DLGPROC)&DLGIProc);
											SetFocus(wnd);

										}


										TK.cenab=art.Cena_Brutto;
										TK.is_bl=art.is_blok;
										TK.is_op=art.is_op;
										TK.is_wylzRN=art.is_wylznr;
										TK.list_podr=art.is_list;
										TK.wpr_cen=art.is_cena;
										is_zapT=true;
										i=get_tow_kas(&TK_T,KS[Kas_id],TK.numer);
										if(i!=-3)
										{
											memset(TK.numer,0,50);
											memset(ART[HD_A.count-1].KOD_TOW,0,35);
											itoa(l+1,ART[HD_A.count-1].KOD_TOW,10);
											itoa(l+1,TK.numer,10);
										}
										DialogBox(hst,MAKEINTRESOURCE(ID_DLG_27),wnd,(DLGPROC)&DLG27Proc);
									}
								}
							}
						}
					}
					DestroyWindow(wnd);
					SendMessage(MainWnd,WM_COMMAND,(WPARAM)ID_B_Szuk,0);

				}

				//Przycisk Wyboru dostawcy

				if(wp==DLG1_B3)
				{
					is_zarz=false;
					DialogBox(hst,MAKEINTRESOURCE(ID_DLG_2),wnd,(DLGPROC)&DlgProc2);
					SetFocus(wnd);
					if(idp!=-1)
					{
						for(i=0;i<HD_P.count;i++)
						{
							if(PR[i].IDP==idp)
							{
								memset(zn,0,350);
								strcpy(zn,PR[i].Nazwa);
								SetWindowText(GetDlgItem(wnd,DLG1_E2),zn);

							}
						}
					}
					break;
				}
				break;
			}
		default:
			{
				return DefDlgProc(MainWnd,code,wp,lp);
			}
	}
	return 0;

};



	//Procedura obs³ugi okna dialogowego wyszukiwania dostawców

INT_PTR _stdcall DlgProc2(HWND hwd,int code, WPARAM wp, LPARAM lp)
{
	LVCOLUMN lvc;
	LVITEM lvi;
	int i,i1,i2;
	bool checked,is_valid;
	LPSTR LPS;
	char s_ch[350];

	switch(code)
	{
		
		case WM_INITDIALOG:
		{
			if(is_zarz)
			{
				ShowWindow(GetDlgItem(hwd,DLG2_B3),SW_HIDE);
				SetWindowText(GetDlgItem(hwd,DLG2_B4),"WyjdŸ");
			}
			t_id = new int[HD_P.count];
			idp=-1;
			Dlg2=hwd;
			is_dlg2=true;
			LV2=GetDlgItem(hwd,DLG2_LV1);
			ListView_SetExtendedListViewStyle(LV2,LVS_EX_FULLROWSELECT|LVS_EX_LABELTIP|LVS_EX_GRIDLINES|LVS_EX_ONECLICKACTIVATE);
			lvi.mask=LVIF_TEXT;//|LVIF_COLUMNS;
			for(i=0;i<9;i++)
			{
				lvc.mask=LVCF_TEXT|LVCF_WIDTH|LVCF_FMT;// | LVCF_SUBITEM;
				lvc.pszText=LV2_Col[i];
				lvc.cchTextMax=100;
				lvc.cx=LV2_Width[i];
				lvc.fmt=LVCFMT_LINE_BREAK|LVCFMT_LEFT;
				i1=SendMessage(LV2,LVM_INSERTCOLUMN,(WPARAM)i,(LPARAM)&lvc);
			}
			if(PR!=NULL&&HD_P.count>0)
			{
				lvi.mask=LVIF_TEXT;
				lvi.iSubItem=0;
				for(i=0;i<HD_P.count;i++)
				{
					lvi.iItem=i;
					lvi.cchTextMax=sizeof(Producent);
					lvi.pszText=PR[i].Nazwa; 
					i2=ListView_InsertItem(LV2,&lvi);
					t_id[i]=PR[i].IDP;
					for(i1=1;i1<9;i1++)
					{
						if(i1==1)LPS=PR[i].Kraj;else if(i1==2) LPS=PR[i].Miasto; else if(i1==3) LPS=PR[i].Adres; else if(i1==4)  LPS=PR[i].KodPocz;
						else if(i1==5)LPS=PR[i].Telefon;else if(i1==6)LPS=PR[i].Fax;else if(i1==7)LPS=PR[i].NIP;else if(i1==8)LPS=PR[i].REGON;
						ListView_SetItemText(LV2,i2,i1,LPS);
					}
					
				}
			}
			CheckDlgButton(hwd,DLG2_RB1,BST_CHECKED);
			checked=DLG2_RB1;
			break;
		}
		case WM_COMMAND:
			{
				//Przycisk edycji

				if(wp==DLG2_B9)
				{
					is_editp=true;
					i2=ListView_GetSelectionMark(LV2);
					if(i2<0) break;
					idp=t_id[i2];
					DialogBox(hst,MAKEINTRESOURCE(ID_DLG_3),hwd,(DLGPROC)&DlgProc3);
					SetFocus(hwd);
					is_editp=false;
					idp=-1;
					SendMessage(hwd,WM_COMMAND,DLG2_B2,0);
					break;
				}

				//Przycisk usuwania producenta

				if(wp==DLG2_B8)
				{
					memset(Query_Text,0,350);
					sprintf(Query_Text,"Czy napewno chcesz usun¹æ producenta ?");
					DialogBox(hst,MAKEINTRESOURCE(DLG_Q),hwd,(DLGPROC)&DLGQProc);
					SetFocus(hwd);
					if(is_ok)
					{
						i2=ListView_GetSelectionMark(LV2);
						if(i2<0) break;
						i2=t_id[i2];
						Us_PR(i2);
						SendMessage(hwd,WM_COMMAND,DLG2_B2,0);
					}
					break;
				}
				//Przycisk Szukaj
				
				if(wp==DLG2_B2)
				{
					if(t_id!=NULL)delete t_id;
					t_id=new int[HD_P.count];
					ListView_DeleteAllItems(LV2);
					memset(t_id,-1,HD_P.count);
					for(i=0;i<HD_P.count;i++)
					{
						is_valid=true;
						if(IsDlgButtonChecked(hwd,DLG2_RB1) && is_valid)
						{
							memset(s_ch,0,350);
							GetWindowText(GetDlgItem(hwd,DLG2_E1),s_ch,350);
							if(s_ch[0]!=0)
							{
								LPS=NULL;
								LPS=strstr(PR[i].Nazwa,s_ch);
								if(LPS==NULL) is_valid=false;
							}
						
						}
						if(IsDlgButtonChecked(hwd,DLG2_RB2) && is_valid)
						{
							memset(s_ch,0,350);
							GetWindowText(GetDlgItem(hwd,DLG2_E2),s_ch,350);
							if(s_ch[0]!=0)
							{
								LPS=NULL;
								LPS=strstr(PR[i].NIP,s_ch);
								if(LPS==NULL)  is_valid=false;

							}
						}
						if(IsDlgButtonChecked(hwd,DLG2_RB3) && is_valid)
						{
							memset(s_ch,0,350);
							GetWindowText(GetDlgItem(hwd,DLG2_E3),s_ch,350);
							if(s_ch[0]!=0)
							{
								LPS=NULL;
								LPS=strstr(PR[i].REGON,s_ch);
								if(LPS==NULL)  is_valid=false;
							}
						}
						if(IsDlgButtonChecked(hwd,DLG2_RB4) && is_valid)
						{
							memset(s_ch,0,350);
							GetWindowText(GetDlgItem(hwd,DLG2_E4),s_ch,350);
							if(s_ch[0]!=0)
							{
								LPS=NULL;
								LPS=strstr(PR[i].Kraj,s_ch);
								if(LPS==NULL)  is_valid=false;
							}
							if(is_valid)
							{
								memset(s_ch,0,350);
								GetWindowText(GetDlgItem(hwd,DLG2_E5),s_ch,350);
								if(s_ch[0]!=0)
								{
									
									LPS=NULL;
									LPS=strstr(PR[i].Miasto,s_ch);
									if(LPS==NULL)  is_valid=false;
								}
							}
							if(is_valid)
							{
								memset(s_ch,0,350);
								GetWindowText(GetDlgItem(hwd,DLG2_E6),s_ch,350);
								s_ch[strlen(s_ch)]='-';
								GetWindowText(GetDlgItem(hwd,DLG2_E7),s_ch+strlen(s_ch),350);
								if(strlen(s_ch)>1)
								{
									
									LPS=NULL;
									LPS=strstr(PR[i].KodPocz,s_ch);
									if(LPS==NULL)  is_valid=false;
								}
							}
							
						}
						if(is_valid)
						{
							lvi.mask=LVIF_TEXT;
							lvi.iSubItem=0;
							lvi.iItem=i;
							lvi.cchTextMax=sizeof(Producent);
							lvi.pszText=PR[i].Nazwa; 
							i2=ListView_InsertItem(LV2,&lvi);
							t_id[i2]=PR[i].IDP;
							for(i1=1;i1<9;i1++)
							{
								if(i1==1)LPS=PR[i].Kraj;else if(i1==2) LPS=PR[i].Miasto; else if(i1==3) LPS=PR[i].Adres; else if(i1==4)  LPS=PR[i].KodPocz;
								else if(i1==5)LPS=PR[i].Telefon;else if(i1==6)LPS=PR[i].Fax;else if(i1==7)LPS=PR[i].NIP;else if(i1==8)LPS=PR[i].REGON;
								ListView_SetItemText(LV2,i2,i1,LPS);
							}
						}

					}

					break;
				}

				//Przycisk Dodaj

				if(wp==DLG2_B3)
				{
					i=ListView_GetSelectionMark(LV2);
					if(i>=0)
					{
						idp=t_id[i];
						DestroyWindow(hwd);
					}else 
						{
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Nie wybrano ¿adnego dostawcy");
							DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
							SetFocus(hwd);
						}
					break;
				}

				//Przycisk Anuluj

				if(wp==DLG2_B4)
				{
					
					DestroyWindow(hwd);
					break;
				}

				//Radiobutton NAZWA
				if(wp==DLG2_RB1)
				{
					checked=IsDlgButtonChecked(hwd,DLG2_RB1);
					if(!checked)CheckDlgButton(hwd,DLG2_RB1,BST_CHECKED); else CheckDlgButton(hwd,DLG2_RB1,BST_UNCHECKED);
					EnableWindow(GetDlgItem(hwd,DLG2_E1),!checked);
				}
				//Radiobutton NIP
				if(wp==DLG2_RB2)
				{
					checked=IsDlgButtonChecked(hwd,DLG2_RB2);
					if(!checked)CheckDlgButton(hwd,DLG2_RB2,BST_CHECKED); else CheckDlgButton(hwd,DLG2_RB2,BST_UNCHECKED);
					EnableWindow(GetDlgItem(hwd,DLG2_E2),!checked);
					

				}
				//Radiobutton REGON
				if(wp==DLG2_RB3)
				{
					checked=IsDlgButtonChecked(hwd,DLG2_RB3);
					if(!checked)CheckDlgButton(hwd,DLG2_RB3,BST_CHECKED); else CheckDlgButton(hwd,DLG2_RB3,BST_UNCHECKED);
					EnableWindow(GetDlgItem(hwd,DLG2_E3),!checked);
				}
				//Radiobutton ADRES
				if(wp==DLG2_RB4)
				{
					checked=IsDlgButtonChecked(hwd,DLG2_RB4);
					if(!checked)CheckDlgButton(hwd,DLG2_RB4,BST_CHECKED); else CheckDlgButton(hwd,DLG2_RB4,BST_UNCHECKED);
					EnableWindow(GetDlgItem(hwd,DLG2_E4),!checked);
					EnableWindow(GetDlgItem(hwd,DLG2_E5),!checked);
					EnableWindow(GetDlgItem(hwd,DLG2_E6),!checked);
					EnableWindow(GetDlgItem(hwd,DLG2_E7),!checked);
				}

				//Przycisk dodania nowego dostawcy

				if(wp==DLG2_B7)
				{
					is_editp=false;
					DialogBox(hst,MAKEINTRESOURCE(ID_DLG_3),hwd,(DLGPROC)&DlgProc3);
					SetFocus(hwd);
					SendMessage(hwd,WM_COMMAND,DLG2_B2,0);
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
				if(t_id!=NULL) delete t_id;
				is_dlg2=false;
				EndDialog(hwd,0);
				//PostQuitMessage(0);
				break;
			}
		default:
			{
				return DefDlgProc(GetParent(hwd),code,wp,lp);
			}
	}
	return 0;
}


	//Procedura obs³ugi okna dialogowego dodawania nowych dostawców

INT_PTR _stdcall DlgProc3(HWND hwd,int code, WPARAM wp, LPARAM lp)
{
	int i,i1,j;
	static char naz_k[200];
	static bool val;
	int *ptv;
	LPSTR naz;
	char *adr;
	char adres[350], kraj[250];
	PAINTSTRUCT lppaint;
	HDC hdc;
	HPEN hpn;
	RECT rc;
	LPPOINT pt;
	Producent prd;
	switch(code)
	{
		case WM_INITDIALOG:
		{
			Dlg3=hwd;
			is_dlg3=true;
			val=true;
			for(i=0;i<241;i++)
			{
				SendMessage(GetDlgItem(hwd,DLG3_LB1),LB_ADDSTRING,0,(LPARAM)kraje[i]);
			}
			
			if(is_editp)
			{
				for(i=0;i<HD_P.count;i++)
				{
					if(PR[i].IDP==idp)
					{
						prd=PR[i];
						break;
					}
				}
				SetWindowText(GetDlgItem(hwd,DLG3_E1),prd.Nazwa);
				SetWindowText(GetDlgItem(hwd,DLG3_E2),prd.NIP);
				SetWindowText(GetDlgItem(hwd,DLG3_E3),prd.REGON);
				SetWindowText(GetDlgItem(hwd,DLG3_E4),prd.Kraj);
				SetWindowText(GetDlgItem(hwd,DLG3_E5),prd.Miasto);
				memset(adres,0,350);
				i=0;
				while((prd.KodPocz[i]!='-')&&(prd.KodPocz[i]!=0))
				{
					if(prd.KodPocz[i]!='-')adres[i]=prd.KodPocz[i];
					i++;
				}
				if(adres[0]!=0)
				{
					SetWindowText(GetDlgItem(hwd,DLG3_E9),adres);
					memset(adres,0,350);
					strcpy(adres,prd.KodPocz+i+1);
					SetWindowText(GetDlgItem(hwd,DLG3_E10),adres);
				}
				SetWindowText(GetDlgItem(hwd,DLG3_E11),prd.Telefon);
				SetWindowText(GetDlgItem(hwd,DLG3_E12),prd.Fax);
			}
			break;
		}
		case WM_PAINT:
			{
				if (!val)
				{

					hdc=BeginPaint(hwd,&lppaint);
					hpn=CreatePen(PS_SOLID,2,0x0000ff);
					SelectObject(hdc,(HGDIOBJ)hpn);
					GetWindowRect(GetDlgItem(hwd,DLG3_E1),&rc);
					pt=(LPPOINT)&rc;
					ScreenToClient(hwd,pt);
					pt++;
					ScreenToClient(hwd,pt);
					InflateRect(&rc,1,1);
					Rectangle(hdc,rc.left,rc.top,rc.right,rc.bottom);
					DeleteObject(hpn);
					EndPaint(hwd,&lppaint);
				}
				break;
			}
		case WM_COMMAND:
			{
				//Obs³uga lisy zawieraj¹cej listê krajów

				if(LOWORD(wp)==DLG3_LB1)
				{
					if(HIWORD(wp)==LBN_SELCHANGE)
					{
						i=SendMessage(GetDlgItem(hwd,DLG3_LB1),LB_GETCURSEL,0,0);
						SendMessage(GetDlgItem(hwd,DLG3_LB1),LB_GETTEXT,(WPARAM)i,(LPARAM)naz_k);
						SetWindowText(GetDlgItem(hwd,DLG3_E4),naz_k);
					}
					break;
				}

				//Obs³uga pola zawieraj¹cego nazwê kraju

				if(LOWORD(wp)==DLG3_E4)
				{
					if(HIWORD(wp)==EN_CHANGE)
					{
						memset(naz_k,0,strlen(naz_k));
						GetWindowTextA(GetDlgItem(hwd,DLG3_E4),naz_k,200);
						SendMessage(GetDlgItem(hwd,DLG3_LB1),LB_RESETCONTENT,0,0);
						naz=naz_k;
						for(i=0;i<241;i++)
						{
							if(naz_k[0]==0) SendMessage(GetDlgItem(hwd,DLG3_LB1),LB_ADDSTRING,0,(LPARAM)kraje[i]);
							else
							{
								i1=strncmp(naz,kraje[i],strlen(naz));
								if(i1==0)
								{
									SendMessage(GetDlgItem(hwd,DLG3_LB1),LB_ADDSTRING,0,(LPARAM)kraje[i]);;
								}
							}

						}
						break;
					}
					break;
				}

				//Przycisk Anuluj
					
				if(wp==DLG3_B1)
				{
					DestroyWindow(hwd);
					break;
				}
				
				//Przycisk Dodaj

				if(wp==DLG3_B2)
				{
				
					memset(adres,0,350);
					memset(&prd,0,sizeof(Producent));
					val=true;
					GetWindowText(GetDlgItem(hwd,DLG3_E1),prd.Nazwa,200);
					if(prd.Nazwa[0]==0)
					{
						val=false;
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Pola zaznaczone s¹ wymagane");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						InvalidateRgn(hwd,NULL,true);
						RedrawWindow(hwd,NULL,NULL,RDW_ALLCHILDREN|RDW_INVALIDATE|RDW_ERASENOW);
						SetFocus(hwd);
					} else
					{
						GetWindowText(GetDlgItem(hwd,DLG3_E2),prd.NIP,200);
						GetWindowText(GetDlgItem(hwd,DLG3_E3),prd.REGON,200);
						memset(adres,0,350);
						GetWindowText(GetDlgItem(hwd,DLG3_E4),adres,350);
						if(adres[0]!=0)strcpy(prd.Kraj,adres);			
						memset(adres,0,350);
						GetWindowText(GetDlgItem(hwd,DLG3_E5),adres,350);
						if(adres[0]!=0)strcpy(prd.Miasto,adres);					
						memset(adres,0,350);
						GetWindowText(GetDlgItem(hwd,DLG3_E6),adres,350);
						if(adres[0]!=0)strcpy(prd.Adres,adres);			
						memset(adres,0,350);
						GetWindowText(GetDlgItem(hwd,DLG3_E9),adres,350);
						if(adres[0]!=0)
						{
							strcpy(prd.KodPocz,adres);
							memset(adres,0,350);
							GetWindowText(GetDlgItem(hwd,DLG3_E10),adres,350);
							if(adres[0]!=0)
							{
								strcpy(prd.KodPocz+strlen(prd.KodPocz),"-");
								strcpy(prd.KodPocz+strlen(prd.KodPocz),adres);
							} else strcpy(prd.KodPocz,"");

						}
						GetWindowText(GetDlgItem(hwd,DLG3_E11),prd.Telefon,350);
						GetWindowText(GetDlgItem(hwd,DLG3_E12),prd.Fax,350);
						if(!is_editp)  prd.IDP=HD_P.LastID+1; else prd.IDP=idp;
						prd.BR[0]=13;
						prd.BR[1]=10;
						prd.CRC=EnumSum((BYTE*)&(prd.IDP),sizeof(Producent)-sizeof(int));
						if(is_editp)
						{
							for(i=0;i<HD_P.count;i++)
							{
								if(PR[i].IDP==prd.IDP)
								{
									for(j=0;j<HD_A.count;j++)
									{
										if(strcmp(ART[j].Producent,PR[i].Nazwa)==0)
										{
											memset(ART[j].Producent,0,350);
											strcpy(ART[j].Producent,prd.Nazwa);
										}
									}
									PR[i]=prd;
									break;
								}
							}
							Save_PR(&prd);
						}else
						{
							Dodaj_PR(&prd);
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Dodano nowego dostawcê");
							DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
							SetFocus(hwd);
						}
						
						DestroyWindow(hwd);
						break;
					}
					
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
				is_dlg3=false;
				EndDialog(hwd,0);
				//PostQuitMessage(0);
				break;
			}
		default:
			{
				return DefDlgProc(GetParent(hwd),code,wp,lp);
			}
	}
	return 0;
}


	//Procedura obs³ugi okna dialogowego wystawiania faktury

LRESULT CALLBACK Dlg4Proc(HWND hwd, int code, WPARAM wp, LPARAM lp)
{
	static HWND h,h1;
	LVCOLUMN lvc;
	LVITEM lvi;
	int i,i1,i2;
	char zn[350];
	bool bl;
	double c_br;
	static double zaplacono,zaplata;
	static int licz,sel,sel1;
	Fakt_Vat FVAT;
	static Fakt_Vat *FVAT_T,*FVAT_T1;
	Header_F hdf;
	SYSTEMTIME st;

	switch(code)
	{
		case WM_INITDIALOG:
		{
			if(!FRM._is)
			{
				memset(Err_Text,0,350);
				sprintf(Err_Text,"Nie dodano jeszcze danych firmy.\nPotrzebne bêd¹ one do wystawienia faktury.\nNale¿y uzupe³niæ wszystkie dane");
				DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
				SetFocus(hwd);
				DestroyWindow(hwd);
				break;
			}
			if(!NV.is_)
			{
				memset(Err_Text,0,350);
				sprintf(Err_Text,"Nie ustawiono jeszcze numeracji faktury.\nPotrzebna ona jest do wystawienia faktury.\nNale¿y ustawiæ numeracjê w menu Ustawienia->Numeracja faktur");
				DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
				SetFocus(hwd);
				DestroyWindow(hwd);
				break;
			}
			sel=0;
			sel1=0;
			Tid=-1;
			is_dlg4=true;
			licz=0;
			FVAT_T=NULL;
			SetProp(GetDlgItem(hwd,DLG4_E5),"BOOL",(HANDLE)false);
			SetProp(GetDlgItem(hwd,DLG4_E5),"PROC",(HANDLE)GetWindowLong(GetDlgItem(hwd,DLG4_E5),GWL_WNDPROC));
			SetWindowLong(GetDlgItem(hwd,DLG4_E5),GWL_WNDPROC,(LONG)WndEProc);
			SetProp(GetDlgItem(hwd,DLG4_E6),"BOOL",(HANDLE)false);
			SetProp(GetDlgItem(hwd,DLG4_E6),"PROC",(HANDLE)GetWindowLong(GetDlgItem(hwd,DLG4_E6),GWL_WNDPROC));
			SetWindowLong(GetDlgItem(hwd,DLG4_E6),GWL_WNDPROC,(LONG)WndEProc);
			SetProp(GetDlgItem(hwd,DLG4_E7),"BOOL",(HANDLE)false);
			SetProp(GetDlgItem(hwd,DLG4_E7),"PROC",(HANDLE)GetWindowLong(GetDlgItem(hwd,DLG4_E7),GWL_WNDPROC));
			SetWindowLong(GetDlgItem(hwd,DLG4_E7),GWL_WNDPROC,(LONG)WndEProc);
			SetProp(GetDlgItem(hwd,DLG4_E10),"BOOL",(HANDLE)false);
			SetProp(GetDlgItem(hwd,DLG4_E10),"PROC",(HANDLE)GetWindowLong(GetDlgItem(hwd,DLG4_E10),GWL_WNDPROC));
			SetWindowLong(GetDlgItem(hwd,DLG4_E10),GWL_WNDPROC,(LONG)WndEProc);
			CheckDlgButton(hwd,DLG4_RB2,BST_CHECKED);
			h=GetDlgItem(hwd,DLG4_E4);
			for(i=0;i<cnt.jmcnt;i++)
			{
				memset(zn,0,350);
				sprintf(zn,"%s(%s)",jm[i].naz,jm[i].znak);
				SendMessage(h,CB_ADDSTRING,(WPARAM)0,(LPARAM)zn);
			}
			SendMessage(h,CB_SETCURSEL,(WPARAM)cnt.def_jm,0);
			h1=GetDlgItem(hwd,DLG4_E12);
			for(i=0;i<cnt.jmcnt;i++)
			{
				memset(zn,0,350);
				sprintf(zn,"%s",form_zap[i].naz);
				SendMessage(h1,CB_ADDSTRING,0,(LPARAM)zn);
			}
			ComboBox_SetCurSel(h1,cnt.def_form_zap);
			LVD4=GetDlgItem(hwd,DLG4_LV1);
			ListView_SetExtendedListViewStyle(LVD4,LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_INFOTIP | LVS_EX_AUTOSIZECOLUMNS);
			lvc.mask=LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH;
			lvc.iSubItem=0;
			for(i=0;i<12;i++)
			{
				lvc.pszText=VAT_Col[i];
				lvc.cx=LVD4_W[i];
				ListView_InsertColumn(LVD4,i,&lvc);
			}
			if(is_Korekta)
			{
				SetWindowText(GetDlgItem(hwd,DLG4_E8),KONTR[id_k].Nazwa);
				EnableWindow(GetDlgItem(hwd,DLG4_B2),false);
			}
				/*zaplata=HD_F[fid].Zaplata;
				EnableWindow(GetDlgItem(hwd,DLG4_B2 ),false);
				memset(zn,0,350);
				dbl_str(HD_F[fid].Zaplata,zn,2,350);
				SetWindowText(GetDlgItem(hwd,DLG4_E11),zn);
			
				for(i1=0;i1<Vat_C;i1++)
				{
					FVAT=F_Vat[i1];
					memset(zn,0,350);
					lvi.mask=LVIF_TEXT;
					lvi.iSubItem=0;
					lvi.iItem=licz;
					itoa(FVAT.LP,zn,10);
					lvi.pszText=zn;
					ListView_InsertItem(LVD4,&lvi);
					memset(zn,0,350);
					for(i=0;i<11;i++)
					{
						if(i==0)strcpy(zn,FVAT.Nazwa); else if(i==1) itoa(FVAT.PKWiU,zn,10); else if(i==2) itoa(FVAT.ilosc,zn,10); else
							if(i==3) strcpy(zn,FVAT.JM); else if(i==4) dbl_str(FVAT.Cena_Netto,zn,2,350); else if(i==5) dbl_str(FVAT.Rabat,zn,2,350); else
								if(i==6) dbl_str(FVAT.Cena_Netto2,zn,2,350); else if(i==7) dbl_str(FVAT.VAT,zn,2,350); else 
									if(i==8) dbl_str(FVAT.KW_Netto,zn,2,350); else if(i==9) dbl_str(FVAT.KW_VAT,zn,2,350); else 
										if(i==10) dbl_str(FVAT.KW_Brutto,zn,2,350);
						ListView_SetItemText(LVD4,licz,i+1,zn);
					}
					licz++;
					if(FVAT_T!=NULL)
					{
						FVAT_T1=new Fakt_Vat[licz];
						for(i=0;i<licz-1;i++)
						{
							FVAT_T1[i]=FVAT_T[i];
						}
						delete FVAT_T;
						FVAT_T=FVAT_T1;
					}else FVAT_T=new Fakt_Vat[licz];
					FVAT_T[licz-1]=FVAT;
				}
			}else */ 
			zaplata=0;
			break;
		}
		case WM_COMMAND:
			{
				
				if(LOWORD(wp)==DLG4_E12)
				{
					if(HIWORD(wp)==CBN_SELCHANGE)
					{
						sel=ComboBox_GetCurSel(h1);
						break;
					}
					if(HIWORD(wp)==CBN_EDITCHANGE)
					{
						
						if(sel!=2) ComboBox_SetCurSel(h1,sel);
					}
					break;
				}

				if(LOWORD(wp)==DLG4_E4)
				{
					if(HIWORD(wp)==CBN_SELCHANGE)
					{
						sel1=ComboBox_GetCurSel(h);
						break;
					}
					if(HIWORD(wp)==CBN_EDITCHANGE)
					{
						
						if(sel1!=7) ComboBox_SetCurSel(h,sel1);
						
					}
					break;
				}

				if(wp==DLG4_RB1)
				{
					if(Tid!=-1)
					{
						dbl_str(ART[Tid].Cena_Netto,zn,2,350);
						SetWindowText(GetDlgItem(hwd,DLG4_E5),zn);
					}

					break;
				}
				if(wp==DLG4_RB2)
				{
					if(Tid!=-1)
					{
						dbl_str(ART[Tid].Cena_Brutto,zn,2,350);
						SetWindowText(GetDlgItem(hwd,DLG4_E5),zn);
					}

					break;
				}
				if(wp==DLG4_B2)     //Przycisk wyboru kontrahenta
				{
					is_wyb_k=false;
					DialogBox(hst,MAKEINTRESOURCE(ID_DLG_6),hwd,(DLGPROC)&Dlg6Proc);
					if(is_wyb_k)
					{
						SetWindowText(GetDlgItem(hwd,DLG4_E8),KONTR[idk].Nazwa);
					}
					SetFocus(hwd);
					break;
				}
				if(wp==DLG4_B4)		//Przycisk Anuluj
				{
					is_Korekta=false;
					DestroyWindow(hwd);
					break;
				}

				if(wp==DLG4_B5)			//Przycisk dodania pozycji do faktury
				{
					memset(&FVAT,0,sizeof(Fakt_Vat));
					FVAT.LP=licz+1;
					bl=true;
					memset(zn,0,350);
					GetWindowText(GetDlgItem(hwd,DLG4_E4),zn,350);
					if(sel1!=7)
					{
						for(i=0;zn[i]!='(';i++);
						i1=0;
						i++;
						for(i=i;zn[i]!=')';i++)
						{
							if(zn[i]!=')') FVAT.JM[i1]=zn[i];
							i1++;
						}
					}else strncpy(FVAT.JM,zn,10);

					memset(zn,0,350);
					GetWindowText(GetDlgItem(hwd,DLG4_E2),zn,350);
					if(zn[0]!=0)  FVAT.PKWiU=atoi(zn);
					memset(zn,0,350);
					GetWindowText(GetDlgItem(hwd,DLG4_E7),zn,350);
					if(zn[0]!=0)  FVAT.Rabat=(float)atof(zn); else FVAT.Rabat=0;
					GetWindowText(GetDlgItem(hwd,DLG4_E1),FVAT.Nazwa,350);
					if(FVAT.Nazwa[0]==0) bl=false;
					if(bl)
					{
						memset(zn,0,350);
						GetWindowText(GetDlgItem(hwd,DLG4_E3),zn,350);
						if(zn[0]==0) bl =false; else FVAT.ilosc=atoi(zn);
						
					}
					if(bl)
					{
						memset(zn,0,350);
						GetWindowText(GetDlgItem(hwd,DLG4_E6),zn,350);
						if(zn[0]==0) bl =false; else FVAT.VAT=atof(zn);
						
						
					}
					if(bl)
					{
						memset(zn,0,350);
						GetWindowText(GetDlgItem(hwd,DLG4_E5),zn,350);
						if(zn[0]==0) bl =false; else
						{
							if(IsDlgButtonChecked(hwd,DLG4_RB1)) FVAT.Cena_Netto=atof(zn); else
							{
								c_br=atof(zn);
								c_br=c_br/(100+FVAT.VAT);
								FVAT.Cena_Netto=c_br*100;
								//dbl_str(FVAT.Cena_Netto,zn,2,350);
								//FVAT.Cena_Netto=atof(zn);

							}
							if(IsDlgButtonChecked(hwd,DLG4_CH1)) FVAT.Cena_Netto=(-FVAT.Cena_Netto);
							if(FVAT.Rabat>0)
							{
								FVAT.Cena_Netto2=FVAT.Cena_Netto-((FVAT.Cena_Netto/100)*FVAT.Rabat);
								//dbl_str(FVAT.Cena_Netto2,zn,2,350);
								//FVAT.Cena_Netto2=atof(zn);
							}else FVAT.Cena_Netto2=FVAT.Cena_Netto;
							FVAT.KW_Netto=FVAT.Cena_Netto2*FVAT.ilosc;
							//dbl_str(FVAT.KW_Netto,zn,2,350);
							//FVAT.KW_Netto=atof(zn);
							FVAT.KW_VAT=(FVAT.KW_Netto/100)*FVAT.VAT;
							//dbl_str(FVAT.KW_VAT,zn,2,350);
							//FVAT.KW_VAT=atof(zn);
							FVAT.KW_Brutto=FVAT.KW_Netto+FVAT.KW_VAT;
							//dbl_str(FVAT.KW_Brutto,zn,2,350);
							//FVAT.KW_Brutto=atof(zn);
							FVAT.BR[0]=13;
							FVAT.BR[1]=10;
						}
					}
					if(bl)
					{	memset(zn,0,350);
						lvi.mask=LVIF_TEXT;
						lvi.iSubItem=0;
						lvi.iItem=licz;
						itoa(FVAT.LP,zn,10);
						lvi.pszText=zn;
						ListView_InsertItem(LVD4,&lvi);
						memset(zn,0,350);
						for(i=0;i<11;i++)
						{
							if(i==0)strcpy(zn,FVAT.Nazwa); else if(i==1) itoa(FVAT.PKWiU,zn,10); else if(i==2) itoa(FVAT.ilosc,zn,10); else
								if(i==3) strcpy(zn,FVAT.JM); else if(i==4) dbl_str(FVAT.Cena_Netto,zn,2,350); else if(i==5) dbl_str(FVAT.Rabat,zn,2,350); else
									if(i==6) dbl_str(FVAT.Cena_Netto2,zn,2,350); else if(i==7) dbl_str(FVAT.VAT,zn,2,350); else 
										if(i==8) dbl_str(FVAT.KW_Netto,zn,2,350); else if(i==9) dbl_str(FVAT.KW_VAT,zn,2,350); else 
											if(i==10) dbl_str(FVAT.KW_Brutto,zn,2,350);
							ListView_SetItemText(LVD4,licz,i+1,zn);

						}
						licz++;
						if(FVAT_T!=NULL)
						{
							FVAT_T1=new Fakt_Vat[licz];
							zaplata=0;
							for(i=0;i<licz-1;i++)
							{
								FVAT_T1[i]=FVAT_T[i];
								zaplata=zaplata+FVAT_T[i].KW_Brutto;
								/*if(!is_Korekta) zaplata=zaplata+FVAT_T[i].KW_Brutto;
								else 
									if(i>=Vat_C) zaplata=zaplata+FVAT_T[i].KW_Brutto;*/
							}
							delete FVAT_T;
							FVAT_T=FVAT_T1;
						}else FVAT_T=new Fakt_Vat[licz];
						FVAT_T[licz-1]=FVAT;
						zaplata=zaplata+FVAT_T[licz-1].KW_Brutto;
						memset(zn,0,350);
						dbl_str(zaplata,zn,2,350);
						SetWindowText(GetDlgItem(hwd,DLG4_E11),zn);
						zaplata=atof(zn);
					} else 
						{
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Pola oznaczone gwiazdk¹ s¹ wymagane");
							DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
							SetFocus(hwd);
						}
					break;
				}

				if(wp==DLG4_B6)		//Przycisk usuniêcia pozycji z faktury
				{
					i1=ListView_GetSelectionMark(LVD4);
					if(i1<0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie zaznaczono pozycji");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
				/*	if(is_Korekta && i1+1<=Vat_C)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Tej pozycji nie da siê ju¿ usun¹æ");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					*/
					if(i1>=0)
					{
						if(licz>0)
						{
							zaplata=0;
							licz--;
							if(FVAT_T!=NULL)
							{
								FVAT_T1=new Fakt_Vat[licz];
								i2=0;
								for(i=0;i<=licz;i++)
								{
									if(i!=i1) 
									{
										FVAT_T1[i2]=FVAT_T[i];
										zaplata=zaplata+FVAT_T[i].KW_Brutto;
										/*if(!is_Korekta) zaplata=zaplata+FVAT_T[i].KW_Brutto;
										else
											if(i>=Vat_C) zaplata=zaplata+FVAT_T[i].KW_Brutto;*/
										FVAT_T1[i2].LP=i2+1;
										i2++;
									}
								}
								delete FVAT_T;
								FVAT_T=FVAT_T1;
							}
							memset(zn,0,350);
							dbl_str(zaplata,zn,2,350);
							SetWindowText(GetDlgItem(hwd,DLG4_E11),zn);
							zaplata=atof(zn);
						}
						i2=licz;
						licz=0;
						ListView_DeleteAllItems(LVD4);
						for(i1=0;i1<i2;i1++)
						{
							FVAT=FVAT_T[i1];
							memset(zn,0,350);
							lvi.mask=LVIF_TEXT;
							lvi.iSubItem=0;
							lvi.iItem=licz;
							itoa(FVAT.LP,zn,10);
							lvi.pszText=zn;
							ListView_InsertItem(LVD4,&lvi);
							memset(zn,0,350);
							for(i=0;i<11;i++)
							{
								if(i==0)strcpy(zn,FVAT.Nazwa); else if(i==1) itoa(FVAT.PKWiU,zn,10); else if(i==2) itoa(FVAT.ilosc,zn,10); else
									if(i==3) strcpy(zn,FVAT.JM); else if(i==4) dbl_str(FVAT.Cena_Netto,zn,2,350); else if(i==5) dbl_str(FVAT.Rabat,zn,2,350); else
										if(i==6) dbl_str(FVAT.Cena_Netto2,zn,2,350); else if(i==7) dbl_str(FVAT.VAT,zn,2,350); else 
											if(i==8) dbl_str(FVAT.KW_Netto,zn,2,350); else if(i==9) dbl_str(FVAT.KW_VAT,zn,2,350); else 
												if(i==10) dbl_str(FVAT.KW_Brutto,zn,2,350);
								ListView_SetItemText(LVD4,licz,i+1,zn);

							}
							licz++;
						}
					}
					break;
				}
				
				if(wp==DLG4_B1)		//Przycisk wyboru towaru
				{
					DialogBox(hst,MAKEINTRESOURCE(ID_DLG_5),hwd,(DLGPROC)&Dlg5Proc);
					if(Tid!=-1)
					{
						SetWindowText(GetDlgItem(hwd,DLG4_E1),ART[Tid].Nazwa);
						dbl_str(ART[Tid].VAT,zn,2,350);
						SetWindowText(GetDlgItem(hwd,DLG4_E6),zn);
						if(IsDlgButtonChecked(hwd,DLG4_RB1))dbl_str(ART[Tid].Cena_Netto,zn,2,350);
						else dbl_str(ART[Tid].Cena_Brutto,zn,2,350);
						SetWindowText(GetDlgItem(hwd,DLG4_E5),zn);

					}
					SetFocus(hwd);
					break;
				}
				if(wp==DLG4_B3)		//Przycisk zatwierdŸ
				{
					if(!FRM._is)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie dodano jeszcze danych firmy.\nPotrzebne bêd¹ one do wystawienia faktury.\nNale¿y uzupe³niæ wszystkie dane");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					if(!NV.is_)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie ustawiono jeszcze numeracji faktury.\nPotrzebna ona jest do wystawienia faktury.\nNale¿y ustawiæ numeracjê w menu Ustawienia->Numeracja faktur");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					if(licz<=0) 
						{
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Brak pozycji w fakturze VAT");
							DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
							SetFocus(hwd);
						}
					else
					{
						memset(zn,0,350);
						GetWindowText(GetDlgItem(hwd,DLG4_E8),zn,350);
						if(zn[0]==0)
						{
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Musisz wybraæ kontrahenta");
							DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
							SetFocus(hwd);
							break;
						}
						GetWindowText(GetDlgItem(hwd,DLG4_E12),hdf.form_zap,35);
						GetSystemTime(&st);
						hdf.count=licz;
						if(is_Korekta) hdf.IDK=KONTR[id_k].IDK; else hdf.IDK=KONTR[idk].IDK;
						hdf.dzien=st.wDay;
						hdf.miesiac=st.wMonth;
						hdf.rok=st.wYear;
						hdf.KW_B=0;
						hdf.KW_N=0;
						hdf.KW_V=0;
						for(i=0;i<licz;i++)
						{
							
							hdf.KW_B=hdf.KW_B+FVAT_T[i].KW_Brutto;
							hdf.KW_N=hdf.KW_N+FVAT_T[i].KW_Netto;
							hdf.KW_V=hdf.KW_V+FVAT_T[i].KW_VAT;
							
						}
						/*memset(zn,0,350);
						dbl_str(hdf.KW_V,zn,2,350);
						hdf.KW_V=atof(zn);
						memset(zn,0,350);
						dbl_str(hdf.KW_N,zn,2,350);
						hdf.KW_N=atof(zn);
						memset(zn,0,350);
						dbl_str(hdf.KW_B,zn,2,350);
						hdf.KW_B=atof(zn);
						memset(hdf.numer,0,50);
						*/
						if(!is_Korekta)
						{
							DialogBox(hst,MAKEINTRESOURCE(ID_DLG_46),hwd,(DLGPROC)&DLG46Proc);
							strcpy(hdf.numer,NV.przed);
							if(HD_FB.id+1<10000 && HD_FB.rok==st.wYear)
							{
								if(HD_FB.id+1<10) strcpy(hdf.numer+strlen(hdf.numer),"0000");
								else 
									if(HD_FB.id+1<100)strcpy(hdf.numer+strlen(hdf.numer),"000");
									else 
										if(HD_FB.id+1<1000)strcpy(hdf.numer+strlen(hdf.numer),"00");
										else strcpy(hdf.numer+strlen(hdf.numer),"0");
							}
							if(HD_FB.rok==st.wYear || is_zm_num) itoa(HD_FB.id+1,hdf.numer+strlen(hdf.numer),10); 
							else
							{
								strcpy(hdf.numer+strlen(hdf.numer),"0000");
								itoa(1,hdf.numer+strlen(hdf.numer),10);
							}
							strcpy(hdf.numer+strlen(hdf.numer),"/");
							itoa(st.wYear,hdf.numer+strlen(hdf.numer),10);
							hdf.is_korekta=false;
						}
						else 
						{
							strcpy(hdf.numer,HD_F[fid].numer);
							hdf.is_korekta=true;
						}
					
						memset(zn,0,350);
						GetWindowText(GetDlgItem(hwd,DLG4_E10),zn,350);
						if(zn[0]==0) zaplacono=0; else zaplacono=atof(zn);
						hdf.Zaplata=zaplata-zaplacono;
						memset(zn,0,350);
						GetWindowText(GetDlgItem(hwd,DLG4_E13),zn,350);
						if(zn[0]==0)hdf.il_dni=0;
						else hdf.il_dni= atoi(zn);
						hdf.ter_plat=Time_Add(st,hdf.il_dni);
						hdf.is_ex=true;
						Dodaj_Fakt(FVAT_T,hdf);
						memset(Query_Text,0,350);
						sprintf(Query_Text,"Zapisano Fakturê w bazie danych\nCzy chcesz wydrukowaæ fakturê ?");
						DialogBox(hst,MAKEINTRESOURCE(DLG_Q),hwd,(DLGPROC)&DLGQProc);
						if(is_ok) Print_Vat(hdf,FVAT_T,hwd,hst,false);
						DestroyWindow(hwd);
					}
					break;
				}

				if(wp==DLG4_B7)		//Przycisk drukuj proformê
				{
					if(licz<=0) 
						{
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Brak pozycji w fakturze VAT");
							DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
							SetFocus(hwd);
							
						}
					else
					{
						memset(zn,0,350);
						GetWindowText(GetDlgItem(hwd,DLG4_E8),zn,350);
						if(zn[0]==0)
						{
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Musisz wybraæ kontrahenta");
							DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
							SetFocus(hwd);
							break;
						}
						GetWindowText(GetDlgItem(hwd,DLG4_E12),hdf.form_zap,35);
						GetSystemTime(&st);
						hdf.count=licz;
						if(is_Korekta) hdf.IDK=KONTR[id_k].IDK; else hdf.IDK=KONTR[idk].IDK;
						hdf.dzien=st.wDay;
						hdf.miesiac=st.wMonth;
						hdf.rok=st.wYear;
						hdf.KW_B=0;
						hdf.KW_N=0;
						hdf.KW_V=0;
						for(i=0;i<licz;i++)
						{
							
							hdf.KW_B=hdf.KW_B+FVAT_T[i].KW_Brutto;
							hdf.KW_N=hdf.KW_N+FVAT_T[i].KW_Netto;
							hdf.KW_V=hdf.KW_V+FVAT_T[i].KW_VAT;
							
						}
						/*memset(zn,0,350);
						dbl_str(hdf.KW_V,zn,2,350);
						hdf.KW_V=atof(zn);
						memset(zn,0,350);
						dbl_str(hdf.KW_N,zn,2,350);
						hdf.KW_N=atof(zn);
						memset(zn,0,350);
						dbl_str(hdf.KW_B,zn,2,350);
						hdf.KW_B=atof(zn);
						memset(hdf.numer,0,50);
						*/
						if(!is_Korekta)
						{
							strcpy(hdf.numer,NV.przed);
							if(HD_FB.id+1<10000 && HD_FB.rok==st.wYear)
							{
								if(HD_FB.id+1<10) strcpy(hdf.numer+strlen(hdf.numer),"0000");
								else 
									if(HD_FB.id+1<100)strcpy(hdf.numer+strlen(hdf.numer),"000");
									else 
										if(HD_FB.id+1<1000)strcpy(hdf.numer+strlen(hdf.numer),"00");
										else strcpy(hdf.numer+strlen(hdf.numer),"0");
							}
							if(HD_FB.rok==st.wYear) itoa(HD_FB.id+1,hdf.numer+strlen(hdf.numer),10); 
							else
							{
								strcpy(hdf.numer+strlen(hdf.numer),"0000");
								itoa(1,hdf.numer+strlen(hdf.numer),10);
							}
							strcpy(hdf.numer+strlen(hdf.numer),"/");
							itoa(st.wYear,hdf.numer+strlen(hdf.numer),10);
							hdf.is_korekta=false;
						}
						else 
						{
							strcpy(hdf.numer,HD_F[fid].numer);
							hdf.is_korekta=true;
						}
					
						memset(zn,0,350);
						GetWindowText(GetDlgItem(hwd,DLG4_E10),zn,350);
						if(zn[0]==0) zaplacono=0; else zaplacono=atof(zn);
						hdf.Zaplata=zaplata-zaplacono;
					
						
						Print_Vat(hdf,FVAT_T,hwd,hst,true);
						DestroyWindow(hwd);
					}
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
				is_dlg4=false;
				if(FVAT_T!=NULL) delete FVAT_T;
				EndDialog(hwd,0);
			}
		default: 
			{
				return DefDlgProc(MainWnd,code,wp,lp);
			}
	}
	return 0;
}


	//Procedura obs³ugi okna dialogowego wybrania towaru do faktury


LRESULT CALLBACK Dlg5Proc(HWND hwd, int code, WPARAM wp, LPARAM lp)
{
	static HWND h;
	int i,i1,i2;
	static int *TID;
	char zn[350];
	bool bl;
	DWORD dw;

	switch(code)
	{
		case WM_INITDIALOG:
		{
			h=GetDlgItem(hwd,DLG5_LB1);
			TID=new int[HD_A.count+1];
			memset((char*)TID,0,(HD_A.count+1)*sizeof(int));
			for(i=0;i<HD_A.count;i++)
			{
				SendMessage(h,LB_ADDSTRING,(WPARAM)0,(LPARAM)ART[i].Nazwa);
				TID[0]++;
				TID[i+1]=i;
			}
			SendMessage(GetDlgItem(hwd,DLG5_B3),WM_KILLFOCUS,0,0);
			break;
		}
		case WM_COMMAND:
		{
			if(LOWORD(wp)==DLG5_LB1)
			{
				if(HIWORD(wp)==LBN_SELCHANGE)
				{
					
					i=-1;
					i=ListBox_GetCurSel(h);
					if(i>=0)
					{
						Tid=TID[i+1];
						EnableWindow(GetDlgItem(hwd,DLG5_E1),false);
						EnableWindow(GetDlgItem(hwd,DLG5_E2),false);
						EnableWindow(GetDlgItem(hwd,DLG5_E3),false);
						SetWindowText(GetDlgItem(hwd,DLG5_E3),ART[Tid].KOD_KR);
						SetWindowText(GetDlgItem(hwd,DLG5_E2),ART[Tid].KOD_TOW);
						SetWindowText(GetDlgItem(hwd,DLG5_E1),ART[Tid].Nazwa);
						EnableWindow(GetDlgItem(hwd,DLG5_E1),true);
						EnableWindow(GetDlgItem(hwd,DLG5_E2),true);
						EnableWindow(GetDlgItem(hwd,DLG5_E3),true);
					}
				}
				break;
			}
			
			if(wp==DLG5_B3)				//Dodaj Nowy Artyku³
			{
				is_edit=false;
				DialogBox(hst,MAKEINTRESOURCE(ID_DLG_1),hwd,(DLGPROC)&DlgProc1);
				if(TID) delete TID;
				TID=new int[HD_A.count+1];
				memset(TID,0,HD_A.count+1);
				for(i=0;i<HD_A.count;i++)
				{
					TID[0]++;
					TID[i+1]=i;
				}
				dw=EN_CHANGE;
				dw=dw<<16;
				SendMessage(hwd,WM_COMMAND,(WPARAM)dw,0);
				SetFocus(hwd);
				break;
			}
			
			if(wp==DLG5_B2)				//ANULUJ
			{
				DestroyWindow(hwd);
				Tid=-1;
				break;
			}
			if(wp==DLG5_B1)				//OK
			{
				i=SendMessage(h,LB_GETCURSEL,0,0);
				if(i<0) 
				{
					memset(kod_tow,0,35);
					GetWindowText(GetDlgItem(hwd,DLG5_E2),kod_tow,35);
					DestroyWindow(hwd); 
					break;
				}
				Tid=TID[i+1];
				memset(kod_tow,0,35);
				strcpy(kod_tow,ART[Tid].KOD_KR);
				DestroyWindow(hwd);
				break;
			}
			if(HIWORD(wp)==EN_CHANGE)
			{
				SendMessage(h,LB_RESETCONTENT,0,0);
				memset((char*)TID,0,(HD_A.count+1)*sizeof(int));
				for(i=0;i<HD_A.count;i++)
				{
					bl=true;
					memset(zn,0,350);
					GetWindowText(GetDlgItem(hwd,DLG5_E1),zn,350);
					if(zn[0]!=0)
					{
						i1=strncmp(ART[i].Nazwa,zn,strlen(zn));
						if(i1!=0)bl=false;
					}
					
					if(bl)
					{
						memset(zn,0,350);
						GetWindowText(GetDlgItem(hwd,DLG5_E2),zn,350);
						if(zn[0]!=0)
						{
							i1=strncmp(ART[i].KOD_TOW,zn,strlen(zn));
							if(i1!=0)bl=false;
						}
					}

					if(bl)
					{
						memset(zn,0,350);
						GetWindowText(GetDlgItem(hwd,DLG5_E3),zn,350);
						if(zn[0]!=0)
						{
							i1=strncmp(ART[i].KOD_KR,zn,strlen(zn));
							if(i1!=0)bl=false;
						}
					}
					if(bl) 
					{
						SendMessage(h,LB_ADDSTRING,(WPARAM)0,(LPARAM)ART[i].Nazwa);
						TID[0]++;
						TID[TID[0]]=i;
					}

				}
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
				if(TID!=NULL) delete TID;
				EndDialog(hwd,0);
				break;
			}
		default:
			{
				return DefDlgProc(GetParent(hwd),code,wp,lp);
			}
	}
	return 0;
};

	//Procedura okna dialogowego zarz¹dzania baz¹ kontrahentów

LRESULT CALLBACK Dlg6Proc(HWND hwd, int code, WPARAM wp, LPARAM lp)
{
	LVCOLUMN lvc;
	LVITEM lvi;
	int i,i1,i2;
	char zn[350];
	bool bl;
	LPSTR LPS;

	switch(code)
	{
		case WM_INITDIALOG:
		{
			is_ch_k=false;
			is_dlg6=true;
			if(is_z_k) ShowWindow(GetDlgItem(hwd,DLG6_B5),SW_HIDE);
			KID = new int[HD_K.count];
			memset(KID,-1,HD_K.count);
			LVD6=GetDlgItem(hwd,DLG6_LV1);
			ListView_SetExtendedListViewStyle(LVD6,LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_INFOTIP | LVS_EX_AUTOSIZECOLUMNS);
			lvc.mask=LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH;
			lvc.iSubItem=0;
			for(i=0;i<8;i++)
			{
				lvc.pszText=KONTR_Col[i];
				lvc.cx=LVD6_W[i];
				ListView_InsertColumn(LVD6,i,&lvc);
			}
			lvi.iSubItem=0;
			lvi.mask=LVIF_TEXT;
			for(i=0;i<HD_K.count;i++)
			{
				lvi.iItem=i;
				lvi.pszText=KONTR[i].Nazwa;
				KID[i]=ListView_InsertItem(LVD6,&lvi);
				for(i1=0;i1<7;i1++)
				{
					if(i1==0)LPS=KONTR[i].Adres; else if(i1==1)LPS=KONTR[i].KodPocz; else if(i1==2)LPS=KONTR[i].Miasto; else
						if(i1==3)LPS=KONTR[i].Kraj; else if(i1==4)LPS=KONTR[i].NIP; else if(i1==5)LPS=KONTR[i].Regon; else
							if(i1==6)LPS=KONTR[i].Tel;
					ListView_SetItemText(LVD6,i,i1+1,LPS);
				}
			}
			break;
		}

		case WM_COMMAND:
			{
				if(HIWORD(wp)==EN_CHANGE)	//zdarzenie zmiany wartoœci pól edycyjnych
				{
					if(KID) delete KID;
					KID = new int[HD_K.count];
					ListView_DeleteAllItems(LVD6);
					memset(KID,-1,HD_K.count);
					i2=0;
					for(i=0;i<HD_K.count;i++)
					{
						bl=true;
						memset(zn,0,350);
						GetWindowText(GetDlgItem(hwd,DLG6_E1),zn,350);
						if(zn[0]!=0)
						{
							if(strncmp(zn,KONTR[i].Nazwa,strlen(zn))!=0) bl=false;
						}
						if(bl)
						{
							memset(zn,0,350);
							GetWindowText(GetDlgItem(hwd,DLG6_E2),zn,350);
							if(zn[0]!=0)
							{
								if(strncmp(zn,KONTR[i].NIP,strlen(zn))!=0) bl=false;
							}
						}
						if(bl)
						{
							memset(zn,0,350);
							GetWindowText(GetDlgItem(hwd,DLG6_E3),zn,350);
							if(zn[0]!=0)
							{
								if(strncmp(zn,KONTR[i].Regon,strlen(zn))!=0) bl=false;
							}
						}
						if(bl)
						{
							lvi.iSubItem=0;
							lvi.mask=LVIF_TEXT;
							lvi.iItem=i2;
							lvi.pszText=KONTR[i].Nazwa;
							ListView_InsertItem(LVD6,&lvi);
							KID[i2]=i;
							for(i1=0;i1<7;i1++)
							{
								if(i1==0)LPS=KONTR[i].Adres; else if(i1==1)LPS=KONTR[i].KodPocz; else if(i1==2)LPS=KONTR[i].Miasto; else
									if(i1==3)LPS=KONTR[i].Kraj; else if(i1==4)LPS=KONTR[i].NIP; else if(i1==5)LPS=KONTR[i].Regon; else
										if(i1==6)LPS=KONTR[i].Tel;
								ListView_SetItemText(LVD6,i2,i1+1,LPS);
							}
							i2++;
						}
					}
					break;
				}
				if(wp==DLG6_B2)		//Przycisk usuwania kontrahenta z bazy
				{
					i=ListView_GetSelectionMark(LVD6);
					if(i<0) break;
					memset(Query_Text,0,350);
					sprintf(Query_Text,"Czy napenwo chcesz usun¹æ kontrahenta ?");
					DialogBox(hst,MAKEINTRESOURCE(DLG_Q),hwd,(DLGPROC)&DLGQProc);
					if(!is_ok) break;
					i=KID[i];
					Us_KR(KONTR[i].IDK);
					SendMessage(hwd,WM_COMMAND,(WPARAM)(EN_CHANGE<<16),0);
					SetFocus(hwd);
					break;
				}
				if(wp==DLG6_B1)		//przycisk dodanaia nowego kontrahentu
				{

					DialogBox(hst,MAKEINTRESOURCE(ID_DLG_7),hwd,(DLGPROC)&Dlg7Proc);
					SetFocus(hwd);
					SendMessage(hwd,WM_COMMAND,(WPARAM)(EN_CHANGE<<16),0);
					break;
				}

				if(wp==DLG6_B3)		//Przycisk zmiany danych kontrahenta
				{
					idk=ListView_GetSelectionMark(LVD6);
					if(idk<0)break;
					idk=KID[idk];
					is_ch_k=true;
					DialogBox(hst,MAKEINTRESOURCE(ID_DLG_7),hwd,(DLGPROC)&Dlg7Proc);
					is_ch_k=false;
					SendMessage(hwd,WM_COMMAND,(WPARAM)(EN_CHANGE<<16),0);
					SetFocus(hwd);
					break;
				}

				if(wp==DLG6_B5)		//Przycisk Wyboru kontrahenta do faktury
				{
					i=ListView_GetSelectionMark(LVD6);
					if(i<0) break;
					idk=KID[i];
					is_wyb_k=true;
					DestroyWindow(hwd);
					break;
				}

				
				if(wp==DLG6_B4)			//Przycisk anuluj
				{
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
			if(KID!=NULL) delete KID;
			is_dlg6=false;
			EndDialog(hwd,0);
		}
		default:
		{
			return DefDlgProc(GetParent(hwd),code,wp,lp);
		}
	}

	return 0;
}


	//Procedura obs³ugi okna dialogowego dodawania nowych kontrahentów

LRESULT _stdcall Dlg7Proc(HWND hwd, int code ,WPARAM wp, LPARAM lp)
{
	Kontrahent KONT;
	bool bl;
	char zn[350];
	int i;
	char z;

	switch(code)
	{
		case WM_INITDIALOG:
		{
			memset(&KONT,0,sizeof(Kontrahent));
			if(is_ch_k)
			{
				SetWindowText(GetDlgItem(hwd,DLG7_E1),KONTR[idk].Nazwa);
				SetWindowText(GetDlgItem(hwd,DLG7_E2),KONTR[idk].Adres);
				memset(zn,0,350);
				for(i=0;KONTR[idk].KodPocz[i]!='-';i++)
				{
					if(KONTR[idk].KodPocz[i]!='-') zn[i]=KONTR[idk].KodPocz[i];
				}
				SetWindowText(GetDlgItem(hwd,DLG7_E3),zn);
				memset(zn,0,350);
				strcpy(zn,KONTR[idk].KodPocz+i+1);
				SetWindowText(GetDlgItem(hwd,DLG7_E4),zn);
				SetWindowText(GetDlgItem(hwd,DLG7_E5),KONTR[idk].Miasto);
				SetWindowText(GetDlgItem(hwd,DLG7_E6),KONTR[idk].Kraj);
				SetWindowText(GetDlgItem(hwd,DLG7_E7),KONTR[idk].NIP);
				SetWindowText(GetDlgItem(hwd,DLG7_E8),KONTR[idk].Regon);
				SetWindowText(GetDlgItem(hwd,DLG7_E9),KONTR[idk].Tel);
			}
			break;
		}

		case WM_COMMAND:
			{
				if(wp==DLG7_B1)				//Przycisk Anuluj
				{
					DestroyWindow(hwd);
					break;
				}
				if(wp==DLG7_B2)				//Przycisk Dodaj
				{
					bl=true;
					memset(zn,0,350);
					GetWindowText(GetDlgItem(hwd,DLG7_E1),KONT.Nazwa,350);
					if(KONT.Nazwa[0]==0)bl=false;
					if(bl)
					{
						GetWindowText(GetDlgItem(hwd,DLG7_E2),KONT.Adres,350);
						if(KONT.Adres[0]==0)bl=false;
					}
					if(bl)
					{
						GetWindowText(GetDlgItem(hwd,DLG7_E3),KONT.KodPocz,350);
						if(KONT.KodPocz[0]==0)bl=false;
						if(bl)
						{
							GetWindowText(GetDlgItem(hwd,DLG7_E4),zn,350);
							if(zn[0]==0) bl=false; else
							{
								strcpy(KONT.KodPocz+strlen(KONT.KodPocz),"-");
								strcpy(KONT.KodPocz+strlen(KONT.KodPocz),zn);
							}
						}
					}
					if(bl)
					{
						GetWindowText(GetDlgItem(hwd,DLG7_E5),KONT.Miasto,350);
						if(KONT.Miasto[0]==0)bl=false;
					}
					if(bl)
					{
						GetWindowText(GetDlgItem(hwd,DLG7_E7),KONT.NIP,350);
						if(KONT.NIP[0]==0)bl=false;
					}
					if(!bl)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Musisz wype³niæ pola oznaczone gwiazdk¹");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}else
					{
						GetWindowText(GetDlgItem(hwd,DLG7_E6),KONT.Kraj,350);
						GetWindowText(GetDlgItem(hwd,DLG7_E8),KONT.Regon,350);
						GetWindowText(GetDlgItem(hwd,DLG7_E9),KONT.Tel,350);
						KONT.BR[0]=13;
						KONT.BR[1]=10;
						
						if(is_ch_k)
						{
							KONT.IDK=KONTR[idk].IDK;
							KONT.CRC=EnumSum((BYTE*)&(KONT.IDK),sizeof(Kontrahent)-sizeof(int));
							KONTR[idk]=KONT;
							Save_KR(&KONT);
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Zaktualizowano kontrahenta...");
							DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
							SetFocus(hwd);

						}else
						{
							KONT.IDK=HD_K.LastID+1;
							KONT.CRC=EnumSum((BYTE*)&(KONT.IDK),sizeof(Kontrahent)-sizeof(int));
							Dodaj_Kontr(&KONT);
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Dodano kontrahenta do bazy danych");
							DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
							SetFocus(hwd);
						}
						DestroyWindow(hwd);
						break;
					}
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
				EndDialog(hwd,0);
			}
		default:
			{
				return DefDlgProc(GetParent(hwd),code,wp,lp);
			}

	}
	return 0;
}

	//Procedura obs³ugi okna zarz¹dzania baz¹ faktur

LRESULT _stdcall Dlg8Proc(HWND hwd, int code, WPARAM wp, LPARAM lp)
{

	LVCOLUMN lvc;
	LVITEM lvi;
	int i,i1,ik,item,k;
	char zn[350],NIP[100],REG[100];
	bool bl,bl1;
	double db;
	WORD data;

	switch(code)
	{
		case WM_INITDIALOG:
			{
				CheckDlgButton(hwd,DLG8_RB4,BST_CHECKED);
				LVD8=GetDlgItem(hwd,DLG8_LV1);
				ListView_SetExtendedListViewStyle(LVD8,LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP|LVS_EX_SIMPLESELECT);
				is_dlg8=true;
				lvc.mask=LVCF_TEXT | LVCF_WIDTH;
				for(i=0;i<9;i++)
				{
					lvc.cx=LVD8_W[i];
					lvc.pszText=LVD8_Col[i];
					i1=ListView_InsertColumn(LVD8,i,&lvc);
				}
				break;
			}

		case WM_COMMAND:
			{
				if(wp==DLG8_B1)				//Przycisk zakoñcz
				{
					DestroyWindow(hwd);
					break;
				}
				if(wp==DLG8_B2)				//Przycisk Szukaj
				{
					if(FID) delete FID;
					FID=new int[HD_FB.CountF];
					item=-1;
					ListView_DeleteAllItems(LVD8);
					for(i=0;i<HD_FB.CountF;i++)
					{
						bl=HD_F[i].is_ex;
						ik=-1;
						memset(zn,0,350);
						GetWindowText(GetDlgItem(hwd,DLG8_E1),zn,350);
						if(zn[0]!=0 && bl)
						{
							if(strnicmp(zn,HD_F[i].numer,strlen(zn))!=0)
								bl=false;
						}
						if(bl)
						{
							memset(zn,0,350);
							GetWindowText(GetDlgItem(hwd,DLG8_E5),zn,350);
							if(zn[0]!=0)
							{
								data=(WORD)atoi(zn);
								if(HD_F[i].dzien<data) bl=false;
								else
								{
									memset(zn,0,350);
									GetWindowText(GetDlgItem(hwd,DLG8_E6),zn,350);
									if(zn[0]!=0)
									{
										data=(WORD)atoi(zn);
										if(HD_F[i].dzien>data) bl=false;
									}
								}
							}

							memset(zn,0,350);
							GetWindowText(GetDlgItem(hwd,DLG8_E7),zn,350);
							if(zn[0]!=0)
							{
								data=(WORD)atoi(zn);
								if(HD_F[i].miesiac<data) bl=false;
								else
								{
									memset(zn,0,350);
									GetWindowText(GetDlgItem(hwd,DLG8_E8),zn,350);
									if(zn[0]!=0)
									{
										data=(WORD)atoi(zn);
										if(HD_F[i].miesiac>data) bl=false;
									}
								}
							}
							memset(zn,0,350);
							GetWindowText(GetDlgItem(hwd,DLG8_E9),zn,350);
							if(zn[0]!=0)
							{
								data=(WORD)atoi(zn);
								if(HD_F[i].rok<data) bl=false;
								else
								{
									memset(zn,0,350);
									GetWindowText(GetDlgItem(hwd,DLG8_E10),zn,350);
									if(zn[0]!=0)
									{
										data=(WORD)atoi(zn);
										if(HD_F[i].rok>data) bl=false;
									}
								}
							}
						}
						if(bl)
						{
							if(IsDlgButtonChecked(hwd,DLG8_RB1) && HD_F[i].Zaplata!=0) bl=false;
								else
								if(IsDlgButtonChecked(hwd,DLG8_RB2) && HD_F[i].Zaplata<=0) bl=false;
									else
									if(IsDlgButtonChecked(hwd,DLG8_RB3) && HD_F[i].Zaplata>=0) bl=false;
									
						}
						if(bl)
						{
							if(IsDlgButtonChecked(hwd,DLG8_CH1)&& !HD_F[i].is_korekta) bl=false;	
						}
						if(bl)
						{
							memset(zn,0,350);
							memset(NIP,0,100);
							memset(REG,0,100);
							GetWindowText(GetDlgItem(hwd,DLG8_E2),zn,350);
							GetWindowText(GetDlgItem(hwd,DLG8_E3),NIP,100);
							GetWindowText(GetDlgItem(hwd,DLG8_E4),REG,100);
							if(zn[0]==0 && NIP[0]==0 && REG[0]==0) bl=true; 
							else
							{
								bl=true;
								for(i1=0;i1<HD_K.count;i1++)
								{
									if(KONTR[i1].IDK==HD_F[i].IDK)
									{
										ik=i1;
										if(strnicmp(zn,KONTR[i1].Nazwa,strlen(zn))!=0 && zn[0]!=0)
										{	
											bl=false;
											break;
										}else if(strnicmp(NIP,KONTR[i1].NIP,strlen(NIP))!=0 && NIP[0]!=0)
										{
											bl=false;
											break;
										}else if(strnicmp(REG,KONTR[i1].Regon,strlen(REG))!=0 && REG[0]!=0)
										{
											bl=false;
											break;
										}
										break;
									}
								}
							}
						}
						if(bl)
						{
							item++;
							lvi.mask=LVIF_TEXT;
							lvi.iSubItem=0;
							lvi.iItem=item;
							lvi.pszText=HD_F[i].numer;
							ListView_InsertItem(LVD8,&lvi);
							FID[item]=i;
							for(i1=0;i1<8;i1++)
							{
								memset(zn,0,350);
								if(i1==0)
								{
									if(ik!=-1) strcpy(zn,KONTR[ik].Nazwa);
									else
									{
										for(k=0;k<HD_K.count;k++)
										{
											if(KONTR[k].IDK==HD_F[i].IDK)
											{
												strcpy(zn,KONTR[k].Nazwa);
												break;
											}
										}
									}
								}
								else if(i1==1)
								{
									itoa((WORD)HD_F[i].dzien,zn,10);
									strcpy(zn+strlen(zn),"-");
									itoa((WORD)HD_F[i].miesiac,zn+strlen(zn),10);
									strcpy(zn+strlen(zn),"-");
									itoa((WORD)HD_F[i].rok,zn+strlen(zn),10);
								}else if(i1==2) dbl_str(HD_F[i].KW_N,zn,2,350); else if(i1==3) dbl_str(HD_F[i].KW_V,zn,2,350);
								else if(i1==4) dbl_str(HD_F[i].KW_B,zn,2,350); else 
									if(i1==5) 
									{
										dbl_str(HD_F[i].KW_B,zn,2,10);
										db=atof(zn);
										dbl_str(db-HD_F[i].Zaplata,zn,2,350);
									}
									else if(i1==6)dbl_str(HD_F[i].Zaplata,zn,2,350);
									else if(i1==7) sprintf(zn,"%d-%d-%d",HD_F[i].ter_plat.wDay,HD_F[i].ter_plat.wMonth,HD_F[i].ter_plat.wYear);
									ListView_SetItemText(LVD8,item,i1+1,zn);
							}

							
						
						}
					}
					break;
				}
				if(wp==DLG8_B3)
				{
					i=ListView_GetSelectionMark(LVD8);
					if(i<0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie zaznaczono faktury");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					fid=FID[i];
					DialogBox(hst,MAKEINTRESOURCE(ID_DLG_9),hwd,(DLGPROC)&Dlg9Proc);
					SetFocus(hwd);
					SendMessage(hwd,WM_COMMAND,(WPARAM)DLG8_B2,0);
					break;
				}
				if(wp==DLG8_B4)
				{
					i=ListView_GetSelectionMark(LVD8);
					if(i<0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie zaznaczono faktury");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					sprintf(Query_Text,"Czy napewno chcesz usun¹æ fakturê z bazy ?");
					DialogBox(hst,MAKEINTRESOURCE(DLG_Q),hwd,(DLGPROC)&DLGQProc);
					SetFocus(hwd);
					if(!is_ok) break;
					fid=FID[i];
					Usun_Fakt(fid);
					SendMessage(hwd,WM_COMMAND,(WPARAM)DLG8_B2,0);
					break;
				}
				break;
			}

		case WM_CLOSE:
			{
				DestroyWindow(hwd);
			}
		case WM_DESTROY:
			{
				is_dlg8=false;
				EndDialog(hwd,0);
			}
	}
	return 0;

}


	//Procedura obs³ugi okna zarz¹dzania faktur¹ VAT

LRESULT _stdcall Dlg9Proc(HWND hwd, int code, WPARAM wp, LPARAM lp)
{
	LVCOLUMN lvc;
	LVITEM lvi;
	int i,j,resz,poz,indeks;
	Fakt_Vat fvat;
	fstream pl;
	char zn[350];
	double db,db1;

	switch(code)
	{
		case WM_INITDIALOG:
			{
				is_Korekta=false;
				for(i=0;i<HD_K.count;i++)
				{
					if(HD_F[fid].IDK==KONTR[i].IDK)
					{
						id_k=i;
						memset(zn,0,350);
						strcpy(zn,"NAZWA: ");
						strcpy(zn+strlen(zn),KONTR[i].Nazwa);
						zn[strlen(zn)]=13;
						zn[strlen(zn)]=10;
						strcpy(zn+strlen(zn),"ADRES: ");
						strcpy(zn+strlen(zn),KONTR[i].Adres);
						strcpy(zn+strlen(zn),"  ");
						strcpy(zn+strlen(zn),KONTR[i].KodPocz);
						strcpy(zn+strlen(zn),"  ");
						strcpy(zn+strlen(zn),KONTR[i].Miasto);
						strcpy(zn+strlen(zn),"  ");
						strcpy(zn+strlen(zn),KONTR[i].Kraj);
						zn[strlen(zn)]=13;
						zn[strlen(zn)]=10;
						strcpy(zn+strlen(zn),"NIP: ");
						strcpy(zn+strlen(zn),KONTR[i].NIP);
						zn[strlen(zn)]=13;
						zn[strlen(zn)]=10;
						strcpy(zn+strlen(zn),"REGON: ");
						strcpy(zn+strlen(zn),KONTR[i].Regon);
						SetWindowText(GetDlgItem(hwd,DLG9_E1),zn);
						SendMessage(LVD9,WM_LBUTTONDOWN,0,0);
						SendMessage(LVD9,WM_LBUTTONUP,0,0);
						break;
					}

				}
				SetWindowText(GetDlgItem(hwd,DLG9_E2),HD_F[fid].numer);
				LVD9=GetDlgItem(hwd,DLG9_LV1);
				ListView_SetExtendedListViewStyle(LVD9,LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_INFOTIP | LVS_EX_AUTOSIZECOLUMNS);
				lvc.mask=LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH;
				lvc.iSubItem=0;
				for(i=0;i<12;i++)
				{
					lvc.pszText=VAT_Col[i];
					lvc.cx=LVD4_W[i];
					ListView_InsertColumn(LVD9,i,&lvc);
				}
				memset(zn,0,350);
				i=(fid+1)/Max_F;
				resz=(fid+1)%Max_F;
				if (F_Vat!=NULL) delete F_Vat;
				F_Vat=new Fakt_Vat[HD_F[fid].count];
				Vat_C=HD_F[fid].count;
				if(resz!=0)i++;
				sprintf(zn,"%sDBF",path);
				//strcpy(zn,"Data\\DBF");
				itoa(i,zn+strlen(zn),10);
				strcpy(zn+strlen(zn),".amb");
				poz=0;
				if(resz!=0 && resz!=1)
				{
					indeks=fid-resz;
					indeks++;
					for(i=indeks;i<fid;i++)
					{
						poz=poz+HD_F[i].count*sizeof(Fakt_Vat);
						poz=poz+sizeof(Header_F);
					}

				}else
					if(resz==0)
					{
						poz=HD_F[fid].count*sizeof(Fakt_Vat);
					}
				pl.open(zn,ios_base::in|ios_base::out|ios_base::binary);
				if(resz==0)  pl.seekg(-poz,ios_base::end); else
				{
					memset(path1,0,300);
					sprintf(path1,"%sDBF1.amb",path);
					if(strcmp(zn,path1)==0)
					{
						pl.seekg(sizeof(Header_FB),ios_base::beg);
					}
					if(resz!=1) pl.seekg(poz,ios_base::cur);
					pl.seekg(sizeof(Header_F),ios_base::cur);
				}
				for(i=0;i<HD_F[fid].count;i++)
				{
					pl.read((char*)&fvat,sizeof(Fakt_Vat));
					F_Vat[i]=fvat;	
					memset(zn,0,350);
					lvi.mask=LVIF_TEXT;
					lvi.iSubItem=0;
					lvi.iItem=i;
					itoa(fvat.LP,zn,10);
					lvi.pszText=zn;
					ListView_InsertItem(LVD9,&lvi);
					memset(zn,0,350);
					for(j=0;j<11;j++)
					{
						if(j==0)strcpy(zn,fvat.Nazwa); else if(j==1) itoa(fvat.PKWiU,zn,10); else if(j==2) itoa(fvat.ilosc,zn,10); else
							if(j==3) strcpy(zn,fvat.JM); else if(j==4) dbl_str(fvat.Cena_Netto,zn,2,350); else if(j==5) dbl_str(fvat.Rabat,zn,2,350); else
								if(j==6) dbl_str(fvat.Cena_Netto2,zn,2,350); else if(j==7) dbl_str(fvat.VAT,zn,2,350); else 
									if(j==8) dbl_str(fvat.KW_Netto,zn,2,350); else if(j==9) dbl_str(fvat.KW_VAT,zn,2,350); else 
										if(j==10) dbl_str(fvat.KW_Brutto,zn,2,350);
						ListView_SetItemText(LVD9,i,j+1,zn);

							
					}

				}
				SetProp(GetDlgItem(hwd,DLG9_E3),"PROC",(HANDLE)GetWindowLong(GetDlgItem(hwd,DLG9_E3),GWL_WNDPROC));
				SetProp(GetDlgItem(hwd,DLG9_E3),"BOOL",(HANDLE)false);
				SetWindowLong(GetDlgItem(hwd,DLG9_E3),GWL_WNDPROC,(LONG)WndEProc);
				memset(zn,0,350);
				dbl_str(HD_F[fid].KW_B-HD_F[fid].Zaplata,zn,2,350);
				SetWindowText(GetDlgItem(hwd,DLG9_E3),zn);
				if(pl) pl.close();
				break;
			}
		case  WM_ACTIVATE:
				{
					SetFocus(LVD9);
					break;
				}
		case WM_COMMAND:
			{
				if(wp==DLG9_B1)					//Zamknij
				{
					DestroyWindow(hwd);
					break;
				}
				if(wp==DLG9_B2)					//Drukuj
				{
					Print_Vat(HD_F[fid],F_Vat,hwd,hst,false);	
					SetFocus(hwd);
					break;
				}
				if(wp==DLG9_B3)					//Korekta
				{
					is_Korekta=true;
					DialogBox(hst,MAKEINTRESOURCE(ID_DLG_4),hwd,(DLGPROC)&Dlg4Proc);
					if(is_Korekta) DestroyWindow(hwd);else SetFocus(hwd);
					is_Korekta=false;
					break;
				}
				if(wp==DLG9_B4)			//zapisz zmiany
				{
					sprintf(Query_Text,"Czy napewno chcesz zapisaæ zmiany w  fakturzer Vat ?");
					DialogBox(hst,MAKEINTRESOURCE(DLG_Q),hwd,(DLGPROC)&DLGQProc);
					SetFocus(hwd);
					if(!is_ok) break;
					memset(zn,0,350);
					GetWindowText(GetDlgItem(hwd,DLG9_E3),zn,350);
					db=atof(zn);
					memset(zn,0,350);
					dbl_str(HD_F[fid].KW_B,zn,2,350);
					db1=atof(zn);
					HD_F[fid].Zaplata=db1-db;
					Save_Fakt(fid);
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
				if(F_Vat!=NULL) delete F_Vat;
				F_Vat=NULL;
				is_Korekta=false;
				EndDialog(hwd,0);
			}
	}
	return 0;

}



LRESULT _stdcall Dlg10Proc(HWND hwd, int code, WPARAM wp, LPARAM lp)
{
	FIRMA FR;
	fstream pf;
	char zn[12];
	LONGLONG pos;
	int i;

	switch(code)
	{
		case WM_INITDIALOG:
			{
				if(!FRM._is) break;
				SetWindowText(GetDlgItem(hwd,DLG10_E1),FRM.Nazwa);
				SetWindowText(GetDlgItem(hwd,DLG10_E2),FRM.Adres);
				memset(zn,0,12);
				i=0;
				while(FRM.Kod_Pocz[i]!='-')
				{
					if(FRM.Kod_Pocz[i]!='-')zn[i]=FRM.Kod_Pocz[i]; 
					i++;
				}
				SetWindowText(GetDlgItem(hwd,DLG10_E3),zn);
				memset(zn,0,12);
				memset(zn,0,12);
				strcpy(zn,FRM.Kod_Pocz+i+1);
				SetWindowText(GetDlgItem(hwd,DLG10_E4),zn);
				SetWindowText(GetDlgItem(hwd,DLG10_E5),FRM.Miasto);
				SetWindowText(GetDlgItem(hwd,DLG10_E6),FRM.Kraj);
				SetWindowText(GetDlgItem(hwd,DLG10_E7),FRM.NIP);
				SetWindowText(GetDlgItem(hwd,DLG10_E8),FRM.Regon);
				SetWindowText(GetDlgItem(hwd,DLG10_E9),FRM.Tel);
				EnableWindow(GetDlgItem(hwd,DLG10_B2),false);
				break;
			}
		case WM_COMMAND:
			{
				if(HIWORD(wp)==EN_CHANGE)
				{
					EnableWindow(GetDlgItem(hwd,DLG10_B2),true);
					break;
				}
				if(wp==DLG10_B1)			//Zamknij
				{
					DestroyWindow(hwd);
					break;
				}
				if(wp==DLG10_B2)			//Zapisz
				{
					memset(&FR,0,sizeof(FIRMA));
					GetWindowText(GetDlgItem(hwd,DLG10_E1),FR.Nazwa,150);
					if(FR.Nazwa[0]==0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Pola oznaczone s¹ wymagane");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					GetWindowText(GetDlgItem(hwd,DLG10_E2),FR.Adres,150);
					if(FR.Adres[0]==0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Pola oznaczone s¹ wymagane");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					GetWindowText(GetDlgItem(hwd,DLG10_E3),FR.Kod_Pocz,12);
					if(FR.Kod_Pocz[0]==0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Pola oznaczone s¹ wymagane");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					memset(zn,0,10);
					GetWindowText(GetDlgItem(hwd,DLG10_E4),zn,12);
					if(zn[0]==0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Pola oznaczone s¹ wymagane");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					strcpy(FR.Kod_Pocz+strlen(FR.Kod_Pocz),"-");
					strcpy(FR.Kod_Pocz+strlen(FR.Kod_Pocz),zn);
					GetWindowText(GetDlgItem(hwd,DLG10_E5),FR.Miasto,150);
					if(FR.Miasto[0]==0)
					{
						memset(Err_Text,0,150);
						sprintf(Err_Text,"Pola oznaczone s¹ wymagane");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					GetWindowText(GetDlgItem(hwd,DLG10_E6),FR.Kraj,150);
					if(FR.Kraj[0]==0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Pola oznaczone s¹ wymagane");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					GetWindowText(GetDlgItem(hwd,DLG10_E7),FR.NIP,150);
					if(FR.NIP[0]==0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Pola oznaczone s¹ wymagane");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					GetWindowText(GetDlgItem(hwd,DLG10_E8),FR.Regon,150);
					if(FR.Regon[0]==0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Pola oznaczone s¹ wymagane");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					GetWindowText(GetDlgItem(hwd,DLG10_E9),FR.Tel,150);
					FR._is=true;
					pf.open("DAM.dll",ios_base::out|ios_base::in|ios_base::binary);
					if(!pf)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Biblioteka uleg³a usuniêciu\nSkontaktuj siê z Autorem programu, albo przeinstaluj program");
						DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
						SetFocus(hwd);
						break;
					}
					find_str("DAM.dll",&pos,"ADAPRIM_A&P",11);
					pos==-1;
					pf.seekg(pos+16,ios_base::beg);
					if(pos>0)
					{
						pf.write((char*)&FR,sizeof(FIRMA));
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Dane zosta³y zapisane");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
					}
					pf.close();
					FRM=FR;
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
				is_dlg1=false;
				EndDialog(hwd,0);
				break;
			}
		default: return DefDlgProc(GetParent(hwd),code,wp,lp);
	}
	return 0;
}



LRESULT _stdcall Dlg12Proc(HWND hwd, int code, WPARAM wp, LPARAM lp)
{
	int i;
	char zn[100];
	Prz_Tow pt;
	bool bl;
	double d,il;
	SYSTEMTIME tm;

	switch(code)
	{
		case WM_INITDIALOG:
			{
				SetWindowText(GetDlgItem(hwd,DLG12_T1),ART[Tid].Nazwa);
				CheckDlgButton(hwd,DLG12_RB1,BST_CHECKED);
				ComboBox_AddString(GetDlgItem(hwd,DLG12_CB1),"Cena Netto");
				ComboBox_AddString(GetDlgItem(hwd,DLG12_CB1),"Cena Brutto");
				ComboBox_AddString(GetDlgItem(hwd,DLG12_CB1),"Kwota Netto Faktury(stany siê nie zmieniaj¹)");
				ComboBox_AddString(GetDlgItem(hwd,DLG12_CB1),"Kwota Brutto Faktury(stany siê nie zmieniaj¹)");
				ComboBox_SetCurSel(GetDlgItem(hwd,DLG12_CB1),0);
				SetProp(GetDlgItem(hwd,DLG12_E2),"PROC",(HANDLE)GetWindowLong(GetDlgItem(hwd,DLG12_E2),GWL_WNDPROC));
				SetProp(GetDlgItem(hwd,DLG12_E2),"BOOL",(HANDLE)false);
				SetWindowLong(GetDlgItem(hwd,DLG12_E2),GWL_WNDPROC,(LONG)WndEProc);
				SetProp(GetDlgItem(hwd,DLG12_E1),"PROC",(HANDLE)GetWindowLong(GetDlgItem(hwd,DLG12_E1),GWL_WNDPROC));
				SetProp(GetDlgItem(hwd,DLG12_E1),"BOOL",(HANDLE)false);
				SetWindowLong(GetDlgItem(hwd,DLG12_E1),GWL_WNDPROC,(LONG)WndEProc);
								
				break;
			}
		case WM_COMMAND:
			{
				if(wp==DLG12_B1)				//Przycisk ZatwierdŸ
				{
					memset(zn,0,100);
					bl=false;
					GetWindowText(GetDlgItem(hwd,DLG12_E2),zn,100);
					if(zn[0]==0)
					{
						memset(Query_Text,0,350);
						sprintf(Query_Text,"Jeœli nie podasz ceny towaru, to statystyki sprzeda¿y mog¹ byæ niezgodne z rzeczywstymi stanami sprzeda¿y\nCzy chcesz kontyn³owaæ ?");
						DialogBox(hst,MAKEINTRESOURCE(DLG_Q),hwd,(DLGPROC)&DLGQProc);
						SetFocus(hwd);
						if(!is_ok)
						break;
					}
					if(zn[0]!=0)d=atof(zn); else d=0;
					memset(zn,0,100);
					GetWindowText(GetDlgItem(hwd,DLG12_E1),zn,100);
					i=ComboBox_GetCurSel(GetDlgItem(hwd,DLG12_CB1));
					if(zn[0]==0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Musisz podaæ iloœæ towaru do przyjêcia");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					il=atof(zn);
					GetSystemTime(&tm);
					pt.miesiac=(BYTE)tm.wMonth;
					pt.rok=tm.wYear;
					if(i==0 || i==1)
					{
						if(IsDlgButtonChecked(hwd,DLG12_RB1))ART[Tid].Stan=ART[Tid].Stan+(float)il; else ART[Tid].Stan=ART[Tid].Stan-(float)il;
					}
					if(i==0)pt.cena_n=il*d;
					else if(i==1)
					{
						d=d/1.23;
						dbl_str(d,zn,2,100);
						d=atof(zn);
						pt.cena_n=d*il;
					}else if(i==2) pt.cena_n=d;
					else if(i==3) pt.cena_n=d/1.23;
					if(IsDlgButtonChecked(hwd,DLG12_RB2)) pt.cena_n=-(pt.cena_n);
					Save_AR(&ART[Tid]);
					Save_TW(pt,ART[Tid].VAT);
					DestroyWindow(hwd);
					break;
				}
				
				if(wp==DLG12_B2)				//Przycisk Anuluj
				{
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
				EndDialog(hwd,0);
				break;
			}
		default: return DefDlgProc(GetParent(hwd),code,wp,lp);
	}
	return 0;
}

HWND SP;

LRESULT _stdcall Dlg13Proc(HWND hwd, int code , WPARAM wp, LPARAM lp)
{
	char con_str[300];
	char txt[350];
	fstream pl;
	HANDLE hn;
	HMODULE hm;
	WIN32_FIND_DATA fdt;
	static KASA_ K;
	int i,licz,kod;
	char zn;

	switch(code)
	{
		
		case WM_INITDIALOG:
			{
				SetWindowText(GetDlgItem(hwd,DLG13_E1),"1");
				SetWindowText(GetDlgItem(hwd,DLG13_E6),"10");
				SetWindowText(GetDlgItem(hwd,DLG13_E3),"10");
				SetWindowText(GetDlgItem(hwd,DLG13_E2),"3");
				SetWindowText(GetDlgItem(hwd,DLG13_E8),"1001");
				SetWindowText(GetDlgItem(hwd,DLG13_RB18),"8");
				SendMessage(GetDlgItem(hwd,DLG13_SB1),UDM_SETBUDDY,(WPARAM)GetDlgItem(hwd,DLG13_E1),0);
				SendMessage(GetDlgItem(hwd,DLG13_SB1),UDM_SETRANGE32,(WPARAM)1,(LPARAM)2147483647);
				SendMessage(GetDlgItem(hwd,DLG13_SB2),UDM_SETBUDDY,(WPARAM)GetDlgItem(hwd,DLG13_E2),0);
				SendMessage(GetDlgItem(hwd,DLG13_SB2),UDM_SETRANGE32,(WPARAM)1,(LPARAM)2147483647);
				SendMessage(GetDlgItem(hwd,DLG13_SB3),UDM_SETBUDDY,(WPARAM)GetDlgItem(hwd,DLG13_E6),0);
				SendMessage(GetDlgItem(hwd,DLG13_SB3),UDM_SETRANGE32,(WPARAM)1,(LPARAM)2147483647);
				SendMessage(GetDlgItem(hwd,DLG13_SB4),UDM_SETBUDDY,(WPARAM)GetDlgItem(hwd,DLG13_E3),0);
				SendMessage(GetDlgItem(hwd,DLG13_SB4),UDM_SETRANGE32,(WPARAM)1,(LPARAM)2147483647);
				SendMessage(GetDlgItem(hwd,DLG13_SB5),UDM_SETBUDDY,(WPARAM)GetDlgItem(hwd,DLG13_E8),0);
				SendMessage(GetDlgItem(hwd,DLG13_SB5),UDM_SETRANGE32,(WPARAM)1,(LPARAM)2147483647);
				ComboBox_AddString(GetDlgItem(hwd,DLG13_CB1),"PSTN Prolnik/Action Tec/GVC400");
				ComboBox_AddString(GetDlgItem(hwd,DLG13_CB1),"GSM Siemens");
				ComboBox_AddString(GetDlgItem(hwd,DLG13_CB1),"Inny");
				ComboBox_SetCurSel(GetDlgItem(hwd,DLG13_CB1),2);
				if(Kas_id==-1)
				{
					EnableWindow(GetDlgItem(hwd,DLG13_B3),false);
					CheckDlgButton(hwd,DLG13_RB5,BST_CHECKED);
					CheckDlgButton(hwd,DLG13_RB1,BST_CHECKED);
					CheckDlgButton(hwd,DLG13_RB11,BST_CHECKED);
					CheckDlgButton(hwd,DLG13_RB19,BST_CHECKED);
				}else
				{
					K=KS[Kas_id];
					if(K.Szybk==9600)CheckDlgButton(hwd,DLG13_RB1,BST_CHECKED);
						else if(K.Szybk==19200)CheckDlgButton(hwd,DLG13_RB2,BST_CHECKED);
							else if(K.Szybk==28800)CheckDlgButton(hwd,DLG13_RB3,BST_CHECKED);
								else if(K.Szybk==57600)CheckDlgButton(hwd,DLG13_RB4,BST_CHECKED);
					memset(txt,0,350);
					itoa(K.Com,txt,10);
					SetWindowText(GetDlgItem(hwd,DLG13_E1),txt);
					CheckDlgButton(hwd,DLG13_RB5,BST_CHECKED);
					SetWindowText(GetDlgItem(hwd,DLG13_E9),K.nazwa);
					if(K.rodz_pol==1 || K.rodz_pol==2 || K.rodz_pol==3 || K.rodz_pol==4 || K.rodz_pol==5)
					{
						if(K.rodz_pol==1 ) {CheckDlgButton(hwd,DLG13_RB6,BST_CHECKED);SendMessage(hwd,WM_COMMAND,(WPARAM)DLG13_RB6,0);CheckDlgButton(hwd,DLG13_RB11,BST_UNCHECKED);}
							else if(K.rodz_pol==2 ) {CheckDlgButton(hwd,DLG13_RB7,BST_CHECKED);SendMessage(hwd,WM_COMMAND,(WPARAM)DLG13_RB7,0);CheckDlgButton(hwd,DLG13_RB11,BST_UNCHECKED);}
								else if (K.rodz_pol==3 ) {CheckDlgButton(hwd,DLG13_RB8,BST_CHECKED);SendMessage(hwd,WM_COMMAND,(WPARAM)DLG13_RB8,0);CheckDlgButton(hwd,DLG13_RB11,BST_UNCHECKED);}
									else if(K.rodz_pol==4 ) {CheckDlgButton(hwd,DLG13_RB9,BST_CHECKED);SendMessage(hwd,WM_COMMAND,(WPARAM)DLG13_RB9,0);CheckDlgButton(hwd,DLG13_RB11,BST_UNCHECKED);}
										else if (K.rodz_pol==5 ) {CheckDlgButton(hwd,DLG13_RB10,BST_CHECKED);SendMessage(hwd,WM_COMMAND,(WPARAM)DLG13_RB10,0);CheckDlgButton(hwd,DLG13_RB11,BST_UNCHECKED);}

						if(K.kanal==1) CheckDlgButton(hwd,DLG13_RB11,BST_CHECKED);
							else if(K.kanal==2) CheckDlgButton(hwd,DLG13_RB12,BST_CHECKED);
								else if(K.kanal==3) CheckDlgButton(hwd,DLG13_RB13,BST_CHECKED);
									else if(K.kanal==4) CheckDlgButton(hwd,DLG13_RB14,BST_CHECKED);
										else if(K.kanal==5) CheckDlgButton(hwd,DLG13_RB15,BST_CHECKED);
											else if(K.kanal==6) CheckDlgButton(hwd,DLG13_RB16,BST_CHECKED);
												else if(K.kanal==7) CheckDlgButton(hwd,DLG13_RB17,BST_CHECKED);
													else if(K.kanal==8) CheckDlgButton(hwd,DLG13_RB18,BST_CHECKED);
					}
					if(K.rodz_pol==2)
					{
						SetWindowText(GetDlgItem(hwd,DLG13_E4),K.tel);
						SetWindowText(GetDlgItem(hwd,DLG13_E5),K.haslo);
						if(K.PT==84) CheckDlgButton(hwd,DLG13_RB19,BST_CHECKED); else CheckDlgButton(hwd,DLG13_RB20,BST_CHECKED);
						memset(txt,0,350);
						itoa(K.AT,txt,10);
						SetWindowText(GetDlgItem(hwd,DLG13_E3),txt);
						memset(txt,0,350);
						itoa(K.ret,txt,10);
						SetWindowText(GetDlgItem(hwd,DLG13_E2),txt);
						memset(txt,0,350);
						itoa(K.timeout,txt,10);
						SetWindowText(GetDlgItem(hwd,DLG13_E6),txt);

					}
					if(K.rodz_pol==5)
					{
						SetWindowText(GetDlgItem(hwd,DLG13_E5),K.haslo);
						SetWindowText(GetDlgItem(hwd,DLG13_E7),K.IP);
						memset(txt,0,350);
						itoa(K.ret,txt,10);
						SetWindowText(GetDlgItem(hwd,DLG13_E2),txt);
						memset(txt,0,350);
						itoa(K.timeout,txt,10);
						SetWindowText(GetDlgItem(hwd,DLG13_E6),txt);
					}
					EnableWindow(GetDlgItem(hwd,DLG13_B3),true);
				}	
				break;
			}
		
		case WM_COMMAND:
			{

				if(HIWORD(wp)==DLG13_SB1)
				{
					break;
				}
				if(wp==DLG13_B1) //Testuj po³¹czenie
				{
					memset(&K,0,sizeof(KASA_));
					K.is_exist=true;
					memset(con_str,0,300);
					memset(txt,0,150);
					GetWindowText(GetDlgItem(hwd,DLG13_E1),txt,350);
					K.Com=atoi(txt);
					if(IsDlgButtonChecked(hwd,DLG13_RB1))K.Szybk=9600; else
						if(IsDlgButtonChecked(hwd,DLG13_RB2))K.Szybk=19200; else
							if(IsDlgButtonChecked(hwd,DLG13_RB3))K.Szybk=28800; else
								if(IsDlgButtonChecked(hwd,DLG13_RB4))K.Szybk=57600; 
						
					if(IsDlgButtonChecked(hwd,DLG13_RB5))K.rodz_pol=0; else
						if(IsDlgButtonChecked(hwd,DLG13_RB6))K.rodz_pol=1; else
							if(IsDlgButtonChecked(hwd,DLG13_RB7))K.rodz_pol=2; else
								if(IsDlgButtonChecked(hwd,DLG13_RB8))K.rodz_pol=3; else
									if(IsDlgButtonChecked(hwd,DLG13_RB9))K.rodz_pol=4; else
										if(IsDlgButtonChecked(hwd,DLG13_RB10))K.rodz_pol=5; 
					if(IsDlgButtonChecked(hwd,DLG13_RB5))K.kanal=1; else
					{
						if(IsDlgButtonChecked(hwd,DLG13_RB11))K.kanal=1; else
							if(IsDlgButtonChecked(hwd,DLG13_RB12))K.kanal=2; else
								if(IsDlgButtonChecked(hwd,DLG13_RB13))K.kanal=3; else
									if(IsDlgButtonChecked(hwd,DLG13_RB14))K.kanal=4; else
										if(IsDlgButtonChecked(hwd,DLG13_RB15))K.kanal=5; else
											if(IsDlgButtonChecked(hwd,DLG13_RB16))K.kanal=6; else
												if(IsDlgButtonChecked(hwd,DLG13_RB17))K.kanal=7; else
													if(IsDlgButtonChecked(hwd,DLG13_RB18))K.kanal=8;
					}
					K.timeout=5;

					strcpy(K.RU,"AnyString");
					memset(txt,0,150);
					GetWindowText(GetDlgItem(hwd,DLG13_E9),txt,350);
					if(txt[0]==0)strcpy(K.RU,"Elzab"); else strcpy(K.RU,txt);
					memset(txt,0,350);
					if(IsDlgButtonChecked(hwd,DLG13_CB2)) strcpy(txt,"STX"); else strcpy(txt,"MUX");
					sprintf(con_str,"$%d\tCOM%d:%d:%s%d:%d\t%d\t%s",1,K.Com,K.Szybk,txt,K.rodz_pol,K.kanal,K.timeout,K.RU);
					if(IsDlgButtonChecked(hwd,DLG13_RB7))
					{
						if(IsDlgButtonChecked(hwd,DLG13_RB19))K.PT='T'; else K.PT='P';
						GetWindowText(GetDlgItem(hwd,DLG13_E4),K.tel,50);
						GetWindowText(GetDlgItem(hwd,DLG13_E5),K.haslo,50);
						memset(txt,0,350);
						GetWindowText(GetDlgItem(hwd,DLG13_E3),txt,150);
						K.AT=atoi(txt);
						memset(txt,0,350);
						GetWindowText(GetDlgItem(hwd,DLG13_E6),txt,150);
						K.T1=atoi(txt);
						memset(txt,0,350);
						GetWindowText(GetDlgItem(hwd,DLG13_E2),txt,150);
						K.ret=atoi(txt);
			
						sprintf(con_str+strlen(con_str),"\t%c%s:%s:%d:%d:%d",(char)K.PT,K.tel,K.haslo,K.AT,K.T1,K.ret);
					}else if(IsDlgButtonChecked(hwd,DLG13_RB10))
					{
						GetWindowText(GetDlgItem(hwd,DLG13_E7),K.IP,50);
						memset(txt,0,350);
						GetWindowText(GetDlgItem(hwd,DLG13_E8),txt,150);
						K.port=atoi(txt);
						GetWindowText(GetDlgItem(hwd,DLG13_E5),K.haslo,50);
						memset(txt,0,350);
						GetWindowText(GetDlgItem(hwd,DLG13_E6),txt,150);
						K.T1=atoi(txt);
						memset(txt,0,350);
						GetWindowText(GetDlgItem(hwd,DLG13_E2),txt,150);
						K.ret=atoi(txt);
						sprintf(con_str+strlen(con_str),"\tAnyString:3001:%s:%d:%s:%d:%d",K.IP,K.port,K.haslo,K.T1,K.ret);
					}
					sprintf(K.end_str,"ADAPRIM_4321");
					pl.open("KONFIG.txt",ios_base::in|ios_base::out|ios_base::trunc);
					if(!pl.is_open())
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie mo¿na utworzyæ pliku konfiguracyjnego potrzebnego do po³¹czenia siê z kas¹ fiskaln¹");
						DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
						SetFocus(hwd);
					}
					pl.write((char*)con_str,strlen(con_str));
					pl.close();
					pl.open("Config/pin.in",ios_base::in|ios_base::out|ios_base::trunc);
					if(!pl.is_open())
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie mo¿na utworzyæ pliku wejœcia dla procedury");
						DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
						SetFocus(hwd);
						break;
					}
					pl.write((char*)"#1\n#\n#",6);
					pl.close();
					pl.open("Config/pin.out",ios_base::in|ios_base::out|ios_base::trunc);
					if(!pl.is_open())
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie mo¿na utworzyæ pliku wyjœcia dla procedury");
						DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
						SetFocus(hwd);
						DeleteFile("Config/pin.in");
						break;
					}
					pl.close();
					
					if(IsDlgButtonChecked(hwd,DLG13_RB7)) (*_ModStart)("Config/pin.in");
					else
					//(*_OBajty)("Config/pin.in","Config/pin.out");
					(*_ONrKasy)("Config/pin.in","Config/pin.out");
					hn=FindFirstFile("RAPORT.TXT",&fdt);
					if(hn==INVALID_HANDLE_VALUE)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie mo¿na odnaleŸæ pliku raportu");
						DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
						DeleteFile("Config/pin.in");
						DeleteFile("Config/pin.out");
						SetFocus(hwd);
						
					}else
					{
						pl.open("RAPORT.TXT",ios_base::in);
						if(!pl.is_open())
						{
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Nie mo¿na otworzyæ pliku raportu");
							DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
							SetFocus(hwd);
							DeleteFile("Config/pin.in");
							DeleteFile("Config/pin.out");
							break;
						}
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

								if(kod==0)
								{
									i=-1;
									memset(txt,0,350);
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
												if(zn!='(') strncpy(txt+i,&zn,1); 
												if(zn=='(' || zn==10) 
												{
													zn=-1;
													if(txt[strlen(txt)-1]==32 || txt[strlen(txt)-1]=='.') txt[strlen(txt)-1]=0;
												}
											}while(zn!=-1 && licz<fdt.nFileSizeLow);
										}
									}while(zn!=-1 && licz<fdt.nFileSizeLow);
								}
							}
						}while(licz<fdt.nFileSizeLow && zn!=-1 );
						pl.close();
					}
					
					if(kod==0)
					{
						strcpy(K.nazwa,txt);
						hn=FindFirstFile("Config/pin.out",&fdt);
						if(hn==INVALID_HANDLE_VALUE)
						{
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Nie mo¿na odnaleŸæ pliku danych wyjœciowych z kasy fiskalnej");
							DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
							SetFocus(hwd);
							DeleteFile("Config/pin.in");
							DeleteFile("Config/pin.out");
							break;		
						}

						pl.open("Config/pin.out",ios_base::in);
						pl.seekg(0,ios_base::beg);
						if(!pl.is_open())
						{
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Nie mo¿na otworzyæ pliku dajych wyjœciowych z kasy fiskalnej");
							DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
							SetFocus(hwd);
							DeleteFile("Config/pin.in");
							DeleteFile("Config/pin.out");
							break;
						}
						licz=0;
						zn=0;
						while(licz<fdt.nFileSizeLow && zn!='$')
						{
							zn=pl.get();
							licz++;
						}
						if(zn=='$' && licz<fdt.nFileSizeLow)
						{
							memset(txt,0,350);
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
							strcpy(K.numer,txt);
						}
						pl.close();
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nawi¹zano po³¹czenie z kas¹ fiskaln¹\n%s",K.nazwa);
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetWindowText(GetDlgItem(hwd,DLG13_E9),K.nazwa);
						EnableWindow(GetDlgItem(hwd,DLG13_B3),true);
						SetFocus(hwd);
					}else
					{
						memset(Err_Text,0,350);
						LoadString(hst,kod+1000,txt,350);
						sprintf(Err_Text,"Nie mo¿na wykonaæ operacji\n%s",txt);
						if(IsDlgButtonChecked(hwd,DLG13_RB7)&& kod==16) sprintf(Err_Text+strlen(Err_Text),"\nSprawŸ czy poda³eœ poprawne has³o");
						DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
						EnableWindow(GetDlgItem(hwd,DLG13_B3),true);
						SetFocus(hwd);
					}
					break;
				}

				if(wp==DLG13_B3)	//Przycisk Zapisz Parametry
				{
				
					if(KS==NULL) 
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie mo¿na za³adowaæ tablicy kas z pliku fisk.dll",txt);
						DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
						SetFocus(hwd);
						break;
					}
					if(Kas_id!=-1)
					{
						memset(txt,0,350);
						GetWindowText(GetDlgItem(hwd,DLG13_E9),txt,50);
						if(txt[0]==0)sprintf(K.nazwa,"Kasa_%d",Kas_id+1); else strcpy(K.nazwa,txt);
						//strcpy(K.numer,KS[Kas_id].numer);
						KS[Kas_id]=K;
						Save_KS(true);
						memset(Query_Text,0,350);
						sprintf(Query_Text,"Zapisano kasê w bazie danych\nCzy chcesz ustawiæ j¹ jako kasê domyœln¹ podczas komunikacji z komputerem?");
						DialogBox(hst,MAKEINTRESOURCE(DLG_Q),hwd,(DLGPROC)&DLGQProc);
						SetFocus(hwd);
						if(is_ok)
						{
							Default = Kas_id;
							Save_KS(false);
							
						}
						break;
					}
					if(Count_Kas>=MAX_Kas)
					{
						memset(Query_Text,0,350);
						sprintf(Query_Text,"Zapisano ju¿ maksymaln¹ iloœæ kas\nCzy chcesz zast¹piæ wybran¹ kasê fiskaln¹ ?");
						is_ok=false;
						DialogBox(hst,MAKEINTRESOURCE(DLG_Q),hwd,(DLGPROC)&DLGQProc);
						SetFocus(hwd);
						if(is_ok)
						{
							DialogBox(hst,MAKEINTRESOURCE(ID_DLG_14),hwd,(DLGPROC)&DLG14Proc);
							SetFocus(hwd);
							if(Kas_id!=-1)
							{
								i=Kas_id;
								itoa(Kas_id+1,K.numer,10);
								memset(txt,0,350);
								GetWindowText(GetDlgItem(hwd,DLG13_E9),txt,50);
								if(txt[0]==0)sprintf(K.nazwa,"Kasa_%d",i+1); else strcpy(K.nazwa,txt);
								KS[Kas_id]=K;
								Save_KS(true);
								memset(Query_Text,0,350);
								sprintf(Query_Text,"Zapisano kasê w bazie danych\nCzy chcesz ustawiæ j¹ jako kasê domyœln¹ podczas komunikacji z komputerem?");
								DialogBox(hst,MAKEINTRESOURCE(DLG_Q),hwd,(DLGPROC)&DLGQProc);
								if(is_ok)
								{
									Default = Kas_id;
									Save_KS(false);
							
								}
								SetFocus(hwd);
							}
						}
						break;
					}else
					{
						i=-1;
						do
						{
							i++;

						}while(i<MAX_Kas && KS[i].is_exist!=false);
						memset(txt,0,350);
						GetWindowText(GetDlgItem(hwd,DLG13_E9),txt,50);
						if(txt[0]==0)sprintf(K.nazwa,"Kasa_%d",i+1); else strcpy(K.nazwa,txt);
						KS[i]=K;
						if(Count_Kas==-1){Count_Kas=1;Default=1;} else Count_Kas++;
						if((Save_KS(true))==-1)
						{
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Nie mo¿na zapisaæ kasy , poniewa¿ plik fisk.dll jest uszkodzony",txt);
							DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
							SetFocus(hwd);
							break;
						}
						memset(Query_Text,0,350);
						sprintf(Query_Text,"Zapisano kasê w bazie danych\nCzy chcesz ustawiæ j¹ jako kasê domyœln¹ podczas komunikacji z komputerem?");
						DialogBox(hst,MAKEINTRESOURCE(DLG_Q),hwd,(DLGPROC)&DLGQProc);
						if(is_ok)
						{
							Default = i;
							Save_KS(false);
							
						}
						SetFocus(hwd);
						break;

					}
					break;
				}

				if(wp==DLG13_B2)	//Przycisk zamknij
				{
					DestroyWindow(hwd);
					break;
				}
				if(wp==DLG13_RB1)	// transmisja 9600
				{
					CheckDlgButton(hwd,DLG13_RB1,BST_CHECKED);
					CheckDlgButton(hwd,DLG13_RB2,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB3,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB4,BST_UNCHECKED);
					EnableWindow(GetDlgItem(hwd,DLG13_B3),false);
					break;
				}
				if(wp==DLG13_RB2)	// transmisja 19600
				{
					CheckDlgButton(hwd,DLG13_RB2,BST_CHECKED);
					CheckDlgButton(hwd,DLG13_RB1,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB3,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB4,BST_UNCHECKED);
					EnableWindow(GetDlgItem(hwd,DLG13_B3),false);
					break;
				}
				if(wp==DLG13_RB3)	// transmisja 28800
				{
					CheckDlgButton(hwd,DLG13_RB3,BST_CHECKED);
					CheckDlgButton(hwd,DLG13_RB2,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB1,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB4,BST_UNCHECKED);
					EnableWindow(GetDlgItem(hwd,DLG13_B3),false);
					break;
				}
				if(wp==DLG13_RB4)	// transmisja 57600
				{
					CheckDlgButton(hwd,DLG13_RB4,BST_CHECKED);
					CheckDlgButton(hwd,DLG13_RB2,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB3,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB1,BST_UNCHECKED);
					EnableWindow(GetDlgItem(hwd,DLG13_B3),false);
					break;
				}

				if(wp==DLG13_RB5)	// transmisja bezpoœrednia
				{
					SendMessage(hwd,WM_COMMAND,(WPARAM)DLG13_RB11,0);
					CheckDlgButton(hwd,DLG13_RB5,BST_CHECKED);
					CheckDlgButton(hwd,DLG13_RB6,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB7,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB8,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB9,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB10,BST_UNCHECKED);
					EnableWindow(GetDlgItem(hwd,DLG13_RB11),false);
					EnableWindow(GetDlgItem(hwd,DLG13_RB12),false);
					EnableWindow(GetDlgItem(hwd,DLG13_RB13),false);
					EnableWindow(GetDlgItem(hwd,DLG13_RB14),false);
					EnableWindow(GetDlgItem(hwd,DLG13_RB15),false);
					EnableWindow(GetDlgItem(hwd,DLG13_RB16),false);
					EnableWindow(GetDlgItem(hwd,DLG13_RB17),false);
					EnableWindow(GetDlgItem(hwd,DLG13_RB18),false);
					EnableWindow(GetDlgItem(hwd,DLG13_RB19),false);
					EnableWindow(GetDlgItem(hwd,DLG13_RB20),false);
					EnableWindow(GetDlgItem(hwd,DLG13_E1),true);
					EnableWindow(GetDlgItem(hwd,DLG13_E2),false);
					EnableWindow(GetDlgItem(hwd,DLG13_E3),false);
					EnableWindow(GetDlgItem(hwd,DLG13_E4),false);
					EnableWindow(GetDlgItem(hwd,DLG13_E5),false);
					EnableWindow(GetDlgItem(hwd,DLG13_E6),false);
					EnableWindow(GetDlgItem(hwd,DLG13_E7),false);
					EnableWindow(GetDlgItem(hwd,DLG13_E8),false);
					EnableWindow(GetDlgItem(hwd,DLG13_SB1),true);
					EnableWindow(GetDlgItem(hwd,DLG13_SB2),false);
					EnableWindow(GetDlgItem(hwd,DLG13_SB3),false);
					EnableWindow(GetDlgItem(hwd,DLG13_SB4),false);
					EnableWindow(GetDlgItem(hwd,DLG13_SB5),false);
					EnableWindow(GetDlgItem(hwd,DLG13_CB1),false);
					EnableWindow(GetDlgItem(hwd,DLG13_RB3),true);
					EnableWindow(GetDlgItem(hwd,DLG13_RB4),true);
					SetWindowText(GetDlgItem(hwd,DLG13_T6),"Timeout Komunikacji z Modemem");
					EnableWindow(GetDlgItem(hwd,DLG13_B3),false);
					break;
				}

				if(wp==DLG13_RB6)	// transmisja multiplekser 4-kana³owy
				{
					SendMessage(hwd,WM_COMMAND,(WPARAM)DLG13_RB11,0);
					CheckDlgButton(hwd,DLG13_RB6,BST_CHECKED);
					CheckDlgButton(hwd,DLG13_RB5,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB7,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB8,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB9,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB10,BST_UNCHECKED);
					EnableWindow(GetDlgItem(hwd,DLG13_RB11),true);
					EnableWindow(GetDlgItem(hwd,DLG13_RB12),true);
					EnableWindow(GetDlgItem(hwd,DLG13_RB13),true);
					EnableWindow(GetDlgItem(hwd,DLG13_RB14),true);
					EnableWindow(GetDlgItem(hwd,DLG13_RB15),false);
					EnableWindow(GetDlgItem(hwd,DLG13_RB16),false);
					EnableWindow(GetDlgItem(hwd,DLG13_RB17),false);
					EnableWindow(GetDlgItem(hwd,DLG13_RB18),false);
					EnableWindow(GetDlgItem(hwd,DLG13_RB19),false);
					EnableWindow(GetDlgItem(hwd,DLG13_RB20),false);
					EnableWindow(GetDlgItem(hwd,DLG13_E1),true);
					EnableWindow(GetDlgItem(hwd,DLG13_E2),false);
					EnableWindow(GetDlgItem(hwd,DLG13_E3),false);
					EnableWindow(GetDlgItem(hwd,DLG13_E4),false);
					EnableWindow(GetDlgItem(hwd,DLG13_E5),false);
					EnableWindow(GetDlgItem(hwd,DLG13_E6),false);
					EnableWindow(GetDlgItem(hwd,DLG13_E7),false);
					EnableWindow(GetDlgItem(hwd,DLG13_E8),false);
					EnableWindow(GetDlgItem(hwd,DLG13_SB1),true);
					EnableWindow(GetDlgItem(hwd,DLG13_SB2),false);
					EnableWindow(GetDlgItem(hwd,DLG13_SB3),false);
					EnableWindow(GetDlgItem(hwd,DLG13_SB4),false);
					EnableWindow(GetDlgItem(hwd,DLG13_SB5),false);
					EnableWindow(GetDlgItem(hwd,DLG13_CB1),false);
					EnableWindow(GetDlgItem(hwd,DLG13_RB3),true);
					EnableWindow(GetDlgItem(hwd,DLG13_RB4),true);
					SetWindowText(GetDlgItem(hwd,DLG13_T6),"Timeout Komunikacji z Modemem");
					EnableWindow(GetDlgItem(hwd,DLG13_B3),false);
					break;
				}

				if(wp==DLG13_RB7)	// transmisja modem
				{
					SendMessage(hwd,WM_COMMAND,(WPARAM)DLG13_RB11,0);
					CheckDlgButton(hwd,DLG13_RB7,BST_CHECKED);
					CheckDlgButton(hwd,DLG13_RB6,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB5,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB8,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB9,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB10,BST_UNCHECKED);
					EnableWindow(GetDlgItem(hwd,DLG13_RB11),true);
					EnableWindow(GetDlgItem(hwd,DLG13_RB12),true);
					EnableWindow(GetDlgItem(hwd,DLG13_RB13),true);
					EnableWindow(GetDlgItem(hwd,DLG13_RB14),true);
					EnableWindow(GetDlgItem(hwd,DLG13_RB15),true);
					EnableWindow(GetDlgItem(hwd,DLG13_RB16),true);
					EnableWindow(GetDlgItem(hwd,DLG13_RB17),true);
					EnableWindow(GetDlgItem(hwd,DLG13_RB18),true);
					EnableWindow(GetDlgItem(hwd,DLG13_RB19),true);
					EnableWindow(GetDlgItem(hwd,DLG13_RB20),true);
					EnableWindow(GetDlgItem(hwd,DLG13_E1),true);
					EnableWindow(GetDlgItem(hwd,DLG13_E2),true);
					EnableWindow(GetDlgItem(hwd,DLG13_E3),true);
					EnableWindow(GetDlgItem(hwd,DLG13_E4),true);
					EnableWindow(GetDlgItem(hwd,DLG13_E5),true);
					EnableWindow(GetDlgItem(hwd,DLG13_E6),true);
					EnableWindow(GetDlgItem(hwd,DLG13_E7),false);
					EnableWindow(GetDlgItem(hwd,DLG13_E8),false);
					EnableWindow(GetDlgItem(hwd,DLG13_SB1),true);
					EnableWindow(GetDlgItem(hwd,DLG13_SB2),true);
					EnableWindow(GetDlgItem(hwd,DLG13_SB3),true);
					EnableWindow(GetDlgItem(hwd,DLG13_SB4),true);
					EnableWindow(GetDlgItem(hwd,DLG13_SB5),false);
					EnableWindow(GetDlgItem(hwd,DLG13_CB1),true);
					CheckDlgButton(hwd,DLG13_RB1,BST_CHECKED);
					CheckDlgButton(hwd,DLG13_RB2,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB3,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB4,BST_UNCHECKED);
					EnableWindow(GetDlgItem(hwd,DLG13_RB3),false);
					EnableWindow(GetDlgItem(hwd,DLG13_RB4),false);
					SetWindowText(GetDlgItem(hwd,DLG13_T6),"Timeout Komunikacji z Modemem");
					EnableWindow(GetDlgItem(hwd,DLG13_B3),false);
					break;
				}

				if(wp==DLG13_RB8)	// transmisja prze³¹cznik multiplekserów
				{
					SendMessage(hwd,WM_COMMAND,(WPARAM)DLG13_RB11,0);
					CheckDlgButton(hwd,DLG13_RB8,BST_CHECKED);
					CheckDlgButton(hwd,DLG13_RB6,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB7,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB5,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB9,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB10,BST_UNCHECKED);
					EnableWindow(GetDlgItem(hwd,DLG13_RB11),true);
					EnableWindow(GetDlgItem(hwd,DLG13_RB12),true);
					EnableWindow(GetDlgItem(hwd,DLG13_RB13),true);
					EnableWindow(GetDlgItem(hwd,DLG13_RB14),true);
					EnableWindow(GetDlgItem(hwd,DLG13_RB15),true);
					EnableWindow(GetDlgItem(hwd,DLG13_RB16),true);
					EnableWindow(GetDlgItem(hwd,DLG13_RB17),true);
					EnableWindow(GetDlgItem(hwd,DLG13_RB18),true);
					EnableWindow(GetDlgItem(hwd,DLG13_RB19),false);
					EnableWindow(GetDlgItem(hwd,DLG13_RB20),false);
					EnableWindow(GetDlgItem(hwd,DLG13_E1),true);
					EnableWindow(GetDlgItem(hwd,DLG13_E2),false);
					EnableWindow(GetDlgItem(hwd,DLG13_E3),false);
					EnableWindow(GetDlgItem(hwd,DLG13_E4),false);
					EnableWindow(GetDlgItem(hwd,DLG13_E5),false);
					EnableWindow(GetDlgItem(hwd,DLG13_E6),false);
					EnableWindow(GetDlgItem(hwd,DLG13_E7),false);
					EnableWindow(GetDlgItem(hwd,DLG13_E8),false);
					EnableWindow(GetDlgItem(hwd,DLG13_SB1),true);
					EnableWindow(GetDlgItem(hwd,DLG13_SB2),false);
					EnableWindow(GetDlgItem(hwd,DLG13_SB3),false);
					EnableWindow(GetDlgItem(hwd,DLG13_SB4),false);
					EnableWindow(GetDlgItem(hwd,DLG13_SB5),false);
					EnableWindow(GetDlgItem(hwd,DLG13_CB1),false);
					EnableWindow(GetDlgItem(hwd,DLG13_RB3),true);
					EnableWindow(GetDlgItem(hwd,DLG13_RB4),true);
					SetWindowText(GetDlgItem(hwd,DLG13_T6),"Timeout Komunikacji z Modemem");
					EnableWindow(GetDlgItem(hwd,DLG13_B3),false);
					break;
				}

				if(wp==DLG13_RB9)	// transmisja multiplekser 8-kana³owy
				{
					SendMessage(hwd,WM_COMMAND,(WPARAM)DLG13_RB11,0);
					CheckDlgButton(hwd,DLG13_RB9,BST_CHECKED);
					CheckDlgButton(hwd,DLG13_RB6,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB7,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB8,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB5,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB10,BST_UNCHECKED);
					EnableWindow(GetDlgItem(hwd,DLG13_RB11),true);
					EnableWindow(GetDlgItem(hwd,DLG13_RB12),true);
					EnableWindow(GetDlgItem(hwd,DLG13_RB13),true);
					EnableWindow(GetDlgItem(hwd,DLG13_RB14),true);
					EnableWindow(GetDlgItem(hwd,DLG13_RB15),true);
					EnableWindow(GetDlgItem(hwd,DLG13_RB16),true);
					EnableWindow(GetDlgItem(hwd,DLG13_RB17),true);
					EnableWindow(GetDlgItem(hwd,DLG13_RB18),true);
					EnableWindow(GetDlgItem(hwd,DLG13_RB19),false);
					EnableWindow(GetDlgItem(hwd,DLG13_RB20),false);
					EnableWindow(GetDlgItem(hwd,DLG13_E1),true);
					EnableWindow(GetDlgItem(hwd,DLG13_E2),false);
					EnableWindow(GetDlgItem(hwd,DLG13_E3),false);
					EnableWindow(GetDlgItem(hwd,DLG13_E4),false);
					EnableWindow(GetDlgItem(hwd,DLG13_E5),false);
					EnableWindow(GetDlgItem(hwd,DLG13_E6),false);
					EnableWindow(GetDlgItem(hwd,DLG13_E7),false);
					EnableWindow(GetDlgItem(hwd,DLG13_E8),false);
					EnableWindow(GetDlgItem(hwd,DLG13_SB1),true);
					EnableWindow(GetDlgItem(hwd,DLG13_SB2),false);
					EnableWindow(GetDlgItem(hwd,DLG13_SB3),false);
					EnableWindow(GetDlgItem(hwd,DLG13_SB4),false);
					EnableWindow(GetDlgItem(hwd,DLG13_SB5),false);
					EnableWindow(GetDlgItem(hwd,DLG13_CB1),false);
					EnableWindow(GetDlgItem(hwd,DLG13_RB3),true);
					EnableWindow(GetDlgItem(hwd,DLG13_RB4),true);
					SetWindowText(GetDlgItem(hwd,DLG13_T6),"Timeout Komunikacji z Modemem");
					EnableWindow(GetDlgItem(hwd,DLG13_B3),false);
					break;
				}

				if(wp==DLG13_RB10)	// transmisja Multiplekser LAN/Delta Max LAN/Jota E
				{
					CheckDlgButton(hwd,DLG13_RB10,BST_CHECKED);
					CheckDlgButton(hwd,DLG13_RB6,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB7,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB8,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB9,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB5,BST_UNCHECKED);
					EnableWindow(GetDlgItem(hwd,DLG13_RB11),true);
					EnableWindow(GetDlgItem(hwd,DLG13_RB12),true);
					EnableWindow(GetDlgItem(hwd,DLG13_RB13),true);
					EnableWindow(GetDlgItem(hwd,DLG13_RB14),true);
					EnableWindow(GetDlgItem(hwd,DLG13_RB15),false);
					EnableWindow(GetDlgItem(hwd,DLG13_RB16),false);
					EnableWindow(GetDlgItem(hwd,DLG13_RB17),false);
					EnableWindow(GetDlgItem(hwd,DLG13_RB18),false);
					EnableWindow(GetDlgItem(hwd,DLG13_RB19),false);
					EnableWindow(GetDlgItem(hwd,DLG13_RB20),false);
					EnableWindow(GetDlgItem(hwd,DLG13_E1),true);
					EnableWindow(GetDlgItem(hwd,DLG13_E2),true);
					EnableWindow(GetDlgItem(hwd,DLG13_E3),false);
					EnableWindow(GetDlgItem(hwd,DLG13_E4),false);
					EnableWindow(GetDlgItem(hwd,DLG13_E5),true);
					EnableWindow(GetDlgItem(hwd,DLG13_E6),true);
					EnableWindow(GetDlgItem(hwd,DLG13_E7),true);
					EnableWindow(GetDlgItem(hwd,DLG13_E8),true);
					EnableWindow(GetDlgItem(hwd,DLG13_SB1),false);
					EnableWindow(GetDlgItem(hwd,DLG13_SB2),true);
					EnableWindow(GetDlgItem(hwd,DLG13_SB3),true);
					EnableWindow(GetDlgItem(hwd,DLG13_SB4),false);
					EnableWindow(GetDlgItem(hwd,DLG13_SB5),true);
					EnableWindow(GetDlgItem(hwd,DLG13_CB1),false);
					EnableWindow(GetDlgItem(hwd,DLG13_RB3),true);
					EnableWindow(GetDlgItem(hwd,DLG13_RB4),true);
					SetWindowText(GetDlgItem(hwd,DLG13_T6),"Timeout Komunikacji z Multiplekserem");
					SendMessage(hwd,WM_COMMAND,(WPARAM)DLG13_RB11,0);
					EnableWindow(GetDlgItem(hwd,DLG13_B3),false);
					break;
				}

				if(wp==DLG13_RB11)	// Kana³ 1
				{
					CheckDlgButton(hwd,DLG13_RB11,BST_CHECKED);
					CheckDlgButton(hwd,DLG13_RB12,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB13,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB14,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB15,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB16,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB17,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB18,BST_UNCHECKED);
					EnableWindow(GetDlgItem(hwd,DLG13_B3),false);
					break;
				}

				if(wp==DLG13_RB12)	// Kana³ 2
				{
					CheckDlgButton(hwd,DLG13_RB12,BST_CHECKED);
					CheckDlgButton(hwd,DLG13_RB11,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB13,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB14,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB15,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB16,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB17,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB18,BST_UNCHECKED);
					EnableWindow(GetDlgItem(hwd,DLG13_B3),false);
					break;
				}
				if(wp==DLG13_RB13)	// Kana³ 3
				{
					CheckDlgButton(hwd,DLG13_RB13,BST_CHECKED);
					CheckDlgButton(hwd,DLG13_RB12,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB11,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB14,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB15,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB16,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB17,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB18,BST_UNCHECKED);
					EnableWindow(GetDlgItem(hwd,DLG13_B3),false);
					break;
				}
				if(wp==DLG13_RB14)	// Kana³ 4
				{
					CheckDlgButton(hwd,DLG13_RB14,BST_CHECKED);
					CheckDlgButton(hwd,DLG13_RB12,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB13,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB11,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB15,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB16,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB17,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB18,BST_UNCHECKED);
					EnableWindow(GetDlgItem(hwd,DLG13_B3),false);
					break;
				}

				if(wp==DLG13_RB15)	// Kana³ 5
				{
					CheckDlgButton(hwd,DLG13_RB15,BST_CHECKED);
					CheckDlgButton(hwd,DLG13_RB12,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB13,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB14,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB11,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB16,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB17,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB18,BST_UNCHECKED);
					EnableWindow(GetDlgItem(hwd,DLG13_B3),false);
					break;
				}

				if(wp==DLG13_RB16)	// Kana³ 6
				{
					CheckDlgButton(hwd,DLG13_RB16,BST_CHECKED);
					CheckDlgButton(hwd,DLG13_RB12,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB13,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB14,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB15,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB11,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB17,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB18,BST_UNCHECKED);
					EnableWindow(GetDlgItem(hwd,DLG13_B3),false);
					break;
				}

				if(wp==DLG13_RB17)	// Kana³ 7
				{
					CheckDlgButton(hwd,DLG13_RB17,BST_CHECKED);
					CheckDlgButton(hwd,DLG13_RB12,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB13,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB14,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB15,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB16,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB11,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB18,BST_UNCHECKED);
					EnableWindow(GetDlgItem(hwd,DLG13_B3),false);
					break;
				}

				if(wp==DLG13_RB18)	// Kana³ 8
				{
					CheckDlgButton(hwd,DLG13_RB18,BST_CHECKED);
					CheckDlgButton(hwd,DLG13_RB12,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB13,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB14,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB15,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB16,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB17,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG13_RB11,BST_UNCHECKED);
					EnableWindow(GetDlgItem(hwd,DLG13_B3),false);
					break;
				}

				if(wp==DLG13_RB19)	// wybieranie jednotonowe
				{
					CheckDlgButton(hwd,DLG13_RB19,BST_CHECKED);
					CheckDlgButton(hwd,DLG13_RB20,BST_UNCHECKED);
					EnableWindow(GetDlgItem(hwd,DLG13_B3),false);
					break;
				}
				if(wp==DLG13_RB20)	// wybieranie impulsywne
				{
					CheckDlgButton(hwd,DLG13_RB20,BST_CHECKED);
					CheckDlgButton(hwd,DLG13_RB19,BST_UNCHECKED);
					EnableWindow(GetDlgItem(hwd,DLG13_B3),false);
					break;
				}
				if(wp==DLG13_CB1)
				{
					EnableWindow(GetDlgItem(hwd,DLG13_B3),false);
					break;
				}
				if(wp==DLG13_CB2)
				{
					EnableWindow(GetDlgItem(hwd,DLG13_B3),false);
					break;
				}
				if(HIWORD(wp)==EN_CHANGE)
				{
					//EnableWindow(GetDlgItem(hwd,DLG13_B3),false);
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
				is_dlg1=false;
				EndDialog(hwd,0);
			}
		default: return DefDlgProc(GetParent(hwd),code,wp,lp);
	}
	return 0;
}


	//okno zapytania

LRESULT _stdcall	DLGQProc(HWND hwd, int code, WPARAM wp, LPARAM lp)
{
	static bool bl;

	switch (code)
	{
		case WM_INITDIALOG:
			{
				
				SendMessage(GetDlgItem(hwd,DLG_Q_B1),BM_SETIMAGE,0,(LPARAM)LoadBitmap(hst,MAKEINTRESOURCE(IDB_14)));
				SendMessage(GetDlgItem(hwd,DLG_Q_B2),BM_SETIMAGE,0,(LPARAM)LoadBitmap(hst,MAKEINTRESOURCE(IDB_15)));
				SetWindowText(GetDlgItem(hwd,DLG_Q_T),Query_Text);
				bl=false;
				break;
			}
		case WM_COMMAND:
			{
				if(wp==DLG_Q_B1)
				{
					bl=true;
					DestroyWindow(hwd);
					break;
				}
				if(wp==DLG_Q_B2)
				{
					bl=false;
					DestroyWindow(hwd);
					break;
				}
			}
		case WM_CLOSE:
			{
				DestroyWindow(hwd);
				break;
			}
		case WM_DESTROY:
			{
				is_ok=bl;
				EndDialog(hwd,0);
				break;
			}
		default: return DefDlgProc(GetParent(hwd),code,wp,lp);
	}
	return 0;
}

	//okno b³êdu

LRESULT _stdcall	DLGERRProc(HWND hwd, int code, WPARAM wp, LPARAM lp)
{

	switch (code)
	{
		case WM_INITDIALOG:
			{
				
				SendMessage(GetDlgItem(hwd,DLG_ERR_B),BM_SETIMAGE,0,(LPARAM)LoadBitmap(hst,MAKEINTRESOURCE(IDB_14)));
				SetWindowText(GetDlgItem(hwd,DLG_ERR_T),Err_Text);
				break;
			}
		case WM_COMMAND:
			{
				if(wp==DLG_ERR_B)
				{
				
					DestroyWindow(hwd);
					break;
				}
			
			}
		case WM_CLOSE:
			{
				DestroyWindow(hwd);
				break;
			}
		case WM_DESTROY:
			{
				EndDialog(hwd,0);
				break;
			}
		default: return DefDlgProc(GetParent(hwd),code,wp,lp);
	}
	return 0;
}

// okno informacyjne


LRESULT _stdcall	DLGIProc(HWND hwd, int code, WPARAM wp, LPARAM lp)
{

	switch (code)
	{
		case WM_INITDIALOG:
			{
				
				SendMessage(GetDlgItem(hwd,DLG_I_B),BM_SETIMAGE,0,(LPARAM)LoadBitmap(hst,MAKEINTRESOURCE(IDB_14)));
				SetWindowText(GetDlgItem(hwd,DLG_I_T),Err_Text);
				break;
			}
		case WM_COMMAND:
			{
				if(wp==DLG_I_B)
				{
				
					DestroyWindow(hwd);
					break;
				}
			
			}
		case WM_CLOSE:
			{
				DestroyWindow(hwd);
				break;
			}
		case WM_DESTROY:
			{
				EndDialog(hwd,0);
				break;
			}
		default: return DefDlgProc(GetParent(hwd),code,wp,lp);
	}
	return 0;
}

LRESULT _stdcall DLG14Proc(HWND hwd, int code, WPARAM wp, LPARAM lp)
{
	int i;
	int licz;
	char txt[250];
	DWORD dw;

	switch(code)
	{
		case WM_INITDIALOG:
			{
				dw=0;
				memset(Kas_ind,0,sizeof(int)*MAX_Kas);
				licz=0;
				Kas_id=-1;
				SendMessage(GetDlgItem(hwd,DLG14_B2),BM_SETIMAGE,0,(LPARAM)LoadBitmap(hst,MAKEINTRESOURCE(IDB_14)));
				SendMessage(GetDlgItem(hwd,DLG14_B1),BM_SETIMAGE,0,(LPARAM)LoadBitmap(hst,MAKEINTRESOURCE(IDB_15)));
				if(is_dlg14) SetWindowText(hwd,"Usuwanie kasy fiskalnej");
				
				for(i=0;i<MAX_Kas;i++)
				{
					if(KS[i].is_exist)
					{
						memset(txt,0,250);
						sprintf(txt,"%s   Szybkoœæ: %d    Potr: COM%d",KS[i].nazwa,KS[i].Szybk,KS[i].Com);
						SendMessage(GetDlgItem(hwd,DLG14_LB1),LB_ADDSTRING,0,(LPARAM)txt);
						Kas_ind[licz]=i;
						licz++;
					}


				}
				break;
			}
		case WM_COMMAND:
			{
				if(wp==DLG14_B1)
				{
					DestroyWindow(hwd);
					break;
				}
				if(wp==DLG14_B2)
				{
					i=SendMessage(GetDlgItem(hwd,DLG14_LB1),LB_GETCURSEL,0,0);
					if(i>=0)
					{
						if(!is_dlg14) Kas_id=i;
						else
						{
							memset(Query_Text,0,350);
							sprintf(Query_Text,"Czy napewno chcesz usun¹æ wybran¹ kasê fiskaln¹ ?");
							DialogBox(hst,MAKEINTRESOURCE(DLG_Q),hwd,(DLGPROC)&DLGQProc);
							if(is_ok)
							{
								Kas_id=Kas_ind[i];
								KS[Kas_id].is_exist=false;
								Count_Kas--;
								if(Default==Kas_id)
								{
									i=-1;
									do
									{
										i++;

									}while(i<MAX_Kas && KS[i].is_exist!=true);
									if(i==MAX_Kas) Default=-1; else Default=i;
								}
								Save_KS(true);
								memset(Err_Text,0,350);
								sprintf(Err_Text,"Usuniêto kasê fiskaln¹ z bazy");
								DialogBox(hst,MAKEINTRESOURCE(DLG_I),MainWnd,(DLGPROC)&DLGIProc);
								SendMessage(GetDlgItem(hwd,DLG14_LB1),LB_RESETCONTENT,0,0);
								licz=0;
								for(i=0;i<MAX_Kas;i++)
								{
									if(KS[i].is_exist)
									{
										memset(txt,0,250);
										sprintf(txt,"%s   Szybkoœæ: %d    Potr: COM%d",KS[i].nazwa,KS[i].Szybk,KS[i].Com);
										SendMessage(GetDlgItem(hwd,DLG14_LB1),LB_ADDSTRING,0,(LPARAM)txt);
										Kas_ind[licz]=i;
										licz++;
									}


								}

							}
							SetFocus(hwd);
						}
						//DestroyWindow(hwd);
					}
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
				EndDialog(hwd,0);
				is_dlg14=false;
				break;
			}
		default: return DefDlgProc(GetParent(hwd),code,wp,lp);
	}

	return 0;
}




LRESULT _stdcall DLG15Proc(HWND hwd, int code, WPARAM wp, LPARAM lp)
{
	LVCOLUMN lvc;
	LVITEM lvi;
	int i,licz,j;
	char txt[150];
	static bool is_act=false;

	switch(code)
	{
		case WM_INITDIALOG:
			{	
				memset(Kas_ind,0,MAX_Kas);
				SendMessage(GetDlgItem(hwd,DLG15_B2),BM_SETIMAGE,0,(LPARAM)LoadBitmap(hst,MAKEINTRESOURCE(IDB_14)));
				SendMessage(GetDlgItem(hwd,DLG15_B1),BM_SETIMAGE,0,(LPARAM)LoadBitmap(hst,MAKEINTRESOURCE(IDB_15)));

				ListView_SetExtendedListViewStyle(GetDlgItem(hwd,DLG15_LV1),LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_INFOTIP);
				ListView_DeleteAllItems(GetDlgItem(hwd,DLG15_LV1));
				if(!is_act)
				{
					for(i=0;i<5;i++)
					{
						lvc.mask=LVCF_WIDTH |LVCF_TEXT;
						lvc.pszText=LVD15[i];
						lvc.cx=LVD15_W[i];
						ListView_InsertColumn(GetDlgItem(hwd,DLG15_LV1),i,&lvc);
					}
					is_act=true;
				}
				licz=0;
				lvi.mask=LVIF_TEXT;
				lvi.iSubItem=0;
				for(i=0;i<MAX_Kas;i++)
				{
					if(KS[i].is_exist)
					{
						lvi.iItem=licz;
						lvi.pszText=KS[i].nazwa;
						ListView_InsertItem(GetDlgItem(hwd,DLG15_LV1),&lvi);
						Kas_ind[licz]=i;
						for(j=0;j<4;j++)
						{
							memset(txt,0,150);
							if(j==0) sprintf(txt,"%s",KS[i].numer); else
								if(j==1) sprintf(txt,"COM%d",KS[i].Com); else if(j==2) sprintf(txt,"%d",KS[i].Szybk);
								else if(j==3)
								{
									memset(txt,0,150);
									if(KS[i].rodz_pol==0) strcpy(txt,"Bezpoœrednio");
										else if(KS[i].rodz_pol==1) strcpy(txt,"Multiplekser 4-kana³owy");
											else if(KS[i].rodz_pol==2) strcpy(txt,"Modem");
												else if(KS[i].rodz_pol==3) strcpy(txt,"Prze³¹cznik multiplekserów");
													else if(KS[i].rodz_pol==4) strcpy(txt,"Multiplekser 8-kana³owy");
														else if(KS[i].rodz_pol==5) strcpy(txt,"Multiplekser LAN/Delta Max LAN/Jota E");
								}
							ListView_SetItemText(GetDlgItem(hwd,DLG15_LV1),licz,j+1,txt);
						}
						licz++;
					}
				}

				break;
			}
		case WM_COMMAND:
			{
				if(wp==DLG15_B1)
				{
					DestroyWindow(hwd);
					break;
				}
				if(wp==DLG15_B2)
				{
					
					i=ListView_GetSelectionMark(GetDlgItem(hwd,DLG15_LV1));
					if(i<0) break;
					Kas_id=Kas_ind[i];
					DialogBox(hst,MAKEINTRESOURCE(ID_DLG_13),hwd,(DLGPROC)&Dlg13Proc);
					SetFocus(hwd);
					SendMessage(hwd,WM_INITDIALOG,0,0);
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
				EndDialog(hwd,0);
				is_dlg14=false;
				is_act=false;
				break;
			}
		default: return DefDlgProc(GetParent(hwd),code,wp,lp);
	}

	return 0;
}

		//Okno dialogowe zarz¹dzania walutami


LRESULT _stdcall DLG16Proc(HWND hwd, int code, WPARAM wp, LPARAM lp)
{
	int i,max,ac;
	char zn[50],zn1[50];
	WALUTA _wal[15];

	switch(code)
	{
		case WM_INITDIALOG:
		{

			for (i=0;i<cnt.walcnt;i++)
			{
				memset(zn,0,50);
				sprintf(zn,"%s(%s)",wal[i].naz,wal[i].znak);
				SendMessage(GetDlgItem(hwd,DLG16_LB1),LB_ADDSTRING,0,(LPARAM)zn);
			}
			memset(zn,0,50);
			sprintf(zn,"Domyœlna waluta: %s(%s)",wal[cnt.def_wal].naz,wal[cnt.def_wal].znak);
			SetWindowText(GetDlgItem(hwd,DLG16_T1),zn);
			is_zm_wal=false;
			break;
		}

		case WM_COMMAND:
			{
				if(wp==DLG16_B1)				//Przycisk wyjdŸ
				{
					DestroyWindow(hwd);
					break;
				}


				if(wp==DLG16_B4)			//Przycisk ustaw domyœln¹ walutê
				{
					i=SendMessage(GetDlgItem(hwd,DLG16_LB1),LB_GETCURSEL,0,0);
					if(i<0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nale¿y zanzaczyæ walutê");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					cnt.def_wal=i;
					if(Save_Cnt()!=1)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie mo¿na zapisaæ walut do bazy. ");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGERRProc);
						SetFocus(hwd);
						break;
					}
					memset(zn,0,50);
					sprintf(zn,"Domyœlna waluta: %s(%s)",wal[cnt.def_wal].naz,wal[cnt.def_wal].znak);
					SetWindowText(GetDlgItem(hwd,DLG16_T1),zn);
					is_zm_wal=true;
					break;
				}

				if(wp==DLG16_B3)				//Przycisk usuñ walutê
				{
					if(cnt.walcnt==1)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie mo¿na usun¹c waluty, poniewa¿ przynajmniej jedna waluta musi byæ zdefiniowana");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					i=SendMessage(GetDlgItem(hwd,DLG16_LB1),LB_GETCURSEL,0,0);
					if(i<0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nale¿y zanzaczyæ walutê");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					ac=i;
					for(i=i;i<cnt.walcnt;i++)
					{
						if(i+1==cnt.walcnt) memset(&wal[i],0,sizeof(WALUTA));
						else
						wal[i]=wal[i+1];
					}
					cnt.walcnt--;
					if(ac<cnt.def_wal) 
					{
						cnt.def_wal--;
						is_zm_wal=true;
					}
					else if(cnt.def_wal==cnt.walcnt) 
					{
						cnt.def_wal--;
						is_zm_wal=true;
					}
					i=Save_Wal();
					if(i!=1)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie mo¿na zapisaæ walut do bazy. ");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGERRProc);
						SetFocus(hwd);
					} else
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Usuniêto walutê z bazy");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						memset(zn,0,50);
						sprintf(zn,"Domyœlna waluta: %s(%s)",wal[cnt.def_wal].naz,wal[cnt.def_wal].znak);
						SetWindowText(GetDlgItem(hwd,DLG16_T1),zn);
						i=SendMessage(GetDlgItem(hwd,DLG16_LB1),LB_RESETCONTENT,0,0);
						for (i=0;i<cnt.walcnt;i++)
						{
							memset(zn,0,50);
							sprintf(zn,"%s(%s)",wal[i].naz,wal[i].znak);
							SendMessage(GetDlgItem(hwd,DLG16_LB1),LB_ADDSTRING,0,(LPARAM)zn);
						}
					}

					break;
				}

				if(wp==DLG16_B2)				//Przycisk Dodaj walutê
				{
					if(cnt.walcnt==99)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Zdefiniowano ju¿ maksymaln¹ iloœæ walut");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					memset(zn,0,50);
					GetWindowText(GetDlgItem(hwd,DLG16_E1),zn,50);
					memset(zn1,0,50);
					GetWindowText(GetDlgItem(hwd,DLG16_E2),zn1,50);
					if(zn[0]==0 || zn1[0]==0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nale¿y podaæ nazwê waluty");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;

					}

					strcpy(wal[cnt.walcnt].naz,zn);
					strcpy(wal[cnt.walcnt].znak,zn1);
					cnt.walcnt++;
					i=Save_Wal();
					if(i!=1)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie mo¿na zapisaæ walut do bazy. ");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGERRProc);
						SetFocus(hwd);
					} else
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Dodano walutê do bazy");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						memset(zn,0,50);
						sprintf(zn,"%s(%s)",wal[cnt.walcnt-1].naz,wal[cnt.walcnt-1].znak);
						SendMessage(GetDlgItem(hwd,DLG16_LB1),LB_ADDSTRING,0,(LPARAM)zn);
						SetFocus(hwd);
					}
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
				EndDialog(hwd,0);
				break;
			}
		default: return DefDlgProc(GetParent(hwd),code,wp,lp);
	}
	return 0;
}



//Okno dialogowe zarz¹dzania formami zap³aty


LRESULT _stdcall DLG17Proc(HWND hwd, int code, WPARAM wp, LPARAM lp)
{
	int i,max,ac;
	char zn[50];
	WALUTA _wal[15];

	switch(code)
	{
		case WM_INITDIALOG:
		{

			for (i=0;i<cnt.fzapcnt;i++)
			{
				memset(zn,0,50);
				sprintf(zn,"%s",form_zap[i].naz);
				SendMessage(GetDlgItem(hwd,DLG17_LB1),LB_ADDSTRING,0,(LPARAM)zn);
			}
			memset(zn,0,50);
			sprintf(zn,"Domyœlna forma zap³aty: %s",form_zap[cnt.def_form_zap].naz);
			SetWindowText(GetDlgItem(hwd,DLG17_T1),zn);
			SetWindowText(GetDlgItem(hwd,DLG17_E2),form_zap[cnt.def_form_zap].opis);
			break;
		}

		case WM_COMMAND:
			{
				if(wp==DLG17_B1)				//Przycisk wyjdŸ
				{
					DestroyWindow(hwd);
					break;
				}


				if(wp==DLG17_B4)			//Przycisk ustaw domyœln¹ formê zap³aty
				{
					i=SendMessage(GetDlgItem(hwd,DLG17_LB1),LB_GETCURSEL,0,0);
					if(i<0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nale¿y zanzaczyæ pozycjê na liœcie");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					cnt.def_form_zap=i;
					if(Save_Cnt()!=1)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie mo¿na zapisaæ danych do bazy. ");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGERRProc);
						SetFocus(hwd);
						break;
					}
					memset(zn,0,50);
					sprintf(zn,"Domyœlna forma zap³aty: %s",form_zap[cnt.def_form_zap].naz);
					SetWindowText(GetDlgItem(hwd,DLG17_T1),zn);
					SetWindowText(GetDlgItem(hwd,DLG17_E2),form_zap[cnt.def_form_zap].opis);
					is_zm_wal=true;
					break;
				}

				if(wp==DLG17_B3)				//Przycisk usuñ formê zap³aty
				{
					if(cnt.fzapcnt==1)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie mo¿na usun¹c pozycji z listy, poniewa¿ przynajmniej jedna forma zap³aty musi byæ zdefiniowana");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					i=SendMessage(GetDlgItem(hwd,DLG17_LB1),LB_GETCURSEL,0,0);
					if(i<0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nale¿y zanzaczyæ pozycjê na liœcie");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					ac=i;
					for(i=i;i<cnt.fzapcnt;i++)
					{
						if(i+1==cnt.fzapcnt) memset(&form_zap[i],0,sizeof(FORM_ZAP));
						else
						form_zap[i]=form_zap[i+1];
					}
					cnt.fzapcnt--;
					if(ac<cnt.def_form_zap) cnt.def_form_zap--;
					else if(cnt.def_form_zap==cnt.fzapcnt) cnt.def_form_zap--;
					
					i=Save_FZ();
					if(i!=1)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie mo¿na zapisaæ danych do bazy. ");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGERRProc);
						SetFocus(hwd);
					} else
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Usuniêto formê zap³aty z bazy");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						memset(zn,0,50);
						sprintf(zn,"Domyœlna forma zap³aty: %s",form_zap[cnt.def_form_zap].naz);
						SetWindowText(GetDlgItem(hwd,DLG17_T1),zn);
						SetWindowText(GetDlgItem(hwd,DLG17_E2),form_zap[cnt.def_form_zap].opis);
						i=SendMessage(GetDlgItem(hwd,DLG17_LB1),LB_RESETCONTENT,0,0);
						for (i=0;i<cnt.fzapcnt;i++)
						{
							memset(zn,0,50);
							sprintf(zn,"%s",form_zap[i].naz);
							SendMessage(GetDlgItem(hwd,DLG17_LB1),LB_ADDSTRING,0,(LPARAM)zn);
						}
					}

					break;
				}

				if(wp==DLG17_B2)				//Przycisk Dodaj formê zap³aty
				{
					if(cnt.fzapcnt==99)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Zdefiniowano ju¿ maksymaln¹ iloœæ form zap³aty");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					memset(zn,0,50);
					GetWindowText(GetDlgItem(hwd,DLG17_E1),zn,50);
					if(zn[0]==0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nale¿y podaæ nazwê formy zap³aty");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;

					}

					strcpy(form_zap[cnt.fzapcnt].naz,zn);
					GetWindowText(GetDlgItem(hwd,DLG17_E2),form_zap[cnt.fzapcnt].opis,350);
					cnt.fzapcnt++;
					i=Save_FZ();
					if(i!=1)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie mo¿na zapisaæ danych do bazy. ");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGERRProc);
						SetFocus(hwd);
					} else
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Dodano formê zap³aty do bazy");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						memset(zn,0,50);
						sprintf(zn,"%s",form_zap[cnt.fzapcnt-1].naz);
						SendMessage(GetDlgItem(hwd,DLG17_LB1),LB_ADDSTRING,0,(LPARAM)zn);
						SetFocus(hwd);
					}
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
				EndDialog(hwd,0);
				break;
			}
		default: return DefDlgProc(GetParent(hwd),code,wp,lp);
	}
	return 0;
}









//Okno dialogowe zarz¹dzania stawkami vat zap³aty


LRESULT _stdcall DLG18Proc(HWND hwd, int code, WPARAM wp, LPARAM lp)
{
	int i,max,ac;
	char zn[100];
	ST_VAT _Vat[15];
	static HWND edit;

	switch(code)
	{
		case WM_INITDIALOG:
		{

			for (i=0;i<cnt.vatcnt;i++)
			{
				memset(zn,0,100);
				sprintf(zn,"%0.2f%%",Vat[i].vat);
				SendMessage(GetDlgItem(hwd,DLG18_LB1),LB_ADDSTRING,0,(LPARAM)zn);
			}
			edit=GetDlgItem(hwd,DLG18_E1);
			memset(zn,0,100);
			sprintf(zn,"Domyœlna stawka VAT: %0.2f%%",Vat[cnt.def_vat].vat);
			SetWindowText(GetDlgItem(hwd,DLG18_T1),zn);
			SetWindowText(GetDlgItem(hwd,DLG18_E2),Vat[cnt.def_vat].opis);
			SetProp(edit,"BOOL",(HANDLE)false);
			SetProp(edit,"PROC",(HANDLE)GetWindowLong(edit,GWL_WNDPROC));
			SetWindowLong(edit,GWL_WNDPROC,(LONG)WndEProc);
			break;
		}

		case WM_COMMAND:
			{
				if(wp==DLG18_B1)				//Przycisk wyjdŸ
				{
					DestroyWindow(hwd);
					break;
				}


				if(wp==DLG18_B4)			//Przycisk ustaw domyœln¹ stawkê vat
				{
					i=SendMessage(GetDlgItem(hwd,DLG18_LB1),LB_GETCURSEL,0,0);
					if(i<0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nale¿y zanzaczyæ pozycjê na liœcie");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					cnt.def_vat=i;
					if(Save_Cnt()!=1)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie mo¿na zapisaæ danych do bazy. ");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGERRProc);
						SetFocus(hwd);
						break;
					}
					memset(zn,0,100);
					sprintf(zn,"Domyœlna stawka VAT: %0.2f%%",Vat[cnt.def_vat].vat);
					SetWindowText(GetDlgItem(hwd,DLG18_T1),zn);
					SetWindowText(GetDlgItem(hwd,DLG18_E2),Vat[cnt.def_vat].opis);
					is_zm_wal=true;
					break;
				}

				if(wp==DLG18_B3)				//Przycisk usuñ stawkê vat 
				{
					if(cnt.vatcnt==1)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie mo¿na usun¹c pozycji z listy, poniewa¿ przynajmniej jedna forma zap³aty musi byæ zdefiniowana");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					i=SendMessage(GetDlgItem(hwd,DLG18_LB1),LB_GETCURSEL,0,0);
					if(i<0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nale¿y zanzaczyæ pozycjê na liœcie");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					ac=i;
					for(i=i;i<cnt.vatcnt;i++)
					{
						if(i+1==cnt.vatcnt) {memset(&Vat[i],0,sizeof(ST_VAT));Vat[i].vat=-1;}
						else
						Vat[i]=Vat[i+1];
					}
					cnt.vatcnt--;
					if(ac<cnt.def_vat) cnt.def_vat--;
					else if(cnt.def_vat==cnt.vatcnt) cnt.def_vat--;
					
					i=Save_Vat();
					if(i!=1)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie mo¿na zapisaæ danych do bazy. ");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGERRProc);
						SetFocus(hwd);
					} else
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Usuniêto stawkê VAT z bazy");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						memset(zn,0,100);
						sprintf(zn,"Domyœlna stawka VAT: %0.2f%%",Vat[cnt.def_vat].vat);
						SetWindowText(GetDlgItem(hwd,DLG18_T1),zn);
						SetWindowText(GetDlgItem(hwd,DLG18_E2),Vat[cnt.def_vat].opis);
						i=SendMessage(GetDlgItem(hwd,DLG18_LB1),LB_RESETCONTENT,0,0);
						for (i=0;i<cnt.vatcnt;i++)
						{
							memset(zn,0,100);
							sprintf(zn,"%0.2f%%",Vat[i].vat);
							SendMessage(GetDlgItem(hwd,DLG18_LB1),LB_ADDSTRING,0,(LPARAM)zn);
						}
					}

					break;
				}

				if(wp==DLG18_B2)				//Przycisk Dodaj stawkê VAT
				{
					if(cnt.vatcnt==99)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Zdefiniowano ju¿ maksymaln¹ iloœæ stawek VAT");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					memset(zn,0,100);
					GetWindowText(GetDlgItem(hwd,DLG18_E1),zn,50);
					if(zn[0]==0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nale¿y podaæ stawkê VAT");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;

					}

					Vat[cnt.vatcnt].vat=atof(zn);
					GetWindowText(GetDlgItem(hwd,DLG18_E2),Vat[cnt.vatcnt].opis,100);
					cnt.vatcnt++;
					i=Save_Vat();
					if(i!=1)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie mo¿na zapisaæ danych do bazy. ");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGERRProc);
						SetFocus(hwd);
					} else
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Dodano stawkê VAT do bazy");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						memset(zn,0,100);
						sprintf(zn,"%0.2f%%",Vat[cnt.vatcnt-1].vat);
						SendMessage(GetDlgItem(hwd,DLG18_LB1),LB_ADDSTRING,0,(LPARAM)zn);
						SetFocus(hwd);
					}
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
				EndDialog(hwd,0);
				break;
			}
		default: return DefDlgProc(GetParent(hwd),code,wp,lp);
	}
	return 0;
}



	//okno dialogowe zarz¹dzania jednostkami miary



LRESULT _stdcall DLG19Proc(HWND hwd, int code, WPARAM wp, LPARAM lp)
{
	int i,max,ac;
	char zn[50],zn1[50];
	JM _jm[15];

	switch(code)
	{
		case WM_INITDIALOG:
		{
			SendMessage(GetDlgItem(hwd,DLG19_E2),EM_SETLIMITTEXT,(WPARAM)4,0);
			for (i=0;i<cnt.jmcnt;i++)
			{
				memset(zn,0,50);
				sprintf(zn,"%s(%s)",jm[i].naz,jm[i].znak);
				SendMessage(GetDlgItem(hwd,DLG19_LB1),LB_ADDSTRING,0,(LPARAM)zn);
			}
			memset(zn,0,50);
			sprintf(zn,"Domyœlna jednostka miary: %s(%s)",jm[cnt.def_jm].naz,jm[cnt.def_jm].znak);
			SetWindowText(GetDlgItem(hwd,DLG19_T1),zn);
			is_zm_wal=false;
			break;
		}

		case WM_COMMAND:
			{
				if(wp==DLG19_B1)				//Przycisk wyjdŸ
				{
					DestroyWindow(hwd);
					break;
				}


				if(wp==DLG19_B4)			//Przycisk ustaw domyœln¹ jednostkê
				{
					i=SendMessage(GetDlgItem(hwd,DLG19_LB1),LB_GETCURSEL,0,0);
					if(i<0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nale¿y zanzaczyæ pozycjê na liœcie");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					cnt.def_jm=i;
					if(Save_Cnt()!=1)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie mo¿na zapisaæ danych do bazy. ");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGERRProc);
						SetFocus(hwd);
						break;
					}
					memset(zn,0,50);
					sprintf(zn,"Domyœlna jedostka miary: %s(%s)",jm[cnt.def_jm].naz,jm[cnt.def_jm].znak);
					SetWindowText(GetDlgItem(hwd,DLG19_T1),zn);
					is_zm_wal=true;
					break;
				}

				if(wp==DLG19_B3)				//Przycisk usuñ jednostkê
				{
					if(cnt.jmcnt==1)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie mo¿na usun¹c jednostki, poniewa¿ przynajmniej jedna waluta musi byæ zdefiniowana");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					i=SendMessage(GetDlgItem(hwd,DLG19_LB1),LB_GETCURSEL,0,0);
					if(i<0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nale¿y zanzaczyæ pozycjê na liœcie");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					ac=i;
					for(i=i;i<cnt.jmcnt;i++)
					{
						if(i+1==cnt.jmcnt) memset(&jm[i],0,sizeof(JM));
						else
						jm[i]=jm[i+1];
					}
					cnt.jmcnt--;
					if(ac<cnt.def_jm) 
					{
						cnt.def_jm--;
						is_zm_wal=true;
					}
					else if(cnt.def_jm==cnt.jmcnt) 
					{
						cnt.def_jm--;
						is_zm_wal=true;
					}
					i=Save_JM();
					if(i!=1)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie mo¿na zapisaæ danych do bazy. ");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGERRProc);
						SetFocus(hwd);
					} else
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Usuniêto jednostkê miary z bazy");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						memset(zn,0,50);
						sprintf(zn,"Domyœlna jednostka miary: %s(%s)",jm[cnt.def_jm].naz,jm[cnt.def_jm].znak);
						SetWindowText(GetDlgItem(hwd,DLG19_T1),zn);
						i=SendMessage(GetDlgItem(hwd,DLG19_LB1),LB_RESETCONTENT,0,0);
						for (i=0;i<cnt.jmcnt;i++)
						{
							memset(zn,0,50);
							sprintf(zn,"%s(%s)",jm[i].naz,jm[i].znak);
							SendMessage(GetDlgItem(hwd,DLG19_LB1),LB_ADDSTRING,0,(LPARAM)zn);
						}
					}

					break;
				}

				if(wp==DLG19_B2)				//Przycisk Dodaj walutê
				{
					if(cnt.jmcnt==99)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Zdefiniowano ju¿ maksymaln¹ iloœæ jednostek miary");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					memset(zn,0,50);
					GetWindowText(GetDlgItem(hwd,DLG19_E1),zn,50);
					memset(zn1,0,50);
					GetWindowText(GetDlgItem(hwd,DLG19_E2),zn1,50);
					if(zn[0]==0 || zn1[0]==0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nale¿y podaæ nazwê jednostki");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;

					}

					strcpy(jm[cnt.jmcnt].naz,zn);
					strcpy(jm[cnt.jmcnt].znak,zn1);
					cnt.jmcnt++;
					i=Save_JM();
					if(i!=1)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie mo¿na zapisaæ danych do bazy. ");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGERRProc);
						SetFocus(hwd);
					} else
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Dodano jednostkê do bazy");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						memset(zn,0,50);
						sprintf(zn,"%s(%s)",jm[cnt.jmcnt-1].naz,jm[cnt.jmcnt-1].znak);
						SendMessage(GetDlgItem(hwd,DLG19_LB1),LB_ADDSTRING,0,(LPARAM)zn);
						SetFocus(hwd);
					}
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
				EndDialog(hwd,0);
				break;
			}
		default: return DefDlgProc(GetParent(hwd),code,wp,lp);
	}
	return 0;
}


LRESULT _stdcall DLG20Proc(HWND hwd, int code , WPARAM wp, LPARAM lp)
{

	char zn[8];
	bool bl;

	switch(code)
	{
		case WM_INITDIALOG:
		{
			if(NV.is_)
			{
				SetWindowText(GetDlgItem(hwd,DLG20_E1),NV.przed);
			}
			break;
		}

		case WM_COMMAND:
			{
				if(wp==DLG20_B1)				//przycisk wyjdŸ
				{
					DestroyWindow(hwd);
					break;
				}


				if(wp==DLG20_B2)				//przycisk OK
				{
					memset(zn,0,8);
					GetWindowText(GetDlgItem(hwd,DLG20_E1),zn,8);
					if(zn[0]==0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Musisz podaæ przedrostek");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}

					memset(NV.przed,0,8);
					strcpy(NV.przed,zn);
					NV.is_=true;
					if(!Save_NV())
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie mo¿na zapisaæ danych do bazy. ");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGERRProc);
						SetFocus(hwd);
					}
					else
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Zapisano przedrostek do bazy");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
					}
					break;
				}


				if(wp==DLG20_B3)				//przycisk anuluj
				{
					SetWindowText(GetDlgItem(hwd,DLG20_E1),NV.przed);
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
				EndDialog(hwd,0);
				break;
			}

		default: return DefDlgProc(GetParent(hwd),code,wp,lp);
	}
	return 0;
}


HWND PB,H13;
int indeks;
KASA_ KS_T[30];
bool is_term;
HANDLE mut;

DWORD WINAPI srch_fun(LPVOID pv)
{
	int i,j,k,licz,kod;
	char zn;
	char kon[350],txt[150];
	int szybk;
	bool bl;
	fstream pl;
	WIN32_FIND_DATA fdt;
	HANDLE hn;
	WORD prog;

	memset(KS_T,0,30*sizeof(KASA_));
	indeks=-1;
	if(PB==NULL || H13==NULL)
	{
		SendMessage(H13,WM_USER+3,0,0);
		return -1;
	}
	prog=0;
	for(j=1;j<=15;j++)
	{
		for(k=0;k<4;k++)
		{	
			WaitForSingleObject(mut,INFINITE);
			
			if(is_term)
			{
				ReleaseMutex(mut);
				SendMessage(H13,WM_USER+3,0,0);
				ExitThread(0);
				return 0;
			}else ReleaseMutex(mut);
			prog++;
			SendMessage(H13,WM_USER+1,(WPARAM)prog,0);
			memset(kon,0,350);
			if(k==0)szybk=9600;
				else if(k==1) szybk=19200;
				else if(k==2) szybk=28800;
				else if(k==3) szybk=57600;
			sprintf(kon,"$1\tCOM%d:%d:MUX0:1\t1\tJota",j,szybk);
			pl.open("KONFIG.txt",ios_base::in|ios_base::out|ios_base::trunc);
			if(!pl.is_open())
			{
				memset(Err_Text,0,350);
				sprintf(Err_Text,"Nie mo¿na utworzyæ pliku konfiguracyjnego potrzebnego do po³¹czenia siê z kas¹ fiskaln¹");
				DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),H13,(DLGPROC)&DLGERRProc);
				SetFocus(H13);
				SendMessage(H13,WM_USER+3,0,0);
				return -1;
			}
			pl.write((char*)kon,strlen(kon));
			pl.close();
			pl.open("Config/pin.in",ios_base::in|ios_base::out|ios_base::trunc);
			if(!pl.is_open())
			{
				memset(Err_Text,0,350);
				sprintf(Err_Text,"Nie mo¿na utworzyæ pliku wejœcia dla procedury");
				DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),H13,(DLGPROC)&DLGERRProc);
				SetFocus(H13);
				SendMessage(H13,WM_USER+3,0,0);
				return -1;
			}
			pl.write((char*)"#1\n#\n#",6);
			pl.close();
			pl.open("Config/pin.out",ios_base::in|ios_base::out|ios_base::trunc);
			if(!pl.is_open())
			{
				memset(Err_Text,0,350);
				sprintf(Err_Text,"Nie mo¿na utworzyæ pliku wyjœcia dla procedury");
				DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),H13,(DLGPROC)&DLGERRProc);
				SetFocus(H13);
				DeleteFile("Config/pin.in");
				SendMessage(H13,WM_USER+3,0,0);
				return -1;
			}
			pl.close();
				
			(*_ONrKasy)("Config/pin.in","Config/pin.out");
			hn=FindFirstFile("RAPORT.TXT",&fdt);
			if(hn==INVALID_HANDLE_VALUE)
			{
				memset(Err_Text,0,350);
				sprintf(Err_Text,"Nie mo¿na odnaleŸæ pliku raportu");
				DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),H13,(DLGPROC)&DLGERRProc);
				DeleteFile("Config/pin.in");
				DeleteFile("Config/pin.out");
				SetFocus(H13);
				SendMessage(H13,WM_USER+3,0,0);
				return -1;		
			}else
			kod=RAP(txt,150);
			
			if(kod==0)
			{
				indeks++;
				KS_T[indeks].Szybk=szybk;
				KS_T[indeks].timeout=5;
				KS_T[indeks].Com=j;
				KS_T[indeks].is_exist=true;
				KS_T[indeks].kanal=1;
				strcpy(KS_T[indeks].nazwa,txt);
				KS_T[indeks].rodz_pol=0;
				strcpy(KS_T[indeks].RU,"AnyString");
				sprintf(KS_T[indeks].end_str,"ADAPRIM_4321");
				i=get_num(txt,150);
				if(i==-1)
				{
					memset(Err_Text,0,350);
					sprintf(Err_Text,"Nie mo¿na otworzyæ pliku dajych wyjœciowych z kasy fiskalnej");
					DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),H13,(DLGPROC)&DLGERRProc);
					SetFocus(H13);
					DeleteFile("Config/pin.in");
					DeleteFile("Config/pin.out");
					SendMessage(H13,WM_USER+3,0,0);
					return -1;
				}
				strcpy(KS_T[indeks].numer,txt);


				SendMessage(H13,WM_USER+2,0,0);
			}
			
		}
	}
	SendMessage(H13,WM_USER+3,0,0);
	return 1;
}

int ind;


LRESULT _stdcall DLG21Proc(HWND hwd, int code, WPARAM wp, LPARAM lp)
{
	static	HANDLE thid;
	DWORD range;
	static float pr;
	int i,j;
	static int licz;
	char zn[5],txt[150];
	LVCOLUMN lvc;
	LVITEM lvi;

	switch(code)
	{
		
		case WM_INITDIALOG:
			{
				licz=0;
				ListView_SetExtendedListViewStyle(GetDlgItem(hwd,DLG21_LV1),LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_INFOTIP);
				ListView_DeleteAllItems(GetDlgItem(hwd,DLG21_LV1));
				for(i=0;i<5;i++)
				{
					lvc.mask=LVCF_WIDTH |LVCF_TEXT;
					lvc.pszText=LVD15[i];
					lvc.cx=LVD15_W[i];
					i=ListView_InsertColumn(GetDlgItem(hwd,DLG21_LV1),i,&lvc);
				}

				PB=GetDlgItem(hwd,DLG21_PB1);
				H13=hwd;
				range=MAKELONG((WORD)1,(WORD)60);
				SendMessage(PB,PBM_SETRANGE,0,(LPARAM)range);
				SendMessage(PB,PBM_SETPOS,(WPARAM)0,0);
				EnableWindow(GetDlgItem(hwd,DLG21_B3),false);
				EnableWindow(GetDlgItem(hwd,DLG21_B4),false);
				EnableWindow(GetDlgItem(hwd,DLG21_B2),false);
				EnableWindow(GetDlgItem(hwd,DLG21_B1),true);
				EnableWindow(GetDlgItem(hwd,DLG21_B5),false);
				is_term=false;
				mut=CreateMutex(NULL,false,"MUT");
				thid=CreateThread(NULL,0,&srch_fun,NULL,NORMAL_PRIORITY_CLASS,NULL);
				break;
			}
		case WM_USER+1:		//uaktualnienie pozycji progressbar

			{
				SendMessage(PB,PBM_SETPOS,wp,0);
				pr=(float)100/(float)60;
				pr=pr*(float)wp;
				if (wp==60) pr=100;
				memset(zn,0,5);
				sprintf(zn,"%d%%",(int)pr);
				SetWindowText(GetDlgItem(hwd,DLG21_T1),zn);
				break;
			}

		case WM_USER+2:			// wysy³ane kiedy znaleziono pod³¹czon¹ kasê
			{
				lvi.mask=LVIF_TEXT;
				lvi.iSubItem=0;
				lvi.iItem=licz;
				lvi.pszText=KS_T[indeks].nazwa;
				ListView_InsertItem(GetDlgItem(hwd,DLG21_LV1),&lvi);
				for(j=0;j<4;j++)
				{
					memset(txt,0,150);
					if(j==0) sprintf(txt,"%s",KS_T[indeks].numer); else
						if(j==1) sprintf(txt,"COM%d",KS_T[indeks].Com); else if(j==2) sprintf(txt,"%d",KS_T[indeks].Szybk);
						else if(j==3)
						{
							memset(txt,0,150);
							if(KS_T[indeks].rodz_pol==0) strcpy(txt,"Bezpoœrednio");
								else if(KS_T[indeks].rodz_pol==1) strcpy(txt,"Multiplekser 4-kana³owy");
									else if(KS_T[indeks].rodz_pol==2) strcpy(txt,"Modem");
										else if(KS_T[indeks].rodz_pol==3) strcpy(txt,"Prze³¹cznik multiplekserów");
											else if(KS_T[indeks].rodz_pol==4) strcpy(txt,"Multiplekser 8-kana³owy");
												else if(KS_T[indeks].rodz_pol==5) strcpy(txt,"Multiplekser LAN/Delta Max LAN/Jota E");
						}
					ListView_SetItemText(GetDlgItem(hwd,DLG21_LV1),licz,j+1,txt);
				}
				licz++;
				break;
			}

		case WM_USER+3:		// wysy³ane kiedy zakoñczona w¹tek wyszukuj¹cy kasy fiskalne
			{
				EnableWindow(GetDlgItem(hwd,DLG21_B1),false);
				EnableWindow(GetDlgItem(hwd,DLG21_B2),true);
				EnableWindow(GetDlgItem(hwd,DLG21_B5),true);
				i=ListView_GetItemCount(GetDlgItem(hwd,DLG21_LV1));
				if(i>0) 
				{
					EnableWindow(GetDlgItem(hwd,DLG21_B3),true);
					EnableWindow(GetDlgItem(hwd,DLG21_B4),true);
				}
				SendMessage(PB,PBM_SETPOS,(WPARAM)0,0);
				SetWindowText(GetDlgItem(hwd,DLG21_T1),"0%");
				if(mut!=NULL)
				{
					CloseHandle(mut);
					mut=NULL;
				}
				break;
			}


		case WM_COMMAND:
			{
				if(wp==DLG21_B1)		//przycisk anuluj
				{
					WaitForSingleObject(mut,INFINITE);
					is_term=true;
					ReleaseMutex(mut);
					break;
				}


				if(wp==DLG21_B2)		//Przycisk wyszukaj
				{
					SendMessage(hwd,WM_INITDIALOG,0,0);
					break;
				}

				if(wp==DLG21_B3)		//Zapisujê wybran¹ kasê do bazy
				{
					ind=ListView_GetSelectionMark(GetDlgItem(hwd,DLG21_LV1));
					if(ind<0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Musisz wybraæ pozycjê z listy kas");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),H13,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					DialogBox(hst,MAKEINTRESOURCE(ID_DLG_22),hwd,(DLGPROC)&DLG22Proc);
					SetFocus(hwd);
					break;
				}

				if(wp==DLG21_B5)		//przycisk wyjdŸ
				{
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
				if(mut!=NULL) 
				{
					CloseHandle(mut);
					mut=NULL;
				}
				EndDialog(hwd,0);
				break;
			}
		default: return DefDlgProc(GetParent(hwd),code,wp,lp);
	}
	return 0;
}


	//okno dialogowe zapisania wyszukanej kasy fiskalnej


LRESULT _stdcall DLG22Proc(HWND hwd, int code, WPARAM wp, LPARAM lp)
{
	LVCOLUMN lvc;
	LVITEM lvi;
	int i,licz,j;
	char txt[150];
	switch(code)
	{
		case WM_INITDIALOG:
			{	
				memset(Kas_ind,0,MAX_Kas);
				SendMessage(GetDlgItem(hwd,DLG22_B2),BM_SETIMAGE,0,(LPARAM)LoadBitmap(hst,MAKEINTRESOURCE(IDB_14)));
				SendMessage(GetDlgItem(hwd,DLG22_B1),BM_SETIMAGE,0,(LPARAM)LoadBitmap(hst,MAKEINTRESOURCE(IDB_15)));

				ListView_SetExtendedListViewStyle(GetDlgItem(hwd,DLG22_LV1),LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_INFOTIP);
				ListView_DeleteAllItems(GetDlgItem(hwd,DLG22_LV1));
				for(i=0;i<5;i++)
				{
					lvc.mask=LVCF_WIDTH |LVCF_TEXT;
					lvc.pszText=LVD15[i];
					lvc.cx=LVD15_W[i];
					ListView_InsertColumn(GetDlgItem(hwd,DLG22_LV1),i,&lvc);
				}
				licz=0;
				lvi.mask=LVIF_TEXT;
				lvi.iSubItem=0;
				for(i=0;i<MAX_Kas;i++)
				{
					if(KS[i].is_exist)
					{
						lvi.iItem=licz;
						lvi.pszText=KS[i].nazwa;
						ListView_InsertItem(GetDlgItem(hwd,DLG22_LV1),&lvi);
						Kas_ind[licz]=i;
						for(j=0;j<4;j++)
						{
							memset(txt,0,150);
							if(j==0) sprintf(txt,"%s",KS[i].numer); else
								if(j==1) sprintf(txt,"COM%d",KS[i].Com); else if(j==2) sprintf(txt,"%d",KS[i].Szybk);
								else if(j==3)
								{
									memset(txt,0,150);
									if(KS[i].rodz_pol==0) strcpy(txt,"Bezpoœrednio");
										else if(KS[i].rodz_pol==1) strcpy(txt,"Multiplekser 4-kana³owy");
											else if(KS[i].rodz_pol==2) strcpy(txt,"Modem");
												else if(KS[i].rodz_pol==3) strcpy(txt,"Prze³¹cznik multiplekserów");
													else if(KS[i].rodz_pol==4) strcpy(txt,"Multiplekser 8-kana³owy");
														else if(KS[i].rodz_pol==5) strcpy(txt,"Multiplekser LAN/Delta Max LAN/Jota E");
								}
							ListView_SetItemText(GetDlgItem(hwd,DLG22_LV1),licz,j+1,txt);
						}
						licz++;
					}
				}

				break;
			}
		case WM_COMMAND:
			{
				if(wp==DLG22_B3)			//przycisk wyjdŸ
				{
					DestroyWindow(hwd);
					break;
				}

				if(wp==DLG22_B1)		//przycisk zast¹p
				{
					i=ListView_GetSelectionMark(GetDlgItem(hwd,DLG22_LV1));
					if(i<0) 
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Musisz wybraæ pozycjê z listy");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),H13,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					memset(Query_Text,0,350);
					sprintf(Query_Text,"Czy napewno chcesz zast¹piæ wybran¹ kasê fiskaln¹ ?");
					DialogBox(hst,MAKEINTRESOURCE(DLG_Q),hwd,(DLGPROC)&DLGQProc);
					if(is_ok)
					{
						Kas_id=Kas_ind[i];
						KS[Kas_id]=KS_T[ind];
						if((Save_KS(true))==-1)
						{
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Nie mo¿na zapisaæ kasy , poniewa¿ plik fisk.dll jest uszkodzony",txt);
							DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
							SetFocus(hwd);
							break;
						}
						memset(Query_Text,0,350);
						sprintf(Query_Text,"Zapisano kasê w bazie danych\nCzy chcesz ustawiæ j¹ jako kasê domyœln¹ podczas komunikacji z komputerem?");
						DialogBox(hst,MAKEINTRESOURCE(DLG_Q),hwd,(DLGPROC)&DLGQProc);
						if(is_ok)
						{
							Default = Kas_id;
							Save_KS(false);
							
						}
					}
					SetFocus(hwd);
					SendMessage(hwd,WM_INITDIALOG,0,0);
					break;
				}

				if(wp==DLG22_B2)		//przycisk dodaj now¹
				{
					
					if(Count_Kas==30)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Zapisano ju¿ maksymaln¹ iloœæ kas w bazie danych");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),H13,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					i=-1;
					do
					{
						i++;

					}while(i<MAX_Kas && KS[i].is_exist!=false);
					KS[i]=KS_T[ind];
					if(Count_Kas==-1){Count_Kas=1;Default=1;} else Count_Kas++;
					if((Save_KS(true))==-1)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie mo¿na zapisaæ kasy , poniewa¿ plik fisk.dll jest uszkodzony",txt);
						DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
						SetFocus(hwd);
						break;
					}
					memset(Query_Text,0,350);
					sprintf(Query_Text,"Zapisano kasê w bazie danych\nCzy chcesz ustawiæ j¹ jako kasê domyœln¹ podczas komunikacji z komputerem?");
					DialogBox(hst,MAKEINTRESOURCE(DLG_Q),hwd,(DLGPROC)&DLGQProc);
					if(is_ok)
					{
						Default = i;
						Save_KS(false);
							
					}
					SendMessage(hwd,WM_INITDIALOG,0,0);
					SetFocus(hwd);
					
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
				EndDialog(hwd,0);
				is_dlg14=false;
				break;
			}
		default: return DefDlgProc(GetParent(hwd),code,wp,lp);
	}

	return 0;
}



	//okno dialogowe zmiany domyœlnej kasy fiskalnej

LRESULT _stdcall DLG23Proc(HWND hwd, int code, WPARAM wp, LPARAM lp)

{

	LVCOLUMN lvc;
	LVITEM lvi;
	int i,licz,j,def;
	char txt[150];
	static 	bool is_act=false;

	switch(code)
	{
		case WM_INITDIALOG:
			{	
				is_wyb_k=false;
				if(is_tow)
				{
					SetWindowText(hwd,"Pobieranie towarów");
					SetWindowText(GetDlgItem(hwd,DLG23_B2),"Pobierz towary z kasy fiskalnej");
				}
				memset(Kas_ind,0,MAX_Kas);
				SendMessage(GetDlgItem(hwd,DLG23_B2),BM_SETIMAGE,0,(LPARAM)LoadBitmap(hst,MAKEINTRESOURCE(IDB_14)));
				SendMessage(GetDlgItem(hwd,DLG23_B1),BM_SETIMAGE,0,(LPARAM)LoadBitmap(hst,MAKEINTRESOURCE(IDB_15)));

				ListView_SetExtendedListViewStyle(GetDlgItem(hwd,DLG23_LV1),LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_INFOTIP);
				ListView_DeleteAllItems(GetDlgItem(hwd,DLG23_LV1));
				if(!is_act)
				{
					for(i=0;i<5;i++)
					{
						lvc.mask=LVCF_WIDTH |LVCF_TEXT;
						lvc.pszText=LVD15[i];
						lvc.cx=LVD15_W[i];
						ListView_InsertColumn(GetDlgItem(hwd,DLG23_LV1),i,&lvc);
					}
					is_act=true;
				}
				licz=0;
				lvi.iSubItem=0;
				lvi.state=0;
				for(i=0;i<MAX_Kas;i++)
				{
					if(KS[i].is_exist)
					{
						if(i==Default) 
						{
							lvi.mask=LVIF_TEXT|LVIF_STATE;
							def=i;
							lvi.state=LVIS_SELECTED | LVIS_FOCUSED;
						}else lvi.mask=LVIF_TEXT;
						
						lvi.iItem=licz;
						lvi.pszText=KS[i].nazwa;
						ListView_InsertItem(GetDlgItem(hwd,DLG23_LV1),&lvi);
						Kas_ind[licz]=i;
						for(j=0;j<4;j++)
						{
							memset(txt,0,150);
							if(j==0) sprintf(txt,"%s",KS[i].numer); else
								if(j==1) sprintf(txt,"COM%d",KS[i].Com); else if(j==2) sprintf(txt,"%d",KS[i].Szybk);
								else if(j==3)
								{
									memset(txt,0,150);
									if(KS[i].rodz_pol==0) strcpy(txt,"Bezpoœrednio");
										else if(KS[i].rodz_pol==1) strcpy(txt,"Multiplekser 4-kana³owy");
											else if(KS[i].rodz_pol==2) strcpy(txt,"Modem");
												else if(KS[i].rodz_pol==3) strcpy(txt,"Prze³¹cznik multiplekserów");
													else if(KS[i].rodz_pol==4) strcpy(txt,"Multiplekser 8-kana³owy");
														else if(KS[i].rodz_pol==5) strcpy(txt,"Multiplekser LAN/Delta Max LAN/Jota E");
								}
							ListView_SetItemText(GetDlgItem(hwd,DLG23_LV1),licz,j+1,txt);
						}
						licz++;
					}
				}
				ListView_SetSelectionMark(GetDlgItem(hwd,DLG23_LV1),Default);
				break;
			}
	
		case WM_COMMAND:
			{
				if(wp==DLG23_B1)			//przycisk wyjdŸ
				{
					is_tow=true;
					funkcja=false;
					DestroyWindow(hwd);
					break;
				}
				if(wp==DLG23_B2)		//przycisk wybrania kasy
				{
					i=ListView_GetSelectionMark(GetDlgItem(hwd,DLG23_LV1));
					if(i<0) 
						{
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Musisz wybraæ pozycjê z listy");
							DialogBox(hst,MAKEINTRESOURCE(DLG_I),H13,(DLGPROC)&DLGIProc);
							SetFocus(hwd);
							break;
						}
					Kas_id=Kas_ind[i];
				
					if(!is_tow && !funkcja)
					{
						memset(Query_Text,0,350);
						sprintf(Query_Text,"Czy chcesz ustawiæ wybran¹ kasê jako kasê domyœln¹ podczas komunikacji z komputerem?");
						DialogBox(hst,MAKEINTRESOURCE(DLG_Q),hwd,(DLGPROC)&DLGQProc);
						if(is_ok)
						{
							Default = Kas_id;
							Save_KS(false);
							
						}
						SetFocus(hwd);
					}else
					{
						is_tow=false;
						DestroyWindow(hwd);
						break;
					}
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
				EndDialog(hwd,0);
				is_dlg14=false;
				is_act=false;
				break;
			}
		default: return DefDlgProc(GetParent(hwd),code,wp,lp);
	}

	return 0;
}


HWND H24;

HANDLE mut1;
bool is_end;
int max_t,j_cnt,v_cnt,gr_cnt,ins_cnt,ind_tow,ind_tow1;
Artykuly *AT;
JM * jm_t;
ST_VAT *v_t;
GR_T *grt;

DWORD WINAPI Otow(LPVOID pv)
{
	fstream pl;
	char con_str[350],txt[350];
	int i,j,k,cnt,resz;
	bool bl;
	int licz,l;

	cnt=max_t/100;
	resz=max_t%100;
	licz=0;
	ind_tow=0;
	ind_tow1=0;
	
	bl=false;
	for(k=0;k<cnt;k++)
	{

		WaitForSingleObject(mut1,INFINITE);
		if(is_end)
		{
			ReleaseMutex(mut1);
			SendMessage(H24,WM_USER+4,0,0);
			ExitThread(0);
		}
		ReleaseMutex(mut1);
		pl.open("Config/pin.in",ios_base::in|ios_base::out|ios_base::trunc);
		if(!pl.is_open())
		{
			memset(Err_Text,0,350);
			sprintf(Err_Text,"Nie mo¿na utworzyæ pliku wejœcia dla procedury");
			DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),H24,(DLGPROC)&DLGERRProc);
			SetFocus(H24);
			SendMessage(H24,WM_USER+1,0,0);
			return -1;
		}
		memset(con_str,0,350);
		sprintf(con_str,"#%s\n#\n#\n",KS[Kas_id].numer);
		pl.write(con_str,strlen(con_str));
		if(!bl)l=100;
		else 
		{
			l=cnt;
			k=cnt;
		}
		for(j=0;j<l;j++)
		{
			licz++;
			memset(con_str,0,350);
			sprintf(con_str,"$%d\n",licz);
			pl.write(con_str,strlen(con_str));
		}
		pl.close();

		pl.open("Config/pin.out",ios_base::in|ios_base::out|ios_base::trunc);
		if(!pl.is_open())
		{
			memset(Err_Text,0,350);
			sprintf(Err_Text,"Nie mo¿na utworzyæ pliku wyjœcia dla procedury");
			DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),H24,(DLGPROC)&DLGERRProc);
			SetFocus(H24);
			DeleteFile("Config/pin.in");
			SendMessage(H24,WM_USER+1,0,0);
			return -1;
		}
		pl.close();
		
		(*_OTowar)("Config/pin.in","Config/pin.out");
		i=RAP(NULL,0);
		if(i==-1)
		{
			memset(Err_Text,0,350);
			LoadString(hst,i+1000,txt,350);
			sprintf(Err_Text,"Nie mo¿na otworzyæ pliku raportu");
			DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),H24,(DLGPROC)&DLGERRProc);
			SendMessage(H24,WM_USER+1,0,0);
			SetFocus(H24);
			SendMessage(H24,WM_USER+1,0,0);
			return -1;
		}
		if(i==0)
		{
			if(k<cnt)ins_cnt=100;else ins_cnt=resz;
			ind_tow1=ind_tow;
			get_tow(AT,&ind_tow,jm_t,v_t,grt,j_cnt,gr_cnt,ins_cnt);
			SendMessage(H24,WM_USER+2,(WPARAM)licz,(LPARAM)ind_tow1);
		}else
		{
			memset(Err_Text,0,350);
			LoadString(hst,i+1000,txt,350);
			sprintf(Err_Text,"Nie mo¿na wykonaæ operacji\n%s",txt);
			DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),H24,(DLGPROC)&DLGERRProc);
			SetFocus(H24);
			SendMessage(H24,WM_USER+1,0,0);
			return -1;
		}
		if(k+1==cnt)
		{
			k=0;
			cnt=resz;
			bl=true;
		}
	}
	
	SendMessage(H24,WM_USER+3,0,0);

	return 0;
}

HWND LV24;
int *same;
int *same1;
int ile_dod;

DWORD WINAPI Dod_tow(PVOID pv)
{
	int i,j,code,l;
	int i_cnt;

	code=(int)pv;
	char zn[150];
	int a;
	bool is_same;

	ile_dod=0;
	if(code==0)
	{
		i_cnt=ListView_GetSelectedCount(LV24);
		l=0;
		j=ListView_GetItemCount(LV24);
		if(j<=0) return 0;
		
		for(i=0;i<j;i++)
		{	
			WaitForSingleObject(mut1,INFINITE);
			if(is_end)
			{
				ReleaseMutex(mut1);
				SendMessage(H24,WM_USER+6,0,0);
				ExitThread(0);
			}
		ReleaseMutex(mut1);
			a=0;
			a=ListView_GetItemState(LV24,i,LVIS_SELECTED);
			if(a>0)
			{
				AT[i].exist=true;
				AT[i].IDA=HD_A.LastID+1;
				Dodaj_AR(&AT[i]);
				ile_dod++;
				l++;
				if(l==i_cnt)
				{
					SendMessage(H24,WM_USER+6,0,0);
					return 1;
				}
			}
			SendMessage(H24,WM_USER+5,(WPARAM)i,0);
		}
		SendMessage(H24,WM_USER+6,0,0);
		return 1;
	}else
		if(code==1)
		{
			
			j=ListView_GetItemCount(LV24);
			if(j<=0) return 0;
		
			for(i=0;i<j;i++)
			{	
				WaitForSingleObject(mut1,INFINITE);
				if(is_end)
				{
					ReleaseMutex(mut1);
					SendMessage(H24,WM_USER+6,0,0);
					ExitThread(0);
				}
				ReleaseMutex(mut1);
				
				AT[i].exist=true;
				AT[i].IDA=HD_A.LastID+1;
				Dodaj_AR(&AT[i]);
				ile_dod++;
				SendMessage(H24,WM_USER+5,(WPARAM)i,0);
			}
			SendMessage(H24,WM_USER+6,0,0);
			return 1;
		}
		else 
		if(code==2)
		{
			j=ListView_GetItemCount(LV24);
			if(j<=0) return 0;
			if(same!=NULL)
			{
				delete same;
				same=NULL;
			}
			if(same1!=NULL)
			{
				delete same1;
				same1=NULL;
			}
			same=new int[j+1];
			same1=new int[j];
			memset(same,-1,sizeof(int)*(j+1));
			memset(same1,-1,sizeof(int)*j);
			l=-1;
			for(i=0;i<j;i++)
			{	
				WaitForSingleObject(mut1,INFINITE);
				if(is_end)
				{
					ReleaseMutex(mut1);
					SendMessage(H24,WM_USER+6,0,0);
					ExitThread(0);
				}
				is_same=false;
				ReleaseMutex(mut1);
				for(a=0;a<HD_A.count;a++)
				{
					if(strcmp(ART[a].Nazwa,AT[i].Nazwa)==0 || strcmp(ART[a].KOD_TOW,AT[i].KOD_TOW)==0)
					{
						l++;
						same[l]=i;
						same1[l]=a;
						is_same=true;
						break;
					}
				}
				if(!is_same)
				{
					AT[i].exist=true;
					AT[i].IDA=HD_A.LastID+1;
					Dodaj_AR(&AT[i]);
					ile_dod++;
				}
				
				SendMessage(H24,WM_USER+5,(WPARAM)i,0);
			}
			if(same[0]!=-1)
			{
				SetFocus(H24);
				memset(Err_Text,0,350);
				sprintf(Err_Text,"W bazie danych znajduj¹ siê towary o tych samych nazwach.\nNale¿y wybraæ jedn¹ z mo¿liwoœci...");
				DialogBox(hst,MAKEINTRESOURCE(DLG_I),H24,(DLGPROC)&DLGIProc);
				SetFocus(H24);
				DialogBox(hst,MAKEINTRESOURCE(ID_DLG_25),H24,(DLGPROC)&DLG25Proc);
				SetFocus(H24);
			}
			SendMessage(H24,WM_USER+6,0,0);
			return 1;

		}
	return 1;
}

LRESULT _stdcall DLG24Proc(HWND hwd, int code, WPARAM wp, LPARAM lp)
{
	fstream pl;
	char con_str[350],txt[350],zn[350];
	int i,i1,i2;
	static int count;
	HANDLE thid;
	DWORD range;
	float pr;
	LVCOLUMN lcl;
	LVITEM lvi;
	LPSTR LPS;

	switch(code)
	{
		case WM_INITDIALOG:
			{
				ListView_SetExtendedListViewStyle(GetDlgItem(hwd,DLG24_LV1),LVS_EX_AUTOSIZECOLUMNS|LVS_EX_FULLROWSELECT|LVS_EX_LABELTIP|LVS_EX_GRIDLINES|LVS_EX_ONECLICKACTIVATE | LVS_EX_REGIONAL);
				lcl.mask=LVCF_TEXT|LVCF_WIDTH;
				for(i=0;i<12;i++)
				{
					lcl.pszText=LV1_Col[i];
					lcl.cx=LV1_Width[i];
					ListView_InsertColumn(GetDlgItem(hwd,DLG24_LV1),i,&lcl);
				}
				H24=hwd;
				mut1=CreateMutex(NULL,false,"mut1");
				is_end=false;
				if(jm_t!=NULL)
				{
					delete jm_t;
					jm_t=NULL;
				}
				j_cnt=99;
				jm_t=new JM[j_cnt];
				
				i=get_data(KS[Kas_id],&count,_OIlZaPLU,NULL,0);
				if(i==-1)
				{
					memset(Err_Text,0,350);
					sprintf(Err_Text,"Nie mo¿na utworzyæ pliku danych wyjœciowych kasy fiskalnej");
					DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),H24,(DLGPROC)&DLGERRProc);
					SetFocus(hwd);
					DestroyWindow(hwd);
					break;
				}else
				if(i>0)
				{
					memset(Err_Text,0,350);
					LoadString(hst,i+1000,txt,350);
					sprintf(Err_Text,"Nie mo¿na wykonaæ operacji\n%s",txt);
					DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
					SetFocus(hwd);
					DestroyWindow(hwd);
					break;
				}
				i=get_data(KS[Kas_id],&max_t,_ONrTowar,NULL,0);
				if(i==-1)
				{
					memset(Err_Text,0,350);
					sprintf(Err_Text,"Nie mo¿na utworzyæ pliku danych wyjœciowych kasy fiskalnej");
					DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),H24,(DLGPROC)&DLGERRProc);
					SetFocus(hwd);
					DestroyWindow(hwd);
					break;
				}else
				if(i>0)
				{
					memset(Err_Text,0,350);
					LoadString(hst,i+1000,txt,350);
					sprintf(Err_Text,"Nie mo¿na wykonaæ operacji\n%s",txt);
					DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
					SetFocus(hwd);
					DestroyWindow(hwd);
					break;
				}
				v_cnt=99;
				v_t=new ST_VAT[v_cnt];
				i=get_vat(&KS[Kas_id],v_t,&v_cnt);
				if(i==-2)
				{
					delete v_t;
					v_t=new ST_VAT[v_cnt];
					i=get_vat(&KS[Kas_id],v_t,&v_cnt);
				}
				if(i==-1)
				{
					memset(Err_Text,0,350);
					sprintf(Err_Text,"Nie mo¿na utworzyæ pliku danych wyjœciowych kasy fiskalnej");
					DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),H24,(DLGPROC)&DLGERRProc);
					SetFocus(hwd);
					delete v_t;
					v_t=NULL;
					DestroyWindow(hwd);
					break;
				}else
				if(i==-2)
				{
					delete v_t;
					v_t=new ST_VAT[v_cnt];
					i=get_vat(&KS[Kas_id],v_t,&v_cnt);
				}
				i=get_jm(&KS[Kas_id],jm_t,&j_cnt);
				if(i==-1)
				{
					memset(Err_Text,0,350);
					sprintf(Err_Text,"Nie mo¿na utworzyæ pliku danych wyjœciowych kasy fiskalnej");
					DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),H24,(DLGPROC)&DLGERRProc);
					SetFocus(hwd);
					delete jm_t;
					jm_t=NULL;
					DestroyWindow(hwd);
					break;
				}else
				if(i==-2)
				{
					delete jm_t;
					jm_t=new JM[j_cnt];
					i=get_jm(&KS[Kas_id],jm_t,&j_cnt);
				}else
				if(i>0)
				{
					memset(Err_Text,0,350);
					LoadString(hst,i+1000,txt,350);
					sprintf(Err_Text,"Nie mo¿na wykonaæ operacji\n%s",txt);
					DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
					SetFocus(hwd);
					delete jm_t;
					jm_t=NULL;
					DestroyWindow(hwd);
					break;
				}


				gr_cnt=99;
				grt=new GR_T[gr_cnt];

				i=get_gr(&KS[Kas_id],grt,&gr_cnt);
				if(i==-1)
				{
					memset(Err_Text,0,350);
					sprintf(Err_Text,"Nie mo¿na utworzyæ pliku danych wyjœciowych kasy fiskalnej");
					DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),H24,(DLGPROC)&DLGERRProc);
					SetFocus(hwd);
					delete jm_t;
					jm_t=NULL;
					DestroyWindow(hwd);
					break;
				}else
				if(i==-2)
				{
					delete grt;
					grt=new GR_T[gr_cnt];
					i=get_gr(&KS[Kas_id],grt,&gr_cnt);
				}else
				if(i>0)
				{
					memset(Err_Text,0,350);
					LoadString(hst,i+1000,txt,350);
					sprintf(Err_Text,"Nie mo¿na wykonaæ operacji\n%s",txt);
					DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
					SetFocus(hwd);
					delete grt;
					grt=NULL;
					DestroyWindow(hwd);
					break;
				}

				SetWindowText(GetDlgItem(hwd,DLG24_T2),"Pobieranie towarów z kasy fiskalnej.....");
				range=MAKELONG((DWORD)1,(DWORD)max_t);
				SendMessage(GetDlgItem(hwd,DLG24_PB1),PBM_SETRANGE,0,(LPARAM)range);
				SendMessage(GetDlgItem(hwd,DLG24_PB1),PBM_SETPOS,(WPARAM)0,0);
				AT=new Artykuly[count];
				memset(AT,0,sizeof(Artykuly)*count);
				EnableWindow(GetDlgItem(hwd,DLG24_B2),false);
				EnableWindow(GetDlgItem(hwd,DLG24_B3),false);
				EnableWindow(GetDlgItem(hwd,DLG24_B4),false);
				EnableWindow(GetDlgItem(hwd,DLG24_B5),false);
				thid=CreateThread(NULL,0,Otow,NULL,NORMAL_PRIORITY_CLASS,NULL);
				break;
			}

		case WM_USER+1:		// w¹tek zakoñczono niepowodzweniem
			{

				SendMessage(GetDlgItem(hwd,DLG24_PB1),PBM_SETPOS,(WPARAM)0,0);
				EnableWindow(GetDlgItem(hwd,DLG24_B2),true);
				EnableWindow(GetDlgItem(hwd,DLG24_B3),true);
				EnableWindow(GetDlgItem(hwd,DLG24_B4),true);
				EnableWindow(GetDlgItem(hwd,DLG24_B5),true);
				SetWindowText(GetDlgItem(hwd,DLG24_T1),"0%");
				SetFocus(hwd);
				break;
			}

		case WM_USER+2:		//aktualizacja progressbar
			{
				SendMessage(GetDlgItem(hwd,DLG24_PB1),PBM_SETPOS,wp,0);
				pr=(float)100/(float)max_t;
				pr=pr*(float)wp;
				if (wp==max_t) pr=100;
				memset(zn,0,350);
				sprintf(zn,"%d%%",(int)pr);
				SetWindowText(GetDlgItem(hwd,DLG24_T1),zn);

				lvi.mask=LVIF_TEXT;
				lvi.iSubItem=0;
				
				for(i=ind_tow1;i<ind_tow;i++)
				{
					lvi.iItem=i;
					lvi.cchTextMax=sizeof(Artykuly);
					lvi.pszText=AT[i].Nazwa; 
					i2=ListView_InsertItem(GetDlgItem(hwd,DLG24_LV1),&lvi);
					for(i1=1;i1<12;i1++)
					{
						memset(zn,0,350);
						LPS=zn;
						AT[i].Stan=0;
						if(i1==1)LPS=AT[i].Producent;else if(i1==2)dbl_str(AT[i].Stan,LPS,2,350);else if(i1==3)LPS=AT[i].JM;else if(i1==4)
						{
							memset(zn,0,350);
							dbl_str(AT[i].Cena_Zakupu,zn,2,350);
							strcpy(zn+strlen(zn)," ");
							strcpy(zn+strlen(zn),wal[cnt.def_wal].znak);
						}else 
							if(i1==5)dbl_str(AT[i].Marza,LPS,2,350); else if(i1==6) 
							{
								memset(zn,0,350);
								dbl_str(AT[i].Cena_Netto,zn,2,350);
								strcpy(zn+strlen(zn)," ");
								strcpy(zn+strlen(zn),wal[cnt.def_wal].znak);

							}else 
								if(i1==7) dbl_str(AT[i].VAT,LPS,2,350); else
								if(i1==8) 
								{
									memset(zn,0,350);
									dbl_str(AT[i].Cena_Brutto,zn,2,350);
									strcpy(zn+strlen(zn)," ");
									strcpy(zn+strlen(zn),wal[cnt.def_wal].znak); 
								}else 
									if(i1==9) dbl_str(AT[i].Stan,LPS,2,350); else
										if(i1==10) LPS=AT[i].KOD_TOW;else
											if(i1==11)LPS=AT[i].KOD_KR;
						ListView_SetItemText(GetDlgItem(hwd,DLG24_LV1),i2,i1,LPS);
					}
				}
				break;
			}

		case WM_USER+3:
			{
				memset(Err_Text,0,350);
				sprintf(Err_Text,"Ukoñczono pobieranie towarów");
				DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
				SetFocus(hwd);
				SetWindowText(GetDlgItem(hwd,DLG24_T1),"0%");
				SetWindowText(GetDlgItem(hwd,DLG24_T2),"");
				SendMessage(GetDlgItem(hwd,DLG24_PB1),PBM_SETPOS,(WPARAM)0,0);
				EnableWindow(GetDlgItem(hwd,DLG24_B2),true);
				EnableWindow(GetDlgItem(hwd,DLG24_B3),true);
				EnableWindow(GetDlgItem(hwd,DLG24_B4),true);
				EnableWindow(GetDlgItem(hwd,DLG24_B5),true);
				break;
			}

			case WM_USER+4:
			{
				SetFocus(hwd);
				SetWindowText(GetDlgItem(hwd,DLG24_T1),"0%");
				SetWindowText(GetDlgItem(hwd,DLG24_T2),"");
				SendMessage(GetDlgItem(hwd,DLG24_PB1),PBM_SETPOS,(WPARAM)0,0);
				EnableWindow(GetDlgItem(hwd,DLG24_B2),true);
				EnableWindow(GetDlgItem(hwd,DLG24_B3),true);
				EnableWindow(GetDlgItem(hwd,DLG24_B4),true);
				EnableWindow(GetDlgItem(hwd,DLG24_B5),true);
				break;
			}

			case WM_USER+5:			//aktualizacja progress podczas dodawania towarów do bazy
			{
				SendMessage(GetDlgItem(hwd,DLG24_PB1),PBM_SETPOS,wp,0);
				pr=(float)100/(float)max_t;
				pr=pr*(float)wp;
				if (wp>=(max_t-1)) pr=100;
				memset(zn,0,350);
				sprintf(zn,"%d%%",(int)pr);
				SetWindowText(GetDlgItem(hwd,DLG24_T1),zn);
				break;
			}

			case WM_USER+6:
			{
				SetFocus(hwd);
				SetWindowText(GetDlgItem(hwd,DLG24_T1),"0%");
				SetWindowText(GetDlgItem(hwd,DLG24_T2),"");
				SendMessage(GetDlgItem(hwd,DLG24_PB1),PBM_SETPOS,(WPARAM)0,0);
				memset(Err_Text,0,350);
				sprintf(Err_Text,"Ukoñczono zapisywanie towarów\nIloœæ dodanych towarów %d",ile_dod);
				DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
				SetFocus(hwd);
				EnableWindow(GetDlgItem(hwd,DLG24_B2),true);
				EnableWindow(GetDlgItem(hwd,DLG24_B3),true);
				EnableWindow(GetDlgItem(hwd,DLG24_B4),true);
				EnableWindow(GetDlgItem(hwd,DLG24_B5),true);
				if(same!=NULL)
				{
					delete same;
					same=NULL;
				}
				if(same1!=NULL)
				{
					delete same1;
					same1=NULL;
				}
				break;
			}

		case WM_COMMAND:
			{

				if(wp==DLG24_B1)	//przycisk anuluj pobieranie
				{
					WaitForSingleObject(mut1,INFINITE);
					is_end=true;
					ReleaseMutex(mut1);
					break;
				}

				if(wp==DLG24_B2)			//przycisk dodaj zaznaczone towary
				{
					i=ListView_GetSelectedCount(GetDlgItem(hwd,DLG24_LV1));
					if(i<=0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie zaznaczono ¿adnej pozycji z tabeli");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}

					if(HD_A.count+i>=MAX_ART)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Baza danych jest ju¿ pe³na. Zaznaczono za du¿o towarów");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}

					SetWindowText(GetDlgItem(hwd,DLG24_T2),"Dodawanie towarów do bazy danych.....");
					max_t=ListView_GetItemCount(GetDlgItem(hwd,DLG24_LV1));
					range=MAKELONG((DWORD)1,(DWORD)max_t);
					SendMessage(GetDlgItem(hwd,DLG24_PB1),PBM_SETRANGE,0,(LPARAM)range);
					SendMessage(GetDlgItem(hwd,DLG24_PB1),PBM_SETPOS,(WPARAM)0,0);
					LV24=GetDlgItem(hwd,DLG24_LV1);
					EnableWindow(GetDlgItem(hwd,DLG24_B2),false);
					EnableWindow(GetDlgItem(hwd,DLG24_B3),false);
					EnableWindow(GetDlgItem(hwd,DLG24_B4),false);
					EnableWindow(GetDlgItem(hwd,DLG24_B5),false);
					is_end=false;
					CreateThread(NULL,0,Dod_tow,(PVOID)0,NORMAL_PRIORITY_CLASS,NULL);
					break;
				}

				if(wp==DLG24_B3)			//przycisk wyjdŸ
				{
					DestroyWindow(hwd);
					break;
				}


				if(wp==DLG24_B5 || wp==DLG24_B4)			//przycisk dodaj  towary
				{
					i=ListView_GetItemCount(GetDlgItem(hwd,DLG24_LV1));
					if(i<=0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie ma ¿adnej pozycji na liœcie");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}

					if(HD_A.count+i>MAX_ART)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Baza danych jest ju¿ pe³na. Zaznaczono za du¿o towarów");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}

					SetWindowText(GetDlgItem(hwd,DLG24_T2),"Dodawanie towarów do bazy danych.....");
					max_t=ListView_GetItemCount(GetDlgItem(hwd,DLG24_LV1));
					range=MAKELONG((DWORD)1,(DWORD)max_t);
					SendMessage(GetDlgItem(hwd,DLG24_PB1),PBM_SETRANGE,0,(LPARAM)range);
					SendMessage(GetDlgItem(hwd,DLG24_PB1),PBM_SETPOS,(WPARAM)0,0);
					LV24=GetDlgItem(hwd,DLG24_LV1);
					EnableWindow(GetDlgItem(hwd,DLG24_B2),false);
					EnableWindow(GetDlgItem(hwd,DLG24_B3),false);
					EnableWindow(GetDlgItem(hwd,DLG24_B4),false);
					EnableWindow(GetDlgItem(hwd,DLG24_B5),false);
					is_end=false;
					if(wp==DLG24_B5) CreateThread(NULL,0,Dod_tow,(PVOID)1,NORMAL_PRIORITY_CLASS,NULL);else
						CreateThread(NULL,0,Dod_tow,(PVOID)2,NORMAL_PRIORITY_CLASS,NULL);
					break;
				}


				break;
			}

		case WM_CLOSE:
			{
				//DestroyWindow(hwd);
				break;
			}

		case WM_DESTROY:
			{
				is_end=true;
				if(AT!=NULL)
				{
					delete AT;
					AT=NULL;
				}
				if(v_t!=NULL)
				{
					delete v_t;
					v_t=NULL;
				}
				if(jm_t!=NULL)
				{
					delete jm_t;
					jm_t=NULL;
				}
				if(same!=NULL)
				{
					delete same;
					same=NULL;
				}
				if(same1!=NULL)
				{
					delete same1;
					same1=NULL;
				}
				EndDialog(hwd,0);
				break;
			}
		default: return DefDlgProc(GetParent(hwd),code,wp,lp);
	}

	return 0;
}




HWND LV25;
HWND H25;
int ile_dod1;

DWORD WINAPI Dod_tow1(PVOID pv)
{
	int i,j,code,l;
	int i_cnt;

	code=(int)pv;
	char zn[150];
	int a;
	bool is_same;

	ile_dod1=0;
	code=(int)pv;
	if(code==0)
	{
		i_cnt=ListView_GetSelectedCount(LV25);
		l=0;
		j=ListView_GetItemCount(LV25);
		if(j<=0) return 0;
		
		for(i=0;i<j;i++)
		{	
			
			a=0;
			a=ListView_GetItemState(LV25,i,LVIS_SELECTED);
			if(a>0)
			{
				AT[same[i]].exist=true;
				AT[same[i]].indeks=ART[same1[i]].indeks;
				AT[same[i]].IDA=ART[same1[i]].IDA;
				AT[same[i]].Stan=ART[same1[i]].Stan;
				if(ART[same1[i]].Cena_Zakupu>0)
				{
					AT[same[i]].Cena_Zakupu=ART[same1[i]].Cena_Zakupu;
					AT[same[i]].Marza=(AT[same[i]].Cena_Netto/AT[same[i]].Cena_Zakupu-1)*100;
				}

				memcpy(&ART[same1[i]],&AT[same[i]],sizeof(Artykuly));
				Save_AR(&AT[same[i]]);
				ile_dod1++;
				l++;
				if(l==i_cnt)
				{
					SendMessage(H25,WM_USER+6,0,0);
					return 1;
				}
			}
			SendMessage(H25,WM_USER+5,(WPARAM)i,0);
		}
		SendMessage(H24,WM_USER+6,0,0);
		return 1;
	}else
		if(code==1)
		{
			
			j=ListView_GetItemCount(LV25);
			if(j<=0) return 0;
		
			for(i=0;i<j;i++)
			{	
				
				AT[same[i]].exist=true;
				AT[same[i]].indeks=ART[same1[i]].indeks;
				AT[same[i]].IDA=ART[same1[i]].IDA;
				AT[same[i]].Stan=ART[same1[i]].Stan;
				if(ART[same1[i]].Cena_Zakupu>0)
				{
					AT[same[i]].Cena_Zakupu=ART[same1[i]].Cena_Zakupu;
					AT[same[i]].Marza=(AT[same[i]].Cena_Netto/AT[same[i]].Cena_Zakupu-1)*100;
				}
				memcpy(&ART[same1[i]],&AT[same[i]],sizeof(Artykuly));
				Save_AR(&AT[same[i]]);
				ile_dod1++;
				SendMessage(H25,WM_USER+5,(WPARAM)i,0);
			}
			Sleep(1000);
			SendMessage(H25,WM_USER+6,0,0);
			return 1;
		}
	
	return 1;
}


//okno dialogowe zapisywania tych samych towarów


LRESULT _stdcall DLG25Proc(HWND hwd, int code, WPARAM wp, LPARAM lp)
{
	LVCOLUMN lcl;
	LVITEM lvi;
	int i,i2,i1;
	char zn[350];
	LPSTR LPS;
	DWORD range;
	static int maxT;
	float pr;

	switch(code)
	{
		case WM_INITDIALOG:
			{
				SetWindowText(GetDlgItem(hwd,DLG25_T1),"0%");
				H25=hwd;
				LV25=GetDlgItem(hwd,DLG25_LV1);
				CheckDlgButton(hwd,DLG25_RB1,BST_CHECKED);
				ListView_SetExtendedListViewStyle(GetDlgItem(hwd,DLG25_LV1),LVS_EX_AUTOSIZECOLUMNS|LVS_EX_FULLROWSELECT|LVS_EX_LABELTIP|LVS_EX_GRIDLINES|LVS_EX_ONECLICKACTIVATE | LVS_EX_REGIONAL);
				lcl.mask=LVCF_TEXT|LVCF_WIDTH;
				for(i=0;i<12;i++)
				{
					lcl.pszText=LV1_Col[i];
					lcl.cx=LV1_Width[i];
					ListView_InsertColumn(GetDlgItem(hwd,DLG25_LV1),i,&lcl);
				}

				lvi.mask=LVIF_TEXT;
				lvi.iSubItem=0;
				i=0;
				while(same[i]!=-1)
				{
					lvi.iItem=i;
					lvi.cchTextMax=sizeof(Artykuly);
					lvi.pszText=AT[same[i]].Nazwa; 
					i2=ListView_InsertItem(GetDlgItem(hwd,DLG25_LV1),&lvi);
					for(i1=1;i1<12;i1++)
					{
						memset(zn,0,350);
						LPS=zn;
						if(i1==1)LPS=AT[same[i]].Producent;else if(i1==2)dbl_str(AT[same[i]].Stan,LPS,2,350);else if(i1==3)LPS=AT[same[i]].JM;else if(i1==4)
						{
							memset(zn,0,350);
							dbl_str(AT[same[i]].Cena_Zakupu,zn,2,350);
							strcpy(zn+strlen(zn)," ");
							strcpy(zn+strlen(zn),wal[cnt.def_wal].znak);
						}else 
							if(i1==5)dbl_str(AT[same[i]].Marza,LPS,2,350); else if(i1==6) 
							{
								memset(zn,0,350);
								dbl_str(AT[same[i]].Cena_Netto,zn,2,350);
								strcpy(zn+strlen(zn)," ");
								strcpy(zn+strlen(zn),wal[cnt.def_wal].znak);

							}else 
								if(i1==7) dbl_str(AT[same[i]].VAT,LPS,2,350); else
								if(i1==8) 
								{
									memset(zn,0,350);
									dbl_str(AT[same[i]].Cena_Brutto,zn,2,350);
									strcpy(zn+strlen(zn)," ");
									strcpy(zn+strlen(zn),wal[cnt.def_wal].znak); 
								}else 
									if(i1==9) itoa(AT[same[i]].Stan_Kr,LPS,10); else
										if(i1==10) LPS=AT[same[i]].KOD_TOW;else
											if(i1==11)LPS=AT[same[i]].KOD_KR;
						ListView_SetItemText(GetDlgItem(hwd,DLG25_LV1),i2,i1,LPS);
					}
					i++;
				}
				range=MAKELONG((DWORD)1,(DWORD)(i-1));
				maxT=i;
				SendMessage(GetDlgItem(hwd,DLG25_PB1),PBM_SETRANGE,0,(LPARAM)range);
				SendMessage(GetDlgItem(hwd,DLG25_PB1),PBM_SETPOS,(WPARAM)0,0);
				break;
			}

		case WM_COMMAND:
			{
				if(wp==DLG25_B1)
				{
					EnableWindow(GetDlgItem(hwd,DLG25_RB1),false);
					EnableWindow(GetDlgItem(hwd,DLG25_RB2),false);
					EnableWindow(GetDlgItem(hwd,DLG25_RB3),false);
					EnableWindow(GetDlgItem(hwd,DLG25_B1),false);
					if(IsDlgButtonChecked(hwd,DLG25_RB1))
					{
						i=ListView_GetSelectedCount(LV25);
						if(i<=0)
						{
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Nie zaznaczono ¿adnej pozycji");
							DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
							SetFocus(hwd);
							break;
						}
						if(HD_A.count+i>=MAX_ART)
						{
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Baza danych jest ju¿ pe³na. Zaznaczono za du¿o towarów");
							DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
							SetFocus(hwd);
							DestroyWindow(hwd);
							break;
						}
						CreateThread(NULL,0,Dod_tow1,(LPVOID)0,NORMAL_PRIORITY_CLASS,NULL);
					}else
						if(IsDlgButtonChecked(hwd,DLG25_RB2))
						{
							i=ListView_GetItemCount(LV25);
							if(HD_A.count+i>=MAX_ART)
							{
								memset(Err_Text,0,350);
								sprintf(Err_Text,"Baza danych jest ju¿ pe³na. Zaznaczono za du¿o towarów");
								DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
								SetFocus(hwd);
								DestroyWindow(hwd);
								break;
							}
							CreateThread(NULL,0,Dod_tow1,(LPVOID)1,NORMAL_PRIORITY_CLASS,NULL);
						}else DestroyWindow(hwd);
					break;
				}
				if (wp==DLG25_RB1)
				{
					CheckDlgButton(hwd,DLG25_RB1,BST_CHECKED);
					CheckDlgButton(hwd,DLG25_RB2,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG25_RB3,BST_UNCHECKED);
					break;
				}

				if (wp==DLG25_RB2)
				{
					CheckDlgButton(hwd,DLG25_RB1,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG25_RB2,BST_CHECKED);
					CheckDlgButton(hwd,DLG25_RB3,BST_UNCHECKED);
					break;
				}

				if (wp==DLG25_RB3)
				{
					CheckDlgButton(hwd,DLG25_RB1,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG25_RB2,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG25_RB3,BST_CHECKED);
					break;
				}

				break;

			}

		case WM_USER+5:			//aktualizacja progress podczas dodawania towarów do bazy
			{
				SendMessage(GetDlgItem(hwd,DLG25_PB1),PBM_SETPOS,wp,0);
				pr=(float)100/(float)maxT;
				pr=pr*(float)wp;
				if (wp>=(maxT-1)) pr=100;
				memset(zn,0,350);
				sprintf(zn,"%d%%",(int)pr);
				SetWindowText(GetDlgItem(hwd,DLG25_T1),zn);
				break;
			}

			case WM_USER+6:
			{
				SetFocus(hwd);
				SetWindowText(GetDlgItem(hwd,DLG25_T1),"0%");
				SendMessage(GetDlgItem(hwd,DLG25_PB1),PBM_SETPOS,(WPARAM)0,0);
				EnableWindow(GetDlgItem(hwd,DLG25_B1),true);
				EnableWindow(GetDlgItem(hwd,DLG25_RB1),true);
				EnableWindow(GetDlgItem(hwd,DLG25_RB2),true);
				EnableWindow(GetDlgItem(hwd,DLG25_RB3),true);
				memset(Err_Text,0,350);
				sprintf(Err_Text,"Iloœæ zast¹pionych towarów %d ",ile_dod1);
				DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
				SetFocus(hwd);
				DestroyWindow(hwd);
			}

		case WM_CLOSE:
			{
				//DestroyWindow(hwd);
				break;
			}
		case WM_DESTROY:
			{
				EndDialog(hwd,0);
				break;
			}
		default: return DefDlgProc(GetParent(hwd),code,wp,lp);
	}

	return 0;
}



DWORD WINAPI get_vjg(LPVOID p)
{
	int i,c;


	HWND h;
	char txt[350];

	if(gr_t!=NULL)
	{
		delete gr_t;
		gr_t=NULL;
	}
	if(jmt!=NULL)
	{
		delete jmt;
		jmt=NULL;
	}
	if(stv!=NULL)
	{
		delete stv;
		stv=NULL;
	}
	h=(HWND)p;
	c=99;
	gr_t=new GR_T[c];
	memset(gr_t,0,sizeof(GR_T)*c);
	i=get_gr(&KS[Kas_id],gr_t,&c);
	if(i==-2)
	{
		delete gr_t;
		gr_t=new GR_T[c];
		memset(gr_t,0,sizeof(GR_T)*c);
		i=get_gr(&KS[Kas_id],gr_t,&c);
	}
	if(i>0)
	{
		
		is_show=false;
		{
			delete gr_t;
			gr_t=NULL;
		}
		if(jmt!=NULL)
		{
			delete jmt;
			jmt=NULL;
		}
		if(stv!=NULL)
		{
			delete stv;
			stv=NULL;
		}
		SetFocus(h);
		SendMessage(h,WM_USER+2,(WPARAM)i,0);
		return -1;
	}
	c=50;
	jmt=new JM[c];
	memset(jmt,0,sizeof(JM)*c);
	i=get_jm(&KS[Kas_id],jmt,&c);
	if(i==-2)
	{
		delete jmt;
		jmt=new JM[c];
		memset(jm,0,sizeof(JM)*c);
		i=get_jm(&KS[Kas_id],jmt,&c);
	}
	if(i>0) 
	{
		if(gr_t!=NULL)
		{
			delete gr_t;
			gr_t=NULL;
		}
		if(jmt!=NULL)
		{
			delete jmt;
			jmt=NULL;
		}
		if(stv!=NULL)
		{
			delete stv;
			stv=NULL;
		}
		SetFocus(h);
		SendMessage(h,WM_USER+2,(WPARAM)i,0);
		return -1;
	}
	c=50;
	stv=new ST_VAT[c];
	for(i=0;i<c;i++) stv[i].vat=-1;
	i=get_vat(&KS[Kas_id],stv,&c);
	if(i==-2)
	{
		delete stv;
		stv=new ST_VAT[c];
		for(i=0;i<c;i++) stv[i].vat=-1;
		i=get_vat(&KS[Kas_id],stv,&c);
	}
	if(i>0) 
	{
		if(gr_t!=NULL)
		{
			delete gr_t;
			gr_t=NULL;
		}
			if(jmt!=NULL)
		{
			delete jmt;
			jmt=NULL;
			}
		if(stv!=NULL)
		{
			delete stv;
			stv=NULL;
		}
		SetFocus(h);
		SendMessage(h,WM_USER+2,(WPARAM)i,0);
		return -1;
	}
	if(!is_param)
	{
		i=get_tow_kas(&TK,KS[Kas_id],kod_tow);
	}else i=0;
	if(i!=0)SendMessage(h,WM_USER+2,(WPARAM)i,0); else SendMessage(h,WM_USER+1,0,0);
	return 0;
}

LRESULT _stdcall DLG26Proc(HWND hwd, int code, WPARAM wp, LPARAM lp)
{

	fstream pl;
	int timer=100,i;
	char txt[350];
	bool bl;

	switch(code)
	{
		case WM_INITDIALOG:
			{
				ecode=0;
				if(!is_show)bl=SetTimer(hwd,timer,3000,NULL);
				else
				{
					CreateThread(NULL,0,get_vjg,(PVOID)hwd,NORMAL_PRIORITY_CLASS,NULL);
				}
				break;
			}	
		case WM_CLOSE:
			{
				//DestroyWindow(hwd);
				break;
			}
		case WM_USER+1:		//w¹tek zakoñczony powodzeniem
		{
			ecode=0;
			DestroyWindow(hwd);

			break;
		}

		case WM_USER+2:		//w¹tek zakoñczony niepowodzeniem
		{
			if((int)wp<0)
			{
				if((int)wp==-3)
				{
					ecode=-3;
					DestroyWindow(hwd);
					//memset(Err_Text,0,350);
					//sprintf(Err_Text,"Pod podanym numerem nie ma zdefiniowanego towaru w kasie fiskalnej");
				}else
				{
					memset(Err_Text,0,350);
					sprintf(Err_Text,"Nie mo¿na otworzyæ plików konfiguracyjnych kasy fiskalnej");
				}
			}else
			{
				memset(Err_Text,0,350);
				LoadString(hst,wp+1000,txt,350);
				sprintf(Err_Text,"Nie mo¿na wykonaæ operacji\n%s",txt);
			}
			ecode=wp;
			DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
			DestroyWindow(hwd);
			break;
		}
		case WM_TIMER:
			{
				bl=KillTimer(hwd,timer);
				DeleteFile("Config/naz.txt");
				DeleteFile("Config/sprz.txt");
				DeleteFile("Config/sort.txt");
				i=OSprz(KS[Kas_id]);

				if(i!=0)
				{
					if(i<0)
					{
						sprintf(Err_Text,"Nie mo¿na odczytaæ plików konfigurascyjnych kasy fiskalnej");
						DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
						SetFocus(hwd);
					}else
					{
						LoadString(hst,i+1000,txt,350);
						sprintf(Err_Text,"Nie mo¿na wykonaæ operacji\n%s",txt);
						DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
						SetFocus(hwd);
					}
					ecode=i;
					DestroyWindow(hwd);
				}
				SetWindowText(GetDlgItem(hwd,DLG26_T1),"Zapisywanie zmian do bazy danych...");
				i=Mag_act();
				if(i==-1)
				{
					printf(Err_Text,"Nie mo¿na odczytaæ plików konfigurascyjnych kasy fiskalnej");
					DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
					ecode=-1;
					SetFocus(hwd);
				}
				//memset(Err_Text,0,350);
				//sprintf(Err_Text,"Zakoñczono aktualizacjê stanów magazynowych");
				//DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
				DestroyWindow(hwd);
				break;
			}
		case WM_DESTROY:
			{
				EndDialog(hwd,0);
				break;
			}
		default: return DefDlgProc(GetParent(hwd),code,wp,lp);
	}
	
	return 0;
}



LRESULT _stdcall DLG27Proc(HWND hwd, int code, WPARAM wp, LPARAM lp)
{
	bool bl;
	int i;
	char txt[150];
	double vat,cenabr,fl;

	switch(code)
	{
		case WM_INITDIALOG:
			{
				SetWindowText(GetDlgItem(hwd,DLG27_E1),TK.numer);
				SetWindowText(GetDlgItem(hwd,DLG27_E2),TK.nazwa);
				memset(txt,0,150);
				itoa(TK.mpp,txt,10);
				SetWindowText(GetDlgItem(hwd,DLG27_E3),txt);
				if(TK.kod_kr[0]==0)SetWindowText(GetDlgItem(hwd,DLG27_E4),"0000000000000"); else SetWindowText(GetDlgItem(hwd,DLG27_E4),TK.kod_kr);
				dbl_str(TK.cenab,txt,2,150);
				SetWindowText(GetDlgItem(hwd,DLG27_E5),txt);
				bl=false;
				i=0;
				do
				{
					
					{
						memset(txt,0,150);
						if(stv[i].vat==-1)bl=true;
						else if(stv[i].vat!=0)
						{
							sprintf(txt,"%0.2f",stv[i].vat);
							ComboBox_AddString(GetDlgItem(hwd,DLG27_LB2),txt);
						}else if(stv[i].opis[0]!=0)
						{
							ComboBox_AddString(GetDlgItem(hwd,DLG27_LB2),stv[i].opis);
						}else 
						{
							sprintf(txt,"%0.2f",stv[i].vat);
							ComboBox_AddString(GetDlgItem(hwd,DLG27_LB2),txt);
						}
						i++;
					}

				}while(!bl);
				ComboBox_SetCurSel(GetDlgItem(hwd,DLG27_LB2),TK.vat-1);

				bl=false;
				i=0;
				do
				{
					
					if(gr_t[i].nazwa[0]!=0) ComboBox_AddString(GetDlgItem(hwd,DLG27_LB3),gr_t[i].nazwa); else bl=true;
					i++;

				}while(!bl);
				ComboBox_SetCurSel(GetDlgItem(hwd,DLG27_LB3),TK.grupa-1);

				bl=false;
				i=0;
				do
				{
					
					if(jmt[i].znak[0]!=0) ComboBox_AddString(GetDlgItem(hwd,DLG27_LB1),jmt[i].znak); else bl=true;
					i++;

				}while(!bl);
				ComboBox_SetCurSel(GetDlgItem(hwd,DLG27_LB1),TK.jm-1);

				if(TK.is_bl) CheckDlgButton(hwd,DLG27_CB1,true);
				if(TK.is_op) CheckDlgButton(hwd,DLG27_CB2,true);
				if(TK.is_wylzRN) CheckDlgButton(hwd,DLG27_CB3,true);
				if(TK.wpr_cen) CheckDlgButton(hwd,DLG27_CB4,true);
				if(TK.list_podr) CheckDlgButton(hwd,DLG27_CB5,true);
				
				if(is_zapT)
				{
					ShowWindow(GetDlgItem(hwd,DLG27_B2),SW_SHOWNORMAL);
					//EnableWindow(GetDlgItem(hwd,DLG27_E1),true);
					EnableWindow(GetDlgItem(hwd,DLG27_E2),true);
					EnableWindow(GetDlgItem(hwd,DLG27_E3),true);
					EnableWindow(GetDlgItem(hwd,DLG27_E4),true);
					EnableWindow(GetDlgItem(hwd,DLG27_E5),true);
					EnableWindow(GetDlgItem(hwd,DLG27_LB2),true);
					EnableWindow(GetDlgItem(hwd,DLG27_LB3),true);
					EnableWindow(GetDlgItem(hwd,DLG27_LB1),true);
					EnableWindow(GetDlgItem(hwd,DLG27_CB1),true);
					EnableWindow(GetDlgItem(hwd,DLG27_CB2),true);
					EnableWindow(GetDlgItem(hwd,DLG27_CB3),true);
					EnableWindow(GetDlgItem(hwd,DLG27_CB4),true);
					EnableWindow(GetDlgItem(hwd,DLG27_CB5),true);
				}
				SetProp(GetDlgItem(hwd,DLG27_E5),"PROC",(HANDLE)GetWindowLong(GetDlgItem(hwd,DLG27_E5),GWL_WNDPROC));
				SetProp(GetDlgItem(hwd,DLG27_E5),"BOOL",(HANDLE)false);
				SetWindowLong(GetDlgItem(hwd,DLG27_E5),GWL_WNDPROC,(LONG)WndEProc);
				break;
			}	
		case WM_COMMAND:
			{
				if(wp==DLG27_B1)		//przycisk wyjdŸ
				{
					DestroyWindow(hwd);
					break;
				}

				if(wp==DLG27_B2)		//przycisk zapisz
				{
					memset(TK.nazwa,0,150);
					GetWindowText(GetDlgItem(hwd,DLG27_E2),TK.nazwa,150);
					if(TK.nazwa[0]==0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie wype³niono potrzebnych pól");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}

					TK.vat=ComboBox_GetCurSel(GetDlgItem(hwd,DLG27_LB2))+1;
					TK.grupa=ComboBox_GetCurSel(GetDlgItem(hwd,DLG27_LB3))+1;
					memset(txt,0,150);
					GetWindowText(GetDlgItem(hwd,DLG27_E3),txt,150);
					if(txt[0]==0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie wype³niono potrzebnych pól");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					TK.mpp=atoi(txt);

					TK.jm=ComboBox_GetCurSel(GetDlgItem(hwd,DLG27_LB1))+1;

					memset(TK.kod_kr,0,35);
					GetWindowText(GetDlgItem(hwd,DLG27_E4),TK.kod_kr,35);
					if(TK.kod_kr[0]==0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie wype³niono potrzebnych pól");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					if(strlen(TK.kod_kr)!=13)
					{
						memset(Query_Text,0,350);
						sprintf(Query_Text,"Kod kreskowy powinien zawieraæ 13 cyfr\n Czy chcesz kontynuowaæ ?");
						DialogBox(hst,MAKEINTRESOURCE(DLG_Q),hwd,(DLGPROC)&DLGQProc);
						SetFocus(hwd);
						if(!is_ok) break;
					}
					memset(txt,0,150);
					GetWindowText(GetDlgItem(hwd,DLG27_E5),txt,150);
					if(txt[0]==0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie wype³niono potrzebnych pól");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}

					TK.cenab=atof(txt);
					if(IsDlgButtonChecked(hwd,DLG27_CB1)) TK.is_bl=true; else TK.is_bl=false;
					if(IsDlgButtonChecked(hwd,DLG27_CB2)) TK.is_op=true; else TK.is_op=false;
					if(IsDlgButtonChecked(hwd,DLG27_CB3)) TK.is_wylzRN=true; else TK.is_wylzRN=false;
					if(IsDlgButtonChecked(hwd,DLG27_CB4)) TK.wpr_cen=true; else TK.wpr_cen=false;
					if(IsDlgButtonChecked(hwd,DLG27_CB5)) TK.list_podr=true; else TK.list_podr=false;
					memset(Query_Text,0,350);
					sprintf(Query_Text,"Czy napewno chcesz zmieniæ ten towar w kasie fiskalnej ?");
					DialogBox(hst,MAKEINTRESOURCE(DLG_Q),hwd,(DLGPROC)&DLGQProc);
					SetFocus(hwd);
					if(is_ok)
					{
						i=set_tow(KS[Kas_id],&TK);
						if(i==0)
						{
							i=0;
							do
							{
								if(strcmp(ART[i].KOD_TOW,TK.numer)==0)
								{
									memset(ART[i].Nazwa,0,350);
									strcpy(ART[i].Nazwa,TK.nazwa);
									memset(ART[i].KOD_KR,0,35);
									strcpy(ART[i].KOD_KR,TK.kod_kr);
									memset(ART[i].JM,0,25);
									strcpy(ART[i].JM,jmt[TK.jm-1].znak);
									memset(ART[i].Grupa,0,50);
									strcpy(ART[i].Grupa,gr_t[TK.grupa-1].nazwa);
									if(ART[i].Cena_Brutto!=TK.cenab || stv[TK.vat-1].vat!=ART[i].VAT)
									{
										ART[i].Cena_Brutto=TK.cenab;
										ART[i].VAT=vat=stv[TK.vat-1].vat;
										ART[i].Cena_Netto=ART[i].Cena_Brutto/(1+vat/100);
										if(ART[i].Cena_Zakupu!=0) ART[i].Marza=(ART[i].Cena_Netto/ART[i].Cena_Zakupu-1)*100;
									}
									ART[i].is_blok=TK.is_bl;
									ART[i].is_cena=TK.wpr_cen;
									ART[i].is_list=TK.list_podr;
									ART[i].is_op=TK.is_op;
									ART[i].is_wylznr=TK.is_wylzRN;
									Save_AR(&ART[i]);
									i=HD_A.count;
								}

								i++;
							}while(i<HD_A.count);
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Zapisano zmiany w kasie fiskalnej");
							DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
							SetFocus(hwd);
						}
						else if(i<0)
						{
							printf(Err_Text,"Nie mo¿na odczytaæ plików konfigurascyjnych kasy fiskalnej");
							DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
							SetFocus(hwd);
						}
						else
						{
							memset(Err_Text,0,350);
							LoadString(hst,i+1000,txt,350);
							sprintf(Err_Text,"Nie mo¿na wykonaæ operacji\n%s",txt);
							DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
							SetFocus(hwd);
						}
					}
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
				EndDialog(hwd,0);
				break;
			}
		default: return DefDlgProc(GetParent(hwd),code,wp,lp);
	}
	
	return 0;
}

HANDLE m28;
bool is_exit;
HWND H28;
HWND h,h1;
Artykuly *ARTT;
int a_cnt;
int maxTow;

DWORD WINAPI Send_Tow(LPVOID p)
{
	int oper;
	int stan,prev;
	int dziel,resz;
	int i,j,k,l,v,m,g,nt;
	fstream pl;
	char txt[150],con_str[350];
	TOW_K TT;

	if(p==NULL) return -2;
	oper=(int)p;
	stan=0;
	dziel=a_cnt/100;
	resz=a_cnt%100;
	i=InitKonf(KS[Kas_id]);
	if(i<1) return -1;

	if(oper==1)
	{
		
		for(l=0;l<dziel;l++)
		{
			pl.open("Config/pin.in",ios_base::in|ios_base::out|ios_base::trunc);
			if(!pl.is_open()) return -1;
			memset(con_str,0,350);
			sprintf(con_str,"#%s\n#\n#\n",KS[Kas_id].numer);
			pl.write((char*)con_str,strlen(con_str));
			prev=stan;
			for(i=0;i<100;i++)
			{
				if (nazT_max<=0)nazT_max=34;
				memset(txt,32,nazT_max);
				j=strlen(ARTT[stan].Nazwa);
				if(j>34)j=34;
				strncpy(txt,ARTT[stan].Nazwa,j);
				txt[34]=0;
				v=1;
				m=1;
				g=1;
				
				k=-1;
				{
					k++;
					if(stv[k].vat==ARTT[stan].VAT)
					{
						v=k+1;
					}
				}while(stv[k].vat!=-1 && stv[k].vat!=ARTT[stan].VAT);

				k=-1;
				do
				{
					k++;
					if(strcmp(jmt[k].znak,ARTT[stan].JM)==0)
					{
						m=k+1;
					}
				}while(jmt[k].znak[0]!=0 && strcmp(jmt[k].znak,ARTT[stan].JM)!=0);
				k=-1;
				do
				{
					k++;
					if(strcmp(gr_t[k].nazwa,ARTT[stan].Grupa)==0)
					{
						g=k+1;
					}
				}while(gr_t[k].nazwa[0]!=0 && strcmp(gr_t[k].nazwa,ARTT[stan].Grupa)!=0);
				if(ARTT[stan].KOD_KR[0]==0)strcpy(ARTT[stan].KOD_KR,"0000000000000");
				if(ARTT[stan].KOD_TOW[0]==0)
				{
					maxTow++;
					memset(txt,0,150);
					itoa(maxTow,txt,10);
					for(nt=0;nt<HD_A.count;nt++)
					{
						if(ART[nt].indeks==ARTT[stan].indeks)
						{
							strcpy(ART[nt].KOD_TOW,txt);
							break;
						}
					}
					strcpy(ARTT[stan].KOD_TOW,txt);
					Save_AR(&ARTT[stan]);
				}
				memset(con_str,0,350);
				if(HTR==H_f[4]) sprintf(con_str,"$%s\t%s\t%d\t%d\t%d\t%d\t%d\t%s\t%0.0f\t%d\t%d\t%d\t%d\t%d\t%d\n",ARTT[stan].KOD_TOW,txt,v,1,3,m,(int)ARTT[stan].is_blok,ARTT[stan].KOD_KR,ARTT[stan].Cena_Brutto*100,(int)ARTT[stan].is_op,(int)ARTT[stan].is_wylznr,(int)ARTT[stan].is_cena,(int)ARTT[stan].is_list,1,0);
				else if(HTR==H_f[3]) sprintf(con_str,"$%s\n",ARTT[stan].KOD_TOW);
				pl.write(con_str,strlen(con_str));
				stan++;
			}
			pl.close();
			if(HTR==H_f[4])(*_ZTowar)("Config/pin.in");
			else if(HTR==H_f[3]) (*_KTowar)("Config/pin.in");
			i=RAP(NULL,0);
			if(i!=0)
			{
				SendMessage(H28,WM_USER+3,(WPARAM)i,0);
				return -1;
			}
			if(HTR==H_f[3])
			{
				for(prev;prev<stan;prev++) Us_AR(ARTT[prev].indeks);
			}
			SendMessage(H28,WM_USER+1,(WPARAM)stan,0);
		}
		pl.open("Config/pin.in",ios_base::in|ios_base::out|ios_base::trunc);
		if(!pl.is_open()) return -1;
		memset(con_str,0,350);
		sprintf(con_str,"#%s\n#\n#\n",KS[Kas_id].numer);
		pl.write((char*)con_str,strlen(con_str));
		prev=stan;
		for(i=0;i<resz;i++)
		{
			if(ARTT[stan].KOD_TOW[0]==0)
			{
				maxTow++;
				memset(txt,0,150);
				itoa(maxTow,txt,10);
				for(nt=0;nt<HD_A.count;nt++)
				{
					if(ART[nt].indeks==ARTT[stan].indeks)
					{
						strcpy(ART[nt].KOD_TOW,txt);
						break;
					}
				}
				strcpy(ARTT[stan].KOD_TOW,txt);
				Save_AR(&ARTT[stan]);
			}
			if (nazT_max<=0)nazT_max=34;
			memset(txt,32,nazT_max);
			j=strlen(ARTT[stan].Nazwa);
			if(j>34)j=34;
			strncpy(txt,ARTT[stan].Nazwa,j);
			txt[34]=0;
			v=1;
			m=1;
			g=1;
			k=-1;
			do
			{
				k++;
				if(stv[k].vat==ARTT[stan].VAT)
				{
					v=k+1;
				}
			}while(stv[k].vat!=-1 && stv[k].vat!=ARTT[stan].VAT);
			k=-1;
			do
			{
				k++;
				if(strcmp(jmt[k].znak,ARTT[stan].JM)==0)
				{
					m=k+1;
				}
			
			}while(jmt[k].znak[0]!=0 && strcmp(jmt[k].znak,ARTT[stan].JM)!=0);
			k=-1;
			do
			{
				k++;
				if(strcmp(gr_t[k].nazwa,ARTT[stan].Grupa)==0)
				{
					g=k+1;
				}
			}while(gr_t[k].nazwa[0]!=0 && strcmp(gr_t[k].nazwa,ARTT[stan].Grupa)!=0);

			if(ARTT[stan].KOD_KR[0]==0)strcpy(ARTT[stan].KOD_KR,"0000000000000");
			memset(con_str,0,350);
			if(HTR==H_f[4]) sprintf(con_str,"$%s\t%s\t%d\t%d\t%d\t%d\t%d\t%s\t%0.0f\t%d\t%d\t%d\t%d\t%d\t%d\n",ARTT[stan].KOD_TOW,txt,v,1,3,m,(int)ARTT[stan].is_blok,ARTT[stan].KOD_KR,ARTT[stan].Cena_Brutto*100,(int)ARTT[stan].is_op,(int)ARTT[stan].is_wylznr,(int)ARTT[stan].is_cena,(int)ARTT[stan].is_list,1,0);
			else if(HTR==H_f[3]) sprintf(con_str,"$%s\n",ARTT[stan].KOD_TOW);
			pl.write(con_str,strlen(con_str));
			stan++;
		}
		pl.close();
		if(HTR==H_f[4] && resz>0)(*_ZTowar)("Config/pin.in");
		else if(HTR==H_f[3]) (*_KTowar)("Config/pin.in");
		i=RAP(NULL,0);
		if(i!=0)
		{
			SendMessage(H28,WM_USER+3,(WPARAM)i,0);
			return -1;
		}
		if(HTR==H_f[3])
		{
			for(prev;prev<stan;prev++) Us_AR(ARTT[prev].indeks);
		}
		SendMessage(H28,WM_USER+1,(WPARAM)stan,0);
	}
	SendMessage(H28,WM_USER+2,0,0);
	return 0;
}

LRESULT _stdcall DLG28Proc(HWND hwd, int code, WPARAM wp, LPARAM lp)			//okno dialogowe dodawania i usuwania towarów z kay
{
 static int *TID;
 int i,j,i1,min,l1,l2;
 char zn[350];
 DWORD dw;
 WORD w;
 float pr,st;
 bool ok;

	switch(code)
	{
		case WM_INITDIALOG:
			{
				if(HTR==H_f[3]) 
				{
					SetWindowText(hwd,"Usuwanie towarów z kasy fiskalnej");
					SetWindowText(GetDlgItem(hwd,DLG28_T11),"Towary które bêd¹ usuniête z kasy fiskalnej");
					SetWindowText(GetDlgItem(hwd,DLG28_RB1),"Usuñ towary z listy");
					SetWindowText(GetDlgItem(hwd,DLG28_RB2),"Usuñ towary spe³niaj¹ce kryteria");
					SetWindowText(GetDlgItem(hwd,DLG28_GB1),"Kryteria usuwania towarów z kasy fiskalnej");
				}
				H28=hwd;
				TID=NULL;
				h=GetDlgItem(hwd,DLG28_LB1);
				h1=GetDlgItem(hwd,DLG28_LB2);
				TID=new int[HD_A.count+1];
				memset((char*)TID,0,(HD_A.count+1)*sizeof(int));
				for(i=0;i<HD_A.count;i++)
				{
					SendMessage(h,LB_ADDSTRING,(WPARAM)0,(LPARAM)ART[i].Nazwa);
					TID[0]++;
					TID[i+1]=i;
				}
				if(is_del)
				{
					CheckDlgButton(hwd,DLG28_RB2,true);
					SendMessage(hwd,WM_COMMAND,(WPARAM)DLG28_B2,0);
					break;
				}

				CheckDlgButton(hwd,DLG28_RB1,true);
				
				break;
			}	
		case WM_USER+1:			//aktualizacja progressbara
			{
				SendMessage(GetDlgItem(hwd,DLG28_PB1),PBM_SETPOS,wp,0);
				memset(zn,0,350);
				st=(float)wp;
				pr=(st/(float)a_cnt);
				pr=pr*100;
				if(pr>=99)pr=100;
				sprintf(zn,"%0.0f%%",pr);
				SetWindowText(GetDlgItem(hwd,DLG28_T1),zn);
				break;
			}
		case WM_USER+2:
			{
				memset(Err_Text,0,350);
				if(HTR==H_f[3])
				sprintf(Err_Text,"Zakoñczono kasowanie towarów z kasy fiskalnej"); 
				else if(HTR=H_f[4]) sprintf(Err_Text,"Zakoñczono wysy³anie towarów do kasy fiskalnej"); 
				DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
				SetFocus(hwd);
				SendMessage(GetDlgItem(hwd,DLG28_PB1),PBM_SETPOS,0,0);
				SetWindowText(GetDlgItem(hwd,DLG28_T1),"0%");
				break;
			}
		case WM_USER+3:
			{
				memset(Err_Text,0,350);
				if((int)wp>0)
				{
					memset(zn,0,350);
					LoadString(hst,(int)wp+1000,zn,350);
					sprintf(Err_Text,"Nie mo¿na wykonaæ operacji\n%s",zn);
				}else
				{
					sprintf(Err_Text,"Nie mo¿na odczytac plików konfiguracyjnych kasy fiskalnej");
				}
				DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
				SetFocus(hwd);
				break;
			}
		case WM_COMMAND:
			{
				if(wp==DLG28_B1)		//przycisk wyjdŸ
				{
					DestroyWindow(hwd);
					break;
				}

				if(wp==DLG28_B4)		//przycisk dodaj do listy
				{
					i=-1;
					i=ListBox_GetCurSel(h);
					if(i>=0)
					{
						i1=ListBox_GetSelCount(h);
						if(i1>1)
						{
							memset(TID,-1,HD_A.count+1);
							ListBox_GetSelItems(h,HD_A.count,TID);
							for(i=0;i<HD_A.count;i++)
							{
								if(TID[i]!=-1)
								{
									memset(zn,0,350);
									ListBox_GetText(h,TID[i],zn);
									SendMessage(h1,LB_ADDSTRING,(WPARAM)0,(LPARAM)zn);
								}else break;
								
							}
							SetWindowText(GetDlgItem(hwd,DLG28_E6),"");
							SetWindowText(GetDlgItem(hwd,DLG28_E7),"");
							SetWindowText(GetDlgItem(hwd,DLG28_E8),"");
							break;
						}
						memset(zn,0,350);
						ListBox_GetText(h,i,zn);
						for(Tid=0;Tid<HD_A.count;Tid++)
						{
							if(strcmp(ART[Tid].Nazwa,zn)==0) break;
						}
						SendMessage(h1,LB_ADDSTRING,(WPARAM)0,(LPARAM)ART[Tid].Nazwa);
					}

					SetWindowText(GetDlgItem(hwd,DLG28_E6),"");
					SetWindowText(GetDlgItem(hwd,DLG28_E7),"");
					SetWindowText(GetDlgItem(hwd,DLG28_E8),"");
					break;
				}

				if(wp==DLG28_B5)		//przyciks usuñ z listy
				{
					i=-1;
					i=ListBox_GetCurSel(h1);
					if(i>=0)
					{
						ListBox_DeleteString(h1,i);
					}

					break;
				}

				if(wp==DLG28_B2)		//przycisk start
				{
					if(ARTT!=NULL)
					{
						delete ARTT;
						ARTT=NULL;
					}

					if(IsDlgButtonChecked(hwd,DLG28_RB1))
					{
						a_cnt=ListBox_GetCount(h1);
						if(a_cnt<=0)
						{
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Lista towarów do wys³ania jest pusta");
							DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
							SetFocus(hwd);
							break;
						}
						ARTT=new Artykuly[a_cnt];
						for(i=0;i<a_cnt;i++)
						{
							memset(zn,0,350);
							ListBox_GetText(h1,i,zn);
							for(Tid=0;Tid<HD_A.count;Tid++)
							{
								if(strcmp(ART[Tid].Nazwa,zn)==0) break;
							}
							memcpy((char*)(&ARTT[i]),(char*)(&ART[Tid]),sizeof(Artykuly));
						}
						
					}else
					{
						a_cnt=0;
						ARTT=new Artykuly[HD_A.count];
						for(i=0;i<HD_A.count;i++)
						{
							ok=true;
							memset(zn,0,350);
							GetWindowText(GetDlgItem(hwd,DLG28_E1),zn,350);
							if(zn[0]!=0)
							{
								
								if(stricmp(ART[i].Nazwa,zn)==0) ok=false;
								l1=strlen(zn);
								l2=strlen(ART[i].Nazwa);
								if(l1>l2) ok=false;
								ok=false;
								for(j=0;j<=l2-l1;j++)
								{
									if(strnicmp(&ART[i].Nazwa[j],zn,l1)==0)
									{
										ok=true;
										j=l2-l1+1;
									}
								}

							}
							if(ok)
							{
								memset(zn,0,350);
								GetWindowText(GetDlgItem(hwd,DLG28_E2),zn,350);
								if(zn[0]!=0) 
								{
									min=atoi(zn);
									if(ART[i].KOD_TOW[0]!=0)
									{
										if(atoi(ART[i].KOD_TOW)<min) ok=false;
									}else ok=false;
								}
								if(ok)
								{
									memset(zn,0,350);
									GetWindowText(GetDlgItem(hwd,DLG28_E3),zn,350);
									if(zn[0]!=0) 
									{
										min=atoi(zn);
										if(ART[i].KOD_TOW[0]!=0)
										{
											if(atoi(ART[i].KOD_TOW)>min) ok=false;
										}else ok=false;
									}

								}
							}
							if(ok)
							{
								memset(zn,0,350);
								GetWindowText(GetDlgItem(hwd,DLG28_E4),zn,350);
								if(zn[0]!=0) 
								{
									min=atoi(zn);
									if(ART[i].Stan<(float)min) ok=false;
								}
								if(ok)
								{
									memset(zn,0,350);
									GetWindowText(GetDlgItem(hwd,DLG28_E5),zn,350);
									if(zn[0]!=0) 
									{
										min=atoi(zn);
										if(ART[i].Stan>(float)min) ok=false;
									}

								}
							}
							if(ok)
							{
								memcpy((char*)(&ARTT[a_cnt]),(char*)(&ART[i]),sizeof(Artykuly));
								a_cnt++;
							}
						}

					}
					dw=MAKELONG((WORD)1,(WORD)a_cnt);
					SendMessage(GetDlgItem(hwd,DLG28_PB1),PBM_SETRANGE,0,(LPARAM)dw);
					SendMessage(GetDlgItem(hwd,DLG28_PB1),PBM_SETPOS,(WPARAM)0,0);
					is_param=true;
					is_show=true;
					DialogBox(hst,MAKEINTRESOURCE(ID_DLG_26),hwd,(DLGPROC)DLG26Proc);
					if(ecode!=0) break;
					is_param = false;
					SetFocus(hwd);
					i=get_data(KS[Kas_id],&maxTow,_ONrTowar,NULL,0);
					i=1;
					CreateThread(NULL,0,Send_Tow,(LPVOID)i,NORMAL_PRIORITY_CLASS,NULL);
					break;
				}

				if(LOWORD(wp)==DLG28_LB1)
				{
					if(HIWORD(wp)==LBN_DBLCLK)
					{
						SendMessage(hwd,WM_COMMAND,(WPARAM)DLG28_B4,0);
						break;
					}
					if(HIWORD(wp)==LBN_SELCHANGE)
					{
						break;
						i=-1;
						i=ListBox_GetCurSel(h);
						if(i>=0)
						{
							memset(zn,0,350);
							ListBox_GetText(h,i,zn);
							for(Tid=0;Tid<HD_A.count;Tid++)
							{
								if(strcmp(ART[Tid].Nazwa,zn)==0) break;
							}
							//Tid=TID[i+1];
							EnableWindow(GetDlgItem(hwd,DLG28_E6),false);
							EnableWindow(GetDlgItem(hwd,DLG28_E7),false);
							EnableWindow(GetDlgItem(hwd,DLG28_E8),false);
							SetWindowText(GetDlgItem(hwd,DLG28_E8),ART[Tid].KOD_KR);
							SetWindowText(GetDlgItem(hwd,DLG28_E7),ART[Tid].KOD_TOW);
							SetWindowText(GetDlgItem(hwd,DLG28_E6),ART[Tid].Nazwa);
							EnableWindow(GetDlgItem(hwd,DLG28_E6),true);
							EnableWindow(GetDlgItem(hwd,DLG28_E7),true);
							EnableWindow(GetDlgItem(hwd,DLG28_E8),true);
						}
					}
					break;
				}

				if(LOWORD(wp)==DLG28_E6 || LOWORD(wp)==DLG28_E7 || LOWORD(wp)==DLG28_E8)  // WYSZUKIWANIE TOWARU
				{
					if(HIWORD(wp)==EN_CHANGE)
					{
						SendMessage(h,LB_RESETCONTENT,0,0);
						memset((char*)TID,0,(HD_A.count+1)*sizeof(int));
						for(i=0;i<HD_A.count;i++)
						{
							bl=true;
							memset(zn,0,350);
							GetWindowText(GetDlgItem(hwd,DLG28_E6),zn,350);
							if(zn[0]!=0)
							{
								i1=strncmp(ART[i].Nazwa,zn,strlen(zn));
								if(i1!=0)bl=false;
							}
					
							if(bl)
							{
								memset(zn,0,350);
								GetWindowText(GetDlgItem(hwd,DLG28_E7),zn,350);
								if(zn[0]!=0)
								{
									i1=strncmp(ART[i].KOD_TOW,zn,strlen(zn));
									if(i1!=0)bl=false;
								}
							}

							if(bl)
							{
								memset(zn,0,350);
								GetWindowText(GetDlgItem(hwd,DLG28_E8),zn,350);
								if(zn[0]!=0)
								{
									i1=strncmp(ART[i].KOD_KR,zn,strlen(zn));
									if(i1!=0)bl=false;
								}
							}
							if(bl) 
							{
								SendMessage(h,LB_ADDSTRING,(WPARAM)0,(LPARAM)ART[i].Nazwa);
								TID[0]++;
								TID[TID[0]]=i;
							}
						}

					}

				break;
				
			
				}
			}
		case WM_CLOSE:
			{
				break;
			}
		
		case WM_DESTROY:
			{
				if(TID!=NULL)
				{
					delete TID;
					TID=NULL;
				}
				if(ARTT!=NULL)
				{
					delete ARTT;
					ARTT=NULL;
				}
			
				EndDialog(hwd,0);
				break;
			}
		default: return DefDlgProc(GetParent(hwd),code,wp,lp);
	}
	
	return 0;
}




	//okno dialogowe zarz¹dzania grupami towarowymi



LRESULT _stdcall DLG29Proc(HWND hwd, int code, WPARAM wp, LPARAM lp)
{
	int i,max,ac;
	char zn[50],zn1[50];
	GR_T _gr[15];

	switch(code)
	{
		case WM_INITDIALOG:
		{
			SendMessage(GetDlgItem(hwd,DLG29_E1),EM_SETLIMITTEXT,(WPARAM)19,0);
			for (i=0;i<cnt.grcnt;i++)
			{
				SendMessage(GetDlgItem(hwd,DLG29_LB1),LB_ADDSTRING,0,(LPARAM)GR[i].nazwa);
			}
			memset(zn,0,50);
			sprintf(zn,"Domyœlna grupa towarowa: %s",GR[cnt.def_gr].nazwa);
			SetWindowText(GetDlgItem(hwd,DLG29_T1),zn);
			is_zm_wal=false;
			break;
		}

		case WM_COMMAND:
			{
				if(wp==DLG29_B1)				//Przycisk wyjdŸ
				{
					DestroyWindow(hwd);
					break;
				}


				if(wp==DLG29_B4)			//Przycisk ustaw domyœln¹ grupê
				{
					i=SendMessage(GetDlgItem(hwd,DLG29_LB1),LB_GETCURSEL,0,0);
					if(i<0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nale¿y zanzaczyæ pozycjê na liœcie");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					cnt.def_gr=i;
					if(Save_GR()!=1)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie mo¿na zapisaæ danych do bazy. ");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGERRProc);
						SetFocus(hwd);
						break;
					}
					memset(zn,0,50);
					sprintf(zn,"Domyœlna grupa towarowa: %s",GR[cnt.def_gr].nazwa);
					SetWindowText(GetDlgItem(hwd,DLG29_T1),zn);
					is_zm_wal=true;
					break;
				}

				if(wp==DLG29_B3)				//Przycisk usuñ grupê
				{
					if(cnt.grcnt==1)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie mo¿na usun¹c grupy, poniewa¿ przynajmniej jedna grupa musi byæ zdefiniowana");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					i=SendMessage(GetDlgItem(hwd,DLG29_LB1),LB_GETCURSEL,0,0);
					if(i<0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nale¿y zanzaczyæ pozycjê na liœcie");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					ac=i;
					for(i=i;i<cnt.grcnt;i++)
					{
						if(i+1==cnt.grcnt) memset(&GR[i],0,sizeof(GR_T));
						else
						GR[i]=GR[i+1];
					}
					cnt.grcnt--;
					if(ac<cnt.def_gr) 
					{
						cnt.def_gr--;
						is_zm_wal=true;
					}
					else if(cnt.def_gr==cnt.grcnt) 
					{
						cnt.def_gr--;
						is_zm_wal=true;
					}
					i=Save_GR();
					if(i!=1)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie mo¿na zapisaæ danych do bazy. ");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGERRProc);
						SetFocus(hwd);
					} else
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Usuniêto grupê towarow¹ z bazy");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						memset(zn,0,50);
						sprintf(zn,"Domyœlna grupa towarowa: %s",GR[cnt.def_gr].nazwa);
						SetWindowText(GetDlgItem(hwd,DLG29_T1),zn);
						i=SendMessage(GetDlgItem(hwd,DLG29_LB1),LB_RESETCONTENT,0,0);
						for (i=0;i<cnt.grcnt;i++)
						{
							SendMessage(GetDlgItem(hwd,DLG29_LB1),LB_ADDSTRING,0,(LPARAM)GR[i].nazwa);
						}
					}

					break;
				}

				if(wp==DLG29_B2)				//Przycisk Dodaj grupê
				{
					if(cnt.grcnt==99)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Zdefiniowano ju¿ maksymaln¹ iloœæ grup towarowych");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					memset(zn,0,50);
					GetWindowText(GetDlgItem(hwd,DLG29_E1),zn,50);
					if(zn[0]==0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nale¿y podaæ nazwê grupy towarowej");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;

					}

					strcpy(GR[cnt.grcnt].nazwa,zn);
					cnt.grcnt++;
					i=Save_GR();
					if(i!=1)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie mo¿na zapisaæ danych do bazy. ");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGERRProc);
						SetFocus(hwd);
					} else
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Dodano grupê do bazy");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SendMessage(GetDlgItem(hwd,DLG29_LB1),LB_ADDSTRING,0,(LPARAM)GR[cnt.grcnt-1].nazwa);
						SetFocus(hwd);
					}
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
				EndDialog(hwd,0);
				break;
			}
		default: return DefDlgProc(GetParent(hwd),code,wp,lp);
	}
	return 0;
}



		//okno dialogowe zapisywania numeru kasy


LRESULT _stdcall DLG30Proc(HWND hwd, int code, WPARAM wp, LPARAM lp)
{
	char txt[50];
	int i,i1;

	switch(code)
	{
		case WM_INITDIALOG:
		{
			memset(txt,0,50);
			i=get_data(KS[Kas_id],&i1,_ONrKasy,NULL,0);
			if(i==0)
			{
				itoa(i1,txt,10);
				SetWindowText(GetDlgItem(hwd,DLG30_E1),txt);
			}
			else
			{
				memset(Err_Text,0,350);
				sprintf(Err_Text,"Nie mo¿na odczytaæ numeru kasy. ");
				DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGERRProc);
				SetFocus(hwd);
			}

			break;
		}

		case WM_COMMAND:
			{
				if(wp==DLG30_B2)
				{
					DestroyWindow(hwd);
				}
				if(wp==DLG30_B1)
				{
					memset(txt,0,50);
					GetWindowText(GetDlgItem(hwd,DLG30_E1),txt,50);
					if(txt[0]==0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Niepodanu nmeru");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					i=zap_numKas(KS[Kas_id],txt);
					if(i<0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie mo¿na odzczytaæ plików konfiguracyjnych kasy fiskalnej. ");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGERRProc);
						SetFocus(hwd);
					} else
					if(i>0)
					{
						memset(Err_Text,0,350);
						LoadString(hst,i+1000,txt,350);
						sprintf(Err_Text,"Nie mo¿na wykonaæ operacji\n%s",txt);
						DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
						SetFocus(hwd);
					}else
					{
						memset(KS[Kas_id].numer,0,50);
						strcpy(KS[Kas_id].numer,txt);
						Save_KS(true);
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Zapisano numer kasy");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
					}

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
				EndDialog(hwd,0);
				break;
			}
			default: return DefDlgProc(GetParent(hwd),code,wp,lp);
		break;
	}
	return 0;
}




		//okno dialogowe zapisywania/odczytania bitów konfiguracji kasy


LRESULT _stdcall DLG31Proc(HWND hwd, int code, WPARAM wp, LPARAM lp)
{
	char txt[50];
	int i,i1;
	static KAS_CFG kcfg;
	switch(code)
	{
		case WM_INITDIALOG:
		{
			if(!is_zap13) EnableWindow(GetDlgItem(hwd,DLG31_B1),false);
			i=get_bitcfg(&KS[Kas_id],&kcfg);
			if(i<0)
			{
				memset(Err_Text,0,350);
				sprintf(Err_Text,"Nie mo¿na odzczytaæ plików konfiguracyjnych kasy fiskalnej. ");
				DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGERRProc);
				SetFocus(hwd);
			}else
			if(i>0)
			{
				memset(Err_Text,0,350);
				LoadString(hst,i+1000,txt,350);
				sprintf(Err_Text,"Nie mo¿na wykonaæ operacji\n%s",txt);
				DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
				SetFocus(hwd);
			}else
			{
				i1=DLG31_CB1;
				for(i=0;i<2;i++)
				{
					CheckDlgButton(hwd,i1,kcfg.bt[i]);
					i1++;
				}
				//i1++;
				for(i=3;i<5;i++)
				{
					CheckDlgButton(hwd,i1,kcfg.bt[i]);
					i1++;
				}
				//i1++;
				for(i=6;i<9;i++)
				{
					CheckDlgButton(hwd,i1,kcfg.bt[i]);
					i1++;
				}
				for(i=10;i<12;i++)
				{
					CheckDlgButton(hwd,i1,kcfg.bt[i]);
					i1++;
				}
				for(i=13;i<22;i++)
				{
					CheckDlgButton(hwd,i1,kcfg.bt[i]);
					i1++;
				}
			}
						
			break;
		}

		case WM_COMMAND:
			{
				if(wp==DLG31_B2)		//przycisk wyjdŸ
				{
					DestroyWindow(hwd);
				}
				if(wp==DLG31_B1)		//prycisk zapisz
				{
					memset(Query_Text,0,350);
					sprintf(Query_Text,"Czy napewno chcesz zmieniæ knfiguracjê w kasie fiskalnej ?");
					DialogBox(hst,MAKEINTRESOURCE(DLG_Q),hwd,(DLGPROC)&DLGQProc);
					SetFocus(hwd);
					if(is_ok)
					{
						i1=DLG31_CB1;
						for(i=0;i<2;i++)
						{
							kcfg.bt[i]=(BYTE)IsDlgButtonChecked(hwd,i1);
							i1++;
						}
						//i1++;
						for(i=3;i<5;i++)
						{
							kcfg.bt[i]=(BYTE)IsDlgButtonChecked(hwd,i1);
							i1++;
						}
						//i1++;
						for(i=6;i<9;i++)
						{
							kcfg.bt[i]=(BYTE)IsDlgButtonChecked(hwd,i1);
							i1++;
						}
						for(i=10;i<12;i++)
						{
							kcfg.bt[i]=(BYTE)IsDlgButtonChecked(hwd,i1);
							i1++;
						}
						for(i=13;i<22;i++)
						{
							kcfg.bt[i]=(BYTE)IsDlgButtonChecked(hwd,i1);;
							i1++;
						}
						i=set_bitcfg(&KS[Kas_id],&kcfg);
						if(i<0)
						{
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Nie mo¿na odzczytaæ plików konfiguracyjnych kasy fiskalnej. ");
							DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
							SetFocus(hwd);
						}else
						if(i>0)
						{
							memset(Err_Text,0,350);
							LoadString(hst,i+1000,txt,350);
							sprintf(Err_Text,"Nie mo¿na wykonaæ operacji\n%s",txt);
							DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
							SetFocus(hwd);
						}else
						{
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Zapisano bajty konfiguracji kasy fiskalnej");
							DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
							SetFocus(hwd);
						}
					}
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
				EndDialog(hwd,0);
				break;
			}
			default: return DefDlgProc(GetParent(hwd),code,wp,lp);
		break;
	}
	return 0;
}


	// okno dialogowe ustawienia jednostek miary z kas¹ fiskaln¹


LRESULT CALLBACK DLG32Proc(HWND hwd, int code, WPARAM wp, LPARAM lp)
{
	int i,i1,j;
	char txt[350];
	bool bl;

	switch(code)
	{
		case WM_INITDIALOG:
			{ 
				SendMessage(GetDlgItem(hwd,DLG32_E1),EM_SETLIMITTEXT,(WPARAM)4,0);
				if(!is_zap13) EnableWindow(GetDlgItem(hwd,DLG32_B4),false);
				if(jm_t!=NULL) delete jm_t;
				j_cnt=99;
				jm_t=new JM[j_cnt];
				i=get_jm(&KS[Kas_id],jm_t,&j_cnt);
				if(i==-2)
				{
					delete jm_t;
					jm_t=new JM[j_cnt];
					i=get_jm(&KS[Kas_id],jm_t,&j_cnt);
				}else
				if(i>0)
				{
					memset(Err_Text,0,350);
					LoadString(hst,i+1000,txt,350);
					sprintf(Err_Text,"Nie mo¿na wykonaæ operacji\n%s",txt);
					DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
					SetFocus(hwd);
					delete jm_t;
					jm_t=NULL;
					DestroyWindow(hwd);
					break;
				}else
				{
					i=0;
					while(jm_t[i].znak[0]!=0)
					{
						ListBox_AddString(GetDlgItem(hwd,DLG32_LB1),jm_t[i].znak);
						i++;
					}
				}
				break;
			}
		case WM_COMMAND:
			{
				if(wp==DLG32_B1)			//przycisk wyjdŸ
				{
					DestroyWindow(hwd);
				}else
				if(wp==DLG32_B2)			//przycisk dodaj jednostkê do listy
				{
					i=ListBox_GetCount(GetDlgItem(hwd,DLG32_LB1));
					if(i>=16)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Do kasy fiskalnej mo¿na zapisaæ maksymalnie 16 naz jednostek miary");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					memset(txt,0,350);
					GetWindowText(GetDlgItem(hwd,DLG32_E2),txt,50);
					if(txt[0]!=0)i=atoi(txt); else i=-1;
					memset(txt,0,350);
					GetWindowText(GetDlgItem(hwd,DLG32_E1),txt,50);
					if(txt[0]!=0)
					{
						if(i==-1)ListBox_AddString(GetDlgItem(hwd,DLG32_LB1),txt); else ListBox_InsertString(GetDlgItem(hwd,DLG32_LB1),i-1,txt);
					}
					
				}else
				if(wp==DLG32_B3)			//przycisk usuñ jednostkê z listy
				{
					i=ListBox_GetCurSel(GetDlgItem(hwd,DLG32_LB1));
					if(i>=0) ListBox_DeleteString(GetDlgItem(hwd,DLG32_LB1),i);
				}else
				if(wp==DLG32_B4)			//przycisk zapisz
				{
					i1=ListBox_GetCount(GetDlgItem(hwd,DLG32_LB1));
					if(i1>0)
					{
						if(i1>16)
						{
							memset(Query_Text,0,150);
							sprintf(Query_Text,"Do kasy mo¿na zapisaæ maksymalnie 16 nazw jednostek miary.\nCzy chcesz zapisaæ pierwszych 16 jednostek z listy ?");
							DialogBox(hst,MAKEINTRESOURCE(DLG_Q),hwd,(DLGPROC)&DLGQProc);
							SetFocus(hwd);
							if(is_ok) i1=16; else break;
						}
						memset(jm_t,0,j_cnt*sizeof(JM));
						for(i=0;i<i1;i++)
						{
							memset(txt,0,350);
							ListBox_GetText(GetDlgItem(hwd,DLG32_LB1),i,txt);
							strncpy(jm_t[i].znak,txt,25);
						}
						i=set_jm(&KS[Kas_id],jm_t,j_cnt);
						if(i<0)
						{
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Nie mo¿na odzczytaæ plików konfiguracyjnych kasy fiskalnej. ");
							DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
							SetFocus(hwd);
						}else
						if(i>0)
						{
							memset(Err_Text,0,350);
							LoadString(hst,i+1000,txt,350);
							sprintf(Err_Text,"Nie mo¿na wykonaæ operacji\n%s",txt);
							DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
							SetFocus(hwd);
						}else
						{
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Zapisano jednostki miary do kasy fiskalnej");
							DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
							SetFocus(hwd);
						}
						memset(Query_Text,0,150);
						sprintf(Query_Text,"Czy chcesz uaktualniæ jednostki miary w bazie danych ?");
						DialogBox(hst,MAKEINTRESOURCE(DLG_Q),hwd,(DLGPROC)&DLGQProc);
						SetFocus(hwd);
						if(is_ok)
						{
							for(i=0;i<i1;i++)
							{
								bl=false;
								j=0;
								while(1)
								{
									if(strcmp(jm[j].znak,jm_t[i].znak)==0)
									{
										bl=true;
										break;
									}else
										if(j>=cnt.jmcnt) break;
										else j++;
								}
								if(!bl)
								{
									jm[cnt.jmcnt]=jm_t[i];
									cnt.jmcnt++;
								}
							}
							Save_JM();
						}

					}
				}
				break;
			}
		case WM_DESTROY:
			{
				if (jm_t!=NULL)
				{
					delete jm_t;
					jm_t=NULL;
				}
				EndDialog(hwd,0);
				break;
			}
		default: return DefDlgProc(GetParent(hwd),code,wp,lp);
	}
	return 0;
}



	// okno dialogowe ustawienia grup towarowych z kas¹ fiskaln¹


LRESULT CALLBACK DLG33Proc(HWND hwd, int code, WPARAM wp, LPARAM lp)
{
	int i,i1,j;
	char txt[350];
	bool bl;

	switch(code)
	{
		case WM_INITDIALOG:
			{ 
				SendMessage(GetDlgItem(hwd,DLG33_E1),EM_SETLIMITTEXT,(WPARAM)19,0);
				if(!is_zap13) EnableWindow(GetDlgItem(hwd,DLG33_B4),false);
				if(gr_t!=NULL) delete gr_t;
				j_cnt=99;
				gr_t=new GR_T[j_cnt];
				i=get_gr(&KS[Kas_id],gr_t,&j_cnt);
				if(i==-2)
				{
					delete gr_t;
					gr_t=new GR_T[j_cnt];
					i=get_gr(&KS[Kas_id],gr_t,&j_cnt);
				}else
				if(i>0)
				{
					memset(Err_Text,0,350);
					LoadString(hst,i+1000,txt,350);
					sprintf(Err_Text,"Nie mo¿na wykonaæ operacji\n%s",txt);
					DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
					SetFocus(hwd);
					delete gr_t;
					gr_t=NULL;
					DestroyWindow(hwd);
					break;
				}else
				{
					i=0;
					while(gr_t[i].nazwa[0]!=0)
					{
						ListBox_AddString(GetDlgItem(hwd,DLG33_LB1),gr_t[i].nazwa);
						i++;
					}
				}
				break;
			}
		case WM_COMMAND:
			{
				if(wp==DLG33_B1)			//przycisk wyjdŸ
				{
					DestroyWindow(hwd);
				}else
				if(wp==DLG33_B2)			//przycisk dodaj jednostkê do listy
				{
					i=ListBox_GetCount(GetDlgItem(hwd,DLG33_LB1));
					if(i>=16)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Do kasy fiskalnej mo¿na zapisaæ maksymalnie 16 naz grup towarowych");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					memset(txt,0,350);
					GetWindowText(GetDlgItem(hwd,DLG33_E2),txt,50);
					if(txt[0]!=0)i=atoi(txt); else i=-1;
					memset(txt,0,350);
					GetWindowText(GetDlgItem(hwd,DLG33_E1),txt,50);
					if(txt[0]!=0)
					{
						if(i==-1)ListBox_AddString(GetDlgItem(hwd,DLG33_LB1),txt); else ListBox_InsertString(GetDlgItem(hwd,DLG33_LB1),i-1,txt);
					}
					
				}else
				if(wp==DLG33_B3)			//przycisk usuñ grupê z listy
				{
					i=ListBox_GetCurSel(GetDlgItem(hwd,DLG33_LB1));
					if(i>=0) ListBox_DeleteString(GetDlgItem(hwd,DLG33_LB1),i);
				}else
				if(wp==DLG33_B4)			//przycisk zapisz
				{
					i1=ListBox_GetCount(GetDlgItem(hwd,DLG33_LB1));
					if(i1>0)
					{
						if(i1>16)
						{
							memset(Query_Text,0,150);
							sprintf(Query_Text,"Do kasy fiskalnej mo¿na zapisaæ maksymalnie 16 nazw grup towarowych.\n Czy chcesz zapisaæ pierwszych 16 nazw z listy?");
							DialogBox(hst,MAKEINTRESOURCE(DLG_Q),hwd,(DLGPROC)&DLGQProc);
							SetFocus(hwd);
							if(is_ok) i1=16; else break;
						}
						memset(gr_t,0,j_cnt*sizeof(GR_T));
						for(i=0;i<i1;i++)
						{
							memset(txt,0,350);
							ListBox_GetText(GetDlgItem(hwd,DLG33_LB1),i,txt);
							strncpy(gr_t[i].nazwa,txt,25);
						}
						i=set_gr(&KS[Kas_id],gr_t,j_cnt);
						if(i<0)
						{
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Nie mo¿na odzczytaæ plików konfiguracyjnych kasy fiskalnej. ");
							DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
							SetFocus(hwd);
						}else
						if(i>0)
						{
							memset(Err_Text,0,350);
							LoadString(hst,i+1000,txt,350);
							sprintf(Err_Text,"Nie mo¿na wykonaæ operacji\n%s",txt);
							DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
							SetFocus(hwd);
						}else
						{
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Zapisano grupy towarowe do kasy fiskalnej");
							DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
							SetFocus(hwd);
						}
						memset(Query_Text,0,150);
						sprintf(Query_Text,"Czy chcesz uaktualniæ grupy towarowe w bazie danych ?");
						DialogBox(hst,MAKEINTRESOURCE(DLG_Q),hwd,(DLGPROC)&DLGQProc);
						SetFocus(hwd);
						if(is_ok)
						{
							for(i=0;i<i1;i++)
							{
								bl=false;
								j=0;
								while(1)
								{
									if(strcmp(GR[j].nazwa,gr_t[i].nazwa)==0)
									{
										bl=true;
										break;
									}else
										if(j>=cnt.grcnt) break;
										else j++;
								}
								if(!bl)
								{
									GR[cnt.grcnt]=gr_t[i];
									cnt.grcnt++;
								}
							}
							Save_GR();
						}

					}
				}
				break;
			}
		case WM_DESTROY:
			{
				if(gr_t!=NULL)
				{
					delete gr_t;
					gr_t=NULL;
				}
				EndDialog(hwd,0);
				break;
			}
		default: return DefDlgProc(GetParent(hwd),code,wp,lp);
	}
	return 0;
}



	// okno dialogowe ustawienia stawek podatkowych z kas¹ fiskaln¹


LRESULT CALLBACK DLG34Proc(HWND hwd, int code, WPARAM wp, LPARAM lp)
{
	int i,i1,j;
	char txt[350];
	bool bl;

	switch(code)
	{
		case WM_INITDIALOG:
			{ 
				if(stv!=NULL) delete stv;
				j_cnt=99;
				stv=new ST_VAT[j_cnt];
				i=get_vat(&KS[Kas_id],stv,&j_cnt);
				if(i==-2)
				{
					delete stv;
					stv=new ST_VAT[j_cnt];
					i=get_vat(&KS[Kas_id],stv,&j_cnt);
				}else
				if(i>0)
				{
					memset(Err_Text,0,350);
					LoadString(hst,i+1000,txt,350);
					sprintf(Err_Text,"Nie mo¿na wykonaæ operacji\n%s",txt);
					DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
					SetFocus(hwd);
					delete stv;
					stv=NULL;
					DestroyWindow(hwd);
					break;
				}else
				{
					i=0;
					while(stv[i].vat!=-1 && i<j_cnt)
					{
						memset(txt,0,350);
						sprintf(txt,"%0.2f",stv[i].vat);
						ListBox_AddString(GetDlgItem(hwd,DLG34_LB1),txt);
						i++;
					}
				}
				break;
			}
		case WM_COMMAND:
			{
				if(wp==DLG34_B1)			//przycisk wyjdŸ
				{
					DestroyWindow(hwd);
				}else
				if(wp==DLG34_B2)			//przycisk zapisz stawki do bazy
				{
					i1=ListBox_GetCount(GetDlgItem(hwd,DLG34_LB1));
					if(i1>0)
					{
						memset(Query_Text,0,150);
						sprintf(Query_Text,"Czy napewno chcesz uaktualniæ jednostki miary w bazie danych ?");
						DialogBox(hst,MAKEINTRESOURCE(DLG_Q),hwd,(DLGPROC)&DLGQProc);
						SetFocus(hwd);
						if(is_ok)
						{
							for(i=0;i<i1;i++)
							{
								bl=false;
								j=0;
								while(1)
								{
									if(Vat[j].vat==stv[i].vat)
									{
										bl=true;
										break;
									}else
										if(j>=cnt.vatcnt) break;
										else j++;
								}
								if(!bl)
								{
									Vat[cnt.vatcnt].vat=stv[i].vat;
									cnt.vatcnt++;
								}
							}
							Save_Vat();
						}

					}
				}
				break;
			}
		case WM_DESTROY:
			{
				if(stv!=NULL)
				{
					delete stv;
					stv=NULL;
				}
				EndDialog(hwd,0);
				break;
			}
		default: return DefDlgProc(GetParent(hwd),code,wp,lp);
	}
	return 0;
}



	// okno dialogowe ustawienia form zap³aty z kas¹ fiskaln¹


LRESULT CALLBACK DLG35Proc(HWND hwd, int code, WPARAM wp, LPARAM lp)
{
	int i,i1,j;
	char txt[350];
	bool bl;
	static FORM_ZAP *frz;
	switch(code)
	{
		case WM_INITDIALOG:
			{ 
				SendMessage(GetDlgItem(hwd,DLG35_E1),EM_SETLIMITTEXT,(WPARAM)13,0);
				if(!is_zap13) EnableWindow(GetDlgItem(hwd,DLG35_B4),false);
				j_cnt=99;
				frz=new FORM_ZAP[j_cnt];
				i=get_zap(&KS[Kas_id],frz,&j_cnt);
				if(i==-2)
				{
					delete frz;
					frz=new FORM_ZAP[j_cnt];
					i=get_zap(&KS[Kas_id],frz,&j_cnt);
				}else
				if(i>0)
				{
					memset(Err_Text,0,350);
					LoadString(hst,i+1000,txt,350);
					sprintf(Err_Text,"Nie mo¿na wykonaæ operacji\n%s",txt);
					DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
					SetFocus(hwd);
					delete frz;
					frz=NULL;
					DestroyWindow(hwd);
					break;
				}else
				{
					i=0;
					while(frz[i].naz[0]!=0)
					{
						ListBox_AddString(GetDlgItem(hwd,DLG35_LB1),frz[i].naz);
						i++;
					}
				}
				break;
			}
		case WM_COMMAND:
			{
				if(wp==DLG35_B1)			//przycisk wyjdŸ
				{
					DestroyWindow(hwd);
				}else
				if(wp==DLG35_B2)			//przycisk dodaj formê do listy
				{
					i=ListBox_GetCount(GetDlgItem(hwd,DLG35_LB1));
					if(i>=4)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Do kasy fiskalnej mo¿na zapisaæ maksymalnie 4 formy zap³¹ty");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					memset(txt,0,350);
					GetWindowText(GetDlgItem(hwd,DLG35_E2),txt,50);
					if(txt[0]!=0)i=atoi(txt); else i=-1;
					memset(txt,0,350);
					GetWindowText(GetDlgItem(hwd,DLG35_E1),txt,50);
					if(txt[0]!=0)
					{
						if(i==-1)ListBox_AddString(GetDlgItem(hwd,DLG35_LB1),txt); else ListBox_InsertString(GetDlgItem(hwd,DLG35_LB1),i-1,txt);
					}
					
				}else
				if(wp==DLG35_B3)			//przycisk usuñ grupê z listy
				{
					i=ListBox_GetCurSel(GetDlgItem(hwd,DLG35_LB1));
					if(i>=0) ListBox_DeleteString(GetDlgItem(hwd,DLG35_LB1),i);
				}else
				if(wp==DLG35_B4)			//przycisk zapisz
				{
					i1=ListBox_GetCount(GetDlgItem(hwd,DLG35_LB1));
					if(i1>0)
					{
						if(i1>4)
						{
							memset(Query_Text,0,150);
							sprintf(Query_Text,"Do kasy mo¿na zapisaæ maksymalnie 4 formy p³atnoœci.\nCzy chcesz zapisaæ pierwsze 4 p³atnoœci z listy ?");
							DialogBox(hst,MAKEINTRESOURCE(DLG_Q),hwd,(DLGPROC)&DLGQProc);
							SetFocus(hwd);
							if(is_ok) i1=4; else break;
						}
						memset(frz,0,j_cnt*sizeof(FORM_ZAP));
						for(i=0;i<i1;i++)
						{
							memset(txt,0,350);
							ListBox_GetText(GetDlgItem(hwd,DLG35_LB1),i,txt);
							strncpy(frz[i].naz,txt,25);
						}
						i=set_fz(&KS[Kas_id],frz,j_cnt);
						if(i<0)
						{
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Nie mo¿na odzczytaæ plików konfiguracyjnych kasy fiskalnej. ");
							DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
							SetFocus(hwd);
						}else
						if(i>0)
						{
							memset(Err_Text,0,350);
							LoadString(hst,i+1000,txt,350);
							sprintf(Err_Text,"Nie mo¿na wykonaæ operacji\n%s",txt);
							DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
							SetFocus(hwd);
						}else
						{
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Zapisano formy zap³aty do kasy fiskalnej");
							DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
							SetFocus(hwd);
						}
						memset(Query_Text,0,150);
						sprintf(Query_Text,"Czy chcesz uaktualniæ formy zap³aty w bazie danych ?");
						DialogBox(hst,MAKEINTRESOURCE(DLG_Q),hwd,(DLGPROC)&DLGQProc);
						SetFocus(hwd);
						if(is_ok)
						{
							for(i=0;i<i1;i++)
							{
								bl=false;
								j=0;
								while(1)
								{
									if(strcmp(form_zap[j].naz,frz[i].naz)==0)
									{
										bl=true;
										break;
									}else
										if(j>=cnt.fzapcnt) break;
										else j++;
								}
								if(!bl)
								{
									form_zap[cnt.fzapcnt]=frz[i];
									cnt.fzapcnt++;
								}
							}
							Save_FZ();
						}

					}
				}
				break;
			}
		case WM_DESTROY:
			{
				if(frz!=NULL)
				{
					delete frz;
					frz=NULL;
				}
				EndDialog(hwd,0);
				break;
			}
		default: return DefDlgProc(GetParent(hwd),code,wp,lp);
	}
	return 0;
}


		//okno dialogowe zapisania maksymalnego rabatu kasy


LRESULT _stdcall DLG36Proc(HWND hwd, int code, WPARAM wp, LPARAM lp)
{
	char txt[50];
	int i,i1;

	switch(code)
	{
		case WM_INITDIALOG:
		{
			if(is_zap13)
			{
				SetWindowText(GetDlgItem(hwd,DLG36_T1),"Maksymalny narzut (%)");
				SetWindowText(hwd,"Zapisanie maksymalnego narzutu");
			}
			memset(txt,0,50);
			if(is_zap13) i=get_data(KS[Kas_id],&i1,_ONarzut,NULL,0); else
			i=get_data(KS[Kas_id],&i1,_ORabat,NULL,0);
			if(i==0)
			{
				itoa(i1,txt,10);
				SetWindowText(GetDlgItem(hwd,DLG36_E1),txt);
			}
			else
			{
				memset(Err_Text,0,350);
				sprintf(Err_Text,"Nie mo¿na odczytaæ numeru kasy. ");
				DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGERRProc);
				SetFocus(hwd);
			}

			break;
		}

		case WM_COMMAND:
			{
				if(wp==DLG36_B2)
				{
					DestroyWindow(hwd);
				}
				if(wp==DLG36_B1)
				{
					memset(txt,0,50);
					GetWindowText(GetDlgItem(hwd,DLG36_E1),txt,50);
					if(txt[0]==0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Niepodanu nmeru");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					i=atoi(txt);
					if(i<0 || i>99)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nale¿y podac wartoœæ z przedzia³u 1-99");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					if(!is_zap13) i=zap_rab(KS[Kas_id],txt); else
						i=zap_narz(KS[Kas_id],txt);
					if(i<0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie mo¿na odzczytaæ plików konfiguracyjnych kasy fiskalnej. ");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGERRProc);
						SetFocus(hwd);
					} else
					if(i>0)
					{
						memset(Err_Text,0,350);
						LoadString(hst,i+1000,txt,350);
						sprintf(Err_Text,"Nie mo¿na wykonaæ operacji\n%s",txt);
						DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
						SetFocus(hwd);
					}else
					{
						memset(Err_Text,0,350);
						if(is_zap13) sprintf(Err_Text,"Zapisano maksymalny narzut do kasy fiskalnej");else
						sprintf(Err_Text,"Zapisano maksymalny rabat do kasy fiskalnej");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
					}

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
				EndDialog(hwd,0);
				break;
			}
			default: return DefDlgProc(GetParent(hwd),code,wp,lp);
		break;
	}
	return 0;
}



		//okno dialogowe odczytania raportu godzinowego z  kasy


LRESULT _stdcall DLG37Proc(HWND hwd, int code, WPARAM wp, LPARAM lp)
{
	int cnt,i,j;
	static RPG rpg;
	LVCOLUMN lvc;
	LVITEM lvi;
	char txt[350];
	static HWND lv;
	switch(code)
	{
		case WM_INITDIALOG:
		{
			lv=GetDlgItem(hwd,DLG37_LV1);
			ListView_SetExtendedListViewStyle(lv,LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
			lvc.mask=LVCF_TEXT | LVCF_WIDTH;
			lvc.iSubItem=0;
			for(i=0;i<4;i++)
			{
				lvc.pszText=LVD37[i];
				lvc.cx=LV37_W[i];
				i=ListView_InsertColumn(lv,i,&lvc);
			}
			if(!is_zap13) i=rap_godz(&KS[Kas_id],&rpg,0); else 
				i=rap_godz(&KS[Kas_id],&rpg,1);
			if(i<0)
			{
				memset(Err_Text,0,350);
				sprintf(Err_Text,"Nie mo¿na odzczytaæ plików konfiguracyjnych kasy fiskalnej. ");
				DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
				DestroyWindow(hwd);
			} else
			if(i>0)
			{
				memset(Err_Text,0,350);
				LoadString(hst,i+1000,txt,350);
				sprintf(Err_Text,"Nie mo¿na wykonaæ operacji\n%s",txt);
				DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
				DestroyWindow(hwd);
			}
			else
			{
				lvi.mask=LVIF_TEXT;
				lvi.iSubItem=0;
				lvi.cchTextMax=50;
				for(i=0;i<24;i++)
				{
					itoa(rpg.rg[i].godz,txt,10);
					lvi.pszText=(LPSTR)txt;
					lvi.iItem=i;
					cnt=ListView_InsertItem(lv,&lvi);
					for(j=0;j<3;j++)
					{
						memset(txt,0,350);
						if(j==0) itoa(rpg.rg[i].il_par,txt,10); else if(j==1) itoa(rpg.rg[i].il_poz_par,txt,10); else
							if(j==2) sprintf(txt,"%0.2f",rpg.rg[i].wart_sprz);
						ListView_SetItemText(lv,i,j+1,txt);
					}
				}
			}
			break;
		}

		case WM_COMMAND:
			{
				if(wp==DLG37_B1)
				{
					DestroyWindow(hwd);
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
				EndDialog(hwd,0);
				break;
			}
		default: return DefDlgProc(GetParent(hwd),code,wp,lp);
	}
	return 0;
}

KASJER *kasjer=NULL;
int sel;

		//okno dialogowe odczytania raportu godzinowego z  kasy

LRESULT _stdcall DLG38Proc(HWND hwd, int code, WPARAM wp, LPARAM lp)
{
	int i,j;
	static int cnt;
	char txt[350];
	static HWND lb;
	static bool bl;
	switch(code)
	{
		case WM_INITDIALOG:
		{
			SendMessage(GetDlgItem(hwd,DLG38_E1),EM_SETLIMITTEXT,(WPARAM)19,0);
			if(is_zap13) EnableWindow(GetDlgItem(hwd,DLG38_B2),true); else EnableWindow(GetDlgItem(hwd,DLG38_B2),false);
			lb=GetDlgItem(hwd,DLG38_LB1);
			cnt=8;
			kasjer = new KASJER[cnt];
			i=ORodz_Kasj(KS[Kas_id],kasjer,&cnt);
			if(i==-2)
			{
				delete kasjer;
				kasjer = new KASJER[cnt];
				i=ORodz_Kasj(KS[Kas_id],kasjer,&cnt);
			}
			if(i<0)
			{
				memset(Err_Text,0,350);
				sprintf(Err_Text,"Nie mo¿na odzczytaæ plików konfiguracyjnych kasy fiskalnej. ");
				DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
				DestroyWindow(hwd);
				break;
			} else
			if(i>0)
			{
				memset(Err_Text,0,350);
				LoadString(hst,i+1000,txt,350);
				sprintf(Err_Text,"Nie mo¿na wykonaæ operacji\n%s",txt);
				DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
				DestroyWindow(hwd);
				break;
			}
			for(i=0;i<cnt;i++)
			{
				if(kasjer[i].nazwa[0]!=0) 
				{
					ListBox_AddString(lb,kasjer[i].nazwa);
				}
			}
			ListBox_SetCurSel(lb,0);
			SendMessage(hwd,WM_COMMAND,(WPARAM)MAKELONG(DLG38_LB1,LBN_SELCHANGE),0);
			break;
		}

		case WM_COMMAND:
			{
				if(wp==DLG38_B1)				//przycisk wyjdŸ
				{
					DestroyWindow(hwd);
				}else
				if(LOWORD(wp)==DLG38_LB1)
				{
					if(HIWORD(wp)==LBN_SELCHANGE)
					{
						i=ListBox_GetCurSel(lb);
						if(i>=0)
						{
							sel=i;
							if(kasjer[i].d_rap_dob) CheckDlgButton(hwd,DLG38_CB6,true); else CheckDlgButton(hwd,DLG38_CB6,false);
							if(kasjer[i].d_rap_godz) CheckDlgButton(hwd,DLG38_CB5,true); else CheckDlgButton(hwd,DLG38_CB5,false);
							if(kasjer[i].d_rap_kon_zm) CheckDlgButton(hwd,DLG38_CB1,true); else CheckDlgButton(hwd,DLG38_CB1,false);
							if(kasjer[i].d_rap_sprzedaw) CheckDlgButton(hwd,DLG38_CB8,true); else CheckDlgButton(hwd,DLG38_CB8,false);
							if(kasjer[i].d_rap_sprz_wed_gr) CheckDlgButton(hwd,DLG38_CB2,true); else CheckDlgButton(hwd,DLG38_CB2,false);
							if(kasjer[i].d_rap_sum_okr1) CheckDlgButton(hwd,DLG38_CB7,true); else CheckDlgButton(hwd,DLG38_CB7,false);
							if(kasjer[i].d_rap_szcz_sprz) CheckDlgButton(hwd,DLG38_CB3,true); else CheckDlgButton(hwd,DLG38_CB3,false);
							if(kasjer[i].d_rap_zwr_op) CheckDlgButton(hwd,DLG38_CB4,true); else CheckDlgButton(hwd,DLG38_CB4,false);

							if(kasjer[i].z_rap_dob) CheckDlgButton(hwd,DLG38_CB14,true); else CheckDlgButton(hwd,DLG38_CB14,false);
							if(kasjer[i].z_rap_godz) CheckDlgButton(hwd,DLG38_CB13,true); else CheckDlgButton(hwd,DLG38_CB13,false);
							if(kasjer[i].z_rap_kon_zm) CheckDlgButton(hwd,DLG38_CB9,true); else CheckDlgButton(hwd,DLG38_CB9,false);
							if(kasjer[i].z_rap_sprzedaw) CheckDlgButton(hwd,DLG38_CB16,true); else CheckDlgButton(hwd,DLG38_CB16,false);
							if(kasjer[i].z_rap_sprz_wed_gr) CheckDlgButton(hwd,DLG38_CB10,true); else CheckDlgButton(hwd,DLG38_CB10,false);
							if(kasjer[i].z_rap_sum_okr1) CheckDlgButton(hwd,DLG38_CB15,true); else CheckDlgButton(hwd,DLG38_CB15,false);
							if(kasjer[i].z_rap_szcz_sprz) CheckDlgButton(hwd,DLG38_CB11,true); else CheckDlgButton(hwd,DLG38_CB11,false);
							if(kasjer[i].z_rap_zwr_op) CheckDlgButton(hwd,DLG38_CB12,true); else CheckDlgButton(hwd,DLG38_CB12,false);
							bl=true;
							SetWindowText(GetDlgItem(hwd,DLG38_E1),kasjer[sel].nazwa);
							memset(txt,0,350);
							itoa(kasjer[sel].max_rab,txt,10);
							SetWindowText(GetDlgItem(hwd,DLG38_E2),txt);
							memset(txt,0,350);
							itoa(kasjer[sel].max_narz,txt,10);
							SetWindowText(GetDlgItem(hwd,DLG38_E3),txt);
							bl=false;
						}
					}
					
				}else
				if(LOWORD(wp)>=DLG38_CB1 && LOWORD(wp)<=DLG38_CB16)
				{
					sel=ListBox_GetCurSel(lb);
					if(sel<0) break;
					kasjer[sel].d_rap_dob = (bool)IsDlgButtonChecked(hwd,DLG38_CB6);
					kasjer[sel].d_rap_godz=(bool)IsDlgButtonChecked(hwd,DLG38_CB5);
					kasjer[sel].d_rap_kon_zm = (bool)IsDlgButtonChecked(hwd,DLG38_CB1);
					kasjer[sel].d_rap_sprzedaw = (bool)IsDlgButtonChecked(hwd,DLG38_CB8); 
					kasjer[sel].d_rap_sprz_wed_gr = (bool)IsDlgButtonChecked(hwd,DLG38_CB2); 
					kasjer[sel].d_rap_sum_okr1 = (bool) IsDlgButtonChecked(hwd,DLG38_CB7);
					kasjer[sel].d_rap_szcz_sprz = (bool) IsDlgButtonChecked(hwd,DLG38_CB3); 
					kasjer[sel].d_rap_zwr_op = (bool) IsDlgButtonChecked(hwd,DLG38_CB4); 

					kasjer[sel].z_rap_dob = (bool) IsDlgButtonChecked(hwd,DLG38_CB14); 
					kasjer[sel].z_rap_godz = (bool) IsDlgButtonChecked(hwd,DLG38_CB13); 
					kasjer[sel].z_rap_kon_zm = (bool) IsDlgButtonChecked(hwd,DLG38_CB9); 
					kasjer[sel].z_rap_sprzedaw = (bool) IsDlgButtonChecked(hwd,DLG38_CB16); 
					kasjer[sel].z_rap_sprz_wed_gr = (bool) IsDlgButtonChecked(hwd,DLG38_CB10); 
					kasjer[sel].z_rap_sum_okr1 = (bool) IsDlgButtonChecked(hwd,DLG38_CB15);
					kasjer[sel].z_rap_szcz_sprz = (bool) IsDlgButtonChecked(hwd,DLG38_CB11);
					kasjer[sel].z_rap_zwr_op = (bool) IsDlgButtonChecked(hwd,DLG38_CB12);
				}else
				if(wp==DLG38_B3)		//przycisk konfiguracja uprawnieñ
				{
					sel=ListBox_GetCurSel(lb);
					if(sel>=0)
					{
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_39),hwd,(DLGPROC)&DLG39Proc);
						SetFocus(hwd);
					}
				}else
				if(wp==DLG38_B2)
				{
					i=ZRodz_Kasj(KS[Kas_id],kasjer,&cnt);
					if(i<0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie mo¿na odzczytaæ plików konfiguracyjnych kasy fiskalnej. ");
						DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
					} else
					if(i>0)
					{
						memset(Err_Text,0,350);
						LoadString(hst,i+1000,txt,350);
						sprintf(Err_Text,"Nie mo¿na wykonaæ operacji\n%s",txt);
						DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
					}else
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Zapisano dane do kasy fiskalnej");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
					}
					SetFocus(hwd);
				}else
				if(LOWORD(wp)==DLG38_E1 || LOWORD(wp)==DLG38_E2 || LOWORD(wp)==DLG38_E3)
				{
					if(bl) break;
					if(HIWORD(wp)==EN_CHANGE)
					{
						memset(txt,0,350);
						GetWindowText(GetDlgItem(hwd,DLG38_E1),txt,19);
						memset(kasjer[sel].nazwa,32,19);
						strncpy(kasjer[sel].nazwa,txt,strlen(txt));
						ListBox_DeleteString(lb,sel);
						ListBox_InsertString(lb,sel,txt);
						memset(txt,0,350);
						GetWindowText(GetDlgItem(hwd,DLG38_E2),txt,350);
						kasjer[sel].max_rab=atoi(txt);
						memset(txt,0,350);
						GetWindowText(GetDlgItem(hwd,DLG38_E3),txt,350);
						kasjer[sel].max_narz=atoi(txt);
					}
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
				if(kasjer!=NULL)
				{
					delete kasjer;
					kasjer=NULL;
				}
				EndDialog(hwd,0);
				break;
			}
		default: return DefDlgProc(GetParent(hwd),code,wp,lp);
	}
	return 0;
}
			//okno dialogowe konfiguracji rodzajów kasjerów

LRESULT _stdcall DLG39Proc(HWND hwd, int code, WPARAM wp, LPARAM lp)
{
	int i;

	switch(code)
	{
	
		case WM_INITDIALOG:
		{
			EnableWindow(GetDlgItem(hwd,DLG39_B2),is_zap13);
			for(i=0;i<56;i++)
			CheckDlgButton(hwd,DLG39_CB1+i,(bool)kasjer[sel].upr[i]);
			break;
		}

		case WM_COMMAND:
			{
				if(wp==DLG39_B1)				//przycisk wyjdŸ
				{
					DestroyWindow(hwd);
				}else
				if(wp==DLG39_B2)				//przycisk zapisaz zmiany
				{

					for(i=0;i<56;i++)
					{
						if(IsDlgButtonChecked(hwd,DLG39_CB1+i))kasjer[sel].upr[i]=1; else kasjer[sel].upr[i]=0;
					}
					memset(Err_Text,0,350);
					sprintf(Err_Text,"Zapisano zmiany");
					DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
					DestroyWindow(hwd);
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
				EndDialog(hwd,0);
				break;
			}
		default: return DefDlgProc(GetParent(hwd),code,wp,lp);
	}
	return 0;
}


		//okno dialogowe konfiguracji danych o kasjerach

D_KASJER *DK,*DK_T;
int _cnt,_cnt1;
bool is_d_kasjer;

LRESULT _stdcall DLG40Proc(HWND hwd, int code, WPARAM wp, LPARAM lp)
{
	static HWND lb;
	char txt[350];
	int i,j,k;
	static int orig_cnt;
	static bool is_noedit;
	switch(code)
	{
		

		case WM_INITDIALOG:
		{
			SendMessage(GetDlgItem(hwd,DLG40_E1),EM_SETLIMITTEXT,(WPARAM)19,0);
			SendMessage(GetDlgItem(hwd,DLG40_E2),EM_SETLIMITTEXT,(WPARAM)13,0);
			if(kasjer!=NULL)
			{
				delete kasjer;
				kasjer=NULL;
			}
			_cnt1=8;
			kasjer = new KASJER[_cnt1];
			i=ORodz_Kasj(KS[Kas_id],kasjer,&_cnt1);
			if(i==-2)
			{
				delete kasjer;
				kasjer = new KASJER[_cnt1];
				i=ORodz_Kasj(KS[Kas_id],kasjer,&_cnt1);
			}
			if(i<0)
			{
				memset(Err_Text,0,350);
				sprintf(Err_Text,"Nie mo¿na odzczytaæ plików konfiguracyjnych kasy fiskalnej. ");
				DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
				DestroyWindow(hwd);
				break;
			} else
			if(i>0)
			{
				memset(Err_Text,0,350);
				LoadString(hst,i+1000,txt,350);
				sprintf(Err_Text,"Nie mo¿na wykonaæ operacji\n%s",txt);
				DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
				DestroyWindow(hwd);
				break;
			}
			if(!is_zap13)
			{
				EnableWindow(GetDlgItem(hwd,DLG40_B2),false);
				EnableWindow(GetDlgItem(hwd,DLG40_B3),false);
				EnableWindow(GetDlgItem(hwd,DLG40_B4),false);
				EnableWindow(GetDlgItem(hwd,DLG40_E3),false);
				EnableWindow(GetDlgItem(hwd,DLG40_E2),false);
				EnableWindow(GetDlgItem(hwd,DLG40_E1),false);
				EnableWindow(GetDlgItem(hwd,DLG40_E4),false);
				EnableWindow(GetDlgItem(hwd,DLG40_CB1),false);
			}
			lb=GetDlgItem(hwd,DLG40_LB1);
			_cnt=1;
			DK = new D_KASJER[_cnt];
			i=ODane_Kasj(KS[Kas_id],DK,&_cnt);
			if(i==-2)
			{
				delete DK;
				DK = new D_KASJER[_cnt];
				i=ODane_Kasj(KS[Kas_id],DK,&_cnt);
			}
			if(i<0)
			{
				memset(Err_Text,0,350);
				sprintf(Err_Text,"Nie mo¿na odzczytaæ plików konfiguracyjnych kasy fiskalnej. ");
				DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
				DestroyWindow(hwd);
				break;
			} else
			if(i>0)
			{
				memset(Err_Text,0,350);
				LoadString(hst,i+1000,txt,350);
				sprintf(Err_Text,"Nie mo¿na wykonaæ operacji\n%s",txt);
				DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
				DestroyWindow(hwd);
				break;
			}
			orig_cnt=_cnt;
			for(i=0;i<_cnt;i++)
			{
				if(DK[i].nazwa[0]!=0) 
				{
					ListBox_AddString(lb,DK[i].nazwa);
				}
			}
			for(i=0;i<_cnt1;i++)
			{
				if(kasjer[i].nazwa[0]!=0) 
				{
					ComboBox_AddString(GetDlgItem(hwd,DLG40_E3),kasjer[i].nazwa);
				}
			}
			ListBox_SetCurSel(lb,0);
			SendMessage(hwd,WM_COMMAND,(WPARAM)MAKELONG(DLG40_LB1,LBN_SELCHANGE),0);
			break;
		}

		case WM_COMMAND:
			{
				if(wp==DLG40_B1)				//przycisk wyjdŸ
				{
					DestroyWindow(hwd);
				}else
				if(wp==DLG40_B2)				//przycisk zapisaz zmiany
				{
					i=ListBox_GetCount(lb);
					if(i<=0)
					{
						memset(Query_Text,0,150);
						sprintf(Query_Text,"Czy napewno chcesz zapisaæ  kasjerów do kasy fiskalnej ?");
						DialogBox(hst,MAKEINTRESOURCE(DLG_Q),hwd,(DLGPROC)&DLGQProc);
						SetFocus(hwd);
						if(!is_ok) break;
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Przynajmniej jeden kasjer musi byæ zdefiniowany");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					i=ZDane_Kasj(KS[Kas_id],DK,&_cnt);
					if(i<0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie mo¿na odzczytaæ plików konfiguracyjnych kasy fiskalnej. ");
						DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
					} else
					if(i>0)
					{
						memset(Err_Text,0,350);
						LoadString(hst,i+1000,txt,350);
						sprintf(Err_Text,"Nie mo¿na wykonaæ operacji\n%s",txt);
						DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
					}else
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Zapisano dane do kasy fiskalnej");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						DestroyWindow(hwd);
						break;
					}
				}else
				
				if(wp==DLG40_B3)			//usuñ kajsera
				{
					if(_cnt==0) break;
					i=i=ListBox_GetCurSel(lb);
					if(i+1<=orig_cnt)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Kasjer zapisany jest w kasie fiskalnej\nW celu usuniêcia kasjera nale¿y wybraæ opcjê KONFIGURACJA KASJERÓW I SPRZEDAWCÓW->KASOWANIE DANYCH O KASJERACH");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					if(i>=0)
					{
						memset(Query_Text,0,150);
						sprintf(Query_Text,"Czy napewno chcesz usun¹æ zaznaczonego kasjera ?");
						DialogBox(hst,MAKEINTRESOURCE(DLG_Q),hwd,(DLGPROC)&DLGQProc);
						SetFocus(hwd);
						if(!is_ok) break;
						if(_cnt==1)
						{
							delete DK;
							DK=NULL;
							_cnt=0;
							is_noedit=true;
							SetWindowText(GetDlgItem(hwd,DLG40_E1),"");
							SetWindowText(GetDlgItem(hwd,DLG40_E2),"");
							ComboBox_SetCurSel(GetDlgItem(hwd,DLG40_E3),0);
							CheckDlgButton(hwd,DLG40_CB1,false);
							is_noedit=false;
						}else
						{
							_cnt--;
							DK_T = new D_KASJER[_cnt];
							k=-1;
							for(j=0;j<=_cnt;j++)
							{
								if(i!=j) 
								{
									k++;
									DK_T[k]=DK[j];
								}
							}
							delete DK;
							DK=DK_T;
						}
						ListBox_DeleteString(lb,i);
						ListBox_SetCurSel(lb,0);
						SendMessage(hwd,WM_COMMAND,(WPARAM)MAKELONG(DLG40_LB1,LBN_SELCHANGE),0);
					}
				}else

				if(wp==DLG40_B4)		//przycisk dodaj kasjera
				{
					is_d_kasjer=false;
					DialogBox(hst,MAKEINTRESOURCE(ID_DLG_41),hwd,(DLGPROC)&DLG41Proc);
					if(is_d_kasjer)
					{
						ListBox_ResetContent(lb);
						for(i=0;i<_cnt;i++)
						{
							if(DK[i].nazwa[0]!=0) 
							{
								ListBox_AddString(lb,DK[i].nazwa);
							}
						}
						ListBox_SetCurSel(lb,_cnt-1);
						SendMessage(hwd,WM_COMMAND,(WPARAM)MAKELONG(DLG40_LB1,LBN_SELCHANGE),0);
					}
					SetFocus(hwd);
				}else
				if(LOWORD(wp)==DLG40_LB1)
				{
					if(HIWORD(wp)==LBN_SELCHANGE)
					{
						i=ListBox_GetCurSel(lb);
						if(i>=0)
						{
							is_noedit=true;
							SetWindowText(GetDlgItem(hwd,DLG40_E1),DK[i].nazwa);
							SetWindowText(GetDlgItem(hwd,DLG40_E2),DK[i].haslo);
							memset(txt,0,350);
							itoa(DK[i].id,txt,10);
							SetWindowText(GetDlgItem(hwd,DLG40_E4),txt);
							ComboBox_SetCurSel(GetDlgItem(hwd,DLG40_E3),DK[i].numer-1);
							CheckDlgButton(hwd,DLG40_CB1,DK[i].zmiana);
							is_noedit=false;
						}
					}
					break;
				}else
				if(HIWORD(wp)==EN_CHANGE || HIWORD(wp)==CBN_SELCHANGE || LOWORD(wp)==DLG40_CB1)
				{
					if(is_noedit) break;
					i=ListBox_GetCurSel(lb);
					if(i>=0)
					{
						memset(DK[i].nazwa,0,20);
						GetWindowText(GetDlgItem(hwd,DLG40_E1),DK[i].nazwa,20);
						memset(DK[i].haslo,0,5);
						GetWindowText(GetDlgItem(hwd,DLG40_E2),DK[i].haslo,14);
						DK[i].numer=ComboBox_GetCurSel(GetDlgItem(hwd,DLG40_E3))+1;
						DK[i].zmiana=IsDlgButtonChecked(hwd,DLG40_CB1);
						memset(txt,0,350);
						GetWindowText(GetDlgItem(hwd,DLG40_E4),txt,350);
						if(txt[0]!=0) DK[i].id=atoi(txt); else DK[i].id=0;
						ListBox_DeleteString(lb,i);
						ListBox_InsertString(lb,i,DK[i].nazwa);
						is_noedit=true;
						ListBox_SetCurSel(lb,i);
						is_noedit=false;
					}
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
				if(kasjer!=NULL)
				{
					delete kasjer;
					kasjer=NULL;
				}
				if(DK!=NULL)
				{
					delete DK;
					DK=NULL;
				}
				EndDialog(hwd,0);
				break;
			}
		default: return DefDlgProc(GetParent(hwd),code,wp,lp);
	}
	return 0;
}


			//okno dialogowe dodania kasjera

LRESULT _stdcall DLG41Proc(HWND hwd, int code, WPARAM wp, LPARAM lp)
{
	int i;
	char txt[20];
	D_KASJER DKT;
	bool is_e;

	switch(code)
	{
	
		case WM_INITDIALOG:
		{
			SendMessage(GetDlgItem(hwd,DLG41_E1),EM_SETLIMITTEXT,(WPARAM)19,0);
			SendMessage(GetDlgItem(hwd,DLG41_E2),EM_SETLIMITTEXT,(WPARAM)13,0);
			for(i=0;i<_cnt1;i++)
			{
				if(kasjer[i].nazwa[0]!=0)
				ComboBox_AddString(GetDlgItem(hwd,DLG41_E3),kasjer[i].nazwa);
			}
			ComboBox_SetCurSel(GetDlgItem(hwd,DLG41_E3),0);
			break;
		}

		case WM_COMMAND:
			{
				if(wp==DLG41_B1)				//przycisk wyjdŸ
				{
					is_d_kasjer=false;
					DestroyWindow(hwd);
				}else
				if(wp==DLG41_B2)				//przycisk zapisaz zmiany
				{
					memset(&DKT,0,sizeof(D_KASJER));
					memset(txt,0,20);
					GetWindowText(GetDlgItem(hwd,DLG41_E1),txt,20);
					if(txt[0]==0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie podano nazwy kasjera");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					strcpy(DKT.nazwa,txt);
					memset(txt,0,20);
					GetWindowText(GetDlgItem(hwd,DLG41_E4),txt,20);
					if(txt[0]==0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie podano numeru kasjera");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					DKT.id=atoi(txt);
					is_e=false;
					for(i=0;i<_cnt;i++)
					{
						if(DK[i].id==DKT.id)
						{
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Kasjer o takim numerze ju¿ istnieje");
							DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
							SetFocus(hwd);
							is_e=true;
							break;
						}
					}
					if(is_e) break;
					memset(txt,0,20);
					GetWindowText(GetDlgItem(hwd,DLG41_E2),txt,14);
					strcpy(DKT.haslo,txt);
					DKT.zmiana=IsDlgButtonChecked(hwd,DLG41_CB1);
					DKT.numer=ComboBox_GetCurSel(GetDlgItem(hwd,DLG41_E3))+1;
					DK_T=new D_KASJER[_cnt+1];
					if(DK!=NULL) 
					{
						memcpy(DK_T,DK,sizeof(D_KASJER)*_cnt);
						delete DK;
					}
					DK_T[_cnt]=DKT;
					DK=DK_T;
					is_d_kasjer=true;
					_cnt++;
					DestroyWindow(hwd);
				}
				break;
			}

		case WM_CLOSE:
			{
				is_d_kasjer=false;
				DestroyWindow(hwd);
				break;
			}
		case WM_DESTROY:
			{
				EndDialog(hwd,0);
				break;
			}
		default: return DefDlgProc(GetParent(hwd),code,wp,lp);
	}
	return 0;
}



			//okno dialogowe dodania kasjera

LRESULT _stdcall DLG42Proc(HWND hwd, int code, WPARAM wp, LPARAM lp)
{
	int i,j;
	static D_KASJER *DKU=NULL;
	static D_KASJER *DKU_T=NULL;
	D_KASJER * DKU_T1;
	static KASJER *kasj=NULL;
	static HWND lb,lb1;
	static int k_cnt,k_cnt1;
	int rk_cnt;
	char txt[350];
	bool is_add;

	switch(code)
	{
	
		case WM_INITDIALOG:
		{
			k_cnt1=0;
			lb=GetDlgItem(hwd,DLG42_LB1);
			lb1=GetDlgItem(hwd,DLG42_LB2);
			rk_cnt=8;
			kasj = new KASJER[rk_cnt];
			i=ORodz_Kasj(KS[Kas_id],kasj,&rk_cnt);
			if(i==-2)
			{
				delete kasj;
				kasj = new KASJER[rk_cnt];
				i=ORodz_Kasj(KS[Kas_id],kasj,&rk_cnt);
			}
			if(i<0)
			{
				memset(Err_Text,0,350);
				sprintf(Err_Text,"Nie mo¿na odzczytaæ plików konfiguracyjnych kasy fiskalnej. ");
				DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
				DestroyWindow(hwd);
				break;
			} else
			if(i>0)
			{
				memset(Err_Text,0,350);
				LoadString(hst,i+1000,txt,350);
				sprintf(Err_Text,"Nie mo¿na wykonaæ operacji\n%s",txt);
				DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
				DestroyWindow(hwd);
				break;
			}
			k_cnt=1;
			DKU = new D_KASJER[k_cnt];
			i=ODane_Kasj(KS[Kas_id],DKU,&k_cnt);
			if(i==-2)
			{
				delete DKU;
				DKU = new D_KASJER[k_cnt];
				i=ODane_Kasj(KS[Kas_id],DKU,&k_cnt);
			}
			if(i<0)
			{
				memset(Err_Text,0,350);
				sprintf(Err_Text,"Nie mo¿na odzczytaæ plików konfiguracyjnych kasy fiskalnej. ");
				DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
				DestroyWindow(hwd);
				break;
			} else
			if(i>0)
			{
				memset(Err_Text,0,350);
				LoadString(hst,i+1000,txt,350);
				sprintf(Err_Text,"Nie mo¿na wykonaæ operacji\n%s",txt);
				DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
				DestroyWindow(hwd);
				break;
			}
			DKU_T=new D_KASJER[k_cnt];
			for(i=0;i<k_cnt;i++)
			{
				if(DKU[i].nazwa[0]!=0) 
				{
					ListBox_AddString(lb,DKU[i].nazwa);
				}
			}
			ListBox_SetCurSel(lb,0);
			SendMessage(hwd,WM_COMMAND,(WPARAM)MAKELONG(DLG42_LB1,LBN_SELCHANGE),0);
			break;
		}

		case WM_COMMAND:
			{
				if(wp==DLG42_B1)				//przycisk wyjdŸ
				{
					DestroyWindow(hwd);
					break;
				}else
				if(wp==DLG42_B2)			//przycisk usuñ wybranych kasjerów z kasy fiskalnej
				{
					if(k_cnt1>0)
					{
						i=UDane_Kasj(KS[Kas_id],DKU_T,&k_cnt1);
						if(i<0)
						{
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Nie mo¿na odzczytaæ plików konfiguracyjnych kasy fiskalnej. ");
							DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
							SetFocus(hwd);
						} else
						if(i>0)
						{
							memset(Err_Text,0,350);
							LoadString(hst,i+1000,txt,350);
							sprintf(Err_Text,"Nie mo¿na wykonaæ operacji\n%s",txt);
							DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
							SetFocus(hwd);
						}else
						{
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Usuniêto wybranych kasjerów z kasy fiskalnej");
							DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
							SetFocus(hwd);
							DestroyWindow(hwd);
							break;
						}
					}
				}else
				if(wp==DLG42_B3)			//przycisk dodaj kasjerów do listy
				{
					i=ListBox_GetCurSel(lb);
					if(i>=0)
					{
						is_add=true;
						for(j=0;j<k_cnt;j++)
						{
							if(DKU_T[j].id==DKU[i].id) 
							{
								is_add=false;
								break;
							}
						}
						if(!is_add) break;
						DKU_T[k_cnt1]=DKU[i];
						ListBox_AddString(lb1,DKU[i].nazwa);
						k_cnt1++;
					}
				}else
				if(wp==DLG42_B4)			//przycisk usuwania kasjerów z listy
				{
					if(k_cnt1<=0) break;
					i=ListBox_GetCurSel(lb1);
					if(i>=0)
					{
						for(j=i;j<k_cnt1-1;j++) 
						{
							DKU_T[j]=DKU_T[j+1];
						}
						memset((char*)(&DKU_T[k_cnt1-1]),0,sizeof(D_KASJER));
						//ListBox_DeleteString(lb1,i);
						ListBox_ResetContent(lb1);
						k_cnt1--;
						for(i=0;i<k_cnt1;i++)
						{
							ListBox_AddString(lb1,DKU_T[i].nazwa);
						}
					}
				}else
				if(LOWORD(wp)==DLG42_LB1)
				{
					if(HIWORD(wp)==LBN_SELCHANGE)
					{
						i=ListBox_GetCurSel(lb);
						if(i>=0)
						{
							SetWindowText(GetDlgItem(hwd,DLG42_E1),DKU[i].nazwa);
							SetWindowText(GetDlgItem(hwd,DLG42_E2),DKU[i].haslo);
							SetWindowText(GetDlgItem(hwd,DLG42_E3),kasj[DKU[i].numer-1].nazwa);
							memset(txt,0,350);
							itoa(DKU[i].id,txt,10);
							SetWindowText(GetDlgItem(hwd,DLG42_E4),txt);
						
							CheckDlgButton(hwd,DLG42_CB1,DKU[i].zmiana);
						}
					}
					
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
				if(kasj!=NULL)
				{
					delete kasj;
					kasj=NULL;
				}
				if(DKU!=NULL)
				{
					delete DKU;
					DKU=NULL;
				}
				if(DKU_T!=NULL)
				{
					delete DKU_T;
					DKU_T=NULL;
				}
				EndDialog(hwd,0);
				break;
			}
		default: return DefDlgProc(GetParent(hwd),code,wp,lp);
	}
	return 0;
}


			//okno dialogowe statystyki sprzeda¿y


LRESULT _stdcall DLG43Proc(HWND hwd, int code, WPARAM wp, LPARAM lp)
{
	LVCOLUMN lvc;
	LVITEM lvi;
	static HWND lv;
	int i,j,k,l,rok_od,rok_do,mies_od,mies_do;
	static int il,il1;
	static Prz_Tow *sprz,*przyj;
	char zn[100];
	static int item;
	double kwota;
	NMLISTVIEW * nml;

	fstream pl,pl1;

	switch(code)
	{
	
		case WM_INITDIALOG:
		{
			item=0;
			sprz=NULL;
			przyj=NULL;
			il1=-1;
			il=-1;
			lv=GetDlgItem(hwd,DLG43_LV1);
			ListView_SetExtendedListViewStyle(lv,LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
			lvc.mask=LVCF_TEXT | LVCF_WIDTH;
			lvc.iSubItem=0;
			for(i=0;i<5;i++)
			{
				lvc.pszText=LVD43[i];
				lvc.cx=LV43_W[i];
				i=ListView_InsertColumn(lv,i,&lvc);
			}
			memset(path1,0,300);
			sprintf(path1,"%sDBS.amb",path);
			pl.open(path1,ios_base::in | ios_base::out | ios_base::binary);
			if(pl.fail())
			{
				memset(Err_Text,0,350);
				sprintf(Err_Text,"Nie mo¿na odzczytaæ plików zawieraj¹cych  statystykê sprzeda¿y ");
				DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
				SetFocus(hwd);
				EnableWindow(GetDlgItem(hwd,DLG43_B1),false);
			}else
			{
				pl.read((char*)&il,sizeof(int));
				if(il>0)
				{
					sprz=new Prz_Tow[il];
					for(i=0;i<il;i++) pl.read((char*)&sprz[i],sizeof(Prz_Tow));
				}
			}
			memset(path1,0,300);
			sprintf(path1,"%sDBT.amb",path);
			pl1.open(path1,ios_base::in | ios_base::out | ios_base::binary);
			if(pl1.fail())
			{
				memset(Err_Text,0,350);
				sprintf(Err_Text,"Nie mo¿na odzczytaæ plików zawieraj¹cych statystykê przyjêtych towarów");
				DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
				SetFocus(hwd);
				EnableWindow(GetDlgItem(hwd,DLG43_B1),false);
			}else
			{
				pl1.read((char*)&il1,sizeof(int));
				if(il1>0)
				{
					przyj=new Prz_Tow[il1];
					for(i=0;i<il1;i++) pl1.read((char*)&przyj[i],sizeof(Prz_Tow));
				}
			}
			lvi.mask=LVIF_TEXT;
			for(i=0;i<il;i++)
			{
				memset(zn,0,100);
				itoa(sprz[i].rok,zn,10);
				lvi.pszText=zn;
				lvi.cchTextMax=100;
				lvi.iSubItem=0;
				lvi.iItem=item;
				item=ListView_InsertItem(lv,&lvi);
				item++;
				for(j=0;j<2;j++)
				{
					memset(zn,0,100);
					if(j==0) itoa(sprz[i].miesiac,zn,10);
					else dbl_str(sprz[i].cena_n,zn,2,100);
					ListView_SetItemText(lv,item-1,j+1,zn);
				}
				k=-1;
				for(j=0;j<il1;j++)
				{
					if(sprz[i].rok==przyj[j].rok && sprz[i].miesiac==przyj[j].miesiac)
					{
						k=j;
						break;
					}
				}
				if(k!=-1)
				{
					for(j=2;j<4;j++)
					{
						memset(zn,0,100);
						if(j==2)dbl_str(przyj[k].cena_n,zn,2,100);
						else dbl_str(sprz[i].cena_n-przyj[k].cena_n,zn,2,100);
						ListView_SetItemText(lv,item-1,j+1,zn);
					}
				}else
				{
					for(j=2;j<4;j++)
					{
						memset(zn,0,100);
						if(j==2)sprintf(zn,"0");
						else dbl_str(sprz[i].cena_n,zn,2,10);
						ListView_SetItemText(lv,item-1,j+1,zn);
					}
				}
			}

			for(i=0;i<il1;i++)
			{
				k=i;
				for(j=0;j<il;j++)
				{
					if(sprz[j].rok==przyj[i].rok && sprz[j].miesiac==przyj[i].miesiac)
					{
						k=-1;
						break;
					}
				}
				if(k!=-1)
				{
					memset(zn,0,100);
					itoa(przyj[i].rok,zn,10);
					lvi.pszText=zn;
					lvi.cchTextMax=100;
					lvi.iSubItem=0;
					lvi.iItem=item;
					item=ListView_InsertItem(lv,&lvi);
					item++;
					for(j=0;j<4;j++)
					{
						memset(zn,0,100);
						if(j==0) itoa(przyj[i].miesiac,zn,10);
						else if(j==1) sprintf(zn,"0");
						else if(j==2) dbl_str(przyj[i].cena_n,zn,2,100);
						else if(j==3) dbl_str(przyj[i].cena_n-(2*przyj[i].cena_n),zn,2,100);
						ListView_SetItemText(lv,item-1,j+1,zn);
					}
				}
			}
			if(ListView_GetItemCount(lv)>0)
			{
				ListView_SetSelectionMark(lv,0);
				kwota=0;
				j=-1;
				if(sprz!=NULL)
				{
					do
					{
						j++;
						k=20;
						if(sprz[0].rodz_v[j].rodz!=0)
						{
							memset(zn,0,100);
							sprintf(zn,"%0.2f%%",sprz[0].rodz_v[j].rodz);
							if(sprz[0].rodz_v[j].rodz<10) k++;
							for(i=strlen(zn);i<k;i++)zn[i]=' ';
							sprintf(&zn[k],"%0.2f",sprz[0].rodz_v[j].wart,0);
							ListBox_AddString(GetDlgItem(hwd,DLG43_LB1),zn);
							kwota+=sprz[0].rodz_v[j].wart;
						}
					}while(sprz[0].rodz_v[j].rodz!=0);
				
					memset(zn,0,100);
					sprintf(zn,"Razem:              %0.2f",kwota);
					ListBox_AddString(GetDlgItem(hwd,DLG43_LB1),zn);
					kwota+=sprz[0].cena_n;
					memset(zn,0,100);
					sprintf(zn,"%0.2f",kwota);
					SetWindowText(GetDlgItem(hwd,DLG43_E5),zn);
				}
				j=-1;
				kwota=0;
				if(przyj!=NULL)
				{
					do
					{
						j++;
						k=20;
						if(przyj[0].rodz_v[j].rodz!=0)
						{
							memset(zn,0,100);
							sprintf(zn,"%0.2f%%",przyj[0].rodz_v[j].rodz);
							if(przyj[0].rodz_v[j].rodz<10) k++;
							for(i=strlen(zn);i<k;i++)zn[i]=' ';
							sprintf(&zn[strlen(zn)],"%0.2f",przyj[0].rodz_v[j].wart);
							ListBox_AddString(GetDlgItem(hwd,DLG43_LB2),zn);
							kwota+=przyj[0].rodz_v[j].wart;
						}
					}while(przyj[0].rodz_v[j].rodz!=0);
				
					memset(zn,0,100);
					sprintf(zn,"Razem:              %0.2f",kwota);
					ListBox_AddString(GetDlgItem(hwd,DLG43_LB2),zn);
					kwota+=przyj[0].cena_n;
					memset(zn,0,100);
					sprintf(zn,"%0.2f",kwota);
					SetWindowText(GetDlgItem(hwd,DLG43_E6),zn);
				}
			}
			break;
		}
		
		case WM_NOTIFY:
			{
				if(wp==DLG43_LV1)
				{
					nml=(NMLISTVIEW*)lp;
					if(nml->hdr.code==LVN_ITEMCHANGED)
					{
						ListBox_ResetContent(GetDlgItem(hwd,DLG43_LB1));
						ListBox_ResetContent(GetDlgItem(hwd,DLG43_LB2));
						SetWindowText(GetDlgItem(hwd,DLG43_E5),"");
						SetWindowText(GetDlgItem(hwd,DLG43_E6),"");
						if(nml->uNewState==3)
						{
							if(ListView_GetItemCount(lv)>0)
							{
								
								memset(zn,0,100);
								ListView_GetItemText(lv,nml->iItem,0,zn,50);
								i=atoi(zn);
								ListView_GetItemText(lv,nml->iItem,1,zn,50);
								j=atoi(zn);
								k=-1;
								for(l=0;l<il;l++)
								{
									if(sprz[l].rok==i && sprz[l].miesiac==j)
									{
										k=l;
										break;
									}
								}
								if(k!=-1)
								{
									kwota=0;
									j=-1;
									do
									{
										j++;
										l=20;
										if(sprz[k].rodz_v[j].rodz!=0)
										{
											memset(zn,0,100);
											sprintf(zn,"%0.2f%%",sprz[0].rodz_v[j].rodz);
											if(sprz[k].rodz_v[j].rodz<10) l++;
											for(i=strlen(zn);i<l;i++)zn[i]=32;
											sprintf(&zn[strlen(zn)],"%0.2f",sprz[k].rodz_v[j].wart);
											ListBox_AddString(GetDlgItem(hwd,DLG43_LB1),zn);
											kwota+=sprz[k].rodz_v[j].wart;
										}
										
									}while(sprz[k].rodz_v[j].rodz!=0);
									memset(zn,0,100);
									sprintf(zn,"Razem:              %0.2f",kwota);
									ListBox_AddString(GetDlgItem(hwd,DLG43_LB1),zn);
									kwota+=sprz[k].cena_n;
									memset(zn,0,100);
									sprintf(zn,"%0.2f",kwota);
									SetWindowText(GetDlgItem(hwd,DLG43_E5),zn);
								}
								memset(zn,0,100);
								ListView_GetItemText(lv,nml->iItem,0,zn,50);
								i=atoi(zn);
								ListView_GetItemText(lv,nml->iItem,1,zn,50);
								j=atoi(zn);
								k=-1;
								for(l=0;l<il1;l++)
								{
									if(przyj[l].rok==i && przyj[l].miesiac==j)
									{
										k=l;
										break;
									}
								}
								if(k!=-1)
								{
									j=-1;
									kwota=0;
									do
									{
										j++;
										l=20;
									if(przyj[k].rodz_v[j].rodz>0)
										{
											memset(zn,0,100);
											sprintf(zn,"%0.2f%%",przyj[0].rodz_v[j].rodz);
											if(przyj[k].rodz_v[j].rodz<10) l++;
											for(i=strlen(zn);i<l;i++)zn[i]=' ';
											sprintf(&zn[strlen(zn)],"%0.2f",przyj[k].rodz_v[j].wart);
											ListBox_AddString(GetDlgItem(hwd,DLG43_LB2),zn);
											kwota+=przyj[k].rodz_v[j].wart;
									
										}
									
									}while(przyj[k].rodz_v[j].rodz!=0);
									memset(zn,0,100);
									sprintf(zn,"Razem:              %0.2f",kwota);
									ListBox_AddString(GetDlgItem(hwd,DLG43_LB2),zn);
									kwota+=przyj[k].cena_n;
									memset(zn,0,100);
									sprintf(zn,"%0.2f",kwota);
									SetWindowText(GetDlgItem(hwd,DLG43_E6),zn);
								}
							}

						}
					}
					break;
				}
				break;
			}

		case WM_COMMAND:
			{

				if(wp==DLG43_B2)
				{
					DestroyWindow(hwd);
				}else
				if(wp==DLG43_B1)
				{
					SetWindowText(GetDlgItem(hwd,DLG43_E5),"");
					SetWindowText(GetDlgItem(hwd,DLG43_E6),"");
					ListView_DeleteAllItems(lv);
					rok_od=rok_do=mies_od=mies_do=0;
					memset(zn,0,100);
					GetWindowText(GetDlgItem(hwd,DLG43_E1),zn,100);
					if(zn[0]!=0) mies_od=atoi(zn);
					memset(zn,0,100);
					GetWindowText(GetDlgItem(hwd,DLG43_E2),zn,100);
					if(zn[0]!=0) rok_od=atoi(zn);
					memset(zn,0,100);
					GetWindowText(GetDlgItem(hwd,DLG43_E3),zn,100);
					if(zn[0]!=0) mies_do=atoi(zn);
					memset(zn,0,100);
					GetWindowText(GetDlgItem(hwd,DLG43_E4),zn,100);
					if(zn[0]!=0) rok_do=atoi(zn);

					lvi.mask=LVIF_TEXT;
					item=0;
					for(i=0;i<il;i++)
					{
						if(rok_od!=0 && sprz[i].rok<rok_od) continue;
						if(mies_od!=0 && sprz[i].miesiac<mies_od && rok_od==sprz[i].rok)continue;
						if(rok_do!=0 && sprz[i].rok>rok_do) continue;
						if(mies_do!=0 && sprz[i].miesiac>mies_do && rok_do==sprz[i].rok) continue;
						memset(zn,0,100);
						itoa(sprz[i].rok,zn,10);
						lvi.pszText=zn;
						lvi.cchTextMax=100;
						lvi.iSubItem=0;
						lvi.iItem=item;
						item=ListView_InsertItem(lv,&lvi);
						item++;
						for(j=0;j<2;j++)
						{
							memset(zn,0,100);
							if(j==0) itoa(sprz[i].miesiac,zn,10);
							else dbl_str(sprz[i].cena_n,zn,2,100);
							ListView_SetItemText(lv,item-1,j+1,zn);
						}
						k=-1;
						for(j=0;j<il1;j++)
						{
							if(sprz[i].rok==przyj[j].rok && sprz[i].miesiac==przyj[j].miesiac)
							{
								k=j;
								break;
							}
						}
						if(k!=-1)
						{
							for(j=2;j<4;j++)
							{
								memset(zn,0,100);
								if(j==2)dbl_str(przyj[k].cena_n,zn,2,100);
								else dbl_str(sprz[i].cena_n-przyj[k].cena_n,zn,2,100);
								ListView_SetItemText(lv,item-1,j+1,zn);
							}
						}else
						{
							for(j=2;j<4;j++)
							{
								memset(zn,0,100);
								if(j==2)sprintf(zn,"0");
								else dbl_str(sprz[i].cena_n,zn,2,10);
								ListView_SetItemText(lv,item-1,j+1,zn);
							}
						}
					}

					for(i=0;i<il1;i++)
					{
						k=i;
						for(j=0;j<il;j++)
						{
							if(sprz[j].rok==przyj[i].rok && sprz[j].miesiac==przyj[i].miesiac)
							{
								k=-1;
								break;
							}
						}
						if(k!=-1)
						{
							if(rok_od!=0 && przyj[i].rok<rok_od) continue;
							if(mies_od!=0 && przyj[i].miesiac<mies_od && rok_od==przyj[i].rok)continue;
							if(rok_do!=0 && przyj[i].rok>rok_do) continue;
							if(mies_do!=0 && przyj[i].miesiac>mies_do && rok_do==przyj[i].rok) continue;
							memset(zn,0,100);
							itoa(przyj[i].rok,zn,10);
							lvi.pszText=zn;
							lvi.cchTextMax=100;
							lvi.iSubItem=0;
							lvi.iItem=item;
							item=ListView_InsertItem(lv,&lvi);
							item++;
							for(j=0;j<4;j++)
							{
								memset(zn,0,100);
								if(j==0) itoa(przyj[i].miesiac,zn,10);
								else if(j==1) sprintf(zn,"0");
								else if(j==2) dbl_str(przyj[i].cena_n,zn,2,100);
								else if(j==3) dbl_str(przyj[i].cena_n-(2*przyj[i].cena_n),zn,2,100);
								ListView_SetItemText(lv,item-1,j+1,zn);
							}
						}
					}
					ListBox_ResetContent(GetDlgItem(hwd,DLG43_LB1));
					ListBox_ResetContent(GetDlgItem(hwd,DLG43_LB2));
					if(ListView_GetItemCount(lv)>0)
					{
						ListView_SetSelectionMark(lv,0);
						memset(zn,0,100);
						ListView_GetItemText(lv,0,0,zn,50);
						i=atoi(zn);
						ListView_GetItemText(lv,0,1,zn,50);
						j=atoi(zn);
						
						k=-1;
						for(l=0;l<il;l++)
						{
							if(sprz[l].rok==i && sprz[l].miesiac==j)
							{
								k=l;
								break;
							}
						}
						if(k!=-1)
						{
							kwota=0;
							j=-1;
							do
							{
								j++;
								l=20;		
								if(sprz[k].rodz_v[j].rodz!=0)
								{
									memset(zn,0,100);
									sprintf(zn,"%0.2f%%",sprz[k].rodz_v[j].rodz);
									if(sprz[k].rodz_v[j].rodz<10) l++;
									for(i=strlen(zn);i<l;i++)zn[i]=32;
									sprintf(&zn[strlen(zn)],"%0.2f",sprz[k].rodz_v[j].wart);
									ListBox_AddString(GetDlgItem(hwd,DLG43_LB1),zn);
									kwota+=sprz[k].rodz_v[j].wart;
								}
										
							}while(sprz[k].rodz_v[j].rodz!=0);
							memset(zn,0,100);
							sprintf(zn,"Razem:              %0.2f",kwota);
							ListBox_AddString(GetDlgItem(hwd,DLG43_LB1),zn);
							kwota+=sprz[k].cena_n;
							memset(zn,0,100);
							sprintf(zn,"%0.2f",kwota);
							SetWindowText(GetDlgItem(hwd,DLG43_E5),zn);
						}
						memset(zn,0,100);
						ListView_GetItemText(lv,0,0,zn,50);
						i=atoi(zn);
						ListView_GetItemText(lv,0,1,zn,50);
						j=atoi(zn);
						k=-1;
						for(l=0;l<il1;l++)
						{
							if(przyj[l].rok==i && przyj[l].miesiac==j)
							{
								k=l;
								break;
							}
						}
						if(k!=-1)
						{
							j=-1;
							kwota=0;
							do
							{
								j++;
								l=20;	
								if(przyj[k].rodz_v[j].rodz>0)
								{
									memset(zn,0,100);
									sprintf(zn,"%0.2f%%",przyj[k].rodz_v[j].rodz);
									if(przyj[k].rodz_v[j].rodz<10) l++;
									for(i=strlen(zn);i<l;i++)zn[i]=32;
									sprintf(&zn[strlen(zn)],"%0.2f",przyj[k].rodz_v[j].wart);
									ListBox_AddString(GetDlgItem(hwd,DLG43_LB2),zn);
									kwota+=przyj[k].rodz_v[j].wart;
									
								}
									
							}while(przyj[k].rodz_v[j].rodz!=0);
							memset(zn,0,100);
							sprintf(zn,"Razem:              %0.2f",kwota);
							ListBox_AddString(GetDlgItem(hwd,DLG43_LB2),zn);
							kwota+=przyj[k].cena_n;
							memset(zn,0,100);
							sprintf(zn,"%0.2f",kwota);
							SetWindowText(GetDlgItem(hwd,DLG43_E6),zn);
						}
					}
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
				if(pl) pl.close();
				if(pl1) pl1.close();
				if(sprz!=NULL)
				{
					delete sprz;
					sprz=NULL;
				}
				if(przyj!=NULL)
				{
					delete przyj;
					przyj=NULL;
				}
				EndDialog(hwd,0);
				break;
			}
		default: return DefDlgProc(GetParent(hwd),code,wp,lp);
	}
	return 0;
}


LRESULT _stdcall DLG44Proc(HWND hwd, int code, WPARAM wp ,LPARAM lp)
{
	bool bl;
	int i;
	DWORD pcn,pcr,sbuf;
	static DWORD buf;
	static char *zn;
	int licz;
	HANDLE hnd;
	DWORD ptype,result;
	static BYTE *bt;
	DWORD size,nsize,rsize;
	static PRINTER_INFO_2 * pr_info;
	HDC dc;

	switch(code)
	{
		case WM_INITDIALOG:
			{
				
				CheckDlgButton(hwd,DLG44_RB1,BST_CHECKED);
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
				pr_info=(PRINTER_INFO_2*)bt;
				licz=0;
				buf=0;
				do
				{
					if(!IsBadStringPtr(pr_info[licz].pPrinterName,350))
					{
						ComboBox_AddString(GetDlgItem(hwd,DLG44_CB1),pr_info[licz].pPrinterName);
						if(strcmp(pr_info[licz].pPrinterName,zn)==0) sel_item=licz;
						if(strlen(pr_info[licz].pPrinterName)>buf) buf=strlen(pr_info[licz].pPrinterName);
						licz++;
					}
				}while(!IsBadStringPtr(pr_info[licz].pPrinterName,350));
				licz--;
				ComboBox_SetCurSel(GetDlgItem(hwd,DLG44_CB1),sel_item);
				if(pr_info[sel_item].pDevMode->dmFields&DM_DUPLEX)
				{
					EnableWindow(GetDlgItem(hwd,DLG44_RB2),true);
					EnableWindow(GetDlgItem(hwd,DLG44_RB3),true);
				}else
				{
					CheckDlgButton(hwd,DLG44_RB1,BST_CHECKED);
					CheckDlgButton(hwd,DLG44_RB2,BST_UNCHECKED);
					CheckDlgButton(hwd,DLG44_RB3,BST_UNCHECKED);
				}
				
				
			}
		case WM_COMMAND:
			{
				if(LOWORD(wp)==DLG44_CB1)
				{
					if(HIWORD(wp)==CBN_SELENDOK)
					{
						memset(zn,0,buf);
						sel_item=ComboBox_GetCurSel(GetDlgItem(hwd,DLG44_CB1));
						ComboBox_SetCurSel(GetDlgItem(hwd,DLG44_CB1),sel_item);
						ComboBox_GetText(GetDlgItem(hwd,DLG44_CB1),zn,buf);
						if(pr_info[sel_item].pDevMode->dmFields&DM_DUPLEX)
						{
							EnableWindow(GetDlgItem(hwd,DLG44_RB2),true);
							EnableWindow(GetDlgItem(hwd,DLG44_RB3),true);
						}else
						{
							CheckDlgButton(hwd,DLG44_RB1,BST_CHECKED);
							CheckDlgButton(hwd,DLG44_RB2,BST_UNCHECKED);
							CheckDlgButton(hwd,DLG44_RB3,BST_UNCHECKED);
							EnableWindow(GetDlgItem(hwd,DLG44_RB2),false);
							EnableWindow(GetDlgItem(hwd,DLG44_RB3),false);
						}
						
						break;
					}
					if(HIWORD(wp)==CBN_EDITCHANGE)
					{
						SetWindowText(GetDlgItem(hwd,DLG44_CB1),zn);
						break;
					}
				}

				if(wp==DLG44_RB1||wp==DLG44_RB2||wp==DLG44_RB3)
				{
					if(wp==DLG44_RB1)
					{
						CheckDlgButton(hwd,DLG44_RB1,BST_CHECKED);
						CheckDlgButton(hwd,DLG44_RB2,BST_UNCHECKED);
						CheckDlgButton(hwd,DLG44_RB3,BST_UNCHECKED);
					}else
					if(wp==DLG44_RB2)
					{
						CheckDlgButton(hwd,DLG44_RB1,BST_UNCHECKED);
						CheckDlgButton(hwd,DLG44_RB2,BST_CHECKED);
						CheckDlgButton(hwd,DLG44_RB3,BST_UNCHECKED);
					}else
					if(wp==DLG44_RB3)
					{
						CheckDlgButton(hwd,DLG44_RB1,BST_UNCHECKED);
						CheckDlgButton(hwd,DLG44_RB2,BST_UNCHECKED);
						CheckDlgButton(hwd,DLG44_RB3,BST_CHECKED);
					}
					break;
				}

				
				if(wp==DLG44_B2)		//Anuluj
				{

					is_print=false;
					DestroyWindow(hwd);
					break;
				}
				if(wp==DLG44_B1)		//Drukuj
				{
					
					
					if(IsDlgButtonChecked(hwd,DLG44_RB1)) pr_info[sel_item].pDevMode->dmDuplex=DMDUP_SIMPLEX;
						else if(IsDlgButtonChecked(hwd,DLG44_RB2)) pr_info[sel_item].pDevMode->dmDuplex=DMDUP_VERTICAL;
							else if(IsDlgButtonChecked(hwd,DLG44_RB3)) pr_info[sel_item].pDevMode->dmDuplex=DMDUP_HORIZONTAL;
					i=ListView_GetItemCount(LV1);
					if(i<=0)
					{
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Nie ma ¿adnej pozycji w tabeli");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						break;
					}
					if(IsDlgButtonChecked(hwd,DLG44_CB2)) Print_Mag1(pr_info[sel_item],hwd,A_id,i);else
					Print_Mag(pr_info[sel_item],hwd,A_id,i);
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
				if(bt!=NULL) delete bt;
				EndDialog(hwd,0);
				break;
			}
		default : return DefDlgProc(GetParent(hwd),code,wp,lp);
	}
	return 0;
}

LRESULT _stdcall DLG45Proc(HWND hwd, int code, WPARAM wp, LPARAM lp)
{
	int i;
	double wart[4];
	int ilosc,il;
	char text[100];

	LVCOLUMN lvc;
	LVITEM lvi;

	switch(code)
	{
		case WM_INITDIALOG:
			{
				LVD_45=GetDlgItem(hwd,DLG45_LV1);
				for(i=0;i<5;i++)
				{
					memset((char*)&lvc,0,sizeof(LVCOLUMN));
					lvc.mask=LVCF_TEXT|LVCF_WIDTH;
					lvc.cx=LVD45_W[i];;
					lvc.pszText=LVD45[i];
					ListView_InsertColumn(LVD_45,i,&lvc);
				}
				il=ListView_GetItemCount(LV1);
				if(il<=0)break;
				memset((char*)wart,0,sizeof(double)*4);
				ilosc=0;
				for(i=0;i<il;i++)
				{
					if(ART[A_id[i]].Stan<=0) continue;
					ilosc+=ART[A_id[i]].Stan;
					wart[0]+=ART[A_id[i]].Cena_Zakupu*ART[A_id[i]].Stan;
					wart[1]+=ART[A_id[i]].Marza;
					wart[2]+=ART[A_id[i]].Cena_Netto*ART[A_id[i]].Stan;
					wart[3]+=ART[A_id[i]].Cena_Brutto*ART[A_id[i]].Stan;
				}
				wart[1]=wart[1]/il;
				for(i=0;i<5;i++)
				{
					memset((char*)&lvi,0,sizeof(LVITEM));
					lvi.mask=LVIF_TEXT;
					lvi.iSubItem=0;
					memset(text,0,100);
					if(i==0) 
					{
						itoa(ilosc,text,10);
						lvi.pszText=text;
						ListView_InsertItem(LVD_45,&lvi);
					}else
					{
						dbl_str(wart[i-1],text,2,100);
						if(i==2) sprintf(&text[strlen(text)],"%s","%"); else strcpy(text+strlen(text),wal[cnt.def_wal].znak);
						ListView_SetItemText(LVD_45,0,i,text);
					}
					
				}
				break;
			}
		case WM_COMMAND:
			{
				if(wp==DLG45_B1)
				{
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
				EndDialog(hwd,0);
				break;
			}
		default: return DefDlgProc(GetParent(hwd),code,wp,lp);

	}
	return 0;
}



LRESULT _stdcall DLG46Proc(HWND hwd, int code, WPARAM wp, LPARAM lp)
{
	char text[100];
	int i;
	switch(code)
	{
		case WM_INITDIALOG:
			{
				is_zm_num=false;
				memset(text,0,100);
				itoa(HD_FB.id+1,text,10);
				SetWindowText(GetDlgItem(hwd,DLG46_E1),text);
				break;
			}
		case WM_COMMAND:
			{
				if(wp==DLG46_B2)		//Anuluj
				{
					DestroyWindow(hwd);
					break;
				}
				if(wp==DLG46_B1)		//OK
				{
					memset(text,0,100);
					GetWindowText(GetDlgItem(hwd,DLG46_E1),text,100);
					i=atoi(text);
					if(i!=HD_FB.id)
					{
						if(i>1) HD_FB.id=i-1; else HD_FB.id=0;
						is_zm_num=true;
					}
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
				EndDialog(hwd,0);
				break;
			}
		default: return DefDlgProc(GetParent(hwd),code,wp,lp);

	}
	return 0;
}