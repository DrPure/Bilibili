#pragma once
#include <string>
#include "Founctions.h"
#include "rapidjson\document.h"
#include <fstream>  
#include <streambuf>  
using namespace std;


class bili
{
public:
	struct AVInfo
	{
		int current_level;
		int current_min;
		int current_exp;
		int next_exp;
		int bCoins;
		double coins;
		string face;
		string sex;
		string nameplate_current;
		string uname;
		int official_verify;
	}avInfo;
	struct LiveInfo
	{
		string uname;
		string face;
		int silver;
		int gold;
		int achieve;
		int vip;
		int svip;
		int user_level;
		int user_next_level;
		int user_intimacy;
		int user_next_intimacy;
		string user_level_rank;
		int billCoin;
	}liveInfo;
	struct SignInfo
	{
		string text;	/* ǩ������ */
		int status;		/* �Ƿ���ǩ�� */
		string allDays;	/* �������� */
		string curMonth;/* ��ǰ�·� */
		int hadSignDays;/* �Ѿ�ǩ������ */
		int newTask;
	}signInfo;
	struct LiveRoomInfo
	{
		int masterID;	/* ����ID��RUID�� */
		int roomID;		/* ����ID */
		int level;		/* ��ǰ�ȼ� */
		int currentExp;	/* ��ǰ����ֵ */
		int allExp;		/* �ܹ���Ҫ�ľ���ֵ */
	}liveRoomInfo;
	struct FreeSilverTask
	{
		int minute;
		int silver;
		int time_start;
		int time_end;
	}currentTask;
	
	int Login(const string username, const string password);
	int GetUserInfoLive(LiveInfo &l);
	int GetSignInfo(SignInfo &s);
	int GetLiveRoomInfo(LiveRoomInfo &lr);
	bili();
	~bili();
	
private:
	string CheckLogin();
	int GetMasterID(int liveRoomID);//Get RUID
	string cookieFile;
	string cacheFile;
	string uname;
	Founctions f;
	
};