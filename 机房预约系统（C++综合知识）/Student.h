#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include"Identity.h"
#include"computerRoom.h"
#include"globalFile.h"
#include"orderFile.h"

//ѧ����
class Student :public Identity
{
public:
	Student();//�޲ι��캯��
	Student(int id, string name, string pwd);//ѧ�ţ�����������
	//�˵�����
	virtual void operMenu();
	void applyOrder();//����ԤԼ
	void showMyOrder();//�鿴�ҵ�ԤԼ
	void showAllOrder();//�鿴����ԤԼ
	void cancelOrder();//ȡ��ԤԼ

	int m_Id;//ѧ��ѧ��
	vector<ComputerRoom>vCom;//������Ϣ
};