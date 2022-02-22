#include"Manager.h"

Manager::Manager()
{

}

Manager::Manager(string name, string pwd)
{
	//初始化管理员信息
	this->m_Name = name;
	this->m_Pwd = pwd;

	this->initVector();

	//获取机房信息
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);

	ComputerRoom c;
	while (ifs>>c.m_ComId&&ifs>>c.m_MaxNum)
	{
		vCom.push_back(c);
	}

	cout << "当前机房数量为：" << vCom.size() << endl;
	
	ifs.close();
}

void Manager::operMenu()//操作菜单
{
	cout << "欢迎管理员" << this->m_Name << "登录！" << endl;
	cout << "\t\t-----------------------------\n";
	cout << "\t\t|                           |\n";
	cout << "\t\t|       1、添加账号         |\n";
	cout << "\t\t|                           |\n";
	cout << "\t\t|       2、查看账号         |\n";
	cout << "\t\t|                           |\n";
	cout << "\t\t|       3、查看机房         |\n";
	cout << "\t\t|                           |\n";
	cout << "\t\t|       4、清空预约         |\n";
	cout << "\t\t|                           |\n";
	cout << "\t\t|       0、注销登录         |\n";
	cout << "\t\t|                           |\n";
	cout << "\t\t-----------------------------\n";
	cout << "请选择您的操作：" << endl;
}

void Manager::addPerson()//添加账号
{
	cout << "请输入添加账号类型：" << endl;
	cout << "1、添加学生" << endl;
	cout << "2、添加老师" << endl;
	
	string filename;
	string tip;
	ofstream ofs;

	string errorTip;

	int select = 0;
	cin >> select;

	if (select==1)
	{
		filename = STUDENT_FILE;
		tip = "请输入学号：";
		errorTip = "学号重复，请重新输入";
	}
	else
	{
		filename = TEACHER_FILE;
		tip = "请输入职工编号：";
		errorTip = "职工号重复，请重新输入";
	}

	ofs.open(filename, ios::out | ios::app);
	
	int id;
	string name;
	string pwd;

	cout << tip;

	while (true)
	{
		cin >> id;

		int type = 0;
		if (select == 1)type = 1;
		else type = 2;

		bool ret = this->checkRepeat(id, type);
		if (ret)cout << errorTip << endl;
		else break;
	}

	cout << "请输入姓名：" << endl;
	cin >> name;

	cout << "请输入密码：" << endl;
	cin >> pwd;

	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "添加成功" << endl;

	system("pause");
	system("cls");
	
	ofs.close();
	this->initVector();
}

void printStudent(Student& s)
{
	cout << "学号：" << s.m_Id << "    姓名：" << s.m_Name << "    密码：" << s.m_Pwd << endl;
}
void printTeacher(Teacher& t)
{
	cout << "学号：" << t.m_EmpId << "    姓名：" << t.m_Name << "    密码：" << t.m_Pwd << endl;
}

void Manager::showPerson()//展示账号
{
	cout << "请选择查看内容：" << endl;
	cout << "1、查看所有学生" << endl;
	cout << "2、查看所有老师" << endl;

	int select = 0;
	cin >> select;

	if (select==1)
	{
		cout << "所有学生信息如下：" << endl;
		for_each(vStu.begin(), vStu.end(), printStudent);
	}
	else
	{
		cout<< "所有老师信息如下：" << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher);
	}

	system("pause");
	system("cls");
}

void Manager::showComputer()//查看机房信息
{
	cout << "机房信息如下：" << endl;
	for (auto it=vCom.begin();it!=vCom.end();it++)
	{
		cout << "机房编号：" << it->m_ComId << "    最大容量" << it->m_MaxNum << endl;
	}
	system("pause");
	system("cls");
}

void Manager::cleanFile()//清空预约记录
{
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();

	cout << "清空成功!" << endl;

	system("pause");
	system("cls");
}

void Manager::initVector()//初始化容器
{
	//读取学生文件信息
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件打开失败！" << endl;
		return;
	}

	vStu.clear();

	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd)
	{
		vStu.push_back(s);
	}
	cout << "当前学生数量为：" << vStu.size() << endl;
	ifs.close();//学生初始化完成

	//读取老师文件信息
	//ifstream ifs;
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件打开失败 ！" << endl;
		return;
	}

	vTea.clear();

	Teacher t;
	while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd)
	{
		vTea.push_back(t);
	}

	cout << "当前教职工数量为：" << vTea.size() << endl;
	ifs.close();//教职工初始化完成
}

bool Manager::checkRepeat(int id, int type)
{
	if (type==1)
	{
		for (auto it = vStu.begin();it != vStu.end();it++)
		{
			if (id==it->m_Id)
			{
				return true;
			}
		}
	}
	else
	{
		for (auto it = vTea.begin();it != vTea.end();it++)
		{
			if (id == it->m_EmpId)
			{
				return true;
			}
		}
	}

	return false;
}