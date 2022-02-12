#pragma once
#include<iostream>
#include<vector>
#include<map>
using namespace std;
#include"speaker.h"

//设计演讲比赛管理类
class SpeechManager
{
public:
	vector<int>v1;//比赛选手  容器  12人
	vector<int>v2;//第一轮晋级容器  6人
	vector<int>vVictor;//胜利前三名容器
	map<int, Speaker>m_Speaker;//存放编号和对应选手   容器
	int m_index;//记录比赛轮数

	//赛前准备
	SpeechManager();
	void show_Menu();
	void exitSystem();
	void initSpeech();
	void createSpeaker();

	//比赛流程
	void startSpeech();
	void speechDraw();//抽签
	void speechContest();//比赛
	void showScore();//显示分数
	void saveRecord();//保存分数至文件

	//查看记录
	void loadRecord();//读取记录
	bool fileIsEmpty;//判断文件是否为空
	map<int, vector<string>>m_Record;

	void showRecord();//显示往届记录

	void clearRecord();//清空记录

	~SpeechManager();
private:

};

