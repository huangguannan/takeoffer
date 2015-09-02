void *memset(void *dest,int c,int count)
{
	assert(dest!=NULL);
	char *s =(char*)dest;

	while(count--)
		*s++ = (char)c;
	return dest;
}

void *memcpy(void *dest,const void* src,size_t count)
{
	assert( dest!=NULL && src != NULL);
	char *d = (char*)dest;
	const char* s = (const char*)src;

	while(count--)
		*d++ = *s++;
	return dest;
}

void *memmove(void *dest,const void*src,size_t count)
{
	assert(dest != NULL && src != NULL);
	char *d = (char*)dest;
	const char *s = (const char*)src;

	if(dest <= src)
	{
		while(count--)
			*d++ = *s++;
	}
	else
	{
		d += count;
		s += count;

		while(count--)
			*--d = *--s;
	}
	return dest;//尼玛void*是要有返回值得啊，兄弟。
}

int memcmp(const void* cs,const void *ct,size_t count)
{
	const unsigned char *cs1 =(const unsigned char*)cs;
	const unsigned char *ct1 =(const unsigned char*)ct;
	int res = 0;
	while(count--)
	{
		if( (res = *cs1++ - *ct1++) != 0)//没有对*cs是否结束进行判断
			break;
	}
	return res;
}

char* strcpy1(char *dest,const char*src)
{
	assert(dest != NULL && src !=NULL);
	char *d = dest;
	while( (*d++ = *src++) !='\0');
	return dest;
}

char* strncpy(char *dest,const char *src,size_t count)
{
	assert(dest!=NULL && src!=NULL);
	char *d = dest;
	while(count)
	{
		if( (*d = *src) !='\0')
		{
			src++;
			d++;
			count--;
		}
		else
			break;
	}
	return dest;
}


char* strcat1(char *dest,const char *src)
{
	char *d =dest;

	while(*d)
		d++;
	while((*d++ = *src++)!='\0');
	return dest;
}

char* strncat(char* dest,const char *src,size_t count)
{
	char *d = dest;

	if(count)
	{
		while(*d)
			d++;
		while( (*d++ = *src++) != 0)//如果元素小于count个，自然会将\0加上
		{
			if(--count == 0)
			{
				*d = '\0';
				break;
			}
		}
	}
	return dest;
}


int strcmp(const char *cs,const char *ct)
{
	while(*cs == *ct)
	{
		if(*cs == '\0')
			return 0;
		cs++;ct++;
	}
	return *cs-*ct;
}

int strncmp(const char *cs,const char *ct,size_t count)
{
	while(count && (*cs == *ct))
	{
		if(*cs == '\0')
			return 0;
		cs++;ct++;count--;
	}
	return *cs-*ct;
}

size_t strlen(const char* s)
{
	const char* cs = s;
	for(;*cs != '\0';++cs)
		;
	return cs - s;
}

char* strchr1(const char *s,int c)
{
	for(;*s != (char)c;++s)
		if(*s == '\0')
			return NULL;

		return (char *)s;
}

char* strstr1(const char* s1,const char *s2)
{
	if(!s1 || !s2)return NULL;
	int i = 0,j = 0;
	for(i = 0;i<strlen(s1);i++)
	{
		for(j = 0;j<strlen(s2);j++)
		{
			if(s2[j] == '\0')return (char*)s1+i;
			if(s1[i] == '\0')return NULL;
			if(s1[i+j] != s2[j]) break;
		}
	}
	return NULL;
}

/*从*stringp指向的位置起向后扫描，遇到delim指向的字符串中的字符后，将此字符替换为NULL，返回stringp指向的地址。
然后，*stringp更新为指向分隔符的下一个位置*/
char* strsep(char **stringp,const char *delim)
{
	char *s;
	const char *spanp;
	int c,sc;
	char *tok;

	if((s = *stringp) == NULL)
		return NULL;
	for(tok = s;;)
	{
		c = *s++;
		spanp = delim;
		do
		{
			if( (sc = *spanp++) ==c)
			{
				if(c==0)
					s = NULL;
				else
					s[-1] = 0;
				*stringp = s;
				return (tok);
			}
		}while(sc != 0);
	}
	/*not reached*/
}

