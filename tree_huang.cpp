#include <iostream>
#include <queue>
#include <stack>
#include<iomanip>
//#include <fstream>

using namespace std;

int max(int a,int b)
{
	return a>b?a:b;
}

int min(int a,int b)
{
	return a<b?a:b;
}

struct TreeNode
{
	int val;
	TreeNode *lchild,*rchild;
	TreeNode(int x):val(x),lchild(NULL),rchild(NULL){}
	TreeNode(TreeNode *left,TreeNode *right):lchild(left),rchild(right) {}
};
/*******************************************************************/
TreeNode* createTree()
{
	int data;
	cin>>data;
	if(data == -1)
	{
		root = NULL;
	}
	else
	{
		root = new TreeNode(data);
		root->lchild = createTree();
		root->rchild = createTree();
	}

	return root;
}
/*******************************************************************/
//��������ķǵݹ�ʵ��
void inorderWithoutRecursion1(TreeNode *root)
{
	if(root == NULL)	return;
	TreeNode *p=root;
	stack<TreeNode*> s;
	
	while(!s.empty() || p)
	{
		//һֱ���������������±ߣ��߱����߱�����ڵ㵽ջ��
		while(p)
		{
			s.push(p);
			p = p->lchild;
		}
		//��pΪ��ʱ��˵���Ѿ��������������±ߣ���ʱ��Ҫ��ջ��
		if(!s.empty())
		{
			p = s.top();
			s.pop();
			cout<<setw(4)<<p->val;
			//��������������ʼ�µ�һ����������������ʱ�ݹ������ʵ�֣�
			p=p->rchild;
		}
	}//end of while
}

void inorderWithoutRecursion2(TreeNode *root)
{
	if(root == NULL)	return;
	TreeNode *p=root;
	stack<TreeNode*> s;
	
	while(!s.empty() || p)
	{
		if(p)
		{
			s.push(p);
			p=p->lchild;
		}
		else
		{
			p = s.top();
			s.pop();
			cout<<setw(4)<<p->val;
			//��������������ʼ�µ�һ����������������ʱ�ݹ������ʵ�֣�
			p=p->rchild;
		}
	}//end of while
}
/*******************************************************************/
//ǰ������ķǵݹ�ʵ��
void PreOrderWithoutRecursion1(TreeNode *root)
{
	if(root == NULL)	return;
	TreeNode *p=root;
	stack<TreeNode*> s;

	while(!s.empty() || p)
	{
		//�߱����ߴ�ӡ��������ջ�У��Ժ���Ҫ������Щ���ڵ����������
		while(p)
		{
			cout<<setw(4)<<p->val;
			s.push(p);
			p=p->lchild;
		}
		//��pΪ��ʱ��˵���������������������ˣ��ý�����������
		if(!s.empty())
		{
			p = s.top();
			s.pop();
			p=p->rchild;
		}
	}
	cout<<endl;
}

void PreOrderWithoutRecursion2(TreeNode *root)
{
	if(root == NULL)	return;
	TreeNode *p=root;
	stack<TreeNode*> s;

	while(!s.empty() || p)
	{
		if(p)
		{
			cout<<setw(4)<<p->val;
			s.push(p);
			p=p->lchild;
		}
		else
		{
			p = s.top();
			s.pop();
			p=p->rchild;
		}
	}
	cout<<endl;
}

void PreOrderWithoutRecursion3(TreeNode *root)
{
	if(root == NULL)	return;
	TreeNode *p=root;
	stack<TreeNode*> s;
	s.push(root);

	while(!s.empty())//ѭ������������ǰ���ֲ�һ��
	{
		//p��ѭ�������Ƿǿյ�
		cout<<setw(4)<<p->val;
		//ջ���ص㣺�Ƚ�������ȱ����ʵĸ��ڵ���������󱻷���
		if(p->rchild)
			s.push(p->rchild);//��ѹ������������Ϊ�������ڱ����Ĺ������Ѿ����ʹ���
		if(p->lchild)
			p = p->lchild;
		else
		{
			//�������������ˣ�����������
			p = s.top();
			s.pop();
		}
	}
	cout<<endl;
}


