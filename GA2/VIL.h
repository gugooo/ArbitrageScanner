#pragma once
#include "afxwin.h"
#include "bet.h"

// VIL dialog

class VIL : public CDialogEx
{
	DECLARE_DYNAMIC(VIL)

public:
	VIL(bet*,Interface_Ga*,CWnd* pParent = NULL);   // standard constructor
	
	virtual ~VIL();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void CVIL(int N=0,bool OT=true);
	float* v2_r(int*,float*,bool*);
	bet *VI_CBet;
	Interface_Ga* V_IGA;
	v2* VIL2;
	v3* VIL3;
	CString vd_stat1;
	CStatic vdc_stat1;
	CStatic vdc_stat2;
	CString vd_stat2;
	CString vd_stat3;
	CStatic vdc_stat3;
	CStatic vdc_stat4;
	CString vd_stat4;
	CStatic vdc_stat6;
	CString vd_stat6;
	CStatic vdc_stat7;
	CString vd_stat7;
	CStatic vdc_stat8;
	CString vd_stat8;
	CStatic vdc_stat9;
	CString vd_stat9;
	CStatic vdc_stat10;
	CStatic vdc_stat11;
	CStatic vdc_stat14;
	CStatic vdc_p15;
	CStatic vdc_p16;
	CStatic vdc_p17;
	CStatic vdc_p18;
	CStatic vdc_p19;
	CStatic vdc_p20;
	CStatic vdc_p21;
	CEdit vdc_edit3;
	CEdit vdc_edit6;
	CEdit vdc_edit9;
	CButton vdc_ch3;
	CButton vdc_radio3;
	CString vd_edit1;
	CString vd_edit2;
	CString vd_edit4;
	CString vd_edit5;
	CString vd_edit7;
	CString vd_edit8;
	CEdit vdc_edit1;
	CEdit vdc_edit2;
	CString vd_stat12;
	CStatic vdc_stat12;
	CStatic vdc_stat13;
	CString vd_stat13;
	CEdit vdc_edit7;
	CEdit vdc_edit8;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit7();
	afx_msg void OnEnChangeEdit8();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	CString vd_stat23;
	CStatic vdc_stat23;
	CButton vdc_but1;
	CButton vdc_but2;
	BOOL vd_bu1;
	BOOL vd_bu2;
	BOOL vd_bu3;
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
};