/*
可以看到 stringp 如果为 NULL 就回传 NULL，接下来进行每一个字的比对，如果发现到有 delim，
如果是在字符串结尾符号 \0，则将字符串设定为 NULL 并且更新 stringp，如果并非字符串结尾，
就将字符串(s)往前一个(delim 符号)，并且将其改变为 \0 分割点，且更新 *stringp 指向 delim 符号下一个字，回传初始字符串。
*/

//**********************************************************
/*strpbrk
依次检验字符串s1中的字符，当被检验字符在字符串s2中也包含时，z
则停止检验，并返回该字符位置，空字符null不包括在内。
*/

char* strpbrk1(const char *cs,const char *ct)
{
	
	const char *cs1,*ct1;
	for(cs1 = cs;*cs1 != '\0';++cs1)
	{
		for(ct1 = ct;ct1 != '\0';ct1++)
		{
			if(*cs1 == *ct1)
				return (char*)cs1;
		}
	}
	
	return NULL;
}

/*strtok:当strtok()在参数s的字符串中发现参数delim中包含的分割字符时,则会将该字符改为\0 字符。在第一次调用时，
strtok()必需给予参数s字符串，往后的调用则将参数s设置成NULL。每次调用成功则返回指向被分割出片段的指针。*/
//测试用例
#include<iostream>
#include<cstring>
using namespace std;
int test_strtok()
{
	char sentence[] = "This is a sentence with 7 tokens";
	cout<<"This string to be tokenized is:\n"<<sentence<<"\n\nThe tokens are:\n\n";
	char *tokenPtr = strtok(sentence,"");
	while(tokenPtr != NULL)
	{
		cout<<tokenPtr<<'\n';
		tokenPtr = strtok(NULL,"");
	}
	//cout<<"After strtok,sentence="<<tokenPr<<endl;
	return 0;
}

//求字符串中的最长数字子串
int maxContinueNum( char* instr,char* &outstr)
{
	if(instr == NULL) return 0;
	char *s = instr;
	char *temp = NULL;
	char *result = NULL;
	int maxlength = 0;
	int count = 0;

	while(*s != '\0')
	{
		if(isdigit(*s))
		{
			temp = s;
			count = 0;
			while((*s != '\0') && isdigit(*s))
			{
				count++;
				s++;
			}
			if(count > maxlength)
			{
				maxlength = count;
				result = temp;
			}
		}

		if(*s == '\0')	break;
		else	s++;
	}
	outstr = (char*)malloc(maxlength+1);
	memset(outstr,0,maxlength+1);
	memcpy(outstr,result,maxlength);
	return maxlength;
}


//求一个字符串中的最长子串，该子串是由同一个字符构成的
char* searchsameone(char *src)  
{
	if(src == NULL) return NULL;//在测试程序中，输出NULL之前，要先进行测试
	int maxlength = 1;
	char *s = src;
	char *result = src;
	char *temp = NULL;
	int count = 1;

	while(*s != '\0')
	{
		if(*(s+1)!='\0' && *s == *(s+1))
		{
			temp = s;
			count = 1;
			while(*(s+1)!='\0' && *s == *(s+1))
			{
				count++;
				s++;
			}
			if(maxlength < count)
			{
				maxlength = count;
				result = temp;
			}
		}
		if(*(s+1) == '\0') break;
		else s++;
	}

	char *returnresult = (char*)malloc(sizeof(char)*(maxlength+1));
//	memset(returnresult,0,maxlength+1);
	returnresult[maxlength] = '\0';
	memcpy(returnresult,result,maxlength);
	return returnresult;
}


int simpleAtoi(char *str)
{
	assert(str != NULL);
	int sum = 0;
	for(;*str != '\0' && isdigit(*str);str++)
		sum = sum*10+*str-'0';
	return *str == '\0' ? sum:0;
}


//求字符串翻转的高效利用空间
void reverse(char *s)
{
	if(!s) return;
	char *p1 = s;
	char *p2 = s;
	while(*p2)
		p2++;
	p2--;
	while(p1 < p2)
	{
		*p1 = (*p1)^(*p2);
		*p2 = (*p1)^(*p2);
		*p1 = (*p1)^(*p2);
		p1++;p2--;
	}
}


