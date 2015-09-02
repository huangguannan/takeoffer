#include<iostream>
#include<vector>
#include<deque>

using namespace std;

//求最大公约数
void swap(int &a,int &b)
{
	int temp = a;
	a = b;
	b = temp;
}
int gcd_recur(int a,int b)
{
	if(a<b)
		swap(a,b);
	if(b == 0)
		return a;
	return gcd_recur(b,a%b);
}

int gcd(int a,int b)
{
	if(a<b)
		swap(a,b);
	while(b != 0)
	{
		int c = a%b;
		a = b;
		b = c;
	}
	return a;
}

//用于求n个数的最大公约数
int gcd(int a[],int n)
{
	if(a==NULL || n<1)return 0;
	deque<int> q;
	for(int i=0;i<n;i++)
		q.push_back(a[i]);
	//if(q.empty())return 0;
	while(q.size()>1)
	{
		int a = q.front();
		q.pop_front();
		int b = q.front();
		q.pop_front();
		q.push_back(gcd(a,b));
	}
	return q.front();
}
//求最小公倍数
int lcm(int a,int b)
{
	return a*b/gcd(a,b);
}
//用于求n个数的最小公倍数
int lcm(int a[],int n)
{
	if(a==NULL || n<1)return 0;
	vector<int> v;
	for(int i=0;i<n;i++)
		v.push_back(a[i]);
	while(v.size()>1)
	{
		int a = v.back();
		v.pop_back();
		int b = v.back();
		v.pop_back();
		v.push_back(lcm(a,b));s
	}
	return v.front();
}


int main()
{
	int a[]={2,3,4,5,6,7,8};
	int n = sizeof(a)/sizeof(int);
	cout<<gcd(a[0],a[1])<<endl;
	cout<<gcd(a[0],a[2])<<endl;
	cout<<gcd(a[1],a[4])<<endl;
	cout<<gcd(a,n)<<endl;
	cout<<lcm(a[0],a[1])<<endl;
	cout<<lcm(a[0],a[2])<<endl;
	cout<<lcm(a[1],a[4])<<endl;
	cout<<lcm(a[1],a[3])<<endl;
	cout<<lcm(a[5],a[6])<<endl;
	cout<<lcm(a,n)<<endl;
	return 0;
}