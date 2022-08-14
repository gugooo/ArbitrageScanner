#include "stdafx.h"
#include "XmlFeed.h"
#include <string.h>
#include "EFUBET.h"
#include "BETFAIR.h"
#include <algorithm>
using namespace System;
using namespace System::IO;
using namespace System::IO::Compression;
using namespace System::Xml;
using namespace System::Runtime::InteropServices;
using namespace System::Net;
using namespace System::Text;
//using namespace System::Web
using namespace std;

UINT DP_Pinnacle(LPVOID);
UINT DP_CONTROL(LPVOID);
UINT DP_Betfair(LPVOID);
UINT DP_Efubet(LPVOID);
UINT DP_188bet(LPVOID);
UINT DP_Sbobet(LPVOID);
UINT DP_Bet365(LPVOID);
UINT DP_Vivarobet(LPVOID LV);

XmlFeed::XmlFeed(bet* B)
{
	N_BET=B->n_bet;///<<<<<<=========//N_BET kantoraneri qanak@
	CBet=B;
	BL=new sport[N_BET];
	for(int i=0;i<N_BET;i++)
	{
		(BL+i)->id_s=0;
		(BL+i)->next=NULL;
		(BL+i)->ptrch=NULL;
	}
	BETFAIR_SOCCER="http://www.betfair.com/partner/marketData_loader.asp?fa=ss&id=1&SportName=Soccer&Type=BL";
	_188BET_SOCCER="C:/Users/GA/Documents/Visual Studio 2010/Projects/GA2/GA2/soccer/odds_188.xml";
	VIVAROBET_SOCCER="C:/Users/GA/Documents/Visual Studio 2010/Projects/GA2/GA2/soccer/odds_vivaro.xml";
	BASE_I=new BI_BET[N_BET];
	for(int i=0;i<N_BET;i++)
	{
		(BASE_I+i)->CHS=NULL;
		(BASE_I+i)->CHS_ZERO=NULL;
		(BASE_I+i)->ID_BET_NAME=0;
		(BASE_I+i)->ID_BET_POS=0;
	}

	///////////////////////////////
	Time_S_BKA=new string[N_BET];
	Time_S_BK_In_PlayA=new string[N_BET];
	AsyncStatus=new bool[N_BET];
	for(int i=0;i<N_BET;i++){ *(AsyncStatus+i)=false; Time_S_BKA[i]=""; Time_S_BK_In_PlayA[i]=""; }
	//TextReader** OddServiceInPlay=new TextReader*[N_BET];
	//OddServiceOffline=new<TextReader*>(N_BET);
	OSIO=new OddS[N_BET];
	TimeMS=10;//1 ms
	StatIPO=0;//0-InPlay, 1-OffLine, 2-All
}


//***********************************************************
void XmlFeed::BI_BET_IDS(int ID_B_NAME,int ID_B_POS)
{
	(BASE_I+ID_B_NAME-1)->ID_BET_NAME=ID_B_NAME;
	if(ID_B_POS) (BASE_I+ID_B_NAME-1)->ID_BET_POS=ID_B_POS;
	else (BASE_I+ID_B_NAME-1)->ID_BET_POS=ID_B_NAME;
	(BASE_I+ID_B_NAME-1)->CHS=NULL;
	(BASE_I+ID_B_NAME-1)->CHS_ZERO=NULL;
	T_BI_BET=ID_B_NAME;
	T_BI_CH=NULL;
}

void XmlFeed::BI_CHAM(int ID_CH, char* CH_NAME)
{
	bool have_CH=false;
	////////////////////////KRKNVOX CHEMPIONATNERI HAMAR////////////////////////////////////////////////////////////////////////////////
	if(ID_CH)
	{
		if(T_BI_CH){
		if(T_BI_CH->ID_CH==ID_CH)return;
		for(BI_CH* TCH=(BASE_I+T_BI_BET-1)->CHS; TCH; TCH=TCH->next)
		{
			if(TCH->ID_CH==ID_CH)
			{
				T_BI_CH=TCH;
				return;
			}
		}}
	}
	else
	{
		if(T_BI_CH){
		for(int i=0;i<200 && *(CH_NAME+i)==*(T_BI_CH->NAME_CH+i);i++)
		{
			char A1, A2;
			A1=*(CH_NAME+i);
			A2=*(T_BI_CH->NAME_CH+i);
			if(*(CH_NAME+i)=='\0' && *(T_BI_CH->NAME_CH+i)=='\0')return;
		}
		for(BI_CH* TCH=(BASE_I+T_BI_BET-1)->CHS_ZERO; TCH; TCH=TCH->next)
		{
			for(int i=0;i<200 && *(TCH->NAME_CH+i)==*(CH_NAME+i);i++)
			{
				if(*(TCH->NAME_CH+i)=='\0' && *(CH_NAME+i)=='\0')
				{
					T_BI_CH=TCH;
					return;
				}
			}
		}}
	}
	////////////////////////NOR CHEMPIONATNERI HAMAR/////////////////////////////////////////////////////////////////////////////////////
	char* TEMP_NAME=new char[200];
	for(int i=0;i<200;i++){ *(TEMP_NAME+i)=*(CH_NAME+i);if(*(CH_NAME+i)=='\0')break; }
	BI_CH *TEMP_CH=new BI_CH;
	TEMP_CH->ID_CH=ID_CH;
	TEMP_CH->GAMES=NULL;
	TEMP_CH->NAME_CH=TEMP_NAME;
	if(ID_CH)
	{
		TEMP_CH->next=(BASE_I+T_BI_BET-1)->CHS;
		(BASE_I+T_BI_BET-1)->CHS=TEMP_CH;
	}
	else
	{
		TEMP_CH->next=(BASE_I+T_BI_BET-1)->CHS_ZERO;
		(BASE_I+T_BI_BET-1)->CHS_ZERO=TEMP_CH;
	}
	T_BI_CH=TEMP_CH;
}

void XmlFeed::BI_GAME(int ID_T1, char* T1_Name, int ID_T2, char* T2_Name, int *G_DATE)
{
	BI_G* T_GAME=new BI_G;
	T_GAME->ID_T1=ID_T1;
	char* TEMP_NAME=new char[100];
	for(int i=0;i<100;i++){ *(TEMP_NAME+i)=*(T1_Name+i);if(*(T1_Name+i)=='\0')break; }
	T_GAME->NAME_T1=TEMP_NAME;
	T_GAME->ID_T2=ID_T2;
	TEMP_NAME=new char[100];
	for(int i=0;i<100;i++){ *(TEMP_NAME+i)=*(T2_Name+i);if(*(T2_Name+i)=='\0')break; }
	T_GAME->NAME_T2=TEMP_NAME;
	T_GAME->DATE_GAME=new int[5];
	for(int i=0;i<5;i++)
	{
		*(T_GAME->DATE_GAME+i)=*(G_DATE+i);
	}
	T_GAME->next=T_BI_CH->GAMES;
	T_BI_CH->GAMES=T_GAME;
}
//***********************************************************


char* XmlFeed::GetXmlFeed(int ID_BET, int ID_SPORT)
{
	String *Temp;
	///////////////////////////////////////////////
	switch(ID_SPORT)
	{
	case 1://Football(Soccer)
		switch(ID_BET)
		{
		case 1://188BET
			Temp=_188BET_SOCCER;
			break;
		case 2://PINNACLESPORTS
			Temp=PINNACLESPORTS_SOCCER;
			break;
		case 3://BETFAIR
			Temp=BETFAIR_SOCCER;
			break;
		case 4://VIVARO
			Temp=VIVAROBET_SOCCER;
			break;
		case 5://SBOBET
			Temp=SBOBET_SOCCER;
			break;
		case 6://EFUBET
			Temp=EFUBET_SOCCER;
			break;
		}
		break;
	case 2://Tennis
		break;
	case 3://Hockey
		break;
	case 4://Volleyball
		break;
	case 5://Basketball
		break;
	case 6:// Baseball
		break;
	}
	///////////////////////////////////////////////
	XmlTextReader *reader = new XmlTextReader (Temp);
	TextReader *text=reader->GetRemainder();
	String *xml;
	xml=text->ReadToEnd();
	char* PtrXmlChar=(char*)(void*)Marshal::StringToHGlobalAnsi(xml);
	return PtrXmlChar;
}
///////////////////////////////////////////
void XmlFeed::BeginA()
{
	OddServiceCL=true;
	OddServiceCL2=true;
	OddServiceCL3=true;
	OddServiceCL4=true;

	CWinThread* myWinThread = AfxBeginThread(DP_CONTROL,this);

	for(int i=0;i<N_BET;i++)
	{
	 switch( i+1 )
	 {
	 case 1:if((CBet->IGA->Bets+i)->l_xml){ CWinThread* myWinThread1 = AfxBeginThread(DP_Betfair,this);	}break;//Betfair
	 case 2:if((CBet->IGA->Bets+i)->l_xml){ CWinThread* myWinThread2 = AfxBeginThread(DP_Pinnacle,this); }break;//Pinnacle
	 case 3:if((CBet->IGA->Bets+i)->l_xml){ CWinThread* myWinThread3 = AfxBeginThread(DP_188bet,this); } break;//188Bet
	 case 4:if((CBet->IGA->Bets+i)->l_xml){ CWinThread* myWinThread4 = AfxBeginThread(DP_Sbobet,this); }break;//Sbobet
	 case 5:if((CBet->IGA->Bets+i)->l_xml){ CWinThread* myWinThread5 = AfxBeginThread(DP_Vivarobet,this); }break;//Vivaro
	 case 6:if((CBet->IGA->Bets+i)->l_xml){ CWinThread* myWinThread6 = AfxBeginThread(DP_Efubet,this); }break;//Efubet
	 case 7:if((CBet->IGA->Bets+i)->l_xml){ CWinThread* myWinThread7 = AfxBeginThread(DP_Bet365,this); }break;//Bet365
	 case 8:if((CBet->IGA->Bets+i)->l_xml){ /*OddService_XML_Download(8,2); OddService_Xml_ADD(); */}break;//Titanbet
	 }
	}
	/*CWinThread* myWinThread = AfxBeginThread(DP_CONTROL,this);
	CWinThread* myWinThread1 = AfxBeginThread(DP_Betfair,this);
	CWinThread* myWinThread2 = AfxBeginThread(DP_Pinnacle,this);
	CWinThread* myWinThread3 = AfxBeginThread(DP_Efubet,this);
	CWinThread* myWinThread4 = AfxBeginThread(DP_188bet,this);
	CWinThread* myWinThread5 = AfxBeginThread(DP_Sbobet,this);
	CWinThread* myWinThread6 = AfxBeginThread(DP_Bet365,this);*/
}

