#include <iostream>
#include <queue>
#include <stack>
#include<iomanip>
#include<assert.h>
//#include <fstream>

using namespace std;
void swap(char &a,char &b)
{
	char temp = a;
	a = b;
	b = temp;
}

int max(int a,int b)
{
	return a>b?a:b;
}
/************************************************************/
char* mystrstr(char* s,char* t)
{
	if(s==NULL||t==NULL) return s;
	int i=0,j=0;
	
	for(i=0;;i++)
	{
		for(j=0;;j++)
		{
			if(t[j] == '\0') return s+i;
			if(s[i] == '\0') return NULL;
			if(s[i+j] != t[j]) break;
		}
	}
}


int mystrstr2(char *s,char *t)
{
	if(!s || !t) return -1;
	int i=0,j=0;

	for(i=0;;i++)
	{
		for(j=0;;j++)
		{
			if(t[j] == '\0') return i;
			if(s[i] == '\0') return -1;
			if(s[i+j] != t[j]) break;
		}
	}
}

//strstr:
/*
 * strstr - Find the first substring in a %NUL terminated string
 * @s1: The string to be searched
 * @s2: The string to search for
 */
char *strstr(const char *s1, const char *s2)
{
    int l1, l2;

    l2 = strlen(s2);
    if (!l2)
        return (char *)s1;
    l1 = strlen(s1);
    while (l1 >= l2) {
        l1--;
        if (!memcmp(s1, s2, l2))//借助库函数来对子字符串进行比较
            return (char *)s1;
        s1++;
    }

    return NULL;
}


/************************************************************/
//字符串匹配的KMP算法，还没有细看
void getNext(char *pat, int *next){
    int m = strlen(pat);
    next[0] = -1;
    int i, j = -1;
    for(i = 1; i < m; ++i){
        while(j > -1 && pat[i] != pat[j + 1]) j = next[j];
        if(pat[i] == pat[j + 1]) j++;
        next[i] = j;
    }
}

void kmp(char *txt, char *pat){
    if(txt == NULL || pat == NULL) return ;
    const int t_len = strlen(txt);
    const int p_len = strlen(pat);
    int *next = new int[p_len]();
    getNext(pat, next);

    int i, j = -1;
    for(i = 0; i < t_len; ++i){
        while(j > -1 && txt[i] != pat[j + 1]) j = next[j];
        if(txt[i] == pat[j + 1]) j++;
        if(j == p_len - 1){
            cout<<"found: " << i - j + 1 <<" ";
        }
    }
    delete next;
}

/************************************************************/
char* strcpy(char *to,char *from)
{
	assert(to != NULL && from != NULL);
	if(to == from)
		return to;
	char *p=to;
	while((*p++ = *from++)!='\0') 
		;
	return to;
}
/************************************************************/
char* my_strcat(char *dst,const char *src)
{
	if(dst == NULL || src == NULL) return dst;
	char *p=dst;
	while(*p != '\0') p++;
	while((*p++ = *src++)!='\0') 
		;
	return dst;
}
/************************************************************/
int strcmp(const char *str1,const char *str2)
{
	while(*str1 == *str2)
	{
		if(*str1 == '\0') return 0;
		str1++;str2++;
	}
	return *str1-*str2;
}

