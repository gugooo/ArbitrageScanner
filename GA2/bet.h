//#pragma once
#pragma once
#ifndef BET_H
#define BET_H

#include <iostream>
#include <fstream>
#include <iomanip>

#include <clocale>
#include <ctime>
#include <process.h>
#include "afxwin.h"

#include "INTERFACE_GA.h"

/////////////////////////////////////////////////////////////////////////////////////////////
struct kc_b;
struct kcT;
//***************V2********************
struct v2
{
	float vt;//V%
	kc_b* KC1;
	kc_b* KC2;
	bool LAY1;
	bool LAY2;
	v2* next;
};

struct KCV
{
	int ID_KC;
	bool LAY;//LAY=TRUE
	bool LAY_MY;//LAY=TRUE
	KCV* next;
};
/*struct ptr_KCV
{
	kcT* p_ID_KC;
	KCV* pKCV;
};*/

//***************V3********************
struct v3
{
	float vt;//V%
	bool* LAY;//0-L1, 1-L2, 2-L3
	int FormM;
	kc_b* KC1;
	kc_b* KC2;
	kc_b* KC3;
	v3* next;
};
struct sbor_GV//V% (max->min)
{
	v2* G_V2;
	v3* G_V3;
	int N2;
	int N3;
	sbor_GV* next;
};
struct sbor_ALL
{
	sbor_GV* GVALL;
	sbor_ALL* next;
};

struct V
{
	v2* V2;
	v3* V3;
};
//*************************************

struct kc_b
{
	float kc;
	int id_bet;//bazayi dirq
	int id_bet_name;
	bool ng;//true=>T1-T2, false=>T2-T1 
	kcT* TKC;
	//V* V_ALL;
	kc_b* next;
};
struct game;
struct kcT
{
	int id_kc;
	kc_b** ptrk;
	game* back_game;
	kcT* next;
};

struct hour;
struct game
{
	int id_t1;
	int id_t2;
	int *goal;
	kcT* ptrkc;
	V* ptr_V;
	hour* back_hour;
	game* next;
};

struct month;
struct hour
{
	int h;
	int minute;
	game* ptrg;
	month* back_month;
	hour* next;
};

struct cham;
struct month
{
	int y;
	int m;
	int day;
	hour* ptrh;
	cham* back_cham;
	month* next;
};

struct sport;
struct cham
{
	int id_ch;
	month* ptrm;
	sport* back_sport;
	cham* next;
};

struct sport
{
	int id_s;
	cham* ptrch;
	sport* next;
};

//************************************
struct cham_base
{
	char* cham_names;
	int id_cham;
};
/////////////////////////////////////
struct team_base
{
	char* team_name;
	int id_team;
};

struct p_t_b
{
	team_base* ptr_b;
	int id_cham;
};
/////////////////////////////////////
struct kc_base
{
	char kc_name[100];
	kc_base* ptr_kc;
	int id_kc;
	kc_base* BEND;//blok end
	bool end;//<<-----------------------------------
};

struct p_kc_b
{
	kc_base* p_base;
	p_kc_b* next;
};
//---------------------
struct total
{
	char* name;
	int id_total;
};

struct p_total
{
	int id_tt;
	int id_end;
	total* ptr_t;
};
//-------------------
struct xml_buff
{
	char* buffer;
	xml_buff* next;
};
//////////////////////////////////////////////////////////////////////////////////////////////
struct GOAL_G
{
	int ID_T1;
	int ID_T2;
	int *DATA;
	int *GOAL;
	GOAL_G* next;
};

struct GOAL_CH
{
	int ID_CH;
	GOAL_G* ptrGG;
	GOAL_CH* next;
};
//////////////////////////////////////////////////////////////////////////////////////////////

class bet
{
private:
	bool GX_STATUS[3];
//********SPORT*********//
	sport G; //**//linyaneri himan vra stexcvac axyusak//**//
	sport* GX;
	sport* TEMP_S;//@ntacik struct:sport
	cham* TEMP_CH;//@ntacik struct:cham
	game* TEMP_G;//@ntacik stuct:game
	bool TEMP_GT;//@ntacik xaxi tmer@ tarsen=false,
//********BET*********//
	
