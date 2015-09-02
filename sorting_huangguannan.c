#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<stack>
#include<ctype.h>
#include<string>
#include<vector>
#include<algorithm>
#include<math.h>

#include<map>

using namespace std;


//************************************************************
/*快速排序的划分算法*/
int partition(int *a,int left,int right)
/*交换数组data[left...high]的记录，使支点记录到位，并返回其所在位置
此时，在它之前（后）的记录均不大（小）于它*/
{
	int low = left,high = right;
	int pivotkey = a[low];//以数组的第一个元素作为支点记录（元素）

	while(low < high)//从表的两端交替地向中间扫描
	{
		while(low < high && a[high]>=pivotkey)	high--;
			a[low] = a[high];//将比支点记录小的交换到低端
		while(low < high && a[low] <= pivotkey)	low++;
			a[high] = a[low];//将比支点记录大的交换到高端

	}//当循环结束时，low == high

	a[low] = pivotkey;//支点记录到位
	return low;//返回支点记录所在位置
}
//************************************************************



//************************************************************
/*快速排序递归算法*/
/*递归形式的快排序
对数组data[]中的子序列data[left]~data[high]做快速排序*/
void quick_sort(int *a,int left,int right)
{
	if(a == NULL )	return;//显式返回
	int pivotloc;
	if(left < right)//if返回假，则隐式返回
	{                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
	
		pivotloc = partition(a,left,right);//将表一分为二
		quick_sort(a,left,pivotloc-1);//对低子表递归排序
		quick_sort(a,pivotloc+1,right);//对高子表递归排序
	}
}
//************************************************************


//************************************************************
//non recursive,left,right分别表示数组的第一个和最后一个元素的下标
void quick_sort2(int *a, int left, int right)
{
	if(a == NULL)	return;
	stack<int>	s;
	int low = left,high = right;
	int pivotloc;
	if(low < high)//如果if不满足，说明只有一个元素，则隐式返回
	{
		pivotloc=partition(a,low,high);//将表一分为二
		if(low<pivotloc-1)//如果低子表有两个以上的元素，则将低子表的第一个元素的下标和最后一个元素的下标入栈
		{
			s.push(low);
			s.push(pivotloc-1);
		}
		if(pivotloc+1<high)//如果高子表有两个以上的元素，则将高子表的第一个元素的下标和最后一个元素的下标入栈
		{
			s.push(pivotloc+1);
			s.push(high);
		}
		
		while(!s.empty())
		{
			high = s.top();
			s.pop();
			low = s.top();
			s.pop();
			
			pivotloc=partition(a,low,high);
			if(low<pivotloc-1)
			{
				s.push(low);
				s.push(pivotloc-1);
			}
			if(pivotloc+1<high)
			{
				s.push(pivotloc+1);
				s.push(high);
			}
		}
	}
}
//************************************************************


//************************************************************
//利用快排思想找到数组第k个最小的元素
int kth_small_num(int *a,int left,int right,int k)
{
	int low = left,high = right;
	int pivotloc = partition(a,low,high);
	int dist = pivotloc - low +1;
	if(dist == k)
		return a[pivotloc];
	else if(dist < k)
		return kth_small_num(a,pivotloc+1,high,k-dist);
	else
		return kth_small_num(a,low,pivotloc-1,k);

}
//************************************************************


//************************************************************
void bubble_sort(int *a,int arraysize)
{
	int i=arraysize-1;//赋值给最后一个元素下标
	int j=0;
	int lastexchangeindex;

	while(i>0)
	{
		lastexchangeindex = 0;//每次循环将其初始化为0,如果以后没有交换，则直接退出循环

		for(j=0;j<i;j++)//注意j只能取到倒数第二个元素，因为下面的j+1取得是最后一个元素
		{
			if(a[j] > a[j+1])
			{
				swap(a[j],a[j+1]);//函数原型要用传引用
				lastexchangeindex = j;//记录数据元素交换的位置，从j到最后一个元素均已排好序
			}
		}
		i = lastexchangeindex;//缩小待排序序列
	}
}
//************************************************************
for(i=1;i<n;i++)//N个元素，则需要进行N-1趟排序
		for(j=0;j<n-i;j++)
//************************************************************
void bubble_sort(int *a, int start, int end){
    if(a == NULL) return ;
    bool exchange;
    for(int i = start+1; i < =end; ++i){
        exchange = false;
        for(int j = start; j <= end - i; ++j){
            if(a[j] > a[j + 1]){
                swap(a[j], a[j + 1]);
                exchange = true;
            }
        }
        if(!exchange) return;
    }
}
//************************************************************

