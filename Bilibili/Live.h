#pragma once
#include "bili.h"
#include "Founctions.h"
#include "stdafx.h"
class Live : public bili
{
public:
	int DoSign();
	int FreeSilverGetCurrentTask(bili::FreeSilverTask &currentTask);
	int FreeSilverGet();
	int Heart();
	int SendGift(int giftID, int roomID, int num, bool coinType, int bagID);
	int FreeSilverGetCaptcha();
	string GetToken();
	Live()
	{
		//cout << "bilibili �������ˣ�" << endl;
	};
	~Live()
		/*������������coutȡ��ע�ͣ�����new <username> <password> �ᷢ�ֹ��캯����û�б�ִ�У����� del <username> ��ʱ��*/
		/* �ᷢ�� ���캯������������һ��ִ���� */
		/* ��Ҳ��֪������ʲôħ��... */
		/* �ƺ���������Ҳûɶ����.... */
	{
		//cout << "bilibili ���٣�" << endl;

		//remove(cookieFile.c_str());
		//remove(cacheFile.c_str());
	};
private:
	int FreeSilverHeart();
	
	
};

