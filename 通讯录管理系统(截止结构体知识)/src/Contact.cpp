#include<iostream>
#include<string>
#include"Contact.h"

using namespace std;

int i;//客户进行的选项

void Menu() {
	cout << "欢迎进入您的通讯录：请按键执行操作：" << endl;
	cout << "输入 1 ―― 添加联系人" << endl;
	cout << "输入 2 ―― 显示所有联系人详细信息" << endl;
	cout << "输入 3 ―― 按姓名删除联系人" << endl;
	cout << "输入 4 ―― 按姓名查找联系人" << endl;
	cout << "输入 5 ―― 按姓名修改联系人" << endl;
	cout << "输入 6 ―― 清空联系人" << endl;
	cout << "输入 7 ―― 退出通讯录" << endl;
}

void DO() {
	cout << endl << "请输入您要执行的操作：" << endl;

	switch (i) {
	case 1:
		Insert(); break;
	case 2:
		Display(); break;
	case 3:
		Delete(); break;
	case 4:
		Find(); break;
	case 5:
		Update(); break;
	case 6:
		Clear(); break;
	case 7:
		break;
	}
}


void Insert() {//添加联系人1
	for (int i = 0; i < 1000; i++) {
		if (Con[i].isEmpty == false) {
			cout << "以回车键/空格键为分隔，依次输入姓名、性别、年龄、电话、地址：" << endl << endl;
			cin >> Con[i].Name;
			cin >> Con[i].Sex;
			cin >> Con[i].Age;
			cin >> Con[i].Tel;
			cin >> Con[i].Address;

			Con[i].isEmpty = true;
			cout << "联系人: " << Con[i].Name << " 添加成功！" << endl << endl;
		}
		break;
	}
}

void Display() {//显示所有联系人详细信息2
	int count = 0;
	for (int i = 0; i < 1000; i++) {
		if (Con[i].isEmpty == true) {
			cout << Con[i].Name << '\t';
			cout << Con[i].Sex << '\t';
			cout << Con[i].Age << '\t';
			cout << Con[i].Tel << '\t';
			cout << Con[i].Address << endl << endl;

			count++;
		}
	}
	cout << "全部 " << count << "位联系人已显示完毕！" << endl << endl;
}

void Delete() {//按姓名删除联系人3
	cout << "请输入你将要删除的联系人姓名：";
	string one;
	cin >> one;
	for (int i = 0; i < 1000; i++) {
		if (Con[i].Name == one) {
			Con[i].Name = '\0';
			Con[i].Sex = '\0';
			Con[i].Age = -1;
			Con[i].Tel = '\0';
			Con[i].Address = '\0';

			Con[i].isEmpty = false;
			cout << "该联系人信息已删除" << endl << endl;
		}
		break;
	}
}

void Find() {//按姓名查找联系人4
	string one;
	cout << "请输入你要查找的联系人: ";
	cin >> one;
	for (int i = 0; i < 1000; i++) {
		if (one == Con[i].Name) {
			cout << "该联系人信息是：" << endl;
			cout << Con[i].Name << '\t';
			cout << Con[i].Sex << '\t';
			cout << Con[i].Age << '\t';
			cout << Con[i].Tel << '\t';
			cout << Con[i].Address << endl << endl;
		}
		else {
			cout << "没有该联系人! 请重新进入本页面输入。" << endl << endl;
		}
	}
	cout << "查找完毕！" << endl << endl;
}

void Update() {//按姓名修改联系人5
	string one;
	cout << "请输入您要修改的联系人：";
	cin >> one;
	for (int i = 0; i < 1000; i++) {
		if (Con[i].Name != one) {
			cout << "未查询到此人！请重新输入。" << endl;
		}
		else {
			cout << "以回车键/空格键为分隔，依次输入姓名、性别、年龄、电话、地址：" << endl;
			cin >> Con[i].Name;
			cin >> Con[i].Sex;
			cin >> Con[i].Age;
			cin >> Con[i].Tel;
			cin >> Con[i].Address;
		}
		break;
	}
	cout << "联系人信息已修改！" << endl << endl;
}

void Clear() {//清空联系人6
	for (int i = 0; i < 1000; i++) {
		Con[i].Name = '\0';
		Con[i].Sex = '\0';
		Con[i].Age = -1;
		Con[i].Tel = '\0';
		Con[i].Address = '\0';
		Con[i].isEmpty = false;
	}
	cout << "所有联系人信息已删除" << endl << endl;
}


int main() {


	while (true) {
		Menu();
		DO();

		cin >> i;
		if (i == 7) {
			break;
		}

		system("pause");
	}
}