#pragma once
#ifndef BETFAIR_H
#define BETFAIR_H


#include "windows.h"
#include <iostream>
using namespace std;

struct BOdds
{
	char* KC_name;	//minchev '|'
	float Back;
	float Lay;
	BOdds* next;
};

struct BMarket
{
	int ID;
	char* MName;	//michev '\n'
	BOdds* ptr_BOdds;
	BMarket* next;
};

struct B_Line
{
	char* PatchGame;	//michev '\0'
	char* DateOfGame;	//michev '\0'
	BMarket* ptr_BMarket;
	B_Line* next;
};

class BETFAIR
{
private:
	char* GetBetfair(int OnlineOffline);//0- online, 1- ofline, 2- ofline and online
	B_Line* GBLine(char*);
public:
	B_Line* StartL(int PO=2);//0- online, 1- ofline, 2- ofline and online
};

#endif