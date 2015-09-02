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
//中序遍历的非递归实现
void inorderWithoutRecursion1(TreeNode *root)
{
	if(root == NULL)	return;
	TreeNode *p=root;
	stack<TreeNode*> s;
	
	while(!s.empty() || p)
	{
		//一直遍历到左子树最下边，边遍历边保存根节点到栈中
		while(p)
		{
			s.push(p);
			p = p->lchild;
		}
		//当p为空时，说明已经到达左子树最下边，这时需要出栈了
		if(!s.empty())
		{
			p = s.top();
			s.pop();
			cout<<setw(4)<<p->val;
			//进入右子树，开始新的一轮左子树遍历（这时递归的自我实现）
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
			//进入右子树，开始新的一轮左子树遍历（这时递归的自我实现）
			p=p->rchild;
		}
	}//end of while
}
/*******************************************************************/
//前序遍历的非递归实现
void PreOrderWithoutRecursion1(TreeNode *root)
{
	if(root == NULL)	return;
	TreeNode *p=root;
	stack<TreeNode*> s;

	while(!s.empty() || p)
	{
		//边遍历边打印，并存入栈中，以后需要借助这些根节点进入右子树
		while(p)
		{
			cout<<setw(4)<<p->val;
			s.push(p);
			p=p->lchild;
		}
		//当p为空时，说明根和左子树都遍历完了，该进入右子树了
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

	while(!s.empty())//循环结束条件和前两种不一样
	{
		//p在循环中总是非空的
		cout<<setw(4)<<p->val;
		//栈的特点：先进后出，先被访问的根节点的右子树后被访问
		if(p->rchild)
			s.push(p->rchild);//仅压入右子树，因为左子树在遍历的过程中已经访问过了
		if(p->lchild)
			p = p->lchild;
		else
		{
			//左子树访问完了，访问右子树
			p = s.top();
			s.pop();
		}
	}
	cout<<endl;
}


void PreOrderWithoutRecursion4(TreeNode *root)
{
	//这个应该是最容易理解和记住的吧
	if(root == NULL)	return;
	TreeNode *p=root;
	stack<TreeNode*> s;
	s.push(root);

	while(!s.empty())//循环结束条件和前两种不一样
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
//后序遍历的非递归实现
void postOrderWithoutRecursion(TreeNode* root)
{
	if(root == NULL)	return;
	stack<TreeNode*> s;
	TreeNode *pcur,*pLastVisit;//当前访问节点，上一次访问节点
	pcur = root;
	pLastVisit = NULL;

	while(pcur)//先把pcur移动到左子树最下边
	{
		s.push(pcur);
		pcur=pcur->lchild;
	}

	while(!s.empty())//走到这里，pcur都是空，并已经遍历到左子树低端（看成扩充二叉树，则空也是某棵树的左孩子）
	{
		pcur=s.top();
		s.pop();
		if(pcur->rchild == NULL ||pcur->rchild == pLastVisit)//
		//根节点被访问的前提是无右子树，或右子树已被访问过
		{
			cout<<setw(4)<<pcur->val;
			pLastVisit=pcur;//修改最近被访问的节点
		}
		else
		{
			s.push(pcur);//根节点再次入栈
			pcur=pcur->rchild;//进入右子树，且可肯定右子树一定不为空

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
//二叉树的层次遍历
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

//bfs和levelTraverse是一样的
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
//dfs和前序遍历的非递归实现是一样的
void dfs(TreeNode *root)
{
	//这个应该是最容易理解和记住的吧
	if(root == NULL)	return;
	TreeNode *p=root;
	stack<TreeNode*> s;
	s.push(root);

	while(!s.empty())//循环结束条件和前两种不一样
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
//递归，在二叉搜索树中插入节点
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
//迭代的在搜索二叉树中查找
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
//给定两个值，打印平衡搜索树中基于介于这两个值之间的所有值
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
//找到一个给定值的中序遍历的前驱和后继。
//如果该值不在BST中，则返回两个值，一个大于该值，一个小于该值
//递归实现
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
bool delNode(TreeNode *&node)//此处必须要更改node 节点，故用传引用
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
			parent = tmp;//更新parent
			tmp = tmp->rchild;
		}
		node->val = tmp->val;//替换原来节点的值
		if(parent == node)//tmp在左分支上
		{
			parent->lchild = tmp->lchild;
			//因为tmp必然没有右子树，所以只需要将其左子树挂到正确的位置上即可
		}
		else//tmp在右分支上
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
	
	if(!is_balanced) return 0;//在以上两步已能判断出是否平衡
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

//最大深度应该和树的深度是一样的吧
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
//找两个节点的最近的公共祖先节点
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
//破坏原来的树
TreeNode* getSymmetricTree(TreeNode *&root)
{
	if(root == NULL) return root;

	TreeNode *left = getSymmetricTree(root->lchild);
	TreeNode *right = getSymmetricTree(root->rchild);

	root->lchild = right;
	root->rchild = left;
	return root;
}

//不破坏原来的树
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
//判断是否是完全二叉树
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
			flag = true;//flag表示出现一个空位，
			//如果在该节点以后的遍历中出现非空位，则表示不是完全二叉树
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
//给出一棵BST，将其转换为双向链表，left保存前节点，right保存后节点。
struct LeftRightNode
{
	TreeNode *left;//指向双向链表的头结点
	TreeNode *right;//指向双向链表的尾结点
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
	
	root->lchild = leftTree.right;//将节点与左边的双向链表链接起来
	if (leftTree.right)
		leftTree.right->rchild = root;
	
	root->rchild = rightTree.left;//将节点与右边的双向链表链接起来
	if (rightTree.left)
		rightTree.left->lchild = root;
	
	TreeNode *leftNode = leftTree.left ? leftTree.left : root;
	TreeNode *rightNode = rightTree.right ? rightTree.right : root;
	return LeftRightNode(leftNode, rightNode);//返回一个节点，该节点的左指针指向双向链表的头结点，
	//该节点的右指针指向双向链表的尾节点
}

TreeNode* convert2Doublelist(TreeNode *root)
{
	LeftRightNode ret = convert(root);
	return ret.left;
}
/******************************************************************/
//利用前序遍历和中序遍历重建树
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


//先找到根节点，然后递归的构建左子树和右子树
struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) 
{
	if(preorderSize == 0 || inorderSize == 0 || preorderSize != inorderSize)
        return NULL;
	
    struct TreeNode *root=(struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->val=preorder[0];
	
    int i=0,temp1=0,temp2=0;
    for(i;i<inorderSize;i++)//在中序遍历中找到根节点，将其分为前序和后序两部分
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
//利用中序和后序遍历重建树
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
 *  * 12. 求二叉树中节点的最大距离：getMaxDistanceRec
 *
 *  首先我们来定义这个距离：
 *  距离定义为：两个节点间边的数目.
 *  如：
 *     1
 *    / \
 *   2   3
 *        \
 *         4
 *   这里最大距离定义为2，4的距离，为3.
 * 求二叉树中节点的最大距离 即二叉树中相距最远的两个节点之间的距离。 (distance / diameter)
 * 递归解法：
 * 返回值设计：
 * 返回1. 深度， 2. 当前树的最长距离
 * (1) 计算左子树的深度，右子树深度，左子树独立的链条长度，右子树独立的链条长度
 * (2) 最大长度为三者之最：
 *    a. 通过根节点的链，为左右深度+2
 *    b. 左子树独立链
 *    c. 右子树独立链。
 *
 * (3)递归初始条件：
 *   当root == null, depth = -1.maxDistance = -1;
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

    int cross = l.depth + 1 + r.depth + 1;//对于一个跨点的路径，跟左右的最大深度有关
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