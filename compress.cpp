#include <iostream> 
#include <vector> 
#include <cmath> 
#include<ctime>
#include<stdlib.h>
using namespace std; 

#define MAX 20


//随机生成测试数据
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

/*****************准备部分*****************/
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
/*****************准备部分*****************/

/*****************二进制快排部分*****************/

//二进制快排，先根据符号位将数据划分为两部分，然后对每一部分应用：
//先利用高位进行二进制划分（又分成两个子序列），然后再利用次高位进行递归划分
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
/*****************二进制快排部分*****************/

/*****************基数排序1部分*****************/
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
		memset(count,0,sizeof(int)*radix);//尼玛一顶要在下一次循环前，将计数器清零

		for(i=0;i<length;i++)
		{
			count[digit(a[i+left],index)]++;
		}
		for(i=1;i<radix;i++)
			count[i] += count[i-1];

		for(i=right;i>=left;i--)//要保证稳定性，故需要从后往前放置
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
	int radix = 2;//基数

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
/*****************基数排序1部分*****************/

/*****************基数排序2部分*****************/
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

	//d当运行到此处，count[0]已经变成0了，故下面递归调用的时候要注意了

//	radixMSD_core(a,left,left+count[0]-1,index+1);
	for(i=0;i<radix-1;i++)
		radixMSD_core(a,left+count[i],left+count[i+1]-1,index+1);

	radixMSD_core(a,left+count[i],right,index+1);//此时，i等于radix-1,即最后一部分的调用
}

void radixMSD(int a[],int left,int right)
{
	if(a == NULL || left >= right) return;
	int low  = left,high = right;
	int index = 0;
	int radix = 2;//基数

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
  
/*****************基数排序2部分*****************/


/*****************基数排序11-radix = 10部分*****************/
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
		memset(count,0,sizeof(int)*radix);//尼玛一顶要在下一次循环前，将计数器清零

		for(i=0;i<length;i++)
		{
			count[digit10(a[i+left],index)]++;
		}
		for(i=1;i<radix;i++)
			count[i] += count[i-1];

		for(i=right;i>=left;i--)//要保证稳定性，故需要从后往前放置
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
	int radix = 10;//基数

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
/*****************基数排序11-radix = 10部分*****************/


/*****************基数排序22-radix = 10部分*****************/
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

	//d当运行到此处，count[0]已经变成0了，故下面递归调用的时候要注意了

//	radixMSD_core(a,left,left+count[0]-1,index+1);
	for(i=0;i<radix-1;i++)
		radixMSD_core23(a,left+count[i],left+count[i+1]-1,index+1);

	radixMSD_core23(a,left+count[i],right,index+1);//此时，i等于radix-1,即最后一部分的调用
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

	//d当运行到此处，count[0]已经变成0了，故下面递归调用的时候要注意了

//	radixMSD_core(a,left,left+count[0]-1,index+1);
	for(i=0;i<radix-1;i++)
		radixMSD_core22(a,left+count[i],left+count[i+1]-1,index+1);

	radixMSD_core22(a,left+count[i],right,index+1);//此时，i等于radix-1,即最后一部分的调用
}

void radixMSD22(int a[],int left,int right)
{
	if(a == NULL || left >= right) return;
	int low  = left,high = right;
	int index = 0;
	int radix = 10;//基数

	while(low<high)
	{
		while(low<high && digit(a[low],index) == 1)low++;
		while(low<high && digit(a[high],index) == 0) high--;
		exch(a[low],a[high]);
	}
	if(digit(a[low],index) == 1) low++;
	radixMSD_core23(a,left,left+low-1,index);//负数部分取某一位的时候，先将其取绝对值，再取某一位的位数
						//这样排序的结果是降序的，故要进一步处理
	/*****************对于负数部分，因为排序的结果是降序的，故将其调整过来*****************/
	int i =left,j = left+low-1;
	while(i<j)
	{
		exch(a[i],a[j]);
		i++;j--;
	}
	/*****************对于负数部分，因为排序的结果是降序的，故将其调整过来*****************/
	radixMSD_core22(a,left+low,right,index);//整数部分，正常排序
}
/*****************基数排序22-radix = 10部分*****************/
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