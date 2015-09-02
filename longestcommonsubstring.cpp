#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;



//��������Ӵ��ĳ���ⷨ
int longestcommonsubstring1(const string& str1,const string& str2)
{
	int size1 = str1.size();
	int size2 = str2.size();

	if(size1 == 0 ||size2 == 0)	return 0;

//	vector< vector<int> > tabel(size1,vector<size2,0>);

	int i = 0,j = 0;
	int m = 0,n = 0;
	int length;
	int longest = 0,startx = -1,starty =-1;

	for(i = 0;i<size1;i++)//
	{
		for(j = 0;j<size2;j++)//
		{
			m = i;n = j;length = 0;
			while(m<size1 && n < size2)
			{
				if(str1[m] != str2[n])	break;
				length++;
				m++;
				n++;
			}
			if(longest < length)
			{
				longest = length;
				startx = i;
				starty = j;
			}
		}
	}

	return longest;
}

/*
�����ⷨ�Ǵ��ַ������˿�ʼ��Ѱ�����ڻ���˼ά�������ַ���β���Ӵ������ö�̬�滮����
���������ַ����ֱ�Ϊs��t��s[i]��t[j]�ֱ��ʾ���i�͵�j���ַ�(�ַ�˳���0��ʼ)������L[i, j]
��ʾ��s[i]��s[j]Ϊ��β����ͬ�Ӵ�����󳤶ȡ�Ӧ�ò��ѵ��Ƴ�L[i, j]��L[i+1,j+1]֮��Ĺ�ϵ��
��Ϊ������ʵֻ��s[i+1]��t[j+1]��һ���ַ�����s[i+1]��t[j+1]��ͬ����ôL[i+1, j+1]��ȻӦ����0��
��Ϊ�κ�������Ϊ��β���Ӵ�����������ȫ��ͬ�������s[i+1]��t[j+1]��ͬ����ô��ֻҪ����s[i]��t[j]��β
�����ͬ�Ӵ�֮��ֱ������������ַ����ɣ������Ϳ����ó�������һλ���ϲ��������������Ҳ�͵õ�
L[i+1,j+1]=(s[i]==t[j]?L[i,j]+1:0)�����Ĺ�ϵ
������ҪС�ĵľ����ٽ�λ�ã����������ַ������κ�һ���ǿմ�����ô������Ӵ��ĳ���ֻ����0��
��iΪ0ʱ��L[0,j]Ӧ���ǵ���L[-1,j-1]�ټ���s[0]��t[j]�ṩ��ֵ����L[-1,j-1]������Ч����������s[-1]��
���ַ�Ҳ�ͱ����ǰ��һ���ٽ�����������Ϳ�֪L[-1,j-1]==0������L[0,j]=(s[0]==t[j]?1:0)��
����jΪ0Ҳ��һ���ģ�ͬ���ɵ�L[i,0]=(s[i]==t[0]?1:0)��

*/
//��������Ӵ��Ķ���ⷨ
int longestcommonsubstring2(const string& str1,const string& str2)
{
	int size1 = str1.size();
	int size2 = str2.size();

	if(size1 == 0 ||size2 == 0)	return 0;

	vector< vector<int> > table(size1,vector<int>(size2,0));//ע���ʼ���Ĳ�����ʽ

	int i = 0,j = 0;
//	int m = 0,n = 0;
//	int length;
	int longest = 0;
	int startx = -1,starty =-1;

	for(j = 0;j<size2;j++)
	{
		table[0][j] = (str1[0] == str2[j])?1:0; 
	}

	for(i = 1;i<size1;i++)
	{
		table[i][0] = (str1[i] == str2[0])?1:0;
		
		for(j = 1;j<size2;j++)
		{
			table[i][j] = (str1[i] == str2[j])?table[i-1][j-1]+1:0;
		}
	}

	for(i = 0;i<size1;i++)
	{
		for(j = 0;j<size2;j++)
		{
			if(longest < table[i][j])
			{
				longest = table[i][j];
				startx = i - longest + 1;
				starty = j - longest +1;
			}
		}
	}
	return longest;
}

enum flagb{LEFT_UP,LEFT,UP};


