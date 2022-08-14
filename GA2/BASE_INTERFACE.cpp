// BASE_INTERFACE.cpp : implementation file
//

#include "stdafx.h"
#include "GA2.h"
#include "BASE_INTERFACE.h"
#include "afxdialogex.h"
#include <iostream>
#include <fstream>
#include "ColorListBox.h"

// BASE_INTERFACE dialog

IMPLEMENT_DYNAMIC(BASE_INTERFACE, CDialogEx)

BASE_INTERFACE::BASE_INTERFACE(XmlFeed* XmlF, BI_BET* B_I,bet* pB,CWnd* pParent)
	: CDialogEx(BASE_INTERFACE::IDD, pParent)
	, filtr_new1(TRUE)
	, filtr_new2(TRUE)
	, filtr_old2(TRUE)
	, filtr_old1(TRUE)
	, RB_VToo(FALSE)
	, cs_ATN(_T(""))
{
	BASE_I=B_I;
	XF=XmlF;
	ALL_SPORTS=new BI_BET*[pB->n_sport];
	*ALL_SPORTS=BASE_I;//SOCCER (POXEL SPORTADEVERI AVELACMAN JAMANAK)!!!!!!
	for(int i=1;i<pB->n_sport;i++) *ALL_SPORTS=NULL;
	PB=pB;
	CH_BASE=pB->cham_names;
	T_BASE=pB->team_names;
	IDS=new int[6];
	POSB=new int[2];
	NAMEB=new char*[6];
	AT_ON=true;
	
}

BASE_INTERFACE::~BASE_INTERFACE()
{
}

void BASE_INTERFACE::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO2, combo_b1);
	DDX_Control(pDX, IDC_COMBO4, combo_b2);

	DDX_Control(pDX, IDC_COMBO1, combo_DA1);
	DDX_Control(pDX, IDC_COMBO3, combo_DA2);
	DDX_Control(pDX, IDC_LIST1, LB1);
	DDX_Check(pDX, IDC_CHECK1, filtr_new1);
	DDX_Check(pDX, IDC_CHECK3, filtr_new2);
	DDX_Check(pDX, IDC_CHECK4, filtr_old2);
	DDX_Check(pDX, IDC_CHECK2, filtr_old1);
	DDX_Control(pDX, IDC_LIST2, LB2);
	DDX_Control(pDX, IDC_LIST3, listc1);
	DDX_Control(pDX, IDC_LIST4, listc2);
	DDX_Control(pDX, IDC_COMBO5, combo_s);
	DDX_Radio(pDX, IDC_RADIO1, RB_VToo);

	DDX_Control(pDX, IDC_RADIO1, r1);
	DDX_Control(pDX, IDC_RADIO3, rg1_1);
	DDX_Control(pDX, IDC_RADIO4, rg1_2);
	//	DDX_Control(pDX, IDC_RADIO5, rg2_1);
	//	DDX_Control(pDX, IDC_RADIO6, rg2_2);
	DDX_Control(pDX, IDC_BUTTON8, butt_ATN);
	DDX_Control(pDX, IDC_EDIT1, edit_ATN);
	DDX_Control(pDX, IDC_CHECK4, butt_OLD);
	DDX_Control(pDX, IDC_CHECK3, butt_NEW);
	DDX_Text(pDX, IDC_EDIT1, cs_ATN);
	/*DDX_Control(pDX, IDC_RADIO7, r_gt1);
	DDX_Control(pDX, IDC_RADIO8, r_gt2);
	DDX_Control(pDX, IDC_STATIC1, s_gt1);
	DDX_Control(pDX, IDC_STATIC2, s_gt2);*/
	DDX_Control(pDX, IDC_BUTTON3, b_gp);
	DDX_Control(pDX, IDC_BUTTON4, b_gm);
	DDX_Control(pDX, IDC_BUTTON6, b_gt1);
	DDX_Control(pDX, IDC_BUTTON7, b_gt2);
}


BEGIN_MESSAGE_MAP(BASE_INTERFACE, CDialogEx)
	ON_CBN_SELENDOK(IDC_COMBO2, &BASE_INTERFACE::OnCbnSelendokCombo2)
	ON_CBN_SELENDOK(IDC_COMBO4, &BASE_INTERFACE::OnCbnSelendokCombo4)
	ON_BN_CLICKED(IDC_CHECK1, &BASE_INTERFACE::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &BASE_INTERFACE::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &BASE_INTERFACE::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &BASE_INTERFACE::OnBnClickedCheck4)
	ON_LBN_SELCHANGE(IDC_LIST1, &BASE_INTERFACE::OnLbnSelchangeList1)
//	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST3, &BASE_INTERFACE::OnLvnItemchangedList3)
	ON_LBN_SELCHANGE(IDC_LIST2, &BASE_INTERFACE::OnLbnSelchangeList2)
	ON_BN_CLICKED(IDC_BUTTON1, &BASE_INTERFACE::OnBnClickedButton1)
//	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST4, &BASE_INTERFACE::OnLvnItemchangedList4)
	ON_CBN_SELCHANGE(IDC_COMBO2, &BASE_INTERFACE::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDOK, &BASE_INTERFACE::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO1, &BASE_INTERFACE::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &BASE_INTERFACE::OnBnClickedRadio2)
	ON_NOTIFY(NM_CLICK, IDC_LIST3, &BASE_INTERFACE::OnNMClickList3)
	ON_NOTIFY(NM_CLICK, IDC_LIST4, &BASE_INTERFACE::OnNMClickList4)
	ON_CBN_SELCHANGE(IDC_COMBO4, &BASE_INTERFACE::OnCbnSelchangeCombo4)
	ON_BN_CLICKED(IDC_BUTTON5, &BASE_INTERFACE::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON8, &BASE_INTERFACE::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON6, &BASE_INTERFACE::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &BASE_INTERFACE::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON3, &BASE_INTERFACE::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &BASE_INTERFACE::OnBnClickedButton4)
END_MESSAGE_MAP()


// BASE_INTERFACE message handlers


void BASE_INTERFACE::OnCbnSelendokCombo2()
{
	// TODO: Add your control notification handler code here
	ADD_ListBox(true);
}

