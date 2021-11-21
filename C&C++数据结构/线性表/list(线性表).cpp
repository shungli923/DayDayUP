#include<iostream>

using namespace std;

const int MAXSIZE = 20;//线性表大小

typedef int position;//设置别名代表的当前位置
typedef struct LNode* List;//用List代替struct LNode*
struct LNode//结构体定义
{
	int Data[MAXSIZE];//线性表大小
	position last;
};

//初始化
List makeEmpty() {
	List L;
	L = (List)malloc(sizeof(struct LNode));//分配空间
	if (L) {//分配成功，设置数组长度的值
		L->last = -1;
	}
	return L;
}

//查找
position Find(int k, const List& L) {
	position i = 0;//从角标为0开始

	//超出数组长度或者匹配不成功则匹配下一位
	while (i <= L->last && L->Data[i] != k) {
		i++;
	}
	if (i > L->last) {
		return -1;//没找到，返回错误信息
	}
	else {
			return i;//返回位置信息
		}
}

//插入
bool Insert(const List& L, int pos, int k) {
	position i = pos;
	//MAXSIZE为总元素个数，当last=MAXSIZE-1时数组满
	if (L->last == MAXSIZE-1) {
		printf("线性表已满");
		return false;//无法插入返回
	}
	if (pos<0 || pos>MAXSIZE) {
		printf("插入位置不合法");
		return false;
	}
	for (int i = L->last;i >= pos;--i) {
		L->Data[i + 1] = L->Data[i];//向后顺位移动
	}
	L->Data[pos] = k;
	L->last++;
	return true;
}

//删除
bool Delete(const List& L, int pos) {
	if (pos<0 || pos>L->last) {
		printf("输入不合法");
		return false;
	}

	for (;pos + 1 < L->last;pos++) {
		L->Data[pos] = L->Data[pos + 1];
	}
	L->last--;
	return true;
}

//输出
void Print(const List& L) {
	for (int i = 0;i < L->last;++i) {
		cout << L->Data[i] << "   " << endl;
	}
}

//测试
int main() {
	struct LNode* list;
	list = makeEmpty();
	Insert(list, 0, 0);
	Insert(list, 1, 1);
	Insert(list, 2, 2);
	Insert(list, 3, 3);
	Insert(list, 4, 4);
	Insert(list, 5, 5);
	Print(list);
	int temp=Find(3, list);
	cout << temp << endl;
	Delete(list, 3);
	int temp1 = Find(3, list);
	cout << temp1 << endl;
	Print(list);
	delete list;
}