void PreOrderWithoutRecursion4(TreeNode *root)
{
	//���Ӧ�������������ͼ�ס�İ�
	if(root == NULL)	return;
	TreeNode *p=root;
	stack<TreeNode*> s;
	s.push(root);

	while(!s.empty())//ѭ������������ǰ���ֲ�һ��
	{
		p = s.top();
		s.pop();
		cout<<setw(4)<<p->val;

		if(p->rchild)
			s.push(p->rchild);
		if(p->lchild)
			s.push(p->lchild);
	}
	cout<<endl;
}
/*******************************************************************/
//��������ķǵݹ�ʵ��
void postOrderWithoutRecursion(TreeNode* root)
{
	if(root == NULL)	return;
	stack<TreeNode*> s;
	TreeNode *pcur,*pLastVisit;//��ǰ���ʽڵ㣬��һ�η��ʽڵ�
	pcur = root;
	pLastVisit = NULL;

	while(pcur)//�Ȱ�pcur�ƶ������������±�
	{
		s.push(pcur);
		pcur=pcur->lchild;
	}

	while(!s.empty())//�ߵ����pcur���ǿգ����Ѿ��������������Ͷˣ�������������������Ҳ��ĳ���������ӣ�
	{
		pcur=s.top();
		s.pop();
		if(pcur->rchild == NULL ||pcur->rchild == pLastVisit)//
		//���ڵ㱻���ʵ�ǰ�����������������������ѱ����ʹ�
		{
			cout<<setw(4)<<pcur->val;
			pLastVisit=pcur;//�޸���������ʵĽڵ�
		}
		else
		{
			s.push(pcur);//���ڵ��ٴ���ջ
			pcur=pcur->rchild;//�������������ҿɿ϶�������һ����Ϊ��

			while(pcur)
			{
				s.push(pcur);
				pcur=pcur->lchild;
			}
		}
	}
	cout<<endl;
}
/*******************************************************************/
//�������Ĳ�α���
void levelTraverse(TreeNode *root)
{
	if(root == NULL) return;
	queue<TreeNode*> q;
	TreeNode *p;
	q.push(root);

	while(!q.empty())
	{
		p=q.front();
		q.pop();
		cout<<setw(4)<<p->val;

		if(p->lchild) q.push(p->lchild);
		if(p->rchild) q.push(p->rchild);
	}

}

//bfs��levelTraverse��һ����
void bfs(TreeNode *root)
{
	if(root == NULL) return;
	queue<TreeNode*> q;
	TreeNode *p;
	q.push(root);

	while(!q.empty())
	{
		p=q.front();
		q.pop();
		cout<<setw(4)<<p->val;

		if(p->lchild) q.push(p->lchild);
		if(p->rchild) q.push(p->rchild);
	}

}
/*******************************************************************/
//dfs��ǰ������ķǵݹ�ʵ����һ����
void dfs(TreeNode *root)
{
	//���Ӧ�������������ͼ�ס�İ�
	if(root == NULL)	return;
	TreeNode *p=root;
	stack<TreeNode*> s;
	s.push(root);

	while(!s.empty())//ѭ������������ǰ���ֲ�һ��
	{
		p = s.top();
		s.pop();
		cout<<setw(4)<<p->val;

		if(p->rchild)
			s.push(p->rchild);
		if(p->lchild)
			s.push(p->lchild);
	}
	cout<<endl;
}
/*******************************************************************/
//�ݹ飬�ڶ����������в���ڵ�
void insertBST(TreeNode *&root,TreeNode* newNode)
{
	if(root == NULL) root = newNode;
	else if(newNode->val < root->val)
		insertBST(root->lchild,newNode);
	else if(newNode->val > root->val)
		insertBST(root->rchild,newNode);
}

