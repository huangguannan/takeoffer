#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;



//求最长公共子串的常规解法
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
暴力解法是从字符串开端开始找寻，现在换个思维考虑以字符结尾的子串来利用动态规划法。
假设两个字符串分别为s和t，s[i]和t[j]分别表示其第i和第j个字符(字符顺序从0开始)，再令L[i, j]
表示以s[i]和s[j]为结尾的相同子串的最大长度。应该不难递推出L[i, j]和L[i+1,j+1]之间的关系，
因为两者其实只差s[i+1]和t[j+1]这一对字符。若s[i+1]和t[j+1]不同，那么L[i+1, j+1]自然应该是0，
因为任何以它们为结尾的子串都不可能完全相同；而如果s[i+1]和t[j+1]相同，那么就只要在以s[i]和t[j]结尾
的最长相同子串之后分别添上这两个字符即可，这样就可以让长度增加一位。合并上述两种情况，也就得到
L[i+1,j+1]=(s[i]==t[j]?L[i,j]+1:0)这样的关系
最后就是要小心的就是临界位置：如若两个字符串中任何一个是空串，那么最长公共子串的长度只能是0；
当i为0时，L[0,j]应该是等于L[-1,j-1]再加上s[0]和t[j]提供的值，但L[-1,j-1]本是无效，但可以视s[-1]是
空字符也就变成了前面一种临界情况，这样就可知L[-1,j-1]==0，所以L[0,j]=(s[0]==t[j]?1:0)。
对于j为0也是一样的，同样可得L[i,0]=(s[i]==t[0]?1:0)。

*/
//求最长公共子串的动规解法
int longestcommonsubstring2(const string& str1,const string& str2)
{
	int size1 = str1.size();
	int size2 = str2.size();

	if(size1 == 0 ||size2 == 0)	return 0;

	vector< vector<int> > table(size1,vector<int>(size2,0));//注意初始化的参数方式

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
		flag[i][0] = (str1[i] == str2[0])?0:-1;//相等的时候用LEFT_UP(0)标记，即打印
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

	////////////////////分配空间//////////////////////////////
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
///////////////////////分配空间///////////////////////////

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