


#pragma comment(lib,"comctl32.lib")
//#pragma comment(lib,"WinIP.lib")

#include "DBAMng.h"
#include "math.h"
bool LProc;

FIRMA  (*get_F)(void);


HWND DLG26;

LRESULT  _stdcall DlgProc(HWND hwd,int code,WPARAM wp,LPARAM lp)
{
	RECT wrc;
	HBRUSH hbr;
	HPEN hpn;
	PAINTSTRUCT pnt;
	HDC hdc1;
	bool is_valid,is_max;
	int i,i1,i2;
	char w_text[350];
	LPSTR LPS;
	LVITEM lvi;
	int *ida;
	char txt[350];

	switch (code)
	{
		
	
		case WM_CLOSE:
			 {
				 DestroyWindow(hwd);
				 break;
			 }
		case WM_DESTROY:
			{
				if(A_id!=NULL) delete A_id;
				//if(t_id!=NULL) delete t_id;
				if(ART!=NULL) delete ART;
				if(PR!=NULL) delete PR;
				if(KONTR!=NULL) delete KONTR;
				//if(F_Vat!=NULL) delete F_Vat;
				if(HD_F!=NULL) delete HD_F;
				if(KS!=NULL) delete KS;
				if(LProc && WINIP_M!=NULL) FreeLibrary(WINIP_M);
				if(Kas_ind!=NULL) delete Kas_ind;
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
				PostQuitMessage(0);
			}
		case WM_SIZE:
			{
				
				is_max=false;
				GetWindowRect(hwd,&wrc);
				i=wrc.right-wrc.left;
				if(i>MAX_X) 
				{
					wrc.right=wrc.left+MAX_X;
					is_max=true;
				}
				i=wrc.bottom-wrc.top;
				if(i>MAX_Y) 
				{
					wrc.bottom=wrc.top+MAX_Y;
					is_max=true;
				}
				if(is_max)
				{
					MoveWindow(hwd,wrc.left,wrc.top,wrc.right-wrc.left,wrc.bottom-wrc.top,true);
					EnableWindow(hwd,false);
					EnableWindow(hwd,true);
				}
				break;
			}
		case WM_HOTKEY:
			{
				if(GetFocus()!=MainWnd) break;
				if(is_dlg1==true || is_dlg2==true || is_dlg3==true || is_dlg4==true || is_dlg6==true || is_dlg8==true || is_dlg14==true) break;
				
				if(wp==HOT_U_WAL)
				{
					SendMessage(hwd,WM_COMMAND,(WPARAM)ID_WAL,0);
					break;
				}

				if(wp==HOT_U_FZ)
				{
					SendMessage(hwd,WM_COMMAND,(WPARAM)ID_F_Z,0);
					break;
				}

				if(wp==HOT_U_ST)
				{
					SendMessage(hwd,WM_COMMAND,(WPARAM)ID_VAT,0);
					break;
				}

				if(wp==HOT_U_NF)
				{
					SendMessage(hwd,WM_COMMAND,(WPARAM)ID_N_V,0);
					break;
				}

				if(wp==HOT_U_JM)
				{
					SendMessage(hwd,WM_COMMAND,(WPARAM)ID_JM,0);
					break;
				}

				if(wp==HOT_U_GR)
				{
					SendMessage(hwd,WM_COMMAND,(WPARAM)ID_GR,0);
					break;
				}

				if(wp==HOT_K_U)
				{
					SendMessage(hwd,WM_COMMAND,(WPARAM)ID_K_U,0);
					break;
				}

				if(wp==HOT_K_D)
				{
					SendMessage(hwd,WM_COMMAND,(WPARAM)ID_DEF_KAS,0);
					break;
				}
				
				if(wp==HOT_K_S)
				{
					SendMessage(hwd,WM_COMMAND,(WPARAM)ID_SZUK_KAS,0);
					break;
				}
				if(wp==HOT_K_I)
				{
					SendMessage(hwd,WM_COMMAND,(WPARAM)ID_K_Z,0);
					break;
				}
				if(wp==HOT_K_A)
				{
					is_dlg1=true;
					SendMessage(hwd,WM_COMMAND,(WPARAM)ID_K_D,0);
					break;
				}
				if(wp==HOT_FIR)
				{
					SendMessage(hwd,WM_COMMAND,(WPARAM)ID_FIR_P,0);
					break;
				}
				if(wp==HOT_F_Z)
				{
					if(!is_dlg8)SendMessage(hwd,WM_COMMAND,(WPARAM)ID_VAT_Z,0);
					break;
				}
				if (wp==HOT_K_Z)
				{
					if(!is_dlg6)SendMessage(hwd,WM_COMMAND,(WPARAM)ID_KONT_Z,0);
					break;
				}
				if(wp==HOT_F_W)
				{
					if(!is_dlg4)
					SendMessage(hwd,WM_COMMAND,(WPARAM)ID_VAT_W,0);
					break;
				}
				if(wp==HOT_P_Z)
				{
					if(!is_dlg2)
					SendMessage(hwd,WM_COMMAND,(WPARAM)ID_Za_P,0);
					break;
				}
			
				if(wp==HOT_P_D)
				{
					if(!is_dlg3)
					DialogBox(hst,MAKEINTRESOURCE(ID_DLG_3),hwd,(DLGPROC)&DlgProc3);
					break;
				}
				if(wp==HOT_KON)
				{
					DestroyWindow(hwd);
					break;
				}else
				if(wp==HOT_ADD_A)
				{
					if(!is_dlg1) SendMessage(hwd,WM_COMMAND,(WPARAM)ID_Dod_A,0);
					break;
				}else
				if(wp==HOT_REM_A)
				{
					SendMessage(hwd,WM_COMMAND,(WPARAM)ID_Us_A,0);
					break;
				}else
				if(wp==HOT_ED_A)
				{
					if(!is_dlg1) SendMessage(hwd,WM_COMMAND,(WPARAM)ID_Edit_A,0);
					break;
				}else
					if(wp==HOT_P_T)
					{
						SendMessage(hwd,WM_COMMAND,(WPARAM)ID_P_T,0);
					}


			}
		case WM_PAINT:
			{
				hdc=BeginPaint(hwd,&lpP);
				PaintTool(hdc,cx,sy);
				EndPaint(hwd,&lpP);
				UpdateWindow(CB1);
				break;
			}
		
		case WM_COMMAND:
			{
				
				if(wp==(WPARAM)Panel)
				{
					bool bl;
					DWORD dw;
					WORD a,b;

					//if(GetFocus()!=Panel) break;
					HTR=TreeView_GetSelection(Panel);
					if(HTR==H_f[0])			// Odczytanie towarów z kasy
					{
						is_dlg1=true;
						is_tow=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_23),hwd,(DLGPROC)&DLG23Proc);
						SetFocus(hwd);
						is_dlg1=false;
						if(is_tow)is_tow=false;
						else
						{
							is_dlg1=true;
							is_tow=false;
							DialogBox(hst,MAKEINTRESOURCE(ID_DLG_24),hwd,(DLGPROC)&DLG24Proc);
							SetFocus(hwd);
							SendMessage(MainWnd,WM_COMMAND,(WPARAM)ID_B_Szuk,0);
						}
						break;
					}

					if(HTR==H_f[2] || HTR==H_f[1])			//Odczytanie/zapisanie pe³nych danych o towarze
					{
						memset(kod_tow,0,35);
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_5),hwd,(DLGPROC)&Dlg5Proc);
						if(kod_tow[0]!=0)
						{
							is_dlg1=true;
							is_tow=true;
							DialogBox(hst,MAKEINTRESOURCE(ID_DLG_23),hwd,(DLGPROC)&DLG23Proc);
							SetFocus(hwd);
							is_dlg1=false;
							if(is_tow)is_tow=false;
							else
							{	
								is_show=true;

								DialogBox(hst,MAKEINTRESOURCE(ID_DLG_26),MainWnd,(DLGPROC)DLG26Proc);
								if(ecode==-3)
								{
									memset(Err_Text,0,350);
									sprintf(Err_Text,"Pod podanym numerem nie ma zdefiniowanego towaru w kasie fiskalnej");
									DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
									SetFocus(hwd);
									break;
								}
								if(ecode==0)
								{
									strncpy(TK.numer,kod_tow,35);
									is_dlg1=true;
									if(HTR==H_f[2])is_zapT=false; else is_zapT=true;
									DialogBox(hst,MAKEINTRESOURCE(ID_DLG_27),hwd,(DLGPROC)&DLG27Proc);
									SetFocus(hwd);
									is_dlg1=false;
								}
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
							}
						}
						SetFocus(hwd);
						SendMessage(MainWnd,WM_COMMAND,(WPARAM)ID_B_Szuk,0);
						break;
					}

					if(HTR==H_f[4] || HTR==H_f[3])		//wysy³a i usuwa towary do kasy fiskalnej
					{
						is_dlg1=true;
						is_tow=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_23),hwd,(DLGPROC)&DLG23Proc);
						SetFocus(hwd);
						is_dlg1=false;
						if(is_tow)
						{
							is_tow=false;
							break;
						}
						is_dlg1=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_28),hwd,(DLGPROC)&DLG28Proc);
						SetFocus(hwd);
						is_dlg1=false;
						SendMessage(MainWnd,WM_COMMAND,(WPARAM)ID_B_Szuk,0);
						break;
					}

					if(HTR==H_f[5])			//kasowanie wszystkich towarów
					{
						is_dlg1=true;
						is_tow=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_23),hwd,(DLGPROC)&DLG23Proc);
						SetFocus(hwd);
						is_dlg1=false;
						if(is_tow)
						{
							is_tow=false;
							break;
						}
						is_dlg1=true;
						is_del=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_28),hwd,(DLGPROC)&DLG28Proc);
						SetFocus(hwd);
						is_del =false;
						is_dlg1=false;
						SendMessage(MainWnd,WM_COMMAND,(WPARAM)ID_B_Szuk,0);
						break;
					}

					if(HTR==H_f[6])			//odczytanie maksymalnego numeru towaru z kasy
					{
						is_tow=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_23),hwd,(DLGPROC)&DLG23Proc);
						SetFocus(hwd);
						is_dlg1=false;
						if(is_tow)
						{
							is_tow=false;
							break;
						}
						i=get_data(KS[Kas_id],&i1,_ONrTowar,NULL,0);
						if(i!=0)
						{
							if(i<0)
							{
								memset(Err_Text,0,350);
								sprintf(Err_Text,"Nie mo¿na utworzyæ pliku danych wyjœciowych kasy fiskalnej");
								DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),H24,(DLGPROC)&DLGERRProc);
								SetFocus(hwd);
							}else
							{
								memset(Err_Text,0,350);
								LoadString(hst,i+1000,txt,350);
								sprintf(Err_Text,"Nie mo¿na wykonaæ operacji\n%s",txt);
								DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
								SetFocus(hwd);
							}
						}else
						{
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Najwiêkszy numer zdefiniowany w kasie fiskalnej: %d",i1);
							DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
							SetFocus(hwd);
						}
						break;
					}

					if(HTR==H_f[7])			//odczytanie iloœci towarów w kasie
					{

						is_tow=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_23),hwd,(DLGPROC)&DLG23Proc);
						SetFocus(hwd);
						is_dlg1=false;
						if(is_tow)
						{
							is_tow=false;
							break;
						}
						i=get_data(KS[Kas_id],&i1,_OIlZaPLU,NULL,0);
						if(i!=0)
						{
							if(i<0)
							{
								memset(Err_Text,0,350);
								sprintf(Err_Text,"Nie mo¿na utworzyæ pliku danych wyjœciowych kasy fiskalnej");
								DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),H24,(DLGPROC)&DLGERRProc);
								SetFocus(hwd);
							}else
							{
								memset(Err_Text,0,350);
								LoadString(hst,i+1000,txt,350);
								sprintf(Err_Text,"Nie mo¿na wykonaæ operacji\n%s",txt);
								DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
								SetFocus(hwd);
							}
						}else
						{
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Iloœæ zdefiniowanych w kasie towarów: %d",i1);
							DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
							SetFocus(hwd);
						}
						break;
					}

					if(HTR==H_f[8])			//wydruk raportów towarów zmienionych i skasowanych
					{
						is_tow=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_23),hwd,(DLGPROC)&DLG23Proc);
						SetFocus(hwd);
						is_dlg1=false;
						if(is_tow)
						{
							is_tow=false;
							break;
						}
						i=get_data(KS[Kas_id],&i1,_DrukRap,NULL,0);
						if(i<0)
						{
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Nie mo¿na utworzyæ pliku danych wyjœciowych kasy fiskalnej");
							DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),H24,(DLGPROC)&DLGERRProc);
							SetFocus(hwd);
						}
						else if(i>0)
						{
							if(i==1)
							{
								memset(Err_Text,0,350);
								LoadString(hst,i+1000,txt,350);
								sprintf(Err_Text,"Nie mo¿na wykonaæ operacji, poniewa¿ rozpoczêto paragon");
							}else
							if(i==2)
							{
								memset(Err_Text,0,350);
								LoadString(hst,i+1000,txt,350);
								sprintf(Err_Text,"Nie mo¿na wykonaæ operacji, problem z drukarka (brak papieru, podniesiona g³owica)");
							}else
							if(i==3)
							{
								memset(Err_Text,0,350);
								LoadString(hst,i+1000,txt,350);
								sprintf(Err_Text,"Nie mo¿na wykonaæ operacji, z powodu innej przyczyny (brak komunikacji z kontrolerem drukarki, nie wpisane dane u¿ytkownika, w pamiêci dokument do wydrukowania, modu³ przeszed³ w tryb tylko odczyt)");
							}else
							if(i==4)
							{
								memset(Err_Text,0,350);
								LoadString(hst,i+1000,txt,350);
								sprintf(Err_Text,"Nie mo¿na wykonaæ operacji, kasa nie jest w trybie sprzeda¿y (w pierwszej linii na wyœwietlaczu nie ma napisu TRYB SPRZEDA¯Y).");
							}
							memset(Err_Text,0,350);
							LoadString(hst,i+1000,txt,350);
							sprintf(Err_Text,"Nie mo¿na wykonaæ operacji\n%s",txt);
							DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
							SetFocus(hwd);
						}
						else
						{
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Rozpoczêto wydruk raportu");
							DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
							SetFocus(hwd);
						}
						break;
					}

					if(HTR==H_f[9])			//wydruk raportu dobowego
					{
						is_tow=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_23),hwd,(DLGPROC)&DLG23Proc);
						SetFocus(hwd);
						is_dlg1=false;
						if(is_tow)
						{
							is_tow=false;
							break;
						}
						i=get_data(KS[Kas_id],&i1,_DrukRapD,NULL,0);
						if(i<0)
						{
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Nie mo¿na utworzyæ pliku danych wyjœciowych kasy fiskalnej");
							DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),H24,(DLGPROC)&DLGERRProc);
							SetFocus(hwd);
						}
						else if(i>0)
						{
							if(i==1)
							{
								memset(Err_Text,0,350);
								LoadString(hst,i+1000,txt,350);
								sprintf(Err_Text,"Nie mo¿na wykonaæ operacji, poniewa¿ rozpoczêto paragon");
							}else
							if(i==2)
							{
								memset(Err_Text,0,350);
								LoadString(hst,i+1000,txt,350);
								sprintf(Err_Text,"Nie mo¿na wykonaæ operacji, problem z drukarka (brak papieru, podniesiona g³owica)");
							}else
							if(i==3)
							{
								memset(Err_Text,0,350);
								LoadString(hst,i+1000,txt,350);
								sprintf(Err_Text,"Nie mo¿na wykonaæ operacji, z powodu innej przyczyny (brak komunikacji z kontrolerem drukarki, nie wpisane dane u¿ytkownika, w pamiêci dokument do wydrukowania, modu³ przeszed³ w tryb tylko odczyt)");
							}else
							if(i==4)
							{
								memset(Err_Text,0,350);
								LoadString(hst,i+1000,txt,350);
								sprintf(Err_Text,"Nie mo¿na wykonaæ operacji, kasa nie jest w trybie sprzeda¿y (w pierwszej linii na wyœwietlaczu nie ma napisu TRYB SPRZEDA¯Y).");
							}
							else
							{
								memset(Err_Text,0,350);
								LoadString(hst,i+1000,txt,350);
								sprintf(Err_Text,"Nie mo¿na wykonaæ operacji\n%s",txt);
							}
							DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
							SetFocus(hwd);
						}
						else
						{
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Rozpoczêto wydruk raportu");
							DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
							SetFocus(hwd);
						}
						break;
					}

					if(HTR==H_f[10])		//Odczytanie nuneru kasy	
					{
						is_tow=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_23),hwd,(DLGPROC)&DLG23Proc);
						SetFocus(hwd);
						is_dlg1=false;
						if(is_tow)
						{
							is_tow=false;
							break;
						}
						i=get_data(KS[Kas_id],&i1,_ONrKasy,NULL,0);
						if(i<0)
						{
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Nie mo¿na utworzyæ pliku danych wyjœciowych kasy fiskalnej");
							DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),H24,(DLGPROC)&DLGERRProc);
							SetFocus(hwd);
						}
						else if(i>0)
						{
							memset(Err_Text,0,350);
							LoadString(hst,i+1000,txt,350);
							sprintf(Err_Text,"Nie mo¿na wykonaæ operacji\n%s",txt);
							DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
							SetFocus(hwd);
						}
						else
						{
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Numer kasy w systemie: %d",i1);
							DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
							SetFocus(hwd);
						}
						break;
					}

					if(HTR==H_f[11])		//Zapisanie nuneru kasy	
					{
						is_tow=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_23),hwd,(DLGPROC)&DLG23Proc);
						SetFocus(hwd);
						is_dlg1=false;
						if(is_tow)
						{
							is_tow=false;
							break;
						}
						is_dlg1=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_30),hwd,(DLGPROC)&DLG30Proc);
						SetFocus(hwd);
						is_dlg1=false;
						break;
					}

					if(HTR==H_f[12])		//Odczytanie bajtów konfiguracji
					{
						is_tow=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_23),hwd,(DLGPROC)&DLG23Proc);
						SetFocus(hwd);
						is_dlg1=false;
						if(is_tow)
						{
							is_tow=false;
							break;
						}
						is_dlg1=true;
						is_zap13=false;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_31),hwd,(DLGPROC)&DLG31Proc);
						SetFocus(hwd);
						is_dlg1=false;
						break;
					}

					if(HTR==H_f[13])		//Zapisanie bitów konfiguracji
					{
						is_tow=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_23),hwd,(DLGPROC)&DLG23Proc);
						SetFocus(hwd);
						is_dlg1=false;
						if(is_tow)
						{
							is_tow=false;
							break;
						}
						is_dlg1=true;
						is_zap13=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_31),hwd,(DLGPROC)&DLG31Proc);
						SetFocus(hwd);
						is_dlg1=false;
						break;
					}

					if(HTR==H_f[14])		//odczytanie nazw jednostek
					{
						is_tow=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_23),hwd,(DLGPROC)&DLG23Proc);
						SetFocus(hwd);
						is_dlg1=false;
						if(is_tow)
						{
							is_tow=false;
							break;
						}
						is_dlg1=true;
						is_zap13=false;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_32),hwd,(DLGPROC)&DLG32Proc);
						SetFocus(hwd);
						is_dlg1=false;
						break;
					}

					if(HTR==H_f[15])		//zapisywanie nazw jednostek
					{
						is_tow=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_23),hwd,(DLGPROC)&DLG23Proc);
						SetFocus(hwd);
						is_dlg1=false;
						if(is_tow)
						{
							is_tow=false;
							break;
						}
						is_dlg1=true;
						is_zap13=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_32),hwd,(DLGPROC)&DLG32Proc);
						SetFocus(hwd);
						is_dlg1=false;
						break;
					}

					if(HTR==H_f[16])		//odczytanie nazw grup
					{
						is_tow=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_23),hwd,(DLGPROC)&DLG23Proc);
						SetFocus(hwd);
						is_dlg1=false;
						if(is_tow)
						{
							is_tow=false;
							break;
						}
						is_dlg1=true;
						is_zap13=false;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_33),hwd,(DLGPROC)&DLG33Proc);
						SetFocus(hwd);
						is_dlg1=false;
						break;
					}

					if(HTR==H_f[17])		//zapisywanie nazw grup
					{
						is_tow=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_23),hwd,(DLGPROC)&DLG23Proc);
						SetFocus(hwd);
						is_dlg1=false;
						if(is_tow)
						{
							is_tow=false;
							break;
						}
						is_dlg1=true;
						is_zap13=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_33),hwd,(DLGPROC)&DLG33Proc);
						SetFocus(hwd);
						is_dlg1=false;
						break;
					}

					if(HTR==H_f[18])		//odczytywanie stawek podatkowych z kasy
					{
						is_tow=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_23),hwd,(DLGPROC)&DLG23Proc);
						SetFocus(hwd);
						is_dlg1=false;
						if(is_tow)
						{
							is_tow=false;
							break;
						}
						is_dlg1=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_34),hwd,(DLGPROC)&DLG34Proc);
						SetFocus(hwd);
						is_dlg1=false;
						break;
					}

					if(HTR==H_f[19])		//odczytanie nazw form zap³aty z kasy
					{
						is_tow=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_23),hwd,(DLGPROC)&DLG23Proc);
						SetFocus(hwd);
						is_dlg1=false;
						if(is_tow)
						{
							is_tow=false;
							break;
						}
						is_dlg1=true;
						is_zap13=false;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_35),hwd,(DLGPROC)&DLG35Proc);
						SetFocus(hwd);
						is_dlg1=false;
						break;
					}

					if(HTR==H_f[20])		//zapisywanie nazw form zap³aty
					{
						is_tow=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_23),hwd,(DLGPROC)&DLG23Proc);
						SetFocus(hwd);
						is_dlg1=false;
						if(is_tow)
						{
							is_tow=false;
							break;
						}
						is_dlg1=true;
						is_zap13=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_35),hwd,(DLGPROC)&DLG35Proc);
						SetFocus(hwd);
						is_dlg1=false;
						break;
					}

					if(HTR==H_f[21])		//Odczytanie maksymalnego rabatu z kasy	
					{
						is_tow=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_23),hwd,(DLGPROC)&DLG23Proc);
						SetFocus(hwd);
						is_dlg1=false;
						if(is_tow)
						{
							is_tow=false;
							break;
						}
						i=get_data(KS[Kas_id],&i1,_ORabat,NULL,0);
						if(i<0)
						{
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Nie mo¿na utworzyæ pliku danych wyjœciowych kasy fiskalnej");
							DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),H24,(DLGPROC)&DLGERRProc);
							SetFocus(hwd);
						}
						else if(i>0)
						{
							memset(Err_Text,0,350);
							LoadString(hst,i+1000,txt,350);
							sprintf(Err_Text,"Nie mo¿na wykonaæ operacji\n%s",txt);
							DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
							SetFocus(hwd);
						}
						else
						{
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Maksymalny rabat: %d%%",i1);
							DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
							SetFocus(hwd);
						}
						break;
					}

					if(HTR==H_f[22])		//Zapisanie maksymalnego rabatu do kasy	
					{
						is_tow=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_23),hwd,(DLGPROC)&DLG23Proc);
						SetFocus(hwd);
						is_dlg1=false;
						if(is_tow)
						{
							is_tow=false;
							break;
						}
						is_dlg1=true;
						is_zap13=false;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_36),hwd,(DLGPROC)&DLG36Proc);
						SetFocus(hwd);
						is_dlg1=false;
						break;
					}

					if(HTR==H_f[23])		//Odczytanie maksymalnego narzutu z kasy	
					{
						is_tow=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_23),hwd,(DLGPROC)&DLG23Proc);
						SetFocus(hwd);
						is_dlg1=false;
						if(is_tow)
						{
							is_tow=false;
							break;
						}
						i=get_data(KS[Kas_id],&i1,_ONarzut,NULL,0);
						if(i<0)
						{
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Nie mo¿na utworzyæ pliku danych wyjœciowych kasy fiskalnej");
							DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),H24,(DLGPROC)&DLGERRProc);
							SetFocus(hwd);
						}
						else if(i>0)
						{
							memset(Err_Text,0,350);
							LoadString(hst,i+1000,txt,350);
							sprintf(Err_Text,"Nie mo¿na wykonaæ operacji\n%s",txt);
							DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
							SetFocus(hwd);
						}
						else
						{
							memset(Err_Text,0,350);
							sprintf(Err_Text,"Maksymalny narzut: %d%%",i1);
							DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
							SetFocus(hwd);
						}
						break;
					}

					if(HTR==H_f[24])		//Zapisanie maksymalnego narzutu do kasy	
					{
						is_tow=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_23),hwd,(DLGPROC)&DLG23Proc);
						SetFocus(hwd);
						is_dlg1=false;
						if(is_tow)
						{
							is_tow=false;
							break;
						}
						is_dlg1=true;
						is_zap13=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_36),hwd,(DLGPROC)&DLG36Proc);
						SetFocus(hwd);
						is_dlg1=false;
						is_zap13=false;
						break;
					}

					if(HTR==H_f[25])		//Odczytanie stanów magazynowych
					{
						is_dlg1=true;
						funkcja=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_23),hwd,(DLGPROC)&DLG23Proc);
						SetFocus(hwd);
						if(funkcja)
						{
							funkcja=false;
							is_show=false;
							DialogBox(hst,MAKEINTRESOURCE(ID_DLG_26),hwd,(DLGPROC)&DLG26Proc);
							SetFocus(hwd);
						}else break;
						if(ecode!=0) break;
						memset(Err_Text,0,350);
						sprintf(Err_Text,"Zakoñczono aktualizacjê stanów magazynowych");
						DialogBox(hst,MAKEINTRESOURCE(DLG_I),hwd,(DLGPROC)&DLGIProc);
						SetFocus(hwd);
						is_dlg1=false;
						SendMessage(MainWnd,WM_COMMAND,(WPARAM)ID_B_Szuk,0);
						break;
					}
					
					if(HTR==H_f[26])		//Odczytanie raportu godzinowego z kasy
					{
						is_tow=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_23),hwd,(DLGPROC)&DLG23Proc);
						SetFocus(hwd);
						is_dlg1=false;
						if(is_tow)
						{
							is_tow=false;
							break;
						}
						is_zap13=false;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_37),hwd,(DLGPROC)&DLG37Proc);
						SetFocus(hwd);
						break;
					}

				if(HTR==H_f[27])		//Zapisanie poprzedniego raportu godzinowego z kasy
					{
						is_tow=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_23),hwd,(DLGPROC)&DLG23Proc);
						SetFocus(hwd);
						is_dlg1=false;
						if(is_tow)
						{
							is_tow=false;
							break;
						}
						is_zap13=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_37),hwd,(DLGPROC)&DLG37Proc);
						SetFocus(hwd);
						is_zap13=false;
						break;
					
					}

					if(HTR==H_f[28])		//Odczytanie rodzajów kasjerów z kasy
					{
						is_tow=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_23),hwd,(DLGPROC)&DLG23Proc);
						SetFocus(hwd);
						is_dlg1=false;
						if(is_tow)
						{
							is_tow=false;
							break;
						}
						is_zap13=false;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_38),hwd,(DLGPROC)&DLG38Proc);
						SetFocus(hwd);
						break;
					
					}
				
					if(HTR==H_f[29])		//Zapisanie rodzajów kasjerów z kasy
					{
					
						is_tow=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_23),hwd,(DLGPROC)&DLG23Proc);
						SetFocus(hwd);
						is_dlg1=false;
						if(is_tow)
						{
							is_tow=false;
							break;
						}
						is_zap13=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_38),hwd,(DLGPROC)&DLG38Proc);
						SetFocus(hwd);
						is_zap13=false;
						break;
					
					}

					if(HTR==H_f[30])		//Odczytanie danych kasjerów z kasy
					{
						is_tow=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_23),hwd,(DLGPROC)&DLG23Proc);
						SetFocus(hwd);
						is_dlg1=false;
						if(is_tow)
						{
							is_tow=false;
							break;
						}
						is_zap13=false;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_40),hwd,(DLGPROC)&DLG40Proc);
						SetFocus(hwd);
						break;
					
					}
				
					if(HTR==H_f[31])		//Zapisanie danych kasjerów do kasy
					{
					
						is_tow=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_23),hwd,(DLGPROC)&DLG23Proc);
						SetFocus(hwd);
						is_dlg1=false;
						if(is_tow)
						{
							is_tow=false;
							break;
						}
						is_zap13=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_40),hwd,(DLGPROC)&DLG40Proc);
						SetFocus(hwd);
						is_zap13=false;
						break;
					
					}

					if(HTR==H_f[32])		//Usuwanie danych kasjerów z kasy
					{
					
						is_tow=true;
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_23),hwd,(DLGPROC)&DLG23Proc);
						SetFocus(hwd);
						is_dlg1=false;
						if(is_tow)
						{
							is_tow=false;
							break;
						}
						DialogBox(hst,MAKEINTRESOURCE(ID_DLG_42),hwd,(DLGPROC)&DLG42Proc);
						SetFocus(hwd);
						break;
					
					}
					break;
				}
				if(wp==ID_DEF_KAS)
				{
					is_dlg1=true;
					DialogBox(hst,MAKEINTRESOURCE(ID_DLG_23),hwd,(DLGPROC)&DLG23Proc);
					SetFocus(hwd);
					is_dlg1=false;
					break;
				}

				if(wp==ID_SZUK_KAS)
				{
					is_dlg1=true;
					DialogBox(hst,MAKEINTRESOURCE(ID_DLG_21),hwd,(DLGPROC)&DLG21Proc);
					SetFocus(hwd);
					is_dlg1=false;
					break;
				}

				if(wp==ID_N_V)
				{
					is_dlg1=true;
					DialogBox(hst,MAKEINTRESOURCE(ID_DLG_20),hwd,(DLGPROC)&DLG20Proc);
					SetFocus(hwd);
					is_dlg1=false;
					break;
				}

				if(wp==ID_JM)
				{
					is_dlg1=true;
					DialogBox(hst,MAKEINTRESOURCE(ID_DLG_19),hwd,(DLGPROC)&DLG19Proc);
					SetFocus(hwd);
					is_dlg1=false;
					break;
				}

				if(wp==ID_GR)
				{
					is_dlg1=true;
					DialogBox(hst,MAKEINTRESOURCE(ID_DLG_29),hwd,(DLGPROC)&DLG29Proc);
					SetFocus(hwd);
					is_dlg1=false;
					break;
				}

				
				if(wp==ID_VAT)
				{
					is_dlg1=true;
					DialogBox(hst,MAKEINTRESOURCE(ID_DLG_18),hwd,(DLGPROC)&DLG18Proc);
					SetFocus(hwd);
					is_dlg1=false;
					break;
				}

				if(wp==ID_F_Z)
				{
					is_dlg1=true;
					DialogBox(hst,MAKEINTRESOURCE(ID_DLG_17),hwd,(DLGPROC)&DLG17Proc);
					SetFocus(hwd);
					is_dlg1=false;
					break;
				}

				if(wp==ID_WAL)
				{
					is_dlg1=true;
					DialogBox(hst,MAKEINTRESOURCE(ID_DLG_16),hwd,(DLGPROC)&DLG16Proc);
					SetFocus(hwd);
					is_dlg1=false;
					if(is_zm_wal) SendMessage(MainWnd,WM_COMMAND,(WPARAM)ID_B_Szuk,0);
					break;
				}

				if(wp==ID_K_Z)
				{
					is_dlg14=true;
					DialogBox(hst,MAKEINTRESOURCE(ID_DLG_15),hwd,(DLGPROC)&DLG15Proc);
					SetFocus(hwd);
					break;
				}
				if(wp==ID_K_U)
				{
					if(KS==NULL)
					{
						memset(Err_Text,0,150);
						sprintf(Err_Text,"Nie mo¿n zaladowaæ bazy zawieraj¹cej zainstalowane kasy fiskalne. Prawdopodobnie zosta³a uszkodzona biblioteka fisk.dll. Skontaktuj siê z autorem programu, albo przeinstaluj program");
						DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),hwd,(DLGPROC)&DLGERRProc);
						break;
					}
					is_dlg14=true;
					Kas_id=-1;
					DialogBox(hst,MAKEINTRESOURCE(ID_DLG_14),hwd,(DLGPROC)&DLG14Proc);
					SetFocus(hwd);
					break;
				}
				if(wp==ID_K_D)
				{
					is_dlg1=true;
					Kas_id=-1;
					DialogBox(hst,MAKEINTRESOURCE(ID_DLG_13),hwd,(DLGPROC)&Dlg13Proc);
					SetFocus(hwd);
					break;
				}
				if(wp==ID_P_T)
				{
					is_dlg1=true;
					for(i=0;i<HD_A.count;i++)
					{
						if(ART[i].Stan<0)
						{
							memset(Query_Text,0,150);
							sprintf(Query_Text,"W bazie danych znajduj¹ siê artyku³y z ujemnymi stanami.\nJeœli nie zostan¹ wyzerowane to mog¹ siê nie zgadzaæ iloœci towarów\n Czy chcesz wyzerowaæ ujemne stany magazynowe ?");
							DialogBox(hst,MAKEINTRESOURCE(DLG_Q),hwd,(DLGPROC)&DLGQProc);
							if(is_ok)
							{
								for(i=0;i<HD_A.count;i++)
								{
									if (ART[i].Stan < 0)

									{
										ART[i].Stan = 0;
										Save_AR(&ART[i]);
									}
								}
							}
							break;
						}
					}
					DialogBox(hst,MAKEINTRESOURCE(ID_DLG_5),hwd,(DLGPROC)&Dlg5Proc);
					if(Tid!=-1)
					DialogBox(hst,MAKEINTRESOURCE(ID_DLG_12),hwd,(DLGPROC)&Dlg12Proc);	
					is_dlg1=false;
					SendMessage(hwd,WM_COMMAND,(WPARAM)ID_B_Szuk,0);
					SetFocus(hwd);
					break;
				}
				if(wp==ID_FIR_P)
				{
					is_dlg1=true;
					DialogBox(hst,MAKEINTRESOURCE(ID_DLG_10),hwd,(DLGPROC)&Dlg10Proc);
					SetFocus(hwd);
					break;
				}
				if(wp==ID_KONT_Z)
				{
					is_z_k=true;
					DialogBox(hst,MAKEINTRESOURCE(ID_DLG_6),hwd,(DLGPROC)&Dlg6Proc);
					is_z_k=false;
					SetFocus(hwd);
					break;
				}
				if(wp==ID_VAT_W)
				{
					DialogBox(hst,MAKEINTRESOURCE(ID_DLG_4),hwd,(DLGPROC)&Dlg4Proc);
					SetFocus(hwd);
					break;
				}
				if(wp==ID_VAT_Z)
				{
					DialogBox(hst,MAKEINTRESOURCE(ID_DLG_8),hwd,(DLGPROC)&Dlg8Proc);
					SetFocus(hwd);
					break;
				}
				if(wp==ID_Pr_A)
				{
					DialogBox(hst,MAKEINTRESOURCE(ID_DLG_3),hwd,(DLGPROC)&DlgProc3);				
					SetFocus(hwd);
					break;
				}
				if(wp==ID_Za_P)
				{
					is_zarz=true;
					DialogBox(hst,MAKEINTRESOURCE(ID_DLG_2),hwd,(DLGPROC)&DlgProc2);
					SetFocus(hwd);
					is_zarz=false;
					break;
				}

				if(wp==ID_Kon)
				{
					DestroyWindow(hwd);
				}
				if(wp==ID_Dod_A)
				{
					is_edit=false;
					DialogBox(hst,MAKEINTRESOURCE(ID_DLG_1),hwd,(DLGPROC)&DlgProc1);
					SetFocus(hwd);
					break;
				}
				if(wp==ID_Us_A)
				{
					i=-1;
					i=ListView_GetSelectionMark(LV1);
					if (i<0)break;
					i=A_id[i];
					memset(Query_Text,0,150);
					sprintf(Query_Text,"Czy napewno chcesz usun¹æ ten artyku³ z bazy danych ?");
					DialogBox(hst,MAKEINTRESOURCE(DLG_Q),hwd,(DLGPROC)&DLGQProc);
					if(is_ok)
					{
						Us_AR(ART[i].indeks);
						SendMessage(hwd,WM_COMMAND,(WPARAM)ID_B_Szuk,0);
					}
					SetFocus(hwd);
					break;
				}
				if(wp==ID_Edit_A)
				{
					i=-1;
					i=ListView_GetSelectionMark(LV1);
					if (i<0)break;
					is_edit=true;
					Aid=A_id[i];
					DialogBox(hst,MAKEINTRESOURCE(ID_DLG_1),hwd,(DLGPROC)&DlgProc1);
					SetFocus(hwd);
					break;
				}
				if(wp==ID_STAT)
				{
					is_dlg1=true;
					DialogBox(hst,MAKEINTRESOURCE(ID_DLG_43),hwd,(DLGPROC)&DLG43Proc);
					SetFocus(hwd);
					is_dlg1=false;
					break;
				}

				if(wp==ID_PR_MAG)
				{
					is_dlg1=true;
					DialogBox(hst,MAKEINTRESOURCE(ID_DLG_44),hwd,(DLGPROC)&DLG44Proc);
					SetFocus(hwd);
					is_dlg1=false;
					break;
				}

				if(wp==ID_WART_MAG)
				{
					is_dlg1=true;
					DialogBox(hst,MAKEINTRESOURCE(ID_DLG_45),hwd,(DLGPROC)&DLG45Proc);
					SetFocus(hwd);
					is_dlg1=false;
					break;
				}

				if(wp==(DWORD)CB1)
				{
					EnableWindow(E1,Check_isChecked(CB1));			//Nazwa Producenta
					break;
				}
				if(wp==(DWORD)CB2)
				{
					EnableWindow(E2,Check_isChecked(CB2));			 //Nazwa Towaru
					break;
				}
				if(wp==(DWORD)CB3)
				{
					EnableWindow(E3,Check_isChecked(CB3));			//Stan
					EnableWindow(E15,Check_isChecked(CB3));
					break;
				}
				if(wp==(DWORD)CB4)
				{
					EnableWindow(E4,Check_isChecked(CB4));			//Cena Zakupu
					EnableWindow(E7,Check_isChecked(CB4));
					break;
				}
				if(wp==(DWORD)CB5)
				{
					EnableWindow(E5,Check_isChecked(CB5));			//Mar¿a
					EnableWindow(E8,Check_isChecked(CB5));
					break;
				}
				if(wp==(DWORD)CB6)
				{
					EnableWindow(E6,Check_isChecked(CB6));			//Cena Netto
					EnableWindow(E9,Check_isChecked(CB6));
					break;
				}
				if(wp==(DWORD)CB7)
				{
					EnableWindow(E10,Check_isChecked(CB7));			//Vat
					break;
				}
				if(wp==(DWORD)CB8)
				{
					EnableWindow(E11,Check_isChecked(CB8));			//Cena Brutto
					EnableWindow(E12,Check_isChecked(CB8));
					break;
				}
				if(wp==(DWORD)CB9)
				{
					EnableWindow(E13,Check_isChecked(CB9));
					EnableWindow(E14,Check_isChecked(CB9));			//Minimum
					break;
				}
				if(wp==(DWORD)CB10)
				{
					EnableWindow(E16,Check_isChecked(CB10));			//Kod Towaru
					break;
				}
				if(wp==ID_B_Szuk)
				{
					i2=0;
					ListView_DeleteAllItems(LV1);
					if(A_id!=NULL) delete A_id;
					A_id=new int[HD_A.count];
					memset(A_id,-1,HD_A.count);
					for(i=0;i<HD_A.count;i++)
					{
						is_valid=true;
						if(Check_isChecked(CB1))
						{
							memset(w_text,0,350);
							GetWindowText(E1,w_text,350);
							if(w_text[0]!=0)
							{
								LPS=NULL;
								LPS=strstr(ART[i].Nazwa,w_text);
								if(LPS==NULL) is_valid=false;
							}
						}
						if(Check_isChecked(CB2) && is_valid)
						{
							memset(w_text,0,350);
							GetWindowText(E2,w_text,350);
							if(w_text[0]!=0)
							{
								LPS=NULL;
								LPS=strstr(ART[i].Producent,w_text);
								if(LPS==NULL) is_valid=false;
							}
						}
						if(Check_isChecked(CB3) && is_valid)
						{
							memset(w_text,0,350);
							GetWindowText(E3,w_text,350);
							if(w_text[0]!=0)
							{
								if(ART[i].Stan<atof(w_text)) is_valid=false;
							}
							if(is_valid)
							{
								memset(w_text,0,350);
								GetWindowText(E15,w_text,350);
								if(w_text[0]!=0)
								{
									if(ART[i].Stan>atof(w_text)) is_valid=false;
								}

							}
						}
						if(Check_isChecked(CB4) && is_valid)
						{
							memset(w_text,0,350);
							GetWindowText(E4,w_text,350);
							if(w_text[0]!=0)
							{
								if(ART[i].Cena_Zakupu<atof(w_text)) is_valid=false;
							}
							if(is_valid)
							{
								memset(w_text,0,350);
								GetWindowText(E7,w_text,350);
								if(w_text[0]!=0)
								{
									if(ART[i].Cena_Zakupu>atof(w_text)) is_valid=false;
								}

							}

						}
						if(Check_isChecked(CB5) && is_valid)
						{
							memset(w_text,0,350);
							GetWindowText(E5,w_text,350);
							if(w_text[0]!=0)
							{
								if(ART[i].Marza<atof(w_text)) is_valid=false;
							}
							if(is_valid)
							{
								memset(w_text,0,350);
								GetWindowText(E8,w_text,350);
								if(w_text[0]!=0)
								{
									if(ART[i].Marza>atof(w_text)) is_valid=false;
								}

							}

						}
						if(Check_isChecked(CB6) && is_valid)
						{
							memset(w_text,0,350);
							GetWindowText(E6,w_text,350);
							if(w_text[0]!=0)
							{
								if(ART[i].Cena_Netto<atof(w_text)) is_valid=false;
							}
							if(is_valid)
							{
								memset(w_text,0,350);
								GetWindowText(E9,w_text,350);
								if(w_text[0]!=0)
								{
									if(ART[i].Cena_Netto>atof(w_text)) is_valid=false;
								}

							}

						}
						if(Check_isChecked(CB7) && is_valid)
						{
							memset(w_text,0,350);
							GetWindowText(E10,w_text,350);
							if(w_text[0]!=0)
							{
								if(ART[i].VAT!=atoi(w_text)) is_valid=false;
							}
						}
						if(Check_isChecked(CB8) && is_valid)
						{
							memset(w_text,0,350);
							GetWindowText(E11,w_text,350);
							if(w_text[0]!=0)
							{
								if(ART[i].Cena_Brutto<atof(w_text)) is_valid=false;
							}
							if(is_valid)
							{
								memset(w_text,0,350);
								GetWindowText(E12,w_text,350);
								if(w_text[0]!=0)
								{
									if(ART[i].Cena_Brutto>atof(w_text)) is_valid=false;
								}

							}

						}
						if(Check_isChecked(CB9) && is_valid)
						{
							memset(w_text,0,350);
							GetWindowText(E13,w_text,350);
							if(w_text[0]!=0)
							{
								if(ART[i].Stan_Kr<atof(w_text)) is_valid=false;
							}
							if(is_valid)
							{
								memset(w_text,0,350);
								GetWindowText(E14,w_text,350);
								if(w_text[0]!=0)
								{
									if(ART[i].Stan_Kr>atof(w_text)) is_valid=false;
								}

							}

						}
						if(Check_isChecked(CB10) && is_valid)
						{
							memset(w_text,0,350);
							GetWindowText(E16,w_text,350);
							if(w_text[0]!=0)
							{
								if((strncmp(w_text,ART[i].KOD_TOW,strlen(w_text))!=0)&&(strncmp(w_text,ART[i].KOD_KR,strlen(w_text))!=0))
								is_valid=false;
							}
						}

						if(is_valid)
						{
							lvi.mask=LVIF_TEXT;
							lvi.iSubItem=0;
							lvi.iItem=i2;
							lvi.cchTextMax=sizeof(Artykuly);
							lvi.pszText=ART[i].Nazwa; 
							A_id[ListView_InsertItem(LV1,&lvi)]=i;

							for(i1=1;i1<13;i1++)
							{
								memset(w_text,0,350);
								LPS=w_text;
								if(i1==1)LPS=ART[i].Producent;else if(i1==2)dbl_str(ART[i].Stan,LPS,2,350);else if(i1==3)LPS=ART[i].JM;else if(i1==4)
								{
									memset(w_text,0,350);
									dbl_str(ART[i].Cena_Zakupu,w_text,2,350);
									strcpy(w_text+strlen(w_text)," ");
									strcpy(w_text+strlen(w_text),wal[cnt.def_wal].znak);
								}else 
									if(i1==5)dbl_str(ART[i].Marza,LPS,2,350); else if(i1==6) 
									{
										memset(w_text,0,350);
										dbl_str(ART[i].Cena_Netto,w_text,2,350);
										strcpy(w_text+strlen(w_text)," ");
										strcpy(w_text+strlen(w_text),wal[cnt.def_wal].znak);

									}else 
										if(i1==7) dbl_str(ART[i].VAT,LPS,2,350); else
										if(i1==8) 
										{
											memset(w_text,0,350);
											dbl_str(ART[i].Cena_Brutto,w_text,2,350);
											strcpy(w_text+strlen(w_text)," ");
											strcpy(w_text+strlen(w_text),wal[cnt.def_wal].znak); 
										}else 
											if(i1==9) dbl_str(ART[i].Stan_Kr,LPS,2,350); else 
												if(i1==10) LPS=ART[i].KOD_TOW;else
													if(i1==11)LPS=ART[i].KOD_KR;else
														if(i1==12)LPS=ART[i].Num_Fakt;
									ListView_SetItemText(LV1,i2,i1,LPS);
								}
								i2++;
							}
						
						}
					break;
				}
			break;
		}
		default:
			{
				return DefWindowProc(hwd,code,wp,lp);

			}
	}
				
	return 0;
}