bool searchBST(TreeNode *root,int target)
{
	if(root == NULL) return false;
	if(target < root->val)
		return searchBST(root->lchild,target);
	else if(target > root->val)
		return searchBST(root->rchild,target);
	else
		return true;
}

TreeNode* createBST()
{
	TreeNode *root = NULL;
	int data;

	while(cin>>data)
	{
		TreeNode *t=new TreeNode(data);
		insertBST(root,t);
	}
	return root;
}
/*******************************************************************/
//�������������������в���
TreeNode* searchBSTIterative(TreeNode *root,int val)
{
	TreeNode *p = root;

	while(p!=NULL)
	{
		if(val < p->val)
			p=p->lchild;
		else if(val > p->val)
			p=p->rchild;
		else
			return p;
	}

	return NULL;
}

bool insertBSTiterative(TreeNode *&root,int val)
{
	TreeNode *parent = NULL;
	TreeNode *pcur = root;

	while(pcur!=NULL)
	{
		if(val < pcur->val)
		{
			parent = pcur;
			pcur = pcur->lchild;
		}
		else if(val > pcur->val)
		{
			parent = pcur;
			pcur = pcur->rchild;
		}
		else
		{
			return false;
		}
	}//end of while

	TreeNode *newNode = new TreeNode(val);

	if(parent == NULL)
		root = newNode;
	else
	{
		if(val > parent->val)
			parent->rchild = newNode;
		else
			parent->lchild = newNode;
	}

	return true;
}
/*******************************************************************/
//��������ֵ����ӡƽ���������л��ڽ���������ֵ֮�������ֵ
void searchRangeInBSTHelper(TreeNode *root, vector<int> &result, int &low, int &high){
    if(root == NULL) return;

    if(root->val >= low && root->val <= high){
        searchRangeInBSTHelper(root->lchild, result, low, high);
        result.push_back(root->val);
        searchRangeInBSTHelper(root->rchild, result, low, high);
    }else if(root->val > high){
        searchRangeInBSTHelper(root->lchild, result, low, high);
    }else if(root->val < low){
        searchRangeInBSTHelper(root->rchild, result, low, high);
    }
}

vector<int> searchRangeInBST(TreeNode *root, int low, int high){
    vector<int> result;
    if(root == NULL) return result;

    searchRangeInBSTHelper(root, result, low, high);
    return result;
}
/*******************************************************************/
//�ҵ�һ������ֵ�����������ǰ���ͺ�̡�
//�����ֵ����BST�У��򷵻�����ֵ��һ�����ڸ�ֵ��һ��С�ڸ�ֵ
//�ݹ�ʵ��
void findPrevSuc(TreeNode *root,TreeNode *&prev,TreeNode *&suc,int  key)
{
	if(root == NULL) return;

	if(root->val == key)
	{
		if(root->lchild != NULL)
		{
			TreeNode *tmp = root->lchild;
			while(tmp->rchild != NULL)
				tmp=tmp->rchild;
			prev = tmp;
		}

		if(root->rchild != NULL)
		{
			TreeNode *tmp=root->rchild;
			while(tmp->lchild)
				tmp=tmp->lchild;
			suc=tmp;
		}
	}
	else if(root->val > key)
	{
		suc = root;
		findPrevSuc(root->lchild,prev,suc,key);
	}
	else
	{
		prev = root;
		findPrevSuc(root->rchild,prev,suc,key);
	}
}
/*******************************************************************/
bool delNode(TreeNode *&node)//�˴�����Ҫ����node �ڵ㣬���ô�����
{
	TreeNode *parent;
	if(node->lchild == NULL)
	{
		parent = node;
		node = node->rchild;
		free(parent);
	}
	else if(node->rchild == NULL)
	{
		parent = node;
		node = node->lchild;
		free(parent);
	}
	else//internal node
	{
		parent = node;
		TreeNode *tmp=node->lchild;
		while(tmp->rchild != NULL)
		{
			parent = tmp;//����parent
			tmp = tmp->rchild;
		}
		node->val = tmp->val;//�滻ԭ���ڵ��ֵ
		if(parent == node)//tmp�����֧��
		{
			parent->lchild = tmp->lchild;
			//��Ϊtmp��Ȼû��������������ֻ��Ҫ�����������ҵ���ȷ��λ���ϼ���
		}
		else//tmp���ҷ�֧��
		{
			parent->rchild=tmp->lchild;
		}
		free(tmp);
	}

	return true;
}

