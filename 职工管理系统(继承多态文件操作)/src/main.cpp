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
		//չʾ�˵�
		wm.showMenu();
		cout << "����������ѡ��"; 
		cin >> choice;

		switch (choice)
		{
		case 0://�˳���ǰ����ϵͳ
			wm.exitSystem();
			break;
		case 1://���ְ��(�������ְ��������Ϣ¼�뵽�ļ��У�ְ����ϢΪ��ְ����ţ����������ű��
			wm.addEmp();
			break;
		case 2://��ʾ����ְ����Ϣ)
			wm.showEmp();
			break;
		case 3://ɾ��ְ����Ϣ�����ձ��ɾ����
			wm.delEmp();
			break;
		case 4://����ְ����Ϣ�����ձ���޸ģ�
			wm.modEmp();
			break;
		case 5://����ְ�������ձ�Ż����������ң�
			wm.findEmp();
			break;
		case 6://��ְ�������������������û�ָ��)
			wm.sortEmp();
			break;
		case 7://���ְ����Ϣ�����ǰ���ٴ�ȷ�ϣ���ֹ��ɾ��
			wm.cleanFile();
			break;
		default:
			system("cls");
			break;
		}
	}
	return 0;
}