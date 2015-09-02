// ConsoleApplication3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

using namespace std;
#define MAX 20
#define M 5

#define bitsword 32
#define bitsbyte 8
#define bytesword 4
#define R (1<<bitsbyte) 
//R��ʾһ���ֽ��ܱ�ʾ�Ķ��������ĸ���
#define digit(A,B) ((A>>(31-B)) & (0x01))

void exch(int& a,int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

//������ɲ�������
void input(int num[])  
{  
    int i;  
      
    srand((unsigned)time(NULL));  
    for(i=1; i<MAX; i++)  
        num[i]=rand()%1000;        
} 

/////////////////////////////////////////////////////////////
//�����ƿ�������
/*�ȶ����ֵ����λ���п��Ż��֣�Ȼ��Դθ�λ���п��Ż��֣���������32λ�������32�εݹ黮�ֺ󣬼���*/
void quicksortB(int a[],int left,int right,int w)
{
	int i = left,j = right;
	if( j <= i || w > 31) return;//w>32����������
	int temp1 = -1,temp2 = -1;

	while(i < j )
	{
		while((i<j) && (temp1 = digit(a[i],w)) == 0) i++;
		while((i<j) && (temp2 = digit(a[j],w)) == 1 ) j--;
		exch(a[i],a[j]);
	}
	if(digit(a[j],w) == 0) j++;//������ȵ���һλ�Ƿ�Ϊ0����Ϊ0��Ӧ���仮�ֵ�ǰ��һ���������У�����Ӧ���仮�ֵ���һ����������
	quicksortB(a,left,j-1,w+1);
	quicksortB(a,j,right,w+1);
}

void sort(int a[],int left,int right)
{
	int i = left,j = right,w = 0;
	int temp1 = -1,temp2 = -1;
	while(i < j )//��Ϊ���������ֵ����λΪ����λ���ʶ�����н������⴦��Ϊ1���Ǹ�������С��Ϊ0��
	{
		while((i<j) && (temp1 = digit(a[i],w)) == 1) i++;
		while((i<j) && (temp2 = digit(a[j],w)) == 0 ) j--;
		exch(a[i],a[j]);
	}
	if(digit(a[j],w) == 1) j++;
	quicksortB(a,left,j-1,w+1);
	quicksortB(a,j,right,w+1);
}
/////////////////////////////////////////////////////////////
//�����ȶԷ���λ��һ�����֣�Ȼ������������зֱ���ú��ĵĻ�������
//Ҫ��ʹ�õ������㷨�������ȶ��ģ������������
void radixLSD_core(int a[],int left,int right)
{
	int* aux = (int*)malloc((right-left+1)*sizeof(int));
	memset(aux,0,(right-left+1)*sizeof(int));
	int i,j,w,count[3];//ÿһλֻ��0��1����ѡ�񣬹ʶ���count��2+1��
	for(w=31;w>=0;w--)//w������������ĵ�wλ������߱��Ϊ0��ʼ��
		//��λ����һ��ѭ��
	{
		for(j = 0;j <= 2;j++ ) count[j] = 0;
		for(i = left;i <= right;i++)
			count[digit(a[i],w)+1]++;
		for(j=1;j<3;j++)
			count[j] += count[j-1];
		for(i = left;i<=right;i++)
			aux[count[digit(a[i],w)]++] = a[i];
		for(i = left;i <= right;i++)
			a[i] = aux[i-left];
	}
	free(aux);
}

void radixLSD(int a[],int left,int right)
{
	int i = left,j = right,w = 0;
	int temp1 = -1,temp2 = -1;
	while(i < j )//��Ϊ���������ֵ����λΪ����λ���ʶ�����н������⴦��Ϊ1���Ǹ�������С��Ϊ0��
	{
		while((i<j) && (temp1 = digit(a[i],w)) == 1) i++;
		while((i<j) && (temp2 = digit(a[j],w)) == 0 ) j--;
		exch(a[i],a[j]);
	}
	if(digit(a[j],w) == 1) j++;
	radixLSD_core(a,left,j-1);
	radixLSD_core(a,j,right);
}
/////////////////////////////////////////////////////////////
void insertion(int a[],int left,int right)
{
	
	int i=0,j=0;
	int temp = 0;
	for(i = left+1;i<=right;i++)
	{
		j = i-1;
		temp = a[i];
		while(j >= left && a[j] > temp)
		{
			a[j+1] = a[j];
			j--;
		}
		a[j+1] = temp;
	}
	
}
void radixMSD_core(int a[],int left,int right,int w)
{
	int* aux = (int*)malloc((right-left+1)*sizeof(int));
	memset(aux,0,(right-left+1)*sizeof(int));

	int i,j,count[3];//R=2,3=R+1
	if(w > 31) return;
	if(right- left <= M)//��ҪԤ����M
	{
		insertion(a,left,right);
		return;
	}
	for(j=0;j<=2;j++) count[j] = 0;
	for(i = left;i<=right;i++)
		count[digit(a[i],w)+1]++;
	for(j=1;j<3;j++)
		count[j] += count[j-1];
	for(i = left;i<=right;i++)
		aux[count[digit(a[i],w)]++] = a[i];

	for(i = left;i<=right;i++) 
		a[i] = aux[i-left];
	
	radixMSD_core(a,left,left+count[0]-1,w+1);
	for(j=0;j<2;j++)//Ӧ��Ϊj<R-1
		radixMSD_core(a,left+count[j],left+count[j+1]-1,w+1);
	
	free(aux);

}

void radixMSD(int a[],int left,int right)
{
	int i = left,j = right,w = 0;
	int temp1 = -1,temp2 = -1;
	while(i < j )//��Ϊ���������ֵ����λΪ����λ���ʶ�����н������⴦��Ϊ1���Ǹ�������С��Ϊ0��
	{
		while((i<j) && (temp1 = digit(a[i],w)) == 1) i++;
		while((i<j) && (temp2 = digit(a[j],w)) == 0 ) j--;
		exch(a[i],a[j]);
	}
	if(digit(a[j],w) == 1) j++;
	radixMSD_core(a,left,j-1,w+1);
	radixMSD_core(a,j,right,w+1);
}
/////////////////////////////////////////////////////////////

void show(int a[],int n)
{
	for(int i=0;i<n;i++)
		cout<<a[i]<<' ';
	cout<<endl;
}
int main()
{
	int a[MAX];// = {1,3,2,4,6,5,7,8,9,10,112,332,46,741,11,16,421};
	input(a) ;
	int n = sizeof(a)/sizeof(int);

	show(a,n);
	radixMSD(a,0,n-1);
	show(a,n);
	return 0;
}

