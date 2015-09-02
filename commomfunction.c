1，stdio.h
(1)文件操作：
FILE *fopen(const char *filename,const char* mode);
	//fopen函数打开filename指定的文件，并返回一个与之相关联的流。如果打开操作失败，则返回NULL；
int fflush(FILE *stream)
	//对输出流来说，fflush函数将已写到缓冲区但尚未写入文件的所有数据写到文件中。对输入流来说，其结果是未定义的。
		//如果在写的过程中发生错误，则返回EOF，否则返回0.fflush（NULL）将清洗所有的输出流。
int fclose(FILE *stream)
	//	fclose函数将所有未写入的数据写入stream中，丢弃缓冲区中的所有未读输入数据，并释放自动分配的全部缓冲区，最后关闭流。
		//若出错误，则返回EOF，否则返回0
（其他待加）
（2）格式化输出
int fprintf(FILE *stream,const char* format,...);
int printf(const char* format,...);
int sprintf(char* s,const char* format,...);

int vfprintf(FILE *stream,const char* format,va_list arg);
int vprintf(const char* format,va_list arg);
int vsprintf(char* s,const char* format,va_list arg);
vfprintf,vprintf,vsprintf与对应的printf函数等价，但它们用arg代替了可变参数集合。
(3)格式化输入
int fscanf(FILE *stream,const char* format,...);
int scanf(const char* format,...);
int sscanf(const char* s,const char* format,...);
(4)字符输入/输出函数
int fgetc(FILE *stream)
	fgetc函数返回stream流的下一个字符，返回类型为unsigned char(被转换为int类型)。如果到达文件末尾或发生错误，则返回EOF。
char* fgets(char *s,int n,FILE *stream)
	fgets函数最多将下n-1个字符读入到数组s中。当遇到换行符时，把换行符读入到数组s中，读取过程终止。数组s以‘\0’结尾。fgets函数返回数组s。
	如果到达文件的末尾或发生错误，则返回NULL；
int fputc(int c,FILE *stream)
	fputs函数把字符c（转换为unsigned char类型）输出到流stream中。他返回写入的字符，若出错，则返回EOF。
int fputs(const char *s,FILE *stream)
	fputs函数把字符串s（不包含字符‘\n’）输出到流stream中；它返回一个非负值，若出错，则返回EOF。
int getc(FILE *stream)
	getc函数等价于fgetc。
int getchar(void)
	getchar函数等价于getc(stdin)
char* gets(char *s)
	gets函数把下一个输入行读入到数组s中，并把末尾的换行符替换为字符‘\0’，它返回数组s，如果到达文件的末尾或发生错误，则返回NULL；
int putc(int c,FILE* stream)
	putc等价于fputc.
int putchar(int c)
	putchar(c)等价于putc(c,stdout)
int puts(const char* s)
	puts函数把字符串s和一个换行符输出到stdout中。如果发生错误，则返回EOF;否则，返回一个非负值。
（5）直接输入/输出函数
size_t fread(void* ptr,size_t size,size_t nobj,FILE* stream)
	fread函数从流stream中读取最多nobj个长度为size的对象，并保存到ptr指向的数组中。它返回读取的对象数目，此返回值可能小于nobj。必须通过函数feof和ferror获得结果执行状态。
size_t fwrite(const void *ptr,size_t size,size_t nobj,FILE* stream)
	fwrite函数从ptr指向的数组中读取nobj个长度为size的对象，并输出到流stream中。它返回输出的对象数目。如果发生错误，返回值会小于nobj。
（6）文件定位函数
int fseek(FILE* stream,long offset,int origin)
	fseek函数设置流stream的文件位置，后续的读写操作将从新的位置开始。对于二进制文件，此位置被设置为从origin开始的第offset个字符处。origin的值可以为SEEK_SET(文件开始处)，丢弃缓冲区中的所有未读输入数据，并释放自动分配的全部缓冲区，最后关闭流。
	SEEK_CUR（当前位置）或SEEK_END（文件结束处）。对于文本流，offset必须设置为0，或者说由ftell返回的值（此时origin的值必须是SEEK_SET）。fseek函数出错时，返回一个非负值。