void BASE_INTERFACE::ADD_ListBox(bool OneTwo)
{
	CColorListBox* LB;
	CString ID_CH12;
	bool Filtr_new;
	bool Filtr_old;
	int combo_pos;
	UpdateData();
	if(OneTwo)//true=1 or false=2
	{
		combo_pos=combo_b1.GetCurSel();
		B_1=BASE_I+combo_pos;
		LB=&LB1;
		Filtr_new=1&filtr_new1;
		Filtr_old=1&filtr_old1;
	}
	else//2
	{
		combo_pos=combo_b2.GetCurSel();
		B_2=BASE_I+combo_pos;
		LB=&LB2;
		Filtr_new=1&filtr_new2;
		Filtr_old=1&filtr_old2;
	}
	
	LB->ResetContent();
	BI_CH* TEMP_CH;
	for(int i=0;i<2;i++)
	{
		if(!i){ if(Filtr_new)	TEMP_CH=(BASE_I+combo_pos)->CHS_ZERO;}
		else  if(Filtr_old)		TEMP_CH=(BASE_I+combo_pos)->CHS;
		for(;TEMP_CH;TEMP_CH=TEMP_CH->next)
		{
			//if(i)LB->AddString(CString(TEMP_CH->NAME_CH),RGB(10,10,255));
			
			if(i)
			{
				ID_CH12.Format(L"%02i",TEMP_CH->ID_CH);
				ID_CH12=L"["+ID_CH12+L"] "+CString(TEMP_CH->NAME_CH);
				LB->AddString(ID_CH12);
			}
			else LB->AddString(CString(TEMP_CH->NAME_CH));
		}
	}
}

//***********FILTR NEW AND OLD**************************
void BASE_INTERFACE::OnCbnSelendokCombo4()
{
	// TODO: Add your control notification handler code here
	ADD_ListBox(false);
}
void BASE_INTERFACE::OnBnClickedCheck1()
{
	// TODO: Add your control notification handler code here
	if(combo_b1.GetCurSel()!=-1) ADD_ListBox(true);
}
void BASE_INTERFACE::OnBnClickedCheck2()
{
	// TODO: Add your control notification handler code here
	if(combo_b1.GetCurSel()!=-1) ADD_ListBox(true);
}
void BASE_INTERFACE::OnBnClickedCheck3()
{
	// TODO: Add your control notification handler code here
	if(combo_b2.GetCurSel()!=-1) ADD_ListBox(false);
}
void BASE_INTERFACE::OnBnClickedCheck4()
{
	// TODO: Add your control notification handler code here
	if(combo_b2.GetCurSel()!=-1) ADD_ListBox(false);
}
//******************************************************

void BASE_INTERFACE::OnLbnSelchangeList1()
{
	// TODO: Add your control notification handler code here
	ADD_ListCtrl(true);
}
void BASE_INTERFACE::OnLbnSelchangeList2()
{
	// TODO: Add your control notification handler code here
	ADD_ListCtrl(false);
}

//void BASE_INTERFACE::OnLvnItemchangedList3(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
//	// TODO: Add your control notification handler code here
//	*pResult = 0;
//	
//	
//}

//void BASE_INTERFACE::OnLvnItemchangedList4(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
//	// TODO: Add your control notification handler code here
//	*pResult = 0;
//
//}

void BASE_INTERFACE::_SetTeamID(CString T1, CString T2, CString GD, bool OneTwo)
{
	BI_G* TempG;
	if(OneTwo) TempG=CH_1->GAMES;
	else TempG=CH_2->GAMES;
	CString D, ID_T12;
	CString Team1;
	CString Team2;
	for(BI_G* T=TempG;T;T=T->next)
	{
		ID_T12.Format(L"%02i",T->ID_T1);
		if(T->ID_T1) Team1=L"["+ID_T12+L"] "+CString(T->NAME_T1);
		else Team1=CString(T->NAME_T1);
		ID_T12.Format(L"%02i",T->ID_T2);
		if(T->ID_T2) Team2=L"["+ID_T12+L"] "+CString(T->NAME_T2);
		else Team2=CString(T->NAME_T2);

		if(Team1==T1 && Team2==T2)
		{
			int* GT=T->DATE_GAME;
			D.Format(L"%02i:%02i %i.%02i.%02i",*(GT+3), *(GT+4),*GT,*(GT+1),*(GT+2));
			if(D==GD)
			{
				if(OneTwo)
				{
					G1=T;
					*(IDS+2)=T->ID_T1;
					*(IDS+3)=T->ID_T2;
					*(NAMEB+2)=T->NAME_T1;
					*(NAMEB+3)=T->NAME_T2;
					//////////////////////
					data_T=GT;
					L12=true;
					if(T->ID_T1 && T->ID_T2 && *IDS && PB->GX_TIME_C(GT,-3,0)) ActivateGoal();
					else ActivateGoal(false);
				}
				else
				{
					G2=T;
					*(IDS+4)=T->ID_T1;
					*(IDS+5)=T->ID_T2;
					*(NAMEB+4)=T->NAME_T1;
					*(NAMEB+5)=T->NAME_T2;
					//////////////////////
					data_T=GT;
					L12=false;
					if(T->ID_T1 && T->ID_T2 && *IDS && PB->GX_TIME_C(GT,-3,0)) ActivateGoal();
					else ActivateGoal(false);
				}
				return;
			}
			else continue;
		}
	}

}

