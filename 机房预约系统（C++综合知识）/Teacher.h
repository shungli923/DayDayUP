#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
using namespace std;
#include"Identity.h"
#include"orderFile.h"

class Teacher :public Identity
{
public:
	Teacher();
	Teacher(int empId, string name, string pwd);//��ţ�����������
	virtual void operMenu();//�����˵�
	void showAllOrder();//�鿴����ԤԼ
	void validOrder();//���ԤԼ

	int m_EmpId;
};