#pragma once
#include<iostream>
#include<fstream>
using namespace std;
#include<map>
#include"globalFile.h"

class OrderFile
{
public:
	OrderFile();//构造函数
	void UpdateOrder();//更新预约记录
	map<int, map<string, string>>m_orderData;//key:预约数量 value:每条预约包含信息
	
	int m_Size;
};