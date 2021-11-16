#include"workerManager.h"
#include"boss.h"
#include"manager.h"
#include"employee.h"

WorkerManager::WorkerManager() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//�ļ����������
	if (!ifs.is_open()) {
		cout << "�ļ�������" << endl << endl;
		this->m_EmpNum = 0;//��ʼ������
		this->m_EmpArray = NULL;//��ʼ������
		this->m_fileIsEmpty = true;

		ifs.close();
		return;
	}

	//�ļ����ڵ�û�м�¼��Ϣ
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "�ļ�Ϊ��" << endl << endl;
		this->m_EmpNum = 0;//��ʼ������
		this->m_EmpArray = NULL;//��ʼ������
		this->m_fileIsEmpty = true;

		ifs.close();
		return;
	}

	//��������Ա������
	int num = this->getEmpNum();
	/* cout << "ְ������Ϊ��" << num << " ��" << endl;//***������ʾ����ְ������** */
	this->m_EmpNum = num;

	//��Ա�������Թ�������Ա����Ϣ
	this->m_EmpArray = new Worker*[this->m_EmpNum];//���ٿռ�
	this->initEmp();//��ʼ��Ա�����ó�Ա�����¼Ա����Ϣ

	//*****�����������ְ����Ϣ*****
	/*for (int i = 0; i < this->m_EmpNum; ++i) {
		cout << "ְ����ţ�" << this->m_EmpArray[i]->m_Id << "  "
			<< "ְ��������" << this->m_EmpArray[i]->m_Name << "  "
			<< "ְ����λ��" << this->m_EmpArray[i]->m_Dept << "  "<< endl;
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
	cout << "***********      ��ӭʹ��ְ������ϵͳ      ***********" << endl;
	cout << "*   1----�������ְ����Ϣ                            *" << endl;
	cout << "*   2----��ʾ����ְ����Ϣ                            *" << endl;
	cout << "*   3----ɾ��ְ����Ϣ�����ձ��ɾ����                *" << endl;
	cout << "*   4----����ְ����Ϣ�����ձ���޸ģ�                *" << endl;
	cout << "*   5----����ְ�������ձ�Ż����������ң�            *" << endl;
	cout << "*   6----��ְ�������������������û�ָ��)         *" << endl;
	cout << "*   7----���ְ����Ϣ�����ǰ���ٴ�ȷ�ϣ���ֹ��ɾ��  *" << endl;
	cout << "*   0----�˳���ǰ����ϵͳ                            *" << endl;
	cout << "******************************************************" << endl;
	cout << endl;
}

void WorkerManager::exitSystem() {
	cout << "��ӭ�´�ʹ��" << endl;
	exit(0);
}

void WorkerManager::addEmp() {
	int addnum = 0;
	cout << "����������ְ��������" << endl;
	cin >> addnum;

	if (addnum > 0) {
		int newSize = this->m_EmpNum + addnum;//�����¿ռ��С
		Worker** newSpace = new Worker*[newSize];

		if (this->m_EmpArray != NULL) {//��ԭ�ռ��ڵ����ݷ����¿ռ�
			for (int i = 0; i < this->m_EmpNum; ++i) {
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		for (int i = 0; i < addnum; ++i) {//�������������
			int id;
			string name;
			int dpt_id;

			cout << "�����" << i + 1 << "����ְ�����" << endl;
			cin >> id;
			cout << "�����" << i + 1 << "����ְ������" << endl;
			cin >> name;
			cout << "��ѡ���ְ����λ��" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> dpt_id;

			Worker* worker = NULL;
			switch (dpt_id)
			{
			case 1://��ְͨ��
				worker = new Employee(id, name, dpt_id);
				break;
			case 2://����
				worker = new Manager(id, name, dpt_id);
				break;
			case 3://�ϰ�
				worker = new Boss(id, name, dpt_id);
			default:
				break;
			}

			newSpace[this->m_EmpNum + i] = worker;//��ְ������ְ������������
		}
		delete[] this->m_EmpArray;//������һ����������

		this->m_EmpArray = newSpace;//���ڲ���Ա�����µ�ְ����������
		this->m_EmpNum = newSize;//���ڲ���Ա��¼�µ�ְ��������

		cout << "��ӳɹ� " << addnum << " ����ְ��" << endl;

		this->save();//����ְ����Ϣ���ļ���
		this->m_fileIsEmpty = false;//ְ�������ļ��ǿ�
	}
	else {
		cout << "��������" << endl;
	}

	system("pause");
	system("cls");//�����Ļ���ݻص��ϼ�Ŀ¼
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

	int num=0;//��¼Ա����Ϣ

	//���ж�ȡ�ļ�
	int id;
	string name;
	int dId;
	//ÿ����һ��ְ��������1
	while (ifs >> id && ifs >> name && ifs >> dId) {
		num++;
	}

	ifs.close();
	return num;
}

void WorkerManager::initEmp() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//���¶�ȡ����Ϣ
	int id;
	string name;
	int dId;

	int index = 0;//��¼�Ѷ�ȡԱ������

	while (ifs >> id && ifs >> name && ifs >> dId) {
		Worker* worker = NULL;
		//���ݲ�ͬ���ŵ�id������ְͬ������
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
		cout << "�ļ������ڻ�Ϊ��" << endl;
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
	//����ֵ��Ϊ-1���򲻴��ڸ�ְ��
	return ret;
}

void WorkerManager::delEmp() {
	if (this->m_fileIsEmpty) {
		cout << "û��ְ����¼" << endl;
	}
	else {
		cout << "���뽫Ҫɾ����ְ���ı�ţ�" << endl;
		int id = 0;
		cin >> id;
		int get = this->isExist(id);
		if (get != -1) {
			//ְ�����ڣ�����λ��Ϊget��ֵ
			for (int i = get; i < this->m_EmpNum; ++i) {
				//����ǰ��һλ
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;

			this->save();//���µ��ļ���
			cout << "ɾ���ɹ���" << endl;
		}
		else {
			cout << "ɾ��ʧ�ܣ��ñ��ְ�������ڣ������²�����" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::modEmp() {
	if (this->m_fileIsEmpty) {
		cout << "û��ְ����¼" << endl;
	}
	else {
		cout << "�������޸�ְ����ţ�" << endl;
		int id;
		cin >> id;
		int ret = this->isExist(id);
		
		if (ret != -1) {
			delete this->m_EmpArray[ret];

			int newId = 0;
			string newName = "";
			int newdId = 0;

			cout << "�鵽��ţ�" << id << "Ա������������ְ���ţ�" << endl;
			cin >> newId;

			cout << "��������������" << endl;
			cin >> newName;

			cout << "�������¸�λ��" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
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

			this->m_EmpArray[ret] = worker;//�������ݵ�������
			
			cout << "�޸ĳɹ�" << endl;

			this->save();//�������ļ���
		}
		else {
			cout << "û�д�ְ��" << endl;	
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::findEmp() {
	if (this->m_fileIsEmpty) {
		cout << "û��ְ����¼" << endl;
	}
	else {
		cout << "��������ҷ�ʽ��" << endl;
		cout << "1:��ְ����Ų���" << endl;
		cout << "2:��ְ����������" << endl;

		int select = 0;
		cin >> select;

		if (select == 1) {
			int id;
			cout << "������Ҫ��ѯ��ְ����:";
			cin >> id;

			int ret = this->isExist(id);
			if (ret != -1) {
				cout << "���ҳɹ�����ְ����Ϣ��" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else {
				cout << "û�в��ҵ�����" << endl;
			}
		}
		else if (select == 2) {
			string name;
			cout << "������Ҫ����ְ����������";
			cin >> name;

			bool hasfind = false;
			for (int i = 0; i < this->m_EmpNum; ++i) {
				if (this->m_EmpArray[i]->m_Name == name) {
					cout << "���ҳɹ���" << endl;
					cout << "ְ����ϢΪ: " << endl;
					this->m_EmpArray[i]->showInfo();
					hasfind = true;
				}
			}
			if (!hasfind) {
				cout << "û��ѯ����ְ��" << endl;
			}
		}
		else {
			cout << "������������²�����" << endl;
		}
	}

	system("pause");
	system("cls");
}

void WorkerManager::sortEmp() {
	if (this->m_fileIsEmpty) {
		cout << "û��ְ����Ϣ" << endl;
		system("pause");
		system("cls");
	}
	else {

		cout << "ѡ��ְ������ʽ��" << endl;
		cout << "1:��ְ�������������" << endl;
		cout << "2:��ְ����Ž�������" << endl;
		int select = 0;
		cin >> select;

		for (int i = 0; i < this->m_EmpNum; ++i) {
			int key = i;
			for (int j = i + 1; j < this->m_EmpNum; ++j) {
				if (select == 1) {//����
					if (this->m_EmpArray[key]->m_Id > this->m_EmpArray[j]->m_Id) {
						key = j;
					}
				}
				else {//����
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
		cout << "����ɹ����������Ϊ��" << endl;
		this->save();
		this->showEmp();
	}
}

void WorkerManager::cleanFile() {
	cout << "ȷ�����ְ����Ϣ��" << endl;
	cout << "1:ȷ��" << endl;
	cout << "2:����" << endl;

	int select = 0;
	cin >> select;

	if (select == 1) {
		//��ģʽios::trunc�������ɾ���ļ������´���
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		if (this->m_EmpArray!=NULL) {//ɾ��ÿ��ְ������
			for (int i = 0; i < this->m_EmpNum; ++i) {
				if (this->m_EmpArray[i] != NULL) {
					delete this->m_EmpArray[i];
				}
			}
			this->m_EmpNum = 0;
			delete[] this->m_EmpArray;//ɾ����������ָ��
			this->m_EmpArray = NULL;
			this->m_fileIsEmpty = true;
		}
		cout << "��ճɹ�" << endl;

	}
	system("pause");
	system("cls");
}