//************************************************************
void merge(int array[],int temp[],int start,int mid,int end)//设end指向最后一个元素的下标
{
	int i=start,k=start,j=mid+1;
	for(i;i<=end;i++)
		temp[i] = array[i];
	i=start;//i记得复位 

	while(i<=mid && j<=end)
	{
		if(temp[i] < temp[j])
			array[k++]=temp[i++];
		else
			array[k++]=temp[j++];
	}
	
	while(i<=mid)	array[k++]=temp[i++];
	while(j<=end)	array[k++]=temp[j++];
}

void merge_sort(int array[],int temp[],int start,int end)
{
	if(NULL == array || NULL == temp)	return;
	if(start<end)
	{
		int mid=start+((end-start)>>1);
		merge_sort(array,temp,start,mid);
		merge_sort(array,temp,mid+1,end);
		merge(array,temp,start,mid,end);
	}
	
}

//************************************************************
//设array【start】~array[mid],array[mid+1]~array[end]为两个有序，通过两个半数组的元素的比较，来求取数组的逆序数
int mmerge(int array[],int temp[],int start,int mid,int end)//设end指向最后一个元素的下标
{
	int i=start;
	for(i;i<=end;i++)
		temp[i] = array[i];

	i=mid;
	int j=end,k=end,count=0;

	while(i>=start && j>=(mid+1))
	{
		if(temp[i] > temp[j])
		{
			count+=j-mid;
			array[k--] = temp[i--];
			
			
		}
		else
			array[k--] = temp[j--];
	}
	while(i>=start)	array[k--]	= temp[i--];
	while(j>=mid+1)	array[k--]	= temp[j--];

	return count;
}

//用于求数组array【】的逆序数
int mmerge_count(int array[],int temp[],int start,int end)//设end指向最后一个元素的下标
{
	if(NULL == array || NULL == temp)
		return 0;

	if(start < end)
	{
		int mid = start + ((end-start)>>1);
		int left = mmerge_count(array,temp,start,mid);
		int right = mmerge_count(array,temp,mid+1,end);
		int own = mmerge(array,temp,start,mid,end);
		return left+right+own;
	}
	return 0;
}
//************************************************************


//************************************************************
void swap(int& a,int& b)
{
	int temp=a;
	a=b;
	b=temp;
}

void selection_sort(int array[],int n)
{
	int i=0,j=0;
	int min_index;
	for(i=0;i<n;i++)
	{
		min_index = i;//通过保存待排序元素的最小元素的下标来实现
		for(j=i+1;j<n;j++)
		{
			if(array[j] < array[min_index])
				min_index = j;//修改最小元素的下标
		}
		if(min_index != i)	//如果最小元素下标不是自己，则交换元素
			swap(array[i],array[min_index]);
	}
}
//************************************************************

//************************************************************
void straight_insert_sort(int array[],int low,int high)
{
	if(array == NULL || low == high)	return;
	int i=low+1,j=0;
	int temp;
	for(i;i<=high;i++)
	{
		temp=array[i];
		for(j=i-1;j>=low && array[j]>temp;j--)
		{
			array[j+1] = array[j];
		}
		array[j+1] = temp;
	}
}
//************************************************************

//************************************************************
void shell_insert(int array[],int low,int high,int gap)
{
	int i,j,temp;
	for(i=low+gap;i<=high;i++)
	{
		temp = array[i];
		for(j=i-gap;j>=low && temp < array[j];j-=gap)
		{array[j+gap] = array[j];}
		array[j+gap] = temp;
	}
}


void shell_sort(int array[],int low,int high)
{
	if(array == NULL)	return;
	int gap= high-low;
	while(gap>1)
	{
		gap=gap/3+1;
		shell_insert(array,low,high,gap);
	}
}
//************************************************************

