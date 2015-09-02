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
	//ֻ�Ǽ򵥵�ָ��Ľ���
	while(cur != NULL)
	{
		next = cur->next;
		cur->next = pre;
		pre = cur;
		cur = next;
	}
	return pre;
}

//���������Ǵ���Ԫ�ڵ�ĺ����
//������Ҫ���Ŀռ䣬������ԭ����������
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

//�ݹ鷽ʽ
ListNode* reverse_recur(ListNode *head)
{
	//�������Ϊ�ջ���������ֻ��һ��Ԫ��
	if(head == NULL || head->next == NULL)
	{
		return head;
	}
	else
	{
		ListNode *newHead = reverse_recur(head->next);////�ȷ�ת��������� 
		head->next->next = head;//�ٽ���ǰ�ڵ�����Ϊ��Ȼ������ڵ�ĺ����ڵ� 
		head->next = NULL;
		return newHead;
	}
}
/******************************************************/
//ɾ���ڵ㣬 ����ýڵ㲻��β�ڵ�Ļ��������ڳ���ʱ����ɾ��
void delNode(ListNode *&head,ListNode *del)
{
	if(head == NULL || del == NULL) return;

	if(del->next != NULL)
	{//�����ɾ���ڵ㲻��β�ڵ�Ļ������Խ���ֵ����Ϊ���̽���ֵ��
		//Ȼ��ɾ�����̽��
		del->val = del->next->val;
		ListNode *tmp=del->next;
		del->next = del->next->next;
		delete tmp;
	}
	else//�����ɾ���ڵ���β�ڵ㣬��ֻ��ͨ����ͷ��β�����ҵ�
		//β�ڵ��ǰ�̣�Ȼ����ɾ��β�ڵ�
	{
		ListNode dummy(-1);
		dummy.next = head;
		ListNode *prev=&dummy;
		while(prev!=NULL && prev->next!=del)//prev!=NULL�����ж��Ƿ񵽴������β��
			prev = prev->next;

		if(prev == NULL) return;//prev == NULL����ʾ���������β��������û���ҵ�delָ��
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

//	ListNode *slow=head,*fast = head->next;//����������
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
//�ϲ���������ĵ�����
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

//���ÿ���ָ���ҵ��м�ڵ㣬Ȼ����ֹ鲢��������
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


//�������ͷ������ڵ����Ϊa���ӻ���ڵ㵽��һ�����������Ϊb�����������ٵ�����ڵ����Ϊc�������ĳ���Ϊ
//(b+c),��������ĳ���Ϊa+b+c,�����һ������ʱ����ָ������s�������ָ������2s�������е�ʽs=a+b;
//2s=s+n(b+c) ==>a+b=s=n(b+c)==>a=(n-1)(b+c)+c.������������ָ���ͷָ�루�������趨һ��ָ��p����ͷָ�룩
//ÿ���ƶ�һ������ͷָ���ƶ�������ڵ�ʱ����ָ���ȻҲ�ƶ�������ڵ�
//����p��slow�ٴ�����ʱ�ĵ���ǻ�����ڵ㡣
ListNode* detectCycle(ListNode *head)
{
	if(head == NULL) return NULL;

	ListNode *slow = head,*fast = head;//ע��˴�����������м�ڵ㲻ͬ����Ϊ������������Ƶ��У��Ǽ�����ָ������s�������ָ������2s����
										//�ʳ�ʼ��ʱ��ֻ�ܽ�slow��fast��ʼ��Ϊ��ͬ���������������
	do
	{
		if(fast == NULL || fast->next == NULL)
			return NULL;
		fast = fast->next->next;
		slow = slow->next;
	}while(fast!=slow);

	fast = head��
	
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