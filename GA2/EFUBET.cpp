#include "stdafx.h"
#include "EFUBET.h"


EFUBET::EFUBET(bet* CBet, XmlFeed* XFTH)
{
	Ebet=CBet;
	XF=XFTH;
}

void EFUBET::Download_Line(int ID_SP)
{
	if(!Ebet->set_GX_ID(ID_SP))return;
	ID_SPORT=ID_SP;
	std::string uri("http://www.efubet.com/Eurofootball/EN/Default.aspx");
	std::string pageData;
	std::vector<HTTPCookie> cookies;
	try 
	{
		std::vector<HTTPCookie>::iterator it;
		if (crawleUrl(uri, pageData, cookies) == HTTPResponse::HTTP_OK) 
		{
			getSessionInfo(cookies, sessionCookies);
		}
		uri = "http://www.efubet.com/Eurofootball/EN/Bets/GameFilter.aspx";
		crawleUrl(uri, pageData, cookies);
		uri = "http://www.efubet.com/Eurofootball/EN/Bets/Games.aspx";
		HTTPCookie sportIdsForBet;
		sportIdsForBet.setName("Eurofootball_SportIdsForBet");
		sportIdsForBet.setValue("20, 1");
		cookies.push_back(sessionCookies);
		cookies.push_back(sportIdsForBet);
		crawleUrl(uri, pageData, cookies);
		parseEventPage(pageData);
		//printFetchedData();
	} 
	catch (const Poco::Exception& ex) 
	{
		cerr << ex.displayText() << endl;
	}
}
HTTPResponse::HTTPStatus EFUBET::crawleUrl(const string& url, string& retData, std::vector<HTTPCookie>& cookies) 
{
	HTTPResponse res;
	try {
		URI uri(url);
		HTTPClientSession session(uri.getHost(), uri.getPort());
		string path(uri.getPathAndQuery());
		if (path.empty()) {
			path = "/";
		}
		HTTPRequest req(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
		req.set("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
		req.set("Accept-Language", "en-US,en;q=0.5");
		req.set("Connection", "keep-alive");
		req.set("Host", "www.efubet.com");
		req.set("Referer", "http://www.efubet.com/Eurofootball/RU/SysMenu.aspx");
		req.set("User-Agent", "Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:18.0) Gecko/20100101 Firefox/18.0");
		NameValueCollection inCookies;
		inCookies.add("Eurofootball_Lang", "EN");
		if (!cookies.empty()) 
		{
			std::vector<HTTPCookie>::iterator it = cookies.begin();
			for (; it < cookies.end(); ++it) 
			{
				inCookies.add( (*it).getName(), (*it).getValue() );
			}
		}
		req.setCookies(inCookies);
		session.sendRequest(req);
		istream &is = session.receiveResponse(res);
		cookies.clear();
		res.getCookies(cookies);
		stringstream buf;
		StreamCopier::copyStream(is, buf);
		retData = buf.str();
	} 
	catch (Poco::Exception &ex) 
	{
		cerr << ex.displayText() << endl;
		throw;
	}
	return res.getStatus();
}

size_t EFUBET::getSnippet(const string& data, int startPos, string& snippet, const string& startStr, const string& startEndStr, const string& endStr) 
{
	size_t posCaptionBegin = data.find(startStr, startPos);
	if (posCaptionBegin == string::npos) {
		return string::npos;
	}
	if (startEndStr.length() > 0) {
		posCaptionBegin = data.find(startEndStr, posCaptionBegin + 1);
		if (posCaptionBegin == string::npos) {
			return string::npos;
		}
		posCaptionBegin += startEndStr.size() - 1;
	} else {
		posCaptionBegin += startStr.size() - 1;
	}
	posCaptionBegin++;
	size_t posCaptionEnd = data.find(endStr, posCaptionBegin);
	if (posCaptionEnd == string::npos) {
		return string::npos;
	}
	string caption = data.substr(posCaptionBegin, posCaptionEnd - posCaptionBegin);
	posCaptionEnd++;
	snippet = caption;
	return posCaptionEnd;
}

void EFUBET::tripDateString(string& date) 
{
	size_t extraBegin = date.find("<img src=", 0);
	if (extraBegin != string::npos) {
		date = date.substr(0, extraBegin);
	}
}

void EFUBET::formatDateString(string& date) 
{
	if (date.empty()) {
		return;
	}
	Poco::DateTime now;
	string tmp(date);
	date = format("%d/%s", now.year(), tmp);
}

void EFUBET::parseEventPage(const string& data) 
{
	size_t pos = 0;
	string sportIds;
	int *Goal=NULL;
	///////////////////
	int CBD[5];//TIME
	float KC;
	char** KC_NAME=new char*[2];
	*(KC_NAME+1)=NULL;
	string T1;
	string T2;
	size_t gpos;
	size_t gpos2;
	//////////////////
	while (pos != string::npos) 
	{
		SEvents evs;
		pos = getSnippet(data, pos, evs.m_category, "<div class=\"SportForBet\"", ">", "<");
		pos = getSnippet(data, pos, evs.m_id, "<span id=\"Sport", "", "\">");
		////////////////////////////////////////////////////////////////////////////////////
		switch(ID_SPORT)
		{
		case 1: if(evs.m_category == "SOCCER") break;//SOCCER
			continue;
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
		////////////////////////////////////////////////////////////////////////////////////
		while (pos != string::npos) 
		{
			SEvant ev;
			pos = getSnippet(data, pos, ev.m_name, "<table border=0 cellspacing=0 cellpadding=0 width=\"100%\">","<td>", "</td>");
			////////////////////////CHAMPIONSHIP/////////////////////////////////
			///if( Ebet->set_GX_CHAM( (char*)ev.m_name.c_str(),'\0' ) ) {
			bool GCH[2];
		//	GCH[0]=Ebet->set_GX_CHAM( (char*)ev.m_name.c_str(),'\0' );
		//	XF->BI_CHAM(Ebet->id_ch_onl, (char*)ev.m_name.c_str());
			///////////////////////////////////////////////////////////////
			while (pos != string::npos) 
			{
				SEventGame eg;
				size_t prewPos = pos;
				pos = getSnippet(data, pos, eg.m_date, "<tr id=\"Row", "<td width=\"88px\" nowrap align=\"left\">",	"</td>");
				tripDateString(eg.m_date);
				formatDateString(eg.m_date);
				pos = getSnippet(data, prewPos, eg.m_id, "onclick=\"ShowBetTypes(", "", ")\" onmouseover=\"DoMouse(");
				pos = getSnippet(data, pos, eg.m_name, "<td align=\"left\">", "", "</td>");
				pos = getSnippet(data, pos, eg.m_value, "<td width=\"50px\" align=right>", "", "</td>");
				////////////////////////////T1-T2|TIME//////////////////////////////////////////////////
				gpos=eg.m_name.find("&nbsp;&nbsp;&mdash;&nbsp;");
				gpos2=eg.m_name.find("&nbsp;",gpos+25);
				T1=eg.m_name.substr(0,gpos);
				T2=eg.m_name.substr(gpos+25,gpos2-(gpos+25));
				CBD[0]=atoi( (eg.m_date.substr(0,4)).c_str() );//YEAR
				CBD[1]=atoi( (eg.m_date.substr(5,2)).c_str() );//MONTH
				CBD[2]=atoi( (eg.m_date.substr(8,2)).c_str() );//DAY
				CBD[3]=atoi( (eg.m_date.substr(11,2)).c_str() );//HOUR
				CBD[4]=atoi( (eg.m_date.substr(14,2)).c_str() );//MINUTE
				string pm=eg.m_date.substr(17);
				if(pm=="PM") CBD[3]+=12;
				if( Ebet->GX_TIME_C((int*) CBD, Ebet->IGA->Filter.fr_h, Ebet->IGA->Filter.to_h) ){
				GCH[0]=Ebet->set_GX_CHAM( (char*)ev.m_name.c_str(),'\0' );
				XF->BI_CHAM(Ebet->id_ch_onl, (char*)ev.m_name.c_str());
				GCH[1]=Ebet->set_GX_GAME((char*)T1.c_str(),'\0',(char*)T2.c_str(),'\0',CBD,Goal);
				XF->BI_GAME(Ebet->id_t1_onl,(char*)T1.c_str(),Ebet->id_t2_onl,(char*)T2.c_str(),(int*)CBD);
				if( GCH[0] && GCH[1] ){
				//////////////////////////////////////////////////////////////////////////////////////////
				std::string uri("http://www.efubet.com/Eurofootball/EN/Bets/BetTypesForBet.aspx?GameId=" + eg.m_id);
				//cout << "Fetching: "<< "http://www.efubet.com/Eurofootball/EN/Bets/BetTypesForBet.aspx?GameId=" + eg.m_id << endl;
				std::vector<HTTPCookie> cookies;
				HTTPCookie sportIdsForBet;
				sportIdsForBet.setName("Eurofootball_SportIdsForBet");
				if (sportIds.empty()) 
				{
					sportIds.append(evs.m_id);
				} 
				else 
				{
					sportIds.append(", " + evs.m_id);
				}
				sportIdsForBet.setValue(sportIds);
				cookies.push_back(sessionCookies);
				cookies.push_back(sportIdsForBet);
				string pageData;
				crawleUrl(uri, pageData, cookies);
				size_t bPos = 0;
				string sportIds;
				while (bPos != string::npos) 
				{
					SGameBet gb;
					bPos = getSnippet(pageData, bPos, gb.m_betType, "<td style=\"padding-left:2px\">", "", "</td>");
					bPos = getSnippet(pageData, bPos, gb.m_odd, "<td style=\"padding-right:2px\" align=\"right\">", "","</td>");
					size_t pkc1=gb.m_betType.find("&nbsp;");
					string TKc;
					if(pkc1!=string::npos)
					{
						string Tkc1=gb.m_betType.substr(0,pkc1);
						string Tkc2=gb.m_betType.substr(pkc1+6);
						TKc=Tkc1+Tkc2;
						*KC_NAME=(char*)(TKc.c_str());
					}
					else *KC_NAME=(char*)gb.m_betType.c_str();

					KC=atof( gb.m_odd.c_str() );
					if( (int)KC < 1)continue;
					bool KCBOOL=Ebet->set_GX_KC(KC_NAME,'\0',KC);
					KCBOOL;
					//eg.m_gameBet.push_back(gb);
				}
				Sleep(1);
				//ev.m_eventGames.push_back(eg);
			}
			}
				size_t posG=data.find("<tr id=\"Row", pos);
				size_t posCH=data.find("<table border=0 cellspacing=0 cellpadding=0 width=\"100%\">", pos);
				if(posCH<posG)break;

			}
			//evs.m_event.push_back(ev);
		///}
			size_t posCH=data.find("<table border=0 cellspacing=0 cellpadding=0 width=\"100%\">", pos);
			size_t posSP=data.find("<div class=\"SportForBet\"", pos);
			if(posSP<posCH)break;
		}
		//allEvents.push_back(evs);
	}
	//cout<<"OK"<<endl;
}

void EFUBET::getSessionInfo(std::vector<HTTPCookie>& cookies, HTTPCookie& session) 
{
	std::vector<HTTPCookie>::iterator it;
	bool done = false;
	for (it = cookies.begin(); it != cookies.end(); ++it) {
		if ((*it).getName().compare("ASP.NET_SessionId") == 0) {
			session.setName((*it).getName());
			session.setValue((*it).getValue());
			done = true;
			break;
		}
	}
	if (!done) {
		throw(Poco::Exception("Unable to get session information"));
	}
}

void EFUBET::printFetchedData() 
{
	cout << "Category" << "\t" << "Event" << "\t" << "Date" << "\t" << "Name" << "\t" << "Score" << "\t" << "Type"
			<< "\t" << "Odd" << "\t" << endl;
	list<SEvents>::iterator itSEvents;
	for (itSEvents = allEvents.begin(); itSEvents != allEvents.end(); ++itSEvents)
	{
		list<SEvant> Event = (*itSEvents).m_event;
		list<SEvant>::iterator itSEvant;
		for (itSEvant = Event.begin(); itSEvant != Event.end(); ++itSEvant)
		{
			list<SEventGame> eventGames = (*itSEvant).m_eventGames;
			list<SEventGame>::iterator itSEventGame;
			for (itSEventGame = eventGames.begin(); itSEventGame != eventGames.end(); ++itSEventGame) 
			{
				list<SGameBet> gameBet = (*itSEventGame).m_gameBet;
				list<SGameBet>::iterator itSGameBet;
				for (itSGameBet = gameBet.begin(); itSGameBet != gameBet.end(); ++itSGameBet) 
				{
					cout << (*itSEvents).m_category << "\t" << (*itSEvant).m_name << "\t" << (*itSEventGame).m_date
							<< "\t" << (*itSEventGame).m_name << "\t" << (*itSEventGame).m_value << "\t"
							<< (*itSGameBet).m_betType << "\t" << (*itSGameBet).m_odd << "\t" << endl;
				}
			}
		}
	}
}