void BASE_INTERFACE::ADD_ListCtrl(bool OneTwo)
{
	CString CH_NAME;
	CColorListBox* LB;
	CListCtrl* LCtrl;
	int combo_pos;
	if(OneTwo)//true=1 or false=2
	{
		LB=&LB1;
		LCtrl=&listc1;
		combo_pos=combo_b1.GetCurSel();
	}
	else
	{
		LB=&LB2;
		LCtrl=&listc2;
		combo_pos=combo_b2.GetCurSel();
	}
	LCtrl->DeleteAllItems();
	LB->GetText(LB->GetCurSel(),CH_NAME);
	BI_G* TEMP_G=NULL;
	///////////////////////////////////////////////////////////////////////////
	BI_CH* T_CH;
	for(T_CH=(BASE_I+combo_pos)->CHS_ZERO;T_CH;T_CH=T_CH->next)
	{
		if(CH_NAME==CString(T_CH->NAME_CH)){TEMP_G=T_CH->GAMES;break;}
	}

	if(!TEMP_G)
	{ 
		CString IDch;
		for(T_CH=(BASE_I+combo_pos)->CHS;T_CH;T_CH=T_CH->next)
		{
			IDch.Format(L"%02i",T_CH->ID_CH);
			IDch=L"["+IDch+L"] "+CString(T_CH->NAME_CH);
			if(CH_NAME==IDch){TEMP_G=T_CH->GAMES;break;}
		}
	}

	if(OneTwo)
	{
		CH_1=T_CH;
		*IDS=T_CH->ID_CH;
		*NAMEB=T_CH->NAME_CH;
		*POSB=(BASE_I+combo_pos)->ID_BET_POS;
	}
	else
	{
		CH_2=T_CH;
		*(IDS+1)=T_CH->ID_CH;
		*(NAMEB+1)=T_CH->NAME_CH;
		*(POSB+1)=(BASE_I+combo_pos)->ID_BET_POS;
	}

	///////////////////////////////////////////////////////////////////////////
	LVITEM lv;
	CString NAME, ID_T12;
	int* GT;
	for(int i=0;TEMP_G; i++, TEMP_G=TEMP_G->next)
	{
		GT=TEMP_G->DATE_GAME;
		NAME=CString(TEMP_G->NAME_T1);
		ID_T12.Format(L"%02i",TEMP_G->ID_T1);
		if(TEMP_G->ID_T1) NAME=L"["+ID_T12+L"] "+NAME;
		LCtrl->InsertItem(i,NAME);//Arajin syan lracum
		
		lv.mask=LVIF_TEXT;
		lv.iSubItem=1;//erkrord syun
		lv.iItem=i;
		NAME=CString(TEMP_G->NAME_T2);
		ID_T12.Format(L"%02i",TEMP_G->ID_T2);
		if(TEMP_G->ID_T2) NAME=L"["+ID_T12+L"] "+NAME;
		lv.pszText=(LPTSTR)(LPCTSTR)NAME;
		LCtrl->SetItem(&lv);//Ekrord syan lracum

		lv.iSubItem=2;//errord syun
		CString GDATE;
		GDATE.Format(L"%02i:%02i %i.%02i.%02i",*(GT+3), *(GT+4),*GT,*(GT+1),*(GT+2));
		lv.pszText=(LPTSTR)(LPCTSTR)GDATE;
		LCtrl->SetItem(&lv);//Errord syan lracum
	}
}

void BASE_INTERFACE::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	if(LB1.GetCurSel()==-1 || LB2.GetCurSel()==-1 || listc1.GetFirstSelectedItemPosition()==NULL || listc2.GetFirstSelectedItemPosition()==NULL)
	{
		MessageBox(L"Please select games");
		return;
	}
	int IDN[4];
	char** NS=new char*[4] ;

	*NS=*NAMEB;
	*(NS+1)=*(NAMEB+1);
	for(int i=0;i<2;i++)
	{
		IDN[0]=*IDS;
		IDN[1]=*(IDS+1);
		if(!RB_VToo)
		{
			IDN[2]=*(IDS+2+i);
			IDN[3]=*(IDS+4+i);
			*(NS+2)=*(NAMEB+2+i);
			*(NS+3)=*(NAMEB+4+i);
		}
		else
		{
			IDN[2]=*(IDS+2+i);
			IDN[3]=*(IDS+5-i);
			*(NS+2)=*(NAMEB+2+i);
			*(NS+3)=*(NAMEB+5-i);
		}
		NTeam=(i==0);
		if(AB( (int*)IDN, NS, POSB )) ref_base(!i);
	}

}

