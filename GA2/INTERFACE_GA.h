#ifndef INTERFACE_GA_H
#define INTERFACE_GA_H

struct Ctrl_F
{
	bool v2;
	bool v3;
	float fr_h;
	float to_h;
	float vt;
	float usd;
	float rur;
};

struct Ctrl_Bets
{
	float bt;
	bool btp;
	bool l_xml;
	bool add_ch;
	bool add_t;
	bool add_kc;
	bool SF;
};


class Interface_Ga
{
private:
	char *f_name;//fayli anun@
public:
	int N_BET;//kantoraneri qanak@
	Ctrl_F Filter;
	Ctrl_Bets *Bets;
	Interface_Ga(int);
	void Save_Inf_Ga();
};
#endif