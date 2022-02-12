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
	cout << "********* ��ӭ�μ��ݽ����� ********" << endl;
	cout << "********* 1����ʼ�ݽ����� *********" << endl;
	cout << "********* 2���鿴������� *********" << endl;
	cout << "********* 3����ձ�����¼ *********" << endl;
	cout << "********* 0���˳��������� *********" << endl;
	cout << "***********************************" << endl;
	cout << endl;
}

void SpeechManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
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
	this->m_index = 1;//��ʼ����������
}

void SpeechManager::createSpeaker()
{
	string nameSeed{ "ABCDEFGHIJGL" };
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name{ "ѡ��" };
		name += nameSeed[i];
		Speaker sp;
		sp.m_name = name;
		for (int i = 0;i < 2;i++)sp.m_Score[i] = 0;

		this->v1.push_back(i+10001);//12��ѡ�ֱ��
		this->m_Speaker.insert(make_pair(i + 10001, sp));//ѡ�ֱ���Լ���Ӧѡ�ִ�ŵ�map������
	}
}

void SpeechManager::startSpeech()
{
	//��һ�ֱ���
	speechDraw();//1����ǩ
	speechContest();//2������
	showScore();//3����ʾ�������

	this->m_index++;

	//�ڶ��ֱ���
	speechDraw();//1����ǩ
	speechContest();//2������
	showScore();//3����ʾ�������

	//�������
	saveRecord();

	//���ñ�������ʼ������
	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();

	cout << "���������ϣ�" << endl;
	system("pause");
	system("cls");
}

void SpeechManager::speechDraw()
{
	cout << "�� <<" << this->m_index << ">> �ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "-------------------" << endl;
	cout << "��ǩ���ݽ�˳�����£�" << endl;
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
	cout << "------------ ��" << this->m_index << "����ʽ������ʼ��-------------" << endl;
	multimap<double, int, greater<double>> groupScore;//��ʱ���� ����key���� valueѡ�ֱ��

	int num = 0;//��¼��Ա����6��һ��
	
	vector<int>v_Src;//��������Ա����
	if (this->m_index == 1)
		v_Src = v1;
	else
		v_Src = v2;

	for (auto it = v_Src.begin(); it != v_Src.end(); it++)
	{
		//�������в���ѡ��
		num++;

		//��ί���
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;//�÷���600~1000
			//cout << score << " ";
			d.push_back(score);
		}

		sort(v_Src.begin(), v_Src.end(), greater<double>());//����
		d.pop_back();//ȥ����߷�
		d.pop_front();//ȥ����ͷ�

		double sum = accumulate(d.begin(), d.end(), 0.0f);//��ȡ�ܷ�
		double avg = sum / (double)d.size();//��ȡƽ����

		//ÿ���˵�ƽ����
		//cout << "��ţ�" << *it << "  ѡ�֣�" << this->m_Speaker[*it].m_name << "  ƽ����Ϊ��" << avg << endl;
		this->m_Speaker[*it].m_Score[this->m_index - 1] = avg;

		//6��һ�� ����ʱ��������
		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С��������Σ�" << endl;
			for (auto it_1 = groupScore.begin(); it_1 !=groupScore.end(); it_1++)
			{
				cout << "��ţ�" << it_1->second << " ������" << this->m_Speaker[it_1->second].m_name
					<< " �ɼ���" << this->m_Speaker[it_1->second].m_Score[this->m_index - 1] << endl;
			}

			//ȡǰ����
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
	cout << "-------------- ��" << this->m_index << "�ֱ������� ----------------" << endl;
	cout << endl;
}

void SpeechManager::showScore()
{
	cout << "-------------- ��" << this->m_index << "�ֽ���ѡ����Ϣ���� ----------------" << endl;
	vector<int>v;
	if (this->m_index == 1)v = v2;
	else v = vVictor;

	for (auto it = v.begin(); it != v.end(); it++)
	{
		cout << "ѡ�ֱ�ţ�" << *it << " ������" << m_Speaker[*it].m_name << " �÷֣�" << 
		m_Speaker[*it].m_Score[this->m_index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->show_Menu();
}

void SpeechManager::saveRecord()//����������ļ�
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//������ķ�ʽ���ļ���д�ļ�

	//��ÿ��������д���ļ���
	for (auto it = vVictor.begin(); it != vVictor.end(); it++)
	{
		ofs << *it << "," << m_Speaker[*it].m_Score[1] << ',';
	}
	ofs << endl;

	ofs.close();
	cout << "��¼�ѱ���" << endl;
	this->fileIsEmpty = false;
}

void SpeechManager::loadRecord()//��ȡ��¼
{
	ifstream ifs("speech.csv", ios::in);//���������󣬶�ȡ�ļ�
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		cout << "�ļ������ڣ�" << endl;
		ifs.close();
		return;
	}
	
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ�գ�" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//�ļ���Ϊ��
	this->fileIsEmpty = false;
	ifs.putback(ch);//�����ļ��Ƿ�Ϊ��ʱ��ȡ�ĵ����ַ��Ż�ȥ

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
			pos = data.find(",", start);//��0��ʼ���ҡ�����
			if (pos == -1)break;
			string tmp = data.substr(start, pos - start);//�ҵ��˽��н�ȡ�ָ��
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
			cout << "�ļ�Ϊ�ջ��߲�����!" << endl;
		}
		else {
			cout << "��" << i + 1 << "�� " <<
				"�ھ���ţ�" << this->m_Record[i][0] << " �÷֣�" << this->m_Record[i][1] << ' ' <<
				"�Ǿ���ţ�" << this->m_Record[i][2] << " �÷֣�" << this->m_Record[i][3] << ' ' <<
				"������ţ�" << this->m_Record[i][4] << " �÷֣�" << this->m_Record[i][5] << ' ' <<
				endl;
		}
	}
	system("pause");
	system("cls");
}

void SpeechManager::clearRecord()//��ռ�¼
{
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;

	int select = 0;
	cin >> select;

	if (select==1)
	{
		//��ģʽios::trunc�������ɾ���ļ������´���
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		//��ʼ��������
		this->initSpeech();
		this->createSpeaker();
		this->loadRecord();

		cout << "��ճɹ���" << endl;
	}
}