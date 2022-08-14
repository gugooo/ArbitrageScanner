// VIL.cpp : implementation file
//
//#include "bet.h"
#include "stdafx.h"
#include "GA2.h"
#include "VIL.h"
#include "afxdialogex.h"


// VIL dialog

IMPLEMENT_DYNAMIC(VIL, CDialogEx)

VIL::VIL(bet* pB,Interface_Ga* pI,CWnd* pParent /*=NULL*/)
	: CDialogEx(VIL::IDD, pParent)
	, vd_stat1(_T(""))
	, vd_stat2(_T(""))
	, vd_stat3(_T(""))
	, vd_stat4(_T(""))
	, vd_stat6(_T(""))
	, vd_stat7(_T(""))
	, vd_stat8(_T(""))
	, vd_stat9(_T(""))
	
	, vd_edit1(_T(""))
	, vd_edit2(_T(""))
	, vd_edit4(_T(""))
	, vd_edit5(_T(""))
	, vd_edit7(_T(""))
	, vd_edit8(_T(""))
	, vd_stat12(_T(""))
	, vd_stat13(_T(""))
	, vd_stat23(_T(""))
	
	, vd_bu1(FALSE)
	, vd_bu2(FALSE)
	, vd_bu3(FALSE)
{
	VI_CBet=pB;
	V_IGA=pI;
	VIL2=NULL;
	VIL3=NULL;
}

VIL::~VIL()
{
}

void VIL::CVIL(int N,bool OT)
{
	float kc1,kc2,kc3,N1,N2,E1,E2;
	CString BLOK;
	if(VIL2)
	{
////////////// v2_r(int *Status,float *val,bool *fl) /////////////|
//|	************************* IN ******************************	|/|
//|	int* 0[Status] 1[ID_BET1] 2[ID_BET2] 3[ID_KC1] 4[ID_KC2]	|/|
//|	float* 0[kc1] 1[B1%] 2[N1] 3[kc2] 4[B2%] 5[N2]				|/|
//|	bool*  0[Lkc1] 1[Lkc2] 2[S1%] 3[S2%] 4[1-2]		(1=true)	|/|
//|	[Lkc]-> LAY=true, BACK=false, 1=(vigrish%), 0=(stavka%)		|/|
//|	************************* OUT *****************************	|/|
//|	float* 0[V%] 1[N1] 2[LBl1] 3[E1] 4[N2] 5[LBl2] 6[E2]		|/|
//////////////////////////////////////////////////////////////////|		
		int Status[5];	float val[6];	bool fl[5];//IN
		float *ri;//OUT	
////////////////////////////////////////////[IN]//////////////////////////////////////////////
		Status[0]=N;
		Status[1]=VIL2->KC1->id_bet_name;
		Status[2]=VIL2->KC2->id_bet_name;
		Status[3]=VIL2->KC1->TKC->id_kc;
		Status[4]=VIL2->KC2->TKC->id_kc;
		fl[0]=VIL2->LAY1;
		fl[1]=VIL2->LAY2;
		UpdateData();
		fl[2]=vd_bu1;
		fl[3]=vd_bu2;
		fl[4]=OT;
		val[0]=(float)_wtof(vd_edit1);
		val[1]=(float)_wtof(vd_edit4);
		val[2]=(float)_wtof(vd_edit7);
		val[3]=(float)_wtof(vd_edit2);
		val[4]=(float)_wtof(vd_edit5);
		val[5]=(float)_wtof(vd_edit8);
/////////////////////////////////[CHANGE]////////////////////////////////////////////////////////
		if(N)
		{
			ri=v2_r(Status,val,fl);
		}
		else
		{
			val[1]=(V_IGA->Bets+Status[1]-1)->bt;
			val[4]=(V_IGA->Bets+Status[2]-1)->bt;
			fl[2]=(V_IGA->Bets+Status[1]-1)->btp;
			fl[3]=(V_IGA->Bets+Status[2]-1)->btp;
			val[0]=VIL2->KC1->kc;
			if(VIL2->LAY1)val[0]=-val[0];
			val[3]=VIL2->KC2->kc;
			if(VIL2->LAY2)val[3]=-val[3];
			ri=v2_r(Status,val,fl);
			vd_bu1=fl[2];
			vd_bu2=fl[3];
			vd_edit1.Format(L"%.2f",val[0]);
			vd_edit2.Format(L"%.2f",val[3]);
			vd_edit4.Format(L"%.2f",val[1]);
			vd_edit5.Format(L"%.2f",val[4]);
			UpdateData(false);
		}
/////////////////////////////////////////////[OUT]///////////////////////////////////////////////
		if(VIL2->LAY1){BLOK.Format(L"%.2f",*(ri+2)); vdc_but1.SetWindowTextW(BLOK);}
		if(VIL2->LAY2){BLOK.Format(L"%.2f",*(ri+5)); vdc_but2.SetWindowTextW(BLOK);}
		if(N!=-1)
		{
			vd_edit7.Format(L"%.2f",*(ri+1));
			vd_edit8.Format(L"%.2f",*(ri+4));
		}
		vd_stat12.Format(L"%.2f",*(ri+3));
		vd_stat13.Format(L"%.2f",*(ri+6));
		vd_stat23.Format(L"%.2f %%",*ri);
		UpdateData(false);
///////////////////////////////////////////////////////////////////////////////////////////////
	}
	if(VIL3)
	{

	}
}

