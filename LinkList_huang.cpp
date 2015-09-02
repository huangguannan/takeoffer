#include <iostream>
#include <queue>
#include <stack>
#include<iomanip>
#include<assert.h>
//#include <fstream>

using namespace std;
void swap(char &a,char &b)
{
	char temp = a;
	a = b;
	b = temp;
}

int max(int a,int b)
{
	return a>b?a:b;
}


struct ListNode
{
	int val;
	ListNode *next;
	ListNode(int x):val(x),next(NULL){}
};
/******************************************************/
ListNode* createList(int n)
{
	ListNode dummy(-1);
	ListNode *p=&dummy;
	for(int i=0;i<n;i++)
	{
		ListNode *t = new ListNode(i);
		p->next = t;
		p = p->next;
	}
	return dummy.next;
}
/******************************************************/
ListNode* insertAtHead(ListNode *head,int val)
{
	ListNode *newNode = new ListNode(val);
	newNode->next = head;
	return newNode;
}

ListNode* insertAtTail(ListNode *head,int val)
{
	ListNode dummy(-1);
	dummy.next = head;

	ListNode *p = &dummy;
	while(p->next != NULL)
	{
		p = p->next;
	}
	ListNode *newNode = new ListNode(val);
	p->next = newNode;
	return dummy.next;
}
/******************************************************/
ListNode* reverse(ListNode *head)
{
	ListNode *pre=NULL,*cur = head,*next = NULL;
	//只是简单的指针的交换
	while(cur != NULL)
	{
		next = cur->next;
		cur->next = pre;
		pre = cur;
		cur = next;
	}
	return pre;
}

//迭代，还是带哑元节点的好理解
//但是需要消耗空间，不是在原来的链表上
ListNode* reverseList(ListNode* head) {
    ListNode node(-1);
    ListNode* p=head;
    ListNode *pn=&node;
    
    while(p)
    {
        ListNode* temp = new ListNode(p->val);
        temp->next = pn->next;
        pn->next = temp;
        p=p->next;
    }
    
    return node.next;
}

//递归方式
ListNode* reverse_recur(ListNode *head)
{
	//如果链表为空或者链表中只有一个元素
	if(head == NULL || head->next == NULL)
	{
		return head;
	}
	else
	{
		ListNode *newHead = reverse_recur(head->next);////先反转后面的链表 
		head->next->next = head;//再将当前节点设置为其然来后面节点的后续节点 
		head->next = NULL;
		return newHead;
	}
}
/******************************************************/
//删除节点， 如果该节点不是尾节点的话，可以在常数时间内删除
void delNode(ListNode *&head,ListNode *del)
{
	if(head == NULL || del == NULL) return;

	if(del->next != NULL)
	{//如果被删除节点不是尾节点的话，可以将其值更新为其后继结点的值，
		//然后删除其后继结点
		del->val = del->next->val;
		ListNode *tmp=del->next;
		del->next = del->next->next;
		delete tmp;
	}
	else//如果被删除节点是尾节点，则只能通过从头到尾遍历找到
		//尾节点的前继，然后再删除尾节点
	{
		ListNode dummy(-1);
		dummy.next = head;
		ListNode *prev=&dummy;
		while(prev!=NULL && prev->next!=del)//prev!=NULL用于判断是否到达链表的尾部
			prev = prev->next;

		if(prev == NULL) return;//prev == NULL，表示到达链表的尾部，但是没有找到del指针
		prev->next = del->next;
		delete del;
		head = dummy.next;
	}
}
/******************************************************/
ListNode* kthNode(ListNode *head,int k)
{
	if(head == NULL) return NULL;

	while(--k>0 &&head!=NULL)
		head = head->next;

	return head;
}
/******************************************************/
ListNode* lastkth(ListNode *head,int k)
{
	if(head == NULL) return NULL;
	int cnt = 1;
	ListNode *fast = head,*slow = head;

	while(fast!=NULL)
	{
		fast = fast->next;
		cnt++;
		if(cnt>k)
		{
			slow=slow->next;
		}
	}
	if(cnt<k) return NULL;
	else return slow;
}
/******************************************************/
ListNode* findMid(ListNode *head)
{
	if(head == NULL || head->next == NULL) return head;

//	ListNode *slow=head,*fast = head->next;//两个都可以
//	while(fast != NULL && fast->next !=NULL)
	ListNode *slow=head,*fast = head;
	while(fast->next != NULL && fast->next->next !=NULL)
	{
		fast = fast->next->next;
		slow = slow->next;
	}
	return slow;
}


