#pragma once
#include <string>
#include "Founctions.h"
#include "rapidjson\document.h"
#include <fstream>  
#include <streambuf>  
using namespace std;
/* �����������ȡ Cookies ����Ϣ */
/* ���� Live �������������ɾ�������ļ� */
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
	struct GiftBag
	{
		int id;
		int uid;
		int giftID;
		int giftNum;
		int expireat;

	}giftBag;
	int Login(const string username, const string password);
	int FreshUserInfo();
	int ExchangeSilver2Coin();
	int GetUserID();
	bool getLoginStatus() { return isLogin_; };
	void setLoginStatus(bool status) { isLogin_ = status; };
	wstring GetUserNameByUID(int UID);
	string GetUsername()const { return username_; };
	string GetNickname()const { return uname; };
	string GetCaptchaFilePath()const { return captchaFile; };
	bili() { isLogin_ = false; };
	~bili() {};
protected:
	int GetMasterID(int liveRoomID);//Get RUID
	string uname;
	string username_;
	string captchaFile;
	bool isLogin_;
	string CheckLogin();
	string cookieFile;
	string cacheFile;
	Founctions f;
private:

	int GetUserInfoLive(LiveInfo &l);
	int GetUserInfoAV(AVInfo &a);
	int GetSignInfo(SignInfo &s);
	int GetLiveRoomInfo(LiveRoomInfo &lr);
	
};