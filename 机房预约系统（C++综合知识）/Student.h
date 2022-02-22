#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include"Identity.h"
#include"computerRoom.h"
#include"globalFile.h"
#include"orderFile.h"

//学生类
class Student :public Identity
{
public:
	Student();//无参构造函数
	Student(int id, string name, string pwd);//学号，姓名，密码
	//菜单操作
	virtual void operMenu();
	void applyOrder();//申请预约
	void showMyOrder();//查看我的预约
	void showAllOrder();//查看所有预约
	void cancelOrder();//取消预约

	int m_Id;//学生学号
	vector<ComputerRoom>vCom;//机房信息
};