bool BASE_INTERFACE::AB(int *ID, char** NAME, int *posB)//Add Base
{
	if(*POSB==*(POSB+1))
	{ 
		if(NTeam)MessageBox(L"Please select other bookmaker\nBET_POS1 == BET_POS2");
		return false;
	}
	static bool vb=true;
	if(vb){ NEWCH=0; vb=false; }
	else vb=true;
	int ID_CH1=*ID;//ID_CH1
	int ID_CH2=*(ID+1);//ID_CH2
	int ID_T1=*(ID+2);//ID_T1
	int ID_T2=*(ID+3);//ID_T2
	
	char* CH_N1=*NAME;//CH_NAME1
	char* CH_N2=*(NAME+1);//CH_NAME2
	char* T_N1=*(NAME+2);//T_NAME1
	char* T_N2=*(NAME+3);//T_NAME2

	int ID_B1=*posB;
	int ID_B2=*(posB+1);
	int ID_SP=combo_s.GetCurSel();//ID SPORT -1 
	const int NCHB=200;
	const int NTB=100;
	if(!*ID && !*(ID+1)) //0 && 0
	{
		cham_base* TCH;
		int ID_CH;
		if(!*(CH_BASE+ID_SP))
		{
			*(CH_BASE+ID_SP)=new cham_base[2];
			(*(CH_BASE+ID_SP)+1)->cham_names=NULL;
			(*(CH_BASE+ID_SP)+1)->id_cham=0;
			(*(CH_BASE+ID_SP))->cham_names=new char[NCHB*(PB->n_bet)];
			for(int i=0;i<PB->n_bet;i++) *((*(CH_BASE+ID_SP))->cham_names+i*NCHB)='\0';
			AddName((*(CH_BASE+ID_SP))->cham_names,NCHB*(ID_B1-1),*NAME);//ADD CH1
			AddName((*(CH_BASE+ID_SP))->cham_names,NCHB*(ID_B2-1),*(NAME+1));//ADD CH2
			ID_CH=(*(CH_BASE+ID_SP))->id_cham=1;
			*IDS=*(IDS+1)=CH_1->ID_CH=CH_2->ID_CH=1;
			NEWCH=3;
			TCH=*(CH_BASE+ID_SP);
		}
		else
		{
			TCH=*(CH_BASE+ID_SP);
			for(int i=0;;i++, TCH++)
			{
				if(!TCH->cham_names)
				{
					cham_base* TEMP=new cham_base[i+2];
					bool d=true;
					for(int j=0;j<=i;j++)
					{
						if((j+1)==(*(CH_BASE+ID_SP)+j)->id_cham && d)
						{
							(TEMP+j)->cham_names=(*(CH_BASE+ID_SP)+j)->cham_names;
							(TEMP+j)->id_cham=(*(CH_BASE+ID_SP)+j)->id_cham;
						}
						else
						{
							if(d)
							{
								(TEMP+j)->cham_names=new char[NCHB*(PB->n_bet)];
								for(int k=0; k<PB->n_bet; k++) *( ((TEMP+j)->cham_names)+k*NCHB )='\0';
								AddName((TEMP+j)->cham_names,NCHB*(ID_B1-1),*NAME);//ADD CH1
								AddName((TEMP+j)->cham_names,NCHB*(ID_B2-1),*(NAME+1));//ADD CH2
								ID_CH=(TEMP+j)->id_cham=CH_1->ID_CH=CH_2->ID_CH=j+1;
								*IDS=*(IDS+1)=j+1;
								d=false;
								continue;
							}
							(TEMP+j)->cham_names=(*(CH_BASE+ID_SP)+j-1)->cham_names;
							(TEMP+j)->id_cham=(*(CH_BASE+ID_SP)+j-1)->id_cham;
						}
					}

					delete [] (*(CH_BASE+ID_SP));
					*(CH_BASE+ID_SP)=TEMP;
					/*(*(CH_BASE+ID_SP)+i)->cham_names=new char[NCHB*(PB->n_bet)];
					for(int k=0; k<PB->n_bet; k++) *( (((*(CH_BASE+ID_SP))+i)->cham_names)+k*NCHB )='\0';
					AddName((*(CH_BASE+ID_SP)+i)->cham_names,NCHB*(ID_B1-1),*NAME);//ADD CH1
					AddName((*(CH_BASE+ID_SP)+i)->cham_names,NCHB*(ID_B2-1),*(NAME+1));//ADD CH2
					ID_CH=(*(CH_BASE+ID_SP)+i)->id_cham=CH_1->ID_CH=CH_2->ID_CH=i+1;
					*IDS=*(IDS+1)=i+1;*/
					NEWCH=3;
					(*(CH_BASE+ID_SP)+i+1)->cham_names=NULL;
					(*(CH_BASE+ID_SP)+i+1)->id_cham=0;
					break;
				}
			}
		}
		//////////////////////////////////////////////////////////////////////////////
		p_t_b* TEMP;
		if(! *(T_BASE+ID_SP))
		{
			TEMP=*(T_BASE+ID_SP)=new p_t_b[2];
			(TEMP+1)->id_cham=0;
			(TEMP+1)->ptr_b=NULL;
		}
		else
		{
			int i=0;
			for( p_t_b* T=*(T_BASE+ID_SP);T->id_cham; i++,T++)
			{
				T->id_cham;
			}
			p_t_b* TT=new p_t_b[i+2];
			for(int j=0;j<i;j++)
			{
				(TT+j)->id_cham=(*(T_BASE+ID_SP)+j)->id_cham;
				(TT+j)->ptr_b=(*(T_BASE+ID_SP)+j)->ptr_b;
			}
			//for(int j=0;j<i;j++) delete (*(T_BASE+ID_SP)+j);
			delete [] (*(T_BASE+ID_SP));
			*(T_BASE+ID_SP)=TT;
			TEMP=(TT+i);
			(TT+i+1)->id_cham=0;
			(TT+i+1)->ptr_b=NULL;
		}
		TEMP->id_cham=ID_CH;
		TEMP->ptr_b=NULL;
		_ANTeam(TEMP, (NAME+2), posB);
//------------------------------------------------------------------------------
		for(cham_base* CHB=*(CH_BASE+ID_SP); CHB->id_cham;CHB++)
	{
		int idch=CHB->id_cham;
		char* chNAME[6];
		chNAME[0]=CHB->cham_names;
		chNAME[1]=CHB->cham_names+NCHB;
		chNAME[2]=CHB->cham_names+2*NCHB;
		chNAME[3]=CHB->cham_names+3*NCHB;
		chNAME[4]=CHB->cham_names+4*NCHB;
		chNAME[5]=CHB->cham_names+5*NCHB;
		for(team_base* gb=(*(T_BASE+ID_SP)+idch-1)->ptr_b;gb->id_team;gb++)
		{
			int idg=gb->id_team;
			char* gNAME[6];
			gNAME[0]=gb->team_name;
			gNAME[1]=gb->team_name+NTB;
			gNAME[2]=gb->team_name+2*NTB;
			gNAME[3]=gb->team_name+3*NTB;
			gNAME[4]=gb->team_name+4*NTB;
			gNAME[5]=gb->team_name+5*NTB;
			continue;
		}
	}
//------------------------------------------------------------------------------
		return true;
	}

	if(*ID && *(ID+1) ) //1 && 1 
	{
		if(*ID != *(ID+1)) return false;
		if(*(ID+2) && *(ID+3)){NEWCH=0; return true;}
		if(*(ID+2) | *(ID+3))//0-1 OR 1-0
		{
			_ANTeam( (*(T_BASE+ID_SP)+*ID-1), (NAME+2), posB, (ID+2) );
			//return true;
			//return false;
		}
		else//ID_T1=0 && ID_T2=0
		{
			_ANTeam( (*(T_BASE+ID_SP)+*ID-1), (NAME+2), posB );
		}
		return true;
		
	}
	
	if(*ID | *(ID+1)) //(1 & 0) OR (0 & 1)
	{
		NEWCH=2;
		int IDCHF=*ID;
		int posCH=*(posB+1);
		char* nameCH=*(NAME+1);
		if(! *ID)
		{
			NEWCH=1;
			IDCHF=*(ID+1);
			*ID=*(ID+1);
			posCH=*posB;
			nameCH=*NAME;
		}
		else
		{
			*(ID+1)=*ID;
		}
		CH_1->ID_CH=CH_2->ID_CH=IDCHF;
		//**************************************************
		char* CHname=(*(CH_BASE+ID_SP)+IDCHF-1)->cham_names;
		char hh=*(CHname+NCHB*(posCH-1));
		char* phh=(CHname+NCHB*(posCH-1));
		if( *(CHname+NCHB*(posCH-1))=='\0' )
		{
			AddName( CHname, NCHB*(posCH-1), nameCH);
		}
		else
		{
			cham_base* TCH=*(CH_BASE+ID_SP);
			for(int i=0;;i++, TCH++)
			{
				if(!TCH->cham_names)
				{
					cham_base* TEMP=new cham_base[i+2];
					for(int j=0;j<i;j++)
					{
						(TEMP+j)->cham_names=(*(CH_BASE+ID_SP)+j)->cham_names;
						(TEMP+j)->id_cham=(*(CH_BASE+ID_SP)+j)->id_cham;
					}
					delete [] (*(CH_BASE+ID_SP));
					*(CH_BASE+ID_SP)=TEMP;
					(*(CH_BASE+ID_SP)+i)->cham_names=new char[NCHB*(PB->n_bet)];
					for(int k=0; k<PB->n_bet; k++) *( (((*(CH_BASE+ID_SP))+i)->cham_names)+k*NCHB )='\0';
					AddName((*(CH_BASE+ID_SP)+i)->cham_names,  NCHB*(posCH-1),nameCH);//ADD CH1
					(*(CH_BASE+ID_SP)+i)->id_cham=CH_1->ID_CH=CH_2->ID_CH=IDCHF;
					*IDS=*(IDS+1)=IDCHF;
					//NEWCH=3;
					(*(CH_BASE+ID_SP)+i+1)->cham_names=NULL;
					(*(CH_BASE+ID_SP)+i+1)->id_cham=0;
					break;
				}
			}
		}
		//**************************************************
		/////////////////////////////////////////////////////////////////
		if(!*(ID+2) && !*(ID+3)) _ANTeam( (*(T_BASE+ID_SP)+IDCHF-1), (NAME+2), posB);
		else _ANTeam( (*(T_BASE+ID_SP)+IDCHF-1), (NAME+2), posB, (ID+2));
//------------------------------------------------------------------------------
		for(cham_base* CHB=*(CH_BASE+ID_SP); CHB->id_cham;CHB++)
	{
		int idch=CHB->id_cham;
		char* chNAME[6];
		chNAME[0]=CHB->cham_names;
		chNAME[1]=CHB->cham_names+NCHB;
		chNAME[2]=CHB->cham_names+2*NCHB;
		chNAME[3]=CHB->cham_names+3*NCHB;
		chNAME[4]=CHB->cham_names+4*NCHB;
		chNAME[5]=CHB->cham_names+5*NCHB;
		for(team_base* gb=(*(T_BASE+ID_SP)+idch-1)->ptr_b;gb->id_team;gb++)
		{
			int idg=gb->id_team;
			char* gNAME[6];
			gNAME[0]=gb->team_name;
			gNAME[1]=gb->team_name+NTB;
			gNAME[2]=gb->team_name+2*NTB;
			gNAME[3]=gb->team_name+3*NTB;
			gNAME[4]=gb->team_name+4*NTB;
			gNAME[5]=gb->team_name+5*NTB;
			continue;
		}
	}
//------------------------------------------------------------------------------
		return true;
	}

	
	for(cham_base* CHB=*(CH_BASE+ID_SP); CHB;CHB++)
	{
		int idch=CHB->id_cham;
		char* chNAME=CHB->cham_names;
		for(team_base* gb=(*(T_BASE+ID_SP)+idch-1)->ptr_b;gb;gb++)
		{
			int idg=gb->id_team;
			char* gNAME=gb->team_name;
			continue;
		}
	}
}

