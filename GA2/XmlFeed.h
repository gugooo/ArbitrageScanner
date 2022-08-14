#pragma once
#ifndef XmlFeed_H
#define XmlFeed_H

#include "BETFAIR.h"
#include "bet.h"
#include <tchar.h>
#include <string>
#include <iostream>
#include <vcclr.h>
#using <System.dll>
#using <mscorlib.dll>
#using <System.Xml.dll>

using namespace System::IO;
using namespace System;
//////////////////////////////////////|
//////|	BETFAIR			ID = 1	|/////|
//////|	PINNACLESPORTS	ID = 2	|/////|
//////|	188BET			ID = 3	|/////|
//////|	SBOBET			ID = 4	|/////|
//////|	VIVAROBET		ID = 5	|/////|
//////|	EFUBET			ID = 6	|/////|
//////////////////////////////////////|
//struct UNO;
//----------------BASE INTERFACE------------------------
struct BI_G
{
	int* DATE_GAME;
	int ID_T1;
	int ID_T2;
	char* NAME_T1;
	char* NAME_T2;
	BI_G *next;
};

struct BI_CH
{
	int ID_CH;
	char* NAME_CH;
	BI_G *GAMES;
	BI_CH *next;
};

struct BI_BET
{
	int ID_BET_NAME;
	int ID_BET_POS;
	BI_CH* CHS;
	BI_CH* CHS_ZERO;
};
//-----------------------------------------------------
struct OddS
{
	gcroot<TextReader*> Inplay;
	gcroot<TextReader*> Offline;
};

class XmlFeed
{
private:
	
	gcroot<String*> BETFAIR_SOCCER;
	gcroot<String*> PINNACLESPORTS_SOCCER;
	gcroot<String*>_188BET_SOCCER;
	gcroot<String*> SBOBET_SOCCER;
	gcroot<String*> VIVAROBET_SOCCER;
	gcroot<String*> EFUBET_SOCCER;
	bet* CBet;
	sport *BL;//bolr kantoraneri axyusakner@ arandzin
	int T_BI_BET;//@ntacik BI_BET
	BI_CH* T_BI_CH;//@ntacik chapionat
public:
	int N_BET;
	/////////////////////////////////////////
	BI_BET *BASE_I;//HIMNAKAN
	void BI_BET_IDS(int ID_BET_NAME, int ID_BET_POS);
	void BI_CHAM(int ID_CH,char* CH_NAME);//CHAMPIONSHIP
	void BI_GAME(int ID_TEAM1, char* T1_NAME,int ID_TEAM2, char* T2_NAME,int* GAME_DATE);
	/////////////////////////////////////////
	XmlFeed(bet*);
	char* GetXmlFeed(int ID_BET, int ID_SPORT);
	//void get_CBet(bet*);
	sport* GET_ACCESS_F();//veradarcnum e BL*
	void DownloadX(void);//qashuma kantoraneri linyaner@ yev srquma axyusak
	
	bool Betfair_XML(void);
	bool Betfair_WEB(void);
	bool Pinnacle(void);
	bool _188bet(void);
	bool Sbobet(void);
	bool Vivaro(void);
	bool Efubet(void);
	bool OddService(int ID_BET);
	////////////ASYNC///////////////////////////////////////////////////////////////////////////////
	bool *AsyncStatus;

	TextReader* Betfair_XML_Download(void);//Downloat XML
	bool Betfair_Xml_ADD(TextReader* XML_FILE);
	B_Line* Betfair_WEB_Download(void);//Downloat WEB
	bool Betfair_WEB_ADD(B_Line* WEB_FILE);

	TextReader* Pinnacle_XML_Download(void);//Downloat XML
	bool Pinnacle_Xml_ADD(TextReader* XML_FILE);
	gcroot<TextReader*> PinnacleChName;//chempionatneri hamar

	TextReader* Vivaro_XML_Download(void);//Downloat XML
	bool Vivaro_Xml_ADD(TextReader* XML_FILE);

	void OddService_XML_Download(int ID_BET,int IPOA);//Downloat XML
	bool OddService_Xml_ADD(int ID_B);

	gcroot<TextReader*> OddServiceCount;//erkrneri hamar<<-----------------------------------sarbel bolori hamar
	gcroot<TextReader*> OddServiceLeag;//chempionatneri hamar

	OddS* OSIO;
	bool OddServiceCL;
	bool OddServiceCL2;
	bool OddServiceCL3;
	bool OddServiceCL4;
	std::string Time_CounA;
	std::string Time_LeagA;
	std::string* Time_S_BKA;
	std::string* Time_S_BK_In_PlayA;
	//int A_ID_BET;
	int A_IPOA;
	int TimeMS;//1000MS = 1S
	void BeginA(void);
	int IJN;

	int StatIPO;//0-InPlay, 1-OffLine, 2-All
};

#endif