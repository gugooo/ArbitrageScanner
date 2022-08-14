#include "stdafx.h"
#include "INTERFACE_GA.h"
#include <fstream>

using namespace std;
Interface_Ga::Interface_Ga(int N_B)
{
	f_name="SAVE_GA.GA";
	N_BET=N_B;
	Bets=new Ctrl_Bets[N_BET];
	ifstream read_GA(f_name,ios::binary);
	bool NO_FILE=read_GA;
	if(!NO_FILE)
	{
		ofstream write_GA(f_name,ios::binary);
	}
	else
	{
		int I=sizeof(this);
		int J=sizeof(Ctrl_Bets)+I;
		read_GA.read(reinterpret_cast<char*>(&(this->Filter)),sizeof(this->Filter));
		for(int i=0;i<N_BET;i++)
		{
			read_GA.read(reinterpret_cast<char*>((this->Bets+i)),sizeof(Ctrl_Bets));
		}
	}
}

void Interface_Ga::Save_Inf_Ga()
{
	ofstream write_GA(f_name,ios::binary);
	write_GA.write(reinterpret_cast<char*>(&(this->Filter)),sizeof(this->Filter));
	for(int i=0;i<N_BET;i++)
	{
		write_GA.write(reinterpret_cast<char*>((this->Bets+i)),sizeof(Ctrl_Bets));
	}

}