UINT DP_CONTROL(LPVOID LV)
{
	XmlFeed *lp=(XmlFeed*)LV;
	//lp->Efubet();
	for(int i=0;;i++)
	{
		if( *(lp->AsyncStatus+i) )
		{
			*(lp->AsyncStatus+i)=false;
			for(;!*(lp->AsyncStatus+i);) Sleep(lp->TimeMS);
			*(lp->AsyncStatus+i)=false;
			if(!(--(lp->IJN)))break;
		}
		if(i==(lp->N_BET-1)) i=-1;
		//if(lp->A1 & lp->A2 & lp->A3 & lp->A4 & lp->A6 & lp->A7) break;
		Sleep(lp->TimeMS);
	}
	return 0;
}
UINT DP_Betfair(LPVOID LV)
{
	XmlFeed *lp=(XmlFeed*)LV;
	static const int ID=1;
	//XML
	/*TextReader* Temp=lp->Betfair_XML_Download();
	*(lp->AsyncStatus+ID-1)=true;
	for(;*(lp->AsyncStatus+ID-1);) Sleep(lp->TimeMS);;
	lp->Betfair_Xml_ADD(Temp);
	*(lp->AsyncStatus+ID-1)=true;
	//WEB*/
	B_Line* TEMP=lp->Betfair_WEB_Download();
	*(lp->AsyncStatus+ID-1)=true;
	for(;*(lp->AsyncStatus+ID-1););
	lp->Betfair_WEB_ADD(TEMP);
	*(lp->AsyncStatus+ID-1)=true;
	//lp->A1=true;
	
	return 0;
}
UINT DP_Pinnacle(LPVOID LV)
{
	XmlFeed *lp=(XmlFeed*)LV;
	static const int ID=2;
	TextReader* Temp=lp->Pinnacle_XML_Download();
	*(lp->AsyncStatus+ID-1)=true;
	for(;*(lp->AsyncStatus+ID-1);)Sleep(lp->TimeMS);;
	lp->Pinnacle_Xml_ADD(Temp);
	*(lp->AsyncStatus+ID-1)=true;
	//lp->A2=true;
	return 0;
}
UINT DP_Efubet(LPVOID LV)
{
	XmlFeed *lp=(XmlFeed*)LV;
	static const int ID=6;
	*(lp->AsyncStatus+ID-1)=true;
	for(;*(lp->AsyncStatus+ID-1);)Sleep(lp->TimeMS);;
	lp->Efubet();
	*(lp->AsyncStatus+ID-1)=true;
	//lp->A6=true;
	return 0;
}
UINT DP_188bet(LPVOID LV)
{
	XmlFeed *lp=(XmlFeed*)LV;
	static const int ID=3;
	lp->OddService_XML_Download(ID,lp->StatIPO);
	*(lp->AsyncStatus+ID-1)=true;
	for(;*(lp->AsyncStatus+ID-1);)Sleep(lp->TimeMS);;
	lp->OddService_Xml_ADD(ID);
	*(lp->AsyncStatus+ID-1)=true;
	//lp->A3=true;
	return 0;
}
UINT DP_Sbobet(LPVOID LV)
{
	XmlFeed *lp=(XmlFeed*)LV;
	static const int ID=4;
	lp->OddService_XML_Download(ID,lp->StatIPO);
	*(lp->AsyncStatus+ID-1)=true;
	for(;*(lp->AsyncStatus+ID-1);)Sleep(lp->TimeMS);
	lp->OddService_Xml_ADD(ID);
	*(lp->AsyncStatus+ID-1)=true;
	//lp->A4=true;
	return 0;
}
UINT DP_Bet365(LPVOID LV)
{
	XmlFeed *lp=(XmlFeed*)LV;
	static const int ID=7;
	lp->OddService_XML_Download(ID,lp->StatIPO);
	*(lp->AsyncStatus+ID-1)=true;
	for(;*(lp->AsyncStatus+ID-1);)Sleep(lp->TimeMS);;
	lp->OddService_Xml_ADD(ID);
	*(lp->AsyncStatus+ID-1)=true;
	//lp->A7=true;
	return 0;
}
UINT DP_Titanbet(LPVOID LV)
{
	XmlFeed *lp=(XmlFeed*)LV;
	//lp->Efubet();
	return 0;
}
UINT DP_Vivarobet(LPVOID LV)
{
	XmlFeed *lp=(XmlFeed*)LV;
	static const int ID=5;
	TextReader* Temp=lp->Vivaro_XML_Download();
	*(lp->AsyncStatus+ID-1)=true;
	for(;*(lp->AsyncStatus+ID-1);)Sleep(lp->TimeMS);;
	lp->Vivaro_Xml_ADD(Temp);
	*(lp->AsyncStatus+ID-1)=true;
	return 0;
}
///////////////////////////////////////////
 void XmlFeed::DownloadX(void)
 {
	 /////////////////////LINYANERI QASHUM/////////////////////////
	 CBet->SendLBM->AddString(L"________________________________________________");
	
	 /*
	 for(int i=0;i<N_BET;i++)
	 {
		 switch( i+1 )
		 {
		 case 1:if((CBet->IGA->Bets+i)->l_xml){ Betfair_Xml_ADD(Betfair_XML_Download()); }break;//Betfair_XML();break;/* Betfair_WEB();break;//OddService(1);
		 case 2:if((CBet->IGA->Bets+i)->l_xml){ Pinnacle_Xml_ADD(Pinnacle_XML_Download());}break;//Pinnacle();break;
		 case 3:if((CBet->IGA->Bets+i)->l_xml){ OddService_XML_Download(3,2); OddService_Xml_ADD();} break;//OddService(3);break;
		 case 4:if((CBet->IGA->Bets+i)->l_xml){ OddService_XML_Download(4,2); OddService_Xml_ADD();}break;//OddService(4);break;
		 case 5:if((CBet->IGA->Bets+i)->l_xml){ Vivaro();}break;
		 case 6:if((CBet->IGA->Bets+i)->l_xml){ Efubet();}break;
		 case 7:if((CBet->IGA->Bets+i)->l_xml){ OddService_XML_Download(7,2); OddService_Xml_ADD();}break;//OddService(7);;break;
		 case 8:if((CBet->IGA->Bets+i)->l_xml){ OddService_XML_Download(8,2); OddService_Xml_ADD();}break;//OddService(8);;break;
		 }
	 }
	 //////////////////LINYANERI MIAVORUM//////////////////////////
	 */
	
	 IJN=N_BET;
	 for(int i=0;i<N_BET;i++) if( !(CBet->IGA->Bets+i)->l_xml ) IJN--;
	 BeginA();
	 for(;IJN;) Sleep(TimeMS);

	 bool ON=false;
	 for(int i=0;i<N_BET;i++)
	 {
		 switch( i+1 )
		 {
		 case 1:if((CBet->IGA->Bets+i)->SF){CBet->FIX_BET(i+1)/*UNIVERSAL ID*/; CBet->ADD_GX((BL+i),ON); ON=true;} break;
		 case 2:if((CBet->IGA->Bets+i)->SF){CBet->FIX_BET(i+1); CBet->ADD_GX((BL+i),ON); ON=true;} break;
		 case 3:if((CBet->IGA->Bets+i)->SF){CBet->FIX_BET(3)/*UNIVERSAL ID*/; CBet->ADD_GX((BL+i),ON); ON=true;} break;
		 case 4:if((CBet->IGA->Bets+i)->SF){CBet->FIX_BET(3)/*UNIVERSAL ID*/; CBet->ADD_GX((BL+i),ON); ON=true;} break;
		 case 5:if((CBet->IGA->Bets+i)->SF){CBet->FIX_BET(i+1); CBet->ADD_GX((BL+i),ON); ON=true;} break;
		 case 6:if((CBet->IGA->Bets+i)->SF){CBet->FIX_BET(i+1); CBet->ADD_GX((BL+i),ON); ON=true;} break;
		 case 7:if((CBet->IGA->Bets+i)->SF){CBet->FIX_BET(3)/*UNIVERSAL ID*/; CBet->ADD_GX((BL+i),ON); ON=true;} break;
		 case 8:if((CBet->IGA->Bets+i)->SF){CBet->FIX_BET(3)/*UNIVERSAL ID*/; CBet->ADD_GX((BL+i),ON); ON=true;} break;
		 }
	 }
 }

bool XmlFeed::Betfair_XML(void)
{
	int ID_BET=1;
	BI_BET_IDS(ID_BET,ID_BET);//BASE INTERFACE
	int *Goal=NULL;
	int Diff_Time=180;//[MINUT] jamayin tarberutyun
	char** KC_NAME=new char*[3];
	*(KC_NAME+2)=NULL;
	float KC;
	float LAY;
	int ID_SPORT=1;//<<=========
	(BL+ID_BET-1)->next=NULL;
	(BL+ID_BET-1)->ptrch=NULL;
	if( !CBet->set_GX(BL+ID_BET-1,ID_BET,true) ) /*ERROR*/return false;

	switch(ID_SPORT)
	{
	case 1://Football(Soccer)
	CBet->SendLBM->AddString(L"Betfair (XML)");
////////////////////////////////////////////////////////////////////////////////////////////////////
if(CBet->set_GX_ID(ID_SPORT))
{

	///////////////////////////////////////////////////////
	WebRequest *request = WebRequest::Create(BETFAIR_SOCCER); 
	WebResponse *response = request->GetResponse();
	Stream *responseStream = response->GetResponseStream(); 
	////////////////////////////////////////////////////////
	XmlParserContext *context =new XmlParserContext(nullptr, nullptr, nullptr, XmlSpace::None, Encoding::UTF8);
	XmlTextReader *reader = new XmlTextReader(responseStream,XmlNodeType::Document,context);
	reader->WhitespaceHandling = WhitespaceHandling::None;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////System Time///////
	SYSTEMTIME sti;
	GetLocalTime(&sti);
	int STime[5];
	STime[0]=sti.wYear;
	STime[1]=sti.wMonth;
	STime[2]=sti.wDay;
	STime[3]=sti.wHour;
	STime[4]=sti.wMinute;
	int *STiD=CBet->GX_time_convert(STime,int((CBet->IGA->Filter).fr_h));
	for(int i=0;i<5;i++) STime[i]=*(STiD+i);
	/////////////////////////
	string Elem_Name;
	string BHM;//hour minute
	string Btime;
	string CH_and_G;
	string CH;
	string T1;
	string T2;
	int Bdate[5];//0-year, 1-month, 2-day, 3-hour, 4-minute
	int *CBD;
	try
	{
		while(true)
		{
			switch(reader->NodeType)
			{
				case XmlNodeType::Element: 
					Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
					//if(EN=="betfair");
					if(Elem_Name=="selection")
					{
						*(KC_NAME+1)=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("name"))).ToPointer();
						string kcname=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("backp1") )).ToPointer();
						KC=atof(kcname.c_str());
						if( int(KC) ) CBet->set_GX_KC(KC_NAME,'\0',KC);
						
						string layname=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("layp1") )).ToPointer();
						LAY=-atof( layname.c_str() );
						if( int(LAY) ) CBet->set_GX_KC(KC_NAME,'\0',LAY);
						
						reader->Read();
						continue;
					}
					if(Elem_Name=="subevent")
					{
						*KC_NAME=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("title"))).ToPointer();
						reader->Read();
						continue;
					}
					//--------------------------------------------------------------------------------------------------
					if(Elem_Name=="event")
					{
						Btime=(const char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("date"))).ToPointer();
						Bdate[0]=atoi( (Btime.substr(6,4)).c_str() );//year
						if(Bdate[0]>=STime[0])
						{
							Bdate[1]=atoi( (Btime.substr(3,2)).c_str() );//month
							Bdate[2]=atoi( (Btime.substr(0,2)).c_str() );//day
							CH_and_G=(const char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("name"))).ToPointer();
							reader->Read();
							Elem_Name=(const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
							BHM=(const char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("time"))).ToPointer();
							Bdate[3]=atoi( (BHM.substr(0,2)).c_str() );//hour
							Bdate[4]=atoi( (BHM.substr(3,2)).c_str() );//min
							CBD=CBet->GX_time_convert(Bdate,Diff_Time);
							bool GXT=false;
							if(*(CBD)>STime[0]) GXT=true;
							else
							{
								if(*(CBD)==STime[0])
								{
									if(*(CBD+1)>=STime[1]) GXT=true;
								}
							}
							if(GXT/**(CBD+1)>=STime[1] &&  *(CBD+2)>=STime[2]*/)
							{
								
								unsigned int pos = CH_and_G.find("/Fixtures");
								if(int(pos)==-1) pos = CH_and_G.find("/Fixtues");
								if(int(pos)==-1) pos = CH_and_G.find("/To Qualify/");
								//////////////////////////////////////////////////////////////////////////////////
									////////////////////////////////////
									if(int(pos)==-1)
									{
										CBet->set_GX_CHAM((char*)CH_and_G.c_str(),'\0');
										for(;Elem_Name!="event";)
										{
											reader->Skip();
											Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
										}
										continue;
									}
									/////////////////////////////////////
								/////////////////////////////////////////////////////////////////////////////
								CH=CH_and_G.substr(0,pos);
								unsigned pos1=CH_and_G.find("/",pos+1)+1;
								unsigned pos2=CH_and_G.find(" v ",pos1);
								if(int(pos1)!=-1 && int(pos2)!=-1)
								{
									T1=CH_and_G.substr(pos1,(pos2-pos1));
									T2=CH_and_G.substr(pos2+3);
									bool CHG[2];
									CHG[0]=CBet->set_GX_CHAM((char*)CH.c_str(),'\0');//CHAMPIONSHIP
									BI_CHAM(CBet->id_ch_onl,(char*)CH.c_str());//BASE INTERFACE
									CHG[1]=CBet->set_GX_GAME((char*)T1.c_str(),'\0',(char*)T2.c_str(),'\0',CBD,Goal );
									BI_GAME(CBet->id_t1_onl,(char*)T1.c_str(),CBet->id_t2_onl,(char*)T2.c_str(),CBD);
									if(CHG[0] && CHG[1]) continue;	//GAME								
								}
							}

							/////////////////////////////////////////////////////////////////////////////////////
							for(;Elem_Name!="event";)
							{
								reader->Skip();
								Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
							}
							continue;
							//////////////////////////////////////////////////////////////////////////////////////

						}
						reader->Skip();
						Elem_Name=(const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
						continue;
						
					}
					//--------------------------------------------------------------------------------------------------
				break;
				
				case XmlNodeType::EndElement:				
					break;
			}
			if(! reader->Read() )break;
			Elem_Name=(const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
		}
	}
	catch(System::Exception *ex)
	{
		//ERROR
		CBet->SendLBM->AddString(L"Download Betfair: ERROR");
	}
	//CBet->SendLBM->AddString(L"Download Betfair: OK");

}
////////////////////////////////////////////////////////////////////////////////////////////////////
	case 2:return false;//Tennis
		
	case 3:return false;//Hockey
		
	case 4:return false;//Volleyball
		
	case 5:return false;//Basketball
		
	case 6:return false;// Baseball
		
	default:return false;
	}
	
}
bool XmlFeed::Betfair_WEB(void)//STUGEL BASE INTERFACE-i FUNKCIANER@
{
	/////////////////////////////////////////////
	int ID_BET=1;
	BI_BET_IDS(ID_BET,ID_BET);//BASE INTERFACE
	int *Goal=NULL;
	int Diff_Time=180;//[MINUT] jamayin tarberutyun
	char** KC_NAME=new char*[3];
	*(KC_NAME+2)=NULL;
	int ID_SPORT=1;//<<=========
	(BL+ID_BET-1)->next=NULL;
	(BL+ID_BET-1)->ptrch=NULL;
	if( !CBet->set_GX(BL+ID_BET-1,ID_BET,true) ) /*ERROR*/return false;
	CBet->SendLBM->AddString(L"Betfair (Node_JS)");
	/////////////////////////////////////////////
	string patch,Mname,MStatus;
	string CH,T1,T2;
	int *CBD;
	if(CBet->set_GX_ID(ID_SPORT))
	{
		BETFAIR BF;
		B_Line *BL=BF.StartL();
		for(B_Line *TG=BL;TG;TG=TG->next)
		{
			//-------------------------------------------------------------------------------------------
			patch=(const char*)(TG->PatchGame);
			unsigned int pos = patch.find("\\Fixtures");
			if(int(pos)==-1) pos = patch.find("\\Fixtues");
			if(int(pos)==-1) pos = patch.find("\\To Qualify/");
			if(int(pos)==-1)
			{
				CBet->set_GX_CHAM((char*)patch.c_str(),'\0');//SET CHAMPIONSHIP
				continue;
			}
			CH=patch.substr(8,pos-8);
			CH+='\0';
			for(;int(CH.find("\\"))!=-1;) CH.replace(CH.find("\\"),1,"/");
			unsigned int pos1=patch.find("\\",pos+1)+1;
			unsigned int pos2=patch.find(" v ",pos1);
			if(int(pos1)!=-1 && int(pos2)!=-1)
			{
				T1=patch.substr(pos1,(pos2-pos1));
				T2=patch.substr(pos2+3);
				bool GCH[2];
				GCH[0]=CBet->set_GX_CHAM((char*)CH.c_str(),'\0');
				BI_CHAM(CBet->id_ch_onl,(char*)CH.c_str());//BASE INTERFACE
				CBD=CBet->GX_time_convert( (int*)(CBet->GX_TIME_U((const char*)TG->DateOfGame)), Diff_Time);
				GCH[1]=CBet->set_GX_GAME((char*)T1.c_str(),'\0',(char*)T2.c_str(),'\0',CBD,Goal );
				BI_GAME(CBet->id_t1_onl,(char*)T1.c_str(),CBet->id_t2_onl,(char*)T2.c_str(),CBD);//BASE INTERFCE
				if( !GCH[0] | !GCH[1] )	continue;
			}
			//-------------------------------------------------------------------------------------------
			for(BMarket *TM=TG->ptr_BMarket;TM;TM=TM->next)
			{
				int Z=0;
				for(;*(TM->MName+Z)!='|';Z++);
				*(TM->MName+Z)='\0';
				int C;
				for(C=++Z;*(TM->MName+C)!='\n';C++);
				*(TM->MName+C)='\0';
				MStatus=(const char*)(TM->MName+Z);
				*KC_NAME=TM->MName;//MARKET NAME
				if(MStatus!="ACTIVE")continue;
				for(BOdds *TO=TM->ptr_BOdds;TO;TO=TO->next)
				{
					for(Z=0;*(TO->KC_name+Z)!='|';Z++);
					*(TO->KC_name+Z)='\0';
					*(KC_NAME+1)=TO->KC_name;
					if(TO->Back>1) CBet->set_GX_KC(KC_NAME,'\0',TO->Back);//SET MARKET AND BACK ODDS
					if(TO->Lay>1) CBet->set_GX_KC(KC_NAME,'\0',-TO->Lay);//SET MARKET AND LAY ODDS
				}
			}
		}
	}
	return true;
}