/************************************************************/
void* memcpy(void *dst,const void *src,size_t count)
{
	assert(dst != NULL && src != NULL);
	char *s_dst=(char*)dst;
	const char *s_src=(char*)src;
	for(size_t i=0;i<count;i++)
	{
		s_dst[i] = s_src[i];
	}
	return s_dst;
}
/************************************************************/
size_t strlen(const char *str)
{
	const char *s;
	for(s=str;*s;++s)
		;
	return (s-str);
}
/************************************************************/
int myAtoi(char* str) {
    if(str == NULL)//应该设置一个全局变量，以判断是空指针还是确实是-1
	{
		invalidflag = NULLSTR;
        return -1;
	}
    int sign,sum=0,temp;
    while(str && isspace(*str)) //是不是应该改为while(*str!='\0' && isspace(*str))
		str++;

     if(*str == '-') sign = -1;
        else    sign = 1;

		
    if(*str == '-' || *str == '+')
    str++;
    
    while(str && isdigit(*str))//是不是应该改为while(*str!='\0' && isspace(*str))
    {
        temp=*str-'0';
        if(sign>0 )
        {
            sum=((INT_MAX-temp)/10)>=sum?10*sum+temp:INT_MAX;
        }
        if(sign<0)
        {
            sum=((INT_MIN+temp)/10)<=sum?10*sum-temp:INT_MIN;
        }
        str++;
    }
    
    return sum;
}
/************************************************************/
void reverse(char *str,int s,int e)
{
	if(str == NULL) return;
	while(s<e)
	{
		swap(str[s++],str[e--]);
	}
}

char* rightRotate(char *str,int k)
//将字符串的右边的k个字母向右旋转使其到左边
{
	if(str == NULL) return NULL;

	int len = strlen(str);
	k%=len;
	k = len-1-k;
	reverse(str,0,k);
	reverse(str,k+1,len-1);
	reverse(str,0,len-1);
	return str;
}

char* leftRotate(char *str,int k)
//将字符串的左边的k个字母向左旋转使其到右边
{
	if(str == NULL) return NULL;
	int len = strlen(str);
	k%=len;
	reverse(str,0,k-1);
	reverse(str,k,len-1);
	reverse(str,0,len-1);

	return str;
}
/************************************************************/
int maxSymSubstring(char str[])
{
    char *fromStart2End, *left, *right;
    int length = 1, newlength;

    for (fromStart2End = str; *fromStart2End; fromStart2End++)
    {
        newlength = 1;            //对称子串可能为奇数时
        left = fromStart2End - 1;
        right = fromStart2End + 1;
        for (; left >= str && right <= str + strlen(str) - 1; --left, ++right)
            if (*left == *right)    newlength += 2;
            else    break;
        if (newlength > length)
            length = newlength;

        newlength = 0;           //对称子串可能为偶数时
        left = fromStart2End;
        right = fromStart2End + 1;
        for (; left >= str && right <= str + strlen(str) - 1; --left, ++right)
            if (*left == *right)    newlength += 2;
            else    break;
        if (newlength > length)
            length = newlength;
    }// for
    return length;
} 

/************************************************************/
//stl 中 string的源代码, stl 中string 是小写的
class String{
private:
    unsigned len;
    char *pbuf;
public:
    String() : len(0), pbuf(0){}
    String(const String&);
    String& operator=(const String&);
    ~String();
	
    String(const char * str);
    String& operator=(const char *s);
	
    const char& operator[](unsigned idx) const;
    char& operator[](unsigned idx);
	
    bool operator==(const String &other);
    String operator+(const String &other) const; // return value, not reference
	
    const char* c_str() const;
    unsigned length() const;
    unsigned size() const;
    friend ostream& operator<<(ostream &os, const String &s);
    friend istream& operator>>(istream &is, String &s);
};

String::String(const char *str) : len(0), pbuf(0){
    *this = str;
}

String::String(const String &s) : len(0), pbuf(0){
    *this = s;
}

String::~String(){
    if(pbuf != 0){
        delete[] pbuf;
        pbuf = 0;
    }
}
//this is not the best, use "copy and swap" is better to avoid exception in new operator
String& String::operator=(const char *s){
    this->~String();
    len = strlen(s);
    pbuf = strcpy(new char[len + 1], s);
    return *this;
}

String& String::operator=(const String &s){
    if(&s == this)
        return *this;
    this->~String();
    len = s.len;
    pbuf = strcpy(new char[len + 1], s.pbuf);
    return *this;
}

const char& String::operator[](unsigned idx) const{
    return pbuf[idx];
}

char& String::operator[](unsigned idx){
    return pbuf[idx];
}