/******************************************************/
//合并两个有序的单链表
ListNode* merge(ListNode *h1,ListNode *h2)
{
	ListNode dummy(-1);
	ListNode *p=&dummy;
                   
	while(h1!=NULL && h2!=NULL)
	{
		if(h1->val < h2->val)
		{
			p->next = h1;
			h1=h1->next;
		}
		else
		{
			p->next = h2;
			h2 = h2->next;
		}
		p = p->next;
	}
	if(h1 != NULL) p->next = h1;
	if(h2 != NULL) p->next = h2;
	return dummy.next;
}

//利用快慢指针找到中间节点，然后二分归并排序单链表
ListNode* sortList(ListNode *head)
{
	if(head == NULL || head->next == NULL) return head;

	ListNode *slow = head,*fast=head->next;
	while(fast!=NULL && fast->next != NULL)
	{
		fast = fast->next->next;
		slow = slow->next;
	}
	ListNode *mid = slow;

	ListNode *h1=head,*h2=mid->next;
	mid->next = NULL;
	h1 = sortList(h1);
	h2 = sortList(h2);
	return merge(h1,h2);
}
/******************************************************/
bool hasCycle(ListNode *head)
{
	if(head == NULL) return false;

	ListNode *slow=head,*fast=head;
	do
	{
		if(fast == NULL || fast->next == NULL)
			return false;
		fast = fast->next->next;
		slow = slow->next;
	}while(fast!=slow);
	
	return true;
}


//设从链表头到环入口点距离为a，从环入口点到第一次相遇点距离为b，从相遇点再到环入口点距离为c，即环的长度为
//(b+c),整个链表的长度为a+b+c,再设第一次相遇时，慢指针走了s步，则快指针走了2s步，则有等式s=a+b;
//2s=s+n(b+c) ==>a+b=s=n(b+c)==>a=(n-1)(b+c)+c.即从相遇点慢指针和头指针（或重新设定一个指针p等于头指针）
//每次移动一步，则当头指针移动到环入口点时，慢指针必然也移动到环入口点
//即当p和slow再次相遇时的点就是环的入口点。
ListNode* detectCycle(ListNode *head)
{
	if(head == NULL) return NULL;

	ListNode *slow = head,*fast = head;//注意此处与求链表的中间节点不同，因为我们在上面的推导中，是假设慢指针走了s步，则快指针走了2s步，
										//故初始化时，只能将slow和fast初始化为相同，才能满足此条件
	do
	{
		if(fast == NULL || fast->next == NULL)
			return NULL;
		fast = fast->next->next;
		slow = slow->next;
	}while(fast!=slow);

	fast = head；
	
	while(fast != slow)
	{
		fast = fast->next;
		slow = slow->next;
	}
	return fast;
}


/******************************************************/
void printList(ListNode *head){
    while(head != NULL){
        cout<<head->val <<" ";
        head = head->next;
    }
    cout<<endl;
}
/******************************************************/

int main()
{
	ListNode *h = createList(8);
   // ListNode *nh = insertAtHead(h, 100);
    printList(h);
   // ListNode *nh2 = insertAtTail(nh, 200);
   // printList(nh2);
    ListNode *p=findMid(h);
	cout<<p->val<<endl;

    //printList(p);


    return 0;
}