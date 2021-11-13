#pragma once
#include<string>
using namespace std;

struct Contacts
{
	string Name;
	string Sex;
	int Age;
	string Tel;
	string Address;
	bool isEmpty = false;
};

Contacts Con[1000];//最多1000人

void Insert();//添加联系人
void Display();//显示联系人详细信息
void Delete();//删除联系人
void Find();//查找联系人
void Update();//修改联系人
void Clear();//清空联系人
void Quit();//退出通讯录