struct PINNACLE_CHAM
{
	int ID_PCH;
	char *PCH_NAME;
	PINNACLE_CHAM *next;
};

bool XmlFeed::Pinnacle(void)
{
	int ID_BET=2;
	BI_BET_IDS(ID_BET,ID_BET);
	int *Goal=NULL;
	int Diff_Time=181;//[MINUTE]
	char** KC_NAME=new char*[4];
	*(KC_NAME+3)=NULL;
	float KC;
	int ID_SPORT=1;//<<=========
	(BL+ID_BET-1)->next=NULL;
	(BL+ID_BET-1)->ptrch=NULL;
	if( !CBet->set_GX(BL+ID_BET-1,ID_BET) ) /*ERROR*/return false;
	static PINNACLE_CHAM *p_ch=NULL;
	PINNACLE_CHAM *PTemp;
	string Elem_Name;
	string TimeG;
	string T1;
	string T2;
	int ITime[5];
	string totalV;
	string totalT;
	string TV;
	bool GCH[2];
	switch(ID_SPORT)
	{
	case 1://Football(Soccer)
		CBet->SendLBM->AddString(L"Pinnaclesports");
//////////////////////////////////////////////////////////////////////////////
	if(CBet->set_GX_ID(ID_SPORT))
	{
		XmlTextReader *reader;
	//////////////LOAD CHAM ID///////////////////
		if(!p_ch)
		{
			reader = new XmlTextReader("http://api.pinnaclesports.com/v1/leagues?sportid=29");//LOAD CHAM ID FOR PINNACLE
			while (reader->Read()) 
			{
				switch (reader->NodeType) 
				{
					case XmlNodeType::Element: // The node is an element.
					Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
					if(Elem_Name=="league")
					{
						PTemp=new PINNACLE_CHAM;
						PTemp->ID_PCH=atoi(  (char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("id"))).ToPointer()  );
						reader->Read();
						PTemp->PCH_NAME=(char*)(Marshal::StringToHGlobalAnsi(reader->Value)).ToPointer();
						PTemp->next=p_ch;
						p_ch=PTemp;
						break;
					}
					else break;
					case XmlNodeType::EndElement: //Display the end of the element.
					break;
				}
			}
			reader->Close();
	
		}
	/////////////////////////////////////////
		string URL_PINN="http://api.pinnaclesports.com/v1/feed?sportid=29&clientid=VA446096&apikey=d2e6f564-4726-46a1-871e-edefc57a74ed&oddsformat=1";
		/*string LAST="&last=";
		string LAST_V;
		static bool L_V=false;
		if(L_V)	URL_PINN=URL_PINN+LAST+LAST_V;*/
		String *SURL_PINN=new String(URL_PINN.c_str());
		reader=new XmlTextReader(SURL_PINN);
		while (true) 
		{
				switch (reader->NodeType) 
				{
					case XmlNodeType::Element: // The node is an element.
					Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
					////////////////////////////////////////KC//////////////////////////////////////////////////////////////////
					if(Elem_Name=="period")
					{
						reader->Read(); reader->Skip();
						*KC_NAME=(char*)(Marshal::StringToHGlobalAnsi(reader->ReadElementString("description"))).ToPointer();
						reader->Skip();
						for(;;)
						{
							Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
							if(Elem_Name=="maxBetAmount"){reader->Skip(); continue;}
							if(Elem_Name=="period" && reader->NodeType==XmlNodeType::EndElement)break;

							if(Elem_Name=="spreads")
							{
								reader->Read();
								Elem_Name=(const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
								*(KC_NAME+1)=(char*)Elem_Name.c_str();
								for(;Elem_Name=="spread" && reader->NodeType==XmlNodeType::Element;)
								{
									reader->Read();
									totalV=(const char*)(Marshal::StringToHGlobalAnsi(reader->ReadElementString("awaySpread"))).ToPointer();
									totalT="F2 ";
									TV=totalT+totalV;
									*(KC_NAME+2)=(char*)TV.c_str();
									KC= atof( (char*)(Marshal::StringToHGlobalAnsi(reader->ReadElementString("awayPrice"))).ToPointer() );
									CBet->set_GX_KC(KC_NAME,'\0',KC);
									totalV=(const char*)(Marshal::StringToHGlobalAnsi(reader->ReadElementString("homeSpread"))).ToPointer();
									totalT="F1 ";
									TV=totalT+totalV;
									*(KC_NAME+2)=(char*)TV.c_str();
									KC= atof( (char*)(Marshal::StringToHGlobalAnsi(reader->ReadElementString("homePrice"))).ToPointer() );
									CBet->set_GX_KC(KC_NAME,'\0',KC);
									reader->Read();
									Elem_Name=(const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
								}
								continue;
							}
							if(Elem_Name=="totals")
							{
								reader->Read();
								Elem_Name=(const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
								*(KC_NAME+1)=(char*)Elem_Name.c_str();
								for(;Elem_Name=="total" && reader->NodeType==XmlNodeType::Element;)
								{
									reader->Read();
									totalV=(const char*)(Marshal::StringToHGlobalAnsi(reader->ReadElementString("points"))).ToPointer();
									totalT="O ";
									TV=totalT+totalV;
									*(KC_NAME+2)=(char*)( TV.c_str() );
									KC= atof( (char*)(Marshal::StringToHGlobalAnsi(reader->ReadElementString("overPrice"))).ToPointer() );
									CBet->set_GX_KC(KC_NAME,'\0',KC);
									totalT="U ";
									TV=totalT+totalV;
									*(KC_NAME+2)=(char*)( TV.c_str() );
									KC= atof( (char*)(Marshal::StringToHGlobalAnsi(reader->ReadElementString("underPrice"))).ToPointer() );
									CBet->set_GX_KC(KC_NAME,'\0',KC);
									reader->Read();
									Elem_Name=(const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
								}
								continue;
							}
							if(Elem_Name=="moneyLine")
							{
								*(KC_NAME+1)=(char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
								reader->Read();
								*(KC_NAME+2)="P2";
								KC= atof( (char*)(Marshal::StringToHGlobalAnsi(reader->ReadElementString("awayPrice"))).ToPointer() );
								CBet->set_GX_KC(KC_NAME,'\0',KC);
								*(KC_NAME+2)="P1";
								KC= atof( (char*)(Marshal::StringToHGlobalAnsi(reader->ReadElementString("homePrice"))).ToPointer() );
								CBet->set_GX_KC(KC_NAME,'\0',KC);
								*(KC_NAME+2)="X";
								KC= atof( (char*)(Marshal::StringToHGlobalAnsi(reader->ReadElementString("drawPrice"))).ToPointer() );
								CBet->set_GX_KC(KC_NAME,'\0',KC);
								reader->Read();
								Elem_Name=(const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
								continue;
							}
							*(KC_NAME+1)=(char*)Elem_Name.c_str();
							*(KC_NAME+2)="ERROR PINNACLE KC: NO FOUND TAYPE";
							CBet->set_GX_KC(KC_NAME,'\0',2);
							reader->Skip();
						}
						
					}
					////////////////////////////////////////GAME//////////////////////////////////////////////////////////////////
					if(Elem_Name=="event")
					{
						reader->Read();
						TimeG = (const char*)(Marshal::StringToHGlobalAnsi(reader->ReadElementString("startDateTime"))).ToPointer();
						ITime[0]=atoi( (TimeG.substr(0,4)).c_str() );//Y
						ITime[1]=atoi( (TimeG.substr(5,2)).c_str() );//M
						ITime[2]=atoi( (TimeG.substr(8,2)).c_str() );//D
						ITime[3]=atoi( (TimeG.substr(11,2)).c_str() );//H
						ITime[4]=atoi( (TimeG.substr(14,2)).c_str() );//Mi
						for(int i=0; i<4 ;i++) reader->Skip();
						for(int i=0;i<2;i++)
						{
							Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
							reader->Read();
							if(Elem_Name=="homeTeam") T1 = (const char*)(Marshal::StringToHGlobalAnsi(reader->ReadElementString("name"))).ToPointer();
							if(Elem_Name=="awayTeam") T2 = (const char*)(Marshal::StringToHGlobalAnsi(reader->ReadElementString("name"))).ToPointer();
							for(;;)
							{
								reader->Skip();
								if(reader->NodeType==XmlNodeType::EndElement )break;
							}
							reader->Read();
						}
						int *GAME_Time=CBet->GX_time_convert((int*)ITime,Diff_Time);
						GCH[1]=CBet->set_GX_GAME((char*)T1.c_str(),'\0',(char*)T2.c_str(),'\0', GAME_Time,Goal );
						BI_GAME(CBet->id_t1_onl,(char*)T1.c_str(),CBet->id_t2_onl,(char*)T2.c_str(), GAME_Time);
						if( GCH[0] && GCH[1] )
						{
							reader->Read();
							continue;
						}
						reader->Skip();
					}
					///////////////////////////////////////////CHAMPIONSHIP////////////////////////////////////////////////////////////////////
					if(Elem_Name=="league")
					{
						reader->Read();
						int IDPCH=atoi( (char*)(Marshal::StringToHGlobalAnsi(reader->ReadElementString("id")).ToPointer()) );
						string CHN;
						for(PINNACLE_CHAM *FCHN=p_ch;FCHN;FCHN=FCHN->next)
						{
							if(IDPCH==FCHN->ID_PCH)
							{
								//if( !CBet->set_GX_CHAM( FCHN->PCH_NAME, '\0') ) reader->Skip();
								GCH[0]=CBet->set_GX_CHAM( FCHN->PCH_NAME, '\0');
								BI_CHAM(CBet->id_ch_onl, FCHN->PCH_NAME);
								break;
							}
						}
						break;
					}
					////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					/*if(Elem_Name=="fdTime")
					{
						reader->Read();
						LAST_V=(char*)(Marshal::StringToHGlobalAnsi(reader->Value)).ToPointer();
						L_V=true;
						break;
					}
					else break;*/
					////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					case XmlNodeType::EndElement: //Display the end of the element.
					break;
				}
				if(!reader->Read()) break;
		}
		
	}		
//////////////////////////////////////////////////////////////////////////////
	case 2:return false;//Tennis
		
	case 3:return false;//Hockey
		
	case 4:return false;//Volleyball
		
	case 5:return false;//Basketball
		
	case 6:return false;// Baseball
		
	default:return false;
	}

	//CBet->SendLBM->AddString(L"Download Pinnaclesports: OK");
	
	return true;
}

bool XmlFeed::_188bet(void){return true;}
bool XmlFeed::Sbobet(void){return true;}
bool XmlFeed::Vivaro(void){return true;}

bool XmlFeed::Efubet(void)
{
	int ID_BET=6;
	BI_BET_IDS(ID_BET,ID_BET);//BASE INTERFACE
	int Diff_Time=0;//[HOUR] jamayin tarberutyun
	char** KC_NAME=new char*[2];
	//*(KC_NAME+1)=NULL;
	//float KC;
	int ID_SPORT=1;//<<=========
	CBet->SendLBM->AddString(L"Efubet");
	EFUBET EFB(CBet,this);
	(BL+ID_BET-1)->next=NULL;
	(BL+ID_BET-1)->ptrch=NULL;
	if( !EFB.Ebet->set_GX(BL+ID_BET-1,ID_BET) ) /*ERROR*/ return false;
	EFB.Download_Line(ID_SPORT);
	//CBet->SendLBM->AddString(L"Download Efubet: OK");
	return true;
}

struct UNO
{
	string ID;
	string ID2;
	string name;
};

XmlTextReader* web_gzip(string URL_Coun)
{
	String *SURL=new String(URL_Coun.c_str());
	///////////////////////////////////////////////////////
	HttpWebRequest *request =dynamic_cast<HttpWebRequest*>(WebRequest::Create(SURL));
	request->AutomaticDecompression = DecompressionMethods::GZip;
	//--------------------------------------------------------
	request->Timeout=300*1000;
	//-------------------------------------------------------
	WebResponse *response = request->GetResponse();
	Stream *responseStream = response->GetResponseStream();
	////////////////////////////////////////////////////////
	XmlParserContext *context =new XmlParserContext(nullptr, nullptr, nullptr, XmlSpace::None, Encoding::UTF8);
	XmlTextReader *reader = new XmlTextReader (responseStream,XmlNodeType::Document,context);
	reader->WhitespaceHandling = WhitespaceHandling::None;
	return reader;
}

bool XmlFeed::OddService(int ID_BET)//STUGEL BASE INTERFACE-i FUNKCIANER@
{
	
//////////////////////////////////////|
//////|	BETFAIR			ID = 1	|/////|
//////|	PINNACLESPORTS	ID = 2	|/////|
//////|	188BET			ID = 3	|/////|
//////|	SBOBET			ID = 4	|/////|
//////|	VIVAROBET		ID = 5	|/////|
//////|	EFUBET			ID = 6	|/////|
//////|	BET365			ID = 7	|/////|
//////|	TITANBET		ID = 8	|/////|
//////////////////////////////////////|
	BI_BET_IDS(ID_BET,3);
	XmlTextReader *reader;
	static string Time_Stamp="&timestamp=";
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	static list<UNO> Countries;
	{
	static string Web_Coun="http://xml.oddservice.com/OS/OddsWebService.svc/GetCountries?email=gugooo@mail.ru&password=Newoddservice!&guid=7aa33128-9556-413c-8ead-3ff1c04232d0";
	static string Time_Coun;
	string URL_Coun=Web_Coun;
	if(Time_Coun.length()) URL_Coun+=Time_Stamp+Time_Coun;
	
	///////////////////////////////////////////////////////
	XmlTextReader *reader = web_gzip(URL_Coun);
	//reader = new XmlTextReader(SURL);//LOAD Countries ID AND NAME
	
	string Elem_Name;
	while (reader->Read()) 
	{
		switch (reader->NodeType) 
		{
			case XmlNodeType::Element: // The node is an element.
				Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
				/*if(Elem_Name=="OddService") continue;
				if(Elem_Name=="Header") continue;
				if(Elem_Name=="Status") continue;*/
				if(Elem_Name=="Status")
				{
					reader->Read();
					Elem_Name=(char*)(Marshal::StringToHGlobalAnsi(reader->Value)).ToPointer();
					continue;
				}

				if(Elem_Name=="Description")
				{
					reader->Read();
					Elem_Name=(char*)(Marshal::StringToHGlobalAnsi(reader->Value)).ToPointer();
					continue;
				}

				if(Elem_Name=="Country")
				{
					UNO PTemp;
					PTemp.ID= (char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("id"))).ToPointer();
					//reader->Read();
					PTemp.name=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("name"))).ToPointer();
					Countries.push_back(PTemp);
					break;
				}
				if(Elem_Name=="Timestamp")
				{
					reader->Read();
					Time_Coun=(char*)(Marshal::StringToHGlobalAnsi(reader->Value)).ToPointer(); 
					reader->Read();
					continue;
				}
				continue;
			case XmlNodeType::EndElement: //Display the end of the element.
				Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
				if(Elem_Name=="Results") break;
				continue;
		}
	}
	reader->Close();
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	static list<UNO> Leagues;
	{
	static string Web_Leag="http://xml.oddservice.com/OS/OddsWebService.svc/GetLeagues?email=gugooo@mail.ru&password=Newoddservice!&guid=face94a0-de60-46b9-aef9-24c0a8c5f889";
	static string Time_Leag;
	string URL_Leag=Web_Leag;
	if(Time_Leag.length()) URL_Leag+=Time_Stamp+Time_Leag;
	//String *SURL=new String(URL_Leag.c_str());
	reader = web_gzip(URL_Leag);//LOAD Countries ID AND NAME
	//TextReader *text=reader->GetRemainder();
	string Elem_Name;
	while (reader->Read()) 
	{
		switch (reader->NodeType) 
		{
			case XmlNodeType::Element: // The node is an element.
				Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
				/*if(Elem_Name=="OddService") continue;
				if(Elem_Name=="Header") continue;
				if(Elem_Name=="Status") continue;*/
				if(Elem_Name=="League")
				{
					UNO PTemp;
					PTemp.ID= (char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("id"))).ToPointer();
					PTemp.ID2= (char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("locationID"))).ToPointer();
					//reader->Read();
					PTemp.name=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("name"))).ToPointer();
					Leagues.push_back(PTemp);
					break;
				}
				if(Elem_Name=="Timestamp")
				{
					reader->Read();
					Time_Leag=(char*)(Marshal::StringToHGlobalAnsi(reader->Value)).ToPointer();
					reader->Read();
					continue;
				}
				continue;
			case XmlNodeType::EndElement: //Display the end of the element.
			break;
		}
	}
	reader->Close();
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CString BNAME=CBet->bet_name(ID_BET);
	CBet->SendLBM->AddString(BNAME);
	string TEMP_W;
	static string Web_Odds="http://xml.oddservice.com/OS/OddsWebService.svc/GetSportEvents?email=gugooo@mail.ru&password=Newoddservice!";
	static string Guid="&guid=face94a0-de60-46b9-aef9-24c0a8c5f889";
	static string Guid_In_Play="&guid=7aa33128-9556-413c-8ead-3ff1c04232d0";
	static string Bookmaker="&bookmakers=";
	//////////////////////////////////////////////////////////////////////////
	const int N_B=N_BET;
	static string* Time_S_BK=new string[N_B];
	static string* Time_S_BK_In_Play=new string[N_B];
	static string WEB_ID_BET[]={"41","4","21","36","0","0","8","29"};
	//////////////////////////////////////////////////////////////////////////
	int Diff_Time=180;//[MINUTE]
	bool Birja=false;
	int *Goal=NULL;
	if(ID_BET==1)Birja=true;
	if( !CBet->set_GX(BL+ID_BET-1,3,Birja) ) /*ERROR*/return false;
	if(!CBet->set_GX_IB(ID_BET)) /*ERROR*/return false;
	int ID_SPORT=1;//SOCCER
	if(CBet->set_GX_ID(ID_SPORT)){
		char** KC_NAME=new char*[3];
		*(KC_NAME+2)=NULL;
	for(int i=0;i<2;i++)
	{
		TEMP_W=Web_Odds;
		if(!i)//DOWNLOAD OFFLINE ODDS
		{
			TEMP_W+=Guid;
			if(Time_S_BK[ID_BET-1].length()) TEMP_W+=Time_Stamp+Time_S_BK[ID_BET-1];
		}
		else
		{
			TEMP_W+=Guid_In_Play;
			if( Time_S_BK_In_Play[ID_BET-1].length() ) TEMP_W+=Time_Stamp+Time_S_BK_In_Play[ID_BET-1];
		}
		TEMP_W+=Bookmaker+WEB_ID_BET[ID_BET-1];
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		//String *SURL=new String(TEMP_W.c_str());
		reader=web_gzip(TEMP_W);
		//TextReader *text=reader->GetRemainder();
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		bool Res=false,Outcomes=false,Outcome=false;
		int ETime[5];
		string Elem_Name, League_name, Location_name, T1, T2, kc_name1;
		
		while (reader->Read()) 
		{
			switch (reader->NodeType) 
			{

			case XmlNodeType::Element: // The node is an element.
				Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
				
				if(Elem_Name=="Bookmaker"  & Outcomes & Outcome)
				{
					for(reader->Read();reader->NodeType==XmlNodeType::Element; reader->Read())
					{
						Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
						if(Elem_Name=="Odds")
						{
							string ST=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("Status"))).ToPointer();
							if(ST=="Open")
							{
								string kc_n=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("bet"))).ToPointer();
								*(KC_NAME+1)=(char*)kc_n.c_str();
								string FKC=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("currentPrice"))).ToPointer();
								string Total=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("line"))).ToPointer();
								if(Total.length()) kc_n+=" "+Total;
								CBet->set_GX_KC(KC_NAME, '\0', atof(FKC.c_str()) );
							}
							else
							{
								string kc_n=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("bet"))).ToPointer();
								*(KC_NAME+1)=(char*)kc_n.c_str();
								//string FKC=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("currentPrice"))).ToPointer();
								string Total=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("line"))).ToPointer();
								if(Total.length()) kc_n+=" "+Total;
								CBet->set_GX_KC(KC_NAME, '\0',1 /*atof(FKC.c_str())*/ );
							}
							if(Birja)
							{
								//<--------------
							}
						}
						else /*ERROR*/;
					}
					continue;
				}
				
				if(Elem_Name=="Outcome" & Outcomes)
				{
					kc_name1=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("name"))).ToPointer();
					*KC_NAME=(char*)kc_name1.c_str();
					Outcome=true;
					continue;
				}

				if(Elem_Name=="Header")
				{
					reader->Read();
					Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
					if(Elem_Name=="Status")
					{
						reader->Read();
						Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Value)).ToPointer();
						if(Elem_Name=="000")
						{
							reader->Read(); reader->Read(); reader->Skip(); reader->Read();
							Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Value)).ToPointer();//timestamp
							if(!i) Time_S_BK[ID_BET-1]=Elem_Name;
							else Time_S_BK_In_Play[ID_BET-1]=Elem_Name;
							reader->Read();reader->Read();
							continue;
						}
						else	//ERROR//
						{
							reader->Skip(); reader->Read();
							Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Value)).ToPointer();//Masige ERROR
						}
					}
					else /*ERROR*/;
				}
				
				if(Elem_Name=="Results"){ Res=true; continue;}

				if(Elem_Name=="Event")
				{
					if(Res)
					{
						reader->Read(); reader->Skip();
						Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
						if(Elem_Name=="StartDate")
						{
							reader->Read();
							Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Value)).ToPointer();//Time
							ETime[0]=atoi( (Elem_Name.substr(0,4)).c_str() );//Y
							ETime[1]=atoi( (Elem_Name.substr(5,2)).c_str() );//M
							ETime[2]=atoi( (Elem_Name.substr(8,2)).c_str() );//D
							ETime[3]=atoi( (Elem_Name.substr(11,2)).c_str() );//H
							ETime[4]=atoi( (Elem_Name.substr(14,2)).c_str() );//Mi
							reader->Read(); reader->Read();
						}
						reader->Skip();
						Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
						if(Elem_Name=="LeagueID")
						{
							reader->Read();
							Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Value)).ToPointer();//League_ID
							//UNO *ptr=find_if(Leagues.begin(),Leagues.end(),FU);
							list<UNO>::iterator ptrLeag;
							for(ptrLeag=Leagues.begin();/*ptrLeag!=Leagues.end()*/;ptrLeag++)
							{
								if(ptrLeag==Leagues.end())
								{
									/*ERROR*/
								}
								if(ptrLeag->ID==Elem_Name){League_name=ptrLeag->name;break;}
							}
							reader->Read();reader->Read();
						}
	
						//reader->Read();
						Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
						if(Elem_Name=="LocationID")
						{
							reader->Read();
							Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Value)).ToPointer();//Location_ID
							list<UNO>::iterator ptrLoc;
							for(ptrLoc=Countries.begin();/*ptrLoc!=Countries.end()*/;ptrLoc++)
							{
								if(ptrLoc==Countries.end())
								{
									/*ERROR*/
								}
								if(ptrLoc->ID==Elem_Name){Location_name=ptrLoc->name;break;}

							}
							reader->Read();reader->Read();reader->Skip();
						}
					
						string Cham_Name=Location_name+'/'+League_name;//CHAMPIONSHIP
						bool GCH[2];
						GCH[0]=CBet->set_GX_CHAM( (char*)Cham_Name.c_str(), '\0');
						BI_CHAM(CBet->id_ch_onl,(char*)Cham_Name.c_str());//BASE INTERFACE
						//if(CHAM)
						{
							reader->Skip();// reader->Skip();
							bool BO[4];
							for(int i=0;i<4;i++)BO[i]=false;
							for(; ; reader->Read())
							{
								
								Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
								if(Elem_Name=="CoverageLevel") {/*reader->Read();reader->Read();*/ continue;}
								if(Elem_Name=="HomeTeam"){BO[0]=true; T1=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("Name"))).ToPointer();continue;}//#1
								if(Elem_Name=="AwayTeam"){BO[1]=true; T2=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("Name"))).ToPointer();continue;}//#2
								if(Elem_Name=="Scores") 
								{
									if(reader->IsStartElement() && reader->IsEmptyElement) continue;
									for(;reader->NodeType != XmlNodeType::EndElement;reader->Read()); continue;
								}
								if(Elem_Name=="Scorers") //#3
								{
									BO[2]=true;
									if(reader->IsStartElement() && reader->IsEmptyElement) continue;
									//reader->Skip(); continue;
									for(;reader->NodeType != XmlNodeType::EndElement;reader->Read()); continue;
								}
								if(Elem_Name=="Cards") //#4
								{
									BO[3]=true;
									if(reader->IsStartElement() && reader->IsEmptyElement) continue;
									//reader->Skip(); continue;
									for(;reader->NodeType != XmlNodeType::EndElement;reader->Read()); continue;
								}
								if(BO[0] & BO[1] & BO[2] & BO[3]) break;
							}
							int* GAME_Time=CBet->GX_time_convert((int*)ETime,Diff_Time);
							GCH[1]=CBet->set_GX_GAME((char*)T1.c_str(),'\0',(char*)T2.c_str(),'\0', GAME_Time,Goal);
							BI_GAME(CBet->id_t1_onl,(char*)T1.c_str(),CBet->id_t2_onl,(char*)T2.c_str(),GAME_Time);//BASE INTERFACE
							if(GCH[0] && GCH[1])
							{
								//Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
								if(Elem_Name=="Outcomes"){ Outcomes=true;continue;}
							}
							else
							{
								for(reader->Skip();reader->NodeType==XmlNodeType::Element;reader->Skip());
								continue;
							}
						}
						/*else
						{
							for(reader->Skip();reader->NodeType==XmlNodeType::Element;reader->Skip());
							continue;
						}*/
					}
					else /*ERROR*/;
				}

				

			case XmlNodeType::EndElement: //Display the end of the element.
				{Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
				if(Elem_Name=="Results") Res=false;
				if(Elem_Name=="Outcomes") Outcomes=false;
				if(Elem_Name=="Outcome") Outcome=false;}
				break;
			}
		}
		reader->Close();
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}}
	return true;
}

