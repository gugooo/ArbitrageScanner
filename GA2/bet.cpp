#include "stdafx.h"
#include "bet.h"
#include "XmlFeed.h"

using namespace std;

//////////////////////////////////////|
//////|	BETFAIR			ID = 1	|/////|
//////|	PINNACLESPORTS	ID = 2	|/////|
//////|	188BET			ID = 3	|/////|
//////|	SBOBET			ID = 4	|/////|
//////|	VIVAROBET		ID = 5	|/////|
//////|	EFUBET			ID = 6	|/////|
//////////////////////////////////////|

bet::bet(CListBox& Cd,Interface_Ga *pIGA,bool B_GX)
{
	SendLBM=&Cd;
	IGA=pIGA;
	n_bet=pIGA->N_BET;
	if(!B_GX)
	{
		load_bet("BASE/KANTORS/BET.b");
		load_id_lge_all();
	}
	sports_name();
	load_cham("BASE/CHAMPIONSHIP/CHAM.b");
	load_team("BASE/TEAM/TEAM.b");
	load_kc("BASE/KC/KC.b");
	G.id_s=0;
	G.next=NULL;
	G.ptrch=NULL;
	V_ALL.GVALL=NULL;
	V_ALL.next=NULL;
	GX_GOAL=NULL;
	/////////////////////////////////
	BASE_GOAL=new GOAL_CH[n_sport];
	for(int i=0; i<n_sport;i++)
	{
		(BASE_GOAL+i)->ID_CH=0;
		(BASE_GOAL+i)->next=NULL;
		(BASE_GOAL+i)->ptrGG=NULL;
	}
	//ADD INTERFACE GA<<-------------------------------------
	CForaC=true;
	BetInPlayKcConvert=new bool[n_bet];

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
	*BetInPlayKcConvert=false;
	*(BetInPlayKcConvert+1)=true;
	*(BetInPlayKcConvert+2)=true;
	*(BetInPlayKcConvert+3)=true;
	*(BetInPlayKcConvert+4)=false;
	*(BetInPlayKcConvert+5)=false;
	*(BetInPlayKcConvert+6)=true;
	*(BetInPlayKcConvert+7)=true;
}

void bet::erl(char* er,bool E)
{
	CString Temp=L"ERROR: ";
	for(int i=0;;i++)
	{
		if((*(er+i))=='\0'){SendLBM->AddString(Temp);break;}
		if((*(er+i))=='\n'){SendLBM->AddString(Temp);}
		Temp+=CString(*(er+i));
	}
}

void bet::col(char* co)
{
	static CString Temp;
	for(int i=0;;i++)
	{
		if((*(co+i))=='\0'){/*SendLBM->AddString(Temp);*/break;}
		if((*(co+i))=='\n'){SendLBM->AddString(Temp);Temp=L"";}
		Temp+=CString((*(co+i)));
	}
}

void bet::load_bet(char* bets_file_name)
{
	col("Loading BET.b...	");
	ifstream inbet(bets_file_name);
	if(!inbet){	erl("EROR: FILE *");	erl(bets_file_name);	erl("* NO FOUND\n\n",true); /*exit(0);*/ }
	inbet>>n_bet;
	bets_name=new char*[n_bet];
	id_lge_all=new bool[n_bet];
	for(int i=0;i<n_bet;i++)
	{
		(*(bets_name+i))=new char[30];
		inbet>>(*(bets_name+i));
	}
	/////////////////////////////interface
	f_bets=new int[n_bet];
	*f_bets=1;
	*(f_bets+1)=4;
	/*(f_bets+2)=3;
	*(f_bets+3)=4;*/
	*(f_bets+2)='\0';
	//---------jameri tarberutyan veracum
	Xml_bet_time=new int[n_bet];
	*Xml_bet_time=-120;//ID_B=1
	*(Xml_bet_time+1)=0;//ID_B=2
	*(Xml_bet_time+2)=0;//ID_B=3
	*(Xml_bet_time+3)=0;//ID_B=4
	*(Xml_bet_time+4)=0;//ID_B=5
	*(Xml_bet_time+5)=0;//ID_B=6
	//---------
	//////////////////////////////
	col("OK\n");
}

void bet::get_bets_name()
{
	for(int i=0;i<n_bet;i++){ col((*(bets_name+i)));col("\n");}
}

char* bet::bet_name(int id)
{
	static char betNAME[][20]=
	{
		"BETFAIR",
		"PINNACLE",
		"188BET",
		"SBOBET",
		"VIVARO",
		"EFUBET",
		"BET365",
		"TITANBET"
	};
	if(0<id && id<=n_bet)
	{
		return betNAME[id-1];/**(bets_name+id-1);*/
	}
	erl("EROR: id_bet\n",true);
	//exit(0);
}

void bet::fix_id_lge()
{
	if(id_bet>0 && id_bet<=n_bet) (id_lge=(*(id_lge_all+id_bet-1)));
	else {erl("\nEROR: ! fix_id_lge() ! not correct 'id_bet'\n",true);/*exit(0);*/}
}

void bet::load_id_lge_all()
{
	for(int i=1;i<=n_bet;i++)
	{
		char* temp=bet_name(i);
		while((*(temp++))!=':') if((*temp)=='\0'){erl("\nEROR: no fixid language 1! ");erl(bet_name(i));erl(" !\n",true);/*exit(0);*/}
		*(temp-1)='\0';
		switch(*temp)
		{
		case 'r':	if((*(++temp))=='u')(*(id_lge_all+i-1))=false; 
					else {erl("EROR: no fixid language 2! ");erl(bet_name(i));erl(" !\n",true);/*exit(0);*/} 
					break;

		case 'u':	if((*(++temp))=='s')(*(id_lge_all+i-1))=true; 
					else {erl("EROR: no fixid language 3! ");erl(bet_name(i)),erl(" !\n",true);/*exit(0);*/}
					break;

		default:	erl("EROR: no fixid language 4! ");erl(bet_name(i)),erl(" !\n",true);/*exit(0);*/
			
		}
	}
}

void bet::FIX_BET(int ID_BET)
{
	if(ID_BET>0 && ID_BET<=n_bet){ id_bet=ID_BET; /*fix_id_lge();*/ }
	else {erl("\nEROR: ! fix_id_lge() ! not correct 'id_bet'\n",true);/*exit(0);*/}
}

//*************************************************//
void bet::sports_name()
{
	col("Loading Sports...	");
	n_sport=6;
	sport_name=new char*[n_sport];
	for(int i=0;i<n_sport;i++)
	{
		(*(sport_name+i))=new char[62];
	}
	
	f(0,"Футбол","Football");
	f(1,"Теннис","Tennis");
	f(2,"Хоккей","Hockey");
	f(3,"Волейбол","Volleyball");
	f(4,"Баскетбол","Basketball");
	f(5,"Бейсбол","Baseball");
	f_sports=new int[n_sport];
	*f_sports=1;
	*(f_sports+1)='\0';
	col("OK\n");
}

int bet::get_sport_id(char* s_name)
{
	int n=0;
	if(id_lge)n=32;

	for(int i=0;i<n_sport;i++)
		{

			for(int j=0;;j++)	
			{
				
				if( (*((*(sport_name+i))+n+j))==(*(s_name+j)) ){ if((*(s_name+j))=='\0') return (id_s_onl=(i+1));}
				else break;
			}
			
		}

	return 0;

}

char* bet::get_sport_name(int ID_SPORT,int ID_BET)
{
	static char sportNAME[][20]=
	{
		"Football",
		"Tennis",
		"Hockey",
		"Volleyball",
		"Basketball",
		"Baseball"
	};
	if(ID_BET>0 && ID_BET<=n_bet && ID_SPORT>0 && ID_SPORT<=n_sport) 
	{
		return sportNAME[ID_SPORT-1];
	}
	else {erl("\nEROR: !get_sport_name()! not correct ID\n",true);/*exit(0);*/}
}

void bet::f(int j,char* ru_n, char* us_n )
	{

		int i=-1;
		do
		{
			 i++;
			(*((*(sport_name+j))+i))=(*(ru_n+i));
		
		}while((*(ru_n+i))!='\0');

		i=-1;
		do
		{
			 i++;
			(*((*(sport_name+j))+32+i))=(*(us_n+i));
		
		}while((*(us_n+i))!='\0');
	}

//**********************************************************//
void bet::load_cham(char* file_name)
{
	col("Loading CHAM.b...	");
	ifstream in_file(file_name);
	if(!in_file){erl("EROR: FILE *");erl(file_name);erl("* NO FOUND\n\n",true);/*exit(0);*/ }
	cham_names=new cham_base* [n_sport];
	n_cham=new int[n_sport];
	int ID_S;
	int n_ch_s;

	int ID_CH;
	char* temp=new char[200*n_bet];

	for(int ns=1;!in_file.eof();ns++)
	{
		in_file>>ID_S;
		//cout<<ID_S<<" "<<get_sport_name(ID_S,1)<<" ";
		char idsch[32];
		if(ID_S<1 || ID_S>n_sport){erl("\nEROR: ID SPORT file ! ");erl(file_name);erl(" !\n");erl("ID_S: ");erl(itoa(ID_S,idsch,10));erl("\n",true);/*exit(0);*/}
		in_file>>n_ch_s;

		*(n_cham+ID_S-1)=n_ch_s;

		//cout<<n_ch_s<<endl<<endl;
		if(!n_ch_s) { (*(cham_names+ID_S-1))=NULL; continue; }
		*(cham_names+ID_S-1)=new cham_base[n_ch_s+1];
		for(int i=0;;i++)
		{
			if(i==n_ch_s) { (*(*(cham_names+ID_S-1)+i)).cham_names=NULL; (*(*(cham_names+ID_S-1)+i)).id_cham=NULL;break;}

			(*(*(cham_names+ID_S-1)+i)).cham_names=new char[200*n_bet];
		}
		
		for(int i=0;i<n_ch_s;i++)
		{
			
			in_file>>ID_CH;
			if(ID_CH!=(i+1)) (*(n_cham+ID_S-1))--;
			(*(*(cham_names+ID_S-1)+i)).id_cham=ID_CH;
			in_file.getline(temp,(200*n_bet),'\n');
			//cout<<ID_CH<<" "<<temp<<endl<<endl;
			for(int j=0,ji=0,n=200,k=0;;j++)	
			{
				if(!ji)for(;*(temp+j)==' ';j++);

				if((*(temp+j))=='=')
				{
					for(;( *(((*(*(cham_names+ID_S-1)+i)).cham_names)+ji-1+n*k) )==' ';ji--);
					( *(((*(*(cham_names+ID_S-1)+i)).cham_names)+ji+n*k) )='\0';
					k++;
					ji=0;
					continue;
				}
				
				if((*(temp+j))=='\0')for(;( *(((*(*(cham_names+ID_S-1)+i)).cham_names)+ji-1+n*k) )==' ';ji--);

				( *(((*(*(cham_names+ID_S-1)+i)).cham_names)+ji+n*k) )=( *(temp+j) );

				ji++;

				if((*(temp+j))=='\0')
				{
					
					for(;k!=n_bet;)( *(((*(*(cham_names+ID_S-1)+i)).cham_names)+n*(++k)) )='\0';
					break;
				}
			}
		}
		if(ns==n_sport)break;
		
	}
	col("OK\n");
}

int bet::get_cham_id(char* CH_name,char End)
{

	char* CH_name_t=CH_name;
	if(!(*(cham_names+id_s_onl-1)))
	{
		out_f_t_CH(CH_name_t,End);
		return 0;
	}
	
	for(int i=0; (*(*(cham_names+id_s_onl-1)+i)).cham_names  &&  (*(*(cham_names+id_s_onl-1)+i)).id_cham ;i++)
	{
		for(int j=0, q=0;;j++,q++)
		{
			
			if( (*(CH_name_t+q))==End && (*((*(*(cham_names+id_s_onl-1)+i)).cham_names+200*(id_bet-1)+j))=='\0')return ((*(*(cham_names+id_s_onl-1)+i)).id_cham);
			if( (*(CH_name_t+q))!=(*((*(*(cham_names+id_s_onl-1)+i)).cham_names+200*(id_bet-1)+j)) )
			{
				if((*((*(*(cham_names+id_s_onl-1)+i)).cham_names+200*(id_bet-1)+j))=='\0')
				{
					if((*(CH_name_t+q))==' ' || (*(CH_name_t+q))=='\r' || (*(CH_name_t+q))=='\t')
					{
						j--;
						continue;
					}
				}
				break;
			}
		}
	}
	out_f_t_CH(CH_name_t,End);
	return 0;
}

void bet::out_f_t_CH(char* CH_name, char End)
{
	if( (IGA->Bets+id_bet_T-1)->add_ch)
	{
	ofstream out_file("TEMP/TEMP_CH.t",ios::app);
	out_file<<id_bet_T<<"	"<<id_s_onl<<"	";
	for(int i=0;*(CH_name+i)!=End;i++)out_file.put(*(CH_name+i));
	out_file<<"\n";
	}
}

char* bet::get_cham_name(int ID_cham, int ID_sport ,int ID_bet)
{

	if(ID_sport<1 || ID_sport>n_sport || !(*(cham_names+ID_sport-1)) ){erl("\nEROR: !get_cham_name()! not correct ID_sport\n",true);/*exit(0);*/}
	
	if(ID_bet<1 || ID_bet>n_bet){erl("\nEROR: !get_cham_name()! not correct ID_bet\n",true);/*exit(0);*/}
	
	if(  ID_cham == ((*(*(cham_names+ID_sport-1)+ID_cham-1)).id_cham)  ) return ( (*(*(cham_names+ID_sport-1)+ID_cham-1)).cham_names+200*(ID_bet-1) );
	
	for(int i=0; (*(*(cham_names+ID_sport-1)+i)).id_cham ;i++)	if(  ID_cham == ((*(*(cham_names+ID_sport-1)+i)).id_cham)  ) return ( (*(*(cham_names+ID_sport-1)+i)).cham_names+200*(ID_bet-1) );
	
	erl("\nEROR: !get_cham_name()! not correct ID_cham\n",true); /*exit(0)*/;
}

//***********************************************************************//
void bet::load_team(char* file_name)
{
	/*bazayum chempionat avelacnelu het mek tex anhrajeshte avelacnel nayev mek kam avel tmi anun*/
	col("Loading TEAM.b...	");
	ifstream in_file(file_name);
	if(!in_file){erl("EROR: FILE *");erl(file_name);erl("* NO FOUND\n\n",true); /*exit(0);*/ }
	team_names=new p_t_b*[n_sport];
	for(int i=0;i<n_sport;i++)
	{
		int Tgh=*(n_cham+i);
		if(!*(n_cham+i)){*(team_names+i)=NULL;continue;}
		*(team_names+i)=new p_t_b[*(n_cham+i)+1];
		(*(team_names+i)+(*(n_cham+i)))->id_cham=0;
		(*(team_names+i)+(*(n_cham+i)))->ptr_b=NULL;
	}
	int ID_S, ID_CH, ID_T, N_T;
	char* temp=new char[100*n_bet];
	for(int ns=0; !in_file.eof() ;ns++)
	{
		if(ns==n_sport)break;
		in_file>>ID_S;
		if(ID_S<1 || ID_S>n_sport){erl("\nEROR: ID SPORT file ! ");erl(file_name);erl(" !\n\n",true);/*exit(0);*/}
		//cout<<"ID_SPORT: "<<ID_S<<"  "<<get_sport_name(ID_S,id_bet)<<"\t N_CHAM: "<<*(n_cham+ns)<<endl<<endl;////////////////
		if(!*(team_names+ID_S-1))continue;
		for(int nch=0; nch < *(n_cham+ns) ;nch++)
		{
			in_file>>ID_CH>>N_T;
			//cout<<"\nID_CH: "<<ID_CH<<"  "<<get_cham_name(ID_CH,ID_S,id_bet)<<"\n	N_T: "<<N_T<<endl;/////////////////////
			(*(*(team_names+ID_S-1)+nch)).id_cham=ID_CH;
			if(!N_T) 
			{
				(*(*(team_names+ID_S-1)+nch)).ptr_b=NULL;
				
				continue;
			}

			(*(*(team_names+ID_S-1)+nch)).ptr_b=new team_base[N_T+1];
			for(int i=0;i<N_T;i++) (*((*(*(team_names+ID_S-1)+nch)).ptr_b+i)).team_name=new char[100*n_bet];
			(*((*(*(team_names+ID_S-1)+nch)).ptr_b+N_T)).team_name=NULL;
			(*((*(*(team_names+ID_S-1)+nch)).ptr_b+N_T)).id_team=0;
			for(int nt=0;nt<N_T;nt++)
			{
				in_file>>ID_T;
				(*((*(*(team_names+ID_S-1)+nch)).ptr_b + nt)).id_team=ID_T;
				in_file.getline(temp,(100*n_bet),'\n');
				for(int j=0, ji=0,n=100,k=0 ;; j++)
				{
					if(!ji)for(;(*(temp+j))==' ';j++);
					if( (*(temp+j))=='=')
					{
						for(; *((*((*(*(team_names+ID_S-1)+nch)).ptr_b + nt)).team_name+ji-1+n*k) == ' ' ;ji--);
						*((*((*(*(team_names+ID_S-1)+nch)).ptr_b + nt)).team_name+ji+n*k)='\0';
						k++;
						ji=0;
						continue;
					}
					if( (*(temp+j)) =='\0') for(;*((*((*(*(team_names+ID_S-1)+nch)).ptr_b + nt)).team_name+ji-1+n*k) == ' ' ;ji--);

					(*((*((*(*(team_names+ID_S-1)+nch)).ptr_b + nt)).team_name+ji+(n*k) ))=(*(temp+j));
					ji++;
					
					if((*(temp+j))=='\0')
					{
						for(;k < n_bet;) *((*((*(*(team_names+ID_S-1)+nch)).ptr_b + nt)).team_name+n*(++k))='\0';
						break;
					}
					
				}
				//cout<<"ID_T: "<<ID_T<<" "<< ((*((*(*(team_names+ID_S-1)+nch)).ptr_b + nt)).team_name+100*(id_bet-1))<<endl;/////////////////
			}

		}
				
	}
	col("OK\n");
}

void bet::get_teams_name(int idbet)
{
	p_t_b** temp1=team_names;
	col("\n");
	char nn[32];
	for(int i=0;*temp1;temp1++,i++)
	{
		col("ID_SPORT: ");col(itoa((i+1),nn,10));col("\n");
		p_t_b* temp2=*team_names;
		for(int q=0;temp2->id_cham/*q<*(n_cham+i)*/;temp2++,q++)
		{
			col("\nID_CHAM: ");col(itoa(temp2->id_cham,nn,10));col("\n");
			team_base* temp3=temp2->ptr_b;
			for(;temp3->team_name;temp3++)
			{
				col("ID_TEAM: ");col(itoa(temp3->id_team,nn,10));col("	");col((temp3->team_name+(idbet-1)*200));col("\n");
			}
		}
	}
}

int bet::get_team_id(char* t_name,char End)
{
	if(!id_ch_onl) return 0;
	char* temp=t_name;
	
	if( (*(team_names+id_s_onl-1)) == NULL ) return 0;
	
	if( (*(*(team_names+id_s_onl-1)+id_ch_onl-1)).ptr_b==NULL )
	{
		out_f_t_T(temp,End);
		return 0;
	}
	
	for(int i=0; (*((*(*(team_names+id_s_onl-1)+id_ch_onl-1)).ptr_b+i)).id_team && (*((*(*(team_names+id_s_onl-1)+id_ch_onl-1)).ptr_b+i)).team_name ;i++)
	{
		for(int j=0;;j++)
		{
			if( *(temp+j)==End && ( *((*((*(*(team_names+id_s_onl-1)+id_ch_onl-1)).ptr_b+i)).team_name+j+100*(id_bet-1))=='\0' || *((*((*(*(team_names+id_s_onl-1)+id_ch_onl-1)).ptr_b+i)).team_name+j+100*(id_bet-1))=='|' ) ) return(*((*(*(team_names+id_s_onl-1)+id_ch_onl-1)).ptr_b+i)).id_team;
			if(*(temp+j) !=  (*((*((*(*(team_names+id_s_onl-1)+id_ch_onl-1)).ptr_b+i)).team_name+j+100*(id_bet-1))) ) break;
		}
	}
	out_f_t_T(temp,End);
	return 0;
}

