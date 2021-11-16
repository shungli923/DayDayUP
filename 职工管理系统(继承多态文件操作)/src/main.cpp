#include<iostream>
#include"workerManager.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
using namespace std;

int main() {
	WorkerManager wm;
	int choice = 0;
	
	while (true){
		//展示菜单
		wm.showMenu();
		cout << "请输入您的选择："; 
		cin >> choice;

		switch (choice)
		{
		case 0://退出当前管理系统
			wm.exitSystem();
			break;
		case 1://添加职工(批量添加职工，将信息录入到文件中，职工信息为：职工编号，姓名，部门编号
			wm.addEmp();
			break;
		case 2://显示所有职工信息)
			wm.showEmp();
			break;
		case 3://删除职工信息（按照编号删除）
			wm.delEmp();
			break;
		case 4://更新职工信息（按照编号修改）
			wm.modEmp();
			break;
		case 5://查找职工（按照编号或者姓名查找）
			wm.findEmp();
			break;
		case 6://将职工按编号排序（排序规则用户指定)
			wm.sortEmp();
			break;
		case 7://清空职工信息（清空前需再次确认，防止误删）
			wm.cleanFile();
			break;
		default:
			system("cls");
			break;
		}
	}
	return 0;
}