void BASE_INTERFACE::_ANTeam(p_t_b* PTB, char** T12, int* pos, int* IDT)//ADD TEAM NAME 1 & 2
{
	p_t_b* pp=PTB;
	char* T1n=*T12;
	char* T2n=*(T12+1);
	int p1=*pos;
	int p2=*(pos+1);
	if(IDT){
	int it1=*IDT;
	int it2=*(IDT+1);}

	const int NTB=100;
	int IDTeam=0;
	if(IDT)
	{
		int IDTF=*IDT;
		int Tpos=*(pos+1);
		char* Tname=*(T12+1);
		if(!(*IDT))
		{
			IDTF=*(IDT+1);
			Tpos=*pos;
			Tname=*T12;
		}
		IDTeam=IDTF;
		AddName((PTB->ptr_b+IDTF-1)->team_name,NTB*(Tpos-1),Tname);
	}else{
	//////////////////////////////////////////////////////////////////////////////
	if(!(PTB->ptr_b))//NO TEAM
	{
		PTB->ptr_b=new team_base[2];
		IDTeam=PTB->ptr_b->id_team=1;
		PTB->ptr_b->team_name=new char[NTB*(PB->n_bet)];
		for(int i=0;i<PB->n_bet;i++) *(PTB->ptr_b->team_name+i*NTB)='\0';
		AddName(PTB->ptr_b->team_name,NTB*(*pos-1),*T12);
		AddName(PTB->ptr_b->team_name,NTB*(*(pos+1)-1),*(T12+1));
		(PTB->ptr_b+1)->id_team=0;
		(PTB->ptr_b+1)->team_name=NULL;

	}
	else//HAVE TEAM
	{
		int i=0;
		for(team_base* t=PTB->ptr_b;t->id_team; i++, t++);
		team_base* TEMP=new team_base[i+2];
		for(int j=0;j<i;j++)
		{
			(TEMP+j)->id_team=(PTB->ptr_b+j)->id_team;
			(TEMP+j)->team_name=(PTB->ptr_b+j)->team_name;
		}
		PTB->ptr_b=TEMP;
		IDTeam=(TEMP+i)->id_team=i+1;
		(TEMP+i)->team_name=new char[NTB*(PB->n_bet)];
		for(int j=0;j<PB->n_bet;j++) *((TEMP+i)->team_name+j*NTB)='\0';
		AddName((TEMP+i)->team_name,NTB*(*pos-1),*T12);
		AddName((TEMP+i)->team_name,NTB*(*(pos+1)-1),*(T12+1));
		(TEMP+i+1)->id_team=0;
		(TEMP+i+1)->team_name=NULL;
	}}
	if(NTeam)
	{
		if(!RB_VToo) G1->ID_T1 = G2->ID_T1 = *(IDS+2) = *(IDS+4) = IDTeam;
		else G1->ID_T1 = G2->ID_T2 = *(IDS+2) = *(IDS+5) = IDTeam;
	}
	else
	{
		if(!RB_VToo) G1->ID_T2 = G2->ID_T2 = *(IDS+3) = *(IDS+5) = IDTeam;
		else G1->ID_T2 = G2->ID_T1 = *(IDS+3) = *(IDS+4) = IDTeam;
	}
}

