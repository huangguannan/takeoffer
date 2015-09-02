#include <iostream>
//#include <hash_map>
#include <queue>
#include <set>
#include <list>
using namespace std;

struct Node
{
	char symbol;
	int weight;
	Node* left;
	Node* right;
	Node(int w = 0, char s = '\0') :symbol(s), weight(w), left(0), right(0){}
};

struct Node_comparator
{
	bool operator()(const Node* a, const Node* b)
	{
		return !!(a->weight > b->weight);
	}
};

typedef priority_queue<Node*, vector<Node*>, Node_comparator> Forest;
Node* huffman(Forest& f);

void encode(Forest& f);
void encode(Node* n, list<char> li=list<char>());

Node* huffman(Forest& f)
{
	while (f.size() > 1)
	{
		Node* const n1 = f.top(); f.pop();
		cout << n1->weight << endl;
		Node* const n2 = f.top(); f.pop();
		cout << n2->weight << endl;
		Node* nf = new Node(n1->weight + n2->weight);
		nf->left = (n1->weight < n2->weight) ? n2 : n1;
		nf->right = (n1->weight < n2->weight) ? n1 : n2;
		f.push(nf);
	}
	return f.top();
}

void encode(Forest& f)
{
	encode(huffman(f));
}

void encode(Node* n, list<char> li)//list<char> li具有缺省参数，而缺省参数只需要放在函数声明中就可以了
									//在有函数声明的情况下，函数定义不需要说明缺省参数
									//在没有函数声明的情况下，函数定义需要加缺省参数
{
	if (n == 0) return;
	if (n->symbol != '\0')//构造的新节点的字符都是0，所以只编码外部节点
	{
		for (list<char>::iterator it=li.begin();it!=li.end();it++)
		{
			cout << *it;
		}
		cout << ": " << n->symbol << endl;
		return;
	}
	list<char> l = list<char>(li);
	l.push_back('0');
	li.push_back('1');
	encode(n->left, l);
	encode(n->right, li);
}

int main()
{
	return 0;
}