bool delBST(TreeNode *&root,int val)
{
	if(root == NULL) return false;

	if(val < root->val)
		return delBST(root->lchild,val);
	else if(val > root->val)
		return delBST(root->rchild,val);
	else
		return delNode(root);
}
/*******************************************************************/
bool isValid(TreeNode *root,int lower,int upper)
{
	if(root == NULL) return true;
	return (root->val > lower)&&(root->val < upper)
		&&isValid(root->lchild,lower,root->val)
		&&isValid(root->rchild,root->val,upper);
}

bool isValidBST(TreeNode *root)
{
	return isValid(root,INT_MIN,INT_MAX);
}
/*******************************************************************/
int isBalancedHelper(TreeNode *root,bool &is_balanced)
{
	if(root == NULL) return 0;
	if(!is_balanced) return 0;

	int lh=isBalancedHelper(root->lchild,is_balanced);
	int rh=isBalancedHelper(root->rchild,is_balanced);
	
	if(!is_balanced) return 0;//���������������жϳ��Ƿ�ƽ��
	is_balanced = abs(lh-rh)<=1;

	return max(lh,rh)+1;
}

bool isBalanced(TreeNode *root)
{
	bool is_balanced=true;
	isBalancedHelper(root,is_balanced);
	return is_balanced;
}
/******************************************************************/
int treeDepth(TreeNode *root)
{
	if(root == NULL) return 0;
	return max( treeDepth(root->lchild), treeDepth(root->rchild))+1;
}

int minDepth(TreeNode *root)
{
	if(root == NULL) return 0;
	int ld = minDepth(root->lchild);
	int rd = minDepth(root->rchild);
	if(ld == 0)
		return rd + 1;
	else if(rd == 0)
		return ld + 1;
	else
		return min(ld,rd)+1;
}

//������Ӧ�ú����������һ���İ�
int maxDepth(TreeNode *root)
{
	if(root ==  NULL) return 0;
	int ld = minDepth(root->lchild);
	int rd = minDepth(root->rchild);
	if(ld == 0)
		return rd + 1;
	else if(rd == 0)
		return ld + 1;
	else
		return max(ld,rd)+1;
}
/******************************************************************/
//�������ڵ������Ĺ������Ƚڵ�
bool isFather(TreeNode *f,TreeNode *s)
{
	if(f == NULL) return false;
	else if(f == s) return true;
	else return isFather(f->lchild,s)||isFather(f->rchild,s);
}

void commonAncestor(TreeNode *root,TreeNode *n1,TreeNode *n2,TreeNode *&ans)
{
	if(root == NULL || n1 == NULL || n2 == NULL) return;

	if(isFather(root,n1) && isFather(root,n2))
	{
		ans = root;
		commonAncestor(root->lchild,n1,n2,ans);
		commonAncestor(root->rchild,n1,n2,ans);
	}
}
/******************************************************************/

/******************************************************************/
bool isSameTree(TreeNode *r1,TreeNode *r2)
{
	if(r1 == NULL && r2 == NULL) return true;
	else if(r1 == NULL || r2 == NULL) return false;

	return (r1->val == r2->val)
		&& isSameTree(r1->lchild,r2->lchild)
		&& isSameTree(r1->rchild,r2->rchild);
}
/******************************************************************/
bool isSymmetricTree(TreeNode *L,TreeNode *R)
{
	if(L == NULL && R == NULL) return true;
	else if(L == NULL || R == NULL) return false;

	return L->val == R->val
		&& isSymmetricTree(L->lchild,R->rchild)
		&& isSymmetricTree(L->rchild,R->lchild);
}

