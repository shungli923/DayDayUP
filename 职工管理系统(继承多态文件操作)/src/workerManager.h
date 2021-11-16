#pragma once
#include<iostream>
#include"Worker.h"
#include<fstream>
using namespace std;
#define FILENAME "empfile.txt"

class WorkerManager {
public:
	WorkerManager();
	~WorkerManager();
	
	void showMenu();//展示菜单
	void exitSystem();//退出系统
	void addEmp();//添加职工
	void save();//保存在文件中
	int getEmpNum();//获取职工数量
	void initEmp();//初始化已存在员工
	void showEmp();//显示职工信息
	int isExist(int id);//判断职工是否存在（按编号）
	void delEmp();//删除职工
	void modEmp();//修改职工
	void findEmp();//查找职工
	void sortEmp();//排序职工
	void cleanFile();//清空职工信息
	
private:
	int m_EmpNum;//职工数量
	Worker** m_EmpArray;//存放职工信息的数组
	bool m_fileIsEmpty;//标志文件是否为空
};
 