sport* XmlFeed::GET_ACCESS_F()
{
	return BL;
}

///////////////////////////////ASYNC///////////////////////////////////////////////////////////////////////////////

////////////////////[BETFAIR]
TextReader* XmlFeed::Betfair_XML_Download(void)
{
	CBet->SendLBM->AddString(L"DOWNLOAD BETFAIR (XML)");
	///////////////////////////////////////////////////////
	WebRequest *request = WebRequest::Create(BETFAIR_SOCCER); 
	WebResponse *response = request->GetResponse();
	Stream *responseStream = response->GetResponseStream(); 
	////////////////////////////////////////////////////////
	XmlParserContext *context =new XmlParserContext(nullptr, nullptr, nullptr, XmlSpace::None, Encoding::UTF8);
	XmlTextReader *reader = new XmlTextReader(responseStream,XmlNodeType::Document,context);
	reader->WhitespaceHandling = WhitespaceHandling::None;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	TextReader* TR=reader->GetRemainder();
	return TR;
}

bool XmlFeed::Betfair_Xml_ADD(TextReader* XML_FILE)
{
	int ID_BET=1;
	BI_BET_IDS(ID_BET,ID_BET);//BASE INTERFACE
	int *Goal=NULL;
	int Diff_Time=180;//[MINUT] jamayin tarberutyun
	char** KC_NAME=new char*[3];
	*(KC_NAME+2)=NULL;
	float KC;
	float LAY;
	int ID_SPORT=1;//<<=========
	(BL+ID_BET-1)->next=NULL;
	(BL+ID_BET-1)->ptrch=NULL;
	if( !CBet->set_GX(BL+ID_BET-1,ID_BET,true) ) /*ERROR*/return false;

	switch(ID_SPORT)
	{
	case 1://Football(Soccer)
	CBet->SendLBM->AddString(L"ADD Betfair (XML)");
////////////////////////////////////////////////////////////////////////////////////////////////////
if(CBet->set_GX_ID(ID_SPORT))
{

	XmlTextReader *reader = new XmlTextReader(XML_FILE);
	reader->WhitespaceHandling = WhitespaceHandling::None;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////System Time///////
	SYSTEMTIME sti;
	GetLocalTime(&sti);
	int STime[5];
	STime[0]=sti.wYear;
	STime[1]=sti.wMonth;
	STime[2]=sti.wDay;
	STime[3]=sti.wHour;
	STime[4]=sti.wMinute;
	int *STiD=CBet->GX_time_convert(STime,int((CBet->IGA->Filter).fr_h));
	for(int i=0;i<5;i++) STime[i]=*(STiD+i);
	/////////////////////////
	string Elem_Name;
	string BHM;//hour minute
	string Btime;
	string CH_and_G;
	string CH;
	string T1;
	string T2;
	int Bdate[5];//0-year, 1-month, 2-day, 3-hour, 4-minute
	int *CBD;
	try
	{
		while(true)
		{
			switch(reader->NodeType)
			{
				case XmlNodeType::Element: 
					Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
					//if(EN=="betfair");
					if(Elem_Name=="selection")
					{
						*(KC_NAME+1)=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("name"))).ToPointer();
						string kcname=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("backp1") )).ToPointer();
						KC=atof(kcname.c_str());
						if( int(KC) ) CBet->set_GX_KC(KC_NAME,'\0',KC);
						
						string layname=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("layp1") )).ToPointer();
						LAY=-atof( layname.c_str() );
						if( int(LAY) ) CBet->set_GX_KC(KC_NAME,'\0',LAY);
						
						reader->Read();
						continue;
					}
					if(Elem_Name=="subevent")
					{
						*KC_NAME=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("title"))).ToPointer();
						reader->Read();
						continue;
					}
					//--------------------------------------------------------------------------------------------------
					if(Elem_Name=="event")
					{
						Btime=(const char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("date"))).ToPointer();
						Bdate[0]=atoi( (Btime.substr(6,4)).c_str() );//year
						if(Bdate[0]>=STime[0])
						{
							Bdate[1]=atoi( (Btime.substr(3,2)).c_str() );//month
							Bdate[2]=atoi( (Btime.substr(0,2)).c_str() );//day
							CH_and_G=(const char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("name"))).ToPointer();
							reader->Read();
							Elem_Name=(const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
							BHM=(const char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("time"))).ToPointer();
							Bdate[3]=atoi( (BHM.substr(0,2)).c_str() );//hour
							Bdate[4]=atoi( (BHM.substr(3,2)).c_str() );//min
							CBD=CBet->GX_time_convert(Bdate,Diff_Time);
							bool GXT=false;
							if(*(CBD)>STime[0]) GXT=true;
							else
							{
								if(*(CBD)==STime[0])
								{
									if(*(CBD+1)>=STime[1]) GXT=true;
								}
							}
							if(GXT/**(CBD+1)>=STime[1] &&  *(CBD+2)>=STime[2]*/)
							{
								
								unsigned int pos = CH_and_G.find("/Fixtures");
								if(int(pos)==-1) pos = CH_and_G.find("/Fixtues");
								if(int(pos)==-1) pos = CH_and_G.find("/To Qualify/");
								//////////////////////////////////////////////////////////////////////////////////
									////////////////////////////////////
									if(int(pos)==-1)
									{
										CBet->set_GX_CHAM((char*)CH_and_G.c_str(),'\0');
										for(;Elem_Name!="event";)
										{
											reader->Skip();
											Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
										}
										continue;
									}
									/////////////////////////////////////
								/////////////////////////////////////////////////////////////////////////////
								CH=CH_and_G.substr(0,pos);
								unsigned pos1=CH_and_G.find("/",pos+1)+1;
								unsigned pos2=CH_and_G.find(" v ",pos1);
								if(int(pos1)!=-1 && int(pos2)!=-1)
								{
									T1=CH_and_G.substr(pos1,(pos2-pos1));
									T2=CH_and_G.substr(pos2+3);
									bool CHG[2];
									CHG[0]=CBet->set_GX_CHAM((char*)CH.c_str(),'\0');//CHAMPIONSHIP
									BI_CHAM(CBet->id_ch_onl,(char*)CH.c_str());//BASE INTERFACE
									CHG[1]=CBet->set_GX_GAME((char*)T1.c_str(),'\0',(char*)T2.c_str(),'\0',CBD,Goal );
									BI_GAME(CBet->id_t1_onl,(char*)T1.c_str(),CBet->id_t2_onl,(char*)T2.c_str(),CBD);
									if(CHG[0] && CHG[1]) continue;	//GAME								
								}
							}

							/////////////////////////////////////////////////////////////////////////////////////
							for(;Elem_Name!="event";)
							{
								reader->Skip();
								Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
							}
							continue;
							//////////////////////////////////////////////////////////////////////////////////////

						}
						reader->Skip();
						Elem_Name=(const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
						continue;
						
					}
					//--------------------------------------------------------------------------------------------------
				break;
				
				case XmlNodeType::EndElement:				
					break;
			}
			if(! reader->Read() )break;
			Elem_Name=(const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
		}
	}
	catch(System::Exception *ex)
	{
		//ERROR
		CBet->SendLBM->AddString(L"Download Betfair: ERROR");
	}
	//CBet->SendLBM->AddString(L"Download Betfair: OK");

}
////////////////////////////////////////////////////////////////////////////////////////////////////
	case 2:return false;//Tennis
		
	case 3:return false;//Hockey
		
	case 4:return false;//Volleyball
		
	case 5:return false;//Basketball
		
	case 6:return false;// Baseball
		
	default:return false;
	}
}

