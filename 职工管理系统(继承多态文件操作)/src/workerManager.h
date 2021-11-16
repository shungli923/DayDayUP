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
	
	void showMenu();//չʾ�˵�
	void exitSystem();//�˳�ϵͳ
	void addEmp();//���ְ��
	void save();//�������ļ���
	int getEmpNum();//��ȡְ������
	void initEmp();//��ʼ���Ѵ���Ա��
	void showEmp();//��ʾְ����Ϣ
	int isExist(int id);//�ж�ְ���Ƿ���ڣ�����ţ�
	void delEmp();//ɾ��ְ��
	void modEmp();//�޸�ְ��
	void findEmp();//����ְ��
	void sortEmp();//����ְ��
	void cleanFile();//���ְ����Ϣ
	
private:
	int m_EmpNum;//ְ������
	Worker** m_EmpArray;//���ְ����Ϣ������
	bool m_fileIsEmpty;//��־�ļ��Ƿ�Ϊ��
};
 