void bet::out_f_t_T(char* T_name,char E)
{
	if( (IGA->Bets+id_bet_T-1)->add_t)
	{
	ofstream out_file("TEMP/TEMP_T.t",ios::app);
	out_file<<setw(7)<<setiosflags(ios::left)<<id_bet_T<<"| "<<setw(9)<<id_s_onl
		<<"| "<<setw(8)<<id_ch_onl<<"| ";
	for(int i=0;*(T_name+i)!=E;i++)out_file.put(*(T_name+i));
	out_file<<"\n";
	}
}

char* bet::get_team_name(int ID_T, int ID_CH, int ID_S, int ID_B )
{
	//////////////////////////////////KC_NAME-um goler@ avelacnelu hamar
	static bool OneTwo=true;
	if(OneTwo)
	{
		id_t1_onl=ID_T;
		OneTwo=false;
	}
	else
	{
		id_t2_onl=ID_T;
		id_ch_onl=ID_CH;
		id_s_onl=ID_S;
		OneTwo=true;
	}
	//////////////////////////////////
	if(ID_S<1 || ID_S>n_sport || !(*(team_names+ID_S-1)) ){erl("\nEROR: !get_team_name()! not correct ID_sport\n",true);/*exit(0);*/}

	if(ID_B<1 || ID_B>n_bet){erl("\nEROR: !get_cham_name()! not correct ID_bet\n",true);/*exit(0);*/}

	if( ID_CH == (*(*(team_names+ID_S-1)+ID_CH-1)).id_cham )
	{
		if( ID_T== (*((*(*(team_names+ID_S-1)+ID_CH-1)).ptr_b+ID_T-1)).id_team ) return ((*((*(*(team_names+ID_S-1)+ID_CH-1)).ptr_b+ID_T-1)).team_name+100*(ID_B-1));
		else
		{
			for(int i=0; (*((*(*(team_names+ID_S-1)+ID_CH-1)).ptr_b+i)).id_team ;i++) if(ID_T == (*((*(*(team_names+ID_S-1)+ID_CH-1)).ptr_b+i)).id_team ) return ((*((*(*(team_names+ID_S-1)+ID_CH-1)).ptr_b+i)).team_name+100*(ID_B-1));
			erl("\nEROR: !get_team_name()! not correct ID_team\n",true); /*exit(0);*/
		}
	}
	p_t_b* nCH=*(team_names+ID_S-1);
	for(int i=0;nCH->id_cham /*i < *(n_cham+ID_S-1)*/ ;i++, nCH++)
	{
		if( ID_CH == (*(*(team_names+ID_S-1)+i)).id_cham )
		{
			if( ID_T== (*((*(*(team_names+ID_S-1)+i)).ptr_b+ID_T-1)).id_team ) return ((*((*(*(team_names+ID_S-1)+i)).ptr_b+ID_T-1)).team_name+100*(ID_B-1));
			else
			{
				for(int j=0; (*((*(*(team_names+ID_S-1)+i)).ptr_b+j)).id_team ;j++) if(ID_T == (*((*(*(team_names+ID_S-1)+i)).ptr_b+j)).id_team ) return ((*((*(*(team_names+ID_S-1)+i)).ptr_b+j)).team_name+100*(ID_B-1));
				erl("\nEROR: !get_team_name()! not correct ID_team\n",true); /*exit(0);*/
			}
		}
	}
	erl("\nEROR: !get_team_name()! not correct ID_cham\n",true);/* exit(0);*/
}

//**************************************************************************
void bet::load_kc(char* file_name)
{
	col("Loading KC.b...		");
	ifstream in_file(file_name);
	if(!in_file){erl("EROR: FILE *");erl(file_name);erl("* NO FOUND\n\n",true); /*exit(0); */}
	kc_names=new p_kc_b*[n_bet];
	for(int i=0;i<n_bet;i++)
	{
		*(kc_names+i)=new p_kc_b[n_sport];
		for(int j=0;j<n_sport;j++) (*(kc_names+i)+j)->next=NULL;
	}
	p_kc_b* tm;
	const int N=5;
	char ID_B_name[N];
	char T_ID_B[]="ID_B";
	char ID_S_name[N];
	char T_ID_S[]="ID_S";
	int ID_B, ID_S, ID_KC;
	char* TP=new char[150];
	char* temp=TP; 
	int tn;
	in_file>>ID_B_name>>ID_B;
	for(int nb=0; !in_file.eof() && nb<n_bet; in_file>>ID_B_name>>ID_B, nb++)
	{
		 
		for(int i=0;i<(N-1);i++){ if(ID_B_name[i]!=T_ID_B[i])	{erl("EROR: FILE *");erl(file_name);erl("* no correct name ID_B => ");erl(ID_B_name);erl("\n",true);/*exit(0);*/} }
		char bb[32];
		if(ID_B<1 || ID_B>n_bet){erl("EROR: FILE *");erl(file_name);erl("* no correct ID_B: ");erl(itoa(ID_B,bb,10));erl("\n",true);/* exit(0);*/}
		
		for(int ns=0; !in_file.eof() && ns<n_sport;  ns++)
		{
			in_file>>ID_S_name;
			if(in_file.eof())break; 
			for(int i=0;i<(N-2);i++){ if(ID_S_name[i]!=T_ID_S[i])	{erl("EROR: FILE *");erl(file_name);erl("* no correct name ID_S => ");erl(ID_S_name);erl("\n",true);/* exit(0);*/} }
			if(ID_S_name[N-2]=='B'){in_file.seekg(-(N-1),ios::cur); break;}
			if(ID_S_name[N-2]!='S'){erl("eROR: FILE *");erl(file_name);erl("* no correct name ID_S => ");erl(ID_S_name);erl("\n",true);/* exit(0);*/}
			in_file>>ID_S;
			if(ID_S<1 || ID_S>n_sport){erl("EROR: FILE *");erl(file_name);erl("* no correct ID_S: ");erl(itoa(ID_S,bb,10));erl("\n",true);/*exit(0);*/}
			kc_base* t_end=NULL;//bloki verchi hamar

			for(int go=0, end=0;;)
			{
				//-------------------------------------------------------------------
				if(in_file.eof())break; 
				temp=TP;
				*temp='\0';
				for(int i=0;;)
				{
					for(;!in_file.eof() && !*temp;)in_file.getline(temp,150,'\n');
					if(in_file.eof())break;
					for(; ;i++)
					{
						if(*(temp+i)==' ')continue;
						else
						{
							temp+=i;
							break;
						}
					}
					if(*temp=='\0'){temp-=i;*temp='\0';i=0;continue;}
					break;
				}
				if(*temp!='I')
				{
					for(int i=0;;i++)
					{
						if(*(temp+i)=='\0')
						{
							for(;*(temp+i-1)==' ';){i--;continue;}
							*(temp+i)='\0';
							break;
						}
				
					}
				}
				//--------------------------------------------------------------------
				if(*temp>='1' && *temp<='9')
				{
					ID_KC=convert(temp,tn);
					if(ID_KC>ID_KC_MAX)ID_KC_MAX=ID_KC;
					if(!go)
					{
						tm=new p_kc_b;
						tm->next = (*(kc_names+ID_B-1)+ID_S-1)->next;
						(*(kc_names+ID_B-1)+ID_S-1)->next=tm;
						tm->p_base=new kc_base;
						tm->p_base->ptr_kc=NULL;
						tm->p_base->id_kc=ID_KC;
						tm->p_base->end=false;
						tm->p_base->BEND=t_end;
						for(int i=0; i<100 ;i++)
						{ 
							*(tm->p_base->kc_name+i)=*(temp+tn+i);
							if(*(temp+tn+i)=='\0')break;
						}
					}
					else
					{
						kc_base* T=(*(kc_names+ID_B-1)+ID_S-1)->next->p_base;
						for(; T->ptr_kc; T=T->ptr_kc);
						T->ptr_kc=new kc_base;
						T->ptr_kc->ptr_kc=NULL;
						T->ptr_kc->id_kc=ID_KC;
						T->ptr_kc->end=false;
						T->ptr_kc->BEND=t_end;
						for(int i=0; i<100 ;i++)
						{ 
							*(T->ptr_kc->kc_name+i)=*(temp+tn+i);
							if(*(temp+tn+i)=='\0')break;
						}
					}
					
					continue;
				}

				if(*temp=='<')
				{
					temp++;
					if(*(temp)=='/')
					{
						if(!go){erl("EROR: FILE *");erl(file_name);erl("* no correct end: ");erl(temp);erl("\n");continue;}
						go--;
						//////////////////////////////////////////////////////
						kc_base* T=(*(kc_names+ID_B-1)+ID_S-1)->next->p_base;
						for(; T->ptr_kc; T=T->ptr_kc);
						if(go)T->end=true;
						kc_base* t_end2=t_end->BEND;
						t_end->BEND=T;
						t_end=t_end2;
						//////////////////////////////////////////////////////
						continue;
					}
					if(!go)
					{
						tm=new p_kc_b;
						tm->next = (*(kc_names+ID_B-1)+ID_S-1)->next;
						(*(kc_names+ID_B-1)+ID_S-1)->next = tm;
						tm->p_base=new kc_base;
						tm->p_base->id_kc=0;
						tm->p_base->ptr_kc=NULL;
						tm->p_base->end=false;
						tm->p_base->BEND=NULL;
						t_end=tm->p_base;
						for(int i=0;i<100;i++)
						{
							*(tm->p_base->kc_name+i) = *(temp+i);
							if(*(temp+i)=='>')
							{
								*(tm->p_base->kc_name+i)='\0';
								break;
							}
						}
						go++;
						continue;
					}
					
					kc_base* T=(*(kc_names+ID_B-1)+ID_S-1)->next->p_base;
					for(; T->ptr_kc; T=T->ptr_kc);
					T->ptr_kc=new kc_base;
					T->ptr_kc->id_kc=0;
					T->ptr_kc->ptr_kc=NULL;
					T->ptr_kc->end=false;
					T->ptr_kc->BEND=t_end;
					t_end=T->ptr_kc;
					for(int i=0;i<100;i++)
					{
						*(T->ptr_kc->kc_name+i)=*(temp+i);
						if(*(temp+i)=='>')
						{
							*(T->ptr_kc->kc_name+i)='\0';
							break;
						}
					}
					go++;
					continue;
				}
				
				if(*temp=='I')
				{
					int siz=2;
					for(int i=0;*(temp+i)!='\0';i++)siz+=sizeof(*(temp+i));
					in_file.seekg(-siz,ios::cur);
					break;
				}
				
			}
		}
		


	}
	col("OK\n");
	load_total("BASE/KC/TOTAL.b");
}

int bet::convert(char* ID_int,int& n)
{
	int t=0;
	int i=0;
	for(;*(ID_int+i)!=' ';i++)
	{
		t=t*10+int(*(ID_int+i)-48);
	}
	for(;*(ID_int+i+1)==' ';)i++;
	n=++i;
	return t;
}

int bet::get_kc_id(char* KC_n,char End, bool P)
{
	static kc_base* temp;
	static kc_base* temp2;
	int ID_TOTAL=0;
	bool two=false;
	bool Kc_Element=false;
	char* KC_n_t=KC_n;
	//----------------------------------------------//
	if(temp && !temp2 && !P){temp2=temp=NULL;}
	if(temp2 && P)temp2=temp=NULL;
	for(;;)
	{
		if(!temp)
		{
			if( (*(kc_names+id_bet-1)+id_s_onl-1)->next==NULL ) {nf=false; return 0;}
			for(p_kc_b* i=(*(kc_names+id_bet-1)+id_s_onl-1)->next; ;i=i->next)
			{

				for(int j=0,jn=0;;j++,jn++)
				{
					/////////////////////////////////////////////////////////////////////////
					if(*(i->p_base->kc_name+jn)=='*')
					{
						char* DKC_T=get_DKC( (i->p_base->kc_name+jn), jn );
						if(DKC_T)
						{
							bool E=false;
							for(int k=0; ;k++,j++)
							{
								if(*(DKC_T+k+1)=='\0' || *(DKC_T+k+1)=='|'){j++; break;}
								if(*(DKC_T+k)!=*(KC_n_t+j))
								{
									bool two_name=false;
									for(int Z=k;*(DKC_T+Z)!='\0';Z++)
									{
										if(*(DKC_T+Z)=='|')
										{j=j-(k+1); k=Z;two_name=true; break;}
									}
									if(two_name)continue;
									E=true;
									break;
								}
							}
							if(E)break;
						}
					}
					/////////////////////////////////////////////////////////////////////////
					if(*(i->p_base->kc_name+jn)=='(' && *(i->p_base->kc_name+jn+1)=='#')
					{
						ID_TOTAL=get_total_id(KC_n_t+j,i->p_base->kc_name+jn,i->p_base->id_kc, j, jn, two, Kc_Element);
						if(!ID_TOTAL && !two && !Kc_Element)break;
						
					}
					/////////////////////////////////////////////////////////////////////////
					if(*(i->p_base->kc_name+jn)=='\0' && *(KC_n_t+j)==End && j>0)
					{
						if(!i->p_base->id_kc)
						{
							if(!P)temp2=i->p_base;
							temp=i->p_base;
							return 0;
						}
						if(!P)temp2=NULL;
						if(!ID_TOTAL)return i->p_base->id_kc;
						return ID_TOTAL;
					}
					if( *(i->p_base->kc_name+jn) != *(KC_n_t+j) ) break;
				}
				if( i->next==NULL ){nf=false; return 0;}
			}
		
		}
		else
		{
			if(!P)
			{
				if(!temp2->ptr_kc){temp2=temp=NULL;return 0;}
			}
			for(kc_base* i=temp->ptr_kc; ;i=i->ptr_kc)
			{
				if(i==temp){temp=NULL;break;}
				for(int j=0,jn=0; ;jn++,j++)
				{
					/////////////////////////////////////////////////////////////////////////
					if(*(i->kc_name+jn)=='*')
					{
						char* DKC_T=get_DKC( (i->kc_name+jn), jn );
						if(DKC_T)
						{
							bool E=false;
							for(int k=0; ;k++,j++)
							{
								if(*(DKC_T+k+1)=='\0' || *(DKC_T+k+1)=='|'){j++; break;}
								if(*(DKC_T+k)!=*(KC_n_t+j))
								{
									bool two_name=false;
									for(int Z=k;*(DKC_T+Z)!='\0';Z++)
									{
										if(*(DKC_T+Z)=='|')
										{j=j-(k+1);k=Z;two_name=true; break;}
									}
									if(two_name)continue;
									E=true;
									break;
								}
							}
							if(E)break;
						}
					}
					/////////////////////////////////////////////////////////////////////////
					if(*(i->kc_name+jn)=='(' && *(i->kc_name+jn+1)=='#')
					{
						ID_TOTAL=get_total_id(KC_n_t+j, i->kc_name+jn, i->id_kc, j, jn, two, Kc_Element);
						if(!ID_TOTAL && !two && !Kc_Element)
						{
							if(i==i->BEND->BEND){nf=false;	/*out_f_kc_t(KC_n_t,End);*/ temp=NULL; return 0;}
							break;
						}
					}
					/////////////////////////////////////////////////////////////////////////
					if( *(i->kc_name+jn)=='\0' && *(KC_n_t+j)==End )
					{ 
						if(!i->id_kc)
						{
							temp=i;
							return 0;
						}
						//if(P)temp=NULL;cout<<" R2 ";
						temp=NULL;
						if(!ID_TOTAL)return i->id_kc;
						return ID_TOTAL;
					}
					if( *(i->kc_name+jn)!=*(KC_n_t+j) )
					{
						if(!i->id_kc)i=i->BEND;
						if(!i->ptr_kc)
						{
							//out_f_kc_t(KC_n_t,End);
							nf=false;
							temp=NULL;
							return 0;
						}
						break;
					}
				}
				if(!i->ptr_kc)
				{
					if(P)
					{
						nf=false;
						temp2=temp=NULL;
						return 0;
					}
					else
					{
						if(temp!=temp2)i=temp2;
						else temp=NULL;
					}
				}
			}
		}
	}
}

void bet::out_f_kc_t(char* KC_n,char End)
{
	if( (IGA->Bets+id_bet_T-1)->add_kc)
	{
	ofstream out_file("TEMP/TEMP_KC.t",ios::app);
	if(nf)
	{
		out_file<<"\n"<<setw(7)<<setiosflags(ios::left)<<id_bet_T<<"| ["<<id_ch_onl<<"]	| "<<setw(9)<<id_s_onl<<"| ";
		for(int i=0;*(KC_n+i)!=End;i++){out_file.put(*(KC_n+i));}
		//nf=false;
	}
	else
	{
		out_file<<"|><|";
		for(int i=0;*(KC_n+i)!=End;i++)out_file.put(*(KC_n+i));
	}
	}
}

char* bet::get_DKC(char* DKC,int& Pn)
{
	if(*DKC=='*')
	{
		int i;
		for(i=0; *(DKC+1+i)==' ' ;i++);
		i++;
		if(*(DKC+i)>'0' && *(DKC+i)<'3')
		{
			int j=0;
			for(j=i+1;*(DKC+j)==' ';j++)
			{
				if(*(DKC+j+1)=='*'){Pn=++j;break;}
				if(*(DKC+j+1)!=' ')return NULL;
			}
			if((j-1)==i && *(DKC+j)!='*')return NULL;
			j++;
			if(*(DKC+i)=='1'){Pn+=j;return get_team_name(id_t1_onl, id_ch_onl, id_s_onl, id_bet);}
			if(*(DKC+i)=='2'){Pn+=j;return get_team_name(id_t2_onl, id_ch_onl, id_s_onl, id_bet);}
		}
		
	}
	return NULL;
}

void bet::load_total(char* file_name)
{
	col("Loading TOTAL.b...			");
	ifstream in_file(file_name);
	if(!in_file){erl("EROR: FILE *");erl(file_name);erl("* NO FOUND\n\n",true);/* exit(0);*/ }
	ID_KC_MAX=0;
	total_names=new p_total*[n_sport];
	for(int i=0;i<n_sport;i++) *(total_names+i)=NULL;
	int ID_S, N_T;
	int ID_TT, N_TT;
	int ID_KC;
	char* temp;
	for(int is=0;is<n_sport || !in_file.eof();is++)
	{
		in_file>>ID_S>>N_T;
		if(ID_S<1 || ID_S>n_sport){erl("\nEROR: ID SPORT file ! ");erl(file_name);erl(" !\n",true);/*exit(0);*/}
		if(!N_T)continue;
		if(N_T<0){erl("\nEROR: N TOTAL TYPE file ! ");erl(file_name);erl(" !\n",true);/*exit(0);*/}
		*(total_names+ID_S-1)=new p_total[N_T+1];
		(*(total_names+ID_S-1)+N_T)->id_tt=0;
		(*(total_names+ID_S-1)+N_T)->id_end=0;
		(*(total_names+ID_S-1)+N_T)->ptr_t=NULL;
		for(int it=0;it<N_T;it++)
		{
			in_file>>ID_TT>>N_TT;
			if(ID_TT<1){erl("\nEROR: ID TOTAL TYPE file ! ");erl(file_name);erl(" !\n",true);/*exit(0);*/}
			if(N_TT<0){erl("\nEROR: N TOTAL file ! ");erl(file_name);erl(" !\n",true);/*exit(0);*/}
			(*(total_names+ID_S-1)+it)->id_tt=ID_TT;
			(*(total_names+ID_S-1)+it)->ptr_t=new total[N_TT+1];
			((*(total_names+ID_S-1)+it)->ptr_t+N_TT)->id_total=0;
			((*(total_names+ID_S-1)+it)->ptr_t+N_TT)->name=NULL;
			int Q=0;
			for(int itt=0;itt<N_TT;itt++)
			{
				in_file>>ID_KC;
				if(ID_KC<1){erl("\nEROR: ID TOTAL TYPE file ! ");erl(file_name);erl(" !\n",true);/*exit(0);*/}
				if(ID_KC>Q)Q=ID_KC;
				if(ID_KC>ID_KC_MAX)ID_KC_MAX=ID_KC;
				temp=new char[50];
				in_file.getline(temp,50,'\n');
				for(int i=0;*(temp+i)==' ';i++)temp++;
				((*(total_names+ID_S-1)+it)->ptr_t+itt)->id_total=ID_KC;
				((*(total_names+ID_S-1)+it)->ptr_t+itt)->name=temp;
				//if((itt+1)==N_TT) (*(total_names+ID_S-1)+it)->id_end=ID_KC;
			}
			(*(total_names+ID_S-1)+it)->id_end=Q;
		}

	}
	col("OK\n");

}

