#include "stdafx.h"
#include <stdio.h>
#include "bili.h"

using namespace std;

int main(void)
{
	bili b;
	int a = b.Login("15552878163", "Kt!OW0n@");/*1 �����½ʧ�� -626 �û������� -627 ������� -105 �ո��������޷�ʹ�ô˵�¼��ʽ ���򷵻�δ֪���� */
	if (a == 0)
		printf("Login success!\n");
	bili::LiveInfo l;
	bili::SignInfo s;
	bili::LiveRoomInfo lr;
	//a = b.GetUserInfoLive(l);
	//cout << "GetUserInfo: " << a << endl;
	//a = b.GetSignInfo(s);
	//cout << "GetSignInfo: " << a << endl;
	a = b.GetLiveRoomInfo(lr);
	cout << "GetLiveRoomInfo: " << a << endl;
	system("pause");
	return 0;
}