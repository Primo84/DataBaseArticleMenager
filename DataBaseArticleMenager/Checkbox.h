
#include "Windows.h"
#include "tchar.h";



typedef struct m_point
{
	WORD x;
	WORD y;
}MPOINT;

bool bl;

void Check_SetHoverColor(HWND hwd,DWORD color)
{
	SendMessage(hwd,WM_USER+14,0,(LPARAM)color);

}

void Check_SetBkg(HWND hwd,DWORD color)
{
	SendMessage(hwd,WM_USER+10,0,(LPARAM)color);

}

bool Check_isChecked(HWND hwd)
{
	SendMessage(hwd,WM_USER+12,0,(LPARAM)&bl);
	return bl;
}

void Check_SetChkColor(HWND hwd,DWORD color)
{
	SendMessage(hwd,WM_USER+11,0,(LPARAM)color);

}
void Check_check(HWND hwd,bool bl)
{
	SendMessage(hwd,WM_USER+13,0,(LPARAM)bl);
}



LRESULT _stdcall DlgBProc (HWND hwd, int code, WPARAM wp , LPARAM lp);



WNDCLASSEX wnd1={sizeof(WNDCLASSEX),CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS,(WNDPROC)DlgBProc,0,0,0,NULL,NULL,CreateSolidBrush(COLOR_WINDOW),NULL,"Check"};