void BASE_INTERFACE::AddName(char *Base, int pos, char *Name)
{
	int i=0;
	for(;*(Name+i)!='\0';i++)
	{
		*(Base+pos+i)=*(Name+i);
	}
	*(Base+pos+i)='\0';
}

void BASE_INTERFACE::ref_base(bool OneTwo)
{
	SortNewOld();

	if(OneTwo)
	{
		if(!(CH_1->ID_CH)) CH_1->ID_CH=*IDS;
		if(!(CH_2->ID_CH)) CH_2->ID_CH=*IDS;
		if(RB_VToo)
		{
			G1->ID_T1=G2->ID_T2=*(IDS+2);
			return;
		}
		G1->ID_T1=G2->ID_T1=*(IDS+2);
	}
	else
	{
		if(RB_VToo)	G1->ID_T2=G2->ID_T1=*(IDS+3);
		else	G1->ID_T2=G2->ID_T2=*(IDS+3);
		CColorListBox* LB;
		CListCtrl* LC;
		CString IDch;
		BI_G* G;
		BI_CH* CH;
		for(int i=0;i<2;i++)
		{
			if(i)
			{
				LB=&LB2;
				LC=&listc2;
				CH=CH_2;
				G=G2;
			}
			else
			{
				LB=&LB1;
				LC=&listc1;
				CH=CH_1;
				G=G1;
			}

			if(NEWCH)
			{
				if(NEWCH==3)
				{
					//LB->InsertString(LB->GetCurSel(),CString(CH->NAME_CH),RGB(10,10,255));
					IDch.Format(L"%02i",CH->ID_CH);
					IDch=L"["+IDch+L"] "+CString(CH->NAME_CH);
					LB->InsertString(LB->GetCurSel(),IDch);
					LB->SelectString(LB->GetCurSel(),IDch);
					LB->DeleteString(LB->GetCurSel()+1);
				}
				if(NEWCH==1 && !i)
				{
					//LB->InsertString(LB->GetCurSel(),CString(CH->NAME_CH),RGB(10,10,255));
					IDch.Format(L"%02i",CH->ID_CH);
					IDch=L"["+IDch+L"] "+CString(CH->NAME_CH);
					LB->InsertString(LB->GetCurSel(),IDch);
					LB->SelectString(LB->GetCurSel(),IDch);
					LB->DeleteString(LB->GetCurSel()+1);
				}
				if(NEWCH==2 && i)
				{
					//LB->InsertString(LB->GetCurSel(),CString(CH->NAME_CH),RGB(10,10,255));
					IDch.Format(L"%02i",CH->ID_CH);
					IDch=L"["+IDch+L"] "+CString(CH->NAME_CH);
					LB->InsertString(LB->GetCurSel(),IDch);
					LB->SelectString(LB->GetCurSel(),IDch);
					LB->DeleteString(LB->GetCurSel()+1);
				}
			}
			///////////////////////////////////////////////////////////////////////
			//CString NAME;
			LVITEM lv;
			lv.mask=LVIF_TEXT;
			lv.iItem=LC->GetNextItem(-1,LVNI_FOCUSED);
			lv.iSubItem=0;
			IDch.Format(L"%02i",G->ID_T1);
			IDch=L"["+IDch+"] "+CString(G->NAME_T1);
			//NAME=L"["+CString(G->NAME_T1)+L"]";
			lv.pszText=(LPTSTR)(LPCTSTR)IDch;
			LC->SetItem(&lv);

			lv.iSubItem=1;//erkrord syun
			//NAME=L"["+CString(G->NAME_T2)+L"]";
			IDch.Format(L"%02i",G->ID_T2);
			IDch=L"["+IDch+"] "+CString(G->NAME_T2);
			lv.pszText=(LPTSTR)(LPCTSTR)IDch;
			LC->SetItem(&lv);//Ekrord syan lracum
			//
		}
	}
}

void BASE_INTERFACE::SortNewOld(void)
{
	BI_BET* TEMP;
	BI_CH* TCH;
	for(int i=0;i<2;i++)
	{
		if(!i)	TEMP=B_1;
		else
		{
			if(B_1==B_2)return;
			TEMP=B_2;
		}
		TCH=TEMP->CHS_ZERO;
		if(!TCH)continue;
		for( ; TCH->ID_CH; TCH=TEMP->CHS_ZERO )
		{
			TEMP->CHS_ZERO=TEMP->CHS_ZERO->next;
			TCH->next=TEMP->CHS;
			TEMP->CHS=TCH;
			if(!TEMP->CHS_ZERO) break;
		}
		TCH=TEMP->CHS_ZERO;
		if(!(TCH))continue;
		BI_CH* Tk=(TEMP->CHS_ZERO);
		for(;Tk->next; )
		{
			if(Tk->next->ID_CH)
			{
				TCH=Tk->next;
				Tk->next=Tk->next->next;
				TCH->next=TEMP->CHS;
				TEMP->CHS=TCH;
				continue;
			}
			Tk=Tk->next;
		}
	}
}



void BASE_INTERFACE::OnCbnSelchangeCombo2()
{
	// TODO: Add your control notification handler code here
}


void BASE_INTERFACE::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	SaveBase();
	//CDialogEx::OnOK();
}

void BASE_INTERFACE::SaveBase()
{
	std::ofstream ChBase("BASE/CHAMPIONSHIP/CHAM.b",std::ios::trunc);
	std::ofstream TeamB("BASE/TEAM/TEAM.b",std::ios::trunc);
	const int CHBN=200;
	const int TBN=100;
	
	for(int i=0;i<PB->n_sport;i++)
	{
		////////////////////////-----------------SAVE CHAMPIONSHIP BASE-------------------
		if(*(CH_BASE+i))
		{
			int N_Ch=0;
			for(cham_base* TCH=*(CH_BASE+i);TCH->id_cham;++N_Ch,TCH++);
			ChBase<<(i+1)<<" "<<N_Ch<<"\n\n";
			cham_base* TCH=*(CH_BASE+i);
			for(int j=0;j<N_Ch;j++)
			{
				ChBase<<((TCH+j)->id_cham)<<" ";
				for(int k=0;k<PB->n_bet;k++) ChBase<<((TCH+j)->cham_names+CHBN*k)<<"=";
				ChBase<<"\n";
			}
			ChBase<<"\n\n";
		}
		else
		{
			ChBase<<(i+1)<<" 0\n\n";
		}
		////////////////////////-----------------SAVE TEAM BASE-----------------------------
		TeamB<<(i+1)<<"\n\n";
		if(*(T_BASE+i))
		{
			int NTeam;
			int ji=0;
			for(p_t_b* TT=*(T_BASE+i);TT->id_cham;ji++, TT++)
			{
				if(TT->id_cham!=(ji+1))break;
				TeamB<<TT->id_cham<<" ";
				NTeam=0;
				for(team_base* TTB=TT->ptr_b;TTB->id_team; NTeam++, TTB++);
				TeamB<<NTeam<<"\n\n";
				for(team_base* TTB=TT->ptr_b;TTB->id_team;TTB++)
				{
					TeamB<<TTB->id_team<<" ";
					for(int k=0;k<PB->n_bet;k++) TeamB<<(TTB->team_name+TBN*k)<<"=";
					TeamB<<"\n";
				}
				TeamB<<"\n";
			}
		}

	}
	

}


