#include"workerManager.h"
#include"boss.h"
#include"manager.h"
#include"employee.h"

WorkerManager::WorkerManager() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//文件不存在情况
	if (!ifs.is_open()) {
		cout << "文件不存在" << endl << endl;
		this->m_EmpNum = 0;//初始化人数
		this->m_EmpArray = NULL;//初始化数组
		this->m_fileIsEmpty = true;

		ifs.close();
		return;
	}

	//文件存在但没有记录信息
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "文件为空" << endl << endl;
		this->m_EmpNum = 0;//初始化人数
		this->m_EmpArray = NULL;//初始化数组
		this->m_fileIsEmpty = true;

		ifs.close();
		return;
	}

	//设置已有员工数量
	int num = this->getEmpNum();
	/* cout << "职工人数为：" << num << " 人" << endl;//***测试显示已有职工数量** */
	this->m_EmpNum = num;

	//成员数组属性管理已有员工信息
	this->m_EmpArray = new Worker*[this->m_EmpNum];//开辟空间
	this->initEmp();//初始化员工，用成员数组记录员工信息

	//*****测试输出已有职工信息*****
	/*for (int i = 0; i < this->m_EmpNum; ++i) {
		cout << "职工编号：" << this->m_EmpArray[i]->m_Id << "  "
			<< "职工姓名：" << this->m_EmpArray[i]->m_Name << "  "
			<< "职工岗位：" << this->m_EmpArray[i]->m_Dept << "  "<< endl;
	}*/
}