String String::operator+(const String &other) const{
    String newString;
    if(other.pbuf == NULL){
        newString = *this;
    }else if(this->pbuf == NULL){
        newString = other;
    }else{
        newString.pbuf = new char[strlen(pbuf) + strlen(other.pbuf) + 1];
        strcpy(newString.pbuf, pbuf);
        strcat(newString.pbuf, other.pbuf);
    }
    return newString;
}

bool String::operator==(const String &other){
    if(strlen(pbuf) != strlen(other.pbuf)) return false;
    else return (strcmp(pbuf, other.pbuf) == 0 ? true : false);
}

const char* String::c_str() const{
    return pbuf;
}

unsigned String::length() const{
    return len;
}

unsigned String::size() const{
    return len;
}

ostream& operator<<(ostream &os, const String &s){
    os<<s.c_str();
    return os;
}

istream& operator>>(istream &is, String &s){
    //cout<<"here: " <<endl;
    char temp[256];
    is>>setw(256)>>temp;
    s = temp;
    return is;
}

/************************************************************/
//自己的版本：比较好理解的
int* getnext(string s)
{
	int length = s.length();
	int j = 0;
	int *next = new int[length+1];
	next[0] = next[1] = 0;
	/************************************/
	for(int i = 1;i<length;i++)
	{
		while(j>0 && s[i] != s[j])//初始时，满足j==next[i],以后每次第一次进入for循环时，也同样满足j==next[i]
			j = next[j];
		if(s[i] == s[j])
			j++;
		next[i+1] = j;
	}
/************************************/
	/*//上面的语句可以换成
	int k = 0;
	for(int i = 1;i<length;i++)
	{
		k = next[i];
		while(k>0 && s[i] != s[k])//初始时，满足j==next[i],以后每次第一次进入for循环时，也同样满足j==next[i]
			k = next[k];
		if(s[i] == s[k])
			k++;
		next[i+1] = k;
	}
	*/
	return next;//然后用的时候用，p=next+1;就好了
}

string KMP(string str,string pattern)
{
	int *next = getnext(pattern);
	int size1 = str.size();
	int size2 = pattern.size();

	int i =0;
	int j = 0;
	for(i=0;i<size1;i++)
	{
		while(j>0 && str[i] != pattern[j])
			j = next[j];
		if(str[i] == pattern[j])
			j++;
		if(j == size2)
			return  str.substr(i-j+1,size2);
	}
//	if(i == size1)
		return NULL;
}
/************************************************************/
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
/************************************************************/
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
/************************************************************/
//求最长公共子串：加入可以调用库函数的话，就简单多了
＃include<stdio.h>
＃include<stdlib.h>
＃include<string.h>
char *commanstring(char shortstring[], char longstring[])
{
    int i, j;
    char *substring=malloc(256);
    if(strstr(longstring, shortstring)!=NULL)              //如果……，那么返回shortstring
        return shortstring; 
    for(i=strlen(shortstring)-1;i>0; i--)                 //否则，开始循环计算
    {
        for(j=0; j<=strlen(shortstring)-i; j++)
        {
            memcpy(substring, &shortstring[j], i);
            substring[i]='/0';
            if(strstr(longstring, substring)!=NULL)
            return substring;
        }
    }
    return NULL;
}

main()
{
    char *str1=malloc(256);
    char *str2=malloc(256);
    char *comman=NULL;
    gets(str1);
    gets(str2);
    if(strlen(str1)>strlen(str2))                         //将短的字符串放前面
        comman=commanstring(str2, str1);
    else
        comman=commanstring(str1, str2);
    printf("the longest comman string is: %s/n", comman);
}
/************************************************************/
enum flagb{LEFT_UP,LEFT,UP};


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
/************************************************************/

int main()
{
	char pat[]="abcdabd";
	const int p_len = strlen(pat);
    int *next = new int[p_len]();
	getNext(pat, next);
	int i=0;
	for(i=0;i<p_len;i++)
	{
		cout<<next[i]<<' ';
	}
	cout<<endl;

	return 0;
}