bool isSymmetricTree(TreeNode *root)
{
	if(root == NULL) return true;
	else return isSymmetricTree(root->lchild,root->rchild);
}
/******************************************************************/
//�ƻ�ԭ������
TreeNode* getSymmetricTree(TreeNode *&root)
{
	if(root == NULL) return root;

	TreeNode *left = getSymmetricTree(root->lchild);
	TreeNode *right = getSymmetricTree(root->rchild);

	root->lchild = right;
	root->rchild = left;
	return root;
}

//���ƻ�ԭ������
TreeNode* getSymmetricTree2(TreeNode *root)
{
	if(root == NULL) return root;

	TreeNode *rootcopy = new TreeNode(root->val);
	rootcopy->lchild = getSymmetricTree2(root->rchild);
	rootcopy->rchild = getSymmetricTree2(root->lchild);

	return rootcopy;
}
/******************************************************************/
void destroyTree(TreeNode *root)
{
	if(root == NULL) return;
	destroyTree(root->lchild);
	destroyTree(root->rchild);

	delete root;
}
/******************************************************************/
///////////////////////////advanced//////////////////////////
//�ж��Ƿ�����ȫ������
bool isCompleteTree(TreeNode *root)
{
	if(root == NULL) return true;

	queue<TreeNode *> q;
	TreeNode *p = root;
	q.push(p);
	bool flag = false;

	while(!q.empty())
	{
		p = q.front();
		q.pop();

		//left
		if(p->lchild != NULL)
		{
			if(flag) return false;
			else q.push(p->lchild);
		}
		else
		{
			flag = true;//flag��ʾ����һ����λ��
			//����ڸýڵ��Ժ�ı����г��ַǿ�λ�����ʾ������ȫ������
		}

		//right
		if(p->rchild != NULL)
		{
			if(flag) return false;
			else q.push(p->rchild);
		}
		else
		{
			flag = true;
		}
	}
	return true;
}
/******************************************************************/
void flatten(TreeNode *root)
{
	if(root == NULL) return;

	flatten(root->lchild);
	flatten(root->rchild);

	//flatten process
	if(root->lchild != NULL)
	{
		TreeNode *tmp = root->lchild;

		while(tmp->rchild != NULL)
			tmp = tmp->rchild;

		tmp->rchild = root->rchild;
		root->rchild = root->lchild;
		root->lchild = NULL;
	}
}


//convert BST to double linked list
//����һ��BST������ת��Ϊ˫������left����ǰ�ڵ㣬right�����ڵ㡣
struct LeftRightNode
{
	TreeNode *left;//ָ��˫�������ͷ���
	TreeNode *right;//ָ��˫�������β���
	LeftRightNode(){}
	LeftRightNode(TreeNode *l, TreeNode *r):left(l), right(r){}
};

LeftRightNode convert(TreeNode *root)
{
	if (root == NULL)
	{
		return LeftRightNode(NULL, NULL);
	}
	
	LeftRightNode leftTree = convert(root->lchild);
	LeftRightNode rightTree = convert(root->rchild);
	
	root->lchild = leftTree.right;//���ڵ�����ߵ�˫��������������
	if (leftTree.right)
		leftTree.right->rchild = root;
	
	root->rchild = rightTree.left;//���ڵ����ұߵ�˫��������������
	if (rightTree.left)
		rightTree.left->lchild = root;
	
	TreeNode *leftNode = leftTree.left ? leftTree.left : root;
	TreeNode *rightNode = rightTree.right ? rightTree.right : root;
	return LeftRightNode(leftNode, rightNode);//����һ���ڵ㣬�ýڵ����ָ��ָ��˫�������ͷ��㣬
	//�ýڵ����ָ��ָ��˫�������β�ڵ�
}

