#pragma once
#include<iostream>
#include<fstream>
using namespace std;
#include<map>
#include"globalFile.h"

class OrderFile
{
public:
	OrderFile();//���캯��
	void UpdateOrder();//����ԤԼ��¼
	map<int, map<string, string>>m_orderData;//key:ԤԼ���� value:ÿ��ԤԼ������Ϣ
	
	int m_Size;
};