B_Line* XmlFeed::Betfair_WEB_Download(void)
{
	CBet->SendLBM->AddString(L"DOWNLOAD BETFAIR (Node_JS)");
	BETFAIR BF;
	return BF.StartL();
}

bool XmlFeed::Betfair_WEB_ADD(B_Line* WEB_FILE)
{
	/////////////////////////////////////////////
	int ID_BET=1;
	BI_BET_IDS(ID_BET,ID_BET);//BASE INTERFACE
	int *Goal=NULL;
	int Diff_Time=180;//[MINUT] jamayin tarberutyun
	char** KC_NAME=new char*[3];
	*(KC_NAME+2)=NULL;
	int ID_SPORT=1;//<<=========
	(BL+ID_BET-1)->next=NULL;
	(BL+ID_BET-1)->ptrch=NULL;
	if( !CBet->set_GX(BL+ID_BET-1,ID_BET,true) ) /*ERROR*/return false;
	CBet->SendLBM->AddString(L"ADD Betfair (Node_JS)");
	/////////////////////////////////////////////
	string patch,Mname,MStatus;
	string CH,T1,T2;
	int *CBD;
	if(CBet->set_GX_ID(ID_SPORT))
	{
		BETFAIR BF;
		B_Line *BL=WEB_FILE;
		for(B_Line *TG=BL;TG;TG=TG->next)
		{
			//-------------------------------------------------------------------------------------------
			patch=(const char*)(TG->PatchGame);
			unsigned int pos = patch.find("\\Fixtures");
			if(int(pos)==-1) pos = patch.find("\\Fixtues");
			if(int(pos)==-1) pos = patch.find("\\To Qualify/");
			if(int(pos)==-1)
			{
				CBet->set_GX_CHAM((char*)patch.c_str(),'\0');//SET CHAMPIONSHIP
				continue;
			}
			CH=patch.substr(8,pos-8);
			CH+='\0';
			for(;int(CH.find("\\"))!=-1;) CH.replace(CH.find("\\"),1,"/");
			unsigned int pos1=patch.find("\\",pos+1)+1;
			unsigned int pos2=patch.find(" v ",pos1);
			if(int(pos1)!=-1 && int(pos2)!=-1)
			{
				T1=patch.substr(pos1,(pos2-pos1));
				T2=patch.substr(pos2+3);
				bool GCH[2];
				GCH[0]=CBet->set_GX_CHAM((char*)CH.c_str(),'\0');
				BI_CHAM(CBet->id_ch_onl,(char*)CH.c_str());//BASE INTERFACE
				CBD=CBet->GX_time_convert( (int*)(CBet->GX_TIME_U((const char*)TG->DateOfGame)), Diff_Time);
				GCH[1]=CBet->set_GX_GAME((char*)T1.c_str(),'\0',(char*)T2.c_str(),'\0',CBD,Goal );
				BI_GAME(CBet->id_t1_onl,(char*)T1.c_str(),CBet->id_t2_onl,(char*)T2.c_str(),CBD);//BASE INTERFCE
				if( !GCH[0] | !GCH[1] )	continue;
			}
			//-------------------------------------------------------------------------------------------
			for(BMarket *TM=TG->ptr_BMarket;TM;TM=TM->next)
			{
				int Z=0;
				for(;*(TM->MName+Z)!='|';Z++);
				*(TM->MName+Z)='\0';
				int C;
				for(C=++Z;*(TM->MName+C)!='\n';C++);
				*(TM->MName+C)='\0';
				MStatus=(const char*)(TM->MName+Z);
				*KC_NAME=TM->MName;//MARKET NAME
				if(MStatus!="ACTIVE")continue;
				for(BOdds *TO=TM->ptr_BOdds;TO;TO=TO->next)
				{
					for(Z=0;*(TO->KC_name+Z)!='|';Z++);
					*(TO->KC_name+Z)='\0';
					*(KC_NAME+1)=TO->KC_name;
					if(TO->Back>1) CBet->set_GX_KC(KC_NAME,'\0',TO->Back);//SET MARKET AND BACK ODDS
					if(TO->Lay>1) CBet->set_GX_KC(KC_NAME,'\0',-TO->Lay);//SET MARKET AND LAY ODDS
				}
			}
		}
	}
	return true;
}

