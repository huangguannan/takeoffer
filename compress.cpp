#include <iostream> 
#include <vector> 
#include <cmath> 
#include<ctime>
#include<stdlib.h>
using namespace std; 

#define MAX 20


//������ɲ�������
void input(int num[])  
{  
    int i;  
      
    srand((unsigned)time(NULL));  
    for(i=1; i<MAX; i++)  
        num[i]=rand()%1000;        
} 

void show(int a[],int n)
{
	for(int i=0;i<n;i++)
		cout<<a[i]<<' ';
	cout<<endl;
}

/*****************׼������*****************/
const int intbitnum = sizeof(int)*8-1;
const int intbitnum10 = log10(pow(2,intbitnum+1))+1;

inline int digit(int a,int index)
{
	return (a>>(intbitnum-index) ) & 0x01;
}

inline int digit10(int a,int index)
{
	return (a/(int)pow(10,intbitnum10-index)) %10;
}

void exch(int &a,int &b)
{
	int temp = a;
	a = b;
	b = temp;
}
/*****************׼������*****************/

/*****************�����ƿ��Ų���*****************/

//�����ƿ��ţ��ȸ��ݷ���λ�����ݻ���Ϊ�����֣�Ȼ���ÿһ����Ӧ�ã�
//�����ø�λ���ж����ƻ��֣��ֳַ����������У���Ȼ�������ôθ�λ���еݹ黮��
void quickSortBase2(int a[],int left,int right,int index)
{
	
	if(left>=right || index > intbitnum) return;
	
	int low = left,high = right;
	while(low < high)
	{
		while(low<high && digit(a[low],index) == 0) low++;
		while(low<high && digit(a[high],index) == 1) high--;
		exch(a[low],a[high]);
	}
	if(digit(a[low],index) == 0 )low++;
	quickSortBase2(a,left,low-1, index+1);
	quickSortBase2(a,low, right,index+1);

}

void sortBase2(int a[],int left,int right)
{
	if(a == NULL || left >= right) return;
	int low = left,high = right;
	int index = 0;

	while(low < high)
	{
		while(low<high && digit(a[low],index) == 1) low++;
		while(low<high && digit(a[high],index) == 0) high--;
		exch(a[low],a[high]);
	}
	if(digit(a[low],index) == 1) low++;
	quickSortBase2(a,left,low-1,index+1);
	quickSortBase2(a,low,right,index+1);
}
/*****************�����ƿ��Ų���*****************/

/*****************��������1����*****************/
void radixLSD_core(int a[],int left,int right,int radix)
{
	if(left>=right) return;
	int length = right-left+1;
	int *aux = (int*)malloc(sizeof(int)*length);
	memset(aux,0,sizeof(int)*length);
	int *count = (int*)malloc(sizeof(int)*radix);
	memset(count,0,sizeof(int)*radix);

	int i =0;
	int index = intbitnum;

	for(index;index>0;index--)
	{
		memset(count,0,sizeof(int)*radix);//����һ��Ҫ����һ��ѭ��ǰ��������������

		for(i=0;i<length;i++)
		{
			count[digit(a[i+left],index)]++;
		}
		for(i=1;i<radix;i++)
			count[i] += count[i-1];

		for(i=right;i>=left;i--)//Ҫ��֤�ȶ��ԣ�����Ҫ�Ӻ���ǰ����
		{
			aux[count[digit(a[i],index)] -1 ] = a[i];
			count[digit(a[i],index)]--;
		}
		for(i=left;i<=right;i++)
		{
			a[i] = aux[i-left];
		}
	}
}


void radixLSD(int a[],int left,int right)
{
	if(a == NULL || left >= right) return;
	int low = left,high = right;
	int index = 0;
	int radix = 2;//����

	while(low < high)
	{
		while(low<high && digit(a[low],index) == 1) low++;
		while(low<high && digit(a[high],index) == 0) high--;
		exch(a[low],a[high]);
	}
	if(digit(a[low],index) == 1) low++;
	radixLSD_core(a,left,low-1,radix);
	radixLSD_core(a,low,right,radix);
}
/*****************��������1����*****************/

