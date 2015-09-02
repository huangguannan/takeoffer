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
	return dest;//����void*��Ҫ�з���ֵ�ð����ֵܡ�
}

int memcmp(const void* cs,const void *ct,size_t count)
{
	const unsigned char *cs1 =(const unsigned char*)cs;
	const unsigned char *ct1 =(const unsigned char*)ct;
	int res = 0;
	while(count--)
	{
		if( (res = *cs1++ - *ct1++) != 0)//û�ж�*cs�Ƿ���������ж�
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
		while( (*d++ = *src++) != 0)//���Ԫ��С��count������Ȼ�Ὣ\0����
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

/*��*stringpָ���λ�������ɨ�裬����delimָ����ַ����е��ַ��󣬽����ַ��滻ΪNULL������stringpָ��ĵ�ַ��
Ȼ��*stringp����Ϊָ��ָ�������һ��λ��*/
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
���Կ��� stringp ���Ϊ NULL �ͻش� NULL������������ÿһ���ֵıȶԣ�������ֵ��� delim��
��������ַ�����β���� \0�����ַ����趨Ϊ NULL ���Ҹ��� stringp����������ַ�����β��
�ͽ��ַ���(s)��ǰһ��(delim ����)�����ҽ���ı�Ϊ \0 �ָ�㣬�Ҹ��� *stringp ָ�� delim ������һ���֣��ش���ʼ�ַ�����
*/

//**********************************************************
/*strpbrk
���μ����ַ���s1�е��ַ������������ַ����ַ���s2��Ҳ����ʱ��z
��ֹͣ���飬�����ظ��ַ�λ�ã����ַ�null���������ڡ�
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

/*strtok:��strtok()�ڲ���s���ַ����з��ֲ���delim�а����ķָ��ַ�ʱ,��Ὣ���ַ���Ϊ\0 �ַ����ڵ�һ�ε���ʱ��
strtok()����������s�ַ���������ĵ����򽫲���s���ó�NULL��ÿ�ε��óɹ��򷵻�ָ�򱻷ָ��Ƭ�ε�ָ�롣*/
//��������
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

//���ַ����е�������Ӵ�
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


//��һ���ַ����е���Ӵ������Ӵ�����ͬһ���ַ����ɵ�
char* searchsameone(char *src)  
{
	if(src == NULL) return NULL;//�ڲ��Գ����У����NULL֮ǰ��Ҫ�Ƚ��в���
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


//���ַ�����ת�ĸ�Ч���ÿռ�
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


//��ĸ���в����Ӵ����ֵĴ���
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
			if(*p == '\0')//��������֮�����ж��Ƿ񵽴��ַ�����β��
			{
				count++;
				break;
			}
		}
		str++;
	}
	return count;
}
//��ĸ���в����Ӵ����ֵĴ���2
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




1��/*1��google���ԣ�����ʵ��������ַ���(ȫΪСдӢ����ĸ)����С��̣���"abc"����С���Ϊ"abd","dhz"����С���Ϊ"di"��*/
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

//15,����һ���ַ���,���������ظ��Ӵ��� 
/*�������ú�׺������ʵ�֣����ĳ�����Ӵ��ظ������������Ӵ���Ȼ������������׺�Ӵ��Ĺ���ǰ׺
���ǣ����ǿ����ȵõ����еĺ�׺�Ӵ����洢��һ�������С�
��2����ʱҪ�󹫹�ǰ׺����ˣ����ԶԸ������������Ȼ��ֻ��Ҫ����������ڵ�����Ԫ��
��3��ȡ����󹫹����ȵ�ǰ׺���ɡ�
*/

//�汾1������string

//ע��STL��sort�ıȽϺ���������ֵΪbool���ͣ�����Ϊ���������
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

	vector<string> v;//����vector���洢�ַ�����

	int i=0;
	for(i=0;i<len;i++)
		v.push_back(str.substr(i,len-i));//substr������Ӵ�

	sort(v.begin(),v.end(),cmp);//��vector����ķ�ʽ
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

//2,�汾2�����ó���ָ��
bool cmp(char* str1,char *str2)
{
	if(strcmp(str1,str2)>0)
		return false;
	else
		return true;
	//����ֱ��
	//return strcmp(str1,str2)<0����
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
		array[i]=&str[i];//�����д洢�����Ӵ��ĵ�ַ
//	for(i=0;i<len;i++)
//		cout<<array[i]<<endl;
	sort(array,array+len,cmp);//����������
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
