///////////////////[PINNACLESPORTS]
TextReader* XmlFeed::Pinnacle_XML_Download(void)
{
	static bool P_CH_ID=true;
	XmlTextReader *reader;
	if(P_CH_ID)
	{
		CBet->SendLBM->AddString(L"DOWNLOAD PINNACLE");
		reader = new XmlTextReader("http://api.pinnaclesports.com/v1/leagues?sportid=29");//LOAD CHAM ID FOR PINNACLE
		PinnacleChName=reader->GetRemainder();
		P_CH_ID=false;
	}
	//////////////////////////////////////
	reader = new XmlTextReader("http://api.pinnaclesports.com/v1/feed?sportid=29&clientid=VA446096&apikey=d2e6f564-4726-46a1-871e-edefc57a74ed&oddsformat=1");
	return reader->GetRemainder();
}

bool XmlFeed::Pinnacle_Xml_ADD(TextReader* XML_FILE)
{
	int ID_BET=2;
	BI_BET_IDS(ID_BET,ID_BET);
	int *Goal=NULL;
	int Diff_Time=181;//[MINUTE]
	char** KC_NAME=new char*[4];
	*(KC_NAME+3)=NULL;
	float KC;
	int ID_SPORT=1;//<<=========
	(BL+ID_BET-1)->next=NULL;
	(BL+ID_BET-1)->ptrch=NULL;
	if( !CBet->set_GX(BL+ID_BET-1,ID_BET) ) /*ERROR*/return false;
	static PINNACLE_CHAM *p_ch=NULL;
	PINNACLE_CHAM *PTemp;
	string Elem_Name;
	string TimeG;
	string T1;
	string T2;
	int ITime[5];
	string totalV;
	string totalT;
	string TV;
	bool GCH[2];
	switch(ID_SPORT)
	{
	case 1://Football(Soccer)
		CBet->SendLBM->AddString(L"ADD Pinnacle");
//////////////////////////////////////////////////////////////////////////////
	if(CBet->set_GX_ID(ID_SPORT))
	{
		XmlTextReader *reader;
	//////////////LOAD CHAM ID///////////////////
		if(!p_ch)
		{
			reader = new XmlTextReader(PinnacleChName);//LOAD CHAM ID FOR PINNACLE
			reader->WhitespaceHandling = WhitespaceHandling::None;
			while (reader->Read()) 
			{
				switch (reader->NodeType) 
				{
					case XmlNodeType::Element: // The node is an element.
					Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
					if(Elem_Name=="league")
					{
						PTemp=new PINNACLE_CHAM;
						PTemp->ID_PCH=atoi(  (char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("id"))).ToPointer()  );
						reader->Read();
						PTemp->PCH_NAME=(char*)(Marshal::StringToHGlobalAnsi(reader->Value)).ToPointer();
						PTemp->next=p_ch;
						p_ch=PTemp;
						break;
					}
					else break;
					case XmlNodeType::EndElement: //Display the end of the element.
					break;
				}
			}
			reader->Close();
	
		}
	/////////////////////////////////////////
		reader=new XmlTextReader(XML_FILE);
		reader->WhitespaceHandling = WhitespaceHandling::None;
		char* P_CH_NAME=NULL;
		bool CH_P=false;
		while (true) 
		{
				switch (reader->NodeType) 
				{
					case XmlNodeType::Element: // The node is an element.
					Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
					////////////////////////////////////////KC//////////////////////////////////////////////////////////////////
					if(Elem_Name=="period")
					{
						reader->Read(); reader->Skip();
						*KC_NAME=(char*)(Marshal::StringToHGlobalAnsi(reader->ReadElementString("description"))).ToPointer();
						reader->Skip();
						for(;;)
						{
							Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
							if(Elem_Name=="maxBetAmount"){reader->Skip(); continue;}
							if(Elem_Name=="period" && reader->NodeType==XmlNodeType::EndElement)break;

							if(Elem_Name=="spreads")
							{
								reader->Read();
								Elem_Name=(const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
								*(KC_NAME+1)=(char*)Elem_Name.c_str();
								for(;Elem_Name=="spread" && reader->NodeType==XmlNodeType::Element;)
								{
									reader->Read();
									totalV=(const char*)(Marshal::StringToHGlobalAnsi(reader->ReadElementString("awaySpread"))).ToPointer();
									totalT="F2 ";
									TV=totalT+totalV;
									*(KC_NAME+2)=(char*)TV.c_str();
									KC= atof( (char*)(Marshal::StringToHGlobalAnsi(reader->ReadElementString("awayPrice"))).ToPointer() );
									CBet->set_GX_KC(KC_NAME,'\0',KC);
									totalV=(const char*)(Marshal::StringToHGlobalAnsi(reader->ReadElementString("homeSpread"))).ToPointer();
									totalT="F1 ";
									TV=totalT+totalV;
									*(KC_NAME+2)=(char*)TV.c_str();
									KC= atof( (char*)(Marshal::StringToHGlobalAnsi(reader->ReadElementString("homePrice"))).ToPointer() );
									CBet->set_GX_KC(KC_NAME,'\0',KC);
									reader->Read();
									Elem_Name=(const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
								}
								continue;
							}
							if(Elem_Name=="totals")
							{
								reader->Read();
								Elem_Name=(const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
								*(KC_NAME+1)=(char*)Elem_Name.c_str();
								for(;Elem_Name=="total" && reader->NodeType==XmlNodeType::Element;)
								{
									reader->Read();
									totalV=(const char*)(Marshal::StringToHGlobalAnsi(reader->ReadElementString("points"))).ToPointer();
									totalT="O ";
									TV=totalT+totalV;
									*(KC_NAME+2)=(char*)( TV.c_str() );
									KC= atof( (char*)(Marshal::StringToHGlobalAnsi(reader->ReadElementString("overPrice"))).ToPointer() );
									CBet->set_GX_KC(KC_NAME,'\0',KC);
									totalT="U ";
									TV=totalT+totalV;
									*(KC_NAME+2)=(char*)( TV.c_str() );
									KC= atof( (char*)(Marshal::StringToHGlobalAnsi(reader->ReadElementString("underPrice"))).ToPointer() );
									CBet->set_GX_KC(KC_NAME,'\0',KC);
									reader->Read();
									Elem_Name=(const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
								}
								continue;
							}
							if(Elem_Name=="moneyLine")
							{
								*(KC_NAME+1)=(char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
								reader->Read();
								*(KC_NAME+2)="P2";
								KC= atof( (char*)(Marshal::StringToHGlobalAnsi(reader->ReadElementString("awayPrice"))).ToPointer() );
								CBet->set_GX_KC(KC_NAME,'\0',KC);
								*(KC_NAME+2)="P1";
								KC= atof( (char*)(Marshal::StringToHGlobalAnsi(reader->ReadElementString("homePrice"))).ToPointer() );
								CBet->set_GX_KC(KC_NAME,'\0',KC);
								*(KC_NAME+2)="X";
								KC= atof( (char*)(Marshal::StringToHGlobalAnsi(reader->ReadElementString("drawPrice"))).ToPointer() );
								CBet->set_GX_KC(KC_NAME,'\0',KC);
								reader->Read();
								Elem_Name=(const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
								continue;
							}
							*(KC_NAME+1)=(char*)Elem_Name.c_str();
							*(KC_NAME+2)="ERROR PINNACLE KC: NO FOUND TAYPE";
							CBet->set_GX_KC(KC_NAME,'\0',2);
							reader->Skip();
						}
						
					}
					////////////////////////////////////////GAME//////////////////////////////////////////////////////////////////
					if(Elem_Name=="event")
					{
						reader->Read();
						TimeG = (const char*)(Marshal::StringToHGlobalAnsi(reader->ReadElementString("startDateTime"))).ToPointer();
						ITime[0]=atoi( (TimeG.substr(0,4)).c_str() );//Y
						ITime[1]=atoi( (TimeG.substr(5,2)).c_str() );//M
						ITime[2]=atoi( (TimeG.substr(8,2)).c_str() );//D
						ITime[3]=atoi( (TimeG.substr(11,2)).c_str() );//H
						ITime[4]=atoi( (TimeG.substr(14,2)).c_str() );//Mi
						for(int i=0; i<4 ;i++) reader->Skip();
						for(int i=0;i<2;i++)
						{
							Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
							reader->Read();
							if(Elem_Name=="homeTeam") T1 = (const char*)(Marshal::StringToHGlobalAnsi(reader->ReadElementString("name"))).ToPointer();
							if(Elem_Name=="awayTeam") T2 = (const char*)(Marshal::StringToHGlobalAnsi(reader->ReadElementString("name"))).ToPointer();
							for(;;)
							{
								reader->Skip();
								if(reader->NodeType==XmlNodeType::EndElement )break;
							}
							reader->Read();
						}
						int *GAME_Time=CBet->GX_time_convert((int*)ITime,Diff_Time);
						if( CBet->GX_TIME_C(GAME_Time, CBet->IGA->Filter.fr_h, CBet->IGA->Filter.to_h) )
						{
							if(CH_P)
							{
								GCH[0]=CBet->set_GX_CHAM( P_CH_NAME, '\0');
								BI_CHAM(CBet->id_ch_onl, P_CH_NAME);
								CH_P=false;
							}
							GCH[1]=CBet->set_GX_GAME((char*)T1.c_str(),'\0',(char*)T2.c_str(),'\0', GAME_Time,Goal );
							BI_GAME(CBet->id_t1_onl,(char*)T1.c_str(),CBet->id_t2_onl,(char*)T2.c_str(), GAME_Time);
							if( GCH[0] && GCH[1] )
							{
								reader->Read();
								continue;
							}
						}
						reader->Skip();
					}
					///////////////////////////////////////////CHAMPIONSHIP////////////////////////////////////////////////////////////////////
					if(Elem_Name=="league")
					{
						reader->Read();
						int IDPCH=atoi( (char*)(Marshal::StringToHGlobalAnsi(reader->ReadElementString("id")).ToPointer()) );
						string CHN;
						for(PINNACLE_CHAM *FCHN=p_ch;FCHN;FCHN=FCHN->next)
						{
							if(IDPCH==FCHN->ID_PCH)
							{
								//if( !CBet->set_GX_CHAM( FCHN->PCH_NAME, '\0') ) reader->Skip();
								/*GCH[0]=CBet->set_GX_CHAM( FCHN->PCH_NAME, '\0');
								BI_CHAM(CBet->id_ch_onl, FCHN->PCH_NAME);*/
								P_CH_NAME=FCHN->PCH_NAME;
								CH_P=true;
								break;
							}
						}
						break;
					}
					////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					/*if(Elem_Name=="fdTime")
					{
						reader->Read();
						LAST_V=(char*)(Marshal::StringToHGlobalAnsi(reader->Value)).ToPointer();
						L_V=true;
						break;
					}
					else break;*/
					////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					case XmlNodeType::EndElement: //Display the end of the element.
					break;
				}
				if(!reader->Read()) break;
		}
		
	}		
//////////////////////////////////////////////////////////////////////////////
	case 2:return false;//Tennis
		
	case 3:return false;//Hockey
		
	case 4:return false;//Volleyball
		
	case 5:return false;//Basketball
		
	case 6:return false;// Baseball
		
	default:return false;
	}

	//CBet->SendLBM->AddString(L"Download Pinnaclesports: OK");
	
	return true;
}

///////////////////[OddService]

void XmlFeed::OddService_XML_Download(int ID_BET, int IPOA)//IPOA= InPlay(0), Offline(1), All(2)
{
//	A_ID_BET=ID_BET;
	A_IPOA=IPOA;
	XmlTextReader *reader;
	//TextReader **as=new TextReader*[8];
	CString BNAME=L"DOWNLOAD "+CString(CBet->bet_name(ID_BET));
	CBet->SendLBM->AddString(BNAME);

	static string Time_Stamp="&timestamp=";
	if(OddServiceCL)
	{
		OddServiceCL=false;
		static string Web_Coun="http://xml.oddservice.com/OS/OddsWebService.svc/GetCountries?email=gugooo@mail.ru&password=Newoddservice!&guid=7aa33128-9556-413c-8ead-3ff1c04232d0";
		string URL_Coun=Web_Coun;
		if(Time_CounA.length()) URL_Coun+=Time_Stamp+Time_CounA;
		reader=web_gzip(URL_Coun);
		OddServiceCount=reader->GetRemainder();
		//////////////////////////
		static string Web_Leag="http://xml.oddservice.com/OS/OddsWebService.svc/GetLeagues?email=gugooo@mail.ru&password=Newoddservice!&guid=face94a0-de60-46b9-aef9-24c0a8c5f889";
		string URL_Leag=Web_Leag;
		if(Time_LeagA.length()) URL_Leag+=Time_Stamp+Time_LeagA;
		reader=web_gzip(URL_Leag);//LOAD Countries ID AND NAME
		OddServiceLeag=reader->GetRemainder();
		OddServiceCL4=false;
	}
	//////////////////////////
	static string Web_Odds="http://xml.oddservice.com/OS/OddsWebService.svc/GetSportEvents?email=gugooo@mail.ru&password=Newoddservice!";
	static string Guid="&guid=face94a0-de60-46b9-aef9-24c0a8c5f889";
	static string Guid_In_Play="&guid=7aa33128-9556-413c-8ead-3ff1c04232d0";
	static string Bookmaker="&bookmakers=";
	static string WEB_ID_BET[]={"41","4","21","36","0","0","8","29"};
	string TEMP_W;
	int i,j;
	if(!IPOA) {i=1; j=2;}
	else
	{
		if(IPOA==1){i=0; j=1;}
		else{i=0; j=2;}
	}
	for(;i<j;i++)
	{
		TEMP_W=Web_Odds;
		if(!i)//DOWNLOAD OFFLINE ODDS
		{
			TEMP_W+=Guid;
			if(Time_S_BKA[ID_BET-1].length()) TEMP_W+=Time_Stamp+Time_S_BKA[ID_BET-1];
			TEMP_W+=Bookmaker+WEB_ID_BET[ID_BET-1];
			reader=web_gzip(TEMP_W);
			//*(OddServiceOffline+ID_BET-1)=reader->GetRemainder();
			(OSIO+ID_BET-1)->Offline=reader->GetRemainder();
		}
		else
		{
			TEMP_W+=Guid_In_Play;
			if( Time_S_BK_In_PlayA[ID_BET-1].length() ) TEMP_W+=Time_Stamp+Time_S_BK_In_PlayA[ID_BET-1];
			TEMP_W+=Bookmaker+WEB_ID_BET[ID_BET-1];
			reader=web_gzip(TEMP_W);
			//*(OddServiceInPlay+ID_BET-1)=reader->GetRemainder();
			(OSIO+ID_BET-1)->Inplay=reader->GetRemainder();
		}
		
	}
}

bool XmlFeed::OddService_Xml_ADD(int A_ID_BET)
{
	//////////////////////////////////////|
//////|	BETFAIR			ID = 1	|/////|
//////|	PINNACLESPORTS	ID = 2	|/////|
//////|	188BET			ID = 3	|/////|
//////|	SBOBET			ID = 4	|/////|
//////|	VIVAROBET		ID = 5	|/////|
//////|	EFUBET			ID = 6	|/////|
//////|	BET365			ID = 7	|/////|
//////|	TITANBET		ID = 8	|/////|
//////////////////////////////////////|
	int ID_BET=A_ID_BET;
	int IPOA=A_IPOA;
	BI_BET_IDS(ID_BET,3);
	static list<UNO> Countries;
	static list<UNO> Leagues;
	if(OddServiceCL2){
		OddServiceCL2=false;
		for(;OddServiceCL4;) Sleep(TimeMS);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	{
	///////////////////////////////////////////////////////
	XmlTextReader *reader = new XmlTextReader(OddServiceCount);
	reader->WhitespaceHandling = WhitespaceHandling::None;
	string Elem_Name;
	while (reader->Read()) 
	{
		switch (reader->NodeType) 
		{
			case XmlNodeType::Element: // The node is an element.
				Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
				/*if(Elem_Name=="OddService") continue;
				if(Elem_Name=="Header") continue;
				if(Elem_Name=="Status") continue;*/
				if(Elem_Name=="Status")
				{
					reader->Read();
					Elem_Name=(char*)(Marshal::StringToHGlobalAnsi(reader->Value)).ToPointer();
					continue;
				}

				if(Elem_Name=="Description")
				{
					reader->Read();
					Elem_Name=(char*)(Marshal::StringToHGlobalAnsi(reader->Value)).ToPointer();
					continue;
				}

				if(Elem_Name=="Country")
				{
					UNO PTemp;
					PTemp.ID= (char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("id"))).ToPointer();
					//reader->Read();
					PTemp.name=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("name"))).ToPointer();
					Countries.push_back(PTemp);
					break;
				}
				if(Elem_Name=="Timestamp")
				{
					reader->Read();
					Time_CounA=(char*)(Marshal::StringToHGlobalAnsi(reader->Value)).ToPointer(); 
					reader->Read();
					continue;
				}
				continue;
			case XmlNodeType::EndElement: //Display the end of the element.
				Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
				if(Elem_Name=="Results") break;
				continue;
		}
	}
	//reader->Close();
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	{
	XmlTextReader *reader = new XmlTextReader(OddServiceLeag);//LOAD Countries ID AND NAME
	reader->WhitespaceHandling = WhitespaceHandling::None;
	string Elem_Name;
	while (reader->Read()) 
	{
		switch (reader->NodeType) 
		{
			case XmlNodeType::Element: // The node is an element.
				Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
				/*if(Elem_Name=="OddService") continue;
				if(Elem_Name=="Header") continue;
				if(Elem_Name=="Status") continue;*/
				if(Elem_Name=="League")
				{
					UNO PTemp;
					PTemp.ID= (char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("id"))).ToPointer();
					PTemp.ID2= (char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("locationID"))).ToPointer();
					//reader->Read();
					PTemp.name=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("name"))).ToPointer();
					Leagues.push_back(PTemp);
					break;
				}
				if(Elem_Name=="Timestamp")
				{
					reader->Read();
					Time_LeagA=(char*)(Marshal::StringToHGlobalAnsi(reader->Value)).ToPointer();
					reader->Read();
					continue;
				}
				continue;
			case XmlNodeType::EndElement: //Display the end of the element.
			break;
		}
	}
	//reader->Close();
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	OddServiceCL3=false;
	}
	CString BNAME=L"ADD "+CString(CBet->bet_name(ID_BET));
	CBet->SendLBM->AddString(BNAME);
	TextReader* TEMP_W;
	//////////////////////////////////////////////////////////////////////////
	const int N_B=N_BET;
	//////////////////////////////////////////////////////////////////////////
	int Diff_Time=180;//[MINUTE]
	bool Birja=false;
	int *Goal=NULL;
	if(ID_BET==1)Birja=true;
	if( !CBet->set_GX(BL+ID_BET-1,3,Birja) ) /*ERROR*/return false;
	if(!CBet->set_GX_IB(ID_BET)) /*ERROR*/return false;
	int ID_SPORT=1;//SOCCER
	if(CBet->set_GX_ID(ID_SPORT)){
	char** KC_NAME=new char*[3];
	*(KC_NAME+2)=NULL;
	int i,jA;
	if(!IPOA) {i=1; jA=2;}
	else
	{
		if(IPOA==1){i=0; jA=1;}
		else{i=0; jA=2;}
	}
	for(;i<jA;i++)
	{
		if(!i)//DOWNLOAD OFFLINE ODDS
		{
			//TEMP_W=*(OddServiceOffline+ID_BET-1);
			TEMP_W=(OSIO+ID_BET-1)->Offline;
		}
		else
		{
			//TEMP_W=*(OddServiceInPlay+ID_BET-1);
			TEMP_W=(OSIO+ID_BET-1)->Inplay;
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		//String *SURL=new String(TEMP_W.c_str());
		XmlTextReader *reader=new XmlTextReader(TEMP_W);
		reader->WhitespaceHandling = WhitespaceHandling::None;
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		bool Res=false,Outcomes=false,Outcome=false;
		int ETime[5];
		string Elem_Name, League_name, Location_name, T1, T2, kc_name1;
		
		for(;OddServiceCL3;) Sleep(TimeMS);

		while (reader->Read()) 
		{
			switch (reader->NodeType) 
			{

			case XmlNodeType::Element: // The node is an element.
				Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
				
				if(Elem_Name=="Bookmaker"  & Outcomes & Outcome)
				{
					for(reader->Read();reader->NodeType==XmlNodeType::Element; reader->Read())
					{
						Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
						if(Elem_Name=="Odds")
						{
							string ST=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("Status"))).ToPointer();
							if(ST=="Open")
							{
								string kc_n=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("bet"))).ToPointer();
								*(KC_NAME+1)=(char*)kc_n.c_str();
								string FKC=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("currentPrice"))).ToPointer();
								string Total=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("line"))).ToPointer();
								if(Total.length()) kc_n+=" "+Total;
								CBet->set_GX_KC(KC_NAME, '\0', atof(FKC.c_str()) );
							}
							else
							{
								string kc_n=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("bet"))).ToPointer();
								*(KC_NAME+1)=(char*)kc_n.c_str();
								//string FKC=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("currentPrice"))).ToPointer();
								string Total=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("line"))).ToPointer();
								if(Total.length()) kc_n+=" "+Total;
								CBet->set_GX_KC(KC_NAME, '\0',1 /*atof(FKC.c_str())*/ );
							}
							if(Birja)
							{
								//<--------------
							}
						}
						else /*ERROR*/;
					}
					continue;
				}
				
				if(Elem_Name=="Outcome" & Outcomes)
				{
					kc_name1=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("name"))).ToPointer();
					*KC_NAME=(char*)kc_name1.c_str();
					Outcome=true;
					continue;
				}

				if(Elem_Name=="Header")
				{
					reader->Read();
					Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
					if(Elem_Name=="Status")
					{
						reader->Read();
						Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Value)).ToPointer();
						if(Elem_Name=="000")
						{
							reader->Read(); reader->Read(); reader->Skip(); reader->Read();
							Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Value)).ToPointer();//timestamp
							if(!i) Time_S_BKA[ID_BET-1]=Elem_Name;
							else Time_S_BK_In_PlayA[ID_BET-1]=Elem_Name;
							reader->Read();reader->Read();
							continue;
						}
						else	//ERROR//
						{
							reader->Skip(); reader->Read();
							Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Value)).ToPointer();//Masige ERROR
						}
					}
					else /*ERROR*/;
				}
				
				if(Elem_Name=="Results"){ Res=true; continue;}

				if(Elem_Name=="Event")
				{
					if(Res)
					{
						reader->Read(); reader->Skip();
						Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
						if(Elem_Name=="StartDate")
						{
							reader->Read();
							Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Value)).ToPointer();//Time
							ETime[0]=atoi( (Elem_Name.substr(0,4)).c_str() );//Y
							ETime[1]=atoi( (Elem_Name.substr(5,2)).c_str() );//M
							ETime[2]=atoi( (Elem_Name.substr(8,2)).c_str() );//D
							ETime[3]=atoi( (Elem_Name.substr(11,2)).c_str() );//H
							ETime[4]=atoi( (Elem_Name.substr(14,2)).c_str() );//Mi
							reader->Read(); reader->Read();
						}
						reader->Skip();
						Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
						if(Elem_Name=="LeagueID")
						{
							reader->Read();
							Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Value)).ToPointer();//League_ID
							//UNO *ptr=find_if(Leagues.begin(),Leagues.end(),FU);
							list<UNO>::iterator ptrLeag;
							for(ptrLeag=Leagues.begin();/*ptrLeag!=Leagues.end()*/;ptrLeag++)
							{
								if(ptrLeag==Leagues.end())
								{
									/*ERROR*/
								}
								if(ptrLeag->ID==Elem_Name){League_name=ptrLeag->name;break;}
							}
							reader->Read();reader->Read();
						}
	
						//reader->Read();
						Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
						if(Elem_Name=="LocationID")
						{
							reader->Read();
							Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Value)).ToPointer();//Location_ID
							list<UNO>::iterator ptrLoc;
							for(ptrLoc=Countries.begin();/*ptrLoc!=Countries.end()*/;ptrLoc++)
							{
								if(ptrLoc==Countries.end())
								{
									/*ERROR*/
								}
								if(ptrLoc->ID==Elem_Name){Location_name=ptrLoc->name;break;}

							}
							reader->Read();reader->Read();reader->Skip();
						}
					
						string Cham_Name=Location_name+'/'+League_name;//CHAMPIONSHIP
						bool GCH[2];
						GCH[0]=CBet->set_GX_CHAM( (char*)Cham_Name.c_str(), '\0');
						BI_CHAM(CBet->id_ch_onl,(char*)Cham_Name.c_str());//BASE INTERFACE
						//if(CHAM)
						{
							reader->Skip();// reader->Skip();
							bool BO[4];
							for(int k=0;k<4;k++)BO[k]=false;
							for(; ; reader->Read())
							{
								
								Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
								if(Elem_Name=="CoverageLevel") {/*reader->Read();reader->Read();*/ continue;}
								if(Elem_Name=="HomeTeam"){BO[0]=true; T1=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("Name"))).ToPointer();continue;}//#1
								if(Elem_Name=="AwayTeam"){BO[1]=true; T2=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("Name"))).ToPointer();continue;}//#2
								if(Elem_Name=="Scores") 
								{
									if(reader->IsStartElement() && reader->IsEmptyElement) continue;
									for(;reader->NodeType != XmlNodeType::EndElement;reader->Read()); continue;
								}
								if(Elem_Name=="Scorers") //#3
								{
									BO[2]=true;
									if(reader->IsStartElement() && reader->IsEmptyElement) continue;
									//reader->Skip(); continue;
									for(;reader->NodeType != XmlNodeType::EndElement;reader->Read()); continue;
								}
								if(Elem_Name=="Cards") //#4
								{
									BO[3]=true;
									if(reader->IsStartElement() && reader->IsEmptyElement) continue;
									//reader->Skip(); continue;
									for(;reader->NodeType != XmlNodeType::EndElement;reader->Read()); continue;
								}
								if(BO[0] & BO[1] & BO[2] & BO[3]) break;
							}
							int* GAME_Time=CBet->GX_time_convert((int*)ETime,Diff_Time);
							GCH[1]=CBet->set_GX_GAME((char*)T1.c_str(),'\0',(char*)T2.c_str(),'\0', GAME_Time,Goal);
							BI_GAME(CBet->id_t1_onl,(char*)T1.c_str(),CBet->id_t2_onl,(char*)T2.c_str(),GAME_Time);//BASE INTERFACE
							if(GCH[0] && GCH[1])
							{
								//Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
								if(Elem_Name=="Outcomes"){ Outcomes=true;continue;}
							}
							else
							{
								for(reader->Skip();reader->NodeType==XmlNodeType::Element;reader->Skip());
								continue;
							}
						}
						/*else
						{
							for(reader->Skip();reader->NodeType==XmlNodeType::Element;reader->Skip());
							continue;
						}*/
					}
					else /*ERROR*/;
				}

				

			case XmlNodeType::EndElement: //Display the end of the element.
				{Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
				if(Elem_Name=="Results") Res=false;
				if(Elem_Name=="Outcomes") Outcomes=false;
				if(Elem_Name=="Outcome") Outcome=false;}
				break;
			}
		}
		reader->Close();
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}}
	return true;
}

