#pragma once
#include<iostream>
#include<vector>
#include<map>
using namespace std;
#include"speaker.h"

//����ݽ�����������
class SpeechManager
{
public:
	vector<int>v1;//����ѡ��  ����  12��
	vector<int>v2;//��һ�ֽ�������  6��
	vector<int>vVictor;//ʤ��ǰ��������
	map<int, Speaker>m_Speaker;//��ű�źͶ�Ӧѡ��   ����
	int m_index;//��¼��������

	//��ǰ׼��
	SpeechManager();
	void show_Menu();
	void exitSystem();
	void initSpeech();
	void createSpeaker();

	//��������
	void startSpeech();
	void speechDraw();//��ǩ
	void speechContest();//����
	void showScore();//��ʾ����
	void saveRecord();//����������ļ�

	//�鿴��¼
	void loadRecord();//��ȡ��¼
	bool fileIsEmpty;//�ж��ļ��Ƿ�Ϊ��
	map<int, vector<string>>m_Record;

	void showRecord();//��ʾ�����¼

	void clearRecord();//��ռ�¼

	~SpeechManager();
private:

};