//在母串中查找子串出现的次数
int countofsubstring(const char* str,const char *s)
{
	if(!str || !s)return 0;
	int count = 0;
	const char* p = s;
	const char *pstr = str;
	
	while(*str)
	{
		p = s;pstr = str;
		while(*pstr == *p)
		{
			p++;
			pstr++;
			if(*p == '\0')//先增加完之后，再判断是否到达字符串的尾端
			{
				count++;
				break;
			}
		}
		str++;
	}
	return count;
}
//在母串中查找子串出现的次数2
int count1(char* str,char* s)
{
    char* s1;
    char* s2;
    int count = 0;
    while(*str!='/0')
    {
        s1 = str;
        s2 = s;
        while(*s2 == *s1&&(*s2!='/0')&&(*s1!='0'))
        {
            s2++;
            s1++;
        }
        if(*s2 == '/0')
            count++;
        str++;
    }
    return count;
}




1，/*1、google笔试：编码实现求给定字符串(全为小写英文字母)的最小后继，如"abc"的最小后继为"abd","dhz"的最小后继为"di"。*/
int MinNextStr(const char* src,char* &minnext)
{
	int srclen=strlen(src);
	minnext=(char*)malloc((srclen+1)*sizeof(char));
	if(minnext==NULL)
	{
		return -1;
	}
	strcpy(minnext,src);
	int i=srclen-1;
	while(i>=0)
	{
		minnext[i]++;
		if(minnext[i]<='z')
		{
			break;
		}
		i--;
	}
	if(i<0)
	{
		return 0;
	}
	else
	{
		minnext[++i]='\0';
		return 1;
	}
}

//15,给定一个字符串,求出其最长的重复子串。 
/*可以利用后缀数组来实现，如果某两个子串重复，则这两个子串必然是另外两个后缀子串的公共前缀
于是，我们可以先得到所有的后缀子串，存储在一个数组中。
（2）此时要求公共前缀，因此，可以对该数组进行排序，然后只需要检测两个相邻的数组元素
（3）取出最大公共长度的前缀即可。
*/

//版本1，利用string

//注意STL中sort的比较函数，返回值为bool类型，参数为具体的类型
bool cmp(string str1,string str2)
{
	return str1 < str2;
}

int getrepeatedsubstring(string str1,string str2)
{
	int count = 0;
	int i=0;
	while(str1[i]!='\n'&&str2[i]!='\n'&&str1[i]==str2[i])
	{
		count++;
		i++;
	}
	return count;
}

string getlongestrepeatedsubstring(string str)
{
	int len = str.size();
	int maxlen=0;
	int temp=0;
	int start=0;

	vector<string> v;//利用vector来存储字符数组

	int i=0;
	for(i=0;i<len;i++)
		v.push_back(str.substr(i,len-i));//substr来求得子串

	sort(v.begin(),v.end(),cmp);//对vector排序的方式
	cout<<"***********************************"<<endl;

	for(i=0;i<len-1;i++)
	{
		temp = getrepeatedsubstring(v[i],v[i+1]);
		if(maxlen < temp)
		{
			maxlen = temp;
			start = i;
		}
	}

	return v[start].substr(0,maxlen);
} 

//2,版本2，利用常规指针
bool cmp(char* str1,char *str2)
{
	if(strcmp(str1,str2)>0)
		return false;
	else
		return true;
	//或者直接
	//return strcmp(str1,str2)<0即可
}

int getrepeatedsubstring(char* str1,char* str2)
{
	int count = 0;
	while(*str1!='\n'&&*str2!='\n'&&*str1==*str2)
	{
		count++;
		str1++;
		str2++;
	}
	return count;
}

char* getlongestrepeatedsubstring(char *str)
{
	int len = strlen(str);
	int maxlen=0;
	int temp=0;
	int start=0;
	char **array = (char**)malloc(sizeof(char*)*len);
	int i=0;
	for(i=0;i<len;i++)
		array[i]=&str[i];//数组中存储的是子串的地址
//	for(i=0;i<len;i++)
//		cout<<array[i]<<endl;
	sort(array,array+len,cmp);//对数组排序
	cout<<"***********************************"<<endl;
//	for(i=0;i<len;i++)
//		cout<<array[i]<<endl;
	for(i=0;i<len-1;i++)
	{
		temp = getrepeatedsubstring(array[i],array[i+1]);
		if(maxlen < temp)
		{
			maxlen = temp;
			start = i;
		}
	}
	char *result = (char*)malloc(maxlen+1);
	memset(result,0,maxlen+1);
	memcpy(result,array[start],maxlen);
	return result;
} 
































