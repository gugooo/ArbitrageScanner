
// GA2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "GA2.h"
#include "GA2Dlg.h"
#include "afxdialogex.h"
#include "VIL.h"
#include "BASE_INTERFACE.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGA2Dlg dialog


UINT Download_Line(LPVOID);

CGA2Dlg::CGA2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGA2Dlg::IDD, pParent)
	, stat1(_T(""))
	, stat2(_T(""))
	, str_LV3(_T(""))
	, N_BETS(8)//////////////N_BETS->6
	, dlg_ch1(FALSE)
	, dlg_ch2(FALSE)
	, dlg_ch3(FALSE)
	, dlg_ch4(FALSE)
	, dlg_ch5(FALSE)
	, dlg_ch6(FALSE)
	, dlg_ch7(FALSE)
	, dlg_ch8(FALSE)
	, dlg_ch9(FALSE)
	, dlg_ch10(FALSE)
	, dlg_ch11(FALSE)
	, dlg_ch12(FALSE)
	, dlg_ch13(FALSE)
	, dlg_ch14(FALSE)
	, dlg_ch15(FALSE)
	, dlg_ch16(FALSE)
	, dlg_ch17(FALSE)
	, dlg_ch18(FALSE)
	, dlg_ch19(FALSE)
	, dlg_ch20(FALSE)
	, dlg_ch21(FALSE)
	, dlg_ch22(FALSE)
	, dlg_ch23(FALSE)
	, dlg_ch24(FALSE)
	, dlg_ch25(FALSE)
	, dlg_ch26(FALSE)
	, dlg_ch27(FALSE)
	, dlg_ch28(FALSE)
	, dlg_ch29(FALSE)
	, dlg_ch30(FALSE)
	, dlg_ch31(FALSE)
	, dlg_ch32(FALSE)
	, dlg_ch33(FALSE)
	, dlg_ch34(FALSE)
	, dlg_ch35(FALSE)
	, dlg_ch36(FALSE)
	, dlg_ch37(FALSE)
	, dlg_ch38(FALSE)
	, dlg_ed1(_T(""))
	, dlg_ed2(_T(""))
	, dlg_ed3(_T(""))
	, dlg_ed4(_T(""))
	, dlg_ed5(_T(""))
	, dlg_ed6(_T(""))
	, dlg_ed7(_T(""))
	, dlg_ed8(_T(""))
	, dlg_ed9(_T(""))
	, dlg_ed10(_T(""))
	, dlg_ed11(_T(""))
	
	
	, dlg_ed12(_T(""))
	, dlg_ed13(_T(""))
	, dlg_ch39(FALSE)
	, dlg_ch40(FALSE)
	, dlg_ch41(FALSE)
	, dlg_ch42(FALSE)
	, dlg_ch43(FALSE)
	, dlg_ch44(FALSE)
	, dlg_ch45(FALSE)
	, dlg_ch46(FALSE)
	, dlg_ch47(FALSE)
	, dlg_ch48(FALSE)
	, dlg_ch49(FALSE)
	, dlg_ch50(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
}

void CGA2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST1, LV);
	DDX_Control(pDX, IDC_LIST22, LV2);
	DDX_Text(pDX, IDC_STATIC1, stat1);
	DDX_Control(pDX, IDC_STATIC2, c_stat2);
	DDX_Text(pDX, IDC_STATIC2, stat2);
	DDX_Control(pDX, IDC_STATIC1, c_stat1);
	DDX_Control(pDX, IDC_LIST2, LV3);
	DDX_LBString(pDX, IDC_LIST2, str_LV3);
	DDX_Check(pDX, IDC_CHECK1, dlg_ch1);
	DDX_Check(pDX, IDC_CHECK2, dlg_ch2);

	DDX_Check(pDX, IDC_CHECK3, dlg_ch3);
	DDX_Check(pDX, IDC_CHECK4, dlg_ch4);
	DDX_Check(pDX, IDC_CHECK5, dlg_ch5);
	DDX_Check(pDX, IDC_CHECK6, dlg_ch6);
	DDX_Check(pDX, IDC_CHECK7, dlg_ch7);
	DDX_Check(pDX, IDC_CHECK8, dlg_ch8);
	DDX_Check(pDX, IDC_CHECK9, dlg_ch9);
	DDX_Check(pDX, IDC_CHECK10, dlg_ch10);
	DDX_Check(pDX, IDC_CHECK11, dlg_ch11);
	DDX_Check(pDX, IDC_CHECK12, dlg_ch12);
	DDX_Check(pDX, IDC_CHECK13, dlg_ch13);
	DDX_Check(pDX, IDC_CHECK14, dlg_ch14);
	DDX_Check(pDX, IDC_CHECK15, dlg_ch15);
	DDX_Check(pDX, IDC_CHECK16, dlg_ch16);
	DDX_Check(pDX, IDC_CHECK17, dlg_ch17);
	DDX_Check(pDX, IDC_CHECK18, dlg_ch18);
	DDX_Check(pDX, IDC_CHECK19, dlg_ch19);
	DDX_Check(pDX, IDC_CHECK20, dlg_ch20);
	DDX_Check(pDX, IDC_CHECK21, dlg_ch21);
	DDX_Check(pDX, IDC_CHECK22, dlg_ch22);
	DDX_Check(pDX, IDC_CHECK23, dlg_ch23);
	DDX_Check(pDX, IDC_CHECK24, dlg_ch24);
	DDX_Check(pDX, IDC_CHECK25, dlg_ch25);
	DDX_Check(pDX, IDC_CHECK26, dlg_ch26);
	DDX_Check(pDX, IDC_CHECK27, dlg_ch27);
	DDX_Check(pDX, IDC_CHECK28, dlg_ch28);
	DDX_Check(pDX, IDC_CHECK29, dlg_ch29);
	DDX_Check(pDX, IDC_CHECK30, dlg_ch30);
	DDX_Check(pDX, IDC_CHECK31, dlg_ch31);
	DDX_Check(pDX, IDC_CHECK32, dlg_ch32);
	DDX_Check(pDX, IDC_CHECK33, dlg_ch33);
	DDX_Check(pDX, IDC_CHECK34, dlg_ch34);
	DDX_Check(pDX, IDC_CHECK35, dlg_ch35);
	DDX_Check(pDX, IDC_CHECK36, dlg_ch36);
	DDX_Check(pDX, IDC_CHECK37, dlg_ch37);
	DDX_Check(pDX, IDC_CHECK38, dlg_ch38);

	DDX_Text(pDX, IDC_EDIT1, dlg_ed1);
	DDX_Text(pDX, IDC_EDIT2, dlg_ed2);
	DDX_Text(pDX, IDC_EDIT3, dlg_ed3);
	DDX_Text(pDX, IDC_EDIT4, dlg_ed4);
	DDX_Text(pDX, IDC_EDIT5, dlg_ed5);
	DDX_Text(pDX, IDC_EDIT6, dlg_ed6);
	DDX_Text(pDX, IDC_EDIT7, dlg_ed7);
	DDX_Text(pDX, IDC_EDIT8, dlg_ed8);
	DDX_Text(pDX, IDC_EDIT9, dlg_ed9);
	DDX_Text(pDX, IDC_EDIT10, dlg_ed10);
	DDX_Text(pDX, IDC_EDIT11, dlg_ed11);
	DDX_Control(pDX, IDC_CHECK7, dlgc_ch7);
	DDX_Control(pDX, IDC_CHECK8, dlgc_ch8);
	DDX_Control(pDX, IDC_CHECK9, dlgc_ch9);
	DDX_Control(pDX, IDC_CHECK10, dlgc_ch10);
	DDX_Control(pDX, IDC_CHECK11, dlgc_ch11);
	DDX_Control(pDX, IDC_CHECK12, dlgc_ch12);
	DDX_Control(pDX, IDC_CHECK31, dlgc_ch31);
	DDX_Control(pDX, IDC_CHECK32, dlgc_ch32);
	DDX_Control(pDX, IDC_CHECK33, dlgc_ch33);
	DDX_Control(pDX, IDC_CHECK34, dlgc_ch34);
	DDX_Control(pDX, IDC_CHECK35, dlgc_ch35);
	DDX_Control(pDX, IDC_CHECK36, dlgc_ch36);
	DDX_Control(pDX, IDC_COMMAND1, com_c1);

	DDX_Control(pDX, IDC_COMMAND2, com_c2);
	DDX_Text(pDX, IDC_EDIT12, dlg_ed12);
	DDX_Text(pDX, IDC_EDIT13, dlg_ed13);
	DDX_Check(pDX, IDC_CHECK39, dlg_ch39);
	DDX_Check(pDX, IDC_CHECK40, dlg_ch40);
	DDX_Check(pDX, IDC_CHECK41, dlg_ch41);
	DDX_Check(pDX, IDC_CHECK42, dlg_ch42);
	DDX_Check(pDX, IDC_CHECK43, dlg_ch43);
	DDX_Check(pDX, IDC_CHECK44, dlg_ch44);
	DDX_Check(pDX, IDC_CHECK45, dlg_ch45);
	DDX_Check(pDX, IDC_CHECK46, dlg_ch46);
	DDX_Check(pDX, IDC_CHECK47, dlg_ch47);
	DDX_Check(pDX, IDC_CHECK48, dlg_ch48);
	DDX_Check(pDX, IDC_CHECK49, dlg_ch49);
	DDX_Check(pDX, IDC_CHECK50, dlg_ch50);
	DDX_Control(pDX, IDC_CHECK41, dlgc_ch41);
	DDX_Control(pDX, IDC_CHECK42, dlgc_ch42);
	DDX_Control(pDX, IDC_CHECK46, dlgc_ch46);
	DDX_Control(pDX, IDC_CHECK50, dlgc_ch50);
	DDX_Control(pDX, IDC_BUTTON1, b_base);
}

