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
	virtual void operMenu();//操作菜单
	void addPerson();//添加账号
	void showPerson();//展示账号
	void showComputer();//查看机房信息
	void cleanFile();//清空预约记录

	void initVector();//初始化容器
	vector<Student>vStu;//学生容器
	vector<Teacher>vTea;//教职工容器
	vector<ComputerRoom>vCom;//机房容器
	//type代表id类型（学生，老师）返回true则为重复
	bool checkRepeat(int id, int type);
};