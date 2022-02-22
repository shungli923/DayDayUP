#pragma once
#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
using namespace std;
#include"Identity.h"
#include"Student.h"
#include"Teacher.h"
#include"computerRoom.h"
#include"globalFile.h"

class Manager :public Identity
{
public:
	Manager();
	Manager(string name, string pwd);
	virtual void operMenu();//�����˵�
	void addPerson();//����˺�
	void showPerson();//չʾ�˺�
	void showComputer();//�鿴������Ϣ
	void cleanFile();//���ԤԼ��¼

	void initVector();//��ʼ������
	vector<Student>vStu;//ѧ������
	vector<Teacher>vTea;//��ְ������
	vector<ComputerRoom>vCom;//��������
	//type����id���ͣ�ѧ������ʦ������true��Ϊ�ظ�
	bool checkRepeat(int id, int type);
};