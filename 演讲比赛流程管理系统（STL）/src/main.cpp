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
		cout << "ѡ�֣�" << it->second.m_name << endl;
		cout << "һ�ַ�����" << it->second.m_Score[0] << endl;
		cout << "���ַ�����" << it->second.m_Score[1] << endl;
		cout << endl;
	}*/

	int choice = 0;//��¼�û�ѡ��

	while (true)
	{
		sm.show_Menu();//չʾ�˵�
		cout << "����������ѡ�";
		cin >> choice;

		switch (choice)
		{
		case 1://��ʼ����
			sm.startSpeech();
			break;
		case 2://�鿴��¼
			sm.showRecord();
			break;
		case 3://��ռ�¼
			sm.clearRecord();
			break;
		case 0://�˳�ϵͳ
			sm.exitSystem();
			break;
		default:
			system("cls");//�����Ļ
			break;
		}
	}


	return 0;
}