void BASE_INTERFACE::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
	RB_VToo=!r1.GetCheck();
}


void BASE_INTERFACE::OnBnClickedRadio2()
{
	// TODO: Add your control notification handler code here
	RB_VToo=!r1.GetCheck();
}


void BASE_INTERFACE::OnNMClickList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
	if(LB1.GetCurSel()==-1) return;
	CString T1=listc1.GetItemText(listc1.GetNextItem(-1,LVNI_FOCUSED),0);
	CString T2=listc1.GetItemText(listc1.GetNextItem(-1,LVNI_FOCUSED),1);
	CString GameDate=listc1.GetItemText(listc1.GetNextItem(-1,LVNI_FOCUSED),2);
	_SetTeamID(T1,T2,GameDate,true);
}


void BASE_INTERFACE::OnNMClickList4(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
	if(LB2.GetCurSel()==-1) return;
	CString T1=listc2.GetItemText(listc2.GetNextItem(-1,LVNI_FOCUSED),0);
	CString T2=listc2.GetItemText(listc2.GetNextItem(-1,LVNI_FOCUSED),1);
	CString GameDate=listc2.GetItemText(listc2.GetNextItem(-1,LVNI_FOCUSED),2);
	_SetTeamID(T1,T2,GameDate,false);
}


void BASE_INTERFACE::OnCbnSelchangeCombo4()
{
	// TODO: Add your control notification handler code here
}


void BASE_INTERFACE::OnBnClickedButton5()
{
	// TODO: Add your control notification handler code here
	if(AT_ON)
	{
		listc2.DeleteAllItems();
		LB2.ResetContent();
		rg1_1.EnableWindow();
		rg1_2.EnableWindow();
		butt_ATN.EnableWindow();
		edit_ATN.EnableWindow();
		butt_OLD.EnableWindow(FALSE);
		butt_NEW.EnableWindow(FALSE);
		combo_DA2.EnableWindow(FALSE);
		combo_b2.EnableWindow(FALSE);
		AT_ON=false;
	}
	else
	{
		listc2.DeleteAllItems();
		LB2.ResetContent();
		rg1_1.EnableWindow(FALSE);
		rg1_2.EnableWindow(FALSE);
		butt_ATN.EnableWindow(FALSE);
		edit_ATN.EnableWindow(FALSE);
		butt_OLD.EnableWindow();
		butt_NEW.EnableWindow();
		combo_DA2.EnableWindow();
		combo_b2.EnableWindow();
		AT_ON=true;
	}
}


void BASE_INTERFACE::OnBnClickedButton8()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CString AddName=L"|"+cs_ATN;
	wchar_t * wAN=AddName.GetBuffer(AddName.GetLength());
	//char g=*(AN+1);
	int z=1;
}

