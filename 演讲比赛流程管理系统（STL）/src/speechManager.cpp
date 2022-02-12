#include<fstream>
#include <deque>
#include<vector>
#include<algorithm>
#include<numeric>
#include"speechManager.h"
#include"speaker.h"



SpeechManager::SpeechManager()
{
	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();
}

SpeechManager::~SpeechManager() {}

void SpeechManager::show_Menu()
{
	cout << "***********************************" << endl;
	cout << "********* 欢迎参加演讲比赛 ********" << endl;
	cout << "********* 1、开始演讲比赛 *********" << endl;
	cout << "********* 2、查看往届比赛 *********" << endl;
	cout << "********* 3、清空比赛记录 *********" << endl;
	cout << "********* 0、退出比赛程序 *********" << endl;
	cout << "***********************************" << endl;
	cout << endl;
}

void SpeechManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

void SpeechManager::initSpeech()
{
	this->v1.clear();
	this->v2.clear();
	this->vVictor.clear();
	this->m_Speaker.clear();
	this->m_Record.clear();
	this->m_index = 1;//初始化比赛轮数
}

void SpeechManager::createSpeaker()
{
	string nameSeed{ "ABCDEFGHIJGL" };
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name{ "选手" };
		name += nameSeed[i];
		Speaker sp;
		sp.m_name = name;
		for (int i = 0;i < 2;i++)sp.m_Score[i] = 0;

		this->v1.push_back(i+10001);//12名选手编号
		this->m_Speaker.insert(make_pair(i + 10001, sp));//选手编号以及对应选手存放到map容器中
	}
}

void SpeechManager::startSpeech()
{
	//第一轮比赛
	speechDraw();//1、抽签
	speechContest();//2、比赛
	showScore();//3、显示比赛结果

	this->m_index++;

	//第二轮比赛
	speechDraw();//1、抽签
	speechContest();//2、比赛
	showScore();//3、显示比赛结果

	//保存分数
	saveRecord();

	//重置比赛，初始化属性
	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();

	cout << "本届比赛完毕！" << endl;
	system("pause");
	system("cls");
}

void SpeechManager::speechDraw()
{
	cout << "第 <<" << this->m_index << ">> 轮比赛选手正在抽签" << endl;
	cout << "-------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;
	if (this->m_index == 1)
	{
		random_shuffle(v1.begin(), v1.end());
		for (auto it = v1.begin(); it != v1.end(); it++)
			cout << *it << " ";
		cout << endl;
	}
	else 
	{
		random_shuffle(v2.begin(), v2.end());
		for (auto it = v2.begin(); it != v2.end(); it++)
			cout << *it << " ";
		cout << endl;
	}
	cout << "-------------------" << endl;
	system("pause");
	cout << endl;
}

void SpeechManager::speechContest()
{
	cout << "------------ 第" << this->m_index << "轮正式比赛开始：-------------" << endl;
	multimap<double, int, greater<double>> groupScore;//临时容器 保存key分数 value选手编号

	int num = 0;//记录人员数，6人一组
	
	vector<int>v_Src;//比赛的人员容器
	if (this->m_index == 1)
		v_Src = v1;
	else
		v_Src = v2;

	for (auto it = v_Src.begin(); it != v_Src.end(); it++)
	{
		//遍历所有参赛选手
		num++;

		//评委打分
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;//得分在600~1000
			//cout << score << " ";
			d.push_back(score);
		}

		sort(v_Src.begin(), v_Src.end(), greater<double>());//排序
		d.pop_back();//去掉最高分
		d.pop_front();//去掉最低分

		double sum = accumulate(d.begin(), d.end(), 0.0f);//获取总分
		double avg = sum / (double)d.size();//获取平均分

		//每个人的平均分
		//cout << "编号：" << *it << "  选手：" << this->m_Speaker[*it].m_name << "  平均分为：" << avg << endl;
		this->m_Speaker[*it].m_Score[this->m_index - 1] = avg;

		//6人一组 用临时容器保存
		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次：" << endl;
			for (auto it_1 = groupScore.begin(); it_1 !=groupScore.end(); it_1++)
			{
				cout << "编号：" << it_1->second << " 姓名：" << this->m_Speaker[it_1->second].m_name
					<< " 成绩：" << this->m_Speaker[it_1->second].m_Score[this->m_index - 1] << endl;
			}

			//取前三名
			int count = 0;
			for (auto it_2 = groupScore.begin(); it_2 != groupScore.end() && count < 3; it_2++, count++)
			{
				if (this->m_index == 1)
					v2.push_back((*it_2).second);
				else
					vVictor.push_back((*it_2).second);
			}

			groupScore.clear();

			cout << endl;
		}
	}
	cout << "-------------- 第" << this->m_index << "轮比赛结束 ----------------" << endl;
	cout << endl;
}

void SpeechManager::showScore()
{
	cout << "-------------- 第" << this->m_index << "轮晋级选手信息如下 ----------------" << endl;
	vector<int>v;
	if (this->m_index == 1)v = v2;
	else v = vVictor;

	for (auto it = v.begin(); it != v.end(); it++)
	{
		cout << "选手编号：" << *it << " 姓名：" << m_Speaker[*it].m_name << " 得分：" << 
		m_Speaker[*it].m_Score[this->m_index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->show_Menu();
}

void SpeechManager::saveRecord()//保存分数至文件
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//用输出的方式打开文件，写文件

	//将每个人数据写入文件中
	for (auto it = vVictor.begin(); it != vVictor.end(); it++)
	{
		ofs << *it << "," << m_Speaker[*it].m_Score[1] << ',';
	}
	ofs << endl;

	ofs.close();
	cout << "记录已保存" << endl;
	this->fileIsEmpty = false;
}

void SpeechManager::loadRecord()//读取记录
{
	ifstream ifs("speech.csv", ios::in);//输入流对象，读取文件
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		cout << "文件不存在！" << endl;
		ifs.close();
		return;
	}
	
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空！" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件不为空
	this->fileIsEmpty = false;
	ifs.putback(ch);//检验文件是否为空时读取的单个字符放回去

	string data;
	int index = 0;
	while (ifs>>data)
	{
		//cout << data << endl;
		vector<string>v;
		
		int pos = -1;
		int start = 0;

		while (true)
		{
			pos = data.find(",", start);//从0开始查找“，”
			if (pos == -1)break;
			string tmp = data.substr(start, pos - start);//找到了进行截取分割逗号
			v.push_back(tmp);
			start = pos + 1;
		}

		this->m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
}

void SpeechManager::showRecord()
{
	for (int i = 0; i < this->m_Record.size(); i++)
	{
		if (this->fileIsEmpty)
		{
			cout << "文件为空或者不存在!" << endl;
		}
		else {
			cout << "第" << i + 1 << "届 " <<
				"冠军编号：" << this->m_Record[i][0] << " 得分：" << this->m_Record[i][1] << ' ' <<
				"亚军编号：" << this->m_Record[i][2] << " 得分：" << this->m_Record[i][3] << ' ' <<
				"季军编号：" << this->m_Record[i][4] << " 得分：" << this->m_Record[i][5] << ' ' <<
				endl;
		}
	}
	system("pause");
	system("cls");
}

void SpeechManager::clearRecord()//清空记录
{
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;

	int select = 0;
	cin >> select;

	if (select==1)
	{
		//打开模式ios::trunc如果存在删除文件并重新创建
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		//初始化各属性
		this->initSpeech();
		this->createSpeaker();
		this->loadRecord();

		cout << "清空成功！" << endl;
	}
}