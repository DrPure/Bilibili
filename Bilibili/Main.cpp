#include "stdafx.h"
#include <stdio.h>
#include "bili.h"
#include "Live.h"
#include "Picture.h"
#include "Founctions.h"
#include <vector>
using namespace std;
vector <Live> l;
Founctions f;
void setColor(const char* color)
{
	if (!strcmp(color, "white"))
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	else if (!strcmp(color, "green"))
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	else if (!strcmp(color, "yellow"))
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	else if (!strcmp(color, "pink"))
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	else if (!strcmp(color, "blue"))
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	else if (!strcmp(color, "red"))
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	else if (!strcmp(color, "yellow"))
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	else if (!strcmp(color, "pink"))
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	else if (!strcmp(color, "cyan"))
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);//������ɫ��û�������ɫ����Ϊԭɫ

}
void printHeader()
{
    system("cls");
	setColor("white");
    printf("\
 __   \n\
[__) * | * |_  * | *\n\
[__) | | | [_) | | |\n\
\n\
");

	printf("\
                   _     _              _   \n\
     /\\           (_)   | |            | |  \n\
    /  \\   ___ ___ _ ___| |_ __ _ _ __ | |_ \n\
   / /\\ \\ / __/ __| / __| __/ _` | '_ \\| __|\n\
  / ____ \\\\__ \\__ \\ \\__ \\ || (_| | | | | |_ \n\
 /_/    \\_\\___/___/_|___/\\__\\__,_|_| |_|\\__|\n\
		\n");
}
void printHelp()
{
    printHeader();
    printf("\n\
  > new <username> <password>  \t ���һ�����û�     \n\
  > del <username>  \t\t ɾ��һ���û�	\n\
  > login <username>  \t\t ʹ <username> ����\n\
  > login /all  \t\t ��½�����û� \n\
  > logout <username>	 \t ʹ <username> ����\n\
  > logout /all  \t\t ʹ�����û�����	\n\
  > list  \t\t\t �鿴�ѱ�����û�	\n\
  > info <username>  \t\t �鿴 <username> ����Ϣ	\n\
  > --debug  \t\t\t ���� Debug ģʽ	\n\
> ");

}
void newUser(string command)
{
	Live newLive;
    vector<string> result = f.split(command, " ");
    if (result.size() != 3)
    {
        printf("�����ʽ����ȷ��\n> ");
        return;
    }
	for (int i = 0; i < l.size(); i++)
	{//���أ���ʵ�� map<Live> Ҳ�а� ������
		if (l[i].GetUsername().compare(result[1]) == 0)
		{
			setColor("yellow");
			printf("�û� %s �Ѵ���\n", result[1].c_str());
			setColor("white");
			printf("> ");
			return;
		}
	}

    int ret = 0;
	
	ret = newLive.Login(result[1], result[2]);
    if (ret == 0)
    {
		setColor("green");
        printf("��½�ɹ�������ˢ���û���Ϣ\n");
        newLive.FreshUserInfo();
		l.push_back(newLive);
        printf("�û���Ϣˢ����ɣ�\n");
    }
    else
    {
		setColor("red");
        if (ret == -626)
            printf("��¼ʧ�ܣ��û�������\n");
        else if (ret == -627)
            printf("��¼ʧ�ܣ��������\n");
        else if (ret == -105)
            printf("��¼ʧ�ܣ����޸������벻������֤���½\n");
        else printf("��¼ʧ�ܣ�δ֪���� %d\n", ret);
    }
	setColor("white");
    printf("> ");
}
void loginUser(string command)
{
	bool flag = false;
	vector<string> result = f.split(command, " ");
	if (result.size() != 2)
	{
		printf("�����ʽ����ȷ��\n> ");
		return;
	}
	setColor("yellow");
	for (int i = 0; i < l.size(); i++)
	{
		if (result[1].compare("/all") == 0)
		{
			l[i].setLoginStatus(true);
			printf("�û� %s ������\n", l[i].GetUsername().c_str());
			flag = true;
		}
		if (l[i].GetUsername().compare(result[1]) == 0)
		{
			if (!l[i].getLoginStatus())
			{
				l[i].setLoginStatus(true);
				printf("�û� %s ������\n", result[1].c_str());
				flag = true;
				break;
			}
			else
			{
				printf("�û� %s ��������\n", result[1].c_str());
				flag = true;
				break;
			}
		}
	}
	if (!flag)
	{
		printf("�Ҳ����û� %s \n", result[1].c_str());
	}
	setColor("white");
	printf("> ");
}
void logoutUser(string command)
{
	bool flag = false;
	vector<string> result = f.split(command, " ");
	if (result.size() != 2)
	{
		printf("�����ʽ����ȷ��\n> ");
		return;
	}
	setColor("yellow");
	for (int i = 0; i < l.size(); i++)
	{
		if (result[1].compare("/all") == 0)
		{
			l[i].setLoginStatus(false);
			printf("�û� %s ������\n", l[i].GetUsername().c_str());
			flag = true;
		}
		else if (l[i].GetUsername().compare(result[1]) == 0)
		{
			if (l[i].getLoginStatus())
			{
				l[i].setLoginStatus(false);
				printf("�û� %s ������\n", result[1].c_str());
				flag = true;
				break;
			}
			else
			{
				printf("�û� %s δ����\n", result[1].c_str());
				flag = true;
				break;
			}
		}
	}
	if (!flag)
	{
		printf("�Ҳ����û� %s \n", result[1].c_str());
	}
	setColor("white");
	printf("> ");
}
void delUser(string command)
{
	//BUG�����http://blog.csdn.net/pecywang/article/details/8990795
	bool flag = false;
	Live temp;
	vector<string> result = f.split(command, " ");
	if (result.size() != 2)
	{
		printf("�����ʽ����ȷ��\n> ");
		return;
	}
	setColor("yellow");
	vector<Live>::iterator it;
	int index = 0;
	for (it = l.begin(); it != l.end(); )//ע������� erase �� it ��д��
	{
		if ((*it).GetUsername().compare(result[1]) == 0)
		{
			it = l.erase(it);
			printf("��ɾ���û� %s\n", result[1].c_str());
			flag = true;
		}
		else
		{
			++it;
		}
	}
	if (!flag)
	{
		printf("�Ҳ����û� %s \n", result[1].c_str());
	}
	setColor("white");
	printf("> ");
}
void userList()
{
    printf("%-20s%-20s%-20s\n", "�û���", "�ǳ�", "״̬");
    for (int i = 0; i < l.size(); i++)
    {
        string username, uname;
        username = l[i].GetUsername();
        uname = l[i].GetUname();
		setColor("cyan");
		printf("%-20s", username.c_str());
		setColor("pink");
        printf("%-20s", uname.c_str());
        if (l[i].getLoginStatus())
        {
			setColor("green");
            printf("%-20s\n", "�� Online");
			setColor("white");
        }
        else
        {
			setColor("default");
            printf("%-20s\n", "�� Offline");
        }
    }
	setColor("white");
    printf("\n> ");
}
void userInfo(string command)
{
	bool flag = false;
	vector<string> result = f.split(command, " ");
	if (result.size() != 2)
	{
		printf("�����ʽ����ȷ��\n> ");
		return;
	}
	for (int i = 0; i < l.size(); i++)
	{
		if (l[i].GetUsername().compare(result[1]) == 0)
		{
			printHeader();
			printf("�û� %s ����Ϣ:\n\n", result[1].c_str());
			setColor("white");
			printf("  �Ƿ���ү�û���");
			if (l[i].liveInfo.vip == 1)
			{
				setColor("green");
				printf("��");
			}
			else
			{
				setColor("yellow");
				printf("��");
			}
			setColor("default");
			printf("   Ӳ�ң�%.1f  B������%d\n", l[i].avInfo.coins, l[i].avInfo.bCoins);
			printf("  �ɾ�ֵ��");
			setColor("cyan");
			printf("%d", l[i].liveInfo.achieve);
			setColor("white");
			printf("  �����ӣ�%d ����ӣ� ", l[i].liveInfo.achieve, l[i].liveInfo.silver);
			setColor("yellow");
			printf("%d\n", l[i].liveInfo.gold);
			setColor("cyan");
			printf("  ��վ�ȼ���%d (%d / %d) \n   ����������%d\n", l[i].avInfo.current_level, l[i].avInfo.next_exp, 
				l[i].avInfo.next_exp - l[i].avInfo.current_exp);
			setColor("pink");
			printf("  ֱ��վ�ȼ���%d (%d / %d) \n   ����������%d\n", l[i].liveInfo.user_level, 
				l[i].liveInfo.user_next_intimacy, l[i].liveInfo.user_next_intimacy, l[i].liveInfo.user_next_intimacy - l[i].liveInfo.user_intimacy);
			setColor("green");
			printf("  �����ȼ���%d (%d / %d) \n   ����������%d\n", l[i].liveRoomInfo.level, 
				l[i].liveRoomInfo.currentExp, l[i].liveRoomInfo.allExp, l[i].liveRoomInfo.allExp - l[i].liveRoomInfo.currentExp);
			flag = true;
		}
	}
	setColor("yellow");
	if (!flag)
		printf("�Ҳ����û� %s\n", result[1].c_str());
	setColor("white");
	printf("> ");
}
int main(void)
{
	
    /*1 �����½ʧ�� -626 �û������� -627 ������� -105 �ո��������޷�ʹ�ô˵�¼��ʽ ���򷵻�δ֪���� */
    /*Live l;
    Live::LiveInfo li;
    Live::SignInfo si;
    Live::LiveRoomInfo lr;
    l.Login("15552878163", "Kt!OW0n@");
    cout << l.FreshUserInfo() << endl;*/
    //cout << l.DoSign() << endl;
    //cout << l.GetUserID() << endl;
    //cout << l.GetToken() << endl;
	setColor("white");
    printHeader();
    printf("\n��ӭʹ�� Bilibili ����\n���� /help �鿴����\n> ");
    string command;
    while (1)
    {
        getline(cin, command);
        if (!command.compare("exit"))
        {
            return 0;
        }
        else if (!command.compare("/h"))
        {
            printHelp();
        }
        else if (!command.compare("/help"))
        {
            printHelp();
        }
        else if (!command.compare("-h"))
        {
            printHelp();
        }
        else if (!command.compare("h"))
        {
            printHelp();
        }
        else if (!strcmp(command.substr(0, 3).c_str(), "new"))
        {
            newUser(command);
        }
		else if (!strcmp(command.substr(0, 6).c_str(), "logout"))
		{
			logoutUser(command);
		}
		else if (!strcmp(command.substr(0, 5).c_str(), "login"))
		{
			loginUser(command);
		}
		else if (!strcmp(command.substr(0, 3).c_str(), "del"))
		{
			delUser(command);
		}
		else if (!strcmp(command.substr(0, 4).c_str(), "info"))
		{
			userInfo(command);
		}
        else if (!command.compare("list"))
        {
            userList();
        }
        else if (!command.compare("l"))
        {
            userList();
        }
		else if (!command.compare("\n"))
		{
			printf("> ");
		}
        else { printf("δ֪���� ���� /help �鿴����\n> "); }
    }
    
    
    system("pause");
    return 0;
}