TreeNode* convert2Doublelist(TreeNode *root)
{
	LeftRightNode ret = convert(root);
	return ret.left;
}
/******************************************************************/
//����ǰ���������������ؽ���
TreeNode* build(vector<int> &preorder,int pL,int pR,
				vector<int> &inorder,int iL,int iR)
{
	TreeNode *root;
	if(pL > pR || iL > iR) root = NULL;
	else
	{
		root = new TreeNode(preorder[pL]);
		int i;
		for(i=iL;i<=iR && inorder[i]!=root->val;++i)
			;
		root->lchild = build(preorder,pL+1,pL+i-iL,inorder,iL,i-1);
		root->rchild = build(preorder,pL+i-iL+1,pR,inorder,i+1,iR);
	}
	return root;
}

TreeNode* buildTree(vector<int> &preorder,vector<int> &inorder)
{
	return build(preorder,0,preorder.size()-1,
			inorder,0,inorder.size()-1);
}


//���ҵ����ڵ㣬Ȼ��ݹ�Ĺ�����������������
struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) 
{
	if(preorderSize == 0 || inorderSize == 0 || preorderSize != inorderSize)
        return NULL;
	
    struct TreeNode *root=(struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->val=preorder[0];
	
    int i=0,temp1=0,temp2=0;
    for(i;i<inorderSize;i++)//������������ҵ����ڵ㣬�����Ϊǰ��ͺ���������
    {
        if(inorder[i] == root->val)
		{
			temp1=i;
			break;
		}
    }
	temp2=preorderSize-temp1-1;
    root->lchild = buildTree(preorder+1, temp1,inorder,temp1);
    root->rchild = buildTree(preorder+temp1+1,temp2,inorder+temp1+1,temp2);
    
    return root;
}

/******************************************************************/
//��������ͺ�������ؽ���
TreeNode* build2(vector<int> &inorder,int iL,int iR,
				vector<int> &postorder,int pL,int pR)
{
	TreeNode *root;
	if(iL > iR || pL > pR) root = NULL;
	else
	{
		root = new TreeNode(postorder[pR]);
		int i;
		for(i=iL;i<=iR && inorder[i]!=root->val;++i)
			;
		root->lchild = build(inorder,iL,i-1,postorder,pL,i-iL+pL-1);
		root->rchild = build(inorder,i+1,iR,postorder,i-iL+pL,pR-1);
	}
	return root;
}
/******************************************************************/
//************************************************************
/*
 *  * 12. ��������нڵ�������룺getMaxDistanceRec
 *
 *  ��������������������룺
 *  ���붨��Ϊ�������ڵ��ߵ���Ŀ.
 *  �磺
 *     1
 *    / \
 *   2   3
 *        \
 *         4
 *   ���������붨��Ϊ2��4�ľ��룬Ϊ3.
 * ��������нڵ�������� ���������������Զ�������ڵ�֮��ľ��롣 (distance / diameter)
 * �ݹ�ⷨ��
 * ����ֵ��ƣ�
 * ����1. ��ȣ� 2. ��ǰ���������
 * (1) ��������������ȣ���������ȣ��������������������ȣ���������������������
 * (2) ��󳤶�Ϊ����֮�
 *    a. ͨ�����ڵ������Ϊ�������+2
 *    b. ������������
 *    c. ��������������
 *
 * (3)�ݹ��ʼ������
 *   ��root == null, depth = -1.maxDistance = -1;
 */
struct Result{
    int maxDist;
    int depth;
    Result(int dist = -1, int depth = -1) : maxDist(dist), depth(depth){}
};

Result getMaxDistHelper(TreeNode *root){
    Result res;
    if(root == NULL) return res;

    Result l = getMaxDistHelper(root->lchild);
    Result r = getMaxDistHelper(root->rchild);
    res.depth = max(l.depth, r.depth) + 1;//1.update depth

    int cross = l.depth + 1 + r.depth + 1;//����һ������·���������ҵ��������й�
    res.maxDist = max(cross, max(l.maxDist, r.maxDist));//2.update max dist
    return res;
}

int getMaxDist(TreeNode *root){
    return getMaxDistHelper(root).maxDist;
}
/******************************************************************/


int main()
{
//	TreeNode *root=createTree();
//	TreeNode* result = getSymmetricTree2(root);

	return 0;
}