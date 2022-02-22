#include<iostream>
#include<fstream>
using namespace std;
#include"globalFile.h"
#include"Identity.h"
#include"Student.h"
#include"Teacher.h"
#include"Manager.h"

//登录功能
void LoginIn(string Filename,int type);//参数1：操作文件名称  参数2：任务类型 1：学生； 2：老师； 3：管理员；
void managerMenu(Identity* &manager);//进入管理员子菜单
void studentMenu(Identity*& student);//进入学生预约子菜单
void teacherMenu(Identity*& teacher);//进入教师预约子菜单

int main()
{
	int select = 0;

	while (true)
	{
		cout << "\t============ 欢迎进入机房预约系统 ============" << endl;
		cout << endl << "请输入您的身份" << endl;
		cout << "\t\t-----------------------------\n";
		cout << "\t\t|                           |\n";
		cout << "\t\t|       1、学生代表         |\n";
		cout << "\t\t|                           |\n";
		cout << "\t\t|       2、老    师         |\n";
		cout << "\t\t|                           |\n";
		cout << "\t\t|       3、管 理 员         |\n";
		cout << "\t\t|                           |\n";
		cout << "\t\t|       0、退    出         |\n";
		cout << "\t\t|                           |\n";
		cout << "\t\t-----------------------------\n";

		cout << "请输入您的选择：";
		cin >> select;//接受用户选择

		switch (select)
		{
		case 1://学生代表身份
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2://老师身份
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3://管理者身份
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0://退出系统
			cout << "欢迎下次使用" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "输入有误，请重新选择！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	return 0;
	system("pause");
}

void LoginIn(string Filename, int type)//参数1：操作文件名称  参数2：任务类型 1：学生； 2：老师； 3：管理员；
{
	Identity* person = nullptr;

	ifstream ifs;
	ifs.open(Filename, ios::in);

	//文件不存在的情况
	if (!ifs.is_open())
	{
		cout << "文件不存在！" << endl;
		ifs.close();
		return;
	}

	int id = 0;
	string name;
	string pwd;

	if (type == 1)
	{
		cout << "请输入您的学号：" << endl;
		cin >> id;
	}
	else if (type == 2)
	{
		cout << "请输入您的职工号：" << endl;
		cin >> id;
	}

	cout << "请输入用户名：" << endl;
	cin >> name;

	cout << "请输入密码：" << endl;
	cin >> pwd;

	if (type == 1)
	{
		//学生登录验证
		int Fid;
		string fName;
		string fPwd;
		
		while (ifs >> Fid && ifs >> fName && ifs >> fPwd)
		{
			if (id == Fid && name == fName && pwd == fPwd)
			{
				cout << "学生验证登录成功！" << endl;
				system("pause");
				system("cls");
				person = new Student(id, name, pwd);
				//学生端子菜单界面
				studentMenu(person);
				return;
			}
		}
	}
	else if (type == 2)
	{
		//老师登录验证
		int Fid;
		string fName;
		string fPwd;

		while (ifs >> Fid && ifs >> fName && ifs >> fPwd)
		{
			if (id == Fid && name == fName && pwd == fPwd)
			{
				cout << "老师验证登录成功！" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				//老师端子菜单界面
				teacherMenu(person);
				return;
			}
		}
	}
	else if (type == 3)
	{
		//管理员登录验证
		string fName;
		string fPwd;

		while (ifs >> fName && ifs >> fPwd)
		{
			if (name == fName && pwd == fPwd)
			{
				cout << "管理员验证登录成功！" << endl;
				system("pause");
				system("cls");
				person = new Manager(name, pwd);
				//管理员操作子菜单
				managerMenu(person);
				return;
			}
		}
	}

	cout << "验证登录失败！" << endl;

	system("pause");
	system("cls");
	return;
}

void teacherMenu(Identity*& teacher)
{
	while (true)
	{
		//教师菜单
		teacher->operMenu();

		Teacher* tea = (Teacher*)teacher;
		int select = 0;
		cin >> select;

		if (select == 1)tea->showAllOrder();//查看所有预约
		else if (select == 2)tea->validOrder();//审核预约
		else
		{
			delete teacher;
			cout << "注销成功" << endl;

			system("pause");
			system("cls");
			return;
		}
		
	}
}

void studentMenu(Identity* &student)
{
	while (true)
	{
		//学生菜单
		student->operMenu();

		Student* stu = (Student*)student;
		int select = 0;

		cin >> select;

		if (select == 1)stu->applyOrder();//申请预约
		else if (select == 2)stu->showMyOrder();//查看我的预约
		else if (select == 3)stu->showAllOrder();//查看全部预约
		else if (select == 4)stu->cancelOrder();//取消预约
		else
		{
			delete student;
			cout << "注销成功！" << endl;

			system("pause");
			system("cls");
			return;
		}
	}
}

void managerMenu(Identity* &manager)
{
	while (true)
	{
		//调用管理员子菜单
		manager->operMenu();

		Manager* man = (Manager*)manager;
		int select;

		cin >> select;

		if (select == 1)man->addPerson();//添加账号
		else if (select==2)man->showPerson();//查看账号
		else if (select==3)man->showComputer();//查看机房
		else if (select == 4)man->cleanFile();//清空预约
		else
		{
			delete manager;
			cout << "注销成功" << endl;

			system("pause");
			system("cls");

			return;
		}
	}
}