
// GA2Dlg.h : header file
//

#pragma once

#include "bet.h"
#include "INTERFACE_GA.h"
#include "XmlFeed.h"
//#include "GA2Dlg.h"
#include "afxwin.h"

// CGA2Dlg dialog
class CGA2Dlg : public CDialogEx
{
// Construction
public:
	CGA2Dlg(CWnd* pParent = NULL);	// standard constructor
	
// Dialog Data
	enum { IDD = IDD_GA2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	
public:
	const int N_BETS;/////////////////KANTORANERI QANAK@->(.cpp)////////
	afx_msg void OnBnClickedCommand1();
	
	void creatlist1(sbor_ALL);
	void creatlist2(sbor_ALL);
	bet* ptrBET;
	CFont* T_FONT;
	CFont* T_FONT2;
	afx_msg void OnLbnSelchangeList2();
	CListBox LV;

	afx_msg void OnLbnSelchangeList1();
	int NLV,NLV2;
	CListBox LV2;
	CString stat1;
	afx_msg void OnLbnSelchangeList22();
	CStatic c_stat2;
	CString stat2;
	CStatic c_stat1;
	CListBox LV3;
	CString str_LV3;
	Interface_Ga *ptrIGA;
	XmlFeed* XmlF;
	afx_msg void OnBnClickedCheckBox(UINT nID);
	afx_msg void OnBnClickedEditC(UINT nID);
	void set_I_GA();
	BOOL dlg_ch1;
	BOOL dlg_ch2;
	BOOL dlg_ch3;
	BOOL dlg_ch4;
	BOOL dlg_ch5;
	BOOL dlg_ch6;
	BOOL dlg_ch7;
	BOOL dlg_ch8;
	BOOL dlg_ch9;
	BOOL dlg_ch10;
	BOOL dlg_ch11;
	BOOL dlg_ch12;
	BOOL dlg_ch13;
	BOOL dlg_ch14;
	BOOL dlg_ch15;
	BOOL dlg_ch16;
	BOOL dlg_ch17;
	BOOL dlg_ch18;
	BOOL dlg_ch19;
	BOOL dlg_ch20;
	BOOL dlg_ch21;
	BOOL dlg_ch22;
	BOOL dlg_ch23;
	BOOL dlg_ch24;
	BOOL dlg_ch25;
	BOOL dlg_ch26;
	BOOL dlg_ch27;
	BOOL dlg_ch28;
	BOOL dlg_ch29;
	BOOL dlg_ch30;
	BOOL dlg_ch31;
	BOOL dlg_ch32;
	BOOL dlg_ch33;
	BOOL dlg_ch34;
	BOOL dlg_ch35;
	BOOL dlg_ch36;
	BOOL dlg_ch37;
	BOOL dlg_ch38;
	
	CString dlg_ed1;
	CString dlg_ed2;
	CString dlg_ed3;
	CString dlg_ed4;
	CString dlg_ed5;
	CString dlg_ed6;
	CString dlg_ed7;
	CString dlg_ed8;
	CString dlg_ed9;
	CString dlg_ed10;
	CString dlg_ed11;
	
	CButton dlgc_ch7;
	CButton dlgc_ch8;
	CButton dlgc_ch9;
	CButton dlgc_ch10;
	CButton dlgc_ch11;
	CButton dlgc_ch12;
	CButton dlgc_ch31;
	CButton dlgc_ch32;
	CButton dlgc_ch33;
	CButton dlgc_ch34;
	CButton dlgc_ch35;
	CButton dlgc_ch36;
	afx_msg void OnBnClickedCommand2();
	CButton com_c1;
	
	CButton com_c2;
	CString dlg_ed12;
	CString dlg_ed13;
	BOOL dlg_ch39;
	BOOL dlg_ch40;
	BOOL dlg_ch41;
	BOOL dlg_ch42;
	BOOL dlg_ch43;
	BOOL dlg_ch44;
	BOOL dlg_ch45;
	BOOL dlg_ch46;
	BOOL dlg_ch47;
	BOOL dlg_ch48;
	BOOL dlg_ch49;
	BOOL dlg_ch50;
	CButton dlgc_ch41;
	CButton dlgc_ch42;
	CButton dlgc_ch46;
	CButton dlgc_ch50;
	afx_msg void OnBnClickedButton1();
	CButton b_base;
};