//************************************************************
void swap(int& a,int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

void fixup(int a[],int k)
{
	while(k>1 && a[k] > a[k/2])//从第k个元素开始，将其与父节点进行比较，如果比父节点大，则与父节点交换
							//while退出条件：k==1即到达根节点，或该节点比父节点小（不大），即满足堆性质
	{
		swap(a[k],a[k/2]);
		k=k/2;
	}
}

void fixdown(int a[],int k,int aSize)//数组大小为aSize,从第k个元素开始，向叶子节点移动
{
	int j=0;
	while(2*k <= aSize)//如果子节点存在
	{
		j= 2*k;
		if(j<aSize && a[j] < a[j+1])	j++;//找到子节点中较大的一个
		if(a[k] > a[j])	break;//如果满足堆性质，则跳出循环
		swap(a[k],a[j]);
		k=j;//否则交换节点，更新节点下标
	}
}

void heap_sort(int a[],int low,int high)
{
	if(a == NULL || low == high)	return;
	int *p=a+low-1;//为了使传递的数组的下标仍为原数组的第一个和最后一个元素的下标，
	//故将p指向原数组的前一个元素,这样在下面以p为参数调用fixdown,可满足k的子节点的序号为2*k,2*k+1.
	int aSize = high - low +1;

	for(int i=aSize/2;i>=1;i--)//从最后一个节点的父节点开始后向扫描，对于每一个节点，
		fixdown(p,i,aSize);		//调用fixdown，使以该节点为根的子树满足堆性质		

	while(aSize > 1)
	{
		swap(p[1],p[aSize]);//将堆顶元素交换到最后一个
		aSize--;		//对堆大小减一
		fixdown(p,1,aSize);//将根节点重新调整为大顶堆
	}
}
//************************************************************


//************************************************************
//创建一个优先队列。若用优先队列排队的话，可以先将数组元素入队，然后将出队的元素逆序输出到数组中即可。
priority_queue pq(3);
	for(i;i<3;i++)	pq.push_back(a[i]);
	for(i=2;i>=0;i--)	
	{
		a[i] = pq.top();
		pq.pop();
	}
	
	
void swap(int& a,int &b)
{
	int temp = a;
	a = b;
	b = temp;
}
void fixup(int a[],int k)
{
	while(k>1 && a[k] > a[k/2])//从第k个元素开始，将其与父节点进行比较，如果比父节点大，则与父节点交换
							//while退出条件：k==1即到达根节点，或该节点比父节点小（不大），即满足堆性质
	{
		swap(a[k],a[k/2]);
		k=k/2;
	}
}

void fixdown(int a[],int k,int aSize)//数组大小为aSize,从第k个元素开始，向叶子节点移动
{
	int j=0;
	while(2*k <= aSize)//如果子节点存在
	{
		j= 2*k;
		if(j<aSize && a[j] < a[j+1])	j++;//找到子节点中较大的一个，注意if的条件
		if(a[k] > a[j])	break;//如果满足堆性质，则跳出循环
		swap(a[k],a[j]);
		k=j;//否则交换节点，更新节点下标
	}
}

class priority_queue
{
public:
	int capacity;
	int size;
	int *elem;
public:
	priority_queue(int max)
	{
		capacity = max;
		size = 0;
		elem = (int *)malloc((max+1)*sizeof(int));
	}

	
	~priority_queue()
	{
		free(elem);
	}

	void push_back(int val)
	{
		if(size == capacity)
			{
				this->elem = (int*)realloc(this->elem,(2*capacity+1)*sizeof(int));
			}
		size +=1;
		elem[size] = val;
		fixup(this->elem,size);
	}
	void pop()
	{
		swap(this->elem[1],this->elem[size]);
		size--;
		fixdown(this->elem,1,size);
	}
	int top()
	{
		return	this->elem[1]; 
	}
	int empty()
	{
		return size == 0;
	}

};

//************************************************************

//************************************************************
void count_sort(int a[],int n,int k)//n为元素个数，k为n个元素的最大值
{
	int *count=(int*)malloc((k+1)*sizeof(int));
	memset(count,0,(k+1)*sizeof(int));
	int i=0,j=0;

	for(i=0;i<n;i++)
		count[a[i]]++;//统计每个元素出现的次数
	for(i=1;i<=k;i++)
		count[i]+= count[i-1];//统计小于等于该元素的个数

	int *b=(int*)malloc(n*sizeof(int));
	for(j=0;j<n;j++)
	{
		b[ count[a[j]]-1]	= a[j];//将a[j]直接放到合适的位置上去，例如小于等于a[j]的元素有count[a[j]]个，
								//故将a[j]放到count[a[j]] -1的位置上去；然后将count[a[j]]--,是为了存在
								//相同的元素a[j]时，将其放到另一个合适的位置
		count[a[j]]--;
	}
	for(i=0;i<n;i++)
		a[i] = b[i];
}

void count_sort2(int a[],int n,int k)
{
	int *count=(int*)malloc((k+1)*sizeof(int));
	memset(count,0,(k+1)*sizeof(int));//注意必须对malloc分配的内存进行清0，不能认为对其中的内容做任何假设
	int i=0,j=0;
	for(i=0;i<n;i++)
		count[a[i]]++;//统计每个元素出现的次数

	for(i=0;i<=k;i++)
	{
		while(count[i]-- > 0)//从小到大，若该元素i出现，则将其赋值给数组a，因为元素i可能存在重复，
								//故要对其出现的次数做一个while循环
			a[j++]=i;
	}
}
//************************************************************