float* VIL::v2_r(int *Status,float *val,bool *fl)
{
//////////////////////////////////////////////////////////////////|
//|	************************* IN ******************************	|/|
//|	int* 0[Status] 1[ID_BET1] 2[ID_BET2] 3[ID_KC1] 4[ID_KC2]	|/|
//|	float* 0[kc1] 1[B1%] 2[N1] 3[kc2] 4[B2%] 5[N2]				|/|
//|	bool*  0[Lkc1] 1[Lkc2] 2[S1%] 3[S2%] 4[1-2]		(1=true)	|/|
//|	[Lkc]-> LAY=true, BACK=false, 1=(vigrish%), 0=(stavka%)		|/|
//|	************************* OUT *****************************	|/|
//|	float* 0[V%] 1[N1] 2[LBl1] 3[E1] 4[N2] 5[LBl1] 6[E2]		|/|
//////////////////////////////////////////////////////////////////|
	float *resp=new float[6];
	bool* twoB;
	bool two=false;
	if(*(Status+1)==1 && *(Status+2)==1)/*!!!ID_BETFAIR=1!!!*/
	{
		twoB=VI_CBet->Market_Bf_Kc(*(Status+3),*(Status+4));
		if(twoB) if( *twoB && *(twoB+1) ) two=true;
	}
	float kc1,Bt1,N1,E1,kc2,Bt2,N2,E2;
	bool lay1,lay2,S1,S2;
	if(*(fl+4))
	{
		kc1=*val;		Bt1=*(val+1);	N1=*(val+2);	lay1=*fl;		S1=*(fl+2);
		kc2=*(val+3);	Bt2=*(val+4);	N2=*(val+5);	lay2=*(fl+1);	S2=*(fl+3);
	}
	else
	{
		kc1=*(val+3);	Bt1=*(val+4);	N1=*(val+5);	lay1=*(fl+1);	S1=*(fl+3);
		kc2=*val;		Bt2=*(val+1);	N2=*(val+2);	lay2=*fl;		S2=*(fl+2);
	}
	/////////////LAY to BACK/////////////////////////////////////////////////
	if(lay1){ N1=N1*(kc1-1); kc1=kc1/(kc1-1); }//LAY1->BACK1
	if(lay2){ N2=N2*(kc2-1); kc2=kc2/(kc2-1); }//LAY2->BACK2
	/////////////////////////////////////////////////////////////////////////
	if(S1 && !S2) kc1=kc1*(1+Bt1/100)-Bt1/100;//KC1<-B%
	if(!S1 && S2) kc2=kc2*(1+Bt2/100)-Bt2/100;//KC2<-B%
	if(S1 && S2 && !two)
	{
		kc1=kc1*(1+Bt1/100)-Bt1/100;//KC1<-B%
		kc2=kc2*(1+Bt2/100)-Bt2/100;//KC2<-B%
	}
	/////////////////////////////////////////////////////////////////////////
	const int Ob=100;//$100
	switch(*Status)
	{
	case 0://
		if(kc1<1 || kc2<1)return NULL;
		N1=Ob*kc2/(kc1+kc2);
		N2=N1*kc1/kc2;
		break;
	case 1:
		N2=N1*kc1/kc2;
		break;
	}
	E1=N1*(kc1-1)-N2;
	E2=N2*(kc2-1)-N1;
	*resp=100*(kc1*kc2-kc1-kc2)/(kc1+kc2);
	if(!*(fl+4))
	{
		float FT[4]; bool BT[2];
		FT[0]=kc1;	FT[1]=Bt1;	FT[2]=N1;	FT[3]=E1;	BT[0]=lay1;	BT[1]=S1;
		kc1=kc2;	Bt1=Bt2;	N1=N2;		E1=E2;		lay1=lay2;	S1=S2;
		kc2=FT[0];	Bt2=FT[1];	N2=FT[2];	E2=FT[3];	lay2=BT[0];	S2=BT[1];
	}
	////////////////////////////////////////////////
	if(two)
	{
		if(E1>0)E1=E1*(1+Bt1/100);
		if(E2>0)E2=E2*(1+Bt2/100);
	}
	if(!S1){	E1+=N1*Bt1/100; E2+=N1*Bt1/100;}
	if(!S2){	E1+=N2*Bt2/100; E2+=N2*Bt2/100;}
	/////////////////////////////////////////////////
	if(lay1){ N1=N1*(kc1-1);if(!two && *(fl+2)) N1=N1*100/(100+Bt1); kc1=(*val); }//N1->LN1, if two=false -> LN1+B%
	if(lay2){ N2=N2*(kc2-1);if(!two && *(fl+3)) N2=N2*100/(100+Bt2); kc2=(*(val+3)); }//N2->LN2, if two=false -> LN2+B%
	////////////////////////////////////////////////
	*(resp+1)=N1;
	if(*fl) *(resp+2)=N1*(kc1-1); else *(resp+2)=0;
	*(resp+3)=E1;
	*(resp+4)=N2;
	if(*(fl+1)) *(resp+5)=N2*(kc2-1); else *(resp+5)=0;
	*(resp+6)=E2;

	return resp;
}