long ftell(FILE *stream)
	ftell函数返回stream流的当前文件位置。出错时，该函数返回-1L
void rewind(FILE* stream)
	rewind(fp)等价于语句fseek(fp,0L,SEEK_SET);clearerr(fp)的执行结果。
int fgetpos（FILE* stream，fpos_t *ptr）
	fgetpos函数把stream流的当前位置记录在*ptr中，供随后的fsetpos函数调用使用。若出错，则返回一个非0值。
int fsetpos（FILE* stream,const fpot_t *ptr）
	fsetpos函数将流stream的当前位置设置为fgetpos记录在*ptr中的位置。若出错，则返回一个非0值。
（7）错误处理函数
void clearerr(FILE* stream)
	

int feof(FIEL* stream)
	如果设置了与stream流相关的文件结束符，feof将返回一个非0值。
int ferror(FIEL* stream)
	如果设置了与stream流相关的错误指示符，ferror将返回一个非0值。	
void perror(const char* s)
	perror(s)函数打印字符串s以及errno中整型值相应的错误信息。该函数的功能类似于执行下列语句：
fprintf(stderr,"%s:%s\n",s,"error message");

B.2字符类别测试<ctype.h>  //每个函数的参数均为int类型，参数的值必须是EOF或可用unsigned char 类型表示的字符，函数的返回值为int类型。
isalnum(c) //函数isalpha(c)或isdigit(c)为真
isalpha(c)//函数isupper(c)或islower(c)为真
iscntrl(c)// c为控制字符
isdigit(c)//c为十进制数字
isgraph(c)//c是除空格外的可打印字符
islower(c)//c是小写字母
isprint(c//c是包括空格的可打印字符
ispunct（c）//c是除空格、字母和数字外的可打印字符
isspace(c)//c是空格、换页符、换行符、回车符、横向制表符或者纵向制表符
isupper(c)//c是大写字母
isxdigit(c)//c是十六进制数字
在7位ASCII字符集中，可打印字符是从0x20(' ')到0x7E('~')之间的字符；控制字符是从0(NUL)到0x1F(US)之间的字符以及字符0x7F(DEL)
int tolower(c)//如果c是大写字母，则tolower(c)返回相应的小写字母，否则返回c。
int toupper(c)//如果c是小写字母，则toupper（c）返回相应的大写字母，否则返回c。


B.3字符串函数<string.h>
//定义了两组字符串函数，第一组以str开头，第二组以mem开头。除函数memmove外，其他函数都没有定义对象间的复制行为。
//比较函数把参数作为unsigned char类型的数组看待。
//在下表中，变量s，t的类型为char *,cs，ct的类型为const char* ，n的类型为size_t；c的类型为int（将被转换为char类型）
char *strcpy(s,ct)//将字符串ct（包括'\0'）复制到字符串s中，并返回s.//不管s是否越界，总是将ct中包括'\0'及之前的内容复制到s中
char *strncpy(s,ct,n)//将字符串ct中最多n个字符复制到字符串s中，并返回s.如果ct中少于n个字符，则用‘\0’填充。如果ct中多于n个元素，则将这n个元素（不包括‘\0’）复制到s中
char *strcat(s,ct)//将字符串ct连接到s的尾部，并返回s//不管s是否越界，总是将ct中包括'\0'及之前的内容复制到s尾部
char *strncat(s,ct,n)//将字符串ct中最多前n个字符连接到s的尾部，并以'\0'结束并返回s，/不管s是否越界，总是将ct中n个元素复制到s尾部，然后在这n个元素之后加上一个'\0'，
					//如果ct中少于n个字符，则用‘\0’填充。
int strcmp(cs,ct)//
int strncmp(cs,ct,n)
char *strchr(cs,c)//返回指向字符c在字符串cs中第一次出现的位置的指针；如果cs中不包含c，则返回NULL
char* strrchr(cs,c)//最后一次出现的位置的指针
char* strpbrk(cs,ct)//返回一个指针，依次检验字符串s1中的字符，当被检验字符在字符串s2中也包含时，则停止检验，并返回该字符位置，空字符null不包括在内。
char* strstr(cs,ct)//返回一个指针，它指向字符串ct第一次出现在字符串cs中的位置；如果字符串ct中不包含字符串ct，则返回NULL；
size_t strlen(cs)//返回字符串的长度
char* strerror(n)//返回一个指针，它指向与错误编号n对应的错误信息字符串
char* strtok(s,ct)//在s中搜索由ct中的字符界定的记号。
//对strtok(s,ct)进行一系列调用，可以把字符串s分成许多记号，这些记号以ct中的字符为分解符。第一次调用时，s为非空。它搜索s，找到不包含ct中字符的第一个记号，
//将s中的下一个字符替换为‘\0’，并返回指向记号的指针。随后每次调用strtok函数时（由s的值是否为NULL指示），均返回下一个不包含ct中字符的记号。当s中没有这样记号时，它返回NULL。
//每次调用时字符串ct可以不同。

//以mem开头的函数按照字符数组的方式操作对象，其主要目的是提供一个高效的函数接口。
在下表列出的函数中，s和t的类型均为void*,cs，ct的类型均为const void *,n的类型为size_t,c的类型为int。
void* memcpy(s,ct,n)//将字符串ct中的n个字符拷贝到s中，并返回s
void* memmove(s,ct,n)//该函数的功能与memcpy相似，所不同的是，当对象重叠时，该函数仍能正确执行。
int memcmp(s,ct,n)//将cs的前n个字符与ct进行比较。
void* memset(s,c,n)//将s中的前n个字符设置为c
void* memchr(cs,c,n)//返回一个指针，它指向c在cs中第一次出现的位置。如果在cs的前n个字符中找不到匹配，则返回NULL

B.4数学函数<math.h>
在下表中，x,y的类型为double,n的类型为int，所有函数的返回值的类型均为double。三角函数的角度用弧度表示。
sin(x),cos(x),tan(x),asin(x),acos(x),atan(x),atan2(y,x),sinh(x),cosh(x),tanh(x),
exp(x)//幂函数e的x次方
log(x)//自然对数ln(x)
log10(x)//以10为底的对数
pow(x,y)//x的y次方
sqrt(x)//平方根
ceil(x)//不小于x的最小整数
floor(x)//不大于x的最大整数
fabs（x）//x的绝对值
ldexp(x,n)//计算x*2的n次方
modf(x,double* ip)//把x分成整数部分和小数两部分，两部分的正负号均与x相同。该函数返回小数部分，整数部分保存在*ip中
fmod(x,y)//求x/y的浮点余数，符号与x相同。如果y为0，则结果与具体的实现相关。


B.5  使用函数<stdlib.h>
double atof(const char* s)//将字符串s转换为double类型，该函数等价于strtod(s,(char**)NULL);
int aoti(const char* s)//将字符串s转换为int类型，该函数等价于(int)strtod(s,(char**)NULL,10);
long atol(const char* s)//将字符串s转换为long类型，该函数等价于strtod(s,(char**)NULL,10);
double strtod(const char *s,char **endp);//该函数将字符串s的前缀转换为double类型，并在转换时跳过s的前导空白符。除非endp为NULL,否则该函数将把指向s中未转换部分（s的后缀部分）
//的指针保存在在*endp中。如果结果上溢，则函数返回带有适当符号的HUGE_VAL；如果结果下溢，则返回0.在这两种情况下，errno都将被设置为ERANGE。
long strtol（const char *s,char **endp，int base）//该函数将字符串s的前缀转换为long类型，并在转换时跳过s的前导空白符。除非endp为NULL,否则该函数将把指向s中未转换部分（s的后缀部分）
//的指针保存在在*endp中。如果base的取值在2~36之间，则假定输入是以该数为基底的；如果base的取值为0，则基底为八进制、十进制或十六进制。以0为前缀的是八进制，以0x或0X为前缀
//的是十六进制，如果结果上溢，则函数根据结果的符号返回LONG_MAX或LONG_MIN,同时将errno的值设置为ERANGE。
unsigned long strtoul（const char *s,char **endp，int base）//功能同strtol，只是结果为unsigned long
int rand(void)//产生一个0~RAND_MAX之间的伪随机数
void srand(unsigned int seed)//srand函数将seed作为生成新的伪随机数序列的种子数。种子数seed的初值为1.
void *calloc(size_t nobj,size_t size)//calloc函数为由nobj个长度为size的对象组成的数组分配内存，并返回指向分配区域的指针；若无法满足要求，则返回NULL，
void *malloc(size_t size)//该函数为长度为size的对象分配内存，并返回指向分配区域的指针，若无法满足要求，则返回NULL，该函数不对分配的区域进行初始化。
void *realloc(void*p,size_t size)//realloc函数将p指向的对象的长度修改为size个字节。如果新分配的内存比原内存大，则原内存的内容保持不变，增加的空间不进行初始化。如果新分配的
//内存比原内存小，则新分配内存单元不被初始化。若无法满足要求，则返回NULL，在这种情况下，原指针p指向的单元内容保持不变。
void free(void *p);//释放p指向的内存空间。当p的值为NULL时，该函数不执行任何操作。p必须指向先前使用动态分配函数分配的空间。
void abort(void)//abort函数使程序非正常终止。其功能与raise（SIGABRT）相似。
void exit(int status)//exit函数使程序正常终止。atexit函数的调用顺序与登记的顺序相反，这种情况下，所有已打开的文件缓冲区将被清洗，所有已打开的流将被关闭，控制也将返回给环境。
//0值表示终止成功，也可以使用EXIT_SUCCESS，和EXIT_FAILURE作为返回值。
int atexit(void (*fcn)())//atexit函数登记函数fcn，该函数将在程序正常终止时被调用。如果登记失败，则返回非0值。
int system(const char* s)//system函数将字符串s传递给执行环境。如果s的值为NULL,并且有命令处理程序，则该函数返回非0值。如果s的值不是NULL，则返回值与具体的实现有关。
char* getenv(const char* name)//返回与name有关的环境字符串。如果该字符串不存在，则返回NULL。

void* bsearch（const void *key,const void *base,size_t n,size_t size,int (*cmp)(const void*keyval,const void *datum)）
//bsearch函数在base[0]...base[n-1]之间查找与*key匹配的项。在函数cmp中，如果第一个参数（查找关键字）小于第二个参数（表项），它必须返回一个负值；
//如果第一个参数等于第二个参数，它必须返回0；如果第一个参数大于第二个参数，它必须返回一个正值；数组base中的项必须按升序排列。bsearch函数返回一个指针，它指向一个匹配项，
//如果不存在匹配项，则返回NULL。
void qsort(void *base,size_t n,size_t size,int (*cmp)(const void*,const void *))
//qsort函数对base[0]...base[n-1]数组中的对象进行升序排序，数组中每个对象的长度为size。比较函数cmp与bsearch函数中的描述相同。
int abs(int n)
//abs返回int类型参数n的绝对值
long labs(long n)
//labs返回long类型参数n的绝对值

div_t div(int num,int denom)
//div函数计算num/denom的商和余数，并把结果分别保存在结构类型div_t的两个int类型的成员quot和rem中
ldiv_t div(long num,long denom)
//div函数计算num/denom的商和余数，并把结果分别保存在结构类型div_t的两个long类型的成员quot和rem中


B.6 诊断<assert.h>
void assert(int 表达式)
//如果执行assert(表达式)，而表达式的值为0，则assert宏将在stderr中打印一条消息
//如果定义宏NDEBUG,同时又包含了头文件<assert.h>，则assert宏将被忽略。     

B.9 信号<sighal.h>
void (*signal(int sig,void （*handler）(int)))(int)
signal决定了如何处理后续的信号。如果handler的值是SIG_DFL，则采用由实现定义的默认行为；如果handler的值是SIG_IGN,则忽略该信号；否则，调用handler指向的函数（以信号作为参数）
对于特定的信号，signal将返回handler的前一个值，如果出现错误，则返回值SIG_ERR

int raise(int sig)//向程序发送信号sig，如果发送不成功，则返回一个非0值

B.10
clock_t clock(void)//函数返回程序开始执行后占用的处理器时间。如果无法获取处理器时间，则返回值为-1.clock()/CLOCKS_PER_SEC是以秒为单位表示的时间。










































































































