#include<iostream>
using namespace std;
#include"speechManager.h"
#include"speaker.h";

int main()
{
	srand((unsigned)time(NULL));
	SpeechManager sm;

	/*for (auto it = sm.m_Speaker.begin();it != sm.m_Speaker.end();it++)
	{
		cout << "选手：" << it->second.m_name << endl;
		cout << "一轮分数：" << it->second.m_Score[0] << endl;
		cout << "二轮分数：" << it->second.m_Score[1] << endl;
		cout << endl;
	}*/

	int choice = 0;//记录用户选项

	while (true)
	{
		sm.show_Menu();//展示菜单
		cout << "请输入您的选项：";
		cin >> choice;

		switch (choice)
		{
		case 1://开始比赛
			sm.startSpeech();
			break;
		case 2://查看记录
			sm.showRecord();
			break;
		case 3://清空记录
			sm.clearRecord();
			break;
		case 0://退出系统
			sm.exitSystem();
			break;
		default:
			system("cls");//清空屏幕
			break;
		}
	}


	return 0;
}