int WINAPI WinMain(HINSTANCE hinst,HINSTANCE prev,LPSTR cmdstr,int cmdshow)

{

	
	HMODULE hlib;
	void (*pf)(char*);
	bool (*pget_zap)(FORM_ZAP*);
	bool (*pget_wal)(WALUTA*);
	bool (*get_count)(COUNT*);
	bool (*pget_vat)(ST_VAT*);
	bool (*pget_jm)(JM*);
	bool (*pget_nv)(N_VAT*);
	bool (*pget_gr)(GR_T*);
	bool (*pget_hda)(Header_A*);
	bool (*pget_art)(Artykuly*);
	int i;
	bool bl;
	bool is_sel;

	is_param=false;
	hst=hinst;
	funkcja=false;	
	stv=NULL;
	gr_t=NULL;
	jmt=NULL;

	hlib=LoadLibraryA("DBA.dll");
	if(hlib==NULL)
	{
		memset(Err_Text,0,150);
		sprintf(Err_Text,"Nie mo¿na za³adowaæ biblioteki 'DBA.dll'\n Prawdopodobnie biblioteka uleg³a uszkodzeniu lub usuniêciu\nSkontaktuj siê z wydawc¹ oprogramowania");
		DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),NULL,(DLGPROC)&DLGERRProc);
		return 0;

	}
	pget_hda=(bool (*)(Header_A*))GetProcAddress(hlib,"get_hd");
	pget_art=(bool (*)(Artykuly*))GetProcAddress(hlib,"get_art");
	if(pget_hda==NULL || pget_art==NULL)
	{
		memset(Err_Text,0,150);
		sprintf(Err_Text,"Nie mo¿na za³adowæ funkcji biblioteki 'DBA.dll'\nPrawdopodobnie bilbioteka uleg³a uszkodzeniu\n Skontaktuj siê z wydawc¹ oprogramowania");
		DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),NULL,(DLGPROC)&DLGERRProc);
		return 0;
	}
	if(!(*pget_hda)(&HD_A))
	{
		memset(Err_Text,0,150);
		sprintf(Err_Text,"Nie mo¿na za³adowæ danych z biblioteki 'DBA.dll'\nPrawdopodobnie bilbioteka uleg³a uszkodzeniu\n Skontaktuj siê z wydawc¹ oprogramowania");
		DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),NULL,(DLGPROC)&DLGERRProc);
		return 0;
	}
	if(HD_A.count+Grow>100000)
	{
		Count_A=100000;
	}else
	Count_A=HD_A.count+Grow;
	ART=new Artykuly[Count_A];

	if(!(*pget_art)(ART))
	{
		memset(Err_Text,0,150);
		sprintf(Err_Text,"Nie mo¿na za³adowæ danych z biblioteki 'DBA.dll'\nPrawdopodobnie bilbioteka uleg³a uszkodzeniu\n Skontaktuj siê z wydawc¹ oprogramowania");
		DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),NULL,(DLGPROC)&DLGERRProc);
		return 0;
	}
	FreeLibrary(hlib);
	/*
	Header_A HD_A1;
	int Count_A1;
	bool (*pget_art1)(Artykuly1*);
	hlib=LoadLibraryA("DBA1.dll");

	pget_hda=(bool (*)(Header_A*))GetProcAddress(hlib,"get_hd");
	pget_art1=(bool (*)(Artykuly1*))GetProcAddress(hlib,"get_art");

	if(!(*pget_hda)(&HD_A1))
	{
		memset(Err_Text,0,150);
		sprintf(Err_Text,"Nie mo¿na za³adowæ danych z biblioteki 'DBA.dll'\nPrawdopodobnie bilbioteka uleg³a uszkodzeniu\n Skontaktuj siê z wydawc¹ oprogramowania");
		DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),NULL,(DLGPROC)&DLGERRProc);
		return 0;
	}
	if(HD_A1.count+Grow>100000)
	{
		Count_A1=100000;
	}else
	Count_A1=HD_A1.count+Grow;
	Artykuly1 *ART11;
	ART11=new Artykuly1[Count_A1];

	if(!(*pget_art1)(ART11))
	{
		memset(Err_Text,0,150);
		sprintf(Err_Text,"Nie mo¿na za³adowæ danych z biblioteki 'DBA.dll'\nPrawdopodobnie bilbioteka uleg³a uszkodzeniu\n Skontaktuj siê z wydawc¹ oprogramowania");
		DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),NULL,(DLGPROC)&DLGERRProc);
		return 0;
	}
	FreeLibrary(hlib);
	Artykuly ART1;

	for(i=0;i<HD_A1.count;i++)
	{
		memset((char*)&ART1,0,sizeof(Artykuly));
		ART1.Cena_Brutto=ART11[i].Cena_Brutto;
		ART1.Cena_Netto=ART11[i].Cena_Netto;
		ART1.Cena_Zakupu=ART11[i].Cena_Zakupu;
		ART1.exist=ART11[i].exist;
		strcpy(ART1.Grupa,ART11[i].Grupa);
		ART1.IDA=ART11[i].IDA;
		ART1.IDP=ART11[i].IDP;
		ART1.indeks=ART11[i].indeks;
		ART1.is_blok=ART11[i].is_blok;
		ART1.is_cena=ART11[i].is_cena;
		ART1.is_list=ART11[i].is_list;
		ART1.is_op=ART11[i].is_op;
		ART1.is_wylznr=ART11[i].is_wylznr;
		strcpy(ART1.JM,ART11[i].JM);
		strcpy(ART1.KOD_KR,ART11[i].KOD_KR);
		strcpy(ART1.KOD_TOW,ART11[i].KOD_TOW);
		ART1.Marza=ART11[i].Marza;
		strcpy(ART1.Nazwa,ART11[i].Nazwa);
		strcpy(ART1.Producent,ART11[i].Producent);
		ART1.Stan=ART11[i].Stan;
		ART1.Stan_Kr=ART11[i].Stan_Kr;
		ART1.VAT=ART11[i].VAT;
		Dodaj_AR(&ART1);
	}
	return 0;
	*/

	hlib=LoadLibraryA("attr_kon.dll");
	if(hlib==NULL)
	{
		memset(Err_Text,0,150);
		sprintf(Err_Text,"Nie mo¿na za³adowaæ biblioteki 'attr_kon.dll'\n Prawdopodobnie biblioteka uleg³a uszkodzeniu lub usuniêciu\nSkontaktuj siê z wydawc¹ oprogramowania");
		DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),NULL,(DLGPROC)&DLGERRProc);
		return 0;

	}
	pget_zap= (bool (*)(FORM_ZAP*))GetProcAddress(hlib,"get_formzap");
	pget_wal= (bool (*)(WALUTA*))GetProcAddress(hlib,"get_wal");
	get_count= (bool(*)(COUNT*))GetProcAddress(hlib,"wal_cnt");
	pget_vat= (bool(*)(ST_VAT*))GetProcAddress(hlib,"get_vat");
	pget_jm= (bool(*)(JM*))GetProcAddress(hlib,"get_jm");
	pget_nv= (bool(*)(N_VAT*))GetProcAddress(hlib,"get_NV");
	pget_gr= (bool(*)(GR_T*))GetProcAddress(hlib,"get_gr");

	if(pget_zap==NULL || pget_wal==NULL || get_count==NULL || pget_vat==NULL || pget_jm==NULL || pget_nv==NULL || pget_gr==NULL)
	{
		memset(Err_Text,0,150);
		sprintf(Err_Text,"Nie mo¿na za³adowæ funkcji biblioteki 'attr_kon.dll'\nPrawdopodobnie bilbioteka uleg³a uszkodzeniu\n Skontaktuj siê z wydawc¹ oprogramowania");
		DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),NULL,(DLGPROC)&DLGERRProc);
		return 0;
	}
	for(i=0;i<99;i++)Vat[i].vat=-1;
	i=sizeof(N_VAT);
	if(!((*pget_wal)(wal)) || !((*pget_zap)(form_zap)) || !((*get_count)(&cnt)) || !((*pget_vat)(Vat)) || !((*pget_jm)(jm)) || !((*pget_nv)(&NV)) || !((*pget_gr)(GR)))
	{
		memset(Err_Text,0,150);
		sprintf(Err_Text,"Nie mo¿na za³adowæ danych z biblioteki 'attr_kon.dll'\nPrawdopodobnie bilbioteka uleg³a uszkodzeniu\n Skontaktuj siê z wydawc¹ oprogramowania");
		DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),NULL,(DLGPROC)&DLGERRProc);
		return 0;
	}
	
	FreeLibrary(hlib);


	hlib=LoadLibraryA("DAM.dll");
	if(hlib==NULL)
	{
		memset(Err_Text,0,150);
		sprintf(Err_Text,"Nie mo¿na za³adowaæ biblioteki 'DAM.dll'\n Prawdopodobnie biblioteka uleg³a uszkodzeniu lub usuniêciu\nSkontaktuj siê z wydawc¹ oprogramowania");
		DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),NULL,(DLGPROC)&DLGERRProc);
		return 0;
	}
	pf=(void(*)(char*))GetProcAddress(hlib,"get_Firma");
	if(pf==NULL)
	{
		memset(Err_Text,0,150);
		sprintf(Err_Text,"Nie mo¿na za³adowæ funkcji biblioteki 'DAM.dll'\nPrawdopodobnie bilbioteka uleg³a uszkodzeniu\n Skontaktuj siê z wydawc¹ oprogramowania");
		DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),NULL,(DLGPROC)&DLGERRProc);
		return 0;
	}
	(*pf)((char*)&FRM);
	FreeLibrary(hlib);

	InitCommonControls();
	WNDCLASSEX wnd={sizeof(WNDCLASSEX),CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS,(WNDPROC)&DlgProc,0,0,hinst,LoadIcon(hinst,MAKEINTRESOURCE(IDI_1)),NULL,CreateSolidBrush(0xF4D1CA),wnd.lpszMenuName=MAKEINTRESOURCE(IDM),"Main_Class"};
	wnd1.hbrBackground=CreateSolidBrush(0xF4D1CA);
	wnd1.hInstance=hinst;
	RegisterClassEx(&wnd);
	RegisterClassEx(&wnd1);
	cx=GetSystemMetrics(SM_CXSCREEN);
	cy=GetSystemMetrics(SM_CYSCREEN);
	my=GetSystemMetrics(SM_CYMENU);
	sy=GetSystemMetrics(SM_CYVSCROLL);
	//if(cx<1024)cx=1024;
	//if(cy<768)cy=768;
	MainWnd=CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,"Main_Class","DataBaseArticleMenager",WS_VISIBLE|WS_CLIPCHILDREN|WS_OVERLAPPEDWINDOW,0,0,MAX_X,MAX_Y,0,NULL,hinst,0);	
	LProc=false;
	i=Init_Proc();
	if(i==-1)
	{
		memset(Err_Text,0,150);
		sprintf(Err_Text,"Nie mo¿na za³adowaæ biblioteki WinIP.dll, która jest potrzebna do komunikacji z kas¹ fiskaln¹");
		DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),MainWnd,(DLGPROC)&DLGERRProc);
	}else
		if(i==0)
		{
			memset(Err_Text,0,150);
			sprintf(Err_Text,"Nie mo¿na za³adowaæ wszystkich funkcji z biblioteki WinIP.dll\n Komunikacja z kas¹ mo¿e nie dza³aæ poprawnie");
			DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),MainWnd,(DLGPROC)&DLGERRProc);
		}else LProc=true;
	i=Init_KS();
	if(i==-1)
	{
		memset(Err_Text,0,150);
		sprintf(Err_Text,"Nie mo¿na za³adowaæ biblioteki fisk.dll, która jest potrzebna do komunikacji z kas¹ fiskaln¹");
		DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),MainWnd,(DLGPROC)&DLGERRProc);
	}else
		if(i==0)
		{
			memset(Err_Text,0,150);
			sprintf(Err_Text,"Nie mo¿na za³adowaæ wszystkich funkcji z biblioteki fisk.dll\n Komunikacja z kas¹ mo¿e nie dza³aæ poprawnie");
			DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),MainWnd,(DLGPROC)&DLGERRProc);
		}

	if(!Init_Base()) 
	{
		memset(Err_Text,0,150);
		sprintf(Err_Text,"Podczas ³adowania plików bazy danych napotkano b³¹d\n Prawdopodobnie któryœ z plików ukleg³ uszkodzeniu\n Aplikacja mo¿e dzia³aæ niepoprawnie");
		DialogBox(hst,MAKEINTRESOURCE(DLG_ERR),NULL,(DLGPROC)&DLGERRProc);
	}
	Create_Controls(MainWnd);
	UpdateWindow(MainWnd);
	ShowWindow(MainWnd,SW_SHOWNORMAL);
	is_sel=false;

	while(GetMessage(&msg,NULL,0,0))
	{
		if(!IsDialogMessage(DLG26,&msg))
		{
			if(msg.hwnd==Panel)
			{	
				if(is_sel)
				{
					is_sel=false;
					SendMessage(MainWnd,WM_COMMAND,(WPARAM)Panel,0);
				}

				else
				if(msg.message==WM_LBUTTONDOWN)
				{
					is_sel=true;
				}
			
			
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
	
		}
	}
	
	return 0;
}