void BASE_INTERFACE::ActivateGoal(bool GO)
{
	if(GO)
	{
		b_gt1.EnableWindow();
		b_gt2.EnableWindow();
		b_gp.EnableWindow();
		b_gm.EnableWindow();
	}
	else
	{
		b_gt1.EnableWindow(FALSE);
		b_gt2.EnableWindow(FALSE);
		b_gp.EnableWindow(FALSE);
		b_gm.EnableWindow(FALSE);
		return;
	}
	int ID_S, ID_CH, ID_T1, ID_T2, ID_B_bi;
	ID_S=1;
	if(L12)//ture=L1;
	{
		ID_CH=*IDS;
		ID_T1=*(IDS+2);
		ID_T2=*(IDS+3);
		ID_B_bi=B_1->ID_BET_NAME;
	}
	else
	{
		ID_CH=*(IDS+1);
		ID_T1=*(IDS+4);
		ID_T2=*(IDS+5);
		ID_B_bi=B_2->ID_BET_NAME;
	}
	GAME_TIP=NULL;
	GAME_TIP_F=NULL;
	sport* SP;
	for(int i=0;i<2;i++){
		if(!i) SP=(XF->GET_ACCESS_F()) + ID_B_bi-1;
		else SP=PB->GET_ACCESS();
	for(; SP; SP=SP->next)
	{
		if(SP->id_s=ID_S)
		{
			for(cham* CHM=SP->ptrch; CHM; CHM=CHM->next)
			{		
				if(CHM->id_ch=ID_CH)
				{
					for(month* MO=CHM->ptrm; MO; MO=MO->next)
					{
						if(MO->y==*data_T && MO->m==*(data_T+1) && MO->day==*(data_T+2))
						{
							for(hour* HO=MO->ptrh; HO; HO=HO->next)
							{
								if(HO->h==*(data_T+3) && HO->minute==*(data_T+4))
								{
									for(game* GA=HO->ptrg; GA; GA=GA->next)
									{
										if((GA->id_t1==ID_T1 && GA->id_t2==ID_T2) | (GA->id_t1==ID_T2 && GA->id_t2==ID_T1))
										{
											if(!i)
											{
												GAME_TIP_F=GA;
												CString GT;
												if(GA->id_t1==ID_T2 && GA->id_t2==ID_T1)
												{
													GT.Format(L"%i",*(GA->goal+1));
													b_gt1.SetWindowTextW(GT);
													GT.Format(L"%i",*(GA->goal));
													b_gt2.SetWindowTextW(GT);
													UpdateData(false);
													continue;
												}
												GT.Format(L"%i",*(GA->goal));
												b_gt1.SetWindowTextW(GT);
												GT.Format(L"%i",*(GA->goal+1));
												b_gt2.SetWindowTextW(GT);
												UpdateData(false);
												continue;
											}
											GAME_TIP=GA;
											return;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}}
	GAME_TIP=NULL;
	GAME_TIP_F=NULL;
	return;
}

void BASE_INTERFACE::AddGoal(bool T12, bool PM)
{
	if(!GAME_TIP_F) return;
	int Goal[2];
	Goal[0]=*(GAME_TIP_F->goal);
	Goal[1]=*(GAME_TIP_F->goal+1);
	int ID_T1, ID_T2, TEMP;
	if(L12){ID_T1=*(IDS+2); ID_T2=*(IDS+3);}
	else{ID_T1=*(IDS+4); ID_T2=*(IDS+5);}
	if(ID_T1==GAME_TIP->id_t2 && ID_T2==GAME_TIP->id_t1){TEMP=Goal[0]; Goal[0]=Goal[1]; Goal[1]=TEMP;}
	if(T12)//T1
	{
		if(PM)
		{
			Goal[0]++;
		}
		else
		{
			Goal[0]--;
			if(Goal[0]<0) Goal[0]=0;
		}
	}
	else//T2
	{
		if(PM)
		{
			Goal[1]++;
		}
		else
		{
			Goal[1]--;
			if(Goal[1]<0) Goal[1]=0;
		}
	}
	CString GT;
	GT.Format(L"%i",Goal[0]);
	b_gt1.SetWindowTextW(GT);
	GT.Format(L"%i",Goal[1]);
	b_gt2.SetWindowTextW(GT);
	UpdateData(false);
	if(ID_T1==GAME_TIP->id_t2 && ID_T2==GAME_TIP->id_t1){TEMP=Goal[0]; Goal[0]=Goal[1]; Goal[1]=TEMP;}
	*(GAME_TIP_F->goal)=Goal[0];
	*(GAME_TIP_F->goal+1)=Goal[1];
	if(L12)	ADD_GOAL_BASE(1,*IDS,ID_T1,ID_T2,G1->DATE_GAME,(int *)Goal);
	else ADD_GOAL_BASE(1,*(IDS+1),ID_T1,ID_T2,G2->DATE_GAME,(int *)Goal);
	GAME_TIP->goal=GAME_TIP_F->goal;
}

void BASE_INTERFACE::OnBnClickedButton6()
{
	// TODO: Add your control notification handler code here
	AddGoal(true,true);
}


void BASE_INTERFACE::OnBnClickedButton7()
{
	// TODO: Add your control notification handler code here
	AddGoal(false,true);
}


void BASE_INTERFACE::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	AddGoal(true,false);
}


void BASE_INTERFACE::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	AddGoal(false,false);
}

void BASE_INTERFACE::ADD_GOAL_BASE(int ID_S, int ID_CH, int ID_T1, int ID_T2,int *DATA, int *GOAL)
{
	GOAL_CH* TGCH=PB->BASE_GOAL+ID_S-1;
	if(!TGCH->ID_CH)
	{
		TGCH->ID_CH=ID_CH;
		TGCH->ptrGG=new GOAL_G;
		TGCH->ptrGG->ID_T1=ID_T1;
		TGCH->ptrGG->ID_T2=ID_T2;
		TGCH->ptrGG->DATA=new int[5];
		for(int i=0;i<5;i++) *(TGCH->ptrGG->DATA+i)=*(DATA+i);
		TGCH->ptrGG->GOAL=new int[2];
		for(int i=0;i<2;i++) *(TGCH->ptrGG->GOAL+i)=*(GOAL+i);
		TGCH->ptrGG->next=NULL;
		return;
	}
	for(;;TGCH=TGCH->next)
	{
		if(TGCH->ID_CH==ID_CH)
		{
			if(!TGCH->ptrGG)
			{
				TGCH->ptrGG=new GOAL_G;
				TGCH->ptrGG->ID_T1=ID_T1;
				TGCH->ptrGG->ID_T2=ID_T2;
				TGCH->ptrGG->next=NULL;
				TGCH->ptrGG->DATA=new int[5];
				for(int i=0;i<5;i++) *(TGCH->ptrGG->DATA+i)=*(DATA+i);
				TGCH->ptrGG->GOAL=new int[2];
				for(int i=0;i<2;i++) *(TGCH->ptrGG->GOAL+i)=*(GOAL+i);
				return;
			}
			for(GOAL_G *TGG=TGCH->ptrGG;;TGG=TGG->next)
			{
				if((TGG->ID_T1)==ID_T1 && (TGG->ID_T2)==ID_T2)
				{
					bool TB=true;
					for(int i=0;i<5;i++) if( *(TGG->DATA+i) != *(DATA+i) ) TB=false; 
					if(TB)
					{
						*(TGG->GOAL)=*GOAL;
						*(TGG->GOAL+1)=*(GOAL+1);
						return;
					}
					else continue;
				}
				if(!TGG->next)
				{
					TGG->next=new GOAL_G;
					TGG=TGG->next;
					TGG->next=NULL;
					TGG->ID_T1=ID_T1;
					TGG->ID_T2=ID_T2;
					TGG->DATA=new int[5];
					for(int i=0;i<5;i++) *(TGG->DATA+i)=*(DATA+i);
					TGG->GOAL=new int[2];
					for(int i=0;i<2;i++) *(TGG->GOAL+i)=*(GOAL+i);
					return;
				}
			}
		}
		if(!TGCH->next)
		{
			TGCH->next=new GOAL_CH;
			TGCH=TGCH->next;
			TGCH->next=NULL;
			TGCH->ID_CH=ID_CH;
			TGCH->ptrGG=new GOAL_G;
			TGCH->ptrGG->ID_T1=ID_T1;
			TGCH->ptrGG->ID_T2=ID_T2;
			TGCH->ptrGG->DATA=new int[5];
			for(int i=0;i<5;i++) *(TGCH->ptrGG->DATA+i)=*(DATA+i);
			TGCH->ptrGG->GOAL=new int[2];
			for(int i=0;i<2;i++) *(TGCH->ptrGG->GOAL+i)=*(GOAL+i);
			TGCH->ptrGG->next=NULL;
			return;
		}
	}
}

