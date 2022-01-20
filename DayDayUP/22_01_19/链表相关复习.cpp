struct ListNode
{
	int val;
	ListNode* next;
	ListNode(int x) :val(x), next(nullptr) {}
};

ListNode* removeElement_01(ListNode* head, int val)
{
	//删除头节点
	while (head != nullptr && head->val == val)
	{
		ListNode* tmp = head;
		head = head->next;
		delete tmp;
	}

	//删除非头节点
	ListNode* cur = head;
	while (cur != nullptr && cur->next != nullptr)
	{
		if (cur->next->val == val)
		{
			ListNode* tmp = cur->next;
			cur->next = cur->next->next;
			delete tmp;
		}
		else {
			cur = cur->next;
		}
	}
	return head;
}


ListNode* removeElement_02(ListNode* head, int val)
{
	ListNode* dummyHead = new ListNode(0);//设置虚拟头节点
	dummyHead->next = head;
	ListNode* cur = dummyHead;
	while (cur->next != nullptr)
	{
		if (cur->next->val == val)
		{
			ListNode* tmp = cur->next;
			cur->next = cur->next->next;
			delete tmp;
		}
		else {
			cur = cur->next;
		}
	}
	head = dummyHead->next;
	delete dummyHead;
	return head;
}

/*———————————————————————————————————————————*/
//4.3链表6个基本操作
class myLinkedList
{
public:
	//定义链表结构体
	struct LinkedNode
	{
		int val;
		LinkedNode* next;
		LinkedNode(int val) :val(val), next(next) {}
	};

	myLinkedList()
	{
		_size = 0;
		_dummyHead = new LinkedNode(0);
	}

	//获取第index个节点的数值
	int get(int index)
	{
		if (index > (_size - 1) && index < 0)
			return -1;

		LinkedNode* cur = _dummyHead->next;
		while (index--)
		{
			cur = cur->next;
		}
		return cur->val;
	}

	//在链表前面插入一个节点
	void addAtHead(int val)
	{
		LinkedNode* newNode = new LinkedNode(val);
		newNode->next = _dummyHead->next;
		_dummyHead->next = newNode;
		_size++;
	}

	//在链表后面添加一个节点
	void addAtTail(int val)
	{
		LinkedNode* newNode = new LinkedNode(val);
		LinkedNode* cur = _dummyHead;
		while (cur->next != nullptr)
		{
			cur = cur->next;
		}
		cur->next = newNode;
		_size++;
	}

	//在index之前插入一个新节点
	void addAtIndex(int index, int val)
	{
		if (index > _size - 1 && index < 0)
			return;
		LinkedNode* cur = _dummyHead;
		LinkedNode* newNode = new LinkedNode(val);
		while (index--)
			cur = cur->next;
		newNode->next = cur->next;
		cur->next = newNode;
		_size++;
	}

	//删除第index个节点
	void deleteAtIndex(int index)
	{
		if (index > (_size - 1) && index < 0)
			return;
		LinkedNode* cur = _dummyHead;
		while (index--)
		{
			cur = cur->next;
		}
		LinkedNode* tmp = cur->next;
		cur->next = cur->next->next;
		delete tmp;
		_size--;
	}

	//打印链表
	void printLinkedList()
	{
		LinkedNode* cur = _dummyHead;
		while (cur->next != nullptr)
		{
			cout << cur->next->val << ' ';
			cur = cur->next;
		}
		cout << endl;
	}

private:
	int _size;
	LinkedNode* _dummyHead;
};

/*———————————————————————————————————————————*/
//反转链表01双指针法
LinkedNode* reverseList(LinkedNode* head)
{
	LinkedNode* tmp;
	LinkedNode* pre = nullptr;
	LinkedNode* cur = head;
	while (cur)
	{
		tmp = cur->next;
		cur->next = pre;

		pre = cur;
		cur = tmp;
	}
	return pre;//pre最终成为头节点
}

/*———————————————————————————————————————————*/
//反转链表02递归法
LinkedNode* reverseNode(LinkedNode* pre, LinkedNode* cur)
{
	if (cur == nullptr) return pre;
	LinkedNode* tmp = cur->next;
	cur->next = pre;
	reverseNode(cur, tmp);

}

LinkedNode* reverseList(LinkedNode* head)
{
	LinkedNode* pre = nullptr;
	LinkedNode* cur = head;
	reverseNode(nullptr, head);
}

/*———————————————————————————————————————————*/
//删除倒数第n个节点
LinkedNode* removeNthFromEnd(LinkedNode* head, int n)
{
	LinkedNode* dummyHead = new LinkedNode(0);
	dummyHead->next = head;
	LinkedNode* fast = dummyHead;
	LinkedNode* slow = dummyHead;
	while (n-- && fast != nullptr)
	{
		fast = fast->next;
	}
	fast = fast->next;
	while (fast!=nullptr)
	{
		fast = fast->next;
		slow = slow->next;
	}
	LinkedNode* tmp = slow->next;
	slow->next = slow->next->next;
	delete tmp;
	return dummyHead->next;
}

/*———————————————————————————————————————————*/
//4.6环形链表
LinkedNode* detectCycle(LinkedNode* head)
{
	LinkedNode* fast = head;
	LinkedNode* slow = head;
	while (fast!=nullptr&&fast->next!=nullptr)
	{
		fast = fast->next->next;
		slow = slow->next;
	}
	if (fast == slow)
	{
		LinkedNode* index1 = head;
		LinkedNode* index2 = fast;
		while (index1 != index2)
		{
			index1 = index1->next;
			index2 = index2->next;
		}
		return index2;
	}
	return nullptr;
}