void VIL::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC1, vd_stat1);
	DDX_Control(pDX, IDC_STATIC1, vdc_stat1);
	DDX_Control(pDX, IDC_STATIC4, vdc_stat2);
	DDX_Text(pDX, IDC_STATIC4, vd_stat2);
	DDX_Text(pDX, IDC_STATIC3, vd_stat3);
	DDX_Control(pDX, IDC_STATIC3, vdc_stat3);
	DDX_Control(pDX, IDC_STATIC5, vdc_stat4);
	DDX_Text(pDX, IDC_STATIC5, vd_stat4);
	DDX_Control(pDX, IDC_STATIC6, vdc_stat6);
	DDX_Text(pDX, IDC_STATIC6, vd_stat6);
	DDX_Control(pDX, IDC_STATIC7, vdc_stat7);
	DDX_Text(pDX, IDC_STATIC7, vd_stat7);
	DDX_Control(pDX, IDC_STATIC8, vdc_stat8);
	DDX_Text(pDX, IDC_STATIC8, vd_stat8);
	DDX_Control(pDX, IDC_STATIC9, vdc_stat9);
	DDX_Text(pDX, IDC_STATIC9, vd_stat9);
	DDX_Control(pDX, IDC_STATIC10, vdc_stat10);
	DDX_Control(pDX, IDC_STATIC11, vdc_stat11);
	DDX_Control(pDX, IDC_STATIC14, vdc_stat14);
	DDX_Control(pDX, IDC_STATIC15, vdc_p15);
	DDX_Control(pDX, IDC_STATIC16, vdc_p16);
	DDX_Control(pDX, IDC_STATIC17, vdc_p17);
	DDX_Control(pDX, IDC_STATIC18, vdc_p18);
	DDX_Control(pDX, IDC_STATIC19, vdc_p19);
	DDX_Control(pDX, IDC_STATIC20, vdc_p20);
	DDX_Control(pDX, IDC_STATIC21, vdc_p21);
	DDX_Control(pDX, IDC_EDIT3, vdc_edit3);
	DDX_Control(pDX, IDC_EDIT6, vdc_edit6);
	DDX_Control(pDX, IDC_EDIT9, vdc_edit9);
	DDX_Control(pDX, IDC_CHECK3, vdc_ch3);
	DDX_Control(pDX, IDC_RADIO3, vdc_radio3);
	DDX_Text(pDX, IDC_EDIT1, vd_edit1);
	DDX_Text(pDX, IDC_EDIT2, vd_edit2);
	DDX_Text(pDX, IDC_EDIT4, vd_edit4);
	DDX_Text(pDX, IDC_EDIT5, vd_edit5);
	DDX_Text(pDX, IDC_EDIT7, vd_edit7);
	DDX_Text(pDX, IDC_EDIT8, vd_edit8);
	DDX_Control(pDX, IDC_EDIT1, vdc_edit1);
	DDX_Control(pDX, IDC_EDIT2, vdc_edit2);
	DDX_Text(pDX, IDC_STATIC12, vd_stat12);
	DDX_Control(pDX, IDC_STATIC12, vdc_stat12);
	DDX_Control(pDX, IDC_STATIC13, vdc_stat13);
	DDX_Text(pDX, IDC_STATIC13, vd_stat13);
	DDX_Control(pDX, IDC_EDIT7, vdc_edit7);
	DDX_Control(pDX, IDC_EDIT8, vdc_edit8);
	DDX_Text(pDX, IDC_STATIC23, vd_stat23);
	DDX_Control(pDX, IDC_STATIC23, vdc_stat23);
	DDX_Control(pDX, IDC_RADIO1, vdc_but1);

	DDX_Control(pDX, IDC_RADIO2, vdc_but2);
	DDX_Check(pDX, IDC_CHECK1, vd_bu1);
	DDX_Check(pDX, IDC_CHECK2, vd_bu2);
	DDX_Check(pDX, IDC_CHECK3, vd_bu3);
}