///////////////////[Vivarobet]

TextReader* XmlFeed::Vivaro_XML_Download(void)
{
	CBet->SendLBM->AddString(L"DOWNLOAD VIVARO");
	//////////////////////////////////////
	XmlTextReader *reader = new XmlTextReader("http://old.vivarobet.am/FLSports/Client/Game.php?lg=eng");
	return reader->GetRemainder();
}

int *GetVbetTime(int Ho, int Mi)
{
	time_t Rtime;
	time(&Rtime);
	tm *TimeNow=localtime(&Rtime);
	TimeNow->tm_sec=0;
	TimeNow->tm_hour=Ho;
	TimeNow->tm_min=Mi;

	time_t GameTime=mktime(TimeNow);
	time_t MyTime=time(NULL);
	if( (GameTime-MyTime) > 11*3600 )
	{
		(TimeNow->tm_mday)--;
		GameTime=mktime(TimeNow);
		TimeNow=localtime(&GameTime);
	}
	int *GT=new int[5];
	*GT=TimeNow->tm_year+1900;
	*(GT+1)=TimeNow->tm_mon+1;
	*(GT+2)=TimeNow->tm_mday;
	*(GT+3)=TimeNow->tm_hour;
	*(GT+4)=TimeNow->tm_min;
	return GT;
}