LRESULT  _stdcall DlgBProc (HWND hwd, int code, WPARAM wp , LPARAM lp)
{
	HDC hdc;
	RECT wrc,crc;
	int cwidth,cheight,rx,ry,r_wh;
	HBRUSH hbr;
	HPEN hpn;
	PAINTSTRUCT pnt;
	char *w_txt;
	DWORD bk_color;
	DWORD chk_color;
	DWORD hov_color;
	DWORD pos;
	MPOINT *pt;
	POINT p;
	char W_Text[250];
	bool is_checked;
	bool is_lmdown;
	bool bl;
	HWND hwnd;

	switch(code)
	{
		case WM_CLOSE:
			{
				DestroyWindow(hwd);
				break;
			}
		case WM_CREATE:
			{
				SetProp(hwd,"is_lmdown",(HANDLE)false);
				SetProp(hwd,"bk_color",(HANDLE)-1);
				SetProp(hwd,"chk_color",(HANDLE)0);
				SetProp(hwd,"is_checked",(HANDLE)false);
				SetProp(hwd,"hov_color",(HANDLE)-1);
				SetProp(hwd,"is_hov",(HANDLE)false);
				w_txt=new char[250];
				memset(w_txt,0,250);
				GetWindowText(hwd,w_txt,250);
				bl=SetProp(hwd,"W_Text",(HANDLE)w_txt);
			break;
			}
		case WM_MOUSEMOVE:
			{
				hwnd=GetCapture();
				if(hwnd==NULL) SetCapture(hwd);
				GetWindowRect(hwd,&crc);
				//rx=crc.right-crc.left;
				//ry=crc.bottom-crc.top;
				pos=GetMessagePos();
				pt=(MPOINT*)&pos;
				p.x=(LONG)pt->x;
				p.y=(LONG)pt->y;
				//ScreenToClient(hwd,&p);
				if((p.x<crc.left+4)||(p.y<crc.top+4)||(p.x>crc.right-4)||(p.y>crc.bottom-4))
				{
					hwnd=GetCapture();
					ReleaseCapture();
					bl=GetProp(hwd,"is_hov");
					if(bl)
					{
						SetProp(hwd,"is_hov",(HANDLE)false);
						ShowWindow(hwd,SW_HIDE);
						ShowWindow(hwd,SW_NORMAL);
					}
					break;
				}
				bl=(bool)GetProp(hwd,"is_hov");
				if(!bl)
				{
					SetProp(hwd,"is_hov",(HANDLE)true);
					ShowWindow(hwd,SW_HIDE);
					ShowWindow(hwd,SW_NORMAL);
				}
				//RedrawWindow(hwd,NULL,NULL,RDW_INVALIDATE|RDW_ERASE);
				break;
			}
		
		case WM_LBUTTONDOWN:
			{
				SetProp(hwd,"is_lmdown",(HANDLE)true);
				RedrawWindow(hwd,NULL,NULL,RDW_INVALIDATE|RDW_ERASENOW);
				break;
			}
		case WM_LBUTTONUP:
			{
				is_checked=(bool)GetProp(hwd,"is_checked");
				is_checked=!is_checked;
				SetProp(hwd,"is_checked",(HANDLE)is_checked);
				SetProp(hwd,"is_lmdown",(HANDLE)false);
				RedrawWindow(hwd,NULL,NULL,RDW_INVALIDATE|RDW_ERASENOW);
				SendMessage(GetParent(hwd),WM_COMMAND,(WPARAM)hwd,0);
				break;
			}
		case WM_SETTEXT:
			{
				memset(W_Text,0,250);
				strcpy(W_Text,(char*)lp);
				SetProp(hwd,"W_Text",(HANDLE)W_Text);
				ShowWindow(hwd,SW_HIDE);
				ShowWindow(hwd,SW_NORMAL);
				break;
			}
		case WM_USER+10:
			{
				bk_color=(DWORD)lp;
				SetProp(hwd,"bk_color",(HANDLE)bk_color);
				ShowWindow(hwd,SW_HIDE);
				ShowWindow(hwd,SW_NORMAL);
			break;
			}
		case WM_USER+11:
			{
				chk_color=(DWORD)lp;
				SetProp(hwd,"chk_color",(HANDLE)chk_color);
				ShowWindow(hwd,SW_HIDE);
				ShowWindow(hwd,SW_NORMAL);
			break;
			}
			case WM_USER+12:
			{
				is_checked=(bool)GetProp(hwd,"is_checked");
				*((bool*)lp)=is_checked;
				break;
			}
			case WM_USER+13:
			{
				is_checked=(bool)lp;
				SetProp(hwd,"is_checked",(HANDLE)is_checked);
				RedrawWindow(hwd,NULL,NULL,RDW_INVALIDATE|RDW_ERASENOW);
				break;
			}
			case WM_USER+14:
			{
				hov_color=(DWORD)lp;
				SetProp(hwd,"hov_color",(HANDLE)hov_color);
				ShowWindow(hwd,SW_HIDE);
				ShowWindow(hwd,SW_NORMAL);
			break;
			}
		case WM_ERASEBKGND:
			{
				bl=(bool)GetProp(hwd,"is_hov"); 
				if(!bl)bk_color=(DWORD)GetProp(hwd,"bk_color"); else
					bk_color=(DWORD)GetProp(hwd,"hov_color");
				if(bk_color==-1) return DefWindowProc(hwd,code,wp,lp);
				//GetWindowRect(hwd,&wrc);
				GetClientRect(hwd,&crc);
				hdc=BeginPaint(hwd,&pnt);
				hbr=CreateSolidBrush((COLORREF)bk_color);
				hpn=CreatePen(PS_SOLID,5,(COLORREF)bk_color);
				SelectObject(hdc,(HGDIOBJ)hbr);
				Rectangle(hdc,0,0,crc.right-1,crc.bottom-1);
				SelectObject(hdc,(HGDIOBJ)hpn);
				Rectangle(hdc,0,0,crc.right,crc.bottom);
				DeleteObject((HGDIOBJ)hbr);
				DeleteDC(hdc);
				EndPaint(hwd,&pnt);
				RedrawWindow(hwd,NULL,NULL,RDW_UPDATENOW|RDW_INVALIDATE);
				break;
			}
		case WM_PAINT:
			
			{
				hdc=BeginPaint(hwd,&pnt);
				bl=(bool)GetProp(hwd,"is_hov"); 
				if(!bl)bk_color=(DWORD)GetProp(hwd,"bk_color"); else
					bk_color=(DWORD)GetProp(hwd,"hov_color");
				//bk_color=(DWORD)GetProp(hwd,"bk_color");
				if(bk_color==-1)
				{
					bk_color=GetPixel(hdc,1,1);
					SetProp(hwd,"bk_color",(HANDLE)bk_color);
				}
				GetClientRect(hwd,&crc);
				cwidth=crc.right-crc.left;
				cheight=crc.bottom-crc.top;
				ry=cheight/2;
				ry=ry-8;
				r_wh=16;
				rx=5;
				is_lmdown=(bool)GetProp(hwd,"is_lmdown");
				if(is_lmdown)hbr=CreateSolidBrush((COLORREF)0xcccccc); else
				hbr=CreateSolidBrush((COLORREF)0xffffff);
				SelectObject(hdc,(HGDIOBJ)hbr);
				Rectangle(hdc,rx,ry,rx+r_wh,ry+r_wh);
				DeleteObject((HGDIOBJ)hbr);
				is_checked=(bool)GetProp(hwd,"is_checked");
				if(is_checked)
				{
					chk_color=(DWORD)GetProp(hwd,"chk_color");
					hpn=CreatePen(PS_SOLID,3,(COLORREF)chk_color);
					SelectObject(hdc,(HGDIOBJ)hpn);
					MoveToEx(hdc,rx+2,ry+2,NULL);
					LineTo(hdc,rx+8,ry+14);
					LineTo(hdc,rx+14,ry+2);
					DeleteObject((HGDIOBJ)hpn);

				}
				w_txt=(char*)GetProp(hwd,"W_Text");
				if(w_txt[0]!=0);
				{
					SetBkColor(hdc,GetPixel(hdc,rx+17,ry));
					TextOut(hdc,rx+17,ry,w_txt,250);
				}
				DeleteDC(hdc);
				EndPaint(hwd,&pnt);
				//DeleteObject(hpn);
				break;
			
		}
		case WM_DESTROY:
			{
				RemoveProp(hwd,"is_lmdown");
				RemoveProp(hwd,"bk_color");
				RemoveProp(hwd,"chk_color");
				RemoveProp(hwd,"is_checked");
				w_txt=(char*)RemoveProp(hwd,"W_Text");
				if(w_txt!=NULL)delete w_txt;
				break;
			}
		default: 
			{
				
				return DefWindowProc(hwd,code,wp,lp);
								
			}
	}
	return 0;
}