BEGIN_MESSAGE_MAP(VIL, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &VIL::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &VIL::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT7, &VIL::OnEnChangeEdit7)
	ON_EN_CHANGE(IDC_EDIT8, &VIL::OnEnChangeEdit8)
	ON_BN_CLICKED(IDC_RADIO1, &VIL::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &VIL::OnBnClickedRadio2)
	ON_EN_CHANGE(IDC_EDIT4, &VIL::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, &VIL::OnEnChangeEdit5)
	ON_BN_CLICKED(IDC_CHECK1, &VIL::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &VIL::OnBnClickedCheck2)
END_MESSAGE_MAP()


// VIL message handlers


void VIL::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CVIL(-1);
}


void VIL::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CVIL(-1,false);
}


void VIL::OnEnChangeEdit7()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CVIL(-1);
}


void VIL::OnEnChangeEdit8()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CVIL(-1,false);
}


void VIL::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
	CVIL(1);
}


void VIL::OnBnClickedRadio2()
{
	// TODO: Add your control notification handler code here
	CVIL(1,false);
}


void VIL::OnEnChangeEdit4()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CVIL(-1);
}


void VIL::OnEnChangeEdit5()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CVIL(-1,false);
}


void VIL::OnBnClickedCheck1()
{
	// TODO: Add your control notification handler code here
	CVIL(-1);
}


void VIL::OnBnClickedCheck2()
{
	// TODO: Add your control notification handler code here
	CVIL(-1,false);
}
