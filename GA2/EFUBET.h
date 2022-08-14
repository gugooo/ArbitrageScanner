#ifndef EFUBET_H
#define EFUBET_H

#include "bet.h"
#include "stdafx.h"
#include "XmlFeed.h"

#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include "Poco/DateTime.h"
#include "Poco/Format.h"
#include "Poco/TextConverter.h"
#include "Poco/Windows1252Encoding.h"
#include "Poco/UTF8Encoding.h"
#include <Poco/Exception.h>

#include <iostream>
#include <string>
#include <sstream>
#include <list>

using Poco::format;
using Poco::DateTime;
using Poco::TextConverter;
using Poco::Windows1252Encoding;
using Poco::UTF8Encoding;
using namespace Poco::Net;
using namespace Poco;
using namespace std;

struct SGameBet //ODDS
{
	string m_betType;
	string m_odd;
};

struct SEventGame //Game
{
	string m_date;
	string m_id;
	string m_name;
	string m_value;
	list<SGameBet> m_gameBet;
};

struct SEvant//Championship
{
	string m_name;
	list<SEventGame> m_eventGames;
};

struct SEvents //Sport
{
	string m_category;
	string m_id;
	list<SEvant> m_event;
};


class EFUBET
{
public:
	EFUBET(bet*,XmlFeed*);
	void Download_Line(int ID_SPORT);
	bet* Ebet;

private:
	XmlFeed* XF;
	int ID_SPORT;
	list<SEvents> allEvents;//ALL SPORTS
	HTTPCookie sessionCookies;
	HTTPResponse::HTTPStatus crawleUrl(const string& url, string& retData, std::vector<HTTPCookie>& cookies);
	size_t getSnippet(const string& data, int startPos, string& snippet, const string& startStr, const string& startEndStr ="", const string& endStr = "<");
	void tripDateString(string& date);
	void formatDateString(string& date);
	void parseEventPage(const string& data);
	void getSessionInfo(std::vector<HTTPCookie>& cookies, HTTPCookie& session);
	void printFetchedData();
};

#endif