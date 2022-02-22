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
	Teacher(int empId, string name, string pwd);//编号，姓名，密码
	virtual void operMenu();//操作菜单
	void showAllOrder();//查看所有预约
	void validOrder();//审核预约

	int m_EmpId;
};