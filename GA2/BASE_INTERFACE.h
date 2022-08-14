#pragma once
#ifndef BASE_INTERFACE_H
#define BASE_INTERFACE_H

#include "XmlFeed.h"
#include "bet.h"
#include "afxwin.h"
#include "ColorListBox.h"
#include "afxcmn.h"
// BASE_INTERFACE dialog



class BASE_INTERFACE : public CDialogEx
{
	DECLARE_DYNAMIC(BASE_INTERFACE)

public:
	BASE_INTERFACE(XmlFeed* XmlF, BI_BET *B_I, bet* p_BET,CWnd* pParent = NULL);   // standard constructor
	virtual ~BASE_INTERFACE();
	BI_BET* BASE_I;
	BI_BET** ALL_SPORTS;
// Dialog Data
	enum { IDD = IDD_DIALOG2 };
	bet* PB;
	cham_base** CH_BASE;
	p_t_b** T_BASE;//BASE TEAMS

	int* IDS;//ID_CH1, ID_CH2, ID_T11, ID_T12, ID_T21, ID_T22
	int* POSB;//posB1, posB2
	char** NAMEB;//CH_N1, CH_N2, T_N11, T_N12, T_N21, T_N22
	int* data_T;//nshvac xaxi jam@
	bool L12;//list1=true, list2=false;
	BI_BET* B_1;
	BI_BET* B_2;
	BI_CH* CH_1;
	BI_CH* CH_2;
	BI_G* G1;
	BI_G* G2;
	bool NTeam;
	bool AT_ON;
	int NEWCH;//0-nor chName chka, 1-arachin@ nora, 2-ekrord@ nora, 3-erkusne nor en
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	XmlFeed* XF;
	DECLARE_MESSAGE_MAP()
public:
	CComboBox combo_b1;
	CComboBox combo_b2;
	CComboBox combo_DA1;
	CComboBox combo_DA2;
	afx_msg void OnCbnSelendokCombo2();
	CColorListBox LB1;
	BOOL filtr_new1;
	BOOL filtr_new2;
	BOOL filtr_old2;
	BOOL filtr_old1;
	CColorListBox LB2;
	void ADD_ListBox(bool OT);//true=1 or false=2
	void ADD_ListCtrl(bool OT);//true=1 or false=2
	bool AB(int *ID, char** NAME, int *posB);//ADD BASE

	
	void ADD_GOAL_BASE(int ID_S, int ID_CH, int ID_T1, int ID_T2, int* DATA, int* GOAL);
	
	game* GAME_TIP;//@ntrvac xax@ glxavor axyusakum
	game* GAME_TIP_F;//@ntrvac xax@ arandzin axyusakum 
	void AddGoal(bool T12, bool PM=true);
	void ActivateGoal(bool GO=true);//true=Activ, false=Pasiv
	void SaveBase(void);
	void SortNewOld(void);
	void ref_base(bool OneTwo=true);
	void AddName(char* B, int p, char* N);
	void _SetTeamID(CString T1, CString T2, CString GD, bool OneTwo);
	void _ANTeam(p_t_b* PTB, char** T12,int* pos, int* IDT=NULL); 
	afx_msg void OnCbnSelendokCombo4();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
	afx_msg void OnLbnSelchangeList1();
	CListCtrl listc1;
	CListCtrl listc2;
//	afx_msg void OnLvnItemchangedList3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLbnSelchangeList2();
	afx_msg void OnBnClickedButton1();
	CComboBox combo_s;
//	afx_msg void OnLvnItemchangedList4(NMHDR *pNMHDR, LRESULT *pResult);
	BOOL RB_VToo;

	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnBnClickedOk();
	CButton r1;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	CButton rg1_1;
	CButton rg1_2;
	//CButton rg2_1;
	//CButton rg2_2;
	afx_msg void OnNMClickList3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeCombo4();
	afx_msg void OnBnClickedButton5();
	CButton butt_ATN;
	CEdit edit_ATN;
	CButton butt_OLD;
	CButton butt_NEW;
	afx_msg void OnBnClickedButton8();
	CString cs_ATN;
	/*CButton r_gt1;
	CButton r_gt2;
	CStatic s_gt1;
	CStatic s_gt2;*/
	CButton b_gp;
	CButton b_gm;
	CButton b_gt1;
	CButton b_gt2;
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};

#endif