bool XmlFeed::Vivaro_Xml_ADD(TextReader* XML_FILE)
{
	int ID_BET=5;
	BI_BET_IDS(ID_BET,ID_BET);
	int *Goal=NULL;
	int Diff_Time=0;//[MINUTE]
	char** KC_NAME=new char*[3];
	*(KC_NAME+2)=NULL;
	float KC;
	int ID_SPORT=1;//<<=========Football
	(BL+ID_BET-1)->next=NULL;
	(BL+ID_BET-1)->ptrch=NULL;
	if( !CBet->set_GX(BL+ID_BET-1,ID_BET) ) /*ERROR*/return false;
	string Elem_Name;
	string TimeG;
	string T1;
	string T2;
	int *ITime;
	XmlTextReader *reader=new XmlTextReader(XML_FILE);
	reader->WhitespaceHandling = WhitespaceHandling::None;
	CBet->SendLBM->AddString(L"ADD Vivaro");
	if( !CBet->set_GX_ID(ID_SPORT))/*ERROR*/return false;
	bool CHG[2];
	bool LS=false;
	bool LE=false;
	reader->Read();
	while (true) 
	{
		switch (reader->NodeType) 
		{
			///////////////////////////
			case XmlNodeType::Element: // The node is an element.
				Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
				if(Elem_Name=="Event" && LE && LS && reader->AttributeCount )
				{
					string KcName=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("Name"))).ToPointer();
					String* Total=reader->GetAttribute("Base");
					if(Total)
					{
						string KcTotal=(char*)(Marshal::StringToHGlobalAnsi( Total )).ToPointer();
						KcName=KcName+KcTotal;
					}
					*(KC_NAME+1)=(char*)KcName.c_str();
					KC=atof( (char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("K"))).ToPointer() );
					CBet->set_GX_KC(KC_NAME,'\0',KC);
					reader->Read();
					continue;
				}
				if(Elem_Name=="Line" && LS)
				{
					*(KC_NAME)=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("Name"))).ToPointer();
					reader->Read();
					Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
					if(Elem_Name=="Row" && reader->NodeType==XmlNodeType::Element) LE=true;
					reader->Read();
					continue;
				}
				if(Elem_Name=="Live")
				{
					reader->Read();
					continue;
				}
				if(Elem_Name=="Game")//SET CHAMPIONSHIP
				{
					string SportTaype=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("Type"))).ToPointer();
					string SportName=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("SportName"))).ToPointer();
					if(SportTaype=="Soccer" && (SportName=="Football" || SportName=="Soccer"))
					{
						string CamName=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("LigaName"))).ToPointer();
						unsigned pos=CamName.find("(LIVE)");
						if(int(pos==-1))
						{
							pos=CamName.find("(live)");
							if(int(pos==-1))
							{
								reader->Skip();
								continue;
							}
						}
						CamName=CamName.substr(0,pos-1);//Campionship name
						string GameStartTime=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("Date"))).ToPointer();
						//**TIME**
						int Ho=atoi( (GameStartTime.substr(0,2)).c_str() );
						int Mi=atoi( (GameStartTime.substr(3,5)).c_str() );
						ITime=GetVbetTime(Ho, Mi);
						*(ITime+1);
						*(ITime+2);
						*(ITime+3);
						*(ITime+4);
						string GoalInfo=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("Info"))).ToPointer();//GOAL<<<<--#
						CHG[0]=CBet->set_GX_CHAM((char*)CamName.c_str(),'\0');//CHAMPIONSHIP
						BI_CHAM(CBet->id_ch_onl,(char*)CamName.c_str());//BASE INTERFACE
						reader->Read();
						continue;
					}
					else {reader->Skip(); continue;}
				}
				if(Elem_Name=="Display")//SET GAME
				{
					for(int Id=2;Id;)
					{
						reader->Read();
						Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
						if(Elem_Name=="Team" && reader->NodeType==XmlNodeType::Element)
						{
							Id--;
							if(Id==1){ T1=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("name"))).ToPointer(); continue; }
							T2=(char*)(Marshal::StringToHGlobalAnsi(reader->GetAttribute("name"))).ToPointer();
						}
					}
					CHG[1]=CBet->set_GX_GAME((char*)T1.c_str(),'\0',(char*)T2.c_str(),'\0',ITime,Goal);
					BI_GAME(CBet->id_t1_onl,(char*)T1.c_str(),CBet->id_t2_onl,(char*)T2.c_str(),ITime);
					for(;;reader->Read()) if(Elem_Name=="Team" && reader->NodeType==XmlNodeType::EndElement) break;
					reader->Read();
					continue;
				}
				if(Elem_Name=="Lines")
				{
					LS=false;
					LE=false;
					if(!CHG[0] || !CHG[1])
					{
						reader->Skip(); 
						continue;
					}
					LS=true;
					reader->Read();
					continue;
				}

				reader->Read();
			/////////////////////////////////			
			case XmlNodeType::XmlDeclaration:
				reader->Read();
				continue;

			/////////////////////////////
			case XmlNodeType::EndElement: //Display the end of the element.
				Elem_Name= (const char*)(Marshal::StringToHGlobalAnsi(reader->Name)).ToPointer();
				if(Elem_Name=="Live")	break;
				else {reader->Read(); continue;}
		}
		if(!reader->Read()) break;
	}


}