BEGIN_MESSAGE_MAP(CGA2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_COMMAND1, &CGA2Dlg::OnBnClickedCommand1)
	ON_BN_CLICKED(IDC_COMMAND2, &CGA2Dlg::OnBnClickedCommand2)
	ON_LBN_SELCHANGE(IDC_LIST1, &CGA2Dlg::OnLbnSelchangeList1)
	ON_LBN_SELCHANGE(IDC_LIST22, &CGA2Dlg::OnLbnSelchangeList22)
	ON_CONTROL_RANGE(BN_CLICKED,IDC_CHECK1,IDC_CHECK50,&CGA2Dlg::OnBnClickedCheckBox)
	ON_CONTROL_RANGE(EN_CHANGE,IDC_EDIT1,IDC_EDIT13,&CGA2Dlg::OnBnClickedEditC)
	ON_BN_CLICKED(IDC_BUTTON1, &CGA2Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CGA2Dlg message handlers

BOOL CGA2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	ShowWindow(SW_MAXIMIZE);
	ptrBET=NULL;
	XmlF=NULL;
	////////////////////////////////LIST_BOX_1-FONT//////////////////////////////////////////
	CFont* ob1;
	ob1 = new CFont;
	ob1->CreateFont(20, 0, 0, 0, FW_MEDIUM,
	FALSE, FALSE, FALSE, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,   DEFAULT_QUALITY,
	DEFAULT_PITCH | FF_MODERN, L"GUGO1");
	LV.SetFont(ob1);
	/*CString qw;
	qw.Format(L"% 35.20s",L"A");*/

	///////////////////////////////////////////////////////////////////////////////////////
	//***********************************************************************************//
	////////////////////////////////LIST_BOX_2-FONT////////////////////////////////////////
	CFont* ob2;
	ob2 = new CFont;
	ob2->CreateFont(18, 0, 0, 0, FW_MEDIUM,
	FALSE, FALSE, FALSE, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,   DEFAULT_QUALITY,
	DEFAULT_PITCH | FF_MODERN, L"GUGO2");
	LV2.SetFont(ob2);
	//LV2.AddString(qw);
	//////////////////////////////////////////////////////////////////////////////////////
	//***********************************************************************************//
	////////////////////////////////LIST_BOX_2-FONT////////////////////////////////////////
	CFont* ob3;
	ob3 = new CFont;
	ob3->CreateFont(22, 0, 0, 0, FW_MEDIUM,
	FALSE, FALSE, FALSE, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,   DEFAULT_QUALITY,
	DEFAULT_PITCH | FF_ROMAN, L"GUGO2");
	c_stat2.SetFont(ob3);
	c_stat1.SetFont(ob3);
	T_FONT=ob3;
	T_FONT2=ob2;
	//////////////////////////////////INTERFACE////////////////////////////////////////
	ptrIGA=new Interface_Ga(N_BETS);
	set_I_GA();
	//////////////////////////////////////////////////////////////////////////////////////

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGA2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGA2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGA2Dlg::OnBnClickedCommand1()
{
	// TODO: Add your control notification handler code here
	
	
	//ptrBET->listM=&LV3;
	
	//ptrBET->START();
	ptrBET->V_ALL.GVALL=NULL;
	ptrBET->V_ALL.next=NULL;
	ptrBET->v_all();
	
	creatlist1(ptrBET->V_ALL);
}

void CGA2Dlg::creatlist1(sbor_ALL S_ALL)
{
	LV.ResetContent();
	LV2.ResetContent();
	if(!S_ALL.GVALL)return;
	NLV=-1;
	int ids,idch,idb1,idbN1,idb2,idbN2,idb3,idbN3,idt1,idt2,idkc1,idkc2,idkc3;
	CString CH_NAME,TE_NAME,KC1_NAME,KC2_NAME,KC3_NAME,VT_NAME;
	sbor_ALL* tall=&S_ALL;
	sbor_GV* tall2;
	int N_V2,N_V3;
	for(int i=0;tall;i++,tall=tall->next)
	{
		//////////////N_V2|N_V3///////////////////////
		tall2=tall->GVALL;
		for(N_V2=0,N_V3=0;tall2;tall2=tall2->next)
		{
			if(tall2->N2)N_V2+=tall2->N2;
			else N_V3+=tall2->N3;
		}
		////////////////////////////////////////////
		if(tall->GVALL->G_V2)
		{
			ids=tall->GVALL->G_V2->KC1->TKC->back_game->back_hour->back_month->back_cham->back_sport->id_s;
			idch=tall->GVALL->G_V2->KC1->TKC->back_game->back_hour->back_month->back_cham->id_ch;
			idb1=tall->GVALL->G_V2->KC1->id_bet;
			idbN1=tall->GVALL->G_V2->KC1->id_bet_name;
			idb2=tall->GVALL->G_V2->KC2->id_bet;
			idbN2=tall->GVALL->G_V2->KC2->id_bet_name;
			idt1=tall->GVALL->G_V2->KC1->TKC->back_game->id_t1;
			idt2=tall->GVALL->G_V2->KC1->TKC->back_game->id_t2;
			idkc1=tall->GVALL->G_V2->KC1->TKC->id_kc;
			idkc2=tall->GVALL->G_V2->KC2->TKC->id_kc;
			//ptrBET->FIX_BET(idb1);
			///////////////////////////////////////////////////////////////////////////
			CString NV;
			NV.Format(L"[%i][%i]",N_V2,N_V3);
			CH_NAME.Format(L"%-45.45s%10.10s",CString(ptrBET->get_cham_name(idch,ids,idb1)),NV);
			LV.AddString(CH_NAME);
			//LV.SetSel(i*6);
			///////////////////////////////////////////////////////////////////////////
			///////////////////////////////////////////////////////////////////////////
			
			TE_NAME.Format(L"%-55.55s",(CString(ptrBET->get_team_name(idt1,idch,ids,idb1))+L"  -  "+CString(ptrBET->get_team_name(idt2,idch,ids,idb2))));
			LV.AddString(TE_NAME);
			///////////////////////////////////////////////////////////////////////////
			///////////////////////////////////////////////////////////////////////////
			CString kc1_name=CString(ptrBET->get_kc_NU(idkc1));
			float LKC=tall->GVALL->G_V2->KC1->kc;
			if(tall->GVALL->G_V2->LAY1){ kc1_name=L"LAY "+kc1_name;LKC=-LKC;}
			KC1_NAME.Format(L"% 10.10s%-17.17s %-20.20s %-7.2f",L"",CString(ptrBET->bet_name(idbN1)),kc1_name,LKC);
			LV.AddString(KC1_NAME);
			///////////////////////////////////////////////////////////////////////////
			///////////////////////////////////////////////////////////////////////////
			VT_NAME.Format(L"%-10.2f",tall->GVALL->G_V2->vt);
			LV.AddString(VT_NAME);
			///////////////////////////////////////////////////////////////////////////
			///////////////////////////////////////////////////////////////////////////
			CString kc2_name=CString(ptrBET->get_kc_NU(idkc2));
			LKC=tall->GVALL->G_V2->KC2->kc;
			if(tall->GVALL->G_V2->LAY2){ kc2_name=L"LAY "+kc2_name;LKC=-LKC;}
			KC2_NAME.Format(L"% 10.10s%-17.17s %-20.20s %-7.2f",L"",CString(ptrBET->bet_name(idbN2)),kc2_name,LKC);
			LV.AddString(KC2_NAME);
			///////////////////////////////////////////////////////////////////////////
			LV.AddString(L"________________________________________________________");
		}
		else 
		{
			ids=tall->GVALL->G_V3->KC1->TKC->back_game->back_hour->back_month->back_cham->back_sport->id_s;
			idch=tall->GVALL->G_V3->KC1->TKC->back_game->back_hour->back_month->back_cham->id_ch;
			idb1=tall->GVALL->G_V3->KC1->id_bet;
			idbN1=tall->GVALL->G_V3->KC1->id_bet_name;
			idb2=tall->GVALL->G_V3->KC2->id_bet;
			idbN2=tall->GVALL->G_V3->KC2->id_bet_name;
			idb3=tall->GVALL->G_V3->KC3->id_bet;
			idbN3=tall->GVALL->G_V3->KC3->id_bet_name;
			idt1=tall->GVALL->G_V3->KC1->TKC->back_game->id_t1;
			idt2=tall->GVALL->G_V3->KC1->TKC->back_game->id_t2;
			idkc1=tall->GVALL->G_V3->KC1->TKC->id_kc;
			idkc2=tall->GVALL->G_V3->KC2->TKC->id_kc;
			idkc3=tall->GVALL->G_V3->KC3->TKC->id_kc;
			///////////////////////////////////////////////////////////////////////////
			CH_NAME.Format(L"%-55.55s",CString(ptrBET->get_cham_name(idch,ids,idb1)));
			LV.AddString(CH_NAME);
			//LV.SetSel(i*6);
			///////////////////////////////////////////////////////////////////////////
			///////////////////////////////////////////////////////////////////////////
			TE_NAME.Format(L"%-55.55s",(CString(ptrBET->get_team_name(idt1,idch,ids,idb1))+L"  -  "+CString(ptrBET->get_team_name(idt2,idch,ids,idb2))));
			LV.AddString(TE_NAME);
			///////////////////////////////////////////////////////////////////////////
			///////////////////////////////////////////////////////////////////////////
			CString kc1_name=CString(ptrBET->get_kc_NU(idkc1));
			float LKC=tall->GVALL->G_V3->KC1->kc;
			if(*(tall->GVALL->G_V3->LAY)){ kc1_name=L"LAY "+kc1_name;LKC=-LKC;}
			KC1_NAME.Format(L"% 10.10s%-17.17s %-20.20s %-7.2f",L"",CString(ptrBET->bet_name(idbN1)),kc1_name,LKC);
			LV.AddString(KC1_NAME);
			///////////////////////////////////////////////////////////////////////////
			///////////////////////////////////////////////////////////////////////////
			CString kc2_name=CString(ptrBET->get_kc_NU(idkc2));
			LKC=tall->GVALL->G_V3->KC2->kc;
			if(*(tall->GVALL->G_V3->LAY+1)){ kc2_name=L"LAY "+kc2_name;LKC=-LKC;}
			//VT_NAME.Format(L"%-10.2f",tall->GVALL->G_V3->vt);
			KC2_NAME.Format(L"%-10.2f%-17.17s %-20.20s %-7.2f",tall->GVALL->G_V3->vt,CString(ptrBET->bet_name(idbN2)),kc2_name,LKC);
			LV.AddString(KC2_NAME);
			///////////////////////////////////////////////////////////////////////////
			///////////////////////////////////////////////////////////////////////////
			CString kc3_name=CString(ptrBET->get_kc_NU(idkc3));
			LKC=tall->GVALL->G_V3->KC3->kc;
			if(*(tall->GVALL->G_V3->LAY+2)){ kc3_name=L"LAY "+kc3_name;LKC=-LKC;}
			KC3_NAME.Format(L"% 10.10s%-17.17s %-20.20s %-7.2f",L"",CString(ptrBET->bet_name(idbN3)),kc3_name,LKC);
			LV.AddString(KC3_NAME);
			///////////////////////////////////////////////////////////////////////////
			LV.AddString(L"________________________________________________________");
		}
	}
	//LV.SetSel(0);
}

void CGA2Dlg::creatlist2(sbor_ALL Game)
{
	LV2.ResetContent();
	if(!Game.GVALL)return;
	sbor_GV* tall2=Game.GVALL;
	int ids,idch,idb1,idbN1,idb2,idbN2,idb3,idbN3,idt1,idt2,idkc1,idkc2,idkc3,Y,M,D,H,Mi;
	CString KC1_NAME, KC2_NAME, KC3_NAME, VT_NAME ;
	bool TV=true;
	bool TwoThree=true;
	for(;tall2;tall2=tall2->next)
	{
		if(tall2->G_V2)
		{
			if(TV)
			{
				Y=tall2->G_V2->KC1->TKC->back_game->back_hour->back_month->y;
				M=tall2->G_V2->KC1->TKC->back_game->back_hour->back_month->m;
				D=tall2->G_V2->KC1->TKC->back_game->back_hour->back_month->day;
				H=tall2->G_V2->KC1->TKC->back_game->back_hour->h;
				Mi=tall2->G_V2->KC1->TKC->back_game->back_hour->minute;
				//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
				v2* T_V2=tall2->G_V2;
				ids=T_V2->KC1->TKC->back_game->back_hour->back_month->back_cham->back_sport->id_s;
				idch=T_V2->KC1->TKC->back_game->back_hour->back_month->back_cham->id_ch;
				idb1=T_V2->KC1->id_bet;
				idbN1=T_V2->KC1->id_bet_name;
				idb2=T_V2->KC2->id_bet;
				idbN2=T_V2->KC2->id_bet_name;
				idt1=T_V2->KC1->TKC->back_game->id_t1;
				idt2=T_V2->KC1->TKC->back_game->id_t2;
				CString Time;
				stat2=CString(ptrBET->get_cham_name(idch,ids,idb2))+L"\n"+CString(ptrBET->get_team_name(idt1,idch,ids,idb2))+L"  -  "+CString(ptrBET->get_team_name(idt2,idch,ids,idb1));
				Time.Format(L"%i.%02i.%02i	%02i:%02i",Y,M,D,H,Mi);
				stat1=Time;
				//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
				TV=false;
			}
			for(v2* T_V2=tall2->G_V2;T_V2;T_V2=T_V2->next)
			{
				//ids=T_V2->KC1->TKC->back_game->back_hour->back_month->back_cham->back_sport->id_s;
				//idch=T_V2->KC1->TKC->back_game->back_hour->back_month->back_cham->id_ch;
				idb1=T_V2->KC1->id_bet;
				idbN1=T_V2->KC1->id_bet_name;
				idb2=T_V2->KC2->id_bet;
				idbN2=T_V2->KC2->id_bet_name;
				//idt1=T_V2->KC1->TKC->back_game->id_t1;
				//idt2=T_V2->KC1->TKC->back_game->id_t2;
				idkc1=T_V2->KC1->TKC->id_kc;
				idkc2=T_V2->KC2->TKC->id_kc;
				///////////////////////////////////////////////////////////////////////////
				CString kc1_name=CString(ptrBET->get_kc_NU(idkc1));
				float LKC=T_V2->KC1->kc;
				if(T_V2->LAY1){ kc1_name=L"LAY "+kc1_name;LKC=-LKC;}
				KC1_NAME.Format(L"% 8.8s%-10.10s %-17.17s %-7.2f",L"",CString(ptrBET->bet_name(idbN1)),kc1_name,LKC);
				LV2.AddString(KC1_NAME);
				///////////////////////////////////////////////////////////////////////////
				///////////////////////////////////////////////////////////////////////////
				VT_NAME.Format(L"%-8.2f",T_V2->vt);
				LV2.AddString(VT_NAME);
				///////////////////////////////////////////////////////////////////////////
				///////////////////////////////////////////////////////////////////////////
				CString kc2_name=CString(ptrBET->get_kc_NU(idkc2));
				LKC=T_V2->KC2->kc;
				if(T_V2->LAY2){ kc2_name=L"LAY "+kc2_name;LKC=-LKC;}
				KC2_NAME.Format(L"% 8.8s%-10.10s %-17.17s %-7.2f",L"",CString(ptrBET->bet_name(idbN2)),kc2_name,LKC);
				LV2.AddString(KC2_NAME);
				///////////////////////////////////////////////////////////////////////////
				LV2.AddString(L"___________________________________________");
			}
		}
		else
		{
			if(TV)
			{
				Y=tall2->G_V3->KC1->TKC->back_game->back_hour->back_month->y;
				M=tall2->G_V3->KC1->TKC->back_game->back_hour->back_month->m;
				D=tall2->G_V3->KC1->TKC->back_game->back_hour->back_month->day;
				H=tall2->G_V3->KC1->TKC->back_game->back_hour->h;
				Mi=tall2->G_V3->KC1->TKC->back_game->back_hour->minute;
				//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
				v3* T_V3=tall2->G_V3;
				ids=T_V3->KC1->TKC->back_game->back_hour->back_month->back_cham->back_sport->id_s;
				idch=T_V3->KC1->TKC->back_game->back_hour->back_month->back_cham->id_ch;
				idb1=T_V3->KC1->id_bet;
				idbN1=T_V3->KC1->id_bet_name;
				idb2=T_V3->KC2->id_bet;
				idbN2=T_V3->KC2->id_bet_name;
				idb3=T_V3->KC3->id_bet;
				idbN3=T_V3->KC3->id_bet_name;
				idt1=T_V3->KC1->TKC->back_game->id_t1;
				idt2=T_V3->KC1->TKC->back_game->id_t2;
				//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
				CString Time;
				stat2=CString(ptrBET->get_cham_name(idch,ids,idb2))+L"\n"+CString(ptrBET->get_team_name(idt1,idch,ids,idb2))+L"  -  "+CString(ptrBET->get_team_name(idt2,idch,ids,idb1));
				Time.Format(L"%i.%02i.%02i	%02i:%02i",Y,M,D,H,Mi);
				stat1=Time;
				TV=false;
			}
			for(v3* T_V3=tall2->G_V3;T_V3;T_V3=T_V3->next)
			{
				//ids=T_V3->KC1->TKC->back_game->back_hour->back_month->back_cham->back_sport->id_s;
				//idch=T_V3->KC1->TKC->back_game->back_hour->back_month->back_cham->id_ch;
				idb1=T_V3->KC1->id_bet;
				idbN1=T_V3->KC1->id_bet_name;
				idb2=T_V3->KC2->id_bet;
				idbN2=T_V3->KC2->id_bet_name;
				idb3=T_V3->KC3->id_bet;
				idbN3=T_V3->KC3->id_bet_name;
				//idt1=T_V3->KC1->TKC->back_game->id_t1;
				//idt2=T_V3->KC1->TKC->back_game->id_t2;
				idkc1=T_V3->KC1->TKC->id_kc;
				idkc2=T_V3->KC2->TKC->id_kc;
				idkc3=T_V3->KC2->TKC->id_kc;
				///////////////////////////////////////////////////////////////////////////
				CString kc1_name=CString(ptrBET->get_kc_NU(idkc1));
				float LKC=T_V3->KC1->kc;
				if(*(T_V3->LAY)){ kc1_name=L"LAY "+kc1_name; LKC=-LKC;}
				KC1_NAME.Format(L"% 8.8s%-10.10s %-17.17s %-7.2f",L"",CString(ptrBET->bet_name(idbN1)),kc1_name,LKC);
				LV2.AddString(KC1_NAME);
				///////////////////////////////////////////////////////////////////////////
				///////////////////////////////////////////////////////////////////////////
				CString kc2_name=CString(ptrBET->get_kc_NU(idkc2));
				LKC=T_V3->KC2->kc;
				if(*(T_V3->LAY+1)){ kc2_name=L"LAY "+kc2_name; LKC=-LKC;}
				KC2_NAME.Format(L"%-8.2fs%-10.10s %-17.17s %-7.2f",T_V3->vt,CString(ptrBET->bet_name(idbN2)),kc2_name,LKC);
				LV.AddString(KC2_NAME);
				///////////////////////////////////////////////////////////////////////////
				///////////////////////////////////////////////////////////////////////////
				CString kc3_name=CString(ptrBET->get_kc_NU(idkc3));
				LKC=T_V3->KC3->kc;
				if(*(T_V3->LAY+2)){ kc3_name=L"LAY "+kc3_name;LKC=-LKC;}
				KC3_NAME.Format(L"% 8.8s%-10.10s %-17.17s %-7.2f",L"",CString(ptrBET->bet_name(idbN3)),kc3_name,LKC);
				LV2.AddString(KC3_NAME);
				///////////////////////////////////////////////////////////////////////////
				LV2.AddString(L"___________________________________________");
			}
		}
	}
	/*CString Time;
	stat2=CString(ptrBET->get_cham_name(idch,ids,idb2))+L"\n"+CString(ptrBET->get_team_name(idt1,idch,ids,idb2))+L"  -  "+CString(ptrBET->get_team_name(idt2,idch,ids,idb1));
	Time.Format(L"%i.%02i.%02i	%02i:%02i",Y,M,D,H,Mi);
	stat1=Time;*/
	UpdateData(false);
	/////////////////////////////////////////////////////////////////////////////////////////////
}


/*void CGA2Dlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	CFont* objFont;
	objFont = new CFont;
	objFont->CreateFont(18, 0, 0, 0, FW_MEDIUM,
	FALSE, FALSE, FALSE, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,   DEFAULT_QUALITY,
	DEFAULT_PITCH | FF_MODERN, L"GUGO");
	LV.SetFont(objFont);
	LV.AddString(L"ARZU");
	
}*/


void CGA2Dlg::OnLbnSelchangeList1()
{
	// TODO: Add your control notification handler code here
	NLV2=-1;
	const int NPOL=6;
	int tn=LV.GetCurSel()/NPOL;
	if(NLV==-1)
	{
		for(int i=0;i<NPOL;i++)LV.SetSel(tn*NPOL+i,true);
	}
	else
	{
		for(int i=1;i<NPOL;i++)LV.SetSel(NLV*NPOL+i,false);
		for(int i=0;i<NPOL;i++)LV.SetSel(tn*NPOL+i,true);
	}
	NLV=tn;

	sbor_ALL Game;
	Game=ptrBET->V_ALL;
	for(int i=0;i<tn;i++)Game=*(Game.next);
	
	creatlist2(Game);
	
}


void CGA2Dlg::OnLbnSelchangeList22()
{
	// TODO: Add your control notification handler code here
	const int NPOL=4;
	int tn=LV2.GetCurSel()/NPOL;
	if(NLV2==-1)
	{
		for(int i=0;i<NPOL;i++)LV2.SetSel(tn*NPOL+i,true);
	}
	else
	{
		for(int i=1;i<NPOL;i++)LV2.SetSel(NLV2*NPOL+i,false);
		for(int i=0;i<NPOL;i++)LV2.SetSel(tn*NPOL+i,true);
	}
	NLV2=tn;
	//////////////////////////////////////////////////////////////////
	sbor_ALL GV=ptrBET->V_ALL;
	for(int i=0;i<NLV;i++,GV=*(GV.next));
	sbor_GV* TV=GV.GVALL;
	int v=0;
	for(;TV;)//
	{
		if(TV->N2)v=TV->N2;
		else v=TV->N3;
		////////////////////
		if(tn<v)break;
		TV=TV->next;
		tn-=v;
	}
	//////////////////////////////////////////////////////////////////
	VIL* ptr_VIL=new VIL(ptrBET, ptrIGA);//patuani stexcum
	int ids,idch,idb1,idb1_N,idb2,idb2_N,idb3,idt1,idt2,idkc1,idkc2,idkc3,Y,M,D,H,Mi;
	//////////////////////////////////////////////////////////////////
	CString Ttime;
	///////////////////////////////////////////////////////////////////
	
	if(TV->G_V2)
	{
		v2* Vil2=TV->G_V2;
		for(int i=0;i<tn;i++,Vil2=Vil2->next);
		ptr_VIL->VIL2=Vil2;
		/////////////////////////////////////////////
		ids=Vil2->KC1->TKC->back_game->back_hour->back_month->back_cham->back_sport->id_s;
		idch=Vil2->KC1->TKC->back_game->back_hour->back_month->back_cham->id_ch;
		idb1=Vil2->KC1->id_bet;
		idb1_N=Vil2->KC1->id_bet_name;
		idb2=Vil2->KC2->id_bet;
		idb2_N=Vil2->KC2->id_bet_name;
		idt1=Vil2->KC1->TKC->back_game->id_t1;
		idt2=Vil2->KC1->TKC->back_game->id_t2;
		idkc1=Vil2->KC1->TKC->id_kc;
		idkc2=Vil2->KC2->TKC->id_kc;
		//ptrBET->FIX_BET(idb1);
		Y=Vil2->KC1->TKC->back_game->back_hour->back_month->y;
		M=Vil2->KC1->TKC->back_game->back_hour->back_month->m;
		D=Vil2->KC1->TKC->back_game->back_hour->back_month->day;
		H=Vil2->KC1->TKC->back_game->back_hour->h;
		Mi=Vil2->KC1->TKC->back_game->back_hour->minute;
		Ttime.Format(L"%i.%02i.%02i\n%02i:%02i",Y,M,D,H,Mi);
		//////////////////////////////////////////
		
		ptr_VIL->vd_stat1=CString(ptrBET->get_cham_name(idch,ids,idb1));
		ptr_VIL->vd_stat2=CString(ptrBET->get_sport_name(ids,idb1));
		ptr_VIL->vd_stat3=CString(ptrBET->get_team_name(idt1,idch,ids,idb1))+L"  -  "+CString(ptrBET->get_team_name(idt2,idch,ids,idb2));
		ptr_VIL->vd_stat4=Ttime;
		ptr_VIL->vd_stat6=CString(ptrBET->bet_name(idb1_N));
		CString kc_name=CString(ptrBET->get_kc_NU(idkc1));
		float LKC1=Vil2->KC1->kc;
		float LKC2=Vil2->KC2->kc;
		if(Vil2->LAY1){ kc_name=L"LAY "+kc_name;LKC1=-LKC1;}
		ptr_VIL->vd_stat7=kc_name;
		ptr_VIL->vd_stat8=CString(ptrBET->bet_name(idb2_N));
		kc_name=CString(ptrBET->get_kc_NU(idkc2));
		if(Vil2->LAY2){ kc_name=L"LAY "+kc_name;LKC2=-LKC2;}
		ptr_VIL->vd_stat9=kc_name;
		ptr_VIL->vd_edit1.Format(L"%.2f",LKC1);
		ptr_VIL->vd_edit2.Format(L"%.2f",LKC2);
		
		UpdateData(false);
		
	}
	else
	{
		v3* Vil3=TV->G_V3;
		for(int i=0;i<tn;i++,Vil3=Vil3->next);
		ptr_VIL->VIL3=Vil3;
		
	}
	//////////////////////////////////////////////////////////////////
	ptr_VIL->Create(IDD_DIALOG1,this);
	(ptr_VIL->vdc_stat1).SetFont(T_FONT);//CHAMPIONSHIP
	(ptr_VIL->vdc_stat2).SetFont(T_FONT);//SPORT
	(ptr_VIL->vdc_stat3).SetFont(T_FONT);//TEAM
	(ptr_VIL->vdc_stat4).SetFont(T_FONT);//TIME
	(ptr_VIL->vdc_stat6).SetFont(T_FONT2);//BET1
	(ptr_VIL->vdc_stat7).SetFont(T_FONT2);//KC_NAME1
	(ptr_VIL->vdc_stat8).SetFont(T_FONT2);//BET2
	(ptr_VIL->vdc_stat9).SetFont(T_FONT2);//KC_NAME2
	ptr_VIL->vdc_stat10.ModifyStyle(WS_VISIBLE,0,0);
	ptr_VIL->vdc_stat11.ModifyStyle(WS_VISIBLE,0,0);
	ptr_VIL->vdc_stat14.ModifyStyle(WS_VISIBLE,0,0);
	ptr_VIL->vdc_p15.ModifyStyle(WS_VISIBLE,0,0);
	ptr_VIL->vdc_p16.ModifyStyle(WS_VISIBLE,0,0);
	ptr_VIL->vdc_p17.ModifyStyle(WS_VISIBLE,0,0);
	ptr_VIL->vdc_p18.ModifyStyle(WS_VISIBLE,0,0);
	ptr_VIL->vdc_p19.ModifyStyle(WS_VISIBLE,0,0);
	ptr_VIL->vdc_p20.ModifyStyle(WS_VISIBLE,0,0);
	ptr_VIL->vdc_p21.ModifyStyle(WS_VISIBLE,0,0);
	ptr_VIL->vdc_edit3.ModifyStyle(WS_VISIBLE,0,0);
	ptr_VIL->vdc_edit6.ModifyStyle(WS_VISIBLE,0,0);
	ptr_VIL->vdc_edit9.ModifyStyle(WS_VISIBLE,0,0);
	ptr_VIL->vdc_ch3.ModifyStyle(WS_VISIBLE,0,0);
	ptr_VIL->vdc_radio3.ModifyStyle(WS_VISIBLE,0,0);
	ptr_VIL->vdc_edit1.SetFont(T_FONT2);
	ptr_VIL->vdc_edit2.SetFont(T_FONT2);
	ptr_VIL->vdc_stat12.SetFont(T_FONT2);
	ptr_VIL->vdc_stat13.SetFont(T_FONT2);
	ptr_VIL->vdc_edit7.SetFont(T_FONT2);
	ptr_VIL->vdc_edit8.SetFont(T_FONT2);
	ptr_VIL->vdc_stat23.SetFont(T_FONT2);
	//ptr_VIL->vdc_but1.SetWindowTextW(L"G1");

	ptr_VIL->CVIL();
	ptr_VIL->ShowWindow(SW_SHOW);
	//////////////////////////////////////////////////////////////////
}


///////////////////////////////////////////////////////////
		///////////////INTERFACE//////////////
///////////////////////////////////////////////////////////
void CGA2Dlg::OnBnClickedEditC(UINT nID)
{
	UpdateData();
	switch(nID)
	{
		case IDC_EDIT1:ptrIGA->Bets->bt=(float)_wtof(dlg_ed1);break;
		case IDC_EDIT2:(ptrIGA->Bets+1)->bt=(float)_wtof(dlg_ed2);break;
		case IDC_EDIT3:(ptrIGA->Bets+2)->bt=(float)_wtof(dlg_ed3);break;
		case IDC_EDIT4:(ptrIGA->Bets+3)->bt=(float)_wtof(dlg_ed4);break;
		case IDC_EDIT5:(ptrIGA->Bets+4)->bt=(float)_wtof(dlg_ed5);break;
		case IDC_EDIT6:(ptrIGA->Bets+5)->bt=(float)_wtof(dlg_ed6);break;
		case IDC_EDIT12:(ptrIGA->Bets+6)->bt=(float)_wtof(dlg_ed12);break;
		case IDC_EDIT13:(ptrIGA->Bets+7)->bt=(float)_wtof(dlg_ed13);break;
		///////////////////////////////////////////////////////////////////
		case IDC_EDIT7:(ptrIGA->Filter).fr_h=(float)_wtof(dlg_ed7);break;
		case IDC_EDIT8:(ptrIGA->Filter).to_h=(float)_wtof(dlg_ed8);break;
		case IDC_EDIT9:(ptrIGA->Filter).vt=(float)_wtof(dlg_ed9);break;
		case IDC_EDIT10:(ptrIGA->Filter).usd=(float)_wtof(dlg_ed10);break;
		case IDC_EDIT11:(ptrIGA->Filter).rur=(float)_wtof(dlg_ed11);break;
		default:return;
	}
	ptrIGA->Save_Inf_Ga();
}
void CGA2Dlg::OnBnClickedCheckBox(UINT nID)
{
	UpdateData();
	switch(nID)
	{
		/////////////[BET-%]//////////////
	case IDC_CHECK1:ptrIGA->Bets->btp=dlg_ch1;break;
	case IDC_CHECK2:((ptrIGA->Bets+1)->btp)=dlg_ch2;break;
	case IDC_CHECK3:(ptrIGA->Bets+2)->btp=dlg_ch3;break;
	case IDC_CHECK4:(ptrIGA->Bets+3)->btp=dlg_ch4;break;
	case IDC_CHECK5:(ptrIGA->Bets+4)->btp=dlg_ch5;break;
	case IDC_CHECK6:(ptrIGA->Bets+5)->btp=dlg_ch6;break;
	case IDC_CHECK39:(ptrIGA->Bets+6)->btp=dlg_ch39;break;
	case IDC_CHECK40:(ptrIGA->Bets+7)->btp=dlg_ch40;break;
		///////////[LOAD XML]/////////////////
	case IDC_CHECK7:ptrIGA->Bets->l_xml=dlg_ch7;
		if(dlg_ch7)dlgc_ch7.SetWindowTextW(L"YES");else dlgc_ch7.SetWindowTextW(L"NO");break;
	case IDC_CHECK8:(ptrIGA->Bets+1)->l_xml=dlg_ch8;
		if(dlg_ch8)dlgc_ch8.SetWindowTextW(L"YES");else dlgc_ch8.SetWindowTextW(L"NO");break;
	case IDC_CHECK9:(ptrIGA->Bets+2)->l_xml=dlg_ch9;
		if(dlg_ch9)dlgc_ch9.SetWindowTextW(L"YES");else dlgc_ch9.SetWindowTextW(L"NO");break;
	case IDC_CHECK10:(ptrIGA->Bets+3)->l_xml=dlg_ch10;
		if(dlg_ch10)dlgc_ch10.SetWindowTextW(L"YES");else dlgc_ch10.SetWindowTextW(L"NO");break;
	case IDC_CHECK11:(ptrIGA->Bets+4)->l_xml=dlg_ch11;
		if(dlg_ch11)dlgc_ch11.SetWindowTextW(L"YES");else dlgc_ch11.SetWindowTextW(L"NO");break;
	case IDC_CHECK12:(ptrIGA->Bets+5)->l_xml=dlg_ch12;
		if(dlg_ch12)dlgc_ch12.SetWindowTextW(L"YES");else dlgc_ch12.SetWindowTextW(L"NO");break;
	case IDC_CHECK41:(ptrIGA->Bets+6)->l_xml=dlg_ch41;
		if(dlg_ch41)dlgc_ch41.SetWindowTextW(L"YES");else dlgc_ch41.SetWindowTextW(L"NO");break;
	case IDC_CHECK42:(ptrIGA->Bets+7)->l_xml=dlg_ch42;
		if(dlg_ch42)dlgc_ch42.SetWindowTextW(L"YES");else dlgc_ch42.SetWindowTextW(L"NO");break;

		/////////[ADD TEMP CHAM]////////////////
	case IDC_CHECK13:ptrIGA->Bets->add_ch=dlg_ch13;break;
	case IDC_CHECK14:(ptrIGA->Bets+1)->add_ch=dlg_ch14;break;
	case IDC_CHECK15:(ptrIGA->Bets+2)->add_ch=dlg_ch15;break;
	case IDC_CHECK16:(ptrIGA->Bets+3)->add_ch=dlg_ch16;break;
	case IDC_CHECK17:(ptrIGA->Bets+4)->add_ch=dlg_ch17;break;
	case IDC_CHECK18:(ptrIGA->Bets+5)->add_ch=dlg_ch18;break;
	case IDC_CHECK43:(ptrIGA->Bets+6)->add_ch=dlg_ch43;break;
	case IDC_CHECK47:(ptrIGA->Bets+7)->add_ch=dlg_ch47;break;
		/////////[ADD TEMP TEAM]////////////////
	case IDC_CHECK19:ptrIGA->Bets->add_t=dlg_ch19;break;
	case IDC_CHECK20:(ptrIGA->Bets+1)->add_t=dlg_ch20;break;
	case IDC_CHECK21:(ptrIGA->Bets+2)->add_t=dlg_ch21;break;
	case IDC_CHECK22:(ptrIGA->Bets+3)->add_t=dlg_ch22;break;
	case IDC_CHECK23:(ptrIGA->Bets+4)->add_t=dlg_ch23;break;
	case IDC_CHECK24:(ptrIGA->Bets+5)->add_t=dlg_ch24;break;
	case IDC_CHECK44:(ptrIGA->Bets+6)->add_t=dlg_ch44;break;
	case IDC_CHECK48:(ptrIGA->Bets+7)->add_t=dlg_ch48;break;
		/////////[ADD TEMP KC]////////////////
	case IDC_CHECK25:ptrIGA->Bets->add_kc=dlg_ch25;break;
	case IDC_CHECK26:(ptrIGA->Bets+1)->add_kc=dlg_ch26;break;
	case IDC_CHECK27:(ptrIGA->Bets+2)->add_kc=dlg_ch27;break;
	case IDC_CHECK28:(ptrIGA->Bets+3)->add_kc=dlg_ch28;break;
	case IDC_CHECK29:(ptrIGA->Bets+4)->add_kc=dlg_ch29;break;
	case IDC_CHECK30:(ptrIGA->Bets+5)->add_kc=dlg_ch30;break;
	case IDC_CHECK45:(ptrIGA->Bets+6)->add_kc=dlg_ch45;break;
	case IDC_CHECK49:(ptrIGA->Bets+7)->add_kc=dlg_ch49;break;
		///////////////[SF]/////////////////////
	case IDC_CHECK31:ptrIGA->Bets->SF=dlg_ch31;
		if(dlg_ch31)dlgc_ch31.SetWindowTextW(L"ON");else dlgc_ch31.SetWindowTextW(L"OFF");break;
	case IDC_CHECK32:(ptrIGA->Bets+1)->SF=dlg_ch32;
		if(dlg_ch32)dlgc_ch32.SetWindowTextW(L"ON");else dlgc_ch32.SetWindowTextW(L"OFF");break;
	case IDC_CHECK33:(ptrIGA->Bets+2)->SF=dlg_ch33;
		if(dlg_ch33)dlgc_ch33.SetWindowTextW(L"ON");else dlgc_ch33.SetWindowTextW(L"OFF");break;
	case IDC_CHECK34:(ptrIGA->Bets+3)->SF=dlg_ch34;
		if(dlg_ch34)dlgc_ch34.SetWindowTextW(L"ON");else dlgc_ch34.SetWindowTextW(L"OFF");break;
	case IDC_CHECK35:(ptrIGA->Bets+4)->SF=dlg_ch35;
		if(dlg_ch35)dlgc_ch35.SetWindowTextW(L"ON");else dlgc_ch35.SetWindowTextW(L"OFF");break;
	case IDC_CHECK36:(ptrIGA->Bets+5)->SF=dlg_ch36;
		if(dlg_ch36)dlgc_ch36.SetWindowTextW(L"ON");else dlgc_ch36.SetWindowTextW(L"OFF");break;
	case IDC_CHECK46:(ptrIGA->Bets+6)->SF=dlg_ch46;
		if(dlg_ch46)dlgc_ch46.SetWindowTextW(L"ON");else dlgc_ch46.SetWindowTextW(L"OFF");break;
	case IDC_CHECK50:(ptrIGA->Bets+7)->SF=dlg_ch50;
		if(dlg_ch50)dlgc_ch50.SetWindowTextW(L"ON");else dlgc_ch50.SetWindowTextW(L"OFF");break;
		///////////////////////////////////////
	case IDC_CHECK37:(ptrIGA->Filter).v2=dlg_ch37;break;
	case IDC_CHECK38:(ptrIGA->Filter).v3=dlg_ch38;break;
	default:return;
	}
	ptrIGA->Save_Inf_Ga();
}
void CGA2Dlg::set_I_GA()
{
	bool TEMP;
	/////////////[BET-%]//////////////
	dlg_ch1=1&ptrIGA->Bets->btp;///////ID_B: 1
	dlg_ed1.Format(L"%.2f",ptrIGA->Bets->bt);
	dlg_ch2=1&((ptrIGA->Bets+1)->btp);///ID_B: 2
	dlg_ed2.Format(L"%.2f",(ptrIGA->Bets+1)->bt);
	dlg_ch3=1&(ptrIGA->Bets+2)->btp;///ID_B: 3
	dlg_ed3.Format(L"%.2f",(ptrIGA->Bets+2)->bt);
	dlg_ch4=1&(ptrIGA->Bets+3)->btp;///ID_B: 4
	dlg_ed4.Format(L"%.2f",(ptrIGA->Bets+3)->bt);
	dlg_ch5=1&(ptrIGA->Bets+4)->btp;///ID_B: 5
	dlg_ed5.Format(L"%.2f",(ptrIGA->Bets+4)->bt);
	dlg_ch6=1&(ptrIGA->Bets+5)->btp;///ID_B: 6
	dlg_ed6.Format(L"%.2f",(ptrIGA->Bets+5)->bt);
	dlg_ch39=1&(ptrIGA->Bets+6)->btp;///ID_B: 7
	dlg_ed12.Format(L"%.2f",(ptrIGA->Bets+6)->bt);
	dlg_ch40=1&(ptrIGA->Bets+7)->btp;///ID_B: 8
	dlg_ed13.Format(L"%.2f",(ptrIGA->Bets+7)->bt);
	///////////[LOAD XML]/////////////////
	dlg_ch7=1&(ptrIGA->Bets->l_xml);if(dlg_ch7)dlgc_ch7.SetWindowTextW(L"YES");
	dlg_ch8=1&(ptrIGA->Bets+1)->l_xml;if(dlg_ch8)dlgc_ch8.SetWindowTextW(L"YES");
	dlg_ch9=1&(ptrIGA->Bets+2)->l_xml;if(dlg_ch9)dlgc_ch9.SetWindowTextW(L"YES");
	dlg_ch10=1&(ptrIGA->Bets+3)->l_xml;if(dlg_ch10)dlgc_ch10.SetWindowTextW(L"YES");
	dlg_ch11=1&(ptrIGA->Bets+4)->l_xml;if(dlg_ch11)dlgc_ch11.SetWindowTextW(L"YES");
	dlg_ch12=1&(ptrIGA->Bets+5)->l_xml;if(dlg_ch12)dlgc_ch12.SetWindowTextW(L"YES");
	dlg_ch41=1&(ptrIGA->Bets+6)->l_xml;if(dlg_ch41)dlgc_ch41.SetWindowTextW(L"YES");
	dlg_ch42=1&(ptrIGA->Bets+7)->l_xml;if(dlg_ch42)dlgc_ch42.SetWindowTextW(L"YES");
	/////////[ADD TEMP CHAM]////////////////
	dlg_ch13=1&ptrIGA->Bets->add_ch;
	dlg_ch14=1&(ptrIGA->Bets+1)->add_ch;
	dlg_ch15=1&(ptrIGA->Bets+2)->add_ch;
	dlg_ch16=1&(ptrIGA->Bets+3)->add_ch;
	dlg_ch17=1&(ptrIGA->Bets+4)->add_ch;
	dlg_ch18=1&(ptrIGA->Bets+5)->add_ch;
	dlg_ch43=1&(ptrIGA->Bets+6)->add_ch;
	dlg_ch47=1&(ptrIGA->Bets+7)->add_ch;
	/////////[ADD TEMP TEAM]////////////////
	dlg_ch19=1&ptrIGA->Bets->add_t;
	dlg_ch20=1&(ptrIGA->Bets+1)->add_t;
	dlg_ch21=1&(ptrIGA->Bets+2)->add_t;
	dlg_ch22=1&(ptrIGA->Bets+3)->add_t;
	dlg_ch23=1&(ptrIGA->Bets+4)->add_t;
	dlg_ch24=1&(ptrIGA->Bets+5)->add_t;
	dlg_ch44=1&(ptrIGA->Bets+6)->add_t;
	dlg_ch48=1&(ptrIGA->Bets+7)->add_t;
	/////////[ADD TEMP KC]////////////////
	dlg_ch25=1&ptrIGA->Bets->add_kc;
	dlg_ch26=1&(ptrIGA->Bets+1)->add_kc;
	dlg_ch27=1&(ptrIGA->Bets+2)->add_kc;
	dlg_ch28=1&(ptrIGA->Bets+3)->add_kc;
	dlg_ch29=1&(ptrIGA->Bets+4)->add_kc;
	dlg_ch30=1&(ptrIGA->Bets+5)->add_kc;
	dlg_ch45=1&(ptrIGA->Bets+6)->add_kc;
	dlg_ch49=1&(ptrIGA->Bets+7)->add_kc;
	///////////////[SF]/////////////////////
	dlg_ch31=1&ptrIGA->Bets->SF;if(dlg_ch31)dlgc_ch31.SetWindowTextW(L"ON");
	dlg_ch32=1&(ptrIGA->Bets+1)->SF;if(dlg_ch32)dlgc_ch32.SetWindowTextW(L"ON");
	dlg_ch33=1&(ptrIGA->Bets+2)->SF;if(dlg_ch33)dlgc_ch33.SetWindowTextW(L"ON");
	dlg_ch34=1&(ptrIGA->Bets+3)->SF;if(dlg_ch34)dlgc_ch34.SetWindowTextW(L"ON");
	dlg_ch35=1&(ptrIGA->Bets+4)->SF;if(dlg_ch35)dlgc_ch35.SetWindowTextW(L"ON");
	dlg_ch36=1&(ptrIGA->Bets+5)->SF;if(dlg_ch36)dlgc_ch36.SetWindowTextW(L"ON");
	dlg_ch46=1&(ptrIGA->Bets+6)->SF;if(dlg_ch46)dlgc_ch35.SetWindowTextW(L"ON");
	dlg_ch50=1&(ptrIGA->Bets+7)->SF;if(dlg_ch50)dlgc_ch36.SetWindowTextW(L"ON");
	////////////////////////////////////////
	dlg_ch37=1&ptrIGA->Filter.v2;
	dlg_ch38=1&ptrIGA->Filter.v3;
	dlg_ed7.Format(L"%.1f",(ptrIGA->Filter).fr_h);
	dlg_ed8.Format(L"%.1f",(ptrIGA->Filter).to_h);
	dlg_ed9.Format(L"%.2f",(ptrIGA->Filter).vt);
	dlg_ed10.Format(L"%.2f",(ptrIGA->Filter).usd);
	dlg_ed11.Format(L"%.2f",(ptrIGA->Filter).rur);
	UpdateData(false);
}

void CGA2Dlg::OnBnClickedCommand2()
{
	// TODO: Add your control notification handler code here
	/*if(!ptrBET) ptrBET=new bet(LV3,ptrIGA,true);
	if(!XmlF) XmlF =new XmlFeed(ptrBET);
	
	XmlF->DownloadX();
	com_c1.EnableWindow();*/
	
	CWinThread* myWinThread = AfxBeginThread(Download_Line,this);
	
}

UINT Download_Line(LPVOID LV)
{
	CGA2Dlg *lp=(CGA2Dlg*)LV;
	lp->com_c2.EnableWindow(false);
	if(!lp->ptrBET) lp->ptrBET=new bet(lp->LV3,lp->ptrIGA,true);
	if(!lp->XmlF) lp->XmlF =new XmlFeed(lp->ptrBET);
	lp->XmlF->DownloadX();
	MessageBeep(MB_ICONINFORMATION );
	lp->com_c2.EnableWindow();
	lp->com_c1.EnableWindow();
	lp->b_base.EnableWindow();
	return 0;
}


void CGA2Dlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	if(XmlF)
	{
		BASE_INTERFACE *BI=new BASE_INTERFACE(XmlF, XmlF->BASE_I,ptrBET);//Patuhani stexcum
		BI->Create(IDD_DIALOG2,this);
		for(int i=0;i<N_BETS;i++)
		{
			BI->combo_b1.AddString(CString(ptrBET->bet_name(i+1)));
			BI->combo_b2.AddString(CString(ptrBET->bet_name(i+1)));
		}
		for(int i=0;i<ptrBET->n_sport;i++)
		{
			BI->combo_s.AddString(CString(ptrBET->get_sport_name(i+1,1)));
		}
		BI->combo_s.SelectString(1,CString(ptrBET->get_sport_name(1,1)));
		/////////////////////////////////////////
		BI->combo_DA1.AddString(L"ALL TIME");
		BI->combo_DA2.AddString(L"ALL TIME");

		BI->combo_DA1.AddString(L"30 Minutes");
		BI->combo_DA2.AddString(L"30 Minutes");

		BI->combo_DA1.AddString(L"1  Houre");
		BI->combo_DA2.AddString(L"1  Houre");

		BI->combo_DA1.AddString(L"3  Houre");
		BI->combo_DA2.AddString(L"3  Houre");

		BI->combo_DA1.AddString(L"6  Houre");
		BI->combo_DA2.AddString(L"6  Houre");

		BI->combo_DA1.AddString(L"12 Houre");
		BI->combo_DA2.AddString(L"12 Houre");

		BI->combo_DA1.AddString(L"24 Houre");
		BI->combo_DA2.AddString(L"24 Houre");
		/////////////////////////////////////////
		CRect rect;
		CListCtrl* TLC;
		
		for(int i=0;i<2;i++)
		{
			if(!i) TLC=&(BI->listc1);
			else TLC=&(BI->listc2);
			TLC->GetClientRect(rect);
			TLC->InsertColumn(0, L"HOME TEAM", LVCFMT_LEFT, rect.Width()*0.35, 0);
			TLC->InsertColumn(1, L"AVAY TEAM", LVCFMT_LEFT, rect.Width()*0.35, 1);
			TLC->InsertColumn(2, L"DATE GAME", LVCFMT_LEFT, rect.Width()*0.3, 2);
			
			DWORD ExStyle = TLC->GetExtendedStyle();
			ExStyle |= LVS_EX_FULLROWSELECT;
			TLC->SetExtendedStyle(ExStyle);
		}
		UpdateData(false);
		
		//ADD FONTS
		BI->ShowWindow(SW_SHOW);
		//BI->StartValue();
	}
}
