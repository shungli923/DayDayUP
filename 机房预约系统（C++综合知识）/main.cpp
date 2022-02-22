#include<iostream>
#include<fstream>
using namespace std;
#include"globalFile.h"
#include"Identity.h"
#include"Student.h"
#include"Teacher.h"
#include"Manager.h"

//��¼����
void LoginIn(string Filename,int type);//����1�������ļ�����  ����2���������� 1��ѧ���� 2����ʦ�� 3������Ա��
void managerMenu(Identity* &manager);//�������Ա�Ӳ˵�
void studentMenu(Identity*& student);//����ѧ��ԤԼ�Ӳ˵�
void teacherMenu(Identity*& teacher);//�����ʦԤԼ�Ӳ˵�

int main()
{
	int select = 0;

	while (true)
	{
		cout << "\t============ ��ӭ�������ԤԼϵͳ ============" << endl;
		cout << endl << "�������������" << endl;
		cout << "\t\t-----------------------------\n";
		cout << "\t\t|                           |\n";
		cout << "\t\t|       1��ѧ������         |\n";
		cout << "\t\t|                           |\n";
		cout << "\t\t|       2����    ʦ         |\n";
		cout << "\t\t|                           |\n";
		cout << "\t\t|       3���� �� Ա         |\n";
		cout << "\t\t|                           |\n";
		cout << "\t\t|       0����    ��         |\n";
		cout << "\t\t|                           |\n";
		cout << "\t\t-----------------------------\n";

		cout << "����������ѡ��";
		cin >> select;//�����û�ѡ��

		switch (select)
		{
		case 1://ѧ���������
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2://��ʦ���
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3://���������
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0://�˳�ϵͳ
			cout << "��ӭ�´�ʹ��" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "��������������ѡ��" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	return 0;
	system("pause");
}

void LoginIn(string Filename, int type)//����1�������ļ�����  ����2���������� 1��ѧ���� 2����ʦ�� 3������Ա��
{
	Identity* person = nullptr;

	ifstream ifs;
	ifs.open(Filename, ios::in);

	//�ļ������ڵ����
	if (!ifs.is_open())
	{
		cout << "�ļ������ڣ�" << endl;
		ifs.close();
		return;
	}

	int id = 0;
	string name;
	string pwd;

	if (type == 1)
	{
		cout << "����������ѧ�ţ�" << endl;
		cin >> id;
	}
	else if (type == 2)
	{
		cout << "����������ְ���ţ�" << endl;
		cin >> id;
	}

	cout << "�������û�����" << endl;
	cin >> name;

	cout << "���������룺" << endl;
	cin >> pwd;

	if (type == 1)
	{
		//ѧ����¼��֤
		int Fid;
		string fName;
		string fPwd;
		
		while (ifs >> Fid && ifs >> fName && ifs >> fPwd)
		{
			if (id == Fid && name == fName && pwd == fPwd)
			{
				cout << "ѧ����֤��¼�ɹ���" << endl;
				system("pause");
				system("cls");
				person = new Student(id, name, pwd);
				//ѧ�����Ӳ˵�����
				studentMenu(person);
				return;
			}
		}
	}
	else if (type == 2)
	{
		//��ʦ��¼��֤
		int Fid;
		string fName;
		string fPwd;

		while (ifs >> Fid && ifs >> fName && ifs >> fPwd)
		{
			if (id == Fid && name == fName && pwd == fPwd)
			{
				cout << "��ʦ��֤��¼�ɹ���" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				//��ʦ���Ӳ˵�����
				teacherMenu(person);
				return;
			}
		}
	}
	else if (type == 3)
	{
		//����Ա��¼��֤
		string fName;
		string fPwd;

		while (ifs >> fName && ifs >> fPwd)
		{
			if (name == fName && pwd == fPwd)
			{
				cout << "����Ա��֤��¼�ɹ���" << endl;
				system("pause");
				system("cls");
				person = new Manager(name, pwd);
				//����Ա�����Ӳ˵�
				managerMenu(person);
				return;
			}
		}
	}

	cout << "��֤��¼ʧ�ܣ�" << endl;

	system("pause");
	system("cls");
	return;
}

void teacherMenu(Identity*& teacher)
{
	while (true)
	{
		//��ʦ�˵�
		teacher->operMenu();

		Teacher* tea = (Teacher*)teacher;
		int select = 0;
		cin >> select;

		if (select == 1)tea->showAllOrder();//�鿴����ԤԼ
		else if (select == 2)tea->validOrder();//���ԤԼ
		else
		{
			delete teacher;
			cout << "ע���ɹ�" << endl;

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
		//ѧ���˵�
		student->operMenu();

		Student* stu = (Student*)student;
		int select = 0;

		cin >> select;

		if (select == 1)stu->applyOrder();//����ԤԼ
		else if (select == 2)stu->showMyOrder();//�鿴�ҵ�ԤԼ
		else if (select == 3)stu->showAllOrder();//�鿴ȫ��ԤԼ
		else if (select == 4)stu->cancelOrder();//ȡ��ԤԼ
		else
		{
			delete student;
			cout << "ע���ɹ���" << endl;

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
		//���ù���Ա�Ӳ˵�
		manager->operMenu();

		Manager* man = (Manager*)manager;
		int select;

		cin >> select;

		if (select == 1)man->addPerson();//����˺�
		else if (select==2)man->showPerson();//�鿴�˺�
		else if (select==3)man->showComputer();//�鿴����
		else if (select == 4)man->cleanFile();//���ԤԼ
		else
		{
			delete manager;
			cout << "ע���ɹ�" << endl;

			system("pause");
			system("cls");

			return;
		}
	}
}