int bet::get_total_id(char* KC_name, char* KC_base, int ID_kc, int &In, int &Ib,bool &w,bool &Kc_Element)
{
	char* RTG=KC_name;
	if( !*(total_names+id_s_onl-1) )return 0;
	
	if(*KC_base=='(' && *(KC_base+1)=='#' && *(KC_base+2)=='*' )
	{
		nf_BT=new char[10];
		*nf_BT='\0';
		Ib+=4;
		for(int i=0;;i++)
		{
			if( (*(KC_name+i)>='0' &&  *(KC_name+i)<='9') || *(KC_name+i)=='.' || *(KC_name+i)==',' || *(KC_name+i)=='-' || *(KC_name+i)=='+' ){In++; *(nf_BT+i)=*(KC_name+i);}
			else {Kc_Element=true; *(nf_BT+i)='\0';return 0;}
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////two total or one
	bool two=false;
	bool one=false;
	static int I=0;
	int one_az=0;
	if(!w)
	{
		for(; ;I++)
		{
			if(!(*(total_names+id_s_onl-1)+I)->id_tt){I=0; return 0;}/////%
			if((*(total_names+id_s_onl-1)+I)->id_tt==ID_kc)
			{
				if( !(*(total_names+id_s_onl-1)+I)->ptr_t ){I=0; return 0;}////////%
				for(int j=0;*((*(total_names+id_s_onl-1)+I)->ptr_t->name+j)!='\0';j++)
				{ if(*((*(total_names+id_s_onl-1)+I)->ptr_t->name+j)=='&'){two=true; break;} }
				break;
			}
		}
		int j=0;
		for(int i=0;two && *(KC_base+i)!='\0';i++)
		{
			if(*(KC_base+i)=='(') if(*(KC_base+i+1)=='#')j++;
		}
		if(two && j<2){one=true; two=false;}
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////(#1.2)-> m=1, p=2
	if(*KC_base!='(' && *(KC_base+1)!='#'){I=0; return 0;}///////%
	static int m=0, p=0;
	if(!w)
	{
		for(int i=2, t=0; ;i++)
		{
			if(*(KC_base+i)>='1' && *(KC_base+i)<='9'){ t=t*10+int(*(KC_base+i)-48); continue;}
			if(*(KC_base+i)=='.' || *(KC_base+i)==','){if(m){m=0; p=0; return 0;} m=t; t=0; continue;}
			if(*(KC_base+i)==')' && t && m){p=t;Ib+=++i;break;}
			m=0; p=0;
			I=0;/////%
			return 0;
		}
		m--;
	}
	else{ if(*(KC_base+2)!=')')return 0; Ib+=3;	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////KC_name-> temp
	char temp[10];
	if(!nf_BT){
	for(int i=0, t=0; ;)
	{
		if(*KC_name=='+')i++;
		if(*KC_name=='-' && *(KC_name+1)=='0')	
		{	
			if((*(KC_name+2)=='.' || *(KC_name+2)==',') && *(KC_name+3)=='0'){In+=4; *temp='0'; *(temp+1)='\0'; for(int JI=4;*(KC_name+JI)=='0';JI++)In++; break;}
			if((*(KC_name+2)!='.' || *(KC_name+2)==',') && (*(KC_name+2)!=',' || *(KC_name+2)=='.') && (*(KC_name+2)<'1' || *(KC_name+2)>'9')){	In+=3; *temp='0'; *(temp+1)='\0'; break;}
		}
		if(*(KC_name+i)=='0' && (*(KC_name+i+1)=='.' || *(KC_name+i+1)==',') && *(KC_name+i+2)=='0'){In+=i+3; *temp='0'; *(temp+1)='\0'; for(int JI=3;*(KC_name+JI)=='0';JI++)In++; break;}
		if( ((*(KC_name+i)<'0') || (*(KC_name+i)>'9')) && (*(KC_name+i)!='-') ){I=0;m=0;p=0; return 0;}
		for(bool k=true, mi=true, ti=true/*,NO=true*/; ; i++, t++)
		{   
			*(temp+t)=*(KC_name+i);
			if(*(KC_name+i)=='-' && mi && ti && k){mi=false; continue;}
			if(*(KC_name+i)>='0' && *(KC_name+i)<='9'){ti=false; /*if(*(KC_name+i)=='0' && !NO && !k)t--; if(*(KC_name+i)=='0' && !k)NO=false;*/ continue;}
			if( (*(KC_name+i)=='.' || *(KC_name+i)==',') && k && !ti){ *(temp+t)='.'; k=false; continue;}
			if(k && *KC_name!='0'){*(temp+t)='.'; *(temp+t+1)='0'; *(temp+t+2)='\0'; In+=i; t+=2; break;}
			In+=i;
			*(temp+t)='\0';break;
		}
		for(;*(temp+t-1)=='0' && *(temp+t-2)!='.' && t>2;t--)*(temp+t-1)='\0';
		break;
	}
	}
	else
	{
		int i=0;
		for(;*(nf_BT+i)!='\0';i++) temp[i]=*(nf_BT+i);
		temp[i]='\0';
	}

	static char* TEMP;
	if(two)
	{
		TEMP=new char[11];
		for(int i=0;i<11;i++)
		{
			*(TEMP+i)=*(temp+i);
			if(*(temp+i)=='\0')break;
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	for(;(*(total_names+id_s_onl-1)+I)->ptr_t;I++)
	{
		if((*(total_names+id_s_onl-1)+I)->id_tt==ID_kc)
		{
			for(static int i=0; ;i+=p)
			{
				static int jj=0;
				if(one)	{ for(; *(((*(total_names+id_s_onl-1)+I)->ptr_t+i+m)->name+jj)!='|' ;jj++); jj++;	}
				static int j=0;
				for(; ;j++, jj++)
				{
					if( (*(temp+j)=='\0' && j) )
					{
						if(two && !w && *(((*(total_names+id_s_onl-1)+I)->ptr_t+i+m)->name+jj)!='&'){j=0; jj=0; break;}
						if(two && !w){jj++; j=0; w=true; return 0;}
						if(!two && w && *(((*(total_names+id_s_onl-1)+I)->ptr_t+i+m)->name+jj)!='|'){jj-=j; j=0; break;}
						if(!two && !w && *(((*(total_names+id_s_onl-1)+I)->ptr_t+i+m)->name+jj)!='\0'){j=0; jj=0; break;}
						int ID_TOT=((*(total_names+id_s_onl-1)+I)->ptr_t+i+m)->id_total;
						I=0; i=0; j=0; jj=0; m=0; p=0;
						if(!two && w){ w=false; return ID_TOT;}
						if(!two && !w){return ID_TOT;}
					}
					if( *(((*(total_names+id_s_onl-1)+I)->ptr_t+i+m)->name+jj) != *(temp+j) )
					{
						
						if(w)
						{
							for(;;i+=p)
							{
								for(int q=0;;q++)
								{
									if(*(TEMP+q)=='\0' && *(((*(total_names+id_s_onl-1)+I)->ptr_t+i+m)->name+q)=='&')
									{
										for(int k=0;; k++)
										{
											q++;
											if( *(temp+k)=='\0' && *(((*(total_names+id_s_onl-1)+I)->ptr_t+i+m)->name+q)=='|' )
											{
												int ID_TOT=((*(total_names+id_s_onl-1)+I)->ptr_t+i+m)->id_total;
												I=0; i=0; j=0; jj=0; m=0; p=0;
												return ID_TOT;
											}
											if( *(temp+k) != *(((*(total_names+id_s_onl-1)+I)->ptr_t+i+m)->name+q) )break;
										}
										break;
									}
									if( *(TEMP+q) != *(((*(total_names+id_s_onl-1)+I)->ptr_t+i+m)->name+q) )break;
								}
								if(!((*(total_names+id_s_onl-1)+I)->ptr_t+i+p)->id_total ){I=0; i=0; j=0; jj=0; m=0; p=0; w=false; return 0;}
							}
						}
						j=0;
						jj=0;
						break;
					}
				}
				if( !((*(total_names+id_s_onl-1)+I)->ptr_t+i+p)->id_total ){I=0; i=0; j=0; jj=0; m=0; p=0; w=false; return 0;}
			}
		}
	}
	I=0;	
	return 0;
}

char* bet::get_kc_name(int ID_KC,int ID_S, int ID_B, int ID_CH, int ID_T1, int ID_T2)
{
	char* T_name=NULL;//TOTAL NAME
	int T_id=ID_KC;
	char bb[32];
	if(!*(kc_names+ID_B-1)){erl("EROR: !get_kc_name()! not correct ID_B: ");erl(itoa(ID_B,bb,10));erl("\n"); return NULL;}
	if(!(*(kc_names+ID_B-1)+ID_S-1)->next){erl("EROR: !get_kc_name()! not correct ID_S: ");erl(itoa(ID_S,bb,10));erl("\n"); return NULL;}
	if(*(total_names+ID_S-1))
	{
		for(int i=0; (*(total_names+ID_S-1)+i)->id_tt;i++)
		{
			if( (ID_KC >= (*(total_names+ID_S-1)+i)->id_tt) && (ID_KC <= (*(total_names+ID_S-1)+i)->id_end) )
			{
				bool p=true;
				if(ID_KC==((*(total_names+ID_S-1)+i)->ptr_t+(ID_KC-(*(total_names+ID_S-1)+i)->id_tt))->id_total)
				{
					T_name=((*(total_names+ID_S-1)+i)->ptr_t+(ID_KC-(*(total_names+ID_S-1)+i)->id_tt))->name;
					T_id=(*(total_names+ID_S-1)+i)->id_tt;
					p=false;
				}
				for(int n=0;p;n++)
				{
					if(n>(*(total_names+ID_S-1)+i)->id_end)break;
					if(ID_KC==((*(total_names+ID_S-1)+i)->ptr_t+n)->id_total)
					{
						T_name=((*(total_names+ID_S-1)+i)->ptr_t+n)->name;
						T_id=(*(total_names+ID_S-1)+i)->id_tt;
						//cout<<"#"<<((*(total_names+ID_S-1)+i)->ptr_t+n)->id_total<<"#";
						break;
					}
				}
			}
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	char* T_n1;//KC TYPE NAME
	char* T_n2;//KC TYPE NAME
	char* KC_B_N=NULL;//KC BASE NAME
	for(p_kc_b* i=(*(kc_names+ID_B-1)+ID_S-1)->next; ;i=i->next)
	{
		if(!i){erl("EROR: !get_kc_name()! not correct ID_KC: ");erl(itoa(T_id,bb,10));erl("\n"); return NULL;}
		T_n1=T_n2=NULL;
		if(i->p_base->id_kc)//ID>0
		{
			if(i->p_base->id_kc==T_id)
			{
				if(T_name)
				{
					///////////////////////////////////////////////////////////////////////////////////////////////////////(#1.2)-> m=1, p=2
					int m=0, p=0;
					char* KC_base;
					for(int j=0;*(i->p_base->kc_name+j)!='\0';j++){ if(*(i->p_base->kc_name+j)=='(' && *(i->p_base->kc_name+j+1)=='#'){ KC_base=i->p_base->kc_name+j; break;}}
					for(int ii=2, t=0; ;ii++)
					{
						if(*(KC_base+ii)>='1' && *(KC_base+ii)<='9'){ t=t*10+int(*(KC_base+ii)-48); continue;}
						if(*(KC_base+ii)=='.' || *(KC_base+ii)==','){if(m)return 0; m=t; t=0; continue;}
						if(*(KC_base+ii)==')' && t && m){p=t; break;}
						m=0; p=0;
						return 0;
					}
					///////////////////////////////////////////////////////////////////////////////////////////////////////
					if( ((ID_KC-T_id)%p) == (--m))
					{
						KC_B_N=i->p_base->kc_name;
						
						break;
					}
					continue;

	
					///////////////////////////////////////////////////////////////////////////////////////////////////////
				}
				KC_B_N=i->p_base->kc_name;
				break;
			}
			continue;
		}
		else//ID=0
		{
			T_n1=i->p_base->kc_name;
			if(T_name)
			{
				bool br=false;
				for(kc_base* j=i->p_base->ptr_kc; ;j=j->ptr_kc)
				{
					if(j->id_kc==T_id)
					{
						///////////////////////////////////////////////////////////////////////////////////////////////////////(#1.2)-> m=1, p=2
						int m=0, p=0;
						char* KC_base=NULL;
						for(int jj=0;*(j->kc_name+jj)!='\0';jj++){ if(*(j->kc_name+jj)=='(' && *(j->kc_name+jj+1)=='#'){ KC_base=j->kc_name+jj; break;}}
						for(int ii=2, t=0; ;ii++)
						{
							if(*(KC_base+ii)>='1' && *(KC_base+ii)<='9'){ t=t*10+int(*(KC_base+ii)-48); continue;}
							if(*(KC_base+ii)=='.' || *(KC_base+ii)==','){if(m)return 0; m=t; t=0; continue;}
							if(*(KC_base+ii)==')' && t && m){p=t; break;}
							m=0; p=0;
							return 0;
						}
						///////////////////////////////////////////////////////////////////////////////////////////////////////
						bool e=false;
						if(T_n2 && j->end) e=true;
						if( ((ID_KC-T_id)%p) == (--m))
						{
							KC_B_N=j->kc_name;
							//cout<<"$ "<<KC_B_N<<" $";
							break;
						}
						if(e)T_n2=NULL;
					}
					if(!j->ptr_kc){br=true; break;}
					if(!j->id_kc){T_n2=j->kc_name;continue;}
				}
			if(br)continue;
			break;
			}
			
			bool br=false;
			for(kc_base* j=i->p_base->ptr_kc; ;j=j->ptr_kc)
			{
				bool e=false;
				if(T_n2 && j->end) e=true;
				if(j->id_kc==T_id){KC_B_N=j->kc_name; break;}
				if(e)T_n2=NULL;
				if(!j->ptr_kc){br=true; break;}
				if(!j->id_kc){T_n2=j->kc_name;continue;}
			}
			if(br)continue;
			break;
			
		}
		
	}
	
	char* TEMP=new char[250];
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int T=0;
	if(T_n1)
	{
		for(int i=0;*(T_n1+i)!='\0'; i++, T++)
		{
			if(*(T_n1+i)=='*')if(v_DKC(T_n1, i, TEMP, T, ID_S, ID_B, ID_CH, ID_T1, ID_T2))continue;
			*(TEMP+T)=*(T_n1+i);
		}
		*(TEMP+T)='|';
	}
	if(T_n2)
	{
		T++;
		for(int i=0;*(T_n2+i)!='\0'; i++, T++)
		{
			if(*(T_n2+i)=='*')if(v_DKC(T_n2, i, TEMP, T, ID_S, ID_B, ID_CH, ID_T1, ID_T2))continue;
			*(TEMP+T)=*(T_n2+i);
		}
		*(TEMP+T)='|';
	}
	bool two=false;
	if(T_name)for(int i=0;*(T_name+i)!='\0';i++)if(*(T_name+i)=='&')two=true;
	bool one=false;
	if(two)
	{
		int j=0;
		for(int i=0;*(KC_B_N+i)!='\0';i++)if(*(KC_B_N+i)=='(' && *(KC_B_N+i+1)=='#')j++;
		if(!j || j>2)return 0;
		if(j==1)one=true;

	}
	if(!*KC_B_N)return 0;
	bool n=false;
	if(T_n1)T++;
	for(int i=0; T<250 ; i++, T++)
	{
		if(*(KC_B_N+i)=='(' && *(KC_B_N+i+1)=='#')
		{
			*(TEMP+T)=' ';
			for(;*(KC_B_N+i)!=')';i++);
			if(two)
			{
				if(one)
				{
					int j=0;
					for(;*(T_name+j)!='|';j++); j++;cout<<(T_name+j);
					for(;*(T_name+j)!='\0';j++)
					{
						T++;
						*(TEMP+T)=*(T_name+j);
					}
					continue;
				}	
				if(!n)
				{
					for(int j=0;*(T_name+j)!='&'; j++)
					{
						T++;
						*(TEMP+T)=*(T_name+j);
					}
					n=true;
					continue;
				}
				T--;
				int j=0;
				for(;*(T_name+j)!='&';j++); j++;
				for(;*(T_name+j)!='|';j++)
				{
					T++;
					*(TEMP+T)=*(T_name+j);
				}	
				continue;
			}

			for(int j=0;*(T_name+j)!='\0';j++)
			{
				T++;
				*(TEMP+T)=*(T_name+j);
			}
			continue;
		}
		if(*(KC_B_N+i)=='*') if(v_DKC(KC_B_N, i, TEMP, T, ID_S, ID_B, ID_CH, ID_T1, ID_T2))continue;
		*(TEMP+T)=*(KC_B_N+i);
		if(*(KC_B_N+i)=='\0') return TEMP;
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	return 0;
}

char* bet::get_kc_NU(int ID_KC)//<<<<<<---------------------------------
{
	static char ptr[][20]=
	{
"P1",//1
"X2",//2
"P2",//3
"1X",//4
"X",//5
"12",//6
"1T P1",//7
"1T X2",//8
"1T P2",//9
"1T 1X",//10
"1T X",//11
"1T 12",//12
"2T P1",//13
"2T X2",//14
"2T P2",//15
"2T 1X",//16
"2T X",//17
"2T 12",//18
"M(0.5)",//19
"B(0.5)",//20
"M(1.5)",//21
"B(1.5)",//22
"M(2.5)",//23
"B(2.5)",//24
"M(3.5)",//25
"B(3.5)",//26
"M(4.5)",//27
"B(4.5)",//28
"M(5.5)",//29
"B(5.5)",//30
"M(6.5)",//31
"B(6.5)",//32
"M(7.5)",//33
"B(7.5)",//34
"M(8.5)",//35
"B(8.5)",//36
"M(9.5)",//37
"B(9.5)",//38
"M(10.5)",//39
"B(10.5)",//40
"M(11.5)",//41
"B(11.5)",//42
"M(12.5)",//43
"B(12.5)",//44
"M(13.5)",//45
"B(13.5)",//46
"M(1)",//47
"B(1)",//48
"M(2)",//49
"B(2)",//50
"M(3)",//51
"B(3)",//52
"M(4)",//53
"B(4)",//54
"M(5)",//55
"B(5)",//56
"M(6)",//57
"B(6)",//58
"M(7)",//59
"B(7)",//60
"M(8)",//61
"B(8)",//62
"M(9)",//63
"B(9)",//64
"M(10)",//65
"B(10)",//66
"M(11)",//67
"B(11)",//68
"M(12)",//69
"B(12)",//70
"M(13)",//71
"B(13)",//72
"1T M(0.5)",//73
"1T B(0.5)",//74
"1T M(1.5)",//75
"1T B(1.5)",//76
"1T M(2.5)",//77
"1T B(2.5)",//78
"1T M(3.5)",//79
"1T B(3.5)",//80
"1T M(4.5)",//81
"1T B(4.5)",//82
"1T M(5.5)",//83
"1T B(5.5)",//84
"1T M(6.5)",//85
"1T B(6.5)",//86
"1T M(1)",//87
"1T B(1)",//88
"1T M(2)",//89
"1T B(2)",//90
"1T M(3)",//91
"1T B(3)",//92
"1T M(4)",//93
"1T B(4)",//94
"1T M(5)",//95
"1T B(5)",//96
"1T M(6)",//97
"1T B(6)",//98
"2T M(0.5)",//99
"2T B(0.5)",//100
"2T M(1.5)",//101
"2T B(1.5)",//102
"2T M(2.5)",//103
"2T B(2.5)",//104
"2T M(3.5)",//105
"2T B(3.5)",//106
"2T M(4.5)",//107
"2T B(4.5)",//108
"2T M(5.5)",//109
"2T B(5.5)",//110
"2T M(6.5)",//111
"2T B(6.5)",//112
"2T M(1)",//113
"2T B(1)",//114
"2T M(2)",//115
"2T B(2)",//116
"2T M(3)",//117
"2T B(3)",//118
"2T M(4)",//119
"2T B(4)",//120
"2T M(5)",//121
"2T B(5)",//122
"2T M(6)",//123
"2T B(6)",//124
"F1(4.0)",//125
"F2(4.0)",//126
"F2(4.0)",//127
"F1(4.0)",//128
"F1(3.0)",//129
"F2(3.0)",//130
"F2(3.0)",//131
"F1(3.0)",//132
"F1(2.0)",//133
"F2(2.0)",//134
"F2(2.0)",//135
"F1(2.0)",//136
"F1(1.0)",//137
"F2(-1.0)",//138
"F2(1.0)",//139
"F1(-1.0)",//140
"F1(0)",//141
"F2(0)",//142
"F1(3.5)",//143
"F2(3.5)",//144
"F2(3.5)",//145
"F1(-3.5)",//146
"F1(2.5)",//147
"F2(-2.5)",//148
"F2(2.5)",//149
"F1(-2.5)",//150
"F1(1.5)",//151
"F2(-1.5)",//152
"F2(1.5)",//153
"F1(-1.5)",//154
"F1(0.5)",//155
"F2(-0.5)",//156
"F2(0.5)",//157
"F1(-0.5)",//158
/*"F1(3.5&4.0)",//159
"F2(-3.5&-4.0)",//160
"F2(3.5&4.0)",//161
"F1(-3.5&-4.0)",//162
"F1(3.0&3.5)",//163
"F2(-3.0&-3.5)",//164
"F2(3.0&3.5)",//165
"F1(-3.0&-3.5)",//166
"F1(2.5&3.0)",//167
"F2(-2.5&-3.0)",//168
"F2(2.5&3.0)",//169
"F1(-2.5&-3.0)",//170
"F1(2.0&2.5)",//171
"F2(-2.0&+2.5)",//172
"F2(2.0&2.5)",//173
"F1(-2.0&+2.5)",//174
"F1(1.5&2.0)",//175
"F2(-1.5&-2.0)",//176
"F2(1.5&2.0)",//177
"F1(-1.5&-2.0)",//178
"F1(1.0&1.5)",//179
"F2(-1.0&-1.5)",//180
"F2(1.0&1.5)",//181
"F1(-1.0&-1.5)",//182
"F1(0.5&1.0)",//183
"F2(-0.5&-1.0)",//184
"F2(0.5&1.0)",//185
"F1(-0.5&-1.0)",//186
"F1(0&0.5)",//187
"F2(0&0.5)",//188
"F2(0&0.5)",//189
"F1(0&-0.5)",//190*/
"F1(3.75)",//159
"F2(-3.75)",//160
"F2(3.75)",//161
"F1(-3.75)",//162
"F1(3.25)",//163
"F2(-3.25)",//164
"F2(3.25)",//165
"F1(-3.25)",//166
"F1(2.75)",//167
"F2(-2.75)",//168
"F2(2.75)",//169
"F1(-2.75)",//170
"F1(2.25)",//171
"F2(-2.25)",//172
"F2(2.25)",//173
"F1(-2.25)",//174
"F1(1.75)",//175
"F2(-1.75)",//176
"F2(1.75)",//177
"F1(-1.75)",//178
"F1(1.25)",//179
"F2(-1.25)",//180
"F2(1.25)",//181
"F1(-1.25)",//182
"F1(0.75)",//183
"F2(-0.75)",//184
"F2(0.75)",//185
"F1(-0.75)",//186
"F1(0.25)",//187
"F2(-0.25)",//188
"F2(0.25)",//189
"F1(-0.25)",//190
"1T F1(0)",//191
"1T F2(0)",//192
"1T F1(0.5)",//193
"1T F2(-0.5)",//194
"1T F2(0.5)",//195
"1T F1(-0.5)",//196
"1T F1(1)",//197
"1T F2(-1)",//198
"1T F2(1)",//199
"1T F1(-1)",//200
"1T F1(1.5)",//201
"1T F2(-1.5)",//202
"1T F2(1.5)",//203
"1T F1(-1.5)",//204
"1T F1(2)",//205
"1T F2(-2)",//206
"1T F2(2)",//207
"1T F1(-2)",//208
"1T F1(2.5)",//209
"1T F2(-2.5)",//210
"1T F2(2.5)",//211
"1T F1(-2.5)",//212
"2T F1(0)",//213
"2T F2(0)",//214
"2T F1(0.5)",//215
"2T F2(-0.5)",//216
"2T F2(0.5)",//217
"2T F1(-0.5)",//218
"2T F1(1)",//219
"2T F2(-1)",//220
"2T F2(1)",//221
"2T F1(-1)",//222
"2T F1(1.5)",//223
"2T F2(-1.5)",//224
"2T F2(1.5)",//225
"2T F1(-1.5)",//226
"2T F1(2)",//227
"2T F2(-2)",//228
"2T F2(2)",//229
"2T F1(-2)",//230
"2T F1(2.5)",//231
"2T F2(-2.5)",//232
"2T F2(2.5)",//233
"2T F1(-2.5)",//234
"1-0",//235
"2-0",//236
"2-1",//237
"3-0",//238
"3-1",//239
"3-2",//240
"0-1",//241
"0-2",//242
"1-2",//243
"0-3",//244
"1-3",//245
"2-3",//246
"0-0",//247
"1-1",//248
"2-2",//249
"3-3",//250
"L.D.SH.",//251
"P1-P1",//252
"P1-X",//253
"P1-P2",//254
"X-P1",//255
"P2-P2",//256
"P2-X",//257
"P2-P1",//258
"X-P2",//259
"X-X",//260
"1T 0-0",//261
"1T 1-1",//262
"1T 2-2",//263
"1T 1-0",//264
"1T 2-0",//265
"1T 2-1",//266
"1T 0-1",//267
"1T 0-2",//268
"1T 1-2",//269
"L.D.SH.",//270
"1T & 2T P1",//271
"1T & 2T !P1",//272
"1T & 2T P2",//273
"1T & 2T !P2",//274
"P1 zabyot",//275
"P1 ne zabyot",//276
"P2 zabyot",//277
"P2 ne zabyot",//278
"CHET(Even)",//279
"NE CHET(Odd)",//280
"0-10",//281
"11-20",//282
"21-30",//283
"31-40",//284
"41-50",//285
"51-60",//286
"61-70",//287
"71-80",//288
"81-END GAME",//289
"NO GOL",//290
"P1",//291
"P2",//292
"NO GOL",//293
"?",//294
"?",//295
"PENALTI",//296
"!PENALTI",//297
"UDALENIE",//298
"!UDALENIE",//299
"OBZ",//300
"!OBZ",//301
"OBZ 1T",//302
"!OBZ 1T",//303
"OBZ 2T",//304
"!OBZ 2T",//305
"P1(1)",//306
"P2(-1)",//307
"X(-1)",//308
"P2(1)",//309
"P1(-1)",//310
"X(1)",//311
"P1(2)",//312
"P2(-2)",//313
"X(-2)",//314
"P2(2)",//315
"P1(-2)",//316
"X(2)",//317
"P1(3)",//318
"P2(-3)",//319
"X(-3)",//320
"P2(3)",//321
"P1(-3)",//322
"X(3)",//323
"P1(4)",//324
"P2(-4)",//325
"X(-4)",//326
"P2(4)",//327
"P1(-4)",//328
"X(4)",//329
"P1(5)",//330
"P2(-5)",//331
"X(-5)",//332
"P2(5)",//333
"P1(-5)",//334
"X(5)",//335
"P1(6)",//336
"P2(-6)",//337
"X(-6)",//338
"P2(6)",//339
"P1(-6)",//340
"X(6)",//341
"P1(0)",//342
"P2(0)",//343
"X(0)",//344
"M(0.5&1.0)",//345
"B(0.5&1.0)",//346
"M(1&1.5)",//347
"B(1&1.5)",//348
"M(1.5&2.0)",//349
"B(1.5&2.0)",//350
"M(2.0&2.5)",//351
"B(2.0&2.5)",//352
"M(2.5&3.0)",//353
"B(2.5&3.0)",//354
"M(3.0&3.5)",//355
"B(3.0&3.5)",//356
"M(3.5&4.0)",//357
"B(3.5&4.0)",//358
"M(4.0&4.5)",//359
"B(4.0&4.5)",//360
"M(4.5&5.0)",//361
"B(4.5&5.0)",//362
"M(5.0&5.5)",//363
"B(5.0&5.5)",//364
"M(5.5&6.0)",//365
"B(5.5&6.0)",//366
/*"1T F1(2.5&3.0)",//367
"1T F2(-2.5&-3.0)",//368
"1T F2(2.5&3.0)",//369
"1T F1(-2.5&-3.0)",//370
"1T F1(2.0&2.5)",//371
"1T F2(-2.0&-2.5)",//372
"1T F2(2.0&2.5)",//373
"1T F1(-2.0&-2.5)",//374
"1T F1(1.5&2.0)",//375
"1T F2(-1.5&-2.0)",//376
"1T F2(1.5&2.0)",//377
"1T F1(-1.5&-2.0)",//378
"1T F1(1.0&1.5)",//379
"1T F2(-1.0&-1.5)",//380
"1T F2(1.0&1.5)",//381
"1T F1(-1.0&-1.5)",//382
"1T F1(0.5&1.0)",//383
"1T F2(-0.5&-1.0)",//384
"1T F2(0.5&1.0)",//385
"1T F1(-0.5&-1.0)",//386
"1T F1(0&0.5)",//387
"1T F2(0&-0.5)",//388
"1T F2(0&0.5)",//389
"1T F1(0&-0.5)",//390*/
"F1(2.75)",//367
"F2(-2.75)",//368
"F2(2.75)",//369
"F1(-2.75)",//370
"F1(2.25)",//371
"F2(-2.25)",//372
"F2(2.25)",//373
"F1(-2.25)",//374
"F1(1.75)",//375
"F2(-1.75)",//376
"F2(1.75)",//377
"F1(-1.75)",//378
"F1(1.25)",//379
"F2(-1.25)",//380
"F2(1.25)",//381
"F1(-1.25)",//382
"F1(0.75)",//383
"F2(-0.75)",//384
"F2(0.75)",//385
"F1(-0.75)",//386
"F1(0.25)",//387
"F2(-0.25)",//388
"F2(0.25)",//389
"F1(-0.25)",//390
"M(0.5&1.0)",//391
"B(0.5&1.0)",//392
"M(1&1.5)",//393
"B(1&1.5)",//394
"M(1.5&2.0)",//395
"B(1.5&2.0)",//396
"M(2.0&2.5)",//397
"B(2.0&2.5)",//398
"M(2.5&3.0)",//399
"B(2.5&3.0)",//400
"M(3.0&3.5)",//401
"B(3.0&3.5)",//402
"M(3.5&4.0)",//403
"B(3.5&4.0)",//404


	};
	if(!ID_KC)
	{
		//GX_KC_NAME.push_back
		return 0;
	}
	static char NA[50];
	int i=0;

	char* Temp=ptr[ID_KC-1];
	for(;*(Temp+i)!='\0' && i<50;i++) NA[i]=*(Temp+i);
	
	if( ((ID_KC>=125 && ID_KC<=234) || (ID_KC>=367 & ID_KC<=390)) & CForaC )
	{
		int *GoalT=GET_GOAL( id_s_onl, id_ch_onl, id_t1_onl, id_t2_onl);
		if(GoalT)
		{
			if(*GoalT != *(GoalT+1))
			{
				int conG[2];
				conG[1]=*GoalT;
				conG[0]=*(GoalT+1);
				GX_GOAL=(int*)conG;
				//GX_GOAL=GoalT;
				int OriginalIdKc=ConvertForaKcId(ID_KC);//het convertacia!!!
				Temp=ptr[OriginalIdKc-1];
				for(i=0;*(Temp+i)!='\0' && i<50;i++) NA[i]=*(Temp+i);
				char TotalS[30];
				sprintf(TotalS," (%i-%i)",*(GoalT), *(GoalT+1));
				for(int j=0;TotalS[j]!='\0' && i<50; j++, i++) NA[i]=TotalS[j];
				int ijkh=45646;
			}
		}
	}
	
	//char* Name=(char*)KcName.c_str();
	
	//for(;*(Name+i)!='\0' && i<50;i++) NA[i]=*(Name+i);
	NA[i]='\0';
	char* Allname=NA;
	return (char*)NA;
}

bool bet::v_DKC(char* BASE, int& B, char* TEMP, int& T, int ID_S, int ID_B, int ID_CH, int ID_T1, int ID_T2)
{
	if( *(BASE+B)=='*' && (*(BASE+B+1)=='1' || *(BASE+B+1)=='2') && *(BASE+B+2)=='*')
	{
		char* T_name=NULL;
		if(*(BASE+B+1)=='1') T_name=get_team_name(ID_T1, ID_CH, ID_S, ID_B);
		else T_name=get_team_name(ID_T2, ID_CH, ID_S, ID_B); 
		B+=2;
		T--;
		for(int i=0;*(T_name+i)!='\0';i++){ T++; *(TEMP+T)=*(T_name+i);}
		return true;
	}
	return false;
}

//*******************************************************************************************************************//

/*sport* bet::START()
{
	///////////////////////////////
	//const int N_BET=6;
	//int IDS_BET_OUT[N_BET]={1,2,3,4,5,6};
	//out_bet(IDS_BET_OUT);
	///////////////////////////////
	//int ID_B=0;
	char* s_name=NULL;
	sport* PTR_SPORT=NULL;
	char* ch_name=NULL;

	int* g_time; //game time 0-year, 1-month, 2-day, 3-hour, 4-minute, 
	int hour=24;//->>
	int* min_time=NULL; //@ntaciq jamanak
	int* max_time=NULL;
	int max_t_m=int(time(0))/60+hour*60;
	


	for(int i=1;;i++)
	{
		FIX_BET(ID_B);		
		for(;sport(s_name);)
		{
			int ID_S;
			ID_S=get_sport_id(s_name);
			if(!ID_S) break;
			//if()continue;
			sport* temp_s=new sport;
			temp_s->next=PTR_SPORT;
			PTR_SPORT=temp_s;
			PTR_SPORT->id_s=ID_S;
			PTR_SPORT->ptrch=NULL;

			for(;championship(ch_name);)
			{
				int ID_CH;
				ID_CH=get_cham_id(ch_name);
				if(!ID_CH) break;
				//if()continue;
				cham* temp_ch=new cham;
				temp_ch->next=PTR_SPORT->ptrch;
				PTR_SPORT->ptrch=temp_ch;
				temp_ch->id_ch=ID_CH;
				temp_ch->ptrm=NULL;
				
				for(;game_time(g_time);)
				{
					g_time=new int[4]; *g_time=2011; *(g_time+1)=10; *(g_time+2)=3; *(g_time+3)=18; *(g_time+4)=45;//porcnakan
					if(*(g_time+1)<1 || *(g_time+1)>12) {cout<<"/nERROR: MONTH/n"; continue;}
					if(*(g_time+2)<1 || *(g_time+2)>31) {cout<<"/nERROR: DAY/n"; continue;}
					if(*(g_time+3)<0 || *(g_time+3)>23) {cout<<"/nERROR: HOUR/n"; continue;}
					if(*(g_time+4)<0 || *(g_time+4)>59) {cout<<"/nERROR: MINUTE/n"; continue;}

					if( !TIME_M(g_time,max_t_m) )continue;
					
					//<<---------------------------------

					month* temp_m=new month;
					temp_m->next=temp_ch->ptrm;
					temp_ch->ptrm=temp_m;
					temp_m->m=*g_time;
					temp_m->day=*(g_time+1);

				}
			}
		}

	}


	return 0;
}*/


void bet::START()
{
	char file[40];
	char* temp_s;
	char* temp_x;
	if(G.id_s)
	{
		G.id_s=0;
		G.next=NULL;
		G.ptrch=NULL;
		V_ALL.GVALL=NULL;
		V_ALL.next=NULL;
	}
	
	for(int i=0;i<n_sport && *(f_sports+i)!='\0';i++)//sports
	{
		switch(*(f_sports+i))
		{//KCi voronman hamar 1.blok 2.gorcakic 3.lay(birjaneri hamar) 4.gocakci anvan hertakanutyun @st bazayi
		case 1: temp_s="soccer/odds_";temp_x="all s & t is= & e ht= at= time= g= & o v= lay= p= tv= bgtype= bv= type= total= odds= " ;break;//"championship","teams","odds" (' '-END)
		case 4: temp_s="basketball/odds_";break;
		}
		id_s_onl=*(f_sports+i);
		//////////////////////////////////////////////////////Build struct:sport
		sport* Temp;
		if(!G.id_s)	{Temp=&G;TEMP_S=Temp; G.id_s=id_s_onl;}
		else
		{
			Temp=&G;
			for(;Temp;)Temp=Temp->next;
			Temp->next=new sport;
			Temp=Temp->next;
			Temp->id_s=id_s_onl;
			Temp->next=NULL;
			Temp->ptrch=NULL;
			TEMP_S=Temp;
		}
		//////////////////////////////////////////////////////
		for(int j=0;j<n_bet && *(f_bets+j)!='\0';j++)//bets
		{
			Xml_Bass=temp_x;
			FIX_BET(*(f_bets+j));
			xml_io( add_char(add_char(temp_s, bet_name(id_bet),true),".xml") );
		}
	}
}

char* bet::add_char(char* a1, char* a2, bool B)
{
	int N=100;
	char* temp=new char[N];
	int n=0;
	for(;;)
	{
		for(int i=0;*(a1+i)!='\0' && n<N;i++,n++) *(temp+i)=*(a1+i);
		if(n>=N){delete []temp; temp=new char[N*=2];continue;}
		int i=0;
		if(*(a2+i)=='*' && B){i++;bet_type=true;}
		else bet_type=false;
		for(;(*(a2+i))!='\0' && n<N ;i++,n++) *(temp+n)=*(a2+i);
		if(n>N){delete []temp; temp=new char[N*=2];continue;}
		*(temp+n)='\0';
		return temp;
	}
	
}

void bet::xml_io(char* file_name)
{
	////////////////////////////////////////////////////////////////////////////////////////
	Xml_temp_file_name=file_name;
	ifstream in_file(file_name);
	if(!in_file){erl("EROR: FILE * ");erl(file_name);erl(" * NO FOUND\n\n"); return;}
	
	xml_buff xml;
	const int N=xml_buff_size=1048576;//1 MB
	xml.buffer=new char[N];
	xml.next=NULL;
	xml_buff* temp=&xml;
	for(;;)
	{
		in_file.get(temp->buffer,N);
		if(!in_file.eof())
		{	temp->next=new xml_buff;
			temp=temp->next;
			temp->buffer=new char[N];
			temp->next=NULL;
			continue;
		}
		break;
	}
	ptr_xml_buf = &xml;
	ptr_xml_buf_temp = NULL;
	Xml_N=0;
	/////////////////////////////////////////////////////////////////////////////////////
	for(int i=0,j=0;*(Xml_Bass+i)!='\0';i++)
	{
		if(*(Xml_Bass+i)=='&')
		{
			for(i++;*(Xml_Bass+i)==' ';i++);
			switch(j)
			{
			case 0: Xml_Bass_Ch=(Xml_Bass+i);j++;break;
			case 1: Xml_Bass_G=(Xml_Bass+i);j++;break;
			case 2:	Xml_Bass_O=(Xml_Bass+i);j++;break;
			}
		}
	}
	//////////////////////////////////////////////////Xml_Bass_O - i arandznacum
	Xml_B_ON=0;
	for(int i=0;*(Xml_Bass_O+i)!='\0';i++)	if(*(Xml_Bass_O+i)==' ' && *(Xml_Bass_O+i+1)!='\0')Xml_B_ON++;
	Xml_B_O=new char*[Xml_B_ON];
	Xml_B_OT=new char*[Xml_B_ON];
	int xi=0;
	for(int i=0;*(Xml_Bass_O+i)!='\0';i++)
	{
		if(*(Xml_Bass_O+i)==' ' && *(Xml_Bass_O+i+1)!='\0')
		{
			*(Xml_B_O+xi)=(Xml_Bass_O+i+1);
			xi++;
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////
	
	xml_ignor();
	for(bool b;b=xml_cham();)
	{
		for(;xml_game();)
		{
			for(;xml_odds(););
		}
	}
	
}

char* bet::ptr_xml(bool B)//dlya xml_iso()---->xml_(ignor,cham,game,odds)
{
	if(B)Xml_N++;
	else Xml_N--;
	if(Xml_N==xml_buff_size)
	{
		ptr_xml_buf_temp = ptr_xml_buf;
		ptr_xml_buf = ptr_xml_buf->next;
		Xml_N=0;
		return (ptr_xml_buf->buffer+Xml_N);
	}
	if(Xml_N<0)
	{
		if(!ptr_xml_buf_temp)
		{
			Xml_N=0;
			return (ptr_xml_buf->buffer+Xml_N);
		}
		ptr_xml_buf=ptr_xml_buf_temp;
		ptr_xml_buf_temp=0;
		Xml_N=xml_buff_size-1;
	}
	return (ptr_xml_buf->buffer+Xml_N);
}

void bet::xml_ignor()
{
	char* temp=Xml_Bass;
	for(;*ptr_xml()!='<';);
	*ptr_xml(false);
	if(*ptr_xml()=='<' && *ptr_xml()=='?')for(;*ptr_xml()!='>';);
	else{ ptr_xml(false); ptr_xml(false);}
	if(*ptr_xml()=='<' && *ptr_xml()=='!')for(;*ptr_xml()!='>';);
	else{ ptr_xml(false); ptr_xml(false);}
	/////////////////////////////////////////////////////////////
	
	for(int i=0;*(temp+i)!='&';i++)
	{
		for(;*ptr_xml()!='<';);
		if(name_serch(temp+i,' ')) 
		{
			for(;*ptr_xml()!='>';);
			for(;*(temp+i)!=' ';i++);
			continue;
		}
		for(;*(temp+i)!=' ';i++);

	}


}

bool bet::name_serch(char* name, char end)
{
	char s=*ptr_xml();
	for( int i=0; s!='>' || s!='"' || s!=' '; s=*ptr_xml(), i++)
	{
		if(*(name+i)==s)
		{
			if(*(name+i+1)==end){return true;}
			continue;
		}
		for(int j=0;j<=i;j++)ptr_xml(false);
		return false;
	}
	ptr_xml(false);
	return false;
}

char* bet::ptr_xml_g_name(char E)
{
	char* Temp_X=NULL;
	if(Xml_N+200>xml_buff_size && ptr_xml_buf->next)
	{
		Temp_X=new char[200];
		for(int i=0;(*(Temp_X+i)=*ptr_xml())!='"' && i<200;i++);
	}
	else Temp_X=ptr_xml();
	return Temp_X;
}

bool bet::xml_cham()//////////////////////////////////////////////////////////////////////////////#1
{
	for(;;)
	{
	for(;*ptr_xml()!='<';);
	if(*ptr_xml()=='/')
	{
		return false;
	}
	ptr_xml(false);
	
	if(name_serch(Xml_Bass_Ch,' '))
	{
		int i=0;
		for(;*(Xml_Bass_Ch+i)!=' ';i++);
		ptr_xml();
		if(name_serch(Xml_Bass_Ch+i+1,' '))
		{
			ptr_xml();
			int IDCH = get_cham_id(ptr_xml_g_name('"'),'"');
			if(IDCH)
			{
				id_ch_onl=IDCH;//@ntacik id_cham
				if(TEMP_S->ptrch)
				{
					cham* Te=TEMP_S->ptrch;
					for(;Te;Te=Te->next)
					{
						if(IDCH==Te->id_ch)break;
						if(!Te->next)
						{
							Te->next=new cham;
							Te=Te->next;
							Te->id_ch=IDCH;
							Te->back_sport=TEMP_S;
							Te->next=NULL;
							Te->ptrm=NULL;
							break;
						}
					}
					TEMP_CH=Te;//@ntacik chami hasce
				}
				else
				{
					TEMP_S->ptrch=new cham;
					TEMP_S->ptrch->id_ch=IDCH;
					TEMP_S->ptrch->back_sport=TEMP_S;
					TEMP_S->ptrch->next=NULL;
					TEMP_S->ptrch->ptrm=NULL;
					TEMP_CH=TEMP_S->ptrch;//@ntacik chami hasce
				}
				for(;*ptr_xml()!='>';);
				return true;
			}
			xml_t_end();//gtnume yev kangnume chempuonati verchi vra
			
			continue;

		}
	}
	xml_eror(1);
	return false;
	}
}

void bet::xml_t_end()
{
	for(;*ptr_xml()!='>';);
	bool ooc=false;//open=true or close=false
	for(;*ptr_xml()!='<';);
	for(char* p=ptr_xml();;p=ptr_xml())
	{
		if(*p=='>')
		{
			for(p=ptr_xml();;p=ptr_xml())
			{
				if(*p=='<')
				{
					if(*(p=ptr_xml())!='/')continue;
					for(;*ptr_xml()!='>';);
					for(;*ptr_xml()!='<';);
					if(*ptr_xml()!='/'){for(;*ptr_xml()!='>';);continue;}
					for(;*ptr_xml()!='>';);
					return;
				}
			}
		}
		if(*p=='/')
		{
			if(*(p=ptr_xml())!='>'){ptr_xml(false);continue;}
			for(p=ptr_xml();;p=ptr_xml())
			{
				if(*p=='<')
				{
					if(*(p=ptr_xml())=='/'){for(;*ptr_xml()!='>';);return;}
					for(;;)
					{
						if(*ptr_xml()=='/')
						{
							if(*ptr_xml()!='>')continue;
							break;
						}
					}
				}
			}

		}
		
	}
}

void bet::xml_eror(int n)
{
	char bb[32];
	erl("\nEROR #");erl(itoa(n,bb,10));erl(": xml file: ");erl(Xml_temp_file_name);erl("\n");
}

bool bet::xml_game()//////////////////////////////////////////////////////////////////#2
{
	for(;;)
	{
	for(;*ptr_xml()!='<';);
	if(*ptr_xml()=='/') return false;
	ptr_xml(false);
	if(name_serch(Xml_Bass_G,' '))//xaxe te voch
	{
		int i=0;
		for(;*(Xml_Bass_G+i)!=' ';i++);
		ptr_xml();
		if(name_serch(Xml_Bass_G+(++i),' '))//arachi timne te voch
		{
			ptr_xml();
			int IDT1=get_team_id(ptr_xml_g_name('"'),'"');
			if(!IDT1)
			{
				xml_t_end();//gtnume yev kangnume xaxi verchi vra
				continue;
			}
			for(;*ptr_xml()!='"';);
			for(;*(Xml_Bass_G+i)!=' ';i++);
			ptr_xml();
			if(name_serch(Xml_Bass_G+(++i),' '))//erkrort timne te voch
			{
				ptr_xml();
				
				int IDT2=get_team_id(ptr_xml_g_name('"'),'"');
				
				if(!IDT2)
				{
					xml_t_end();//gtnume yev kangnume xaxi verchi vra
					continue;
				}
				for(;*ptr_xml()!='"';);
				for(;*(Xml_Bass_G+i)!=' ';i++);
				ptr_xml();
				if(name_serch(Xml_Bass_G+(++i),' '))//jamanakn e te voch
				{
					
					int* Ti=xml_g_time();
					if(*(Xml_bet_time+id_bet-1)) Ti=time_convert(Ti);
					/*for(;*ptr_xml()!='"';);
					for(;*(Xml_Bass_G+i)!=' ';i++);
					ptr_xml();
					name_serch(Xml_Bass_G+(++i),' ')*/
					/////////////////////////////////////////////////////////////////////////month
					month* Te;//@ntacik month*
					if(TEMP_CH->ptrm)
					{
						Te=TEMP_CH->ptrm;
						for(;Te;Te=Te->next)
						{
							if(*Ti==Te->y && *(Ti+1)==Te->m && *(Ti+2)==Te->day)break;
							if(!Te->next)
							{
								Te->next=new month;
								Te=Te->next;
								Te->y=*Ti;
								Te->m=*(Ti+1);
								Te->day=*(Ti+2);
								Te->back_cham=TEMP_CH;
								Te->ptrh=NULL;
								Te->next=NULL;
								break;
							}
						}
					}
					else
					{
						TEMP_CH->ptrm=new month;
						Te=TEMP_CH->ptrm;
						Te->y=*Ti;
						Te->m=*(Ti+1);
						Te->day=*(Ti+2);
						Te->back_cham=TEMP_CH;
						Te->ptrh=NULL;
						Te->next=NULL;
					}
					/////////////////////////////////////////////////////hour*
					hour* Thour;//@ntacik hour*
					if(Te->ptrh)
					{
						Thour=Te->ptrh;
						for(;Thour;Thour=Thour->next)
						{
							if(*(Ti+3)==Thour->h && *(Ti+4)==Thour->minute)break;
							/*if(Thour->ptrg->id_t1==IDT1 || Thour->ptrg->id_t2==IDT1)
							{
								cout<<endl<<"EROR time #2"<<endl;
								break;
							}*/
							if(!Thour->next)
							{
								Thour->next=new hour;
								Thour=Thour->next;
								Thour->h=*(Ti+3);
								Thour->minute=*(Ti+4);
								Thour->back_month=Te;
								Thour->ptrg=NULL;
								Thour->next=NULL;
								break;
							}
						}
					}
					else
					{
						Te->ptrh=new hour;
						Thour=Te->ptrh;
						Thour->h=*(Ti+3);
						Thour->minute=*(Ti+4);
						Thour->back_month=Te;
						Thour->ptrg=NULL;
						Thour->next=NULL;
					}
					/////////////////////////////////////////////////////game*
					game* Tgame;
					TEMP_GT=true;
					if(Thour->ptrg)
					{
						Tgame=Thour->ptrg;
						for(;Tgame;Tgame=Tgame->next)
						{
							if(Tgame->id_t1==IDT1 && Tgame->id_t2==IDT2)break;
							if(Tgame->id_t1==IDT2 && Tgame->id_t2==IDT1){TEMP_GT=false;break;}
							if(!Tgame->next)
							{
								Tgame->next=new game;
								Tgame=Tgame->next;
								Tgame->id_t1=IDT1;
								Tgame->id_t2=IDT2;
								Tgame->back_hour=Thour;
								Tgame->ptr_V=NULL;
								Tgame->next=NULL;
								Tgame->ptrkc=NULL;
								break;
							}
						}
					}
					else
					{
						Thour->ptrg=new game;
						Tgame=Thour->ptrg;
						Tgame->id_t1=IDT1;
						Tgame->id_t2=IDT2;
						Tgame->back_hour=Thour;
						Tgame->ptr_V=NULL;
						Tgame->next=NULL;
						Tgame->ptrkc=NULL;
					}
					TEMP_G=Tgame;//@ntacik game*
					if(TEMP_GT)//@ntacik ID_TEAM(1,2)
					{
						id_t1_onl=IDT1;
						id_t2_onl=IDT2;
					}
					else
					{
						id_t1_onl=IDT2;
						id_t2_onl=IDT1;
					}
					for(;*ptr_xml()!='>';);
					return true;
				}
				

			}
			
		}
	}
	xml_eror(2);
	return false;
	}
}

int* bet::xml_g_time()
{	ptr_xml();
	int* xtime=new int[5];
	int m[5]={4,2,2,2,2};
	int temp;
	for(int i=0;i<5;i++)
	{
		temp=0;
		if(i==3)ptr_xml();
		for(int j=0;j<m[i];j++)
		{
			temp=10*temp+int(*ptr_xml()-48);
		}
		*(xtime+i)=temp;
	}
	return xtime;
}

bool bet::xml_odds()//////////////////////////////////////////////////////#3  -
{
	
	for(;;)
	{
		for(;*ptr_xml()!='<';);
		if(*ptr_xml()=='/')return false;
		ptr_xml(false);
		if(name_serch(Xml_Bass_O,' '))
		{
			int i=0;
			for(;*(Xml_Bass_G+i)!=' ';i++);
			i++;
			ptr_xml();
			float kct;
			char** kc_name=xml_kc_name(kct);
			int IDKC;
			/*cout<<"\nKc: "<<kct<<endl;
			for(int i=0;i<Xml_B_ON;i++)
			{
				if(*(kc_name+i))
				{
					for(int j=0;*(*(kc_name+i)+j)!='"';j++)cout<<*(*(kc_name+i)+j);
					cout<<" ";
				}
			}
			cout<<endl;*/
			nf=true;
			bool sta=true;
			for(int i=0;i<Xml_B_ON;i++)
			{
				if(!nf)
				{
					if(*(kc_name+i)){if(sta)nf=true; out_f_kc_t(*(kc_name+i),'"');}
					if(*(kc_name+i) && sta){nf=false;sta=false;}
					continue;
				}
				if(*(kc_name+i)){/*cout<<"\n------------------"; for(int D=0;*(*(kc_name+i)+D)!='"';D++)cout<<*(*(kc_name+i)+D);*/ IDKC=get_kc_id(*(kc_name+i),'"');}
				if(!nf)	i=-1;
			}
			//cout<<"\nID_KC: "<<IDKC;
			if(IDKC)
			{
				if(!TEMP_GT)IDKC=convert_idkc(IDKC);
				if(TEMP_G->ptrkc)
				{
					for(kcT* i=TEMP_G->ptrkc;;i=i->next)
					{
						if(i->id_kc==IDKC)
						{
							kc_b* Temp_Kc=new kc_b;
							Temp_Kc->kc=kct;
							Temp_Kc->TKC=i;
							Temp_Kc->id_bet=id_bet;
							Temp_Kc->ng=TEMP_GT;
							Temp_Kc->next=NULL;
							if(bet_type && kct<0)
							{
								*(i->ptrk+1)=Temp_Kc;
								break;
							}

							if(!(*(i->ptrk))) {(*(i->ptrk))=Temp_Kc; break;}

							if((*(i->ptrk))->kc<=Temp_Kc->kc) {Temp_Kc->next=*(i->ptrk); *(i->ptrk)=Temp_Kc;break;}

							for(kc_b* j=*(i->ptrk);;j=j->next)
							{
								if(!j->next)
								{
									j->next=Temp_Kc;
									break;
								}
								if(j->next->kc<=kct)
								{
									Temp_Kc->next=j->next;
									j->next=Temp_Kc;
									break;
								}
								
							}
							break;
						}
						if(!i->next)
						{
							i->next=new kcT;
							i->next->id_kc=IDKC;
							i->next->back_game=TEMP_G;
							i->next->next=NULL;
							i->next->ptrk=new kc_b*[2];

							kc_b* Temp_Kc=new kc_b;
							Temp_Kc->kc=kct;
							Temp_Kc->TKC=i->next;
							Temp_Kc->id_bet=id_bet;
							Temp_Kc->ng=TEMP_GT;
							Temp_Kc->next=NULL;

							if(bet_type && kct<0)
							{
								(*(i->next->ptrk+1))=Temp_Kc;
								(*(i->next->ptrk))=NULL;
								break;
							}
							(*(i->next->ptrk))=Temp_Kc;
							(*(i->next->ptrk+1))=NULL;
							break;
						}
					}
				}
				else
				{
					TEMP_G->ptrkc=new kcT;
					TEMP_G->ptrkc->id_kc=IDKC;
					TEMP_G->ptrkc->back_game=TEMP_G;
					TEMP_G->ptrkc->next=NULL;
					TEMP_G->ptrkc->ptrk=new kc_b*[2];

					kc_b* Temp_Kc=new kc_b;
					Temp_Kc->kc=kct;
					Temp_Kc->TKC=TEMP_G->ptrkc;
					Temp_Kc->id_bet=id_bet;
					Temp_Kc->ng=TEMP_GT;
					Temp_Kc->next=NULL;

					if(bet_type && kct<0)
					{
						(*(TEMP_G->ptrkc->ptrk+1))=Temp_Kc;
						(*(TEMP_G->ptrkc->ptrk))=NULL;
						continue;
					}
					(*(TEMP_G->ptrkc->ptrk))=Temp_Kc;
					(*(TEMP_G->ptrkc->ptrk+1))=NULL;
					continue;
				}
			}
			else continue;
			//
			continue;
		}
		//for(int j=0;j<80;j++)cout<<*ptr_xml();exit(0);
		xml_eror(3);
		return false;
	}
}

char** bet::xml_kc_name(float& kc)
{
	char** temp=new char*[Xml_B_ON];
	for(int i=0;i<Xml_B_ON;i++) *(temp+i)=NULL;
	bool lay=false;//LAY=ture
	bool ok;
	for(char s=*ptr_xml();;s=*ptr_xml())
	{
		if(s=='/')
		{
			if(*ptr_xml()=='>')break;
			ptr_xml(false);
		}
		if(s==' ')continue;
		ok=false;
		for(int i=0;i<Xml_B_ON;i++)
		{
			if(!*(Xml_B_O+i))continue;
			if(s==**(Xml_B_O+i))
			{
				for(int q=0;;q++)
				{
					if(*(*(Xml_B_O+i)+q)==' ' && s=='"')
					{
						if(i==1 && bet_type)//ete birjaye yev LAY e
						{
							lay=true;
							ok=true;
							break;
						}
						else
						{
							/////////////////////////////////////////////////////
							char* Temp_X=ptr_xml_g_name('"');
								//if(!Temp_X)cout<<"["<<Temp_X<<"]";
							/////////////////////////////////////////////////////
							for(;*ptr_xml()!='"';);
							*(temp+i)=Temp_X;
						}
						if(!i){ kc=char_fl( *(temp+i) ); *(temp+i)=NULL;}
						//ptr_xml();
						*(Xml_B_OT+i)=*(Xml_B_O+i);
						*(Xml_B_O+i)=NULL;
						ok=true;
						break;
						
					}
					if(*(*(Xml_B_O+i)+q)!=s)
					{
						for(int z=0;z<=q;z++)ptr_xml(false);
						s=*ptr_xml();
						//ok=true;
						break;
					}
					s=*ptr_xml();
				}
			}
			if(ok)break;
		}
	}
	for(int i=0;i<Xml_B_ON;i++)	if(*(Xml_B_O+i)) *(Xml_B_OT+i)=*(Xml_B_O+i);
	char** tt=Xml_B_O;
	Xml_B_O=Xml_B_OT;
	Xml_B_OT=tt;
	if(lay)kc=-kc;
	return temp;
}

float bet::char_fl(char* kc)
{
	float T=0.0;
	float t=0.0;
	int i=0;
	
	for(;*(kc+i)!='"'; i++)
	{
		
		if(*(kc+i)!='.')T=10*T+int(*(kc+i)-48);
		else
		{
			
			double n=1;
			for(int q=i+1;*(kc+q)!='"';q++)
			{
				n*=0.1;
				t+=n*int(*(kc+q)-48);
			}
			break;
		}
				
	}
	return (T+t);
}

int bet::convert_idkc(int IDKC)//Nor kci avelacman depqum ID_KC avelacnel!!!!!!!!!!!!!!!!!!!!!!!!!!!
{
	//////////////////////////////////////////////////////////////////////////////////////////////
	const int Ns=5;
	int m_s[Ns]={1,2,3,4,6};//qayler
	const int Nsid=21;//qaylum amenashat idneri qanak@
	int m_id[Ns][Nsid]=//qaylerin hamapatasxan idiner@ {ID1_min,ID1_max, ID2_min,ID2_max, ...}
	{
		{141,142, 191,192, 213,214, 291,292, 342,343 },//qayl(1)-blok(2)
		{1,4, 7,10, 13,16, 125,140, 143,158, 159,190, 193,212, 215,234, 271,278, 367,390 },//qayl(2)-blok(4)
		{264,269, 306,341},//qayl(3)-blok(6)
		{252,259 },//qayl(4)-blok(8)
		{235,246 }//qayl(6)-blok(12)
	};
	///////////////////////////////////////////////////////////////////////////////////////////////
	for(int i=0;i<Ns;i++)
	{
		for(int j=0;j<Nsid && m_id[i][j];j+=2)
		{
			if(IDKC>=m_id[i][j] && IDKC<=m_id[i][j+1])
			{
				int n=1+(IDKC-m_id[i][j])%(2*m_s[i]);
				if((n+m_s[i])>(2*m_s[i]))return (IDKC-m_s[i]);
				return (IDKC+m_s[i]);
			}
			else continue;
		}
	}
	return IDKC;
}

int* bet::time_convert(int* date)//0-year, 1-month, 2-day, 3-hour, 4-minute
{
	///////////////////////////////////////////////////////////////////////
	int temp_minute=21564000; //1970-2011
	for(int i=2012;i<=*date;i++)
	{
		if( !(i%4) )temp_minute+=1440;
		temp_minute+=365*1440;
	}
	int M[12]={0,31,59,90,120,151,181,212,243,273,304,334};
	//if( !((*date)%4) )temp_minute+=1440;
	temp_minute+=M[*(date+1)-1]*1440;
	temp_minute+=(*(date+2)-1)*1440;
	temp_minute+=(*(date+3))*60;
	temp_minute+=*(date+4);
	///////////////////////////////////////////////////////////////////////
	temp_minute-=180;//<<-------???????????????????????
	////////////////////////////////////////////////////////////
	int* temp=new int[5];
	time_t T=(temp_minute+(*(Xml_bet_time+id_bet-1)))*60;
	tm* a=localtime(&T);
	*temp=a->tm_year+1900;
	*(temp+1)=a->tm_mon+1;
	*(temp+2)=a->tm_mday;
	*(temp+3)=a->tm_hour;
	*(temp+4)=a->tm_min;
	return temp;
	
}

int* bet::TIME_H(int hour)//0-year, 1-month, 2-day, 3-hour, 4-minute
{
	int* temp=new int[5];
	time_t T=time(0)+hour*3600;
	tm* a=localtime(&T);
	*temp=a->tm_year+1900;
	*(temp+1)=a->tm_mon+1;
	*(temp+2)=a->tm_mday;
	*(temp+3)=a->tm_hour;
	*(temp+4)=a->tm_min;
	return temp;
}

bool bet::TIME_M(int* date,int max,int min)//date->0-year, 1-month, 2-day, 3-hour, 4-minute
{
	///////////////////////////////////////////////////////////////////////
	int temp_minute=21564000; //1970-2011
	for(int i=2012;i<=*date;i++)
	{
		if( !(i%4) )temp_minute+=1440;
		temp_minute+=365*1440;
	}
	int M[12]={0,31,59,90,120,151,181,212,243,273,304,334};
	if( !((*date)%4) )temp_minute+=1440;
	temp_minute+=M[*(date+1)-1]*1440;
	temp_minute+=(*(date+2)-1)*1440;
	temp_minute+=(*(date+3))*60;
	temp_minute+=*(date+4);
	///////////////////////////////////////////////////////////////////////
	if(!min) min=int(time(0))/60;
	temp_minute-=300;//<<-------???????????????????????
	//int T_H=temp_minute/60-int(time(0))/3600;
	if(temp_minute>=min && temp_minute<=max)return true;
	return false;
}

void bet::print_all()
{
	//for(;;)
	{
		char ggs[32];
		col("\nID_S: ");col(itoa(G.id_s,ggs,10));col("	");col(get_sport_name(G.id_s,1));col("\n");
		for(cham* ch=G.ptrch;ch;ch=ch->next)
		{
			if(!ch->ptrm)continue;
			col("\nID_CH: ");col(itoa(ch->id_ch,ggs,10));col("\n");//<<"			"<<get_cham_name(ch->id_ch,G.id_s,1)<<endl;
			for(month* mo=ch->ptrm;mo;mo=mo->next)
			{
				if(!mo->ptrh)continue;
				col("(Y M D): ");col(itoa(mo->y,ggs,10));col(" ");col(itoa(mo->m,ggs,10));col(" ");col(itoa(mo->day,ggs,10));col("\n");
				for(hour* ho=mo->ptrh;ho;ho=ho->next)
				{
					col("\n[H M]: ");col(itoa(ho->h,ggs,10));col(" ");col(itoa(ho->minute,ggs,10));col("\n");
					for(game* ga=ho->ptrg;ga;ga=ga->next)
					{
						if(!ga->ptrkc)continue;
						col("\nID_T1: ");col(itoa(ga->id_t1,ggs,10));col(" ");col(get_team_name(ga->id_t1,ch->id_ch,G.id_s,1));col(" ID_T2: ");col(itoa(ga->id_t2,ggs,10));col(" ");col(get_team_name(ga->id_t2,ch->id_ch,G.id_s,1));col("\n");
						for(kcT* k=ga->ptrkc;k;k=k->next)
						{
							col("\nID_KC: ");col(itoa(k->id_kc,ggs,10));col("\n");//<<" "<<get_kc_name(k->id_kc,G.id_s,1,ch->id_ch,ga->id_t1,ga->id_t2)
							for(kc_b** b=k->ptrk;;)
							{
								if(*b){for(kc_b* V=*b;V;V=V->next)
								{
									col("KC: ");sprintf(ggs,"%f",(V->kc));col(ggs);col(" (");col(bet_name(V->id_bet));col(") \n");
									//if(!V->next)break;
								}}
								if(*(b+1)){for(kc_b* V=*(b+1);V;V=V->next)
								{
									col("\nLAY KC: ");sprintf(ggs,"%f",(V->kc));col(ggs);col(" (");col(bet_name(1));col(") ");
									//if(!V->next)break;
								}}
								break;
							}
							//if(!k->next)break;
						}
						//if(!ga->next)break;
					}
					//if(!ho->next)break;
				}
				//if(!mo->next)break;
			}
			//if(!(ch->next))break;
		}
	}
}

//********************************GX************************************//
void bet::ADD_GX(sport* Sp,bool Add_Next)
{
	int IBB=id_bet;
	if(!Add_Next)
	{
		G.id_s=0;
		G.next=NULL;
		G.ptrch=NULL;
		TEMP_S=NULL;
		TEMP_CH=NULL;
		TEMP_G=NULL;
		TEMP_GT=true;
	}

	for(;Sp;Sp=Sp->next)
	{
////////////////////////SPORT/////////////////////////
{
	//sport* Temp;
	if(!G.id_s)
	{ 
		TEMP_S=&G; 
		id_s_onl=Sp->id_s; 
		G.id_s=id_s_onl;
	}
}
//////////////////////////////////////////////////////
////////////////////////CHAM/////////////////////////
	for(cham* GXCHA=Sp->ptrch; GXCHA ; GXCHA=GXCHA->next)
	{
		int IDCH = GXCHA->id_ch;
		if(IDCH)
		{
			id_ch_onl=IDCH;//@ntacik id_cham
			if(TEMP_S->ptrch)
			{
				cham* Te=TEMP_S->ptrch;
				for(;Te;Te=Te->next)
				{
					if(IDCH==Te->id_ch)break;
					if(!Te->next)
					{
						Te->next=new cham;
						Te=Te->next;
						Te->id_ch=IDCH;
						Te->back_sport=TEMP_S;
						Te->next=NULL;
						Te->ptrm=NULL;
						break;
					}
				}
				TEMP_CH=Te;//@ntacik chami hasce
			}
			else
			{
				TEMP_S->ptrch=new cham;
				TEMP_S->ptrch->id_ch=IDCH;
				TEMP_S->ptrch->back_sport=TEMP_S;
				TEMP_S->ptrch->next=NULL;
				TEMP_S->ptrch->ptrm=NULL;
				TEMP_CH=TEMP_S->ptrch;//@ntacik chami hasce
			}
		}
		//////////////////////////month//////////////////////
		for(month* GXMO=GXCHA->ptrm; GXMO; GXMO=GXMO->next)
		{
			bool MO_STATUS=true;
			int* Ti=new int[5];
			*Ti=GXMO->y;
			*(Ti+1)=GXMO->m;
			*(Ti+2)=GXMO->day;
			month* Te;//@ntacik month*
			if(TEMP_CH->ptrm)
			{
				Te=TEMP_CH->ptrm;
				for(;Te;Te=Te->next)
				{
					if(*Ti==Te->y && *(Ti+1)==Te->m && *(Ti+2)==Te->day)break;
					if(!Te->next)
					{
						MO_STATUS=false;
						break;
					}
				}
			}
			else
			{
				TEMP_CH->ptrm=new month;
				Te=TEMP_CH->ptrm;
				Te->y=*Ti;
				Te->m=*(Ti+1);
				Te->day=*(Ti+2);
				Te->back_cham=TEMP_CH;
				Te->ptrh=NULL;
				Te->next=NULL;
			}
			/////////////////////////hour////////////////////////////
			//----------------------------------------------------------------------
			const int Dt=4;//ropenerov shexum@
			int THM_B, THM_N;//bazayum gtnvox xaxi jam@ yev nor xaxi jam@ ropenerov
			//----------------------------------------------------------------------
			for(hour* GXHO=GXMO->ptrh; GXHO; GXHO=GXHO->next)
			{
				bool HO_STATUS=true;
				hour* Thour;//@ntacik hour*
				*(Ti+3)=GXHO->h;
				*(Ti+4)=GXHO->minute;
				if(MO_STATUS){//MO-n chi gtnvel
				if(Te->ptrh)
				{
					Thour=Te->ptrh;
					for(;Thour;Thour=Thour->next)
					{
						if(*(Ti+3)==Thour->h && *(Ti+4)==Thour->minute)break;
						//----------------------------------------------------------------------
						THM_B=(Thour->h)*60+(Thour->minute);
						THM_N=(*(Ti+3))*60+(*(Ti+4));
						if(THM_N>=(THM_B-Dt) && THM_N<=(THM_B+Dt))break;
						//----------------------------------------------------------------------
						if(!Thour->next)
						{
							/*Thour->next=new hour;
							Thour=Thour->next;
							Thour->h=*(Ti+3);
							Thour->minute=*(Ti+4);
							Thour->back_month=Te;
							Thour->ptrg=NULL;
							Thour->next=NULL;*/
							HO_STATUS=false;
							break;
						}
					}
				}
				else
				{
					Te->ptrh=new hour;
					Thour=Te->ptrh;
					Thour->h=*(Ti+3);
					Thour->minute=*(Ti+4);
					Thour->back_month=Te;
					Thour->ptrg=NULL;
					Thour->next=NULL;
				}}
				///////////////////////game//////////////////////////////
				for(game* GXGA=GXHO->ptrg; GXGA;GXGA=GXGA->next)
				{
					int IDT1=GXGA->id_t1;
					int IDT2=GXGA->id_t2;
					if(!MO_STATUS || !HO_STATUS)
					{
						hour* tho;
						for(game* Game=GXHO->ptrg;;Game=Game->next)
						{
							tho=find_gameID(Te->back_cham->ptrm, Ti, Game->id_t1, Game->id_t2);
							if(tho)
							{
								MO_STATUS=true;
								HO_STATUS=true;
								Thour=tho;
								break;
							}
							if(!Game->next)
							{
								if(!MO_STATUS)
								{
									Te->next=new month;
									Te=Te->next;
									Te->y=*Ti;
									Te->m=*(Ti+1);
									Te->day=*(Ti+2);
									Te->back_cham=TEMP_CH;
									//Te->ptrh=NULL;
									Te->next=NULL;
									
									Te->ptrh=new hour;
									Thour=Te->ptrh;
								}
								if(!HO_STATUS)
								{
									Thour->next=new hour;
									Thour=Thour->next;
								}
								Thour->h=*(Ti+3);
								Thour->minute=*(Ti+4);
								Thour->back_month=Te;
								Thour->ptrg=NULL;
								Thour->next=NULL;
								break;
							}
						}
					}
					int* GOAL=GXGA->goal;
					game* Tgame;
					TEMP_GT=true;
					if(Thour->ptrg)
					{
						Tgame=Thour->ptrg;
						for(;Tgame;Tgame=Tgame->next)
						{
							if(Tgame->id_t1==IDT1 && Tgame->id_t2==IDT2)break;
							if(Tgame->id_t1==IDT2 && Tgame->id_t2==IDT1){TEMP_GT=false;break;}
							if(!Tgame->next)
							{
								Tgame->next=new game;
								Tgame=Tgame->next;
								Tgame->id_t1=IDT1;
								Tgame->id_t2=IDT2;
								Tgame->goal=GOAL;
								Tgame->back_hour=Thour;
								Tgame->ptr_V=NULL;
								Tgame->next=NULL;
								Tgame->ptrkc=NULL;
								break;
							}
						}
					}
					else
					{
						Thour->ptrg=new game;
						Tgame=Thour->ptrg;
						Tgame->id_t1=IDT1;
						Tgame->id_t2=IDT2;
						Tgame->goal=GOAL;
						Tgame->back_hour=Thour;
						Tgame->ptr_V=NULL;
						Tgame->next=NULL;
						Tgame->ptrkc=NULL;
					}
					TEMP_G=Tgame;//@ntacik game*
					if(TEMP_GT)//@ntacik ID_TEAM(1,2)
					{
						id_t1_onl=IDT1;
						id_t2_onl=IDT2;
					}
					else
					{
						id_t1_onl=IDT2;
						id_t2_onl=IDT1;
					}
					///////////////////////KC//////////////////////////////
					float kct;
					int IDKC;
					int IDB_N;
					kc_b* KC_BT;
					bool OT;
					for(kcT* GXKC=GXGA->ptrkc; GXKC; GXKC=GXKC->next)
					{
						IDKC=GXKC->id_kc;
						OT=true;
						if( *(GXKC->ptrk) ) KC_BT=*(GXKC->ptrk);
						else{if( *(GXKC->ptrk+1) ) KC_BT=*(GXKC->ptrk+1); OT=false; }
						for(;;)
						{
							kct=KC_BT->kc;
							IDB_N=KC_BT->id_bet_name;
							if(IDKC)
							{
								if(!TEMP_GT)IDKC=convert_idkc(IDKC);
								if(TEMP_G->ptrkc)
								{
									for(kcT* i=TEMP_G->ptrkc;;i=i->next)
									{
										if(i->id_kc==IDKC)
										{
											kc_b* Temp_Kc=new kc_b;
											Temp_Kc->kc=kct;
											Temp_Kc->TKC=i;
											Temp_Kc->id_bet=id_bet;
											Temp_Kc->id_bet_name=IDB_N;
											Temp_Kc->ng=TEMP_GT;
											Temp_Kc->next=NULL;
											if(kct<0)
											{
												*(i->ptrk+1)=Temp_Kc;
												break;
											}

											if(!(*(i->ptrk))) {(*(i->ptrk))=Temp_Kc; break;}

											if((*(i->ptrk))->kc<=Temp_Kc->kc) {Temp_Kc->next=*(i->ptrk); *(i->ptrk)=Temp_Kc;break;}

											for(kc_b* j=*(i->ptrk);;j=j->next)
											{
												if(!j->next)
												{
													j->next=Temp_Kc;
													break;
												}
												if(j->next->kc<=kct)
												{
													Temp_Kc->next=j->next;
													j->next=Temp_Kc;
													break;
												}
								
											}
											break;
										}
										if(!i->next)
										{
											i->next=new kcT;
											i->next->id_kc=IDKC;
											i->next->back_game=TEMP_G;
											i->next->next=NULL;
											i->next->ptrk=new kc_b*[2];
											
											kc_b* Temp_Kc=new kc_b;
											Temp_Kc->kc=kct;
											Temp_Kc->TKC=i->next;
											Temp_Kc->id_bet=id_bet;
											Temp_Kc->id_bet_name=IDB_N;
											Temp_Kc->ng=TEMP_GT;
											Temp_Kc->next=NULL;

											if(kct<0)
											{
												(*(i->next->ptrk+1))=Temp_Kc;
												(*(i->next->ptrk))=NULL;
												break;
											}
											(*(i->next->ptrk))=Temp_Kc;
											(*(i->next->ptrk+1))=NULL;
											break;
										}
									}
								}
								else
								{
									TEMP_G->ptrkc=new kcT;
									TEMP_G->ptrkc->id_kc=IDKC;
									TEMP_G->ptrkc->back_game=TEMP_G;
									TEMP_G->ptrkc->next=NULL;
									TEMP_G->ptrkc->ptrk=new kc_b*[2];
									
									kc_b* Temp_Kc=new kc_b;
									Temp_Kc->kc=kct;
									Temp_Kc->TKC=TEMP_G->ptrkc;
									Temp_Kc->id_bet=id_bet;
									Temp_Kc->id_bet_name=IDB_N;
									Temp_Kc->ng=TEMP_GT;
									Temp_Kc->next=NULL;

									if(kct<0)
									{
										(*(TEMP_G->ptrkc->ptrk+1))=Temp_Kc;
										(*(TEMP_G->ptrkc->ptrk))=NULL;
										
									}
									else
									{
										(*(TEMP_G->ptrkc->ptrk))=Temp_Kc;
										(*(TEMP_G->ptrkc->ptrk+1))=NULL;
									
									}
								}
							}
							if(OT)
							{
								if( *(GXKC->ptrk+1) )
								{
									KC_BT=*(GXKC->ptrk+1); 
									OT=false;
								}
								else break;
							}
							else break;
						}
					}
				}
			}
		}
	}
	}

}

bool bet::set_GX(sport *Gxml,int ID_B,bool Birja)
{
	GX=Gxml;
	bet_type=Birja;
	id_bet_T=ID_B;
	if(!Gxml)return false;
	if(ID_B>0 && ID_B<=n_bet) id_bet=ID_B;
	else return false;
	return true;
}

bool bet::set_GX_IB(int ID_B)
{
	if(ID_B>0 && ID_B<=n_bet) id_bet_T=ID_B;
	else return false;
	return true;
}

bool bet::set_GX_ID(int ID_S)
{
	id_s_onl=ID_S;
	TEMP_S=GX;
	GX_STATUS[0]=false;//CHAM
	GX_STATUS[1]=false;//GAME
	GX_STATUS[2]=false;//KC
	if(!GX->id_s)
	{
		GX->id_s=ID_S;
		return true;
	}
	for(;;)
	{
		if( (TEMP_S->id_s)==ID_S )
		{
			//TEMP_S->ptrch=NULL;//ptrch[DELETE]
			return true;
		}
		if(!TEMP_S->next)
		{
			TEMP_S->next=new sport;
			TEMP_S=TEMP_S->next;
			TEMP_S->id_s=ID_S;
			TEMP_S->ptrch=NULL;
			TEMP_S->next=NULL;
			return true;
		}
		TEMP_S=TEMP_S->next;
	}

}

bool bet::set_GX_CHAM(char* CH_N,char E)
{
	static char* CH_NAME=NULL;
	static char END='\0';
	static int IDCH=0;
	if(!GX_STATUS[2])
	{
		CH_NAME=CH_N;
		END=E;
		IDCH = get_cham_id(CH_NAME,END);
		id_ch_onl=IDCH;//@ntacik id_cham
		if(!IDCH)return false;
		GX_STATUS[0]=true;
		return true;
	}
		
	
	if(IDCH)
	{
		
		if(TEMP_S->ptrch)
		{
			cham* Te=TEMP_S->ptrch;
			for(;Te;Te=Te->next)
			{
				if(IDCH==Te->id_ch)break;
				if(!Te->next)
				{
					Te->next=new cham;
					Te=Te->next;
					Te->id_ch=IDCH;
					Te->back_sport=TEMP_S;
					Te->next=NULL;
					Te->ptrm=NULL;
					break;
				}
			}
			TEMP_CH=Te;//@ntacik chami hasce
		}
		else
		{
			TEMP_S->ptrch=new cham;
			TEMP_S->ptrch->id_ch=IDCH;
			TEMP_S->ptrch->back_sport=TEMP_S;
			TEMP_S->ptrch->next=NULL;
			TEMP_S->ptrch->ptrm=NULL;
			TEMP_CH=TEMP_S->ptrch;//@ntacik chami hasce
		}
		GX_STATUS[0]=false;
		return true;
	}
	return false;
}

int* bet::GX_time_convert(int* date,int Diff_Time)
{
	///////////////////////////////////////////////////////////////////////
	int sd[5];
	sd[0]=*date;
	sd[1]=*(date+1);
	sd[2]=*(date+2);
	sd[3]=*(date+3);
	sd[4]=*(date+4);
	int temp_minute=21564000; //1970-2011
	for(int i=2012;i<=*date;i++)
	{
		if( !(i%4) )temp_minute+=1440;
		temp_minute+=365*1440;
	}
	int M[12]={0,31,59,90,120,151,181,212,243,273,304,334};
	//if( !((*date)%4) )temp_minute+=1440;
	temp_minute+=M[*(date+1)-1]*1440;
	temp_minute+=(*(date+2)-1)*1440;
	temp_minute+=(*(date+3))*60;
	temp_minute+=*(date+4);
	///////////////////////////////////////////////////////////////////////
	temp_minute-=180;//<<-------???????????????????????
	////////////////////////////////////////////////////////////
	int* temp=new int[5];
	time_t T=(temp_minute+(Diff_Time))*60;
	tm* a=localtime(&T);
	*temp=a->tm_year+1900;
	*(temp+1)=a->tm_mon+1;
	*(temp+2)=a->tm_mday;
	*(temp+3)=a->tm_hour;
	*(temp+4)=a->tm_min;
	return temp;
}

bool bet::GX_TIME_C(int* TimeGame,int minT,int maxT)
{
	tm TmTime;
	TmTime.tm_year=*TimeGame-1900;
	TmTime.tm_mon=*(TimeGame+1)-1;
	TmTime.tm_mday=*(TimeGame+2);
	TmTime.tm_hour=*(TimeGame+3);
	TmTime.tm_min=*(TimeGame+4);
	TmTime.tm_sec=0;
	time_t SGT=mktime(&TmTime);
	time_t SMinT=time(NULL)+minT*3600;
	time_t SMaxT=time(NULL)+maxT*3600;
	if(SGT>=SMinT && SGT<=SMaxT) return true;
	return false;
}

int* bet::GX_TIME_U(const char* CH_MST)
{
	__int64 MST=_atoi64(CH_MST);
	__int64 ST=MST/1000;
	time_t TU = static_cast<time_t>(ST);
	int *RT=new int[5];
	tm *ptm=gmtime(&TU);
	*(RT)=ptm->tm_year+1900;
	*(RT+1)=ptm->tm_mon+1;
	*(RT+2)=ptm->tm_mday;
	*(RT+3)=ptm->tm_hour;
	*(RT+4)=ptm->tm_min;
	return RT;
}

bool bet::set_GX_GAME(char* TE1,char E1,char* TE2,char E2,int* TIm,int* Goal)
{
	static char* Team1=NULL;
	static char END1='\0';
	static char* Team2=NULL;
	static char END2='\0';
	static int* Ti=NULL;
	static int IDT1=0;
	static int IDT2=0;
	if(!GX_STATUS[2])
	{
		Team1=TE1;
		END1=E1;
		Team2=TE2;
		END2=E2;
		Ti=TIm;
		IDT1=get_team_id(Team1,END1);
		IDT2=get_team_id(Team2,END2);
		id_t1_onl=IDT1;
		id_t2_onl=IDT2;
		if(!IDT1 || !IDT2)return false;
		if(Goal) 
		{
			GX_GOAL=Goal;
		}
		else GX_GOAL=GET_GOAL(id_s_onl,id_ch_onl,IDT1,IDT2,Ti);
		GX_STATUS[1]=true;
		return true;
	}
	

	/////////////////////////////////////////////////////////////////////////month
	month* Te;//@ntacik month*
	if(TEMP_CH->ptrm)
	{
		Te=TEMP_CH->ptrm;
		for(;Te;Te=Te->next)
		{
			if(*Ti==Te->y && *(Ti+1)==Te->m && *(Ti+2)==Te->day)break;
			if(!Te->next)
			{
				Te->next=new month;
				Te=Te->next;
				Te->y=*Ti;
				Te->m=*(Ti+1);
				Te->day=*(Ti+2);
				Te->back_cham=TEMP_CH;
				Te->ptrh=NULL;
				Te->next=NULL;
				break;
			}
		}
	}
	else
	{
		TEMP_CH->ptrm=new month;
		Te=TEMP_CH->ptrm;
		Te->y=*Ti;
		Te->m=*(Ti+1);
		Te->day=*(Ti+2);
		Te->back_cham=TEMP_CH;
		Te->ptrh=NULL;
		Te->next=NULL;
	}
	/////////////////////////////////////////////////////hour*
	hour* Thour;//@ntacik hour*
	if(Te->ptrh)
	{
		Thour=Te->ptrh;
		for(;Thour;Thour=Thour->next)
		{
			if(*(Ti+3)==Thour->h && *(Ti+4)==Thour->minute)break;
			if(!Thour->next)
			{
				Thour->next=new hour;
				Thour=Thour->next;
				Thour->h=*(Ti+3);
				Thour->minute=*(Ti+4);
				Thour->back_month=Te;
				Thour->ptrg=NULL;
				Thour->next=NULL;
				break;
			}
		}
	}
	else
	{
		Te->ptrh=new hour;
		Thour=Te->ptrh;
		Thour->h=*(Ti+3);
		Thour->minute=*(Ti+4);
		Thour->back_month=Te;
		Thour->ptrg=NULL;
		Thour->next=NULL;
	}
	/////////////////////////////////////////////////////game*
	game* Tgame;
	//TEMP_GT=true;
	if(Thour->ptrg)
	{
		Tgame=Thour->ptrg;
		for(;Tgame;Tgame=Tgame->next)
		{
			if(Tgame->id_t1==IDT1 && Tgame->id_t2==IDT2)break;
			//if(Tgame->id_t1==IDT2 && Tgame->id_t2==IDT1){TEMP_GT=false;break;}
			if(!Tgame->next)
			{
				Tgame->next=new game;
				Tgame=Tgame->next;
				Tgame->id_t1=IDT1;
				Tgame->id_t2=IDT2;
				//Tgame->goal=GX_GOAL;
				//-------------------------
				if(GX_GOAL)
				{
					Tgame->goal=GX_GOAL;
					//*(Tgame->goal)=* GX_GOAL;
					//*(Tgame->goal+1)=*( GX_GOAL+1);
				}
				else
				{
					Tgame->goal=new int[2];
					*(Tgame->goal)=0;
					*(Tgame->goal+1)=0;
				}
				//-------------------------
				Tgame->back_hour=Thour;
				Tgame->ptr_V=NULL;
				Tgame->next=NULL;
				Tgame->ptrkc=NULL;
				break;
			}
		}
	}
	else
	{
		Thour->ptrg=new game;
		Tgame=Thour->ptrg;
		Tgame->id_t1=IDT1;
		Tgame->id_t2=IDT2;
		//Tgame->goal=GX_GOAL;
		//------------------------
		if(GX_GOAL)
		{
			Tgame->goal=GX_GOAL;
			//*(Tgame->goal)=*GX_GOAL;
			//*(Tgame->goal+1)=*(GX_GOAL+1);
		}
		else
		{
			Tgame->goal=new int[2];
			*(Tgame->goal)=0;
			*(Tgame->goal+1)=0;
		}
		//------------------------
		Tgame->back_hour=Thour;
		Tgame->ptr_V=NULL;
		Tgame->next=NULL;
		Tgame->ptrkc=NULL;
	}
	TEMP_G=Tgame;//@ntacik game*
	/*if(TEMP_GT)//@ntacik ID_TEAM(1,2)
	{
		id_t1_onl=IDT1;
		id_t2_onl=IDT2;
	}
	else
	{
		id_t1_onl=IDT2;
		id_t2_onl=IDT1;
	}*/
	GX_STATUS[1]=false;
	return true;
}

hour* bet::find_gameID(month* MO,int* TimeGame, int ID_T1, int ID_T2)
{
	tm TmTime;
	TmTime.tm_year=*TimeGame-1900;
	TmTime.tm_mon=*(TimeGame+1)-1;
	TmTime.tm_mday=*(TimeGame+2);
	TmTime.tm_hour=*(TimeGame+3);
	TmTime.tm_min=*(TimeGame+4);
	TmTime.tm_sec=0;
	time_t SGT=mktime(&TmTime);
	const int minT=-12*3600;
	const int maxT=12*3600;
	time_t SMinT=SGT+minT;
	time_t SMaxT=SGT+maxT;
	//--------------------------------------------
	tm tb;
	time_t AccT;
	tb.tm_sec=0;
	//--------------------------------------------
	for(; MO; MO=MO->next)
	{
		tb.tm_year=MO->y-1900;
		tb.tm_mon=MO->m-1;
		tb.tm_mday=MO->day;
		for(hour* HO=MO->ptrh; HO; HO=HO->next)
		{
			tb.tm_hour=HO->h;
			tb.tm_min=HO->minute;
			AccT=mktime(&tb);
			if(AccT>SMinT && AccT<SMaxT)
			{
				for(game* Ga=HO->ptrg; Ga; Ga=Ga->next)
				{
					if( (Ga->id_t1==ID_T1 && Ga->id_t2==ID_T2) || (Ga->id_t1==ID_T2 && Ga->id_t2==ID_T1)) return HO;
				}
			}
		}
	}
	return NULL;
}

bool bet::set_GX_KC(char** KC_NAME,char END,float KC)
{
	float kct=KC;
	char** kc_name=KC_NAME;
	int IDKC;
	nf=true;
	nf_BT=NULL;
	bool sta=true;
	for(int i=0; *(kc_name+i);i++ )
	{
		if(!nf)
		{
			if(*(kc_name+i)){if(sta)nf=true; out_f_kc_t(*(kc_name+i),END);}
			if(*(kc_name+i) && sta){nf=false;sta=false;}
			continue;
		}
		if(*(kc_name+i)){IDKC=get_kc_id(*(kc_name+i),END);}
		if(!nf){i=-1; if(!nf_BT){delete nf_BT; nf_BT=NULL;}}
	}
	if(!nf_BT){delete nf_BT; nf_BT=NULL;}
	if(IDKC)
	{
		int TEMP_IDKC=IDKC;
		float TEMP_kct=kct;
		if(GX_GOAL)
		{ 
			if( ((*GX_GOAL)!=(*(GX_GOAL+1))) && *(BetInPlayKcConvert+id_bet_T) )
			{ 
				IDKC=ConvertForaKcId(IDKC);
			}
		}//CONVERT FORA "GOAL"
		//////////////////////////////
		GX_STATUS[2]=true;
		if(GX_STATUS[0]) set_GX_CHAM();
		if(GX_STATUS[1]) set_GX_GAME();
		//////////////////////////////
		bool IJK=false;
		bool IJK2=true;
		if(TEMP_IDKC!=IDKC) IJK=true;
		do{
			if(IJK)
			{
				if(IJK2)
				{
					int idkctemp=IDKC;
					IDKC=TEMP_IDKC;
					TEMP_IDKC=idkctemp;
					kct=1.0;
					IJK2=false;
				}
				else
				{
					IDKC=TEMP_IDKC;
					kct=TEMP_kct;
					IJK=false;
				}
			}


		if(!TEMP_GT)IDKC=convert_idkc(IDKC);
		if(TEMP_G->ptrkc)
		{
			for(kcT* i=TEMP_G->ptrkc;;i=i->next)
			{
				if(i->id_kc==IDKC)
				{
					if(kct>0)
					{
						if(*(i->ptrk)){ if((*(i->ptrk))->id_bet_name==id_bet_T){(*(i->ptrk))->kc=kct;break;} }
					}
					else
					{
						if(*(i->ptrk+1)){ if((*(i->ptrk+1))->id_bet_name==id_bet_T){(*(i->ptrk+1))->kc=-kct;break;} }
					}
					kc_b* Temp_Kc=new kc_b;
					Temp_Kc->kc=kct;
					Temp_Kc->TKC=i;
					Temp_Kc->id_bet=id_bet;
					Temp_Kc->id_bet_name=id_bet_T;
					//if(id_bet_T) Temp_Kc->id_bet_name=id_bet_T;
					Temp_Kc->ng=TEMP_GT;
					Temp_Kc->next=NULL;
					if(bet_type && kct<0)
					{
						*(i->ptrk+1)=Temp_Kc;
						break;
					}

					if(!(*(i->ptrk))) {(*(i->ptrk))=Temp_Kc; break;}

					if((*(i->ptrk))->kc<=Temp_Kc->kc) 
					{
						Temp_Kc->next=*(i->ptrk);
						*(i->ptrk)=Temp_Kc;break;
					}

					for(kc_b* j=*(i->ptrk);;j=j->next)
					{
						if(!j->next)
						{
							j->next=Temp_Kc;
							break;
						}
						if(j->next->kc<=kct)
						{
							Temp_Kc->next=j->next;
							j->next=Temp_Kc;
							break;
						}
						
					}
					break;
				}
				if(!i->next)
				{
					i->next=new kcT;
					i->next->id_kc=IDKC;
					i->next->back_game=TEMP_G;
					i->next->next=NULL;
					i->next->ptrk=new kc_b*[2];
					
					kc_b* Temp_Kc=new kc_b;
					Temp_Kc->kc=kct;
					Temp_Kc->TKC=i->next;
					Temp_Kc->id_bet=id_bet;
					Temp_Kc->id_bet_name=id_bet_T;
					//if(id_bet_T) Temp_Kc->id_bet_name=id_bet_T;
					Temp_Kc->ng=TEMP_GT;
					Temp_Kc->next=NULL;

					if(bet_type && kct<0)
					{
						(*(i->next->ptrk+1))=Temp_Kc;
						(*(i->next->ptrk))=NULL;
						break;
					}
					(*(i->next->ptrk))=Temp_Kc;
					(*(i->next->ptrk+1))=NULL;
					break;
				}
			}
		}
		else
		{
			TEMP_G->ptrkc=new kcT;
			TEMP_G->ptrkc->id_kc=IDKC;
			TEMP_G->ptrkc->back_game=TEMP_G;
			TEMP_G->ptrkc->next=NULL;
			TEMP_G->ptrkc->ptrk=new kc_b*[2];
			
			kc_b* Temp_Kc=new kc_b;
			Temp_Kc->kc=kct;
			Temp_Kc->TKC=TEMP_G->ptrkc;
			Temp_Kc->id_bet=id_bet;
			Temp_Kc->id_bet_name=id_bet_T;
			//if(id_bet_T) Temp_Kc->id_bet_name=id_bet_T;
			Temp_Kc->ng=TEMP_GT;
			Temp_Kc->next=NULL;

			if(bet_type && kct<0)
			{
				(*(TEMP_G->ptrkc->ptrk+1))=Temp_Kc;
				(*(TEMP_G->ptrkc->ptrk))=NULL;
				return true;
			}
			(*(TEMP_G->ptrkc->ptrk))=Temp_Kc;
			(*(TEMP_G->ptrkc->ptrk+1))=NULL;
			//return true;
		}

		}while(IJK);

	}
	else return false;
	GX_STATUS[2]=false;
	return true;
	//
	
}

sport* bet::GET_ACCESS()
{
	return &G;
}
//**************************************************************************//
void bet::v_all()
{
	///////////////////////////////////////////////interface
	vil=new int[2];
	*vil=0;
	if(IGA->Filter.v2)*vil=1;
	*(vil+1)=0;
	if(IGA->Filter.v3)*(vil+1)=2;
	////////////
	VilT=IGA->Filter.vt;
	///////////////////////////////////////////////
	//for(;;)
	{
		//cout<<"\nID_S: "<<G.id_s<<"	"<<get_sport_name(G.id_s,1)<<endl;
		for(cham* ch=G.ptrch;ch;ch=ch->next)
		{
			if(!ch->ptrm)continue;
			//cout<<"\nID_CH: "<<ch->id_ch<<"			"<<get_cham_name(ch->id_ch,G.id_s,1)<<endl;
			for(month* mo=ch->ptrm;mo;mo=mo->next)
			{
				if(!mo->ptrh)continue;
				//cout<<"(Y M D): "<<mo->y<<" "<<mo->m<<" "<<mo->day<<endl;
				for(hour* ho=mo->ptrh;ho;ho=ho->next)
				{
					//cout<<"\n[H M]: "<<ho->h<<" "<<ho->minute<<endl;
					int VTIME[5]={mo->y,mo->m,mo->day,ho->h,ho->minute};
					if(!GX_TIME_C((int*)VTIME,IGA->Filter.fr_h,IGA->Filter.to_h))continue;
					for(game* ga=ho->ptrg;ga;ga=ga->next)
					{
						if(!ga->ptrkc)continue;
						if(!ga->ptr_V)
						{
							ga->ptr_V=new V;
							ga->ptr_V->V2=NULL;
							ga->ptr_V->V3=NULL;
						}
						for(int i=0;i<2;i++)//[0]=1->v2, [1]=2->v3 ...
						{
							int NVG=0;//nuyn xaxi arbitrajneri qanak@
							switch (*(vil+i))
							{
							case 1: /*if(ga->ptr_V->V2)break;*/ ga->ptr_V->V2=vil2(ga->ptrkc);break;
							case 2: /*if(ga->ptr_V->V3)break;*/ ga->ptr_V->V3=vil3(ga->ptrkc);break;
							case 0: break;
							};
						}
						if(!(ga->ptr_V->V2) && !(ga->ptr_V->V3))continue;
						///////////////////////////////////////////////////////////////////////////////////////////////////
						sbor_GV* TempGV=NULL;
						//-------------------------------------------------------------------//
						if(!ga->ptr_V->V2 || !ga->ptr_V->V3)
						{
							if(ga->ptr_V->V2)
							{
								TempGV=new sbor_GV;
								TempGV->G_V2=ga->ptr_V->V2;
								TempGV->G_V3=NULL;
								TempGV->N3=0;
								TempGV->next=NULL;
								TempGV->N2=0;
								for(v2* tv2=TempGV->G_V2;tv2;tv2=tv2->next) (TempGV->N2)++;
							}
							else
							{
								TempGV=new sbor_GV;
								TempGV->G_V2=NULL;
								TempGV->G_V3=ga->ptr_V->V3;
								TempGV->N2=0;
								TempGV->next=NULL;
								TempGV->N3=0;
								for(v3* tv3=TempGV->G_V3;tv3;tv3=tv3->next) (TempGV->N3)++;
							}
						}
						//-------------------------------------------------------------------//
						else
						{
							v2* Tv2=ga->ptr_V->V2;
							v3* Tv3=ga->ptr_V->V3;
							TempGV=new sbor_GV;
							TempGV->G_V2=NULL;
							TempGV->G_V3=NULL;
							TempGV->N2=0;
							TempGV->N3=0;
							TempGV->next=NULL;
							for(sbor_GV* TT=NULL;;)
							{
								if(!TT)TT=TempGV;
								else
								{
									TT->next=new sbor_GV;
									TT=TT->next;
									TT->G_V2=NULL;
									TT->G_V3=NULL;
									TT->N2=0;
									TT->N3=0;
									TT->next=NULL;
									if(!Tv2 || !Tv3)
									{
										if(!Tv2)
										{
											TT->G_V3=Tv3;
											for(;Tv3;Tv3=Tv3->next) (TT->N3)++;
										}
										else
										{
											TT->G_V2=Tv2;
											for(;Tv2;Tv2=Tv2->next) (TT->N2)++;
										}
									}
								}
								for(int j=0; (Tv2->vt)>=(Tv3->vt) ;j++)
								{
									if(!j)TT->G_V2=Tv2;
									(TT->N2)++;
									Tv2=Tv2->next;
									if(!Tv2)break;
								}
								if(!Tv2)continue;
								for(int j=0; (Tv3->vt)>(Tv2->vt) ;j++)
								{
									if(!j)TT->G_V3=Tv3;
									(TT->N3)++;
									Tv3=Tv3->next;
									if(!Tv3)break;
								}
							}
						}
						//-------------------------------------------------------------------//
						if(V_ALL.GVALL)
						{
							sbor_ALL* Tm=new sbor_ALL;
							Tm->GVALL=TempGV;
							Tm->next=NULL;
							float Tvt=0.0;
							if(Tm->GVALL->G_V2)Tvt=Tm->GVALL->G_V2->vt;
							else Tvt=Tm->GVALL->G_V3->vt;

							for(sbor_ALL* TF=&V_ALL;;TF=TF->next)
							{
								if(TF->GVALL->G_V2)
								{
									if((TF->GVALL->G_V2->vt)<=Tvt)
									{
										Tm->next=TF->next;
										TF->next=Tm;
										sbor_GV* W=Tm->GVALL;
										Tm->GVALL=TF->GVALL;
										TF->GVALL=W;
										break;
									}
									
								}
								else
								{
									if((TF->GVALL->G_V3->vt)<=Tvt)
									{
										Tm->next=TF->next;
										TF->next=Tm;
										sbor_GV* W=Tm->GVALL;
										Tm->GVALL=TF->GVALL;
										TF->GVALL=W;
										break;
									}
								}
								if(!(TF->next))
								{
									TF->next=Tm;
									break;
								}
							}
						}
						else	V_ALL.GVALL=TempGV;
						
						///////////////////////////////////////////////////////////////////////////////////////////////////
					}
					
				}
				
			}
			
		}
	}
}
void bet::PVALL()
{
	for(sbor_ALL* t=&V_ALL;t;t=t->next)
	{
		col("\n-----------------------------------");
		int idb=t->GVALL->G_V2->KC1->id_bet;
		int ids=t->GVALL->G_V2->KC1->TKC->back_game->back_hour->back_month->back_cham->back_sport->id_s;
		int idch=t->GVALL->G_V2->KC1->TKC->back_game->back_hour->back_month->back_cham->id_ch;
		int idt1=t->GVALL->G_V2->KC1->TKC->back_game->id_t1;
		int idt2=t->GVALL->G_V2->KC1->TKC->back_game->id_t2;
		col("\n");col(get_sport_name(ids, idb));col("	");
		col(get_cham_name(idch,ids,idb));col("\n");
		col(get_team_name(idt1,idch,ids,idb));col(" - ");col(get_team_name(idt2,idch,ids,idb));col("\n");
		char bb[32];
		for(sbor_GV* tt=t->GVALL;tt;tt=tt->next)
		{
			if(tt->G_V2)
			{
				v2* TV2=tt->G_V2;
				for(int i=0;i<tt->N2;i++,TV2=TV2->next)
				{
					col("\nN: ");col(itoa(tt->N2,bb,10));col(" [");col(itoa((i+1),bb,10));col("] V%= ");sprintf(bb,"%f",TV2->vt);col(bb);col("\n");
					col(get_kc_NU(tt->G_V2->KC1->TKC->id_kc));col("	");sprintf(bb,"%f",tt->G_V2->KC1->kc);col(bb);col("\n");
					col(get_kc_NU(tt->G_V2->KC2->TKC->id_kc));col("	");sprintf(bb,"%f",tt->G_V2->KC2->kc);col(bb);col("\n");
				}
			}
			else
			{

			}
		}
	}
}

v2* bet::vil2(kcT* pkc)
{
	if(!pkc)return NULL;
	//ptr_KCV* temp=NULL;
	v2* Temp_v2=NULL;
	kcT** Temp=new kcT*[ID_KC_MAX];
	for(int i=0;i<ID_KC_MAX;i++) *(Temp+i)=NULL;
	//kcT** T=new kcT*;//Tempi het hamematelu hamar
	KCV* A_ID;//@ntacik
	kc_b* kc1;
	kc_b* kc2;
	float E,k1,k2,Bt1,Bt2,EV12;
	bool two,S1,S2;	
	for(kcT* t=pkc;t;t=t->next)
	{
		*(Temp+t->id_kc-1)=t;//@ntacik kci fix
		A_ID=v2_r_id(t->id_kc);
		for(;A_ID;A_ID=A_ID->next)
		{
			if(!(*(Temp+A_ID->ID_KC-1)))continue;//Hamapatasxan ID chka
			if(A_ID->LAY_MY){	if( !(kc1=(*(t->ptrk+1))) ) continue;}	
			else if( !(kc1=(*(t->ptrk))) ) continue;
			if(A_ID->LAY){		if( !(kc2=(*((*(Temp+A_ID->ID_KC-1))->ptrk+1))) ) continue;} 
			else if( !(kc2=(*((*(Temp+A_ID->ID_KC-1))->ptrk))) ) continue;
				
				for(kc_b* dkc1=kc1; dkc1; dkc1=dkc1->next)
				{
					k1=dkc1->kc;
					k2=kc2->kc;
					///////////////////////////////////////////////////////////
					if(A_ID->LAY_MY)	k1=-dkc1->kc/(-dkc1->kc-1);//LAY1->KC1
					if(A_ID->LAY)		k2=-kc2->kc/(-kc2->kc-1);//LAY2->Kc2
					///////////////////////////////////////////////////////////
					two=false;
					if(dkc1->id_bet_name==1 && kc2->id_bet_name==1)//BETFAIR_ID=1
					{
						bool *BE=Market_Bf_Kc(dkc1->TKC->id_kc,kc2->TKC->id_kc);
						if(BE)if(*BE && *(BE+1) )two=true;
					}
					S1=(IGA->Bets+dkc1->id_bet_name-1)->btp;
					Bt1=(IGA->Bets+dkc1->id_bet_name-1)->bt;
					S2=(IGA->Bets+kc2->id_bet_name-1)->btp;
					Bt2=(IGA->Bets+kc2->id_bet_name-1)->bt;
					if(S1 && !S2) k1=k1*(1+Bt1/100)-Bt1/100;//KC1<-B%
					if(!S1 && S2) k2=k2*(1+Bt2/100)-Bt2/100;//KC2<-B%
					if(S1 && S2 && !two)
					{
						k1=k1*(1+Bt1/100)-Bt1/100;//KC1<-B%
						k2=k2*(1+Bt2/100)-Bt2/100;//KC2<-B%
					}
					///////////////////////////////////////////////////////////
					EV12=0;
					if(!S1) EV12=k2*Bt1/100;
					if(!S2) EV12+=k1*Bt2/100;
					E= ((((k1*k2+EV12)/(k1+k2))-1)*100);
					if(two) if(E>0)E=E*(1+Bt1/100);
					if( VilT > E )break;
					if(two && E<0) break;
					for(kc_b* dkc2=kc2; dkc2; dkc2=dkc2->next)
					{
						k2=dkc2->kc;
						///////////////////////////////////////////////////////////
						if(A_ID->LAY)	k2=-dkc2->kc/(-dkc2->kc-1);//LAY2->Kc2
						if(!S1 && S2) k2=k2*(1+Bt2/100)-Bt2/100;//KC2<-B%
						///////////////////////////////////////////////////////////
						EV12=0;
						if(!S1) EV12=k2*Bt1/100;
						if(!S2) EV12+=k1*Bt2/100;
						E=((((k1*k2+EV12)/(k1+k2))-1)*100);
						if(two) if(E>0)E=E*(1+Bt1/100);
						if( VilT > E )break;
						v2* TV2=new v2;
						TV2->KC1=dkc1;
						TV2->KC2=dkc2;
						TV2->LAY1=A_ID->LAY_MY;
						TV2->LAY2=A_ID->LAY;
						TV2->vt=E;
						TV2->next=NULL;
						/////////////////////////////////////////////////////////////
						if(!Temp_v2)
						{
							Temp_v2=TV2;
							continue;
						}
						if(Temp_v2->vt<E)
						{
							TV2->next=Temp_v2;
							Temp_v2=TV2;
							continue;
						}
						for(v2* dv2=Temp_v2;;dv2=dv2->next)
						{
							if(!dv2->next)
							{
								dv2->next=TV2;
								break;
							}
							if(dv2->next->vt<E)
							{
								TV2->next=dv2->next;
								dv2->next=TV2;
								break;
							}
						}
						//////////////////////////////////////////////////////////////
					}
				}
		}
	}
	return  Temp_v2;
}
KCV* bet::v2_r_id(int ID)
{
	KCV* TEMP=NULL;
	KCV* t;
	int* idkc= &ID;
	int Tid;
	bool op=true;
	for(int i=0;*(idkc+i);i++)
	{
		/////////////////////////////////////////////ID_KC1-ID_KC2
		Tid=id1_id2((*(idkc+i)));
		if(Tid)
		{
			t=new KCV;
			t->ID_KC=Tid;
			t->LAY=false;
			t->LAY_MY=false;
			t->next=TEMP;
			TEMP=t;
		}
		/////////////////////////////////////////////ID_KC1-LID_KC2(LAY=true)
		t=new KCV;
		t->ID_KC=*(idkc+i);
		t->LAY=true;
		t->LAY_MY=false;
		t->next=TEMP;
		TEMP=t;	
		/////////////////////////////////////////////LID_KC-ID_KC2(LAY_MY=true)
		if(!op)
		{
			t=new KCV;
			t->ID_KC=*(idkc+i);
			t->LAY=false;
			t->LAY_MY=true;
			t->next=TEMP;
			TEMP=t;
		}
		/////////////////////////////////////////////ID->[==]->ID1, ID2, ...
		if(op)
		{
			idkc=idkl(ID);
			if(!idkc)break;
			op=false;
			i=-1;
			continue;
		}
		else continue;
	}
	return TEMP;
}

int bet::id1_id2(int ID1)
{
	const int NI=8;//NI-> N MI[]
	int MI[]={1,234, 271,280, 296,305, 345,404};//mijakayqer blok(2)
	int ME[]={307,334, 312,339};//E gandikap
	const int Ni=2;
	const int Nj=2;
	int M[Ni][Nj]=//anhatakan bacarutyunner nuyn tipi
	{
		{306, 309},
		{343, 342},
	};
	////////////////////////////////////////////
	for(int i=0;i<NI;i+=2)
	{
		if(MI[i]<=ID1 && MI[i+1]>=ID1)
		{
			if( (ID1-MI[i])%2 )	return (ID1-1);
			return (ID1+1);
		}
	}
	/////////////////////////////////////////////
	for(int i=0;i<=2;i+=2)
	{
		if(ME[i]<=ID1 && ME[i+1]>=ID1)
		{
			if( (ID1-ME[i])%3 )continue;
			if(i) return (ME[0]+(ID1-ME[i]));
			return (ME[2]+(ID1-ME[i]));
		}
	}
	/////////////////////////////////////////////
	for(int i=0;i<Ni;i++)
	{
		for(int j=0;j<Nj;j++)
		{
			if(M[i][j]==ID1)
			{
				if(i) return M[i-1][j];
				return M[i+1][j];
			}
		}
	}
	//////////////////////////////////////////////
	return 0;
}

int* bet::idkl(int IDF)
{
	const int  N=24;
	int Id[N][4]=
	{
		{1,158,342},//P1
		{4,155,306},//1X
		{3,156,343},//P2
		{2,157,309},//X2
		{7,196},//1T P1
		{10,193},//1T 1X
		{9,194},//1T P2
		{8,195},//1T X2
		{13,218},//2T P1
		{16,215},//2T 1X
		{15,216},//2T P2
		{14,217},//2T X2
		{143,324},//F1(+3.5)
		{144,319},//F2(-3.5)
		{145,327},//F2(+3.5)
		{146,322},//F1(-3.5)
		{147,318},//F1(+2.5)
		{148,313},//F2(-2.5)
		{149,321},//F2(+2.5)
		{150,316},//F1(-2.5)
		{151,312},//F1(+1.5)
		{152,307},//F2(-1.5)
		{153,315},//F2(+1.5)
		{154,310}//F1(-1.5)
	};
	for(int i=0;i<N;i++)
	{
		for(int j=0;Id[i][j];j++)
		{
			if(Id[i][j]==IDF)
			{
				int* temp=new int[3];
				for(int k=0,n=0;;k++,n++)
				{
					if(k==j)k++;
					if(!Id[i][k]) 
					{
						*(temp+n)=0; 
						return temp;
					}
					*(temp+n)=Id[i][k];
				}
			}
		}
	}
	return NULL;
}
//////////////////////////////////////////////////V3
v3* bet::vil3(kcT* pkc)
{
	return NULL;
}

bool* bet::Market_Bf_Kc(int ID_kc1,int ID_kc2,int ID_kc3)
{
	bool* B_status=new bool[3];
	*(B_status+0)=*(B_status+1)=*(B_status+2)=false;
	int IDKC[3];
	IDKC[0]=ID_kc1;
	IDKC[1]=ID_kc2;
	IDKC[2]=ID_kc3;
	static const int N_M[]={5,11,1,3};
	static const int M_KC[][4]=
	{
		{1,3,5},//P1-P2-X
		{2,4,6},//X2-1X-12
		{7,9,11},//1T P1-P2-X
		{13,15,17},//2T P1-P2-X
		{291,292,293},//Sleduyushi gol

	///////Mijakayq Qayl[2]///////////////////////
		{19,72},//M(0.5)-B(13)
		{73,98},//1T M(0.5)-B(6)
		{125,190},//F1(+4)-F1(0 & -0.5)
		{271,272},//1T&2T P1 - !P1
		{273,274},//1T&2T P1 - !P1
		{275,276},//P1 zab. - !P1 zab.
		{277,278},//P2 zab. - !P2 zab.
		{279,280},//CHET - !CHET
		{296,297},//Penal-!Penal
		{298,299},//Udal - !Udal
		{300,301},//OBZ - !OBZ

	///////Mijakayq Qayl[3]///////////////////////
		{306,344},//P1(+1)- X(0)

	///////Amboxj interval///////////////////////
		{235,251},//1-0 - L.D.SH.
		{252,260},//P1P1 - XX
		{261,270},//1T 0-0 - L.D.SH.
	};
	bool BS[3];
	BS[0]=BS[1]=BS[2]=false;
	int BS_I=0;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for(int I1=0;I1<N_M[0];I1++)
	{
		if( ID_kc1==M_KC[I1][0] || ID_kc1==M_KC[I1][1] || ID_kc1==M_KC[I1][2]){ BS[0]=true; BS_I++; }
		if( ID_kc2==M_KC[I1][0] || ID_kc2==M_KC[I1][1] || ID_kc2==M_KC[I1][2]){ BS[1]=true; BS_I++; }
		if( ID_kc3==M_KC[I1][0] || ID_kc3==M_KC[I1][1] || ID_kc3==M_KC[I1][2]){ BS[2]=true; BS_I++; }
		if(BS_I>1)
		{
			for(int j=0;j<3;j++) if(BS[j]) *(B_status+j)=BS[j];
			return B_status;
		}
		BS[0]=BS[1]=BS[2]=false; BS_I=0;
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for(int I2=N_M[0]; (I2-N_M[0])<N_M[1] ; I2++)
	{
		if(ID_kc1>=M_KC[I2][0] && ID_kc1<=M_KC[I2][1]){ BS[0]=true; BS_I++;}
		if(ID_kc2>=M_KC[I2][0] && ID_kc2<=M_KC[I2][1]){ BS[1]=true; BS_I++;}
		if(ID_kc3>=M_KC[I2][0] && ID_kc3<=M_KC[I2][1]){ BS[2]=true; BS_I++;}
		if(BS_I>1)
		{
			int posB[3];
			posB[0]=posB[1]=posB[2]=-1;
			if(BS_I==2)
			{
				int NJ[2];
				for(int j=0,q=0;j<3;j++){ if(BS[j]){NJ[q]=j; q++;} }
				posB[NJ[0]]=IDKC[NJ[0]]-M_KC[I2][0];
				posB[NJ[1]]=IDKC[NJ[1]]-M_KC[I2][0];
				int Cp=1;
				if(posB[NJ[0]]%2==1)Cp=-1;
				if(posB[NJ[0]]==posB[NJ[1]] || (posB[NJ[0]]+Cp)==posB[NJ[1]]) { *(B_status+NJ[0])=*(B_status+NJ[1])=true; return B_status; }
			}
			else
			{
				posB[0]=IDKC[0]-M_KC[I2][0];
				posB[1]=IDKC[1]-M_KC[I2][0];
				posB[2]=IDKC[2]-M_KC[I2][0];
				int Cp=1;
				if(posB[0]%2==1)Cp=-1;
				if(posB[0]==posB[1] || (posB[0]+Cp)==posB[1])
				{
					*(B_status+0)=*(B_status+1)=true;
					if(posB[0]==posB[2] || (posB[0]+Cp)==posB[2]) {*(B_status+2)=true; return B_status;}
					return B_status;
				}
				if(posB[0]==posB[2] || (posB[0]+Cp)==posB[2]){	*(B_status+0)=*(B_status+2)=true; return B_status;	}
				Cp=1;
				if(posB[1]%2==1)Cp=-1;
				if(posB[1]==posB[2] || (posB[1]+Cp)==posB[2]){	*(B_status+1)=*(B_status+2)=true; return B_status;	}
			}
			return NULL;
		}
		BS[0]=BS[1]=BS[2]=false; BS_I=0;
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for(int I3=N_M[0]+N_M[1]; (I3-N_M[0]-N_M[1])<N_M[2] ; I3++)
	{
		if(ID_kc1>=M_KC[I3][0] && ID_kc1<=M_KC[I3][1]){ BS[0]=true; BS_I++;}
		if(ID_kc2>=M_KC[I3][0] && ID_kc2<=M_KC[I3][1]){ BS[1]=true; BS_I++;}
		if(ID_kc3>=M_KC[I3][0] && ID_kc3<=M_KC[I3][1]){ BS[2]=true; BS_I++;}
		if(BS_I>1)
		{
			int posB[3];
			posB[0]=posB[1]=posB[2]=-1;
			if(BS_I==2)
			{
				int NJ[2];
				for(int j=0,q=0;j<3;j++){ if(BS[j]){NJ[q]=j; q++;} }
				posB[NJ[0]]=IDKC[NJ[0]]-M_KC[I3][0];
				posB[NJ[1]]=IDKC[NJ[1]]-M_KC[I3][0];
				int Cp1=1;
				int Cp2=2;
				if(posB[NJ[0]]%3==1){Cp1=-1;Cp2=1;}
				if(posB[NJ[0]]%3==2){Cp1=-2;Cp2=-1;}
				if(posB[NJ[0]]==posB[NJ[1]] || (posB[NJ[0]]+Cp1)==posB[NJ[1]] || (posB[NJ[0]]+Cp2)==posB[NJ[1]]) { *(B_status+NJ[0])=*(B_status+NJ[1])=true; return B_status; }
			}
			else
			{
				posB[0]=IDKC[0]-M_KC[I3][0];
				posB[1]=IDKC[1]-M_KC[I3][0];
				posB[2]=IDKC[2]-M_KC[I3][0];
				int Cp1=1;
				int Cp2=2;
				if(posB[0]%3==1){Cp1=-1;Cp2=1;}
				if(posB[0]%3==2){Cp1=-2;Cp2=-1;}
				if(posB[0]==posB[1] || (posB[0]+Cp1)==posB[1] || (posB[0]+Cp2)==posB[1])
				{
					*(B_status+0)=*(B_status+1)=true;
					if(posB[0]==posB[2] || (posB[0]+Cp1)==posB[2] || (posB[0]+Cp2)==posB[2]) {*(B_status+2)=true; return B_status;}
					return B_status;
				}
				if(posB[0]==posB[2] || (posB[0]+Cp1)==posB[2] || (posB[0]+Cp2)==posB[2]){	*(B_status+0)=*(B_status+2)=true; return B_status;	}
				Cp1=1;
				Cp2=2;
				if(posB[1]%3==1){Cp1=-1;Cp2=1;}
				if(posB[1]%3==2){Cp1=-2;Cp2=-1;}
				if(posB[1]==posB[2] || (posB[1]+Cp1)==posB[2] || (posB[1]+Cp2)==posB[2]){	*(B_status+1)=*(B_status+2)=true; return B_status;	}
			}
			return NULL;
		}
		BS[0]=BS[1]=BS[2]=false; BS_I=0;
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for(int I4=N_M[0]+N_M[1]+N_M[2]; (I4-N_M[0]-N_M[1]-N_M[2])<N_M[3] ; I4++)
	{
		if(ID_kc1>=M_KC[I4][0] && ID_kc1<=M_KC[I4][1]){ BS[0]=true; BS_I++;}
		if(ID_kc2>=M_KC[I4][0] && ID_kc2<=M_KC[I4][1]){ BS[1]=true; BS_I++;}
		if(ID_kc3>=M_KC[I4][0] && ID_kc3<=M_KC[I4][1]){ BS[2]=true; BS_I++;}
		if(BS_I>1)
		{
			for(int j=0;j<3;j++) if(BS[j]) *(B_status+j)=BS[j];
			return B_status;
		}
		BS[0]=BS[1]=BS[2]=false; BS_I=0;
	}
	return NULL;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
/////////////////////////////////////////////////////

int* bet::GET_GOAL(int ID_S, int ID_CH, int ID_T1, int ID_T2, int* DATA)
{
	if(!(BASE_GOAL+ID_S-1)->ID_CH) return NULL;
	for(GOAL_CH* TCH=(BASE_GOAL+ID_S-1); TCH; TCH=TCH->next)
	{
		if(TCH->ID_CH==ID_CH)
		{
			for(GOAL_G* TG=TCH->ptrGG; TG; TG=TG->next)
			{
				if( (TG->ID_T1==ID_T1 && TG->ID_T2==ID_T2) ||  (TG->ID_T1==ID_T2 && TG->ID_T2==ID_T1))
				{
					bool BG=true;
					if(DATA) for(int i=0; i<5; i++)if(*(TG->DATA+i) != *(DATA+i)) BG=false;
					if(BG)	return TG->GOAL; 
					else continue;
				}
			}
			return NULL;
		}
	}
	return NULL;
}

int bet::ConvertForaKcId(int ID_KC)
{
	int *Goal=GX_GOAL;
	if(!Goal) return ID_KC;
	if(*Goal == *(Goal+1)) return ID_KC;
	static const int Min1=125;
	static const int Max1=234;
	static const int Min2=367;
	static const int Max2=390;
	int juk=ID_KC;
	if((ID_KC>=Min1 && ID_KC<=Max1) || (ID_KC>=Min2 & ID_KC<=Max2))
	{
		int D=(*Goal)-(*(Goal+1));
		CForaC=false;
		string KcName=string(get_kc_NU(ID_KC));
		CForaC=true;
		unsigned int POS;
		unsigned int POSc;
		bool OneTwo=true;
		POS=KcName.find("F1");
		if(int(POS)==-1)
		{
			POS=KcName.find("F2");
			OneTwo=false;
			if(int(POS)==-1)
			{
				return 0;//ERORR......
			}
		}
		POS+=3;
		POSc=KcName.find(")");
		double total=atof((KcName.substr(POS,POSc-POS)).c_str());
		if(OneTwo) total-=D;
		else total+=D;
		string TotalS;
		sprintf((char*)TotalS.c_str(),"%g",total);
		KcName.replace(POS,POSc-POS,(char*)TotalS.c_str());
		/////////////////////////////////////////////////////////////
		int min,max;
		if(ID_KC>=Min1 && ID_KC<=Max1){ min=Min1; max=Max1; }
		else{ min=Min2; max=Max2; }
		for(int i=min;i<=max;i++)
		{
			CForaC=false;
			if( KcName==string(get_kc_NU(i)) ) 
			{
				CForaC=true;
				return i;
			}
			CForaC=true;
		}
		return 0;
	}
	int ijk=ID_KC;
	return ID_KC;
}