int longestcommonsubseqence(const string& str1,const string& str2,int *table[],int *flag[])
/*	vector< vector<int> > &table,vector< vector<int> > &flag*/
{
	int size1 = str1.size();
	int size2 = str2.size();

	if(size1 == 0 ||size2 == 0)	return 0;
	
	int i=0,j=0;

	

	for(i = 1;i<=size1;i++)
	{
		for(j= 1;j<=size2;j++)
		{
			if(str1[i-1] == str2[j-1])
			{
				table[i][j] = table[i-1][j-1] +1;
				flag[i][j] = LEFT_UP;
			}
			else
			{
				if(table[i-1][j] >= table[i][j-1])
				{
					table[i][j] = table[i-1][j];
					flag[i][j] = LEFT;
				}
				else
				{
					table[i][j] = table[i][j-1];
					flag[i][j] = UP;
				}
			}
		}
	}
	return table[size1][size2];
}

int longestcommonsubseqence2(const string& str1,const string& str2,int *table[],int *flag[])
{
	int size1 = str1.size();
	int size2 = str2.size();

	if(size1 == 0 ||size2 == 0)	return 0;
	
	int i=0,j=0;

	for(j=0;j<size2;j++)
	{
		table[0][j] = (str1[0] == str2[j])?1:0;
		flag[0][j] = (str1[0] == str2[j])?1:0;
	}

	for(i=0;i<size1;i++)
	{
		table[i][0] = (str1[i] == str2[0])?1:0;
		flag[i][0] = (str1[i] == str2[0])?0:-1;//��ȵ�ʱ����LEFT_UP(0)��ǣ�����ӡ
	}
	

	for(i = 1;i<size1;i++)
	{
		for(j= 1;j<size2;j++)
		{
			if(str1[i] == str2[j])
			{
				table[i][j] = table[i-1][j-1] +1;
				flag[i][j] = LEFT_UP;
			}
			else
			{
				if(table[i-1][j] >= table[i][j-1])
				{
					table[i][j] = table[i-1][j];
					flag[i][j] = UP;
				}
				else
				{
					table[i][j] = table[i][j-1];
					flag[i][j] = LEFT;
				}
			}
		}
	}
	return table[size1-1][size2-1];

	
}

void SubSequence(const string& str1,const string& str2,int i,int j,string& result,int *flag[])/*vector< vector<int> > &flag*/
{
	if(i ==-1 || j == -1)
		return;

	if(flag[i][j] == LEFT_UP)
	{
		cout<<str1[i]<<endl;
		SubSequence(str1,str2,i-1,j-1,result,flag);
		
		
		result+=str1[i];
	}	
	else
	{
		if(flag[i][j] == UP)
			SubSequence(str1,str2,i-1,j,result,flag);
		else
			SubSequence(str1,str2,i,j-1,result,flag);
	}
	
}
void test_seqence()
{
	string str1("acbac"),str2("acaccbabb");

	int size1 = str1.size(),size2 = str2.size();

	////////////////////����ռ�//////////////////////////////
		int i=0,j=0;
	int **table = (int**)malloc(sizeof(int*)*(size1));
	for(i = 0;i<size1;i++)
	{
		table[i] = (int*)malloc(sizeof(int)*(size2));
	}

	int **flag = (int**)malloc(sizeof(int*)*(size1));
	for(i = 0;i<size1;i++)
	{
		flag[i] = (int*)malloc(sizeof(int)*(size2));
	}
///////////////////////����ռ�///////////////////////////

	for(i=0;i<str1.size();i++)
	{
		for(j=0;j<str2.size();j++)
		{
			table[i][j] = 0;
			flag[i][j] = 0;
		}
	}
//	int n = longestcommonsubstring2(str1,str2);
	//cout<<n<<endl;
	string result;
	int n = longestcommonsubseqence2(str1, str2,table,flag);
	cout<<n<<endl;
	cout<<endl;

	for(i=0;i<size1;i++)
	{
		for(j=0;j<size2;j++)
			cout<<table[i][j]<<' ';
		cout<<endl;
	}
	cout<<"**********************"<<endl;

	for(i=0;i<size1;i++)
	{
		for(j=0;j<size2;j++)
			cout<<flag[i][j]<<' ';
		cout<<endl;
	}



	SubSequence(str1,str2, size1-1,size2-1,result,flag);
}
int main()
{
	
	return 0;
}