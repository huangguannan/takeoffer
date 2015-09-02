#include<iostream>
#include<stdio.h>
//#include<ctype.h>
#include<iomanip>
#include<stack>
#include<vector>
#include<deque>
#include<map>
#include<string>
#include<algorithm>

using namespace std;

/*斐波那契数的动态规划实现*/

int func(int i)
{
	if(array[i]!=-1)	return array[i];
	if(i==0)	return 0;
	if(i==1)	return 1;
	array[i]=func(i-1)+func(i-2);
	return array[i];
}

typedef struct item
{
	int size;
	int val;
}item;

int known[18];
item itemknow[18];
item a[5];


/*0-1背包问题的自顶向下的动态规划实现*/
int knap(int m)
{
	if(known[m]!=-1)	return known[m];
	int max=0,i=0,space=0,imax=0,t=0;
	for(i=0;i<5;i++)
	{
		if((space=m-a[i].size)>=0)
		{
			if((t=knap(space)+a[i].val)>max)
			{
				max=t;
				imax = i;
			}
		}
	}
	known[m] = max;
	itemknow[m] = a[imax];
	return max;


	int i=0;
	for(i=0;i<18;i++)
	{
		known[i] = -1;
		itemknow[i].size=INT_MAX;
		itemknow[i].val=0;
				
	}
	int b[5]={3,4,7,8,9};
	int c[5]={4,5,10,11,13};	
	
	for(i=0;i<5;i++)
	{
		a[i].size = b[i];
		a[i].val = c[i];
	}

	int h=knap(17);
	cout<<h<<endl;

	int k=17;
	while(k>0)
	{
		cout<<itemknow[k].size<<'\t';
		k=k-itemknow[k].size;
	}
	cout<<endl;
	k=17;
	while(k>0)
	{
		cout<<itemknow[k].val<<'\t';
		k=k-itemknow[k].size;
	}
	cout<<endl;

}


int func(int n,int* known)
{
	if(known[n] != -1)	return known[n];
	int t=0;
	if(n==0)	return 0;
	if(n==1)	return 1;
	if(n==2)	return 2;

		known[n]=func(n-1,known)+func(n-2,known);

	return known[n];
}

int climbStairs(int n) 
{
	int *known=(int*)malloc(sizeof(int)*(n+1));
	int i=0;
	for(i=0;i<n+1;i++)
	{
		known[i]=-1;
	}
	return func(n,known);

}

int func2(int* nums,int numsSize,int *known)
{
	if(known[numsSize] != -1)	return known[numsSize];
	if(numsSize == 0)	return 0;
	if(numsSize == 1)	return known[1]=nums[0];
	if(numsSize == 2)	return known[2]=nums[0]>nums[1]?nums[0]:nums[1];

	int temp1=func2(nums,numsSize-1,known);
	int temp2=func2(nums,numsSize-2,known);

	known[numsSize] = temp1 > (temp2+nums[numsSize-1])?temp1:temp2+nums[numsSize-1];

	return known[numsSize];
}

int rob(int* nums, int numsSize) 
{
    int *known=(int*)malloc(sizeof(int)*(numsSize+1));
	int i=0;
	for(i=0;i<numsSize+1;i++)
	{
		known[i]=-1;
	}
	return func2(nums,numsSize,known);
}

int main()
{
	int nums[]={3,8,2,4};
	int numsSize=sizeof(nums)/sizeof(int);
	int num=rob(nums,numsSize);
	cout<<num<<endl;
	return 0;
}