WorkerManager::~WorkerManager() {
	if (this->m_EmpArray != NULL) {
		for (int i = 0; i < this->m_EmpNum; ++i) {
			if (this->m_EmpArray[i] != NULL) {
				delete this->m_EmpArray[i];
			}
		}
		
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}

void WorkerManager::showMenu() {
	cout << "***********      欢迎使用职工管理系统      ***********" << endl;
	cout << "*   1----批量添加职工信息                            *" << endl;
	cout << "*   2----显示所有职工信息                            *" << endl;
	cout << "*   3----删除职工信息（按照编号删除）                *" << endl;
	cout << "*   4----更新职工信息（按照编号修改）                *" << endl;
	cout << "*   5----查找职工（按照编号或者姓名查找）            *" << endl;
	cout << "*   6----将职工按编号排序（排序规则用户指定)         *" << endl;
	cout << "*   7----清空职工信息（清空前需再次确认，防止误删）  *" << endl;
	cout << "*   0----退出当前管理系统                            *" << endl;
	cout << "******************************************************" << endl;
	cout << endl;
}

void WorkerManager::exitSystem() {
	cout << "欢迎下次使用" << endl;
	exit(0);
}

void WorkerManager::addEmp() {
	int addnum = 0;
	cout << "请输入增加职工数量：" << endl;
	cin >> addnum;

	if (addnum > 0) {
		int newSize = this->m_EmpNum + addnum;//计算新空间大小
		Worker** newSpace = new Worker*[newSize];

		if (this->m_EmpArray != NULL) {//将原空间内的内容放入新空间
			for (int i = 0; i < this->m_EmpNum; ++i) {
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		for (int i = 0; i < addnum; ++i) {//批量添加新数据
			int id;
			string name;
			int dpt_id;

			cout << "输入第" << i + 1 << "个新职工编号" << endl;
			cin >> id;
			cout << "输入第" << i + 1 << "个新职工姓名" << endl;
			cin >> name;
			cout << "请选择该职工岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dpt_id;

			Worker* worker = NULL;
			switch (dpt_id)
			{
			case 1://普通职工
				worker = new Employee(id, name, dpt_id);
				break;
			case 2://经理
				worker = new Manager(id, name, dpt_id);
				break;
			case 3://老板
				worker = new Boss(id, name, dpt_id);
			default:
				break;
			}

			newSpace[this->m_EmpNum + i] = worker;//将职工插入职工管理数组中
		}
		delete[] this->m_EmpArray;//清理上一个管理数组

		this->m_EmpArray = newSpace;//用内部成员管理新的职工管理数组
		this->m_EmpNum = newSize;//用内部成员记录新的职工总数量

		cout << "添加成功 " << addnum << " 名新职工" << endl;

		this->save();//保存职工信息到文件中
		this->m_fileIsEmpty = false;//职工管理文件非空
	}
	else {
		cout << "输入有误" << endl;
	}

	system("pause");
	system("cls");//清空屏幕内容回到上级目录
}

void WorkerManager::save() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	for (int i = 0; i < this->m_EmpNum; ++i) {
		ofs << this->m_EmpArray[i]->m_Id << "  "
			<< this->m_EmpArray[i]->m_Name << "  "
			<< this->m_EmpArray[i]->m_Dept << endl;
	}

	ofs.close();
}

int WorkerManager::getEmpNum() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int num=0;//记录员工信息

	//按行读取文件
	int id;
	string name;
	int dId;
	//每读完一行职工数量加1
	while (ifs >> id && ifs >> name && ifs >> dId) {
		num++;
	}

	ifs.close();
	return num;
}

void WorkerManager::initEmp() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//存下读取的信息
	int id;
	string name;
	int dId;

	int index = 0;//记录已读取员工数量

	while (ifs >> id && ifs >> name && ifs >> dId) {
		Worker* worker = NULL;
		//根据不同部门的id创建不同职工对象
		if (dId == 1) {
			worker = new Employee(id, name, dId);
		}
		else if (dId ==2){
			worker = new Manager(id, name, dId);
		}
		else {
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
}

void WorkerManager::showEmp() {
	if (this->m_fileIsEmpty) {
		cout << "文件不存在或为空" << endl;
	}
	else {
		for (int i = 0; i < this->m_EmpNum; ++i) {
			this->m_EmpArray[i]->showInfo();
		}
	}

	system("pause");
	system("cls");
}

int WorkerManager::isExist(int id) {
	int ret = -1;
	for (int i = 0; i < this->m_EmpNum; ++i) {
		if (id == this->m_EmpArray[i]->m_Id) {
			ret = i;
			break;
		}
	}
	//返回值若为-1，则不存在该职工
	return ret;
}

void WorkerManager::delEmp() {
	if (this->m_fileIsEmpty) {
		cout << "没有职工记录" << endl;
	}
	else {
		cout << "输入将要删除的职工的编号：" << endl;
		int id = 0;
		cin >> id;
		int get = this->isExist(id);
		if (get != -1) {
			//职工存在，且其位置为get的值
			for (int i = get; i < this->m_EmpNum; ++i) {
				//数据前移一位
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;

			this->save();//更新到文件中
			cout << "删除成功！" << endl;
		}
		else {
			cout << "删除失败，该编号职工不存在，请重新操作！" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::modEmp() {
	if (this->m_fileIsEmpty) {
		cout << "没有职工记录" << endl;
	}
	else {
		cout << "请输入修改职工编号：" << endl;
		int id;
		cin >> id;
		int ret = this->isExist(id);
		
		if (ret != -1) {
			delete this->m_EmpArray[ret];

			int newId = 0;
			string newName = "";
			int newdId = 0;

			cout << "查到编号：" << id << "员工，请输入新职工号：" << endl;
			cin >> newId;

			cout << "请输入新姓名：" << endl;
			cin >> newName;

			cout << "请输入新岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> newdId;

			Worker* worker = NULL;
			switch (newdId) {
			case 1:
				worker = new Employee(newId, newName, newdId);
				break;
			case 2:
				worker = new Manager(newId, newName, newdId);
				break;
			case 3:
				worker = new Boss(newId, newName, newdId);
				break;
			}

			this->m_EmpArray[ret] = worker;//更改数据到数组中
			
			cout << "修改成功" << endl;

			this->save();//保存在文件中
		}
		else {
			cout << "没有此职工" << endl;	
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::findEmp() {
	if (this->m_fileIsEmpty) {
		cout << "没有职工记录" << endl;
	}
	else {
		cout << "请输入查找方式：" << endl;
		cout << "1:按职工编号查找" << endl;
		cout << "2:按职工姓名查找" << endl;

		int select = 0;
		cin >> select;

		if (select == 1) {
			int id;
			cout << "请输入要查询的职工号:";
			cin >> id;

			int ret = this->isExist(id);
			if (ret != -1) {
				cout << "查找成功！该职工信息：" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else {
				cout << "没有查找到此人" << endl;
			}
		}
		else if (select == 2) {
			string name;
			cout << "请输入要查找职工的姓名：";
			cin >> name;

			bool hasfind = false;
			for (int i = 0; i < this->m_EmpNum; ++i) {
				if (this->m_EmpArray[i]->m_Name == name) {
					cout << "查找成功！" << endl;
					cout << "职工信息为: " << endl;
					this->m_EmpArray[i]->showInfo();
					hasfind = true;
				}
			}
			if (!hasfind) {
				cout << "没查询到此职工" << endl;
			}
		}
		else {
			cout << "输入错误！请重新操作！" << endl;
		}
	}

	system("pause");
	system("cls");
}

void WorkerManager::sortEmp() {
	if (this->m_fileIsEmpty) {
		cout << "没有职工信息" << endl;
		system("pause");
		system("cls");
	}
	else {

		cout << "选择职工排序方式：" << endl;
		cout << "1:按职工编号升序排序" << endl;
		cout << "2:按职工编号降序排序" << endl;
		int select = 0;
		cin >> select;

		for (int i = 0; i < this->m_EmpNum; ++i) {
			int key = i;
			for (int j = i + 1; j < this->m_EmpNum; ++j) {
				if (select == 1) {//升序
					if (this->m_EmpArray[key]->m_Id > this->m_EmpArray[j]->m_Id) {
						key = j;
					}
				}
				else {//降序
					if (this->m_EmpArray[key]->m_Id < this->m_EmpArray[j]->m_Id) {
						key = j;
					}
				}
			}
			if (i != key) {
				Worker* temp;
				temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[key];
				this->m_EmpArray[key] = temp;
			}
		}
		cout << "排序成功！排序后结果为：" << endl;
		this->save();
		this->showEmp();
	}
}

void WorkerManager::cleanFile() {
	cout << "确认清空职工信息？" << endl;
	cout << "1:确认" << endl;
	cout << "2:返回" << endl;

	int select = 0;
	cin >> select;

	if (select == 1) {
		//打开模式ios::trunc如果存在删除文件并重新创建
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		if (this->m_EmpArray!=NULL) {//删除每个职工对象
			for (int i = 0; i < this->m_EmpNum; ++i) {
				if (this->m_EmpArray[i] != NULL) {
					delete this->m_EmpArray[i];
				}
			}
			this->m_EmpNum = 0;
			delete[] this->m_EmpArray;//删除堆区数组指针
			this->m_EmpArray = NULL;
			this->m_fileIsEmpty = true;
		}
		cout << "清空成功" << endl;

	}
	system("pause");
	system("cls");
}