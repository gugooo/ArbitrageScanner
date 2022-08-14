#include "stdafx.h"
#include "BETFAIR.h"

#include <iostream>
#include <fstream>

char* BETFAIR::GetBetfair(int PO)//0- online, 1- ofline, 2- ofline and online
{
	/////////////////////////////////////
	const unsigned int SizeB=50000000;
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	HANDLE hRead, hWrite;
	CreatePipe(&hRead, &hWrite, &sa, SizeB*sizeof(char));
	//////////////////////////////////////
	STARTUPINFO sti={sizeof(sti)};
	ZeroMemory(&sti,sizeof(STARTUPINFO));
	sti.cb=sizeof(sti);
	sti.dwFlags=STARTF_USESTDHANDLES;
	sti.hStdOutput=hWrite;//GetStdHandle(STD_OUTPUT_HANDLE);
	sti.hStdInput=hRead;//GetStdHandle(STD_OUTPUT_HANDLE);
	/////////////////////////////////////////////////////////
	PROCESS_INFORMATION pi;
	TCHAR szComrnandLine[] =TEXT("node C:\\Betfair\\GA\\BETFAIR_2.js");
	LPCWSTR asd=TEXT("C:\\Program Files (x86)\\nodejs\\node.exe");
	bool q=CreateProcess(asd,szComrnandLine,NULL,NULL,true,REALTIME_PRIORITY_CLASS,NULL,NULL,&sti,&pi);
	WaitForSingleObject( pi.hProcess, INFINITE );
	DWORD n;
	CloseHandle(hWrite);
	/////////////////////////////
	static char* _BA=NULL;
	if(_BA!=NULL) delete [] _BA;
	////////////////////////////
	char *BA=new char[SizeB];
	_BA=BA;
	ReadFile(hRead,BA,SizeB*sizeof(char),&n,0);
	if(n<SizeB)
	{
		*(BA+n)='\0';
		//cout<<"OK";
		return BA;
	}
	//cout<<"ERROR";
	return NULL;
}

B_Line *BETFAIR::GBLine(char* CHL)
{
	//cout<<"\nFiltring the line...";
	if(*CHL=='\0') return NULL;
	B_Line *TGame=NULL;
	/////////////////////////////////////////////////////////////
	char *TP=CHL;
	int Ni=0;
	for(;*(CHL+Ni)!='\n';Ni++);
	*(CHL+Ni)='\0';
	int N_BN=atoi((const char*)CHL);
	BMarket **TM=new BMarket*[N_BN];
	int t;
	bool ONE=true;
	for(int i=Ni+1;*(CHL+i)!='@' && *(CHL+i)!='\0';i++)
	{
		if(*(CHL+i)=='*' && ONE)
		{
			B_Line* TBL=new B_Line;
			/////////////////////////////PATCH
			TBL->PatchGame=(CHL+(++i));
			for(;*(CHL+i)!='\n';i++);
			*(CHL+i)='\0';
			/////////////////////////////DATA
			TBL->DateOfGame=(CHL+(++i));
			for(;*(CHL+i)!='\n';i++);
			*(CHL+i)='\0';

			TBL->ptr_BMarket=NULL;
			TBL->next=TGame;
			TGame=TBL;
			for(;*(CHL+i+1)=='$';)
			{
				for(t=0;*(CHL+i+1+t)!=' ';t++);
				*(CHL+i+1+t)='\0';
				BMarket* Tm=new BMarket;
				Tm->MName=(CHL+i+t+2);
				Tm->ptr_BOdds=NULL;
				Tm->next=TBL->ptr_BMarket;
				TBL->ptr_BMarket=Tm;

				Tm->ID=atoi( (const char*)(CHL+i+2));

				*(TM+atoi( (const char*)(CHL+i+2) ))=Tm;
				for(i+=t+2;*(CHL+i)!='\n';i++);
			}
			//continue;
		}
		if(*(CHL+i)=='#')
		{
			ONE=false;
			for(t=1;*(CHL+i+t)!='\n';t++);
			*(CHL+i+t)='\0';
			int X=++i;
			i+=t-1;
			char op=*(CHL+i+1);
			char op1=*(CHL+i+1+1);
			char op2=*(CHL+i+1-1);
			for(;*(CHL+i+1)=='$';)
			{
				BOdds *To=new BOdds;
				/////////////////////////////KC_NAME
				To->KC_name=(CHL+(++i)+1);
				for(++i;*(CHL+i)!='|';i++);
				for(t=1;*(CHL+i+t)!=' ';t++);
				*(CHL+i+t)='\0';
				To->Back=atof( (const char*)(CHL+(++i)) );
				i+=t;
				for(t=1;*(CHL+i+t)!='\n';t++);
				*(CHL+i+t)='\0';
				To->Lay=atof((const char*)(CHL+i));
				i+=t;
				int N_X=atoi((const char*)(CHL+X));
				To->next=(*(TM+N_X))->ptr_BOdds;
				(*(TM+N_X))->ptr_BOdds=To;

			}
			//continue;
		}
	}
	/////////////////////////////////////////////////////////////
	return TGame;
}

B_Line *BETFAIR::StartL(int PO)
{
	if(PO<0 && PO>3) return NULL;
	return GBLine(GetBetfair(PO));
}