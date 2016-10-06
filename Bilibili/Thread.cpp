#include "stdafx.h"
#include <thread>
#include <vector>
#include "Live.h"
#include "Thread.h"
#include "Founctions.h"
#define MAX_USER 50
using namespace std;
extern vector <Live> l;
Founctions f2;
std::time_t result = std::time(nullptr);
bool lock;//���������߳������Ҫ����������ߴ�ӡ�Ļ����ȼ�������ȱ��˴����������ֵ��Լ�
bool isLocked = false;

std::thread liveHeart[MAX_USER];
std::thread refreshInfo[MAX_USER];
std::thread freeSilver[MAX_USER];

void thread_LiveHeart(Live &l)
{
	int code;
	while (1)
	{
		if (!isLocked)
			return;//���δ��������ô�˳������������е��߳�;
		while(lock){std::this_thread::sleep_for(std::chrono::milliseconds(100));}
		lock = true;
		code = l.Heart();
		if (code == 0)
		{
			cout << std::asctime(std::localtime(&result)) << " �û� " << l.GetUsername() << " ����һ��" << endl;
		}
		else if (code == -403)
		{
			cout << std::asctime(std::localtime(&result)) << " �û� " << l.GetUsername() << " �Ƿ�����" << endl;
		}
		else if (code == -101)
		{//���ȵ�¼
			cout << std::asctime(std::localtime(&result)) << " �û� " << l.GetUsername() << " ���ȵ�¼" << endl;
		}
		else
		{
			cout << std::asctime(std::localtime(&result)) << " �û� " << l.GetUsername() << " δ֪����" << endl;
		}
		lock = false;
		std::this_thread::sleep_for(std::chrono::minutes(5));//�߳����� 5 ���ӣ�
	}
}

void thread_RefreshInfo(Live &l)
{
	while (1)
	{
		if (!isLocked)
			return;//���δ��������ô�˳������������е��߳�;
		std::this_thread::sleep_for(std::chrono::hours(4));//�߳� 4 Сʱ��
		while (lock) { std::this_thread::sleep_for(std::chrono::milliseconds(100)); }
		lock = true;
		cout << std::asctime(std::localtime(&result)) << " �û� " << l.GetUsername() << " ˢ����Ϣ" << endl;
		l.FreshUserInfo();
		lock = false;
	}
}

void thread_FreeSilver(Live &l)
{
	int code, failedTimes = 0;
	while (1)
	{
		if (!isLocked)
			return;//���δ��������ô�˳������������е��߳�;
		while (lock) { std::this_thread::sleep_for(std::chrono::milliseconds(100)); }
		lock = true;
		code = l.FreeSilverGetCurrentTask(l.currentTask);
		lock = false;
		if (code == -101)
		{//���ȵ�¼
			break;
		}
		else if (code == 0)
		{
			while ((l.currentTask.time_end - (int)f2.GetTimeStamp()) > 0)//һֱ���ߵ����������Ϊֹ
			{
				std::this_thread::sleep_for(std::chrono::seconds(1));//�߳����� 1 ��
			}
			while (lock) { std::this_thread::sleep_for(std::chrono::milliseconds(100)); }
			lock = true;
			l.FreeSilverGet();
			lock = false;
			std::this_thread::sleep_for(std::chrono::seconds(5));
		}
		else if (code == -10017)
		{//����������������
			break;
		}
		else
		{
			failedTimes++;
			std::this_thread::sleep_for(std::chrono::minutes(5));//ʧ�ܣ� 5 ���Ӻ�����
			if (failedTimes == 5)
				break;
		}
	}
	cout << " �û� " << l.GetUsername() << " thread_FreeSilver�߳��˳�" << endl;
}
extern void setColor(const char* color);
void tmd_create()
{
	if (isLocked)
	{//��ֹ�ظ������̣߳����ҿ������̼߳���Լ��Ƿ���Դ��
		setColor("red");
		printf("can not create more thread!\n");
		setColor("white");
		printf("> ");
	}
	isLocked = true;
	for (unsigned int i = 0; i < l.size(); i++)
	{
		liveHeart[i] = thread(thread_LiveHeart, l[i]);
		refreshInfo[i] = thread(thread_RefreshInfo, l[i]);
		freeSilver[i] = thread(thread_FreeSilver, l[i]);
	}
	while (1)
	{
		string a;
		cin >> a;
		if (a.compare("!q"))//����ط���BUG�����ֹ��̣� [--debug !q !q <Enter> <Enter> --debug] δ��Ӧ
		{
			isLocked = false;//���������־�����Բ���ɱ���̣߳����߳��Լ��˳�
			lock = false;
			setColor("white");
			printf("\n\n> ");
			return;
		}
	}
}