/*****************��������2����*****************/
void radixMSD_core(int a[],int left,int right,int index)
{
	if( left >= right || index > intbitnum) return;
	int length = right-left+1;
//	int index = 1;
	int radix = 2;
	int i = 0;
	int *aux = (int*)malloc(sizeof(int)*length);
	memset(aux,0,sizeof(int)*length);
	int *count =(int*)malloc(sizeof(int)*radix);
	memset(count,0,sizeof(int)*radix);

	for(i = left;i<=right;i++)
	{
		count[digit(a[i],index)]++;
	}
	for(i = 1;i<radix;i++)
	{
		count[i] += count[i-1];
	}

	for(i = right;i>=left;i--)
	{
		aux[count[digit(a[i],index)] - 1 ] = a[i];
		count[digit(a[i],index)]--;
	}
//	show(aux,MAX);

	for(i = left;i<=right;i++)
	{
		a[i] = aux[i-left];
	}
//	show(a,MAX);

	//d�����е��˴���count[0]�Ѿ����0�ˣ�������ݹ���õ�ʱ��Ҫע����

//	radixMSD_core(a,left,left+count[0]-1,index+1);
	for(i=0;i<radix-1;i++)
		radixMSD_core(a,left+count[i],left+count[i+1]-1,index+1);

	radixMSD_core(a,left+count[i],right,index+1);//��ʱ��i����radix-1,�����һ���ֵĵ���
}

void radixMSD(int a[],int left,int right)
{
	if(a == NULL || left >= right) return;
	int low  = left,high = right;
	int index = 0;
	int radix = 2;//����

	while(low<high)
	{
		while(low<high && digit(a[low],index) == 1)low++;
		while(low<high && digit(a[high],index) == 0) high--;
		exch(a[low],a[high]);
	}
	if(digit(a[low],index) == 1) low++;
	radixMSD_core(a,left,left+low-1,index+1);
	radixMSD_core(a,left+low,right,index+1);
}
  
/*****************��������2����*****************/


/*****************��������11-radix = 10����*****************/
void radixLSD_core11(int a[],int left,int right,int radix)
{
	if(left>=right) return;
	int length = right-left+1;
	int *aux = (int*)malloc(sizeof(int)*length);
	memset(aux,0,sizeof(int)*length);
	int *count = (int*)malloc(sizeof(int)*radix);
	memset(count,0,sizeof(int)*radix);

	int i =0;
	int index = intbitnum10;

	for(index;index>0;index--)
	{
		memset(count,0,sizeof(int)*radix);//����һ��Ҫ����һ��ѭ��ǰ��������������

		for(i=0;i<length;i++)
		{
			count[digit10(a[i+left],index)]++;
		}
		for(i=1;i<radix;i++)
			count[i] += count[i-1];

		for(i=right;i>=left;i--)//Ҫ��֤�ȶ��ԣ�����Ҫ�Ӻ���ǰ����
		{
			aux[count[digit10(a[i],index)] -1 ] = a[i];
			count[digit10(a[i],index)]--;
		}
		for(i=left;i<=right;i++)
		{
			a[i] = aux[i-left];
		}
	}
}


void radixLSD11(int a[],int left,int right)
{
	if(a == NULL || left >= right) return;
	int low = left,high = right;
	int index = 0;
	int radix = 10;//����

	while(low < high)
	{
		while(low<high && digit(a[low],index) == 1) low++;
		while(low<high && digit(a[high],index) == 0) high--;
		exch(a[low],a[high]);
	}
	if(digit(a[low],index) == 1) low++;
	radixLSD_core11(a,left,low-1,radix);
	radixLSD_core11(a,low,right,radix);
}
/*****************��������11-radix = 10����*****************/