	int id_bet;	//@ntacik ID_bet sharqi hamar
	int id_bet_T;//@ntacik ID bet irakan, anuneri hamar
	char** bets_name;
	bool id_lge; //@ntacik ID_language ru(0),us(1)...
	bool bet_type;//@ntacik kantora=false ili birja=true
	bool* id_lge_all;  //bolor kantoraneri ID_language ru(0),us(1)...
	int* f_bets;//mshakvox kantoraneri id ner@
//*********************//

//*******SPORTS*********//
	
	char** sport_name; //char name_ru[31]+char name_us[31], name_ru[30]='\0',
	int id_s_onl;//@ntacik ID sport
	int* f_sports;//mshakvox sportadzeveri id ner@
//*********************//

//**********CHAMPIONSHIP***********//
	
	
	int* n_cham;//n_cham[ID_S-1]=n_ch
//*********************//


//**********TEAM***********//
	
	
	int *GX_GOAL;		//@ntacik xaxi hashiv@ (in play)
//*********************//

//**********KC***********//
	p_kc_b** kc_names;
	p_total** total_names;
	bool nf;//no find out
	char *nf_BT;//Betfair_WEB-i hamar, marketi anuni mejic vrcnume total@
	int ID_KC_MAX;//amenamec id_kc
	
//*********************//
	int xml_buff_size;//xml buferi chap@
	xml_buff* ptr_xml_buf;//
	xml_buff* ptr_xml_buf_temp;//
	int Xml_N;
	int* Xml_bet_time;//jamayin gotiner@ mekin berelu hamar, #--- *(Xml_bet_time+ID_B-1)=60 minute ---#

	char* Xml_Bass;//ignor & cham & game & ods
	char* Xml_Bass_Ch;
	char* Xml_Bass_G;
	char* Xml_Bass_O;
	char** Xml_B_O;//arandznacvac Xml_Bass_O
	char** Xml_B_OT;//arag voronman hamar
	int Xml_B_ON;//arandznacvac elamentneri qanak

	char* Xml_temp_file_name;
	//**********VILL***********//
	int* vil;//[0]=1->v2, [1]=2->v3, ...
	float VilT;//V%=2% <--mijem erku tokos
	
public:
	//BASE_INTERFACE* B_I; 
	//void SET_BaseI(BASE_INTERFACE* BI);
	CListBox* SendLBM;
	GOAL_CH* BASE_GOAL;
	Interface_Ga* IGA;
	sbor_ALL V_ALL;//max --> min
	int* GET_GOAL(int ID_S,int ID_CH, int ID_T1, int ID_T2, int* DATA=NULL);
	bet(CListBox&,Interface_Ga*,bool B_GX);
	void erl(char*,bool=false);//errors list, true->exit(0);
	void col(char*);//cout list
	sport* GET_ACCESS();
//********BET*********//
	int id_ch_onl;//@ntacik ID championship
	int id_t1_onl;		//@ntacik ID team1
	int id_t2_onl;		//@ntacik ID team2
	int n_bet;//kalichestvo kantor
	void fix_id_lge();//ustanovka tekushego yazika kantori <-(TEKUSHEGO) dlya FIX_BET()
	void load_bet(char*);//zagruska kantor iz faila
	void get_bets_name();//pakaz vstex kantor iz faila
	char* bet_name(int IDb);//vazvrashayet imya kantori po ID
	void load_id_lge_all();
	void FIX_BET(int);//ustanavlivaet tekushuyu kantoru i ego yazik
//*********************//

//********SPORTS*********//
	int n_sport;//kalichestvo sportov
	void sports_name();
	int get_sport_id(char*); 
	char* get_sport_name(int S,int B);//get_port_name(ID_SPORT,ID_BET), ID_BET-dlya ustanovki yazika
	void f(int ,char*, char*);//dlya sports_name()
//*********************//

//**********CHAMPIONSHIP***********//
	cham_base** cham_names;//BASE CHAMPIONSHIP

	void load_cham(char*);//zagruska chempionatov iz faila
	int get_cham_id(char*,char);
	char* get_cham_name(int CH,int S,int B);//get_cham_name(ID_CHAM, ID_SPORT, ID_BETE)
	void out_f_t_CH(char*, char='\0');//out_file_temp_championship(cham_name), dlya get_chem_id()
//*********************//

//**********TEAM***********//
	p_t_b** team_names;//BASE TEAMS

	void load_team(char*);
	int get_team_id(char*,char);
	void get_teams_name(int);//pakaz vstex komand iz faila po ID_BET
	char* get_team_name(int idT,int idCH,int idS,int idB);//get_team_name(ID_TEAM, ID_CHAM, ID_SPORT, ID_BET)
	void out_f_t_T(char*,char);//out_file_temp_team(team_name), dlya get_team_id()
//*********************//

//**********KC***********//
	bool* BetInPlayKcConvert;//[N_BET], true=YES 
	int ConvertForaKcId(int ID_KC);//online -i jamanak forayi totalner@ poxelu hamar
	bool CForaC;
	void load_kc(char*);
	int get_kc_id(char*,char,bool=false);//bool dlya opredelenie patoka (false(<n>nkc, nkc,...,nkv</n>); true(<n>nkc</n>))
	char* get_kc_name(int, int, int, int, int, int);//get_kc_name(ID_KC, ID_SPORT, ID_BET, ID_TEAM1, ID_TEAM2, ID_CHAM)
	char* get_kc_NU(int);//ID_KC->KC_NAME
	int convert(char*,int&);//char[]-->int, dlya load_kc()
	void out_f_kc_t(char*,char);//out_file_kc_temp(kc_name),
	char* get_DKC(char*,int&);//dlya get_kc_name() proveryaet inena komand (*1*->Tema1, *2*->Team2)
	void load_total(char*);
	int get_total_id(char*,char*,int,int&,int&,bool&,bool&);
	bool v_DKC(char*, int&, char*, int&, int, int, int, int, int);//dlya get_kc_name(), v_DKC(BASE, B, TEMP, T, ID_S, ID_B, ID_CH, ID_T1, ID_T2)
//**********XML***********//
	void START();
	void print_all();
	void xml_io(char*);//dlya START();
	char* add_char(char*,char*,bool=false);//true start delete-->'*'
	void xml_ignor();
	bool xml_cham();
	bool xml_game();
	bool xml_odds();
	char* ptr_xml(bool=true);//false '<-'; true '->'
	bool name_serch(char*,char);//char*-bari skizb, char-verjin simvol
	char* ptr_xml_g_name(char='\0');
	void xml_t_end();
	void xml_eror(int);
	int* xml_g_time();//[5]={year, month, day, hour, minute}
	char** xml_kc_name(float&);
	float char_fl(char*);//char@ verapoxume float i (kc)
	int convert_idkc(int);//ete tmer@ tars en poxuma kci idner@
	int* time_convert(int*);//xaxi jam@ poxelu hamar

	int* TIME_H(int=0);
	bool TIME_M(int*,int,int=0);//minute
	//**********G_XML***********//
	bool set_GX(sport* Gxml, int ID_BET,bool Birja=false);//ID_BET-bazayi sharqi hamar(#)
	bool set_GX_IB(int ID_BET_NAME);//petqe kanchvi set_GX-ic heto irakan ID_BET i depqum
	bool set_GX_ID(int ID_SPORT);
	bool set_GX_CHAM(char* CH_NAME=NULL,char END='\0');
	int* GX_time_convert(int* Time,int Diff_Time);//xaxi jam@ poxelu hamar
	bool set_GX_GAME(char* Team1=NULL,char END1='\0',char* Team2=NULL,char END2='\0',int* Time=NULL,int* GOAL=NULL);
	bool set_GX_KC(char** KC_NAME,char END,float KC);
	void ADD_GX(sport* Sp,bool Add_Next=true);
	bool GX_TIME_C(int* Time,int min_t,int max_t);
	int* GX_TIME_U(const char* MST);//Unix time convertor milliseconds
	hour* find_gameID(month* MO,int* GameData, int ID_T1, int ID_T2);//gtnum e xax@ ID-ov (+-)1 or intervalum
	//**********V2***********//
	void v_all();
	void PVALL();
	v2* vil2(kcT*);
	KCV* v2_r_id(int);//int ID_KC
	int id1_id2(int);//dlya v2_r_id
	int* idkl(int);//dlya v2_r_id veradarcnume nuy nshanakutyun unecod idner@
	
	v3* vil3(kcT*);
	bool* Market_Bf_Kc(int ID_kc1,int ID_kc2,int ID_kc3=0);//Betfair MARKETS KC, bool [2] or [3]
};

#endif