/*****************��������22-radix = 10����*****************/
void radixMSD_core23(int a[],int left,int right,int index)
{
	if( left >= right || index > intbitnum10) return;
	int length = right-left+1;
//	int index = 1;
	int radix = 10;
	int i = 0;
	int *aux = (int*)malloc(sizeof(int)*length);
	memset(aux,0,sizeof(int)*length);
	int *count =(int*)malloc(sizeof(int)*radix);
	memset(count,0,sizeof(int)*radix);

	for(i = left;i<=right;i++)
	{
		count[digit10(-a[i],index)]++;
	}
	for(i = 1;i<radix;i++)
	{
		count[i] += count[i-1];
	}

	for(i = right;i>=left;i--)
	{
		aux[count[digit10(-a[i],index)] - 1 ] = a[i];
		count[digit10(-a[i],index)]--;
	}
//	show(aux,MAX);

	for(i = left;i<=right;i++)
	{
		a[i] = aux[i-left];
	}
//	show(a,MAX);

	//d�����е��˴���count[0]�Ѿ����0�ˣ�������ݹ���õ�ʱ��Ҫע����

//	radixMSD_core(a,left,left+count[0]-1,index+1);
	for(i=0;i<radix-1;i++)
		radixMSD_core23(a,left+count[i],left+count[i+1]-1,index+1);

	radixMSD_core23(a,left+count[i],right,index+1);//��ʱ��i����radix-1,�����һ���ֵĵ���
}

void radixMSD_core22(int a[],int left,int right,int index)
{
	if( left >= right || index > intbitnum10) return;
	int length = right-left+1;
//	int index = 1;
	int radix = 10;
	int i = 0;
	int *aux = (int*)malloc(sizeof(int)*length);
	memset(aux,0,sizeof(int)*length);
	int *count =(int*)malloc(sizeof(int)*radix);
	memset(count,0,sizeof(int)*radix);

	for(i = left;i<=right;i++)
	{
		count[digit10(a[i],index)]++;
	}
	for(i = 1;i<radix;i++)
	{
		count[i] += count[i-1];
	}

	for(i = right;i>=left;i--)
	{
		aux[count[digit10(a[i],index)] - 1 ] = a[i];
		count[digit10(a[i],index)]--;
	}
//	show(aux,MAX);

	for(i = left;i<=right;i++)
	{
		a[i] = aux[i-left];
	}
//	show(a,MAX);

	//d�����е��˴���count[0]�Ѿ����0�ˣ�������ݹ���õ�ʱ��Ҫע����

//	radixMSD_core(a,left,left+count[0]-1,index+1);
	for(i=0;i<radix-1;i++)
		radixMSD_core22(a,left+count[i],left+count[i+1]-1,index+1);

	radixMSD_core22(a,left+count[i],right,index+1);//��ʱ��i����radix-1,�����һ���ֵĵ���
}

void radixMSD22(int a[],int left,int right)
{
	if(a == NULL || left >= right) return;
	int low  = left,high = right;
	int index = 0;
	int radix = 10;//����

	while(low<high)
	{
		while(low<high && digit(a[low],index) == 1)low++;
		while(low<high && digit(a[high],index) == 0) high--;
		exch(a[low],a[high]);
	}
	if(digit(a[low],index) == 1) low++;
	radixMSD_core23(a,left,left+low-1,index);//��������ȡĳһλ��ʱ���Ƚ���ȡ����ֵ����ȡĳһλ��λ��
						//��������Ľ���ǽ���ģ���Ҫ��һ������
	/*****************���ڸ������֣���Ϊ����Ľ���ǽ���ģ��ʽ����������*****************/
	int i =left,j = left+low-1;
	while(i<j)
	{
		exch(a[i],a[j]);
		i++;j--;
	}
	/*****************���ڸ������֣���Ϊ����Ľ���ǽ���ģ��ʽ����������*****************/
	radixMSD_core22(a,left+low,right,index);//�������֣���������
}
/*****************��������22-radix = 10����*****************/
int main() 
{ 

	int a[MAX];//={17,19,14,12,18,16,20,1,3,5,7,9,2,4,6,8,10,11,13,15};// = {1,3,2,4,6,5,7,8,9,10,112,332,46,741,11,16,421};
	input(a) ;
	a[1] = -1;
	a[6] = -3;
	a[3] = -4;
	a[9] = -13;
	a[15] = -16;
	a[6] = -8;

	int n = sizeof(a)/sizeof(int);

	show(a,n);
	radixMSD22(a,0,